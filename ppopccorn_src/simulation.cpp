#include "simulation.hpp"
#include "particle.hpp"
#include "quadtree.hpp"
#include "utils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>

int SUBSTEPS = 8;

static bool gravity_enabled = false;
static std::vector<Particle> particles;
static int bounds_height = 400;
static int bounds_width = 600;
static float bounds_elasticity = 0.25f;
static Particle *selectedParticle = nullptr;
static bool render_quadtree = false;
static bool interactions_enabled = false;
static bool reactions_enabled = false;
static int quad_max_var = 32;

static QuadTree quad_tree;

void selectBall(sf::Vector2f pos) {
  for (int index = 0; index < particles.size(); index++) {
    Particle *particle = &particles[index];
    if (particle->containsPoint(pos)) {
      selectedParticle = particle;
    }
  }
}

void unselectBall() { selectedParticle = nullptr; }

void addParticle(float radius, sf::Vector2f position, sf::Vector2f velocity,
                 uint8_t id) {
  particles.push_back(Particle(radius, position, velocity, id));
}

int getParticleCount() { return particles.size(); }

void physicsUpdate(float dt, sf::RenderWindow &window) {
  float substep_time = dt / SUBSTEPS;

  if (selectedParticle != nullptr) {
    float distance = distanceTo(selectedParticle->position, getMousePos());
    sf::Vector2f dir = directionTo(selectedParticle->position, getMousePos());
    selectedParticle->velocity += dir * distance * dt * 100.0f;
  }

  sf::Vector2f heighest_particle = sf::Vector2f(0.0f, 0.0f);
  sf::Vector2f lowest_particle =
      sf::Vector2f((float)bounds_width, (float)bounds_height);
  for (int particle_index = 0; particle_index < particles.size();
       particle_index++) {
    Particle *particle = &particles[particle_index];
    if (particle->position.x < lowest_particle.x) {
      lowest_particle.x = particle->position.x;
    }
    if (particle->position.y < lowest_particle.y) {
      lowest_particle.y = particle->position.y;
    }
    if (particle->position.x > heighest_particle.x) {
      heighest_particle.x = particle->position.x;
    }
    if (particle->position.y > heighest_particle.y) {
      heighest_particle.y = particle->position.y;
    }
  }
  if (particles.size() < 2 || lowest_particle == heighest_particle) {
    heighest_particle = lowest_particle;
    lowest_particle = sf::Vector2f(0.0f, 0.0f);
    quad_tree.owned_particles.push_back(0);
  }

  /*lowest_particle = lowest_particle - (lowest_particle * 0.50f);*/
  /*heighest_particle = heighest_particle * 1.50f;*/

  quad_tree.clear();
  quad_tree.resize(heighest_particle, lowest_particle);
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

  owned_particles.clear();
  for (int index = 0; index < particles.size(); index++) {
    Particle *particle = &particles[index];

    if (isParticlePartilWithin(particle, upper_bounds, lower_bounds)) {
      shared_particles.push_back(index);
      if (doesBoundContainPoint(particle->position, upper_bounds,
                                lower_bounds)) {
        owned_particles.push_back(index);
      }
    }

    if (owned_particles.size() > quad_max_var || shared_particles.size() > quad_max_var * 2){

      owned_particles.clear();
      shared_particles.clear();

      sf::Vector2f top_left = lower_bounds;
      sf::Vector2f bottom_right = upper_bounds;
      sf::Vector2f center =
          lower_bounds + ((upper_bounds - lower_bounds) / 2.0f);
      sf::Vector2f bottom_center = sf::Vector2f(center.x, upper_bounds.y);
      sf::Vector2f top_center = sf::Vector2f(center.x, lower_bounds.y);
      sf::Vector2f left_center = sf::Vector2f(lower_bounds.x, center.y);
      sf::Vector2f right_center = sf::Vector2f(upper_bounds.x, center.y);

      QuadTree child1 = QuadTree(center, top_left, particle_max * 2);
      QuadTree child2 =
          QuadTree(bottom_right, center, particle_max * 2); // problem child
      QuadTree child3 = QuadTree(bottom_center, left_center, particle_max * 2);
      QuadTree child4 = QuadTree(right_center, top_center, particle_max * 2);

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
  if (owned_particles.empty()) {
    if (particle_max == QuadTree::FIRST_PARTICLE_MAX) {
      std::thread thread1(&QuadTree::physicsProcess, &children[0], dt);
      std::thread thread2(&QuadTree::physicsProcess, &children[0], dt);
      std::thread thread3(&QuadTree::physicsProcess, &children[0], dt);
      std::thread thread4(&QuadTree::physicsProcess, &children[0], dt);

      thread1.join();
      thread2.join();
      thread3.join();
      thread4.join();

    } else {
      for (QuadTree child : children) {
        child.physicsProcess(dt);
      }
    }
    return;
  }

  for (int index : shared_particles) {
    Particle *particle = &particles[index];

    for (int index2 : shared_particles) {
      if (index == index2) {
        continue;
      }
      Particle *particle2 = &particles[index2];
      float distance = distanceTo(particle->position, particle2->position);
      float radi = particle->radius + particle2->radius;
      sf::Vector2f dir = directionTo(particle->position, particle2->position);


      if (interactions_enabled) {
        particle->velocity += dir * (particle->getInteractionForces(particle2->color) / distance);
      
      }
      if (reactions_enabled) {
        Particle::updateReactions(particle);
      }

      if (distance < radi) {
        particle->touched(particle2);
        float dif = (radi - distance);
        particle->velocity -=
            (dir *
             ((vecMagnitude(particle2->velocity) * 0.125f) *
              -((radToDeg(angleBetween(dir, particle2->velocity)) - 180.0f) /
                180.0f)));
        particle2->velocity +=
            (dir *
             ((vecMagnitude(particle->velocity) * 0.25f) *
              -((radToDeg(angleBetween(dir, particle->velocity)) - 180.0f) /
                180.0f)));
        particle->position -= dir * dif * 0.5f;
        particle2->position += dir * dif * 0.5f;
      }
    }
  }

  for (int index : owned_particles) {
    Particle *particle = &particles[index];
    if (particle->velocity == sf::Vector2f(0.0f, 0.0f)) {
      continue;
    }

    if (particle->position.y > (float)bounds_height) {
      particle->position.y = 0.0f;
      /*particle->velocity.y = -particle->velocity.y * bounds_elasticity;*/
    }

    if (particle->position.y < 0.0f) {
      particle->position.y = (float)bounds_height;
      /*particle->velocity.y = -particle->velocity.y * bounds_elasticity;*/
    }

    if (particle->position.x > (float)bounds_width) {
      particle->position.x = 0.0f;
      /*particle->velocity.x = -particle->velocity.x * bounds_elasticity;*/
    }

    if (particle->position.x < 0.0f) {
      particle->position.x = (float)bounds_width;
      /*particle->velocity.x = -particle->velocity.x * bounds_elasticity;*/
    }

    particle->update(dt);
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

void changeQuadCapacity(int change) { quad_max_var += change; }

int getQuadCapacity() { return quad_max_var; }

void removeParticle() { particles.pop_back(); }

void clearParticles() { particles.clear(); }

void setInteractions(bool set) { interactions_enabled = set;}

bool getInteractionsState() { return interactions_enabled; }

void changeSubstepCount(int change) {
  SUBSTEPS += change;
  if (SUBSTEPS < 8) {
    SUBSTEPS = 8;
  }
  if (SUBSTEPS > 100) {
    SUBSTEPS = 100;
  }
}

int getSubstepCount() { return SUBSTEPS; }



void setReactions(bool set){
  reactions_enabled = set;
}
