#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Particle {
public:
  float radius;
  sf::Vector2f position;
  sf::Vector2f velocity;

  Particle(float radius, sf::Color color, sf::Vector2f position,
           sf::Vector2f velocity);

  void update(float time);

  bool containsPoint(sf::Vector2f point);

  void draw(sf::RenderWindow &window);

private:
  sf::CircleShape shape;
};
