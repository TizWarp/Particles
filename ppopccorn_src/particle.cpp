#include "particle.hpp"
#include "imgui.h"
#include "math.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "defines.hpp"

Particle::Particle(float radius, Vector2 position, Vector2 velocity,
                   uint8_t id) {
  this->velocity = velocity;
  this->type = id;
  this->position = position;
  this->radius = radius;
  this->life = 0;
}


void Particle::updateReactions(Particle *particle){
  for (ReactionDef reaction : Particle::reactions[particle->type]){
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

void Particle::touched(Particle *particle) {
  touching_particles[particle->type].push_back(particle); 
}

float Particle::getInteractionForces(int color){
  return Particle::interactionForces[this->type + (color * 8)];
}


float* Particle::getInteractionForcesPtr(int type1, int type2){
  return &Particle::interactionForces[type1 + (type2 * 8)];
}

void Particle::renderInspector(){
  Colorf color = Particle::particle_colors[this->type];
  ImGui::Begin("Particle");
  ImGui::TextColored(Particle::particle_colors[this->type].toImColor(), "Type %d", type);
  ImGui::Text("Life : %zu", this->life);
  ImGui::Text("Position : (%f, %f)", position.x, position.y);
  ImGui::Text("Velocity : {%f, %f}", velocity.x, velocity.y);
  ImGui::End();
}
