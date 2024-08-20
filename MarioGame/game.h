#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
