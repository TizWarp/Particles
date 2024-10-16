#pragma once

#include "defines.hpp"

class Particle{
  public:
    Vec2 position;
    Vec2 velocity;
    u64 life;
    u32 type;

    Particle(u32 type);
    Particle(u32 type, Vec2 position, Vec2 velocity);

    void update(f32 dt);
};
