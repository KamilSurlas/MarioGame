#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Map.h"
#include <filesystem>
#include "Camera.h"
#include "Mario.h"
#include "Physics.h"
extern Camera camera;

void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
