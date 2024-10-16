#include "application.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Lock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "defines.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "simulation.hpp"
#include "threads.hpp"
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <memory>

Application::Application(ThreadPool *thread_pool) {
  this->thread_pool = thread_pool;
  this->particles_va = sf::VertexArray(sf::Quads);
  this->view = sf::View(Vec2(300.0f, 200.0f), Vec2(600.0f, 400.0f));
  this->window.create(sf::VideoMode(600, 400), "ParticleSim",
                      sf::Style::Close | sf::Style::Resize);
  this->simulation = Simulation(view.getSize());
  this->particle_texture.loadFromFile("./res/circle.png");
  this->states.texture = &particle_texture;

  this->mouse_shape.setSize(Vec2(25.0f, 25.0f));
  this->mouse_shape.setFillColor(sf::Color::Transparent);
  this->mouse_shape.setOutlineColor(Color(1.0f, 1.0f, 1.0f));
  this->mouse_shape.setOutlineThickness(1.0f);
  this->mouse_selected_type = 0;

  ImGui::SFML::Init(window, true);
  this->io = ImGui::GetIO();
}

void Application::pollEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(window, event);
    if (event.type == sf::Event::Closed) {
      is_running = false;
    }
    if (event.type == sf::Event::Resized) {
      view.setCenter((float)event.size.width / 2, (float)event.size.height / 2);
      view.setSize((float)event.size.width, (float)event.size.height);
      window.setView(view);
      simulation.simulation_area =
          Vec2((float)event.size.width, (float)event.size.height);
    }
    if (event.type == sf::Event::KeyPressed){
      if (event.key.code == sf::Keyboard::Space){
        simulation.clearParticles();
        simulation.spawnParticles(particle_spawn_amount);
      }
      if (event.key.code == sf::Keyboard::R){
        simulation.randomizeInteractions();
      }
      if (event.key.code == sf::Keyboard::E){
        mouse_selected_type = (mouse_selected_type + 1) % simulation.particle_type_count;
      }
      if (event.key.code == sf::Keyboard::Q){
        mouse_selected_type -=1;
        if (mouse_selected_type < 0){
          mouse_selected_type = 0;
        }
      }
    }
    if (event.type == sf::Event::MouseMoved){
      mouse_shape.setPosition(Vec2((float)event.mouseMove.x, (float)event.mouseMove.y));
      mouse_shape.setOrigin(mouse_shape.getSize()/2.0f);
    }
    if (event.type == sf::Event::MouseButtonPressed){
      if (event.mouseButton.button == sf::Mouse::Right){
        fillMouseBrush();
      }
    }
    if (event.type == sf::Event::MouseWheelScrolled){
      mouse_shape.setSize(mouse_shape.getSize() + (event.mouseWheelScroll.delta * Vec2(5.0f, 5.0f)));
      if (mouse_shape.getSize().x < 5.0f){
        mouse_shape.setSize(Vec2(5.0f, 5.0f));
      }
      mouse_shape.setOrigin(mouse_shape.getSize()/2.0f);
    }
  }
}

void Application::run() {






  window.setVerticalSyncEnabled(true);

  while (is_running) {
    pollEvents();

    sf::Time deltaTime = delta_clock.restart();
    float dt = deltaTime.asSeconds();

    fps = 1.0f/dt;

    ImGui::SFML::Update(window, deltaTime);


    /*simulation.updatePhysics(dt);*/
    /*while(thread_pool->busy());*/
    u64 half_count = simulation.particles.size()/2.0f;
    u64 count = simulation.particles.size();
    thread_pool->queueJob([this,dt, half_count]{this->simulation.updatePhysics(dt, 0, half_count);});
    thread_pool->queueJob([this,dt, half_count, count]{this->simulation.updatePhysics(dt, half_count, count);});

    /*while(thread_pool->busy());*/

    updateParticlesVA();

    renderUi();

    window.clear(Color(0.0f, 0.0f, 0.0f));
    /*ImGui::NewFrame();*/
    window.draw(mouse_shape);
    window.draw(particles_va, states);
    ImGui::SFML::Render(window);
    /*ImGui::EndFrame();*/
    window.display();
  }
}

void Application::updateParticlesVA() {
  particles_va.resize(simulation.particles.size() * 4);
  const f32 texture_size = 1024.0f;
  const f32 radius = RADIUS;
  for (u32 i = 0; i < simulation.particles.size(); i++) {
    u32 idx = i << 2;
    const Particle &particle = simulation.particles[i];

    particles_va[idx + 0].position = particle.position + Vec2(-radius, -radius);
    particles_va[idx + 1].position = particle.position + Vec2(radius, -radius);
    particles_va[idx + 2].position = particle.position + Vec2(radius, radius);
    particles_va[idx + 3].position = particle.position + Vec2(-radius, radius);
    particles_va[idx + 0].texCoords = {0.0f, 0.0f};
    particles_va[idx + 1].texCoords = {texture_size, 0.0f};
    particles_va[idx + 2].texCoords = {texture_size, texture_size};
    particles_va[idx + 3].texCoords = {0.0f, texture_size};

    const Color color = simulation.particle_colors[particle.type];
    particles_va[idx + 0].color = color;
    particles_va[idx + 1].color = color;
    particles_va[idx + 2].color = color;
    particles_va[idx + 3].color = color;
  }
}

void Application::renderUi(){
  ImGui::Begin("Simulation");
  ImGui::Text("fps : %d",fps);
  ImGui::SliderInt("Particle Spawn Amount", &particle_spawn_amount, 1, 1000);
  ImGui::SliderInt("Mouse Spawn Particle Type", &mouse_selected_type, 0, simulation.particle_type_count);
  if (ImGui::SliderInt("Particle Type Count", &simulation.particle_type_count, 1, 12)){
    simulation.setParticleTypeCount(simulation.particle_type_count);
  }
  ImGui::Text("Particle Count : %zu", simulation.particles.size());
  if (ImGui::CollapsingHeader("Type Colors")){
    for (i32 count_type = 0; count_type < simulation.particle_type_count; count_type++){
      ImGui::PushID(count_type);
      ImGui::ColorEdit4("", simulation.particle_colors[count_type].data()); ImGui::SameLine();
      ImGui::Text("Particle %d Color", count_type);
      ImGui::PopID();
    }
  }
  if (ImGui::CollapsingHeader("Particle Interactions")){
    for (i32 type = 0; type < simulation.particle_type_count; type++){
      ImGui::PushID(type);
      if (ImGui::TreeNode("", "Particle %d Interactions", type)){
        for (i32 other_type = 0; other_type < simulation.particle_type_count; other_type++){
          ImGui::PushID(other_type);
          ImGui::SliderFloat("InteractionsStr", simulation.getInteractionStrength(type, other_type), -100.0f, 100.0f);
          ImGui::SliderFloat("InteractionsDis", simulation.getInteractionDistance(type, other_type), 1.0f, 200.0f);
          ImGui::PopID();
        }


        ImGui::TreePop();
      }


      ImGui::PopID();
    }
  }
  ImGui::End();
}


void Application::fillMouseBrush(){
  Vec2 size_start = mouse_shape.getPosition() - mouse_shape.getSize();
  Vec2 size_end = mouse_shape.getSize() + mouse_shape.getPosition();

  for (i32 x = size_start.x; x < size_end.x; x+=15){
    for (i32 y = size_start.y; y < size_end.y; y+=15){
      simulation.addParticle(Particle(mouse_selected_type, Vec2(x,y), Vec2(0.0f, 0.0f)));
    }
  }

}
