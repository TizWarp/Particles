#pragma once

#include "particle.hpp"
#include "defines.hpp"
#include <SFML/Graphics/Color.hpp>
// Sets an interactions strength
// First color is the color that will be affected when comming into proximity with the second color
// ex -> RED_BLUE effects a red particle comming into proximity with a blue particle, the blue particle will be unaffected
#define SetInteraction(affected, affector, strength) Particle::interactionForces[affected + (affector * 8)] = strength

// Adds a reaction
//@param reaction callback must be a function pointer that return void and takes a reactionParticle as its only parameter
//@param reaction_check_callback must be a function pointer that returns a bool and takes a reactionParticle as its only parameter
// reaction_callback will be called on a particle whenever reaction_check_callback returns true
#define AddReaction(target_color, reaction_callback, reaction_check_callback) Particle::addReaction(target_color, reaction_callback, reaction_check_callback);

/*#define SetColor(target_particle, color) Particle::particle_colors[target_particle] = color;*/

enum ParticleDef{
  ParticleType1 = 0,
  ParticleType2 = 1,
  ParticleType3 = 2,
  ParticleType4 = 3,
  ParticleType5 = 4,
  ParticleType6 = 5,
  ParticleType7 = 6,
  ParticleType8 = 7,
};

typedef Particle *reactionParticle;
typedef sf::Color Color;
// Sets how many of the 8 colors are enabled
// 8 is max
// 1 is min
void enableColors(int count);

//Enables the spawner
//Will spawn particles until fps drops bellow fps target
void enableSpawner(bool enabled);

// sets fps target
void setFpsTarget(int target);

// Enable reaction checking
void enableReactions(bool enabled);

// Enable interaction checking
void enableInteractions(bool enabled);

void setParticleMax(int max);

float getVecMagnitude(Vector2 vec);
