#include "renderer.hpp"
#include "application.hpp"
#include "camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "shader.hpp"
#include "simulation.hpp"
#include "texture.hpp"
#include <bits/types/wint_t.h>
#include <fmt/base.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>


namespace Renderer{
  static std::vector<float> particle_instance_data = {};

  static Camera camera = Camera(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), 70.0f);

  static unsigned int pVAO{0}, pVBO{0}, instanceVBO{0}; 

  static std::vector<Particle*> drawable_particles = {};

  static Shader* shader = nullptr;
  static Texture* texture = nullptr;

  const float particle_vertices[] = {
    -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, // top left
    0.25f, 0.25f, 0.0f, 1.0f, 1.0f, // top right
    0.25f, -0.25f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, // bottom left
  };

};

void Renderer::initRenderer(){

  glewExperimental = true;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK){
    spdlog::error("Failed to init glew");
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  shader = new Shader("./res/shaders/view_shader.vs", "./res/shaders/view_shader.fs");
  texture = new Texture("./res/textures/circle.png");

  glGenVertexArrays(1, &pVAO);
  glGenBuffers(1, &pVBO);
  glGenBuffers(1, &instanceVBO);

  glBindVertexArray(pVAO);
  glBindBuffer(GL_ARRAY_BUFFER, pVBO);

  // location zero is position
  glBufferData(GL_ARRAY_BUFFER, sizeof(particle_vertices), particle_vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // location 1 is texture coords;
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, particle_instance_data.size() * sizeof(float), &particle_instance_data[0], GL_STATIC_DRAW);

  // location 2 is instance position;
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(2);

  //location 3 is instance color;
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(3);

  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);

  glActiveTexture(GL_TEXTURE0);
  shader->use();
  shader->setInt("texture1", 0);

}

void Renderer::prepareFrame(){

  particle_instance_data.clear();

  for (int index = 0; index < drawable_particles.size(); index++){
    Particle *particle = drawable_particles[index];
    
    particle_instance_data.push_back(particle->position.x);
    particle_instance_data.push_back(particle->position.y);

    particle_instance_data.push_back(particle->color.r);
    particle_instance_data.push_back(particle->color.g);
    particle_instance_data.push_back(particle->color.b);
    
  }

  int height, width;
  Application::getWindowSize(&width, &height);
  glViewport(0, 0, width, height);

  shader->use();

  Mat4 projection = glm::perspective(camera.fov, (float)width / (float)height, 0.1f, 100.0f);
  shader->setMat4("projection", projection);

  shader->setMat4("view", camera.getView());

  glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, particle_instance_data.size() * sizeof(float), &particle_instance_data[0], GL_STATIC_DRAW);
}


void Renderer::pushParticle(Particle *particle){
  drawable_particles.push_back(particle);
}

void Renderer::drawFrame(){
  camera.update();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDrawArraysInstanced(GL_QUADS, 0, 4, drawable_particles.size());
  drawable_particles.clear();
}

Camera *Renderer::getCamera(){
  return &camera;
}
