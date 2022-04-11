#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "game.hpp"

namespace game
{

const sf::Time Game::FPS = sf::seconds(1.f / 60.f);
bool Game::ShowFPS = false;

Game::Game(short a_level)
: m_lives(3)
, m_level(a_level)
, m_font()
, m_livesText()
, m_drawFPSText()
, m_gameOverText()
, m_drawFPSFrames(0)
, m_drawFPSTime()
, m_backgroundTex()
, m_background()
{

    windowSetUp();
    textSetUp();
    m_player = Paddle("./images/skate.png", sf::Vector2f((m_window.getSize().x / 2.f), (m_window.getSize().y - 70.f)));
    m_ball = Ball(5.f, sf::Color::White, sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f));
    setUpLevel();
}
void Game::windowSetUp()
{
    m_window.create(sf::VideoMode(800 , 600), "Breaking bricks - Level 1");
    size_t winY = sf::VideoMode::getDesktopMode().height / 2 - m_window.getSize().y / 2;
    size_t winX = sf::VideoMode::getDesktopMode().width / 2 - m_window.getSize().x / 2;

    m_window.setPosition(sf::Vector2i(winX, winY));


    if(!m_backgroundTex.loadFromFile("images/background.jpg"))
    {
        std::cout << "failed to load background image." << std::endl;
    }

    this->m_backgroundTex.setSmooth(true);
    this->m_background.setTexture(this->m_backgroundTex);
    m_background.scale(1.8, 1.6);
}

void Game::textSetUp()
{
    if(!m_font.loadFromFile("fonts/Arial.ttf"))
    {
        std::cout << "failed to load font." << std::endl;
    }
    //FPS text set up
    m_drawFPSText.setFillColor(sf::Color::White);
    m_drawFPSText.setOutlineColor(sf::Color::White);
    m_drawFPSText.setFont(m_font);
    m_drawFPSText.setPosition(5.f, 5.f);
    m_drawFPSText.setCharacterSize(10);
    
    //lives text set up
    m_livesText.setFillColor(sf::Color::White);
    m_livesText.setOutlineColor(sf::Color::White);
    m_livesText.setFont(m_font);
    m_livesText.setPosition(15.f, m_window.getSize().y - 30.f);
    m_livesText.setCharacterSize(16);

    //text set up
    m_gameOverText.setFillColor(sf::Color::White);
    m_gameOverText.setOutlineColor(sf::Color::White);
    m_gameOverText.setFont(m_font);
    m_gameOverText.setPosition(m_window.getSize().y / 2, m_window.getSize().x / 2  - 100.f);
    m_gameOverText.setCharacterSize(30);

        //text set up
    m_roundFinishedText.setFillColor(sf::Color::White);
    m_roundFinishedText.setOutlineColor(sf::Color::White);
    m_roundFinishedText.setFont(m_font);
    m_roundFinishedText.setPosition(m_window.getSize().y / 2, m_window.getSize().x / 2  - 100.f);
    m_roundFinishedText.setCharacterSize(30);
}

void Game::setUpLevel()
{
    switch (m_level)
    {
    case 1:
        createLevel(1, 1, 40.f, m_level);
        break;
    case 2:
        createLevel(5, 5, 40.f, m_level);
        m_window.setTitle("Breaking bricks - Level 2");
        break;
    }
}

// void Game::setWindowBackground()
// {
//     sf::Event event;
//     while(m_window.waitEvent(event))
//     {
//         if (event.type == sf::Event::Resized)
//         {
//             // Get the new size of the window
//             const sf::Vector2f visibleArea(static_cast<float>(event.size.width), static_cast<float>(event.size.height));

//             // Find the scale factor in the x and the y axis
//             const float scaleXFactor = visibleArea.x / m_background.getLocalBounds().width;
//             const float scaleYFactor = visibleArea.y / m_background.getLocalBounds().height;

//             // Pick the smallest factor and get the new view size.
//             const float lowestFactor = std::min(scaleXFactor, scaleYFactor);
//             const sf::Vector2f windowSize(sf::Vector2f(m_window.getSize()));
//             const sf::Vector2f viewSize = windowSize / lowestFactor;

//             m_gameView.setSize(viewSize);
//             m_gameView.setCenter(viewSize / 2.0f);
//             m_window.setView(m_gameView);
//         }
//     }
// }

Game::~Game()
{
	for(auto& e : m_bricks)
    {
		delete e;
	}

	m_bricks.clear();
}

void Game::Run()
{
    // anotherRound:
    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    
    while (m_window.isOpen() && m_lives > 0)
    {
        sf::Time deltaTime = clock.restart();
        time += deltaTime;

        while(time > FPS)
        {
            time -= FPS;
            processEvents();
            update(FPS);
        }
        if (ShowFPS)
        {
            drawFPS(deltaTime);
        }
        render();
    }
    m_gameOverText.setString("Game Over!\n Play again? press 1, \notherwise press 0");
    m_window.draw(m_gameOverText);
    m_window.display();
    gameOverMenu();
}

void Game::gameOverMenu()
{   
    sf::Event event;
    while (m_window.waitEvent(event))
    {
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1))
        {
            Game g(1);
            m_window.close();
            g.Run();
        }
        else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num0))
        {
            m_window.close();
        }
    }
}

void Game::input(sf::Keyboard::Key a_key, bool a_isPressed)
{
    if(a_key == sf::Keyboard::F6 && !a_isPressed)
    {
        ShowFPS = false;
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            input(event.key.code, true);
        }

        else if (event.type == sf::Event::KeyReleased)
        {
            input(event.key.code, false);
        }

        else if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    } 
}

void Game::update(const sf::Time& a_deltaTime)
{
    m_ball.move(a_deltaTime, m_window.getSize(), m_player, m_bricks, m_lives);
    m_player.move(sf::Mouse::getPosition(m_window).x, m_window.getSize().x);
}

void Game::drawFPS(const sf::Time& a_deltaTime)
{
    m_drawFPSTime += a_deltaTime;
    m_drawFPSFrames += 1;

    if(m_drawFPSTime >= sf::seconds(1.0f))
    {
        m_drawFPSText.setString(std::to_string(m_drawFPSFrames) + "FPS");
        m_drawFPSTime -= sf::seconds((1.0f));
        m_drawFPSFrames = 0;
    }
}

void Game::finishRound()
{  
    m_roundFinishedText.setString("Congrats! You finished this round!\n for next round? press 1, \nexit game press 0");
    std::cout << "1212";
    m_window.draw(m_roundFinishedText);
    m_window.display();
    sf::Event event;
    while (m_window.waitEvent(event))
    {
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1))
        {
            Game g(2);
            m_window.close();
            g.Run();
            // ++m_level;

        }
        else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num0))
        {
            m_window.close();
        }
    }
}

void Game::render()
{
    m_window.clear();
    m_window.draw(m_background);
    m_window.draw(m_player);
    m_window.draw(m_ball);
    m_livesText.setString("Lives: " + std::to_string(m_lives));
    m_window.draw(m_livesText);

    std::vector<Brick*>::iterator itr;
	for(itr = m_bricks.begin(); itr != m_bricks.end(); itr++)
    {
		if((*itr) != NULL)
        {
            m_window.draw(**itr);
        }
        else
        {std::cout << "1212";
            // sleep(1);
            finishRound();
            
        }
	}

    if(ShowFPS)
    {
        m_window.draw(m_drawFPSText);
    }

    m_window.display();
}

void Game::createLevel(size_t a_numOfBlocksInRow , size_t a_numOfRows, float a_padding, short m_level)
{
    float width = ((m_window.getSize().x - (a_padding * (a_numOfBlocksInRow + 1))) / a_numOfBlocksInRow);
    sf::Vector2f brickSize(width, 20.f);
    float accumRow = a_padding;

    std::string brickImgPath = "./images/brick_tex.jpg";
    switch (m_level)
    {
    case 1:
        for (size_t row = 0; row < a_numOfRows; ++row)
        {
            float accumCol = a_padding;
            for (size_t col = 0; col < a_numOfBlocksInRow; ++col)
            {
                sf::Vector2f pos = sf::Vector2f((col * brickSize.x) + accumCol, (row * brickSize.y) + accumRow);
                    if(col % 4 == 0)
                {
                    m_bricks.push_back(new Brick(brickImgPath, brickSize, pos, sf:: Color::White, 1));
                }
                else
                {
                    m_bricks.push_back(new Brick(brickImgPath, brickSize, pos, sf:: Color::White, 2));
                }
                accumCol += a_padding;
            }
            accumRow += a_padding;  
        }
        break;
    case 2:
        for (size_t row = 0; row < a_numOfRows; ++row)
        {
            float accumCol = a_padding;
            for (size_t col = 0; col < a_numOfBlocksInRow; ++col)
            {
                sf::Vector2f pos = sf::Vector2f((col * brickSize.x) + accumCol, (row * brickSize.y) + accumRow);
                if(col % 4 == 0)
                {
                    m_bricks.push_back(new Brick(brickImgPath, brickSize, pos, sf:: Color::White, 1));
                }
                else
                {
                    m_bricks.push_back(new Brick(brickImgPath, brickSize, pos, sf:: Color::White, 2));
                }
                
                accumCol += a_padding;
            }
            accumRow += a_padding;  
        }
        break;
    default:
        break;
    }
}

}//namespace game