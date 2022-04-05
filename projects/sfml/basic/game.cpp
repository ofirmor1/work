#include <SFML/Graphics.hpp>

#include "game.hpp"

namespace game
{
Game::Game()
: m_window(sf::VideoMode(600, 800), "Breakout!")
, m_player(sf::Vector2f((m_window.getSize().x / 2.f), (m_window.getSize().y - 70.f)))
, m_ball(5.f, sf::Color::Yellow, sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f))
, m_lives(3)
, m_score(0)
, m_font()
, m_livesText()
, m_scoreText()
, m_drawFPSText()
, m_drawFPSFrames(0)
, m_drawFPSTime()
{}

Game::~Game()
{
	for(auto e : m_level)
    {
		delete e;
	}
	m_level.clear();
}


sf::Vector2u Game::getWindowSize() const
{
    return m_window.getSize(); 
}

Paddle* Game::getPaddle()
{
    return &m_player;
}

std::vector<Brick*>* Game::getLevel()
{
    return &m_level;
}

void Run()
{

}

}//namespace game

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(900, 900), "Bouncing balls!");
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