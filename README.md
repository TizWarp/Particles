# Ppopccorn
### A Particle life simulator

## Installation
- Make sure SFML and Cmake are on your system
- Clone repo and run cmake ./
- Binaries will be located in the **./bin** folder

## Creating Simulations
- Make sure you can compile and run the **default** simulation
- Create a new directory inside of **./simulations**
- Create a cpp file name does not matter
- Include **<ppopccorn.hpp>**
- Define `void create_simulation()`

Inside of the `void create_simulation()` function is where you define the parameters for your simulation

The First thing you will want to do is set some parameters:

- `setFpsTarget(int)` sets the fps target defaults to 60 [FPS Target](#fps-target)
- `enableColors(int)` sets the number of enabled colors defauts to 1 goes up to 8
- `enableSpawner(bool)` enables the spawner defaults to false
- `enableInteractions(bool)` enables interaction checking
- `enableReactions(bool)` enables reaction checking


#### FPS Target and Spawner
The spawner will continously spawn particles in the cetner of the simulation until the frames drop lower than the fps target. Frames should not go lower than 55 but this simulation is not a light application.

The Spawner will spawn alternating colored particles, going through all enabled colors.

## Colors Interactions and Reactions

### Colors
Every particle has a color. There are eight colors int total each color is also repersented by a number:
- Red = 0
- Green = 1
- Blue = 2
- Yellow = 3
- Magenta = 4
- Cyan = 5
- White = 6 
- Orange = 7

When `enableColors(int)` is called all colors up to the number passed in are enabled.

### Interactions
When interactions are enabled via `enableInteractions(bool)` a particle will be influenced by other particles around it \
All interactions default to nothing so you must run `setInteraction(interaction_def, float)` to change them.

The second argument is the strength of the interaction. Positive numbers attract, negitive numbers repel \
The first argument is a combonation of two colors *COLOR1_COLOR2* `ppopccorn.hpp` defines many constants for this\

The first color is the color that will be affected by interaction with the second color \
**ex:** `setInteraction(RED_BLUE, 2.5f)` this makes it so that red particles are attracted to blue particles, blue particles are unaffected.

### Reactions
Reactions allow more complex behavoir by defining functions that operate on particles when certain conditions are met.
Keep in mind that reaction checks are one of the more expensive operations so performace will decrese with reactions enabled. Espcially when lots of reactions are defined.

To enable reactions simply run `enableReactions(bool)`

Defining reactions is a little more complex\
You need to define two function with the following signatures:

- `bool reaction_check(reactionParticle particle);`
- `void reaction_func(reactionParticle particle);`

The first function is the *check* function this should return a bool weather or not the reaction should accur\
The second function is the *reaction* function, this is what is called when the *check* fuction returns true\

The reactionParticles have many different fields that can be checked or modified:
- `particle->color` the current color of the particle
- `particle->velocity` the particles current velocity
- `particle->position` the particles current position

`reactionParticle` also has an size 8 array of type int that contains contact info. Each number in the array corrosponds to the number of particles of that color currently touching the particle \
**ex:** `particle->touched_particles[RED] > 0` would return true if the particle was touching at least 1 red particle

Once you have your functions defined go ahead and call `AddReaction(reaction_func, reaction_check)` passing in the *reaction* function and the *check* function as the first and second parameters.
