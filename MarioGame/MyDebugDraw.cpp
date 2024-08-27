#include "MyDebugDraw.h"


MyDebugDraw::MyDebugDraw(sf::RenderTarget& target)
	:target(target)
{
}

void MyDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape shape(vertexCount);
	for (size_t i = 0; i < vertexCount; i++)
	{
		shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
	}

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(0.02f);
	shape.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	target.draw(shape);
}

void MyDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape shape(vertexCount);
	for (size_t i = 0; i < vertexCount; i++)
	{
		shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
	}

	shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	target.draw(shape);
}

void MyDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x, center.y);
	circle.setOrigin(radius / 2.0f, radius / 2.0f);
	circle.setOutlineThickness(0.02f);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	target.draw(circle);
}

void MyDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x, center.y);
	circle.setOrigin(radius / 2.0f, radius / 2.0f);;
	circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 80));
	target.draw(circle);

	b2Vec2 p = center + (radius * axis);
	DrawSegment(center, p, color);
}

void MyDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::VertexArray va(sf::Lines, 2);
	sf::Color sfColor = sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
	va[0].position = sf::Vector2f(p1.x, p1.y);
	va[0].color = sfColor;

	va[1].position = sf::Vector2f(p2.x, p2.y);
	va[1].color = sfColor;

	target.draw(va);
}

void MyDebugDraw::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p = xf.p;
	b2Vec2 px = p + (0.5f * xf.q.GetXAxis());
	b2Vec2 py = p + (0.5f * xf.q.GetYAxis());

	DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
	DrawSegment(p, py, b2Color(0.0f, 1.0f, 0.0f));
}

void MyDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	sf::CircleShape circle(size);
	circle.setPosition(p.x, p.y);
	circle.setOrigin(size / 2.0f, size / 2.0f);
	circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	target.draw(circle);
}
