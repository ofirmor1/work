#pragma once

#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "brick.hpp"
#include "paddle.hpp"

namespace game
{

class Game
{
public:
    Game();
	~Game();

	sf::Vector2u getWindowSize() const;
	Paddle* getPaddle();
	std::vector<Brick*>* getLevel();

	void Run();

private:
	void createLevel(size_t a_numOfBlocksInRow = 5, size_t a_numOfRows = 5, float a_padding = 40.f, short m_level = 1);

	void input(sf::Keyboard::Key a_key, bool a_isPressed);
	void processEvents();
	void gameOverMenu();
	void update(const sf::Time& a_deltaTime);
	void render();

	void setWindowBackground();

	void drawFPS(const sf::Time& a_deltaTime);

private:
    static const sf::Time FPS;
	static bool	 ShowFPS;
	
	short m_lives;
	short m_level;

	sf::Font	m_font;
	sf::Text	m_livesText;
	sf::Text	m_drawFPSText;
	sf::Text	m_gameOverText;
	std::size_t m_drawFPSFrames;
	sf::Time	m_drawFPSTime;
	sf::View	m_gameView;
	sf::Texture m_backgroundTex;
	sf::Sprite m_background;

	sf::Vector2u m_backgroundSize;
	sf::RenderWindow	m_window;
	Paddle				m_player;
	Ball				m_ball;
	std::vector<Brick*> m_bricks;

};

}//namespace game