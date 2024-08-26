#include "Mario.h"
const float movementSpeed = 180.0f;
void Mario::Update(float deltaTime)
{
	float move = movementSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		move *= 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		position.x += move * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		position.x -= move * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position.y -= move * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position.y += move * deltaTime;
	}
}

void Mario::RenderMario(Renderer& renderer)
{
	renderer.Draw(Resources::textures["mario.png"], position, sf::Vector2f(16.0f,32.0f));
}
