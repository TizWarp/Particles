#include "particle.hpp"
#include "simulation.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdio>

static sf::Vector2f mouse_pos = sf::Vector2f(0.0f, 0.0f);



int main() {

  sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600),
                                             "ParticleSim", sf::Style::Resize);

  sf::Clock deltaClock;

  int spawn_timer = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::Resized) {
        sf::View view(
            sf::Vector2f((float)event.size.width / 2,
                         (float)event.size.height / 2),
            sf::Vector2f((float)event.size.width, (float)event.size.height));
        window.setView(view);
        setBounds((int)event.size.width, (int)event.size.height);
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Right) {
          addParticle(sf::Color::Red, 10.0f,
                      sf::Vector2f((float)event.mouseButton.x,
                                   (float)event.mouseButton.y),
                      sf::Vector2f(0.0f, 0.0f));
        }
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
          selectBall(sf::Vector2f((float)event.mouseButton.x,
                                  (float)event.mouseButton.y));
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
          unselectBall();
        }
      }
      if (event.type == sf::Event::MouseMoved) {
        mouse_pos.x = (float)event.mouseMove.x;
        mouse_pos.y = (float)event.mouseMove.y;
      }
      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Key::G){
          toggleGravity();
        }
        if (event.key.code == sf::Keyboard::Key::Q){
          toggleQuadTree();
        }
      }
    }

    float deltaTime = deltaClock.restart().asSeconds();

    /*printf("%d, %d\n", window.getSize().x, window.getSize().y);*/

    window.clear(sf::Color::Black);

    physicsUpdate(deltaTime, window);

    renderPass(window);

    window.display();


    spawn_timer = (spawn_timer += 1) % 1;

    if (getParticleCount() < 700 && spawn_timer == 0) {



      addParticle(sf::Color::Red, 10.0f, sf::Vector2f(200.0f, 50.0f),
                  sf::Vector2f(100.0f, 0.0f));
    }
  }

  return 0;
}

sf::Vector2f getMousePos() { return mouse_pos; }
