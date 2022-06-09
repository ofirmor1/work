#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "game.hpp"

namespace game
{

const sf::Time Game::FPS = sf::seconds(1.f / 60.f);
bool Game::ShowFPS = false;

Game::Game(short a_level)
: m_lives(3)
, m_score()
, m_level(a_level)
, m_font()
, m_livesText()
, m_scoreText()
, m_drawFPSText()
, m_gameOverText()
, m_drawFPSFrames(0)
, m_drawFPSTime()
, m_backgroundTex()
, m_background()
{
    if(m_level == 1)
    {
        windowSetUp();
    }
    initilizeGameObj();
}

void Game::initilizeGameObj()
{
    textSetUp();
    switch (m_level)
    {
    case 1:
        m_player = Paddle(m_level, "./images/skate.png", sf::Vector2f((m_window.getSize().x / 2.f), (m_window.getSize().y - 70.f)));
        m_ball = Ball(5.f, sf::Color::White, sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y - 250));
        break;
    case 2:
        m_player = Paddle(m_level, "./images/skate2.png", sf::Vector2f((m_window.getSize().x / 2.f), (m_window.getSize().y - 70.f)));
        m_ball = Ball(7.f, sf::Color::Red, sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y - 250));
        break;
    case 3:
        m_player = Paddle(m_level, "./images/skate3.png", sf::Vector2f((m_window.getSize().x / 2.f), (m_window.getSize().y - 70.f)));
        m_ball = Ball(10.f, sf::Color::Blue, sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y - 250));
        break;
    }
    
    setUpLevel(m_level);
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

    //score text set up
    m_scoreText.setFillColor(sf::Color::White);
    m_livesText.setOutlineColor(sf::Color::White);
    m_scoreText.setFont(m_font);
	m_scoreText.setPosition(400.f, m_window.getSize().y - 30.f);
	m_scoreText.setCharacterSize(16);
	m_scoreText.setString("Score: " + std::to_string(m_score));

    //gameOver text set up
    m_gameOverText.setFillColor(sf::Color::White);
    m_gameOverText.setOutlineColor(sf::Color::White);
    m_gameOverText.setFont(m_font);
    m_gameOverText.setPosition(m_window.getSize().y / 2, m_window.getSize().x / 2  - 100.f);
    m_gameOverText.setCharacterSize(30);

    //roundFinished text set up
    m_roundFinishedText.setFillColor(sf::Color::White);
    m_roundFinishedText.setOutlineColor(sf::Color::White);
    m_roundFinishedText.setFont(m_font);
    m_roundFinishedText.setPosition(m_window.getSize().y / 3, m_window.getSize().x / 2  - 100.f);
    m_roundFinishedText.setCharacterSize(30);
}

void Game::setUpLevel(size_t a_level)
{
    switch (a_level)
    {
    case 1:
        createLevel(1, 1, 60.f, a_level);
        break;
    case 2:
        createLevel(3, 5, 40.f, a_level);
        m_window.setTitle("Breaking bricks - Level 2");
        break;
    case 3:
        createLevel(3, 5, 40.f, a_level);
        m_window.setTitle("Breaking bricks - Level 3");
        break;
    default:
        exit(0);
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
        if(m_bricks.empty())
        {
            finishRound();
        }
        render();
    }
    if(m_lives == 0)
    {
        m_gameOverText.setString("Game Over!\n Play again? press 1, \notherwise press 0");
        m_window.draw(m_gameOverText);
        m_window.display();
        gameOverMenu();
    }
}

void Game::gameOverMenu()
{   
    sf::Event event;
    while (m_window.waitEvent(event))
    {
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1))
        {
            Game g(4);
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
    m_ball.move(a_deltaTime, m_window.getSize(), m_player, m_bricks, m_lives, m_score);
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
    m_roundFinishedText.setString("Congrats! You finished round number " + std::to_string(m_level) + "!\npress 1 to continue, \npress 0 to exit the game");
    m_window.draw(m_roundFinishedText);
    m_window.display();
    sf::Event event;
    while(m_window.waitEvent(event))
    {
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1))
        {
            finishLevel();
            ++m_level;
            initilizeGameObj();
            Run();
        }
        else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num0))
        {
            m_window.close();
        }
    }
}

// std::vector<Brick*> m_bricks;
// std::vector<std::unique_ptr<shape::brick> >& a_bricks
void Game::finishLevel()
{
    m_window.clear();
    m_bricks.clear();
    sleep(1);
}

void Game::render()
{
    m_window.clear();
    m_window.draw(m_background);
    m_window.draw(m_player);
    m_window.draw(m_ball);
    m_livesText.setString("Lives: " + std::to_string(m_lives));
    m_window.draw(m_livesText);
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_window.draw(m_scoreText);
    

    brickPtrVec::iterator itr;
	for(itr = m_bricks.begin(); itr != m_bricks.end(); itr++)
    {
		if((*itr) != NULL)
        {
            m_window.draw(**itr);
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
    std::string brickImg2Path = "./images/brick_tex2.jpg";
    switch (m_level)
    {
    case 1:
        for (size_t row = 0; row < a_numOfRows; ++row)
        {
            float accumCol = a_padding;
            for (size_t col = 0; col < a_numOfBlocksInRow; ++col)
            {
                sf::Vector2f pos = sf::Vector2f((col * brickSize.x) + accumCol, (row * brickSize.y) + accumRow);
                m_bricks.emplace_back(std::move(new Brick(brickImgPath, brickSize, pos, sf:: Color::White, 1)));
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
                if(col % 2 == 0 && row % 2 == 0)
                {
                    m_bricks.emplace_back(std::move(new Brick(brickImgPath, brickSize, pos, sf:: Color::White, 1)));
                }
                else
                {
                    m_bricks.emplace_back(std::move(new Brick(brickImg2Path, brickSize, pos, sf:: Color::White, 2)));
                }
                
                accumCol += a_padding;
            }
            accumRow += a_padding;  
        }
        break;
    case 3:
        for (size_t row = 0; row < a_numOfRows; ++row)
        {
            float accumCol = a_padding;
            for (size_t col = 0; col < a_numOfBlocksInRow; ++col)
            {
                sf::Vector2f pos = sf::Vector2f((col * brickSize.x) + accumCol, (row * brickSize.y) + accumRow);
                m_bricks.emplace_back(std::move(new Brick(brickImg2Path, brickSize, pos, sf:: Color::White, 2)));
                accumCol += a_padding;
            }
            accumRow += a_padding;  
        }
        break;
    default:
        break;
    }
        std::cout << m_bricks.size() << std::endl;
}

}//namespace game