#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

struct City final : sf::Drawable
{
	City(uint16_t _x, uint16_t _y, uint8_t _index = 0U);

	bool operator<=>(const City&) const = default;

	float dist(const City&) const;
	static float dist(const City&, const City&);

	float distSqr(const City&) const;
	static float distSqr(const City&, const City&);

	void normalize(const float scale_x,
				   const float scale_y,
				   const float x_offset,
				   const float y_offset)
	{
		m_window_position = {x * scale_x + x_offset, y * scale_y + y_offset};
	}

	sf::Vector2f& windowPosition() { return m_window_position; }
	const sf::Vector2f& windowPosition() const { return m_window_position; }

	const sf::Vector2<uint16_t> position;
	const uint16_t& x = position.x;
	const uint16_t& y = position.y;
	uint8_t index;
	uint8_t radius{5U};
	sf::Color color{sf::Color::Green};

	private:
	sf::Vector2f m_window_position;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};
