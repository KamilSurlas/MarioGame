#include "Map.h"


Map::Map(float cellSize)
	:cellSize(cellSize), grid()
{
}

void Map::Draw(Renderer& renderer)
{
	int x = 0;
	for (const auto& column : grid)
	{
		int y = 0;
		for (const auto& cell  : column)
		{
			if (cell)
			{
				renderer.Draw(*cell,
					sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f),
					sf::Vector2f(cellSize, cellSize));
			}
			y++;
		}
		x++;
	}
}

void Map::CreateBoard(size_t width, size_t height)
{
	grid = std::vector(width, std::vector(height, (sf::Texture*)nullptr));

	bool last = 0;

	for (auto& column : grid) 
	{
		for (auto& cell : column)
		{
			last !=last;
			if (last)
			{
				cell = &Resources::textures["brick.png"];
			}
		}
		if (width % 2 == 0)
		{
			last = !last;
		}
	}

	
}

sf::Vector2f Map::CreateFromImage(const sf::Image& image, std::vector<Object*>& objects)
{
	grid.clear();
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, (sf::Texture*)nullptr));

	sf::Vector2f marioPosition{};

	for (size_t x = 0; x < grid.size(); x++)
	{
		for (size_t y = 0; y < grid[x].size(); y++)
		{
			sf::Color color = image.getPixel(x, y);
			Object* object = nullptr;
			if (color == sf::Color::Red)
			{
				marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
				continue;
			}
			if (color == sf::Color::Black)
			{
				grid[x][y] = &Resources::textures["brick.png"];			
			}		
			if (color == sf::Color::Green)
			{
				grid[x][y] = &Resources::textures["rock.png"];
			}
			else if (color == sf::Color::Yellow)
			{
				object = new Coin();
				
			}
			if (object)
			{
				object->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
				objects.push_back(object);
			}
			else if (grid[x][y])
			{
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);

				b2Body* body = Physics::world.CreateBody(&bodyDef);

				b2PolygonShape shape{};

				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);
				FixtureData* fixtureData = new FixtureData();
				fixtureData->type = FixtureDataType::MapTile;
				fixtureData->mapX = x;
				fixtureData->mapY = y;
				b2FixtureDef fixtureDef{};
				fixtureDef.shape = &shape;
				fixtureDef.userData = fixtureData;
				fixtureDef.density = 0.0f;
				body->CreateFixture(&fixtureDef);
			}
		}
	}
	return marioPosition;
}
