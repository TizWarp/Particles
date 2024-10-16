#pragma once

#include "SFML/Graphics/Color.hpp"
#include "imgui.h"
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>

typedef sf::Vector2f Vec2;

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;

typedef float f32;
typedef double f64;

#define RADIUS 5.0f
#define RADI RADIUS*2

class Color{
  public:
  f32 r, g, b, a;

  Color(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
  Color(u8 r, u8 g, u8 b, u8 a){
    this->r = (f32)r/255.0f;
    this->g = (f32)g/255.0f;
    this->b = (f32)b/255.0f;
    this->a = (f32)a/255.0f;
  }

  Color(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1.0f;
  }
  Color(u8 r, u8 g, u8 b){
    this->r = (f32)r/255.0f;
    this->g = (f32)g/255.0f;
    this->b = (f32)b/255.0f;
    this->a = 1.0;
  }

  float *data(){
    return &r;
  }

  operator sf::Color() const {
    return sf::Color((u8)255.0f*r, (u8)255.0f*g, (u8)255.0f*b, (u8)255.0f*a);
  }

};
