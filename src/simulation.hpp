#pragma once


#include "defines.hpp"
class Particle{
  public:
    Vec2 velocity;
    Vec2 position;
    Color color;

    Particle(Vec2 position, Vec2 velocity, Color color);

    void update(float dt);
};

namespace Simulation{

  const int SUBSTEPS = 8;
  const float RADIUS = 5.0f;

  void init();

  void addParticle(Particle particle);
  void removeParticle(int num);

  void update(float dt);

  int getParticleCount();
};
