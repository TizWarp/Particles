#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Thread.hpp"
#include "SFML/System/Time.hpp"
#include "imgui.h"
#include "simulation.hpp" 
#include "threads.hpp"

class Application{
  public:
    sf::RenderWindow window;
    sf::VertexArray particles_va;
    ThreadPool *thread_pool;
    sf::View view;
    sf::Texture particle_texture;
    sf::RenderStates states;
    sf::Clock delta_clock;
    i32 particle_spawn_amount = 20;
    i32 fps;
    Simulation simulation;
    bool is_running = true;
    sf::RectangleShape mouse_shape;
    i32 mouse_selected_type;
    ImGuiIO io;

    Application(ThreadPool *thread_pool);

    void fillMouseBrush();
    void renderUi();
    void updateParticlesVA();
    void pollEvents();
    void run();
};
