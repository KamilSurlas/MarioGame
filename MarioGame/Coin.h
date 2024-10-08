#pragma once
#include "Object.h"
#include "Animation.h"
#include "Resources.h"
#include <Box2D.h>
#include "FixtureData.h"
class Coin : public Object
{
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;
	~Coin();
private:
	Animation animation{};
	b2Body* body{};
	FixtureData* fixtureData;
};

