#pragma once

namespace game
{

class Paddle : public sf::Drawable
{
public:
	Paddle(sf::Vector2f a_position = sf::Vector2f(30.f, 2.5f),
		   sf::Color a_color = sf::Color::White,
		   sf::Vector2f a_size = sf::Vector2f(60.f, 5.f));
	~Paddle() = default;

	void move(const int a_position, const size_t a_windowWidth);
	sf::FloatRect getBounds() const;

private:
	virtual void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;

private:
	sf::RectangleShape m_paddle;
};

} // namespace game