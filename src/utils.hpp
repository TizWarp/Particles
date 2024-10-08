#pragma once

#include "particle.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

float angleBetween(sf::Vector2f vec1, sf::Vector2f vec2);

float radToDeg(float rads);

sf::Vector2f getMousePos();

float distanceTo(sf::Vector2f from, sf::Vector2f to);

sf::Vector2f normalizeVec(sf::Vector2f vec);

sf::Vector2f directionTo(sf::Vector2f from, sf::Vector2f to);

float vecMagnitude(sf::Vector2f vec);

bool doesBoundContainPoint(sf::Vector2f vec, sf::Vector2f upper_bounds, sf::Vector2f lower_bounds);

bool isParticleWithin(Particle *particle, sf::Vector2f upper_bounds, sf::Vector2f lower_bounds);

bool isParticlePartilWithin(Particle *particle, sf::Vector2f upper_bounds, sf::Vector2f lower_bounds);

void applyForces(Particle *particle1, Particle *particle2, float strength);

void renderText(sf::RenderWindow &window, std::vector<sf::Text> &texts);
