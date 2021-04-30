#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(800U, 600U), "PHYSICS");

	sf::Vector2f min_point(  0.0f,   0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

    const auto N_x = 6U;

    const auto N_y = 6U;

	const auto C = (min_point + max_point) * 0.5f;

	const auto r = 2.5f;

	const auto start_dist = 20.0f;

	std::vector < System::particle_t > particles;

	for (int i = 0; i < N_x*N_y; ++i)
	{
        auto position = sf::Vector2f(start_dist * static_cast< float > (i % N_x) ,
                                     start_dist * static_cast< float > (i / N_y)) + C;

		particles.push_back(std::make_shared < Particle > (position, position,
			sf::Vector2f(0.0f, 10.0f), r));
	}

	System system(min_point, max_point, particles, N_x, N_y);

	sf::Event event{};

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		system.update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			system.push(sf::Vector2f(0.0f, -2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			system.push(sf::Vector2f(0.0f, 2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			system.push(sf::Vector2f(-2.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			system.push(sf::Vector2f(2.0f, 0.0f));
		}

		window.clear();
		
		for (auto i = 0U; i < system.particles().size(); ++i)
		{
			sf::CircleShape circle(2.0f * r);

			circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));

			circle.setFillColor(sf::Color::Red);

			window.draw(circle);
		}
	
		window.display();
	}
	

	return EXIT_SUCCESS;
}
