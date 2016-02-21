#pragma once

#include "SFML/Graphics.hpp"

// gotta give this stuff some namespace
namespace vec {

template <typename T>
T length(sf::Vector2<T> vec) {
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

template <typename T>
sf::Vector2<T> norm(sf::Vector2<T> vec) {
	return vec / std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

// dot product
template <typename T>
T dot(sf::Vector2<T> lhs, sf::Vector2<T> rhs) {
	return lhs.x * rhs.x + lhs.y + rhs.y;
}

// cross product
// (cross product in 2D returns a scalar)
template <typename T>
T cross(sf::Vector2<T> lhs, sf::Vector2<T> rhs) {
	return (lhs.x * rhs.y - lhs.y * rhs.x);
}

};
