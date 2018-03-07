#ifndef VECTOR2UL_H
#define VECTOR2UL_H

#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <vector>

// create a definition for a sf::vector using size_t types
using Vector2ul = sf::Vector2<size_t>;

// returns the length of a sf::vector
template<class T>
double length(const sf::Vector2<T>& t_vec)
{
    // TODO: ...
}

// returns a normalized sf::vector
template<class T>
sf::Vector2<T> normalize(const sf::Vector2<T>& t_vec)
{
    // TODO: ...
}

// allow casting from one sf::vector internal type to another
template<class T, class U>
sf::Vector2<T> Vcast(const sf::Vector2<U>& t_vec)
{
    return sf::Vector2<T>(static_cast<T>(t_vec.x), static_cast<T>(t_vec.y));
}

// converts from degrees to radians
template<class T>
static double deg2rad(double t_degrees)
{
    // TODO: ...
}

// rotate a sf::vector by an angle(degrees)
template<class T>
sf::Vector2<T> rotate(const sf::Vector2<T>& t_vec, const double degrees)
{
    const double theta = deg2rad(degrees);
    const double cs = cos(theta);
    const double sn = sin(theta);

    return {static_cast<T>(t_vec.x * cs - t_vec.y * sn), static_cast<T>(t_vec.x * sn + t_vec.y * cs)};
}

// allow sf::vectors to be printed to the stdout
template<class T>
std::ostream& operator<<(std::ostream& t_os, const sf::Vector2<T> t_vec)
{
    t_os << '<' << t_vec.x << ', ' << t_vec.y << '>';
    return os;
}

#endif !VECTOR2UL_H