#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "brick.hpp"
#include "paddle.hpp"

namespace game
{

class Ball : public sf::Drawable
{
public:
	Ball(float a_radius = 5.f, sf::Color a_color = sf::Color::Blue,
		 sf::Vector2f a_position = sf::Vector2f(5.f, 5.f),
		 sf::Vector2f a_speed = sf::Vector2f(200.f, 200.f));
	~Ball() = default;

	void move(const sf::Time& a_deltaTime, const sf::Vector2u& a_windowSize, 
			  const Paddle& a_paddle, std::vector<Brick*>& a_bricks,
			  short& a_lives);
private:
	sf::CircleShape m_ball;
	sf::Vector2f m_speed;
    size_t m_lives;

private:
	virtual void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;


};

} // namespace game