#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
class QuadTree{
  public:
    const int PARTICLE_MAX = 8;
    sf::Vector2f upper_bounds;
    sf::Vector2f lower_bounds;
    std::vector<int> particle_indexs;

    QuadTree(sf::Vector2f upper_bounds, sf::Vector2f lower_bounds);

    QuadTree(){};

    void regenerate();
    void physicsProcess(float dt);
    void render(sf::RenderWindow &window);

    ~QuadTree();

  private:
    std::vector<QuadTree> children;
    sf::RectangleShape rect_shape;

};
