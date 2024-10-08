#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Particle {
public:
  float radius;
  sf::Vector2f position;
  sf::Vector2f velocity;
  uint8_t id;
  int touching_particles[8];

  Particle(float radius, sf::Vector2f position,
           sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f), uint8_t id = 0);

  void update(float time);

  bool containsPoint(sf::Vector2f point);

  void touched(uint8_t id);

  void draw(sf::RenderWindow &window);

  static void applyInteractionForces(Particle *particle1, Particle *particle2);
  static void applyReaction(Particle *Particle);

private:
  sf::CircleShape shape;

  const sf::Color particle_colors[8] = {
      sf::Color(255, 0, 0),     sf::Color(0, 255, 0),   sf::Color(0, 0, 255),
      sf::Color(255, 255, 0),   sf::Color(255, 0, 255), sf::Color(0, 255, 255),
      sf::Color(255, 255, 255), sf::Color(255, 128, 0),
  };

  //red
  //green
  //blue
  //yellow
  //magenta
  //cyan
  //white
  //orange
public:
  inline static std::map<std::string, float> InteractionForcesMap = {
    {"red->red", 0.0f},
    {"red->green", 0.0f},
    {"red->blue", 0.0f},
    {"red->yellow", 0.0f},
    {"red->magenta", 0.0f},
    {"red->cyan", 0.0f},
    {"red->white", 0.0f},
    {"red->orange", 0.0f},
    {"green->red", 0.0f},
    {"green->green", 0.0f},
    {"green->blue", 0.0f},
    {"green->yellow", 0.0f},
    {"green->magenta", 0.0f},
    {"green->cyan", 0.0f},
    {"green->white", 0.0f},
    {"green->orange", 0.0f},
    {"blue->red", 0.0f},
    {"blue->green", 0.0f},
    {"blue->blue", 0.0f},
    {"blue->yellow", 0.0f},
    {"blue->magenta", 0.0f},
    {"blue->cyan", 0.0f},
    {"blue->white", 0.0f},
    {"blue->orange", 0.0f},
    {"yellow->red", 0.0f},
    {"yellow->green", 0.0f},
    {"yellow->blue", 0.0f},
    {"yellow->yellow", 0.0f},
    {"yellow->magenta", 0.0f},
    {"yellow->cyan", 0.0f},
    {"yellow->white", 0.0f},
    {"yellow->orange", 0.0f},
    {"magenta->red", 0.0f},
    {"magenta->green", 0.0f},
    {"magenta->blue", 0.0f},
    {"magenta->yellow", 0.0f},
    {"magenta->magenta", 0.0f},
    {"magenta->cyan", 0.0f},
    {"magenta->white", 0.0f},
    {"magenta->orange", 0.0f},
    {"cyan->red", 0.0f},
    {"cyan->green", 0.0f},
    {"cyan->blue", 0.0f},
    {"cyan->yellow", 0.0f},
    {"cyan->magenta", 0.0f},
    {"cyan->cyan", 0.0f},
    {"cyan->white", 0.0f},
    {"cyan->orange", 0.0f},
    {"white->red", 0.0f},
    {"white->green", 0.0f},
    {"white->blue", 0.0f},
    {"white->yellow", 0.0f},
    {"white->magenta", 0.0f},
    {"white->cyan", 0.0f},
    {"white->white", 0.0f},
    {"white->orange", 0.0f},
    {"orange->red", 0.0f},
    {"orange->green", 0.0f},
    {"orange->blue", 0.0f},
    {"orange->yellow", 0.0f},
    {"orange->magenta", 0.0f},
    {"orange->cyan", 0.0f},
    {"orange->white", 0.0f},
    {"orange->orange", 0.0f},

  };
};
