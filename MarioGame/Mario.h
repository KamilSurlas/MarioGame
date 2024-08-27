#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Physics.h"
#include <Box2D.h>
#define _USE_MATH_DEFINES
#include "math.h"
class Mario
{
public:
	void Begin();
	void Update(float deltaTime);
	void RenderMario(Renderer& renderer);
	sf::Vector2f position{};
	float angle{};
private:
	b2Body* body;
};

