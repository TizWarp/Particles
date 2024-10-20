#include "application.hpp"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

int main(){

  Application::init();

  Application::run();

  Application::shutdown();

  return 0;
}
