#include "utils.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>

float vecMagnitude(sf::Vector2f vec){
  return std::sqrtf(((vec.x * vec.x) + (vec.y * vec.y)));
}

float distanceTo(sf::Vector2f from, sf::Vector2f to){
  return sqrtf(((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y)));
}

sf::Vector2f normalizeVec(sf::Vector2f vec){
  float mag = vecMagnitude(vec);
  return sf::Vector2f(vec.x/mag, vec.y/mag);
}

sf::Vector2f directionTo(sf::Vector2f from, sf::Vector2f to){
  return normalizeVec(to - from);
}

bool doesBoundContainPoint(sf::Vector2f vec, sf::Vector2f upper_bounds, sf::Vector2f lower_bounds){
  return vec.x < upper_bounds.x && vec.y < upper_bounds.y && vec.y > lower_bounds.y && vec.x > lower_bounds.x;
}
