#pragma once

#include <SFML/System/Vector2.hpp>
float distanceTo(sf::Vector2f from, sf::Vector2f to);

sf::Vector2f normalizeVec(sf::Vector2f vec);

sf::Vector2f directionTo(sf::Vector2f from, sf::Vector2f to);

float vecMagnitude(sf::Vector2f vec);

