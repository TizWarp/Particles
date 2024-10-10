#pragma once

#include "defines.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Particle;

typedef void (*reactionFunc)(Particle *particle);
typedef bool (*canReactFunc)(Particle *particle);

struct ReactionDef {
  reactionFunc func;
  canReactFunc canReact;
};

class Particle {
public:
  float radius;
  Vector2 position;
  Vector2 velocity;
  uint8_t color;
  uint64_t life;
  std::vector<Particle *> touching_particles[8];

  Particle(float radius, Vector2 position,
           Vector2 velocity = Vector2(0.0f, 0.0f), uint8_t id = 0);

  void update(float time);

  bool containsPoint(Vector2 point);

  void touched(Particle *particle);

  void draw(sf::RenderWindow &window);
  static void updateReactions(Particle *particle);

  float getInteractionForces(int color);
  
  static float* getInteractionForcesPtr(int type1, int type2);

  static void addReaction(int target_color, reactionFunc reaction_func,
                          canReactFunc can_react);

  inline static std::vector<ReactionDef> reactions[8] = {};
  inline static Colorf particle_colors[8] = {
      Colorf(1.0f, 0.0f, 0.0f),     Colorf(0.0f, 1.0f, 0.0f),   Colorf(0.0f, 0.0f, 1.0f),
      Colorf(1.0f, 1.0f, 0.0f),   Colorf(1.0f, 0.0f, 1.0f), Colorf(0.0f, 1.0f, 1.0f),
      Colorf(1.0f, 1.0f, 1.0f), Colorf(1.0f, 0.5f, 0.0f),
  };
  inline static float interactionForces[8 * 8] = {};

private:
  sf::CircleShape shape;
};
