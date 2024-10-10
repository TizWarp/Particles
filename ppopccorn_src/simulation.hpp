#pragma once

#include "defines.hpp"
#include "particle.hpp"
#include "ppopccorn.hpp"
#include "quadtree.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <vector>

enum MouseState{
  PULL,
  PUSH,
  NONE,
};

class Simulation {
public:
  inline static std::vector<Particle> particles = {};
  inline static bool reactions_enabled = false;
  inline static bool interactions_enabled = false;
  inline static MouseState mouseState = NONE;
  inline static Vector2 mouse_pos = Vector2(0.0f, 0.0f);

  bool physics_paused;
  bool draw_quad_tree;
  sf::Font font;
  QuadTree quad_tree;
  Window window;
  Bounds bounds;
  bool loop_bounds;
  sf::Clock deltaClock;
  int particle_max;
  int fps;

  Simulation(){};

  void init();

  void addParticle(float radius, Vector2 position,
                   Vector2 velocity = Vector2(0.0f, 0.0f), uint8_t id = 0);
  void physicsUpdate(float dt);
  void renderPass();
  void clearParticles();
  void loopBoundsCheck(Particle *particle);
  void bounceBoundsCheck(Particle *particle);
  void renderUI();
  Vector2 getMousePos();
  MouseState getMouseState();
  void run();
};
