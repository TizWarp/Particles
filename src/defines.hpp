#pragma once



#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include <string>
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;
typedef glm::mat4 Mat4;
typedef std::string string;

class Color{
  public:
    float r, g, b, a;

    Color(float r, float g, float b){
      this->r = r;
      this->g = g;
      this->b = b;
      a = 1.0f;
    }
    Color(float r, float g, float b, float a){
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
    }
    Color(){};
};
