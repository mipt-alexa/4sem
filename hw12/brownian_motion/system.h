#pragma once

#include <cmath>
#include <memory>
#include <random>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "particle.h"

class System
{
public:

    using particle_t = std::shared_ptr < Particle > ;

public:

    explicit System(sf::Vector2f min_point, sf::Vector2f max_point,
                    std::vector < particle_t > & particles,
                    std::vector< std::vector< unsigned int >> & cells,
                    const unsigned int r,  const unsigned int cell_size,
                    std::mt19937& gen
                    ) noexcept :

            m_min_point(min_point), m_max_point(max_point),
            m_particles(particles), m_cells(std::move(cells)),
            m_window(sf::VideoMode(max_point.x, max_point.y), "moving", sf::Style::Close),
            m_r(r), m_gen(gen), m_cell_size(cell_size)

    {
        initialize();
    }

    ~System() noexcept = default;

private:

    void initialize();

    void check_borders() const;

    void count_particles();

    void draw_cells();

    void clear_cells() {
        for (auto & m_cell : m_cells) {
            std::fill(m_cell.begin(), m_cell.end(), 0);
        }
    }

public:

    particle_t particle(std::size_t index) const
    {
        return m_particles.at(index);
    }

    const auto & particles() const noexcept
    {
        return m_particles;
    }

public:

    void run();

private:

    std::mt19937 m_gen;

    sf::RenderWindow m_window;

    const int m_cell_size;

    sf::Vector2f m_min_point;
    sf::Vector2f m_max_point;

    std::vector < particle_t > m_particles;

    const int m_r;

    std::vector < std::vector < unsigned int > > m_cells;

    std::vector < sf::Color > m_colors;

};