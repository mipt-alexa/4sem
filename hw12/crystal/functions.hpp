#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

template < typename T >
auto length(sf::Vector2 < T > vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

template < typename T >
auto norm(sf::Vector2 < T > vector)
{
	const auto l = length(vector);

	if (l == T(0))
	{
		return sf::Vector2 < T > (T(0), T(0));
	}
	else
	{
		return sf::Vector2 < T > (vector.x / l, vector.y / l);
	}
}

template < typename T >
auto operator^ (sf::Vector2 < T > lhs, sf::Vector2 < T > rhs)
{
	return lhs.x * rhs.y - rhs.x * lhs.y;
}