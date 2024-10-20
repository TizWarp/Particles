#include "application.hpp"
#include "events.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "simulation.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <cstdint>
#include <fmt/base.h>
#include <spdlog/spdlog.h>

bool test(Events::EventContext) {
  spdlog::info("Shutting down");
  return false;
}

namespace Application {
static SDL_Window *window;
static SDL_GLContext gl_context;
static bool is_running = true;

static unsigned int mainShader = 0;

static uint64_t now = 0;
static uint64_t last = 0;

void pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      is_running = false;
      return;
    }
    if (event.type == SDL_MOUSEWHEEL) {
      Renderer::getCamera()->fov -= event.wheel.preciseY * 0.25f;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      int width, height;
      getWindowSize(&width, &height);

      float x = event.button.x - (width/2.0f);
      float y = event.button.y - (height/2.0f);

      x /= (width/2.0f);
      y /= (height/2.0f);

      Camera *camera = Renderer::getCamera();

      x += camera->position.x;
      y += camera->position.y;

      Simulation::addParticle(
          Particle(Vec2(x,y),
                   Vec2(0.0f, 1.0f), Color(1.0f, 1.0f, 1.0f)));
    }
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_w) {
        Camera *camera = Renderer::getCamera();
        camera->position += camera->up * 0.05f;
        camera->target += camera->up * 0.05f;
      }
      if (event.key.keysym.sym == SDLK_s) {
        Camera *camera = Renderer::getCamera();
        camera->position -= camera->up * 0.05f;
        camera->target -= camera->up * 0.05f;
      }
      if (event.key.keysym.sym == SDLK_d) {
        Camera *camera = Renderer::getCamera();
        camera->position -= camera->right * 0.05f;
        camera->target -= camera->right * 0.05f;
      }
      if (event.key.keysym.sym == SDLK_a) {
        Camera *camera = Renderer::getCamera();
        camera->position += camera->right * 0.05f;
        camera->target += camera->right * 0.05f;
      }
    }
  }
}

float getDeltaTime() {
  last = now;
  now = SDL_GetPerformanceCounter();

  return (float)(now - last) / (float)SDL_GetPerformanceFrequency();
}
}; // namespace Application

void Application::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    spdlog::error("Failed to init SDL2 {}", SDL_GetError());
  }
  Application::window = SDL_CreateWindow(
      "AparatusVivi", 0, 0, 600, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  Application::gl_context = SDL_GL_CreateContext(Application::window);
  Renderer::initRenderer();
  Simulation::init();
}
void Application::run() {
  while (Application::is_running) {
    pollEvents();

    float dt = getDeltaTime();

    Simulation::update(0.125f * dt);

    Renderer::prepareFrame();
    Renderer::drawFrame();

    SDL_GL_SwapWindow(Application::window);
  }
}
void Application::shutdown() {
  SDL_GL_DeleteContext(Application::gl_context);
  SDL_DestroyWindow(Application::window);
}

void Application::getWindowSize(int *width, int *height) {
  SDL_GetWindowSize(window, width, height);
}
