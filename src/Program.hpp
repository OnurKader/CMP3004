#pragma once

#include "City.hpp"

#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <vector>

class Program final
{
	public:
	Program(const char* filename_of_city_data = "../data/cities.txt",
			uint16_t win_width = 1280U,
			uint16_t win_height = 900U);
	~Program();

	void setBackground(const sf::Color);
	void run();

	sf::RenderWindow& window() { return m_window; }
	const sf::RenderWindow& window() const { return m_window; }

	std::vector<City>& cities() { return m_cities; }
	const std::vector<City>& cities() const { return m_cities; }

	private:
	sf::RenderWindow m_window;
	sf::Color m_background_color;
	sf::Texture m_background_texture;
	sf::Sprite m_background_sprite;

	std::vector<City> m_cities;

	sf::Vector2<uint16_t> m_top_left {65535U, 65535U};
	sf::Vector2<uint16_t> m_bottom_right {0U, 0U};
};
