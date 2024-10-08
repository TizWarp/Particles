#include "particle.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <cstdlib>

Particle::Particle(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity){
  this->velocity = velocity;
  this->position = position;
  this->radius = radius;
  this->color = color;
  shape = sf::CircleShape(radius);
  shape.setFillColor(color);
  shape.setOrigin(radius, radius);
}

void Particle::update(float time){
  position += (velocity * time);
  shape.setPosition(position);
}

bool Particle::containsPoint(sf::Vector2f point){
  return distanceTo(position, point) < radius;
}

void Particle::draw(sf::RenderWindow &window){
  sf::Color new_color = sf::Color((uint8_t)abs((int)this->velocity.x), 0, (uint8_t)abs((int)this->velocity.y), 255);
  shape.setFillColor(new_color);
  window.draw(shape);
}
