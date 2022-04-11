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

    if(!m_bounceBuffer.loadFromFile("sounds/bounce_sound.wav"))
    {
        std::cout << "Failed to load sounds/bounce_sound.wav" << std::endl;
    }
	m_bounceSound.setBuffer(m_bounceBuffer);

	if(!m_brickBuffer.loadFromFile("sounds/brick_sound.wav"))
    {
        std::cout << "Failed to load sounds/brick_sound.wav" << std::endl;
    }
	m_brickSound.setBuffer(m_brickBuffer);
}

void Ball::move(const sf::Time& a_deltaTime, const sf::Vector2u& a_windowSize, 
			  const Paddle& a_paddle, std::vector<Brick*>& a_bricksVec,
			  short& a_lives)
{
    sf::Vector2f pos = m_ball.getPosition();

    //bounce left/right side
    if(pos.x < m_ball.getRadius() || pos.x > a_windowSize.x - m_ball.getRadius())
    {
        bounce(m_bounceSound);
        m_speed = sf::Vector2f(m_speed.x * -1.f, m_speed.y);
    }

    //bounce top
    if(pos.y < m_ball.getRadius())
    {
        bounce(m_bounceSound);
        m_speed = sf::Vector2f(m_speed.x, m_speed.y * -1.f);
    }

    //bounce paddle
    if(a_paddle.getBounds().intersects(m_ball.getGlobalBounds()))
    {
        bounce(m_bounceSound);
        m_speed = sf::Vector2f(m_speed.x, m_speed.y * -1.f);
    }

    //ball hit buttom
    if(a_windowSize.y - m_ball.getRadius() < pos.y)
    {
        --a_lives;
        bounce(m_bounceSound);
        m_ball.setPosition(a_windowSize.x / 2.f, a_windowSize.y / 2.f);
    }

    // check for brick collisions
    std::vector<Brick*>::iterator itr;
    for(itr = a_bricksVec.begin(); itr != a_bricksVec.end(); itr++)
    {
		if(*itr != NULL && (**itr).getBounds().intersects(m_ball.getGlobalBounds()))
        {
            m_speed = sf::Vector2f(m_speed.x, m_speed.y * -1.f);
            bounce(m_brickSound);
            if((*itr)->getCurrHealth() > 1)
            {
                (*itr)->hurt();
            }
            else
            {
                delete *itr;
			    *itr = NULL;
            }
        }
        // ++m_level;
        // Run();

        
    }
        
    m_ball.move(m_speed * a_deltaTime.asSeconds());
}

void Ball::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const
{
	a_target.draw(m_ball);
}

void Ball::bounce(sf::Sound& a_bounce) {
	// Play bounce sound
	a_bounce.play();
}

}//namespace game