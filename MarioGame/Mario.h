#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Physics.h"
#include <Box2D.h>
#include "CollisionListenerHelper.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "Animation.h"
class Mario : public CollisionListenerHelper
{
public:
	void Begin();
	void Update(float deltaTime);
	void RenderMario(Renderer& renderer);

	void OnBeginContact() override;
	void OnEndContact() override;

	sf::Vector2f position{};
	float angle{};
private:
	sf::Texture textureToDraw;
	Animation runAnimation;
	b2Body* body;
	size_t isOnGround = 0;	
	bool facingLeft = false;
};

