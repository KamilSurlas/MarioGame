#include <SFML/Graphics.hpp>
#include "game.h"
#include "Camera.h"
#include "Renderer.h"


int main(void) {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario");
    sf::Clock deltaClock;
    Renderer renderer(window);


    window.setFramerateLimit(60);

    Begin(window);
    while (window.isOpen()) 
    {
        float deltaTime = deltaClock.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && 
                event.key.code == sf::Keyboard::Escape)
                paused = !paused;
        }

        window.setView(camera.GetView(window.getSize()));
        Update(deltaTime);

        window.clear();

        Render(renderer);
        window.setView(camera.GetUiView());
        RenderUi(renderer);

        window.display();
    }

    return 0;
}

