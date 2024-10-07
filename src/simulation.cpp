#include "simulation.hpp"
#include "particle.hpp"
#include "quadtree.hpp"
#include "utils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdio>
#include <vector>

const int SUBSTEPS = 8;

static bool gravity_enabled = true;
static std::vector<Particle> particles;
static int bounds_height = 400;
static int bounds_width = 600;
static float bounds_elasticity = 0.25f;
static Particle *selectedParticle = nullptr;
static bool render_quadtree = false;

void selectBall(sf::Vector2f pos) {
  for (int index = 0; index < particles.size(); index++) {
    Particle *particle = &particles[index];
    if (particle->containsPoint(pos)) {
      selectedParticle = particle;
    }
  }
}

void unselectBall() { selectedParticle = nullptr; }

void addParticle(sf::Color color, float radius, sf::Vector2f position,
                 sf::Vector2f velocity) {
  particles.push_back(Particle(radius, color, position, velocity));
}

int getParticleCount() { return particles.size(); }

void physicsUpdate(float dt, sf::RenderWindow &window) {
  float substep_time = dt / SUBSTEPS;

  if (selectedParticle != nullptr) {
    float distance = distanceTo(selectedParticle->position, getMousePos());
    sf::Vector2f dir = directionTo(selectedParticle->position, getMousePos());
    selectedParticle->velocity += dir * distance * dt * 100.0f;
  }

  QuadTree quad_tree =
      QuadTree(sf::Vector2f((float)bounds_width, (float)bounds_height),
               sf::Vector2f(0.0f, 0.0f));

  quad_tree.regenerate();

  if (render_quadtree) {
    quad_tree.render(window);
  }

  for (int sub_step = 0; sub_step < SUBSTEPS; sub_step++) {

    quad_tree.physicsProcess(substep_time);
  }
}

void renderPass(sf::RenderWindow &window) {
  for (int index = 0; index < particles.size(); index++) {
    Particle *particle = &particles[index];
    particle->draw(window);
  }
}

void setBounds(int width, int height) {
  bounds_height = height;
  bounds_width = width;
}

void QuadTree::regenerate() {

  particle_indexs.clear();
  int particle_count = 0;
  for (int index = 0; index < particles.size(); index++) {
    Particle *particle = &particles[index];

    if (isParticlePartilWithin(particle, upper_bounds, lower_bounds)) {
      particle_indexs.push_back(index);
      if (doesBoundContainPoint(particle->position, upper_bounds,
                                lower_bounds)) {
        particle_count += 1;
      }
    }

    if (particle_count > QuadTree::PARTICLE_MAX) {

      particle_indexs.clear();

      sf::Vector2f top_left = lower_bounds;
      sf::Vector2f bottom_right = upper_bounds;
      sf::Vector2f center =
          lower_bounds + ((upper_bounds - lower_bounds) / 2.0f);
      sf::Vector2f bottom_center = sf::Vector2f(center.x, upper_bounds.y);
      sf::Vector2f top_center = sf::Vector2f(center.x, lower_bounds.y);
      sf::Vector2f left_center = sf::Vector2f(lower_bounds.x, center.y);
      sf::Vector2f right_center = sf::Vector2f(upper_bounds.x, center.y);

      QuadTree child1 = QuadTree(center, top_left);
      QuadTree child2 = QuadTree(bottom_right, center); // problem child
      QuadTree child3 = QuadTree(bottom_center, left_center);
      QuadTree child4 = QuadTree(right_center, top_center);

      child1.regenerate();
      child2.regenerate();
      child3.regenerate();
      child4.regenerate();

      children.push_back(child1);
      children.push_back(child2);
      children.push_back(child3);
      children.push_back(child4);

      return;
    }
  }
}

void QuadTree::physicsProcess(float dt) {
  if (particle_indexs.empty()) {
    for (QuadTree child : children) {
      child.physicsProcess(dt);
    }
    return;
  }

  for (int index : particle_indexs) {
    Particle *particle = &particles[index];

    particle->update(dt);

    for (int index2 : particle_indexs) {
      if (index == index2) {
        continue;
      }
      Particle *particle2 = &particles[index2];
      float distance = distanceTo(particle->position, particle2->position);
      float radi = particle->radius + particle2->radius;

      if (distance < radi) {
        sf::Vector2f dir = directionTo(particle->position, particle2->position);
        float dif = (radi - distance);
        particle->velocity -= dir * dif * 0.25f;
        particle->position -= dir * dif;
        particle2->position += dir * dif;
      }
    }

    if (particle->position.y + particle->radius > (float)bounds_height) {
      particle->position.y = (float)bounds_height - particle->radius;
      particle->velocity.y = -particle->velocity.y * bounds_elasticity;
    }

    if (particle->position.y - particle->radius < 0.0f) {
      particle->position.y = 0.0f + particle->radius;
      particle->velocity.y = -particle->velocity.y * bounds_elasticity;
    }

    if (particle->position.x + particle->radius > (float)bounds_width) {
      particle->position.x = (float)bounds_width - particle->radius;
      particle->velocity.x = -particle->velocity.x * bounds_elasticity;
    }

    if (particle->position.x - particle->radius < 0.0f) {
      particle->position.x = 0.0f + particle->radius;
      particle->velocity.x = -particle->velocity.x * bounds_elasticity;
    }

    if (gravity_enabled) {
      particle->velocity.y += 900.0f * dt;
      if (particle->velocity.y > 500.0f) {
        particle->velocity.y = 500.0f;
      }
    }
  }
}

void toggleGravity() { gravity_enabled = !gravity_enabled; }

void toggleQuadTree() { render_quadtree = !render_quadtree; }
