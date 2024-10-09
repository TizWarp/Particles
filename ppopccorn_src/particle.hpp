#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Particle;

typedef void(*reactionFunc)(Particle *particle);
typedef  bool(*canReactFunc)(Particle *particle);


struct ReactionDef{
  reactionFunc func;
  canReactFunc canReact;
};


class Particle {
public:
  float radius;
  sf::Vector2f position;
  sf::Vector2f velocity;
  uint8_t color;
  std::vector<Particle*> touching_particles[8];

  Particle(float radius, sf::Vector2f position,
           sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f), uint8_t id = 0);

  void update(float time);

  bool containsPoint(sf::Vector2f point);

  void touched(Particle *particle);

  void draw(sf::RenderWindow &window);
  static void updateReactions(Particle *particle);

  float getInteractionForces(int color);

  static void addReaction(int target_color, reactionFunc reaction_func, canReactFunc can_react);

private:
  sf::CircleShape shape;
  inline static std::vector<ReactionDef> reactions[8] = {};
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
  inline static float interactionForces[8*8] = {};
};
