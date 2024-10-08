#include "Camera.h"

Camera::Camera(float zoomLevel)
{
	this->zoomLevel = zoomLevel;
}

sf::View Camera::GetView(sf::Vector2u windowSize)
{
	float aspect = (float)windowSize.x / (float)windowSize.y;
	
	if (aspect < 1.0f)
	{
		viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	}
	else
	{
		viewSize = sf::Vector2f(zoomLevel*aspect,zoomLevel);
	}

	return sf::View(position, viewSize);
}

sf::View Camera::GetUiView()
{
	float aspect = viewSize.x / viewSize.y;
	viewSize = sf::Vector2f(100.0f, 100.f / aspect);
	return sf::View(sf::Vector2f(), viewSize);
}

sf::Vector2f Camera::GetViewSize()
{
	return viewSize;
}
