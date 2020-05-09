#pragma once

#include "City.hpp"

#include <SFML/Graphics.hpp>
#include <array>
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

	private:
	sf::RenderWindow m_window;
	sf::Color m_background_color;
	std::vector<City> m_cities;
};
