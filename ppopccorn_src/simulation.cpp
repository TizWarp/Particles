#include "simulation.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Shader.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "defines.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "math.hpp"
#include "particle.hpp"
#include "ppopccorn.hpp"
#include "quadtree.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <string>
#include <thread>
#include <vector>

const int SUBSTEPS = 8;

void Simulation::init() {
  addParticle(5.0f, Vector2(50.0f, 50.0f), sf::Vector2(50.0f, 50.0f), 0);
  addParticle(5.0f, Vector2(-50.0f, -50.0f), sf::Vector2(50.0f, 50.0f), 0);
  this->window.create(sf::VideoMode(600, 400), "Ppopccorn",
                      sf::Style::Close | sf::Style::Resize);
  this->bounds = Bounds{Vector2(0.0f, 0.0f), Vector2(600.0f, 400.0f)};
  this->particle_max = 100;
  this->loop_bounds = true;
  this->quad_tree.resize(bounds);
  this->font.loadFromFile("./res/Symbola.otf");

  this->physics_paused = false;
  this->draw_quad_tree = false;
  this->initial_particle_quad_max = 32;

  this->object_va = sf::VertexArray(sf::Quads);

  this->thread_pool.Start();

  font.loadFromFile("./res/Symbola.otf");

  Simulation::interactions_enabled = false;
  Simulation::reactions_enabled = false;

  ImGui::SFML::Init(window, true);
}

void Simulation::addParticle(float radius, Vector2 position, Vector2 velocity,
                             uint8_t id) {
  Simulation::particles.push_back(Particle(radius, position, velocity, id));
}

void Simulation::physicsUpdate(float dt) {
  if (Simulation::particles.empty()) {
    return;
  }
  float substep_time = dt / SUBSTEPS;

  Vector2 heighest_particle = bounds.lower;
  Vector2 lowest_particle = bounds.upper;
  for (int particle_index = 0; particle_index < Simulation::particles.size();
       particle_index++) {
    Particle *particle = &particles[particle_index];
    if (particle->position.x > lowest_particle.x) {
      lowest_particle.x = particle->position.x;
    }
    if (particle->position.y > lowest_particle.y) {
      lowest_particle.y = particle->position.y;
    }
    if (particle->position.x < heighest_particle.x) {
      heighest_particle.x = particle->position.x;
    }
    if (particle->position.y < heighest_particle.y) {
      heighest_particle.y = particle->position.y;
    }
  }

  /*lowest_particle = lowest_particle - (lowest_particle * 0.25f);*/
  /*heighest_particle = heighest_particle * 1.25f;*/

  quad_tree.clear();
  quad_tree.resize(Bounds{heighest_particle, lowest_particle});
  quad_tree.generate(initial_particle_quad_max);

  for (int sub_step = 0; sub_step < SUBSTEPS; sub_step++) {
    quad_tree.physicsProcess(substep_time);
    for (int index = 0; index < Simulation::particles.size(); index++) {
      Particle *particle = &Simulation::particles[index];
      particle->update(substep_time);
      if (this->loop_bounds) {
        loopBoundsCheck(particle);
      } else {
        bounceBoundsCheck(particle);
      }
      Vector2 dir;
      float distance;
      switch (Simulation::mouseState) {
      case PULL:
        dir = directionTo(particle->position, Simulation::mouse_pos);
        distance = distanceTo(particle->position, Simulation::mouse_pos);
        particle->velocity += 10.0f * (dir / distance);
        break;
      case PUSH:
        dir = directionTo(particle->position, Simulation::mouse_pos);
        distance = distanceTo(particle->position, Simulation::mouse_pos);
        particle->velocity -= 10.0f * (dir / distance);
        break;
      case NONE:
        break;
      }
    }
  }
}

void Simulation::renderPass() {
  if (draw_quad_tree) {
    quad_tree.render(window);
  }
  if (selected_particle != nullptr) {
    selected_particle->renderInspector();
  }
  window.draw(object_va, states);
}

void Simulation::clearParticles() { Simulation::particles.clear(); }

void Simulation::loopBoundsCheck(Particle *particle) {
  if (particle->position.x > bounds.lower.x) {
    particle->position.x = bounds.upper.x;
  }
  if (particle->position.x < bounds.upper.x) {
    particle->position.x = bounds.lower.x;
  }
  if (particle->position.y > bounds.lower.y) {
    particle->position.y = bounds.upper.y;
  }
  if (particle->position.y < bounds.upper.y) {
    particle->position.y = bounds.lower.y;
  }
}

void Simulation::bounceBoundsCheck(Particle *paticle) {
  if (paticle->position.x + paticle->radius > bounds.lower.x) {
    paticle->position.x = bounds.lower.x - paticle->radius;
    paticle->velocity.x = -paticle->velocity.x * 0.25f;
  }
  if (paticle->position.x - paticle->radius < bounds.upper.x) {
    paticle->position.x = bounds.upper.x + paticle->radius;
    paticle->velocity.x = -paticle->velocity.x * 0.25f;
  }
  if (paticle->position.y + paticle->radius > bounds.lower.y) {
    paticle->position.y = bounds.lower.y - paticle->radius;
    paticle->velocity.y = -paticle->velocity.y * 0.25f;
  }
  if (paticle->position.y - paticle->radius < bounds.upper.y) {
    paticle->position.y = bounds.upper.y + paticle->radius;
    paticle->velocity.y = -paticle->velocity.y * 0.25f;
  }
}

void Simulation::run() {
  sf::Texture texture;
  texture.loadFromFile("./res/circle.png");
  texture.generateMipmap();
  /*texture.setSmooth(true);*/

  /*states = sf::RenderStates::Default;*/
  states.texture = &texture;

  int spawn_timer = 0;
  window.setVerticalSyncEnabled(true);

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::Resized) {
        sf::View view(
            Vector2((float)event.size.width / 2, (float)event.size.height / 2),
            Vector2((float)event.size.width, (float)event.size.height));
        window.setView(view);
        bounds.upper = Vector2(0.0f, 0.0f);
        bounds.lower = Vector2((int)event.size.width, (int)event.size.height);
      }
      if (event.type == sf::Event::MouseMoved) {
        Simulation::mouse_pos.x = (float)event.mouseMove.x;
        Simulation::mouse_pos.y = (float)event.mouseMove.y;
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        Simulation::mouseState = NONE;
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
          Vector2 mouse_pos((float)event.mouseButton.x,
                            (float)event.mouseButton.y);
          for (int particle_index = 0;
               particle_index < Simulation::particles.size();
               particle_index++) {
            Particle *particle = &Simulation::particles[particle_index];
            if (particle->containsPoint(mouse_pos)) {
              selected_particle = particle;
              break;
            }
          }
        }
        if (event.mouseButton.button == sf::Mouse::Button::Right) {
          selected_particle = nullptr;
        }
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
          draw_quad_tree = !draw_quad_tree;
        }
        if (event.key.code == sf::Keyboard::Space) {
          physics_paused = !physics_paused;
        }
      }
    }

    sf::Time deltaTime = deltaClock.restart();
    float deltaTimeSecs = deltaTime.asSeconds();
    ImGui::SFML::Update(window, deltaTime);

    renderUI();

    window.clear(sf::Color::Black);

    if (!physics_paused) {
      /*thread_pool.QueueJob([this, deltaTimeSecs]{this->physicsUpdate(0.125f * deltaTimeSecs);});*/
      physicsUpdate(0.125f * deltaTimeSecs);
    }

    thread_pool.QueueJob([this]{this->updateVA();});
    renderPass();

    fps = int(1.0f / deltaTime.asSeconds());

    ImGui::SFML::Render(window);
    window.display();


    Vector2 spawn_location =
        Vector2((float)window.getSize().x, (float)window.getSize().y);
    spawn_timer = (spawn_timer += 1) % 120;
    if (Simulation::particles.size() < particle_max && !physics_paused) {
      addParticle(5.0f, bounds.lower / 2.0f, sf::Vector2(50.0f, 50.0f),
                  Simulation::particles.size() % 8);
    };
    if (Simulation::particles.size() > particle_max) {
      Simulation::particles.pop_back();
    }
  }

  thread_pool.Stop();
}

void Simulation::renderUI() {
  ImGui::Begin("Simulation");
  ImGui::Text("FPS : %d", fps);
  ImGui::Text("Particle Count : %zu", particles.size());
  ImGui::SliderInt("Particle Max", &particle_max, 0, 10000, "%d");
  ImGui::Checkbox("Enable Interactions", &Simulation::interactions_enabled);
  ImGui::Checkbox("Enable Reactions", &Simulation::reactions_enabled);
  ImGui::Checkbox("Loop Edge", &loop_bounds);
  ImGui::Checkbox("Pause", &physics_paused);
  if (ImGui::CollapsingHeader("Particle Colors")) {
    ImGui::ColorEdit4("Particle 1 Color", Particle::particle_colors[0].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 2 Color", Particle::particle_colors[1].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 3 Color", Particle::particle_colors[2].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 4 Color", Particle::particle_colors[3].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 5 Color", Particle::particle_colors[4].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 6 Color", Particle::particle_colors[5].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 7 Color", Particle::particle_colors[6].data(),
                      ImGuiColorEditFlags_Float);
    ImGui::ColorEdit4("Particle 8 Color", Particle::particle_colors[7].data(),
                      ImGuiColorEditFlags_Float);
  }
  if (ImGui::CollapsingHeader("Particle Interactions")) {
    for (int particle_type = 0; particle_type < 8; particle_type++) {
      if (ImGui::TreeNode(std::to_string(particle_type).c_str(),
                          "Particle %d Interactions", particle_type + 1)) {
        for (int other_particle = 0; other_particle < 8; other_particle++) {
          std::string particle_str = "Particle ";
          ImGui::SliderFloat(
              particle_str.append(std::to_string(other_particle + 1)).c_str(),
              Particle::getInteractionForcesPtr(particle_type, other_particle),
              -25.0f, 25.0f);
        }
        ImGui::TreePop();
      }
    }
  }
  ImGui::End();
}


void Simulation::updateVA(){
  object_va.resize(Simulation::particles.size() * 4);
  float texture_size = 1024.0f;
  float radius = 5.0f;
  for (uint32_t i = 0; i < Simulation::particles.size(); i++){
    uint32_t idx = i << 2;
    const Particle& particle = Simulation::particles[i];

    object_va[idx + 0].position = particle.position + Vector2(-radius, -radius);
    object_va[idx + 1].position = particle.position + Vector2(radius, -radius);
    object_va[idx + 2].position = particle.position + Vector2(radius, radius);
    object_va[idx + 3].position = particle.position + Vector2(-radius, radius);
    object_va[idx + 0].texCoords = {0.0f, 0.0f};
    object_va[idx + 1].texCoords = {texture_size, 0.0f};
    object_va[idx + 2].texCoords = {texture_size, texture_size};
    object_va[idx + 3].texCoords = {0.0f, texture_size};

    const sf::Color color = Particle::particle_colors[particle.type].toIntColor();
    object_va[idx + 0].color = color;
    object_va[idx + 1].color = color;
    object_va[idx + 2].color = color;
    object_va[idx + 3].color = color;
  }
}
