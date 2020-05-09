#include "Program.hpp"

#include <fstream>

Program::Program(const char* filename, uint16_t win_width, uint16_t win_height) :
	m_window(sf::VideoMode(win_width, win_height),
			 "Travelling Salesman",
			 sf::Style::Close | sf::Style::Titlebar),
	m_background_color(sf::Color::Black)
{
	// Reserve some space in the vector, even though the max data is 48 Cities
	m_cities.reserve(8U);

	// Read the given file and extract cities with the coordinates
	std::ifstream city_file(filename);
	if(!city_file)
	{
		fmt::print(stderr, "File {} could not be opened\n", filename);
		return;
	}

	// ???: Should I get the line number from like tellg or tellp? Nah

	uint8_t index = 0U;
	while(city_file.good())
	{
		uint16_t x, y;
		city_file >> x >> y;
		m_cities.emplace_back(x, y, index++);
	}
	// Erase the last element because >> reads the last city twice
	m_cities.pop_back();

	fmt::print("File {} parsed successfully with {} cities\n", filename, m_cities.size());
}

Program::~Program() { m_window.close(); }

void Program::setBackground(const sf::Color color) { m_background_color = color; }
