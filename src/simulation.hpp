#pragma once

#include "SFML/Graphics/View.hpp"
#include "defines.hpp"
#include "particle.hpp"
#include <vector>

struct ParticleInteraction{
  float distance;
  float strength;
};

class Simulation{
  public:
    std::vector<Particle> particles;
    i32 particle_type_count = 3;
    std::vector<Color> particle_colors;
    std::vector<ParticleInteraction> particle_interactions;
    float velocity_dampening = 5.0f;
    Vec2 simulation_area;

    Simulation(){};
    Simulation(Vec2 size);

    float *getInteractionStrength(u32 type1, u32 type2);
    void setInteractionStrength(u32 type1, u32 type2, float interaction);

    float *getInteractionDistance(u32 type1, u32 type2);
    void setInteractionDistance(u32 type1, u32 type2, float distance);

    Color getParticleColor(u32 type);
    void setParticleColor(u32 type, Color color);

    void addParticle(Particle particle);
    void spawnParticles(u32 count);
    void popParticle();
    void clearParticles();

    void setParticleTypeCount(u32 count);

    void boundsCheck(Particle &particle);

    void updatePhysics(f32 dt, u32 start, u32 end);

    void randomizeInteractions();
};
