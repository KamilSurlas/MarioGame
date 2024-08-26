#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Resources.h"
class Mario
{
public:
	void Update(float deltaTime);
	void RenderMario(Renderer& renderer);
	sf::Vector2f position{};
	float angle{};
};

