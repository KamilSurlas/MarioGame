#pragma once
#include "Renderer.h"
class Object
{
public:
	virtual void Begin() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(Renderer& renderer) = 0;
	sf::Vector2f position{};
	float angle{};
	std::string tag;
};

