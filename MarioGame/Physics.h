#pragma once
#include <Box2D.h>
#include "Renderer.h"
#include "MyDebugDraw.h"
#include "CollisionListener.h"

class Physics
{
public:
	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& renderer);
	static b2World world;
	static MyDebugDraw* debugDraw;
};

