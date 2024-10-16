#include "particle.hpp"
#include "defines.hpp"

Particle::Particle(u32 type){
  this->type = type;
  this->position = Vec2(0.0f, 0.0f);
  this->velocity = Vec2(0.0f, 0.0f);
}

void Particle::update(f32 dt){
  this->position += velocity * dt;
}


Particle::Particle(u32 type, Vec2 position, Vec2 velocity){
  this->type = type;
  this->position = position;
  this->velocity = velocity;
}
