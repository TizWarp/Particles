#include "particle.hpp"
#include "simulation.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
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
#include <exception>
#include <fstream>
#include <string>

static sf::Vector2f mouse_pos = sf::Vector2f(0.0f, 0.0f);

const float RADIUS = 5.0f;

int main() {

  sf::Font font;
  font.loadFromFile("./res/Symbola.otf");

  sf::Text fps_counter;
  fps_counter.setFont(font);
  fps_counter.move(sf::Vector2f(2.0f, 0.0f));

  sf::Text particle_count;
  particle_count.setFont(font);
  particle_count.move(sf::Vector2f(2.0f, 50.0f));

  sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600),
                                             "ParticleSim", sf::Style::Resize);

  /*window.setVerticalSyncEnabled(true);*/
  sf::Clock deltaClock;

  int spawn_timer = 0;
  bool red = false;

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
          addParticle(sf::Color::Red, RADIUS,
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
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Key::G) {
          toggleGravity();
        }
        if (event.key.code == sf::Keyboard::Key::Q) {
          toggleQuadTree();
        }
      }
    }

    float deltaTime = deltaClock.restart().asSeconds();

    /*printf("%d, %d\n", window.getSize().x, window.getSize().y);*/

    window.clear(sf::Color::Black);

    physicsUpdate(deltaTime, window);

    renderPass(window);

    int fps = int(1.0f / deltaTime);

    std::string fpsString = std::to_string(fps);
    fps_counter.setString(fpsString);
    window.draw(fps_counter);

    std::string particleCountString = std::to_string(getParticleCount());
    particle_count.setString(particleCountString);
    window.draw(particle_count);

    window.display();

    spawn_timer = (spawn_timer += 1) % 1;
    if (fps >= 60 && spawn_timer == 0) {
        addParticle(sf::Color::Red, RADIUS, sf::Vector2f(200.0f, 50.0f),
                    sf::Vector2f(100.0f, 0.0f));
    }
  }

  return 0;
}

sf::Vector2f getMousePos() { return mouse_pos; }
