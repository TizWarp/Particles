#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

sf::Vector2f getMousePos();

float distanceTo(sf::Vector2f from, sf::Vector2f to);

sf::Vector2f normalizeVec(sf::Vector2f vec);

sf::Vector2f directionTo(sf::Vector2f from, sf::Vector2f to);

float vecMagnitude(sf::Vector2f vec);

bool doesBoundContainPoint(sf::Vector2f vec, sf::Vector2f upper_bounds, sf::Vector2f lower_bounds);
