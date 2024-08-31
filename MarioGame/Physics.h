#pragma once
#include <Box2D.h>
#include "Renderer.h"
#include "MyDebugDraw.h"
#include "FixtureData.h"
class CollisionListenerHelper
{
public:
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) = 0;
};
class Physics
{
public:
	~Physics();
	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& renderer);
	static b2World* world;
	static MyDebugDraw* debugDraw;
};

