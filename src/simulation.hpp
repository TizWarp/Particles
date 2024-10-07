#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

void addParticle(sf::Color color, float radius, sf::Vector2f position, sf::Vector2f velocity);

void physicsUpdate(float dt, sf::RenderWindow &window);

void renderPass(sf::RenderWindow &window);

void setBounds(int width, int height);

void selectBall(sf::Vector2f pos);
void unselectBall();

int getParticleCount();

void toggleGravity();

void toggleQuadTree();
