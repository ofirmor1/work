#include <SFML/Graphics.hpp>
#include "brick.hpp"

namespace game
{

Brick::Brick(sf::Vector2f a_size, sf::Vector2f a_position, sf::Color a_color, short a_health)
: m_brick(a_size)
, m_health(a_health)
{
	m_brick.setPosition(a_position);
	m_brick.setFillColor(a_color);
}

void Brick::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const
{
	a_target.draw(m_brick);
}

void Brick::hurt()
{
	--m_health;
}

short Brick::getCurrHealth() const
{
	return m_health;
}


sf::FloatRect Brick::getBounds() const
{
	return m_brick.getGlobalBounds();
}

}//namespace game