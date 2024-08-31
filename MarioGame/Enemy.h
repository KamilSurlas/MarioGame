#pragma once
#include "Object.h"
#include "Animation.h"
#include <Box2D.h>
#include "FixtureData.h"
#include "Resources.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "game.h"
class Enemy :
	public Object
{
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;
	void Die();
	~Enemy();
	bool GetIsDead();
private:
	float destroyTimer = 0.0f;
	bool isDead = false;
	Animation animation{};
	float movement = 5.0f;
	b2Body* body{};
	FixtureData* fixtureData;
};

