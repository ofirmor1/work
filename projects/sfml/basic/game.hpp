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
    explicit Game(short a_level = 1);
	~Game();

	void initilizeGameObj();
	void textSetUp();
	void windowSetUp();
	void setUpLevel(size_t a_level);
	void Run();

	sf::Vector2u getWindowSize() const;
	Paddle* getPaddle();

private:
	void createLevel(size_t a_numOfBlocksInRow = 1, size_t a_numOfRows = 1, float a_padding = 40.f, short m_level = 1);

	void input(sf::Keyboard::Key a_key, bool a_isPressed);
	void processEvents();

	void gameOverMenu();
	void finishRound();
	void finishLevel();


	void update(const sf::Time& a_deltaTime);
	void render();

	void setWindowBackground();

	void drawFPS(const sf::Time& a_deltaTime);

private:
    static const sf::Time FPS;
	static bool	 ShowFPS;
	using brickPtrVec = std::vector<std::unique_ptr<Brick> >;
	
	short m_lives;
	short m_score;
	size_t m_level;

	sf::Font	 m_font;
	sf::Text	 m_livesText;
	sf::Text     m_scoreText;
	sf::Text	 m_drawFPSText;
	sf::Text 	 m_roundFinishedText;
	sf::Text	 m_gameOverText;
	std::size_t  m_drawFPSFrames;
	sf::Time	 m_drawFPSTime;
	sf::View	 m_gameView;

	sf::Texture  m_backgroundTex;
	sf::Sprite   m_background;
	sf::Vector2f m_backgroundSize;

	sf::RenderWindow	m_window;
	Paddle				m_player;
	Ball				m_ball;
	brickPtrVec			m_bricks;

};

}//namespace game