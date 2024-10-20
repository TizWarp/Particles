#include "simulation.hpp"
#include "defines.hpp"
#include "renderer.hpp"
#include <spdlog/spdlog.h>
#include <vector>

namespace Simulation{
  static std::vector<Particle> particles = {};
  Vec2 upper_bounds = Vec2(-1.0f, -1.0f);
  Vec2 lower_bounds = Vec2(1.0f, 1.0f);
}

void Simulation::addParticle(Particle particle){
  particles.push_back(particle);
}

void Simulation::removeParticle(int num){
  particles.erase(particles.begin() + num);
}

void Simulation::update(float dt){
  float sub_dt = dt / SUBSTEPS;
  for (int step = 0; step < SUBSTEPS; step++){
    for (int p_index = 0; p_index < particles.size(); p_index++){
      Particle &particle = particles[p_index];
      particle.update(sub_dt);
    }
  }

  for (int p_index = 0; p_index < particles.size(); p_index++){
    Renderer::pushParticle(&particles[p_index]);
  }
}

void Simulation::init(){
  addParticle(Particle(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f)));
}

int Simulation::getParticleCount(){
  return particles.size();
}

Particle::Particle(Vec2 position, Vec2 velocity, Color color){
  this->velocity = velocity;
  this->position = position;
  this->color = color;
}

void Particle::update(float dt){
  position += velocity * dt;

}
