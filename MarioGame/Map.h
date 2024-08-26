#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Renderer.h"
#include "Resources.h"
class Map
{
public:
	Map(float cellSize = 32.0f);
	void Draw(Renderer& renderer);
	void CreateBoard(size_t width, size_t height);
	sf::Vector2f CreateFromImage(const sf::Image& image);

	std::vector<std::vector<int>> grid;
	float cellSize;
};

