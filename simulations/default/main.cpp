#include "ppopccorn.hpp"
#include <ppopccorn.cpp>

bool reaction_check(reactionParticle particle){
  return particle->touching_particles[RED].size() > 4;
}

void reaction(reactionParticle particle){
  for (reactionParticle other_particle : particle->touching_particles[RED]){
    other_particle->color = BLUE;
  }
  particle->color = BLUE;
}

void create_simulation(){

  //             || Set interactions 
  //             \/ first arg is the color that will be affected 
  SetInteraction(RED, RED, 2.5f);
  SetInteraction(RED, BLUE, -2.5f);
  SetInteraction(RED, GREEN, 2.0f);


  // second arg is the color that will cause the interactions
  //                     ||
  //                     \/
  SetInteraction(BLUE, GREEN, 2.0f);
  SetInteraction(BLUE, RED, 2.5f);

  // Thrid arg is strength      ||
  //                            \/
  SetInteraction(GREEN, GREEN, 0.0f);


  AddReaction(GREEN, reaction, reaction_check);

  enableColors(3);
  enableReactions(true);
  enableSpawner(true);
  enableInteractions(true);
  setFpsTarget(60); 
};
