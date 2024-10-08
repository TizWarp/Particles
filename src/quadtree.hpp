#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
class QuadTree{
  public:
    const int PARTICLE_MAX = 32;
    sf::Vector2f upper_bounds;
    sf::Vector2f lower_bounds;
    std::vector<int> owned_particles;
    std::vector<int> shared_particles;

    QuadTree(sf::Vector2f upper_bounds, sf::Vector2f lower_bounds);

    QuadTree(){};

    void resize(int width, int height);

    void clear();
    void regenerate();
    void physicsProcess(float dt);
    void render(sf::RenderWindow &window);
    bool isSubdivied();

  private:
    std::vector<QuadTree> children;
    sf::RectangleShape rect_shape;

};
