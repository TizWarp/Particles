#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>

void addParticle(float radius, sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f), uint8_t id = 0);

void physicsUpdate(float dt, sf::RenderWindow &window);

void renderPass(sf::RenderWindow &window);

void setBounds(int width, int height);

void selectBall(sf::Vector2f pos);
void unselectBall();

int getParticleCount();

void toggleGravity();

void toggleQuadTree();

void changeQuadCapacity(int change);

int getQuadCapacity();

void removeParticle();

void clearParticles();

void setInteractions(bool set);

bool getInteractionsState();

void changeSubstepCount(int change);

int getSubstepCount();

void setReactions(bool set);

