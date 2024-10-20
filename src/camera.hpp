#pragma once

#include "defines.hpp"

class Camera{
  public:
    Vec3 position;
    Vec3 target;
    Vec3 up;
    Vec3 right;
    Vec3 front;
    float fov;


    Camera(){};
    Camera(Vec3 position, Vec3 target, float fov);

    void update();

    Mat4 getView();
};
