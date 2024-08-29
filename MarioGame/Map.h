#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Renderer.h"
#include "Resources.h"
#include <Box2D.h>
#include "Physics.h"
#include "Object.h"
#include "Coin.h"
#include "FixtureData.h"

class Map
{
public:
	Map(float cellSize = 32.0f);
	void Draw(Renderer& renderer);
	void CreateBoard(size_t width, size_t height);
	sf::Vector2f CreateFromImage(const sf::Image& image, std::vector<Object*>& objects);

	std::vector<std::vector<int>> grid;
	float cellSize;
};

