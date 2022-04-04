#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Bouncing balls!");
    sf::CircleShape greenCircle(10.f);
    sf::CircleShape blueCircle(10.f);
    greenCircle.setFillColor(sf::Color::Green);
    blueCircle.setFillColor(sf::Color::Red);
    greenCircle.setPosition(20, 30);
    blueCircle.setPosition(40, 90);
    double greenStepX = 5;
    double greenStepY = 5;
    double blueStepX = 50;
    double blueStepY = 50;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(greenCircle.getPosition().x > 120 && greenCircle.getPosition().y < 120)
        {
            greenStepX = -0.1;
            greenStepY = -0.1;
        }
        if(greenCircle.getPosition().x < 50 && greenCircle.getPosition().y > 50)
        {
            greenStepX = 0.1;
            greenStepY = 0.1;
        }
        if(greenCircle.getPosition().x > 120 && greenCircle.getPosition().y > 120)
        {
            greenStepX = 0.1;
            greenStepY = -0.1;
        }
        if(greenCircle.getPosition().x < 50 && greenCircle.getPosition().y < 50)
        {
            greenStepX = -0.1;
            greenStepY = 0.1;
        }

        if(blueCircle.getPosition().x > 120 && blueCircle.getPosition().y < 120)
        {
            blueStepX = -0.1;
            blueStepY = -0.1;
        }
        if(blueCircle.getPosition().x < 50 && blueCircle.getPosition().y > 50)
        {
            blueStepX = 0.1;
            blueStepY = 0.1;
        }
        if(blueCircle.getPosition().x > 120 && blueCircle.getPosition().y > 120)
        {
            blueStepX = 0.1;
            blueStepY = -0.1;
        }
        if(blueCircle.getPosition().x < 50 && blueCircle.getPosition().y < 50)
        {
            blueStepX = -0.1;
            blueStepY = 0.1;
        }
        
        greenCircle.move(greenStepX, greenStepY);
        blueCircle.move(blueStepX, blueStepY);
        window.clear();
        window.draw(greenCircle);
        window.draw(blueCircle);
        window.display();
}

    return 0;
}