#include "particle.hpp"
#include "math.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "defines.hpp"

Particle::Particle(float radius, Vector2 position, Vector2 velocity,
                   uint8_t id) {
  this->velocity = velocity;
  this->color = id;
  this->position = position;
  this->radius = radius;
  shape = sf::CircleShape(radius);
  shape.setFillColor(particle_colors[id].toIntColor());
  shape.setOrigin(radius, radius);
}


void Particle::updateReactions(Particle *particle){
  for (ReactionDef reaction : Particle::reactions[particle->color]){
    if (reaction.canReact(particle)){
      reaction.func(particle);
    }
  }
}

void Particle::addReaction(int target_color, reactionFunc reaction_func, canReactFunc can_react){
  ReactionDef def{};
  def.func = reaction_func;
  def.canReact = can_react;
  Particle::reactions[target_color].push_back(def);
}

void Particle::update(float time) {
  life += 1;
  position += (velocity * time);
  memset(touching_particles, 0, sizeof(touching_particles));
}

bool Particle::containsPoint(Vector2 point) {
  return distanceTo(position, point) < radius;
}

void Particle::draw(sf::RenderWindow &window) {
  shape.setFillColor(particle_colors[color].toIntColor());
  shape.setPosition(position);
  window.draw(shape);
}

void Particle::touched(Particle *particle) {
  touching_particles[particle->color].push_back(particle); 
}

float Particle::getInteractionForces(int color){
  return Particle::interactionForces[this->color + (color * 8)];
}


float* Particle::getInteractionForcesPtr(int type1, int type2){
  return &Particle::interactionForces[type1 + (type2 * 8)];
}
