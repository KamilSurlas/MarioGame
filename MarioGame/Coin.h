#pragma once
#include "Object.h"
#include "Animation.h"
#include "Resources.h"
#include <Box2D.h>
class Coin : public Object
{
public:
	~Coin();
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;
private:
	Animation animation;
	b2Body* body;
};

