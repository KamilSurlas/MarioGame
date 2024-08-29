#pragma once
#include "Box2D.h"
#include "Physics.h"
#include "FixtureData.h"
class CollisionListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};

