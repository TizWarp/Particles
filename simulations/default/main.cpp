#include "ppopccorn.hpp"
#include <ppopccorn.cpp>

bool blue_to_green_react_checl(reactionParticle particle){
  return particle->color == BLUE && particle->touching_particles[RED] > 2; 
}

void blue_to_green_reaction(reactionParticle particle){
  particle->color = GREEN;
}

bool green_to_blue_check(reactionParticle particle){
  return particle->color == GREEN && particle->touching_particles[GREEN] > 3;
}

void green_to_blue(reactionParticle particle){
  particle->color = BLUE;
}

bool yellow_to_blue_check(reactionParticle particle){
  return particle->color == YELLOW && particle->touching_particles[RED] > 1 && particle->touching_particles[BLUE] > 0;
}

void yellow_to_blue(reactionParticle particle){
  particle->color = BLUE;
}

void create_simulation(){
  SetInteraction(RED_RED, 2.5f);
  SetInteraction(RED_BLUE, 2.5f);
  SetInteraction(RED_GREEN, -2.5f);
  SetInteraction(RED_YELLOW, 0.0f);

  SetInteraction(BLUE_BLUE, -2.5f);
  SetInteraction(BLUE_RED, 2.5f);
  SetInteraction(BLUE_GREEN, -2.5f);
  SetInteraction(BLUE_YELLOW, -1.0f);
  
  SetInteraction(GREEN_RED, -2.5f);
  SetInteraction(GREEN_GREEN, 2.5f);
  SetInteraction(GREEN_BLUE, -2.5f);
  SetInteraction(GREEN_YELLOW, -1.0f);

  SetInteraction(YELLOW_YELLOW, 0.5f);
  SetInteraction(YELLOW_RED, 1.0);
  SetInteraction(YELLOW_BLUE, -2.0);
  SetInteraction(YELLOW_GREEN, 5.0);

  AddReaction(blue_to_green_reaction, blue_to_green_react_checl);
  AddReaction(green_to_blue, green_to_blue_check);
  AddReaction(yellow_to_blue, yellow_to_blue_check);

  enableColors(4);
  enableReactions(true);
  enableSpawner(true);
  enableInteractions(true);
  setFpsTarget(60); 
};
