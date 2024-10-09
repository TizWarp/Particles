#include "ppopccorn.hpp"
#include <ppopccorn.cpp>

// reactionParticle fields
// velocity : particle velocity;
// position : particle position;
// touching_particles : array of vectors, each vector is a a list of pointers to
// the currently colliding particles of each color;

// check function that makes sure the tested particle is touching at least 4 red
// particles
bool reaction_check(reactionParticle particle) {
  return particle->touching_particles[RED].size() > 4;
}

// reaction function that turns all touching red particles into blue ones
void reaction(reactionParticle particle) {
  for (reactionParticle other_particle : particle->touching_particles[RED]) {
    other_particle->color = BLUE;
  }
  particle->color = BLUE;
}

void create_simulation() {

  //             || Set interactions
  //             \/ first arg is the color that will be affected
  SetInteraction(RED, RED, 2.5f);
  SetInteraction(RED, BLUE, -2.5f);
  SetInteraction(RED, GREEN, 2.0f);
  // |                             |
  // -------------------------------
  //             |
  // red particles will move twords green particles

  // second arg is the color that will cause the interactions
  // but will not be affected itself
  //                     ||
  //                     \/
  SetInteraction(BLUE, GREEN, 2.0f);
  SetInteraction(BLUE, RED, 2.5f);

  // Thrid arg is strength      ||
  //                            \/
  SetInteraction(GREEN, GREEN, -1.0f);
  //|                                  |
  //------------------------------------
  //               |
  // green particles will run away from green particles

  // arg1 is target color, only green particles will check for this reaction
  // arg2 is reaction function what actually happens when the reaction accurs
  // arg3 is reaction check func that checks if the reaction should happen.
  AddReaction(GREEN, reaction, reaction_check);

  enableColors(3);
  enableReactions(true);
  enableSpawner(true);
  enableInteractions(true);
  setFpsTarget(60);
};
