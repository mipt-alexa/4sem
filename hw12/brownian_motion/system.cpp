#include <chrono>
#include <thread>
#include <iostream>

#include "system.h"


void System::initialize() {

    m_colors.assign({
                            //sf::Color(66, 30, 15),
                            //sf::Color(25, 7, 26),
                            //sf::Color(9, 1, 47),
                            sf::Color(4, 4, 73),
                            sf::Color(0, 7, 100),
                            sf::Color(12, 44, 138),
                            sf::Color(24, 82, 177),
                            sf::Color(57, 125, 209),
                            sf::Color(134, 181, 229),
                            sf::Color(211, 236, 248),
                            sf::Color(241, 233, 191),
                            sf::Color(248, 201, 95),
                            sf::Color(255, 170, 0),
                            sf::Color(204, 128, 0),
                            sf::Color(153, 87, 0),
                            sf::Color(106, 52, 3) });

}

void System::check_borders() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
		}
	}


}


void System::count_particles() {

    clear_cells();

    int x, y;

    for (const auto& i : m_particles) {

        x = static_cast< int > (i->position().x) / m_cell_size;
        y = static_cast< int > (i->position().y) / m_cell_size;

        m_cells[y][x]++;
    }

}


void System::draw_cells() {

    const unsigned int average_num = m_particles.size() * m_cell_size * m_cell_size / m_max_point.x / m_max_point.y;

    for (int i = 0; i < m_cells.size(); ++i) {
        for (int j = 0; j < m_cells[0].size(); ++j) {

            sf::RectangleShape rect(sf::Vector2f(m_cell_size, m_cell_size));

            unsigned int color;

            if (m_cells[i][j] > 5*average_num){
                color = 255;
            }else{
                color = m_cells[i][j] * 255 / 5 / average_num;
            }

            rect.setFillColor(sf::Color(0, 0, color));
            rect.setPosition(j*m_cell_size, i*m_cell_size);

            m_window.draw(rect);

        }
    }
}


void System::run() {

    sf::Event event{};

    std::normal_distribution< float > dis (0, 10);


    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        m_window.clear();

        check_borders();

        count_particles();

        draw_cells();

        for (auto i = 0U; i < m_particles.size(); ++i) {

            particle(i)->move(dis(m_gen), dis(m_gen));

            sf::CircleShape circle(m_r);

            circle.setPosition(particle(i)->position() + sf::Vector2f(m_r, m_r));
            circle.setFillColor(sf::Color::White);

            m_window.draw(circle);
        }

        m_window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }


}
