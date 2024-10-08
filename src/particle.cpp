#include "particle.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>

Particle::Particle(float radius, sf::Vector2f position, sf::Vector2f velocity,
                   uint8_t id) {
  this->velocity = velocity;
  this->id = id;
  this->position = position;
  this->radius = radius;
  shape = sf::CircleShape(radius);
  shape.setFillColor(particle_colors[id]);
  shape.setOrigin(radius, radius);
}

void Particle::update(float time) {
  position += (velocity * time);
  shape.setPosition(position);
  memset(touching_particles, 0, sizeof(touching_particles));
}

bool Particle::containsPoint(sf::Vector2f point) {
  return distanceTo(position, point) < radius;
}

void Particle::draw(sf::RenderWindow &window) {
  shape.setFillColor(particle_colors[id]);
  window.draw(shape);
}

void Particle::touched(uint8_t id) { touching_particles[id] += 1; }

void Particle::applyInteractionForces(Particle *particle1,
                                      Particle *particle2) {

  switch (particle1->id) {
  case 0: // red
    switch (particle2->id) {
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["red->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["red->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["red->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["red->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["red->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["red->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["red->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["red->orange"]);
      return;
    default:
      return;
    }
  case 1: // blue
    switch (particle2->id){
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["green->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["green->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["green->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["green->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["green->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["green->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["green->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["green->orange"]);
      return;
    default:
      return;
    }
  case 2: // green
    switch (particle2->id) {
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["blue->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["blue->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["blue->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["blue->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["blue->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["blue->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["blue->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["blue->orange"]);
      return;
    default:
      return;
    }
  case 3: // yellow
    switch (particle2->id){
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["yellow->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["yellow->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["yellow->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["yellow->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["yellow->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["yellow->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["yellow->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["yellow->orange"]);
      return;
    default:
      return;
    }
  case 4: // magenta
    switch (particle2->id) {
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["magenta->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["magenta->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["magenta->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["magenta->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["magenta->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["magenta->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["magenta->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["magenta->orange"]);
      return;
    default:
      return;
    }
  case 5: // cyan
    switch (particle2->id) {
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["cyan->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["cyan->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["cyan->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["cyan->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["cyan->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["cyan->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["cyan->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["cyan->orange"]);
      return;
    default:
      return;
    }
  case 6: // white
    switch (particle2->id) {
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["white->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["white->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["white->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["white->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["white->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["white->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["white->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["white->orange"]);
      return;
    default:
      return;
    }
  case 7: // orange
    switch (particle2->id){
    case 0:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["orange->red"]);
      return;
    case 1:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["orange->green"]);
      return;
    case 2:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["orange->blue"]);
      return;
    case 3:
      applyForces(particle1, particle2, Particle::InteractionForcesMap["orange->yellow"]);
      return;
    case 4:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["orange->magenta"]);
      return;
    case 5:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["orange->cyan"]);
      return;
    case 6:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["orange->white"]);
      return;
    case 7:
      applyForces(particle1, particle2,Particle::InteractionForcesMap["orange->orange"]);
      return;
    default:
      return;
    }
  default:
    return;
  }
}
