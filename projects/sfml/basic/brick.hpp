#pragma once

#include <iostream>

namespace game
{

class Brick : public sf::Drawable
{

public:
	Brick(sf::Vector2f a_size = sf::Vector2f(60.f, 40.f), 
    sf::Vector2f a_position = sf::Vector2f(0.f, 0.f),
    sf::Color a_color = sf::Color::White, short a_health = 1);
	~Brick() = default;

	sf::FloatRect getBounds() const;
	short getCurrHealth() const;
	void hurt();

private:
	virtual void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;

private:
	sf::RectangleShape m_brick;
	short m_health;

};

// window size 80 / 34

}//namespace game