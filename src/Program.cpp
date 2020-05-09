#include "Program.hpp"

#include <fstream>

static void normalizeCities(Program& program)
{
	[[maybe_unused]] const auto x_offset =
		program.window().getSize().x * 0.14545f;	// Ooh magic numbers
	[[maybe_unused]] const auto y_offset =
		program.window().getSize().y * 0.15117f;	// Ooh magic numbers

	const float x_scale = 1;
	const float y_scale = 2;

	std::for_each(program.cities().begin(),
				  program.cities().end(),
				  [&x_scale, &y_scale](auto&& city) { city.normalize(x_scale, y_scale); });
}

Program::Program(const char* filename, uint16_t win_width, uint16_t win_height) :
	m_window(sf::VideoMode(win_width, win_height),
			 "Travelling Salesman",
			 sf::Style::Close | sf::Style::Titlebar),
	m_background_color(sf::Color::Black)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setActive(true);
	m_window.setPosition({960 - win_width / 2, 540 - win_height / 2});

	// Initialize the background image for drawing
	m_background_texture.loadFromFile("../img/US-B&W.png");
	m_background_sprite.setTexture(m_background_texture);
	m_background_sprite.setScale(win_width / 512.f, win_height / 341.f);

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

		// Find the top-left most and bottom-right most(?) points as reference of the scale for the
		// SFML graph
		m_top_left.x = std::min(m_top_left.x, x);
		m_top_left.y = std::min(m_top_left.y, y);

		m_bottom_right.x = std::max(m_bottom_right.x, x);
		m_bottom_right.y = std::max(m_bottom_right.y, y);
	}
	// Erase the last element because >> reads the last city twice
	m_cities.pop_back();

	fmt::print("Top-Left: ({}, {})\nBottom-Right: ({}, {})\n",
			   m_top_left.x,
			   m_top_left.y,
			   m_bottom_right.x,
			   m_bottom_right.y);

	// TODO: Deal with the scale later, maybe don't make City drawable
	// I think I'll do a function call to something like normalizeCities or which will
	// update the positions of every City
	normalizeCities(*this);

	//	fmt::print("File {} parsed successfully with {} cities\n", filename, m_cities.size());
}

Program::~Program() { m_window.close(); }

void Program::setBackground(const sf::Color color) { m_background_color = color; }

void Program::run()
{
	while(m_window.isOpen())
	{
		//		m_window.clear(m_background_color);

		sf::Event event;
		while(m_window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed: return;
				case sf::Event::KeyPressed:
				{
					switch(event.key.code)
					{
						case sf::Keyboard::Escape: [[fallthrough]];
						case sf::Keyboard::Q: return;
						default: break;
					}
				}
				default: break;
			}
		}
		m_window.draw(m_background_sprite);

		m_window.display();
	}
}
