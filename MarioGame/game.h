#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Map.h"
#include <filesystem>
#include "Camera.h"
#include "Mario.h"
#include "Physics.h"
#include <SFML/Audio.hpp>
extern Camera camera;
extern bool paused;
void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
void RenderUi(Renderer& renderer);
void DeleteObject(Object* obj);
void LoadResources();
void PrepareGame();