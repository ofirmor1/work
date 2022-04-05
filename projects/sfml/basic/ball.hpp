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
		 sf::Vector2f a_velocity = sf::Vector2f(200.f, 200.f));
	~Ball() = default;

	void move(const sf::Time& a_deltaTime, const sf::Vector2u& a_windowSize, 
			  const Paddle& a_paddle, std::vector<Brick*>& a_bricks,
			  int& a_lives, int& a_score);
private:
	sf::CircleShape m_ball;
	sf::Vector2f m_velocity;

private:
	void bounceFX(sf::Sound& sfx);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

} // namespace game
