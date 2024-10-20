#include "camera.hpp"
#include <glm/geometric.hpp>
#include <glm/ext.hpp>

Camera::Camera(Vec3 position, Vec3 target, float fov){
  this->position = position;
  this->target = target;
  this->fov = fov;

  update();
}

void Camera::update(){
  front = glm::normalize(position - target);
  right = glm::cross(Vec3(0.0f, 1.0f, 0.0f), front);
  up = glm::cross(right, front);
}

Mat4 Camera::getView(){
  return glm::lookAt(position, target, up);
}
