#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Physics.h"
#include <Box2D.h>
#include "FixtureData.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "Animation.h"
class Mario : public CollisionListenerHelper
{
public:
	void Begin();
	void Update(float deltaTime);
	void RenderMario(Renderer& renderer);

	void OnBeginContact(b2Fixture* other) override;
	void OnEndContact(b2Fixture* other) override;

	sf::Vector2f position{};
	float angle{};
private:
	FixtureData fixtureData{};
	sf::Sound jumpSound;
	sf::Texture textureToDraw;
	Animation runAnimation;
	b2Body* body;
	size_t isOnGround = 0;	
	bool facingLeft = false;
	size_t coins;
};

