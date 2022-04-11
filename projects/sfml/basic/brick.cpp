#include <SFML/Graphics.hpp>
#include "brick.hpp"
#include <string>

namespace game
{

Brick::Brick(std::string a_brickTexPath, sf::Vector2f a_size, sf::Vector2f a_position, sf::Color a_color, short a_health)
: m_brick(a_size)
, m_health(a_health)
, m_brickTex(new sf::Texture)
{

	if (!(*m_brickTex).loadFromFile(a_brickTexPath))
	{
		std::cout << "failed to load brick texture." << std::endl;
	}
	(*m_brickTex).setSmooth(true);
	m_brick.setTexture(m_brickTex);
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