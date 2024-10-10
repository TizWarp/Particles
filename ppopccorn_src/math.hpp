#pragma once

#include "particle.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "defines.hpp"


float angleBetween(Vector2 vec1, Vector2 vec2);

float radToDeg(float rads);

Vector2 getMousePos();

float distanceTo(Vector2 from, Vector2 to);

Vector2 normalizeVec(Vector2 vec);

Vector2 directionTo(Vector2 from, Vector2 to);

float vecMagnitude(Vector2 vec);

bool doesBoundContainPoint(Vector2 vec, Bounds bounds);

bool isRadiusWithin(Vector2 position, float radius, Bounds bounds);

bool isRadiusPartilWithin(Vector2 position, float radius, Bounds bounds);
