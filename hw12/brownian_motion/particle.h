#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:

    Particle() noexcept = default;

    explicit Particle(sf::Vector2f position, float radius) noexcept :
            m_position(position), m_radius(radius)
    {}

    ~Particle() noexcept = default;

public:

    const auto position() const noexcept
    {
        return m_position;
    }

    const auto radius() const noexcept
    {
        return m_radius;
    }

public:

    void set_x(float x) noexcept
    {
        m_position.x = x;
    }

    void set_y(float y) noexcept
    {
        m_position.y = y;
    }

public:

    void move(float x, float y);

private:

    sf::Vector2f m_position;

    float m_radius;
};