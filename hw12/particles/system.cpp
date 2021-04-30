#include "system.hpp"

void System::initialize(const unsigned int X, const unsigned int Y)
{
    for (int j = 0; j < Y; ++j) {
        for (auto i = 0U; i < X-1; ++i) {

            m_links.emplace_back(particle(j*X + i), particle((j*X + i + 1)), 0.5f);
        }
    }

    for (int j = 0; j < X; ++j) {
        for (auto i = 0U; i < Y-1; ++i) {

            m_links.emplace_back(particle(i*X + j), particle((i*X + j + 1)), 0.5f);
        }
    }

    for (int j = 0; j < Y-1; ++j) {
        for (int i = 0; i < X-1; ++i) {
            m_links.emplace_back(particle(j*X + i), particle((j + 1)*X + i + 1), 0.3f);
            m_links.emplace_back(particle((j + 1)*X + i), particle(j*X + i + 1), 0.3f);

        }
    }

    for (int j = 0; j < Y-2; ++j) {
        for (int i = 0; i < X-1; ++i) {
            m_links.emplace_back(particle(j*X + i), particle((j + 2)*X + i + 1), 0.3f);
            m_links.emplace_back(particle((j + 2)*X + i), particle(j*X + i + 1), 0.3f);

        }
    }

    for (int j = 0; j < Y-1; ++j) {
        for (int i = 0; i < X-2; ++i) {
            m_links.emplace_back(particle(j*X + i), particle((j + 1)*X + i + 2), 0.3f);
            m_links.emplace_back(particle((j + 1)*X + i), particle(j*X + i + 2), 0.3f);

        }
    }
}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void System::update() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(0.25f);

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

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}

}