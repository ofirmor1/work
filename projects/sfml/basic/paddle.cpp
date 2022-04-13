#include "paddle.hpp"

namespace game
{

Paddle::Paddle(size_t a_level, std::string a_paddleTexPath, sf::Vector2f a_position, sf::Color a_color, sf::Vector2f a_size)
: m_paddle(sf::Vector2f(a_size.x, a_size.y))
, m_paddleTex(new sf::Texture)
{
	if (!(*m_paddleTex).loadFromFile(a_paddleTexPath))
	{
		std::cout << "failed to load paddle texture." << std::endl;
	}
	m_paddle.setFillColor(a_color);
	m_paddle.setOrigin((a_size.x / 2.f), (a_size.y / 2.f));
	m_paddle.setPosition(a_position);
	m_paddle.setTexture(m_paddleTex);
	(*m_paddleTex).setSmooth(true);
	switch (a_level)
	{
	case 1:
		m_paddle.setScale(2.5, 8);

		break;
	case 2:
		m_paddle.setScale(1.8, 8);
		break;
	case 3:
		m_paddle.setScale(1.2, 8);
		break;
	}	
}

void Paddle::move(const int a_position, const size_t a_windowWidth)
{
	float radius = (m_paddle.getGlobalBounds().width / 2);

	if((a_position - radius) > 0 && (a_position + radius) < a_windowWidth)
		m_paddle.setPosition(a_position, m_paddle.getPosition().y);
}

void Paddle::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const
{
	a_target.draw(m_paddle);
}

sf::FloatRect Paddle::getBounds() const
{
	return m_paddle.getGlobalBounds();
}

} // namespace game

