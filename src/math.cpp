#include "math.hpp"

#define PI 3.14159
#define RAD_TO_DEG 180.0f/PI

float angleBetween(Vec2 vec1, Vec2 vec2){
  float mag1 = vecMagnitude(vec1);
  float mag2 = vecMagnitude(vec2);

  float dot = (vec1.x * vec2.x) + (vec1.y * vec2.y);
  float det = mag1 * mag2;
  return acos(dot/det);
}

float radToDeg(float rads){
  return rads * RAD_TO_DEG;
}

float distanceTo(Vec2 from, Vec2 to){
  return sqrtf(((to.x - from.x) * (to.x - from.x)) +
               ((to.y - from.y) * (to.y - from.y)));
}

Vec2 normalizeVec(Vec2 vec){
  float mag = vecMagnitude(vec);
  return Vec2(vec.x / mag, vec.y / mag);
}

Vec2 directionTo(Vec2 from, Vec2 to){
 return normalizeVec(to - from);
}

float vecMagnitude(Vec2 vec){
  return std::sqrtf(((vec.x * vec.x) + (vec.y * vec.y)));
}

template<typename T>
T max(T p1, T p2){
  if (p1 > p2){
    return p1;
  } else {
    return p2;
  }
}
