#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Particle{
  public:
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    
    Particle(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity);

    void update(float time);

    bool containsPoint(sf::Vector2f point);
};
