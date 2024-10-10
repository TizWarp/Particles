#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "defines.hpp"
#include "particle.hpp"
class QuadTree{
  public:
    bool is_root;
    Bounds bounds;
    std::vector<int> quad_particles;

    QuadTree(Bounds bounds, bool is_root = false);

    QuadTree(){};

    void resize(Bounds new_bounds);

    void clear();
    void generate(int particle_max);
    void physicsProcess(float dt);
    void render(Window &window);

  private:
    std::vector<QuadTree> children;
    sf::RectangleShape rect_shape;

};
