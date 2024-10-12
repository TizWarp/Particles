#include "quadtree.hpp"
#include "defines.hpp"
#include "math.h"
#include "math.hpp"
#include "simulation.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <thread>

QuadTree::QuadTree(Bounds bounds, bool is_root) {
  this->bounds = bounds;
  this->is_root = is_root;

  rect_shape = sf::RectangleShape(bounds.lower - bounds.upper);
  rect_shape.setPosition(bounds.upper);
  rect_shape.setFillColor(sf::Color::Transparent);
  rect_shape.setOutlineThickness(1.0f);
  rect_shape.setOutlineColor(sf::Color::White);
}

void QuadTree::render(Window &window) {
  window.draw(rect_shape);
  for (QuadTree tree : children) {
    tree.render(window);
  }
}

void QuadTree::clear() {
  quad_particles.clear();
  if (!children.empty()) {
    for (QuadTree child : children) {
      child.clear();
    }
  }
  quad_particles.clear();
  children.clear();
}

void QuadTree::resize(Bounds new_bounds) { this->bounds = new_bounds; }

void QuadTree::generate(int particle_max) {
  if (Simulation::particles.empty()) {
    return;
  }
  for (int index = 0; index < Simulation::particles.size(); index++) {
    Particle *particle = &Simulation::particles[index];

    if (isRadiusPartilWithin(particle->position, particle->radius, bounds)) {
      quad_particles.push_back(index);
    }

    if (quad_particles.size() > particle_max) {

      quad_particles.clear();

      Vector2 top_left = bounds.upper;
      Vector2 bottom_right = bounds.lower;
      Vector2 center = bounds.upper + ((bounds.lower - bounds.upper) / 2.0f);
      Vector2 bottom_center = Vector2(center.x, bounds.lower.y);
      Vector2 top_center = Vector2(center.x, bounds.upper.y);
      Vector2 left_center = Vector2(bounds.upper.x, center.y);
      Vector2 right_center = Vector2(bounds.lower.x, center.y);

      QuadTree child1 = QuadTree(Bounds{top_left, center});
      QuadTree child2 = QuadTree(Bounds{center, bottom_right}); // problem child
      QuadTree child3 = QuadTree(Bounds{top_center, right_center});
      QuadTree child4 = QuadTree(Bounds{left_center, bottom_center});

      child1.generate(particle_max);
      child2.generate(particle_max);
      child3.generate(particle_max);
      child4.generate(particle_max);

      children.push_back(child1);
      children.push_back(child2);
      children.push_back(child3);
      children.push_back(child4);

      return;
    }
  }
}

void QuadTree::physicsProcess(float dt) {
  if (quad_particles.empty()) {
    if (is_root) {
      for (QuadTree child : children){
        Simulation::thread_pool.QueueJob([&child, dt]{child.physicsProcess(dt);});
      }
    } else {
      for (QuadTree child : children) {
        child.physicsProcess(dt);
      }
    }
    return;
  }

  for (int index : quad_particles) {
    Particle *particle = &Simulation::particles[index];

    for (int index2 : quad_particles) {
      if (index == index2) {
        continue;
      }
      Particle *particle2 = &Simulation::particles[index2];
      float distance = distanceTo(particle->position, particle2->position);
      float radi = particle->radius + particle2->radius;
      Vector2 dir = directionTo(particle->position, particle2->position);

      if (Simulation::interactions_enabled) {
        particle->velocity +=
            dir * (particle->getInteractionForces(particle2->type) / distance);
      }
      if (Simulation::reactions_enabled) {
        Particle::updateReactions(particle);
      }

      if (distance < radi) {
        particle->touched(particle2);
        float dif = (radi - distance);

        float particle1_vel_percentage =
            -((radToDeg(angleBetween(dir, particle->velocity)) - 180.0f) /
              180.0f);
        float particle2_vel_percentage =
            -((radToDeg(angleBetween(dir, particle2->velocity)) - 180.0f) /
              180.0f);

        /*printf("%f\n", particle1_vel_percentage);*/

        particle->velocity -=
            dir * (vecMagnitude(particle2->velocity * 0.125f) *
                   particle2_vel_percentage);
        particle2->velocity += dir * (vecMagnitude(particle->velocity * 0.125f) *
                                      particle1_vel_percentage);

        particle->position -= dir * dif * 0.5f;
        particle2->position += dir * dif * 0.5f;
      }
    }
  }
}
