#include "City.hpp"

#include <cmath>

City::City(uint16_t _x, uint16_t _y, uint8_t _index) : position(_x, _y), index(_index) {}

float City::dist(const City& other) const
{
	const float _x = static_cast<float>(position.x - other.position.x);
	const float _y = static_cast<float>(position.y - other.position.y);
	return std::sqrt(_x * _x + _y * _y);
}

float City::dist(const City& first, const City& second)
{
	const float _x = static_cast<float>(first.position.x - second.position.x);
	const float _y = static_cast<float>(first.position.y - second.position.y);
	return std::sqrt(_x * _x + _y * _y);
}

float City::distSqr(const City& other) const
{
	const float _x = static_cast<float>(position.x - other.position.x);
	const float _y = static_cast<float>(position.y - other.position.y);
	return (_x * _x + _y * _y);
}

float City::distSqr(const City& first, const City& second)
{
	const float _x = static_cast<float>(first.position.x - second.position.x);
	const float _y = static_cast<float>(first.position.y - second.position.y);
	return (_x * _x + _y * _y);
}

void City::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPointCount(9U);
	circle.setPosition(m_window_position);
	circle.move(-radius, -radius);

	target.draw(circle, states);
}
