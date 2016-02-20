#pragma once

#include "SFML/Graphics.hpp"

template <typename T>
T length(sf::Vector2<T> vec);

template <typename T>
sf::Vector2<T> norm(sf::Vector2<T> vec);

template <typename T>
T dot(sf::Vector2<T> lhs, sf::Vector2<T> rhs);

template <typename T>
T cross(sf::Vector2<T> lhs, sf::Vector2<T> rhs);
