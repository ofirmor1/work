#include <SFML/Graphics.hpp>
#include <cstddef>
#include <algorithm>

#include "ball.hpp"

namespace game
{

Ball::Ball(float a_radius, sf::Color a_color, sf::Vector2f a_position, sf::Vector2f a_speed)
: m_ball(a_radius)
, m_speed(a_speed)
{
    m_ball.setOrigin(a_radius, a_radius);
    m_ball.setFillColor(a_color);
    m_ball.setPosition(a_position);
}

void Ball::move(const sf::Time& a_deltaTime, const sf::Vector2u& a_windowSize, 
			  const Paddle& a_paddle, std::vector<Brick*>& a_bricks,
			  short& a_lives)
{
    sf::Vector2f pos = m_ball.getPosition();

    //bounce left/right side
    if(pos.x < m_ball.getRadius() || pos.x > a_windowSize.x - m_ball.getRadius())
    {
        m_speed = sf::Vector2f(m_speed.x * -1.f, m_speed.y);
    }

    //bounce top
    if(pos.y < m_ball.getRadius())
    {
        m_speed = sf::Vector2f(m_speed.x, m_speed.y * -1.f);
    }

    //bounce paddle
    if(a_paddle.getBounds().intersects(m_ball.getGlobalBounds()))
    {
        m_speed = sf::Vector2f(m_speed.x, m_speed.y * -1.f);
    }

    //ball hit buttom
    if(a_windowSize.y - m_ball.getRadius() < pos.y)
    {
        --m_lives;
        m_ball.setPosition(a_windowSize.x / 2.f, a_windowSize.y / 2.f);
    }

    //check for brick collisions
    std::vector<Brick*> bricks;
    for(auto e : bricks)
    {
        if(e->getBounds().intersects(m_ball.getGlobalBounds ()))
        {
            m_speed = sf::Vector2f(m_speed.x, m_speed.y * -1.f);

            delete e;
        }

        m_ball.move(m_speed * a_deltaTime.asSeconds());
    }
}

void Ball::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const
{
	a_target.draw(m_ball);
}

}//namespace game