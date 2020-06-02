#include "Program.hpp"

#include <array>
#include <fstream>

static void normalizeCities(Program& program)
{
	// THE UGLIEST CODE I'VE SEEN, command line options, or even a config file would have been much
	// better than this monstrosity
#ifdef BACKGROUND
	const auto start_x_offset = program.window().getSize().x * 0.14545f;	// Ooh magic numbers
	const auto start_y_offset = program.window().getSize().y * 0.15117f;	// Ooh magic numbers
	const auto end_x_offset = program.window().getSize().x * 0.78182f;
	const auto end_y_offset = program.window().getSize().y * 0.77442f;
#else
	const auto start_x_offset = program.window().getSize().x * 0.02f;
	const auto start_y_offset = program.window().getSize().y * 0.02f;
	const auto end_x_offset = program.window().getSize().x * 0.81f;
	const auto end_y_offset = program.window().getSize().y * 0.82f;
#endif

	const auto city_x_range = program.bottomRight().x - program.topLeft().x;
	const auto city_y_range = program.bottomRight().y - program.topLeft().y;

#ifdef BACKGROUND
	const float x_scale = (end_x_offset - start_x_offset) / (city_x_range);
	const float y_scale = (end_y_offset - start_y_offset) / (city_y_range);
#else
	const float x_scale = (end_x_offset - start_x_offset) / (city_x_range) + .027f;
	const float y_scale = (end_y_offset - start_y_offset) / (city_y_range) + .025f;
#endif

	// I'm sorry for all the stupid calculations, just in case I change the window size in the
	// future, I don't want to mess the calculations.
	// These just determine where the city drawing
	// should start, hopefully inside the US map I chose

	std::for_each(program.cities().begin(), program.cities().end(), [&](auto&& city) {
		city.normalize(x_scale, y_scale, start_x_offset, start_y_offset);
	});
}

void Program::handleBackground()
{
	// Initialize the background image for drawing
	m_background_texture.loadFromFile("../img/US-B&W.png");
	m_background_sprite.setTexture(m_background_texture);
	m_background_sprite.setScale(m_window.getSize().x / 512.f + 0.62f,
								 m_window.getSize().y / 341.f + 0.6f);
	m_background_sprite.move(-138.f, -81.f);
	m_background_sprite.setColor(sf::Color(48U, 48U, 48U));
}

const sf::ContextSettings settings(0, 0, 6U);

Program::Program(const char* filename, const uint16_t win_width, const uint16_t win_height) :
	m_window(sf::VideoMode(win_width, win_height),
			 "Travelling Salesman",
			 sf::Style::Close | sf::Style::Titlebar,
			 settings),
	m_background_color(sf::Color::Black),
	m_vertex_array(sf::LineStrip),
	m_vertex_array_2(sf::LineStrip)
{
	m_window.setVerticalSyncEnabled(false);
	m_window.setActive(true);
	m_window.setPosition({960 - win_width / 2, 540 - win_height / 2});

#ifdef BACKGROUND
	handleBackground();
#endif

	// Reserve some space in the vector, even though the max data is 48 Cities
	m_cities.reserve(48U);

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
		uint16_t x = 1337U, y = 4269U;
		city_file >> x >> y;
		if(city_file.eof())
			break;
		m_cities.emplace_back(x, y, index++);

		// Find the top-left most and bottom-right most(?) points as reference of the scale for the
		// SFML graph
		m_top_left.x = std::min(m_top_left.x, x);
		m_top_left.y = std::min(m_top_left.y, y);

		m_bottom_right.x = std::max(m_bottom_right.x, x);
		m_bottom_right.y = std::max(m_bottom_right.y, y);
	}

	normalizeCities(*this);

	// Prepare the VertexArray for drawing
	m_vertex_array.resize(m_cities.size() + 1ULL);
	m_vertex_array_2.resize(m_cities.size() + 1ULL);
}

Program::~Program() { m_window.close(); }

void Program::setBackground(const sf::Color color) { m_background_color = color; }

bool Program::run()
{
	sf::Event event;
	while(m_window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed: return false;
			case sf::Event::KeyPressed:
			{
				switch(event.key.code)
				{
					case sf::Keyboard::Escape: [[fallthrough]];
					case sf::Keyboard::Q: return false;
					default: break;
				}
			}
			default: break;
		}
	}

#ifdef BACKGROUND
	m_window.draw(m_background_sprite);
#else
	m_window.clear(m_background_color);
#endif

	m_window.draw(m_vertex_array);
	m_window.draw(m_vertex_array_2);

	for(const auto& city: m_cities)
	{
		m_window.draw(city);
	}

	m_window.display();
	return true;
}
