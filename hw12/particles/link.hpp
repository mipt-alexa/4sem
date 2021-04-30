#pragma once

#include <cmath>
#include <memory>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "particle.hpp"

class Link
{
public:

	using particle_t = std::shared_ptr < Particle > ;

public:

	Link() noexcept = default;

	explicit Link(particle_t particle_1, particle_t particle_2, float stiffness) noexcept :
		m_particle_1(std::move(particle_1)), m_particle_2(std::move(particle_2)), m_stiffness(stiffness),
		m_distance(length(m_particle_1->position() - m_particle_2->position()))
	{}

	~Link() noexcept = default;

public:

	void update() const;

private:

	particle_t m_particle_1;
	particle_t m_particle_2;

	float m_stiffness;
	float m_distance;
};