#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

struct City final : sf::Drawable
{
	City(uint16_t _x = 0U, uint16_t _y = 0U, uint8_t _index = 0U);

	bool operator<=>(const City &) const = default;

	float dist(const City &) const;
	static float dist(const City &, const City &);

	float distSqr(const City &) const;
	static float distSqr(const City &, const City &);

	void normalize(const float scale_x, const float scale_y)
	{
		m_window_position = {x * scale_x, y * scale_y};
	}

	sf::Vector2<uint16_t> position;
	uint16_t &x = position.x;
	uint16_t &y = position.y;
	uint8_t index;
	uint8_t radius {32U};
	sf::Color color {sf::Color::Green};

	private:
	sf::Vector2f m_window_position;
	void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
