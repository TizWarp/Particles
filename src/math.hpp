#pragma once

#include "defines.hpp"


float angleBetween(Vec2 vec1, Vec2 vec2);

float radToDeg(float rads);

float distanceTo(Vec2 from, Vec2 to);

Vec2 normalizeVec(Vec2 vec);

Vec2 directionTo(Vec2 from, Vec2 to);

float vecMagnitude(Vec2 vec);

template<typename T>
T max(T p1, T p2);
