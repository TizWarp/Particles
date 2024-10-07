#include "quadtree.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <complex>
#include <cstdio>
#include <type_traits>

QuadTree::QuadTree(sf::Vector2f upper_bounds, sf::Vector2f lower_bounds){
  this->upper_bounds = upper_bounds;
  this->lower_bounds = lower_bounds;
  rect_shape = sf::RectangleShape(upper_bounds - lower_bounds);
  /*printf("%f %f\n", (upper_bounds-lower_bounds).x, (upper_bounds-lower_bounds).y);*/
  rect_shape.setPosition(lower_bounds);
  rect_shape.setFillColor(sf::Color::Transparent);
  rect_shape.setOutlineThickness(5.0f);
  rect_shape.setOutlineColor(sf::Color::White);
}

void QuadTree::render(sf::RenderWindow &window){
  window.draw(rect_shape);
  for(QuadTree tree : children){
    tree.render(window);
  }
}