#include "simulation.hpp"
#include "particle.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <execution>
#include <vector>

const int SUBSTEPS = 100;

static bool gravity_enabled = true;
static std::vector<Particle> particles;
static int bounds_height = 400;
static int bounds_width = 600;
static float bounds_elasticity = 0.25f;

void addParticle(sf::Color color, float radius, sf::Vector2f position,
                 sf::Vector2f velocity) {
  particles.push_back(Particle(radius, color, position, velocity));
}

void physicsUpdate(float dt) {
  float substep_time = dt / SUBSTEPS;
  for (int sub_step = 0; sub_step < SUBSTEPS; sub_step++) {
    for (int particle_index = 0; particle_index < particles.size();
         particle_index++) {
      Particle *particle = &particles[particle_index];

      particle->update(substep_time);

      if (particle->position.y - particle->radius > bounds_height) {
        particle->position.y -= particle->radius / SUBSTEPS;
        sf::Vector2f vel = particle->velocity;
        vel.y = -vel.y * bounds_elasticity;
        particle->velocity = vel;
      }

      if (gravity_enabled) {
        particle->velocity.y += 9.8 / SUBSTEPS;
        if (particle->velocity.y > 100.0f) {
          particle->velocity.y = 100.0f;
        }
      }
    }
  }
}

void renderPass(sf::RenderWindow &window) {
  for (int index = 0; index < particles.size(); index++) {
    Particle *particle = &particles[index];
    window.draw(particle->shape);
  }
}

void setBounds(int width, int height){
  bounds_height = height;
  bounds_width = width;
}
