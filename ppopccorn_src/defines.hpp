#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <stdint.h>

#define PI 3.14159
#define RAD_TO_DEG 180.0f/PI
#define DEG_TO_RAD PI/180.0f

typedef sf::Vector2f Vector2;
typedef uint8_t ParticleType;
typedef sf::RenderWindow Window;

class Colorf{
  public:
    float r, g, b, a;

    Colorf(float r, float g, float b){
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = 1.0f;
    }
    Colorf(float r, float g, float b, float a){
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
    }

    float *data(){
      return &r;
    }

    sf::Color toIntColor(){
      return sf::Color((int)255.0f * r, (int)255.0f * g, (int)255.0f * b, (int)255.0f * a);
    }
};

struct Bounds {
  Vector2 upper;
  Vector2 lower;
};
