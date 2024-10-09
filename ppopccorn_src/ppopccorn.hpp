#pragma once

#include "particle.hpp"
#include "simulation.hpp"

#define RED_RED "red->red"
#define RED_GREEN "red->green"
#define RED_BLUE "red->blue"
#define RED_YELLOW "red->yellow"
#define RED_MAGENTA "red->magenta"
#define RED_CYAN "red->cyan"
#define RED_WHITE "red->white"
#define RED_ORANGE "red->orange"

#define GREEN_RED "green->red"
#define GREEN_GREEN "green->green"
#define GREEN_BLUE "green->blue"
#define GREEN_YELLOW "green->yellow"
#define GREEN_MAGENTA "green->magenta"
#define GREEN_CYAN "green->cyan"
#define GREEN_WHITE "green->white"
#define GREEN_ORANGE "green->orange"

#define BLUE_RED "blue->red"
#define BLUE_GREEN "blue->green"
#define BLUE_BLUE "blue->blue"
#define BLUE_YELLOW "blue->yellow"
#define BLUE_MAGENTA "blue->magenta"
#define BLUE_CYAN "blue->cyan"
#define BLUE_WHITE "blue->white"
#define BLUE_ORANGE "blue->orange"

#define YELLOW_RED "yellow->red"
#define YELLOW_GREEN "yellow->green"
#define YELLOW_BLUE "yellow->blue"
#define YELLOW_YELLOW "yellow->yellow"
#define YELLOW_MAGENTA "yellow->magenta"
#define YELLOW_CYAN "yellow->cyan"
#define YELLOW_WHITE "yellow->white"
#define YELLOW_ORANGE "yellow->orange"

#define MAGENTA_RED "magenta->red"
#define MAGENTA_GREEN "magenta->green"
#define MAGENTA_BLUE "magenta->blue"
#define MAGENTA_YELLOW "magenta->yellow"
#define MAGENTA_MAGENTA "magenta->magenta"
#define MAGENTA_CYAN "magenta->cyan"
#define MAGENTA_WHITE "magenta->white"
#define MAGENTA_ORANGE "magenta->orange"

#define CYAN_RED "cyan->red"
#define CYAN_GREEN "cyan->green"
#define CYAN_BLUE "cyan->blue"
#define CYAN_YELLOW "cyan->yellow"
#define CYAN_MAGENTA "cyan->magenta"
#define CYAN_CYAN "cyan->cyan"
#define CYAN_WHITE "cyan->white"
#define CYAN_ORANGE "cyan->orange"

#define WHITE_RED "white->red"
#define WHITE_GREEN "white->green"
#define WHITE_BLUE "white->blue"
#define WHITE_YELLOW "white->yellow"
#define WHITE_MAGENTA "white->magenta"
#define WHITE_CYAN "white->cyan"
#define WHITE_WHITE "white->white"
#define WHITE_ORANGE "white->orange"

#define ORANGE_RED "orange->red"
#define ORANGE_GREEN "orange->green"
#define ORANGE_BLUE "orange->blue"
#define ORANGE_YELLOW "orange->yellow"
#define ORANGE_MAGENTA "orange->magenta"
#define ORANGE_CYAN "orange->cyan"
#define ORANGE_WHITE "orange->white"
#define ORANGE_ORANGE "orange->orange"

// Sets an interactions strength
// First color is the color that will be affected when comming into proximity with the second color
// ex -> RED_BLUE effects a red particle comming into proximity with a blue particle, the blue particle will be unaffected
#define SetInteraction(interaction_id, interaction_strength) Particle::InteractionForcesMap[interaction_id] = interaction_strength;

// Adds a reaction
//@param reaction callback must be a function pointer that return void and takes a reactionParticle as its only parameter
//@param reaction_check_callback must be a function pointer that returns a bool and takes a reactionParticle as its only parameter
// reaction_callback will be called on a particle whenever reaction_check_callback returns true
#define AddReaction(reaction_callback, reaction_check_callback) Particle::addReaction(reaction_callback, reaction_check_callback);

typedef Particle *reactionParticle;

enum ParticleColor{
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  YELLOW = 3,
  MAGENTA = 4,
  CYAN = 5,
  WHITE = 6,
  ORANGE = 7,
};

//Is called before the main simulation loop is called setup interactions/reactions and enable systems here
extern void create_simulation();

// Sets how many of the 8 colors are enabled
// 8 is max
// 1 is min
void enableColors(int count);

//Enables the spawner
//Will spawn particles until fps drops bellow fps target
void enableSpawner(bool enabled);

// sets fps target
void setFpsTarget(int target);

// Enable reaction checking
void enableReactions(bool enabled);

// Enable interaction checking
void enableInteractions(bool enabled);
