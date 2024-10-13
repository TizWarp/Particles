#pragma once

#include "particle.hpp"
#include "defines.hpp"
#include <SFML/Graphics/Color.hpp>



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
