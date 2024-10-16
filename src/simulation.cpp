#include "simulation.hpp"
#include "defines.hpp"
#include "math.hpp"
#include "particle.hpp"
#include <cmath>
#include <random>

Simulation::Simulation(Vec2 size) {
  this->simulation_area = size;
  particle_colors.resize(particle_type_count, Color(1.0f, 1.0f, 1.0f));
  particle_interactions.resize(particle_type_count * particle_type_count, ParticleInteraction{0.0f, 0.0f});
  particles.clear();
}

void Simulation::popParticle() { particles.pop_back(); }

void Simulation::addParticle(Particle particle) {
  particles.push_back(particle);
}

void Simulation::clearParticles() { particles.clear(); }

void Simulation::setParticleColor(u32 type, Color color) {
  particle_colors[type] = color;
}

Color Simulation::getParticleColor(u32 type) { return particle_colors[type]; }

void Simulation::setInteractionStrength(u32 type1, u32 type2, float interaction) {
  particle_interactions[type1 + (type2 * particle_type_count)].strength = interaction;
}

float *Simulation::getInteractionStrength(u32 type1, u32 type2) {
  return &particle_interactions[type1 + (type2 * particle_type_count)].strength;
}

float *Simulation::getInteractionDistance(u32 type1, u32 type2){
  return &particle_interactions[type1 + (type2 * particle_type_count)].distance;
}
void Simulation::setInteractionDistance(u32 type1, u32 type2, float distance){
  particle_interactions[type1 + (type2 * particle_type_count)].distance = distance;
}

void Simulation::setParticleTypeCount(u32 count) {
  particle_type_count = count;
  particle_interactions.resize(count * count, ParticleInteraction{0.0f, 0.0f});;
  particle_colors.resize(count, Color(1.0f, 1.0f, 1.0f));
}

const i32 SUBSTEPS = 8;

void Simulation::updatePhysics(f32 dt, u32 start, u32 end) {
  float sub_dt = dt / (float)SUBSTEPS;
  for (i32 step = 0; step < SUBSTEPS; step++) {
    for (u32 particle_index1 = 0; particle_index1 < particles.size();
         particle_index1++) {
      Particle &particle1 = particles[particle_index1];
      particle1.update(sub_dt);
      particle1.velocity -= particle1.velocity * velocity_dampening * sub_dt;
      boundsCheck(particle1);

      for (u32 particle_index2 = start; particle_index2 < end; particle_index2++) {
        if (particle_index1 == particle_index2) {
          continue;
        }
        Particle &particle2 = particles[particle_index2];
        Vec2 dir = directionTo(particle1.position, particle2.position);
        f32 distance = distanceTo(particle1.position, particle2.position);

        if (distance < *getInteractionDistance(particle1.type, particle2.type)){
          particle1.velocity += dir * (0.125f * (*getInteractionStrength(particle1.type, particle2.type) / distance));
        }

        if (RADI > distance) {
          f32 dif = (RADI - distance);

          float particle1_vel_percentage =
              1.0f -
              (radToDeg(angleBetween(normalizeVec(particle1.velocity), dir)) /
               180.0f);
          float particle2_vel_percentage =
              1.0f -
              (radToDeg(angleBetween(normalizeVec(particle2.velocity), dir)) /
               180.0f);

          if (particle1_vel_percentage != particle1_vel_percentage) {
            particle1_vel_percentage = 0.0f;
          }
          if (particle2_vel_percentage != particle2_vel_percentage) {
            particle2_vel_percentage = 0.0f;
          }

          particle1.velocity -= dir * particle2_vel_percentage * vecMagnitude(particle2.velocity) * 0.125f;
          particle2.velocity += dir * particle1_vel_percentage * vecMagnitude(particle1.velocity) * 0.125f;

          particle1.position -= dir * dif * 0.5f;
          particle2.position += dir * dif * 0.5f;
        }
      }
    }
  }
}

void Simulation::boundsCheck(Particle &particle) {
  if (particle.position.x + RADIUS > simulation_area.x) {
    particle.position.x = simulation_area.x - RADIUS;
    particle.velocity.x = -particle.velocity.x * 0.25f;
  }
  if (particle.position.y + RADIUS > simulation_area.y) {
    particle.position.y = simulation_area.y - RADIUS;
    particle.velocity.y = -particle.velocity.y * 0.25f;
  }
  if (particle.position.x - RADIUS < 0.0f) {
    particle.position.x = RADIUS;
    particle.velocity.x = -particle.velocity.x * 0.25f;
  }
  if (particle.position.y - RADIUS < 0.0f) {
    particle.position.y = RADIUS;
    particle.velocity.y = -particle.velocity.y * 0.25f;
  }
}

void Simulation::spawnParticles(u32 count) {
  Vec2 spawn_point = (simulation_area ) / 2.0f;

  u32 x_div = count;
  if (count > 10){
    x_div = 10;
  }

  u32 y_div = count / 10;

  f32 x_inc = simulation_area.x/x_div;
  f32 y_inc = simulation_area.y/y_div;
  i32 type = 0;
  for (u32 c = 0; c < count; c++) {
    f32 x_pos = (float)((c + 1) % 10) * x_inc;
    f32 y_pos = (float)((c + 1) / 10) * y_inc;

    addParticle(Particle((type += 1) % particle_type_count, Vec2(x_pos, y_pos), Vec2(0.0f, 0.0f)));
  }
}


void Simulation::randomizeInteractions(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<f32> distr(-100.0f, 100.0f);
  std::uniform_real_distribution<f32> pos_dist(1.0f, 200.0f);

  for (i32 i = 0; i < (particle_type_count * particle_type_count); i++){
    particle_interactions[i] = ParticleInteraction{pos_dist(gen), distr(gen)};
  }
}
