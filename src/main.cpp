#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <time.h>

int main()
{

    static bool show_shape(true);

    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    srand(time(NULL));

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        if(ImGui::Button("Look at this pretty button"))
          shape.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255,255));
        if(ImGui::Button("UP"))
          shape.move(0,-10);
        if(ImGui::Button("LEFT"))
          shape.move(-10,0);
        ImGui::SameLine();
        if(ImGui::Button("RIGHT"))
          shape.move(10,0);
        if(ImGui::Button("DOWN"))
          shape.move(0,10);
        ImGui::Checkbox("Visible",&show_shape);
        ImGui::End();

        window.clear(sf::Color(0xCE, 0xCE, 0xCE));

        if(show_shape)
          window.draw(shape);
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}
