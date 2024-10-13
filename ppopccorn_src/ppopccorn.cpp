#include "ppopccorn.hpp"
#include "particle.hpp"
#include "simulation.hpp"
#include "math.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <fstream>
#include <ios>
#include <random>
#include <string>
#include <sys/types.h>
#include <vector>
#include "defines.hpp"

int main() {

  /*Vector2 test1(0.0f, 1.0f);*/
  /*Vector2 test2(0.0f, 0.0f);*/
  
  /*float percent = 1.0f - (radToDeg(angleBetween(test1, test2)) / 180.0f);*/
  /*printf("%f\n",percent);*/

  /*return 0;*/

  Simulation sim = Simulation();
  sim.init();
  
  sim.run();

 
  return 0;
}
