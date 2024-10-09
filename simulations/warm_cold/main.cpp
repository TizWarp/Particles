#include "particle.hpp"
#include "ppopccorn.hpp"
#include <ppopccorn.cpp>

void create_simulation(){
  SetInteraction(RED_RED, 2.5f);
  SetInteraction(RED_GREEN, -2.5f);
  SetInteraction(RED_BLUE, -2.5f);
  SetInteraction(RED_YELLOW, 2.5f);
  SetInteraction(RED_MAGENTA, -2.5f);
  SetInteraction(RED_CYAN, -2.5f);
  SetInteraction(RED_WHITE, 2.5f);
  SetInteraction(RED_ORANGE, 2.5f);

  SetInteraction(GREEN_RED, -2.5f);
  SetInteraction(GREEN_GREEN, 2.5f);
  SetInteraction(GREEN_BLUE, 2.5f);
  SetInteraction(GREEN_YELLOW, -2.5f);
  SetInteraction(GREEN_MAGENTA, 2.5f);
  SetInteraction(GREEN_CYAN, 2.5f);
  SetInteraction(GREEN_WHITE, -2.5f);
  SetInteraction(GREEN_ORANGE, -2.5f);

  SetInteraction(BLUE_RED, -2.5f);
  SetInteraction(BLUE_GREEN, 2.5f);
  SetInteraction(BLUE_BLUE, 2.5f);
  SetInteraction(BLUE_YELLOW, -2.5f);
  SetInteraction(BLUE_MAGENTA, 2.5f);
  SetInteraction(BLUE_CYAN, 2.5f);
  SetInteraction(BLUE_WHITE, -2.5f);
  SetInteraction(BLUE_ORANGE, -2.5f);

  SetInteraction(YELLOW_RED, 2.5f);
  SetInteraction(YELLOW_GREEN, -2.5f);
  SetInteraction(YELLOW_BLUE, -2.5f);
  SetInteraction(YELLOW_YELLOW, 2.5f);
  SetInteraction(YELLOW_MAGENTA, -2.5f);
  SetInteraction(YELLOW_CYAN, -2.5f);
  SetInteraction(YELLOW_WHITE, 2.5f);
  SetInteraction(YELLOW_ORANGE, 2.5f);

  SetInteraction(MAGENTA_RED, -2.5f);
  SetInteraction(MAGENTA_GREEN, 2.5f);
  SetInteraction(MAGENTA_BLUE, 2.5f);
  SetInteraction(MAGENTA_YELLOW, -2.5f);
  SetInteraction(MAGENTA_MAGENTA, 2.5f);
  SetInteraction(MAGENTA_CYAN, 2.5f);
  SetInteraction(MAGENTA_WHITE, -2.5f);
  SetInteraction(MAGENTA_ORANGE, -2.5f);

  SetInteraction(CYAN_RED, -2.5f);
  SetInteraction(CYAN_GREEN, 2.5f);
  SetInteraction(CYAN_BLUE, 2.5f);
  SetInteraction(CYAN_YELLOW, -2.5f);
  SetInteraction(CYAN_MAGENTA, 2.5f);
  SetInteraction(CYAN_CYAN, 2.5f);
  SetInteraction(CYAN_WHITE, -2.5f);
  SetInteraction(CYAN_ORANGE, -2.5f);

  SetInteraction(WHITE_RED, 2.5f);
  SetInteraction(WHITE_GREEN, -2.5f);
  SetInteraction(WHITE_BLUE, -2.5f);
  SetInteraction(WHITE_YELLOW, 2.5f);
  SetInteraction(WHITE_MAGENTA, -2.5f);
  SetInteraction(WHITE_CYAN, -2.5f);
  SetInteraction(WHITE_WHITE, 2.5f);
  SetInteraction(WHITE_ORANGE, 2.5f);

  SetInteraction(ORANGE_RED, 2.5f);
  SetInteraction(ORANGE_GREEN, -2.5f);
  SetInteraction(ORANGE_BLUE, -2.5f);
  SetInteraction(ORANGE_YELLOW, 2.5f);
  SetInteraction(ORANGE_MAGENTA, -2.5f);
  SetInteraction(ORANGE_CYAN, -2.5f);
  SetInteraction(ORANGE_WHITE, 2.5f);
  SetInteraction(ORANGE_ORANGE, 2.5f);

  enableColors(8);
  enableInteractions(true);
  enableSpawner(true);
};
