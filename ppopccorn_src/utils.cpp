#include "utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>
#include <cstdlib>


float radToDeg(float rads){
  return rads * (180.0/3.14159);
}

float angleBetween(sf::Vector2f vec1, sf::Vector2f vec2) {
  float dot = vec1.x * vec2.x + vec1.y * vec2.y;
  float det = vec1.x * vec2.y - vec1.y * vec2.x;
  return atan2(dot, det);
}

float vecMagnitude(sf::Vector2f vec) {
  return std::sqrtf(((vec.x * vec.x) + (vec.y * vec.y)));
}

float distanceTo(sf::Vector2f from, sf::Vector2f to) {
  return sqrtf(((to.x - from.x) * (to.x - from.x)) +
               ((to.y - from.y) * (to.y - from.y)));
}

sf::Vector2f normalizeVec(sf::Vector2f vec) {
  float mag = vecMagnitude(vec);
  return sf::Vector2f(vec.x / mag, vec.y / mag);
}

sf::Vector2f directionTo(sf::Vector2f from, sf::Vector2f to) {
  return normalizeVec(to - from);
}

float dotProduct(sf::Vector2f vec1, sf::Vector2f vec2);

bool doesBoundContainPoint(sf::Vector2f vec, sf::Vector2f upper_bounds,
                           sf::Vector2f lower_bounds) {
  return vec.x <= upper_bounds.x && vec.y <= upper_bounds.y &&
         vec.y >= lower_bounds.y && vec.x >= lower_bounds.x;
}

bool isParticleWithin(Particle *particle, sf::Vector2f upper_bounds,
                      sf::Vector2f lower_bounds) {

  float upper_x = particle->position.x + particle->radius;
  float upper_y = particle->position.y + particle->radius;
  float lower_y = particle->position.y - particle->radius;
  float lower_x = particle->position.x - particle->radius;
  return upper_x < upper_bounds.x && upper_y < upper_bounds.y &&
         lower_x > lower_bounds.x && lower_y > lower_bounds.y;
}

bool isParticlePartilWithin(Particle *particle, sf::Vector2f upper_bounds,
                            sf::Vector2f lower_bounds) {
  float upper_x = particle->position.x + particle->radius;
  float upper_y = particle->position.y + particle->radius;
  float lower_y = particle->position.y - particle->radius;
  float lower_x = particle->position.x - particle->radius;

  return doesBoundContainPoint(sf::Vector2f(upper_x, particle->position.y),
                               upper_bounds, lower_bounds) ||
         doesBoundContainPoint(sf::Vector2f(lower_x, particle->position.y),
                               upper_bounds, lower_bounds) ||
         doesBoundContainPoint(sf::Vector2f(particle->position.x, upper_y),
                               upper_bounds, lower_bounds) ||
         doesBoundContainPoint(sf::Vector2f(particle->position.x, lower_y),
                               upper_bounds, lower_bounds) ||
         doesBoundContainPoint(sf::Vector2f(upper_x, upper_y), upper_bounds,
                               lower_bounds) ||
         doesBoundContainPoint(sf::Vector2f(lower_x, lower_y), upper_bounds,
                               lower_bounds);
}

void applyForces(Particle *particle1, Particle *particle2, float strength) {
  sf::Vector2f dir = directionTo(particle1->position, particle2->position);
  float dis = distanceTo(particle1->position, particle2->position);
  particle1->velocity += dir * strength / dis;
}

// Red
// blue
// green
// yellow
//  Magenta
// cyan
// white
// orange
