#pragma once
class CollisionListenerHelper
{
public:
	virtual void OnBeginContact() = 0;
	virtual void OnEndContact() = 0;
};

