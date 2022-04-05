#include <SFML/Graphics.hpp>
#include <cstddef>
#include <algorithm>

#include "ball.hpp"

namespace game
{

Ball::Ball(float a_radius, sf::Color a_color, sf::Vector2f a_position, sf::Vector2f a_speed)
: m_ball(a_radius)
, m_velocity(a_speed)
{
    m_ball.setOrigin(a_radius, a_radius);
    m_ball.setFillColor(a_color);
    m_ball.setPosition(a_position);
}

}//namespace game