#pragma once

#include "shader.hpp"
#include "simulation.hpp"
#include <string>
#include "camera.hpp"

namespace Renderer{


  Camera* getCamera();

  void initRenderer();

  void prepareFrame();
  void drawFrame();

  void pushParticle(Particle *particle);
};
