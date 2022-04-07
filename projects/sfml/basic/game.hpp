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
	void createLevel(size_t a_numOfBlocksInRow = 10, size_t a_numOfRows = 5, float a_padding = 5.f);

	void input(sf::Keyboard::Key a_key, bool a_isPressed);
	void processEvents();
	void update(const sf::Time& a_deltaTime);
	void render();

	void drawFPS(const sf::Time& a_deltaTime);

private:
    static const sf::Time FPS;
	static bool	 ShowFPS;

	sf::RenderWindow	m_window;
	Paddle				m_player;
	Ball				m_ball;
	std::vector<Brick*> m_level;
	
	short m_lives;

	sf::Font	m_font;
	sf::Text	m_livesText;
	sf::Text	m_drawFPSText;
	std::size_t m_drawFPSFrames;
	sf::Time	m_drawFPSTime;

};

}//namespace game

// int main()
// {
    
//     sf::CircleShape greenCircle(10.f);
//     sf::CircleShape blueCircle(10.f);
//     greenCircle.setFillColor(sf::Color::Green);
//     blueCircle.setFillColor(sf::Color::Red);
//     greenCircle.setPosition(20, 30);
//     blueCircle.setPosition(40, 90);
//     double greenStepX = 5;
//     double greenStepY = 5;
//     double blueStepX = 50;
//     double blueStepY = 50;

//     auto const ws = window.getSize();
//     auto const wsRightEdge = ws - 80;
//     auto const wsLeftEdge = 50;
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(greenCircle);
//         window.draw(blueCircle);
//         window.display();
// }

//     return 0;
// }


//         if(greenCircle.getPosition().x > wsRightEdge && greenCircle.getPosition().y < wsRightEdge)
//         {
//             greenStepX = -0.1;
//             greenStepY = -0.1;
//         }
//         if(greenCircle.getPosition().x < wsLeftEdge && greenCircle.getPosition().y > wsLeftEdge)
//         {
//             greenStepX = 0.1;
//             greenStepY = 0.1;
//         }
//         if(greenCircle.getPosition().x > wsRightEdge && greenCircle.getPosition().y > wsRightEdge)
//         {
//             greenStepX = 0.1;
//             greenStepY = -0.1;
//         }
//         if(greenCircle.getPosition().x < wsLeftEdge && greenCircle.getPosition().y < wsLeftEdge)
//         {
//             greenStepX = -0.1;
//             greenStepY = 0.1;
//         }

//         if(blueCircle.getPosition().x > wsRightEdge && blueCircle.getPosition().y < wsRightEdge)
//         {
//             blueStepX = -0.1;
//             blueStepY = -0.1;
//         }
//         if(blueCircle.getPosition().x < wsLeftEdge && blueCircle.getPosition().y > wsLeftEdge)
//         {
//             blueStepX = 0.1;
//             blueStepY = 0.1;
//         }
//         if(blueCircle.getPosition().x > wsRightEdge && blueCircle.getPosition().y > wsRightEdge)
//         {
//             blueStepX = 0.1;
//             blueStepY = -0.1;
//         }
//         if(blueCircle.getPosition().x < wsLeftEdge && blueCircle.getPosition().y < wsLeftEdge)
//         {
//             blueStepX = -0.1;
//             blueStepY = 0.1;
//         }

//         greenCircle.move(greenStepX, greenStepY);
//         blueCircle.move(blueStepX, blueStepY);