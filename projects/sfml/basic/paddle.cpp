#include "paddle.hpp"

namespace game
{

Paddle::Paddle(sf::Vector2f a_position, sf::Color a_color, sf::Vector2f a_size)
: m_paddle(sf::Vector2f(a_size.x, a_size.y))
{
	m_paddle.setFillColor(a_color);
	m_paddle.setOrigin((a_size.x / 2.f), (a_size.y / 2.f));
	m_paddle.setPosition(a_position);
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

