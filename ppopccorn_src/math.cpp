#include "math.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include "defines.hpp"

float radToDeg(float rads){
  return rads * RAD_TO_DEG;
}

float angleBetween(Vector2 vec1, Vector2 vec2) {
  float dot = vec1.x * vec2.x + vec1.y * vec2.y;
  float det = vec1.x * vec2.y - vec1.y * vec2.x;
  return atan2(dot, det);
}

float vecMagnitude(Vector2 vec) {
  return std::sqrtf(((vec.x * vec.x) + (vec.y * vec.y)));
}

float distanceTo(Vector2 from, Vector2 to) {
  return sqrtf(((to.x - from.x) * (to.x - from.x)) +
               ((to.y - from.y) * (to.y - from.y)));
}

Vector2 normalizeVec(Vector2 vec) {
  float mag = vecMagnitude(vec);
  return Vector2(vec.x / mag, vec.y / mag);
}

Vector2 directionTo(Vector2 from, Vector2 to) {
  return normalizeVec(to - from);
}

float dotProduct(Vector2 vec1, Vector2 vec2);

bool doesBoundContainPoint(Vector2 point, Bounds bounds) {
  return point.x < bounds.lower.x && point.y < bounds.lower.y &&
         point.y > bounds.upper.y && point.x > bounds.upper.x;
}

bool isRadiusWithin(Vector2 position, float radius, Bounds bounds) {

  float upper_x = position.x - radius;
  float upper_y = position.y - radius;
  float lower_y = position.y + radius;
  float lower_x = position.x + radius;
  return upper_x > bounds.upper.x && upper_y > bounds.upper.y &&
         lower_x < bounds.lower.x && lower_y < bounds.lower.y;
}

bool isRadiusPartilWithin(Vector2 position, float radius, Bounds bounds) {
  float upper_x = position.x - radius;
  float upper_y = position.y - radius;
  float lower_y = position.y + radius;
  float lower_x = position.x + radius;

  Vector2 upper_center = Vector2(position.x, upper_y);
  Vector2 lower_center = Vector2(position.x, lower_y);
  Vector2 right_center = Vector2(lower_x, position.y);
  Vector2 left_center = Vector2(upper_x, position.y);

  /*printf("%f\n",bounds.upper.x);*/
  return doesBoundContainPoint(upper_center, bounds) || doesBoundContainPoint(lower_center, bounds) || doesBoundContainPoint(right_center, bounds) || doesBoundContainPoint(left_center, bounds);
}

// Red
// blue
// green
// yellow
//  Magenta
// cyan
// white
// orange
