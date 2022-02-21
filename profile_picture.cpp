/*
* profile_picture.cpp
* Author : Skalefou
* Creation date: 20/02/2022 (D/M/Y)
* Date of last update : 21/02/2022 (D/M/Y)
*
* Program that displays a sinusoidal function, and adds color and animation.
*/

#include <SFML/Graphics.hpp>
#include <array>

#define M_PI 3.14159265358979323846 

//load colors.
sf::Color colorLoad(int i)
{
    sf::Color color(0, 0, 0);
    if (i <= 85 || (i > 255 && i <= 340))
    {
        color.b = 255 - ((255 / 85) * i);
        color.g = ((255 / 85) * i);
    }
    else if (i > 85 && i <= 170 || (i > 340 && i <= 425))
    {
        color.g = 255 - ((255 / 85) * (i - 85));
        color.r = ((255 / 85) * (i - 85));
    }
    else if (i > 170 && i <= 255 || (i > 255 && i <= 512))
    {
        color.r = 255 - ((255 / 85) * (i - 170));
        color.b = ((255 / 85) * (i - 170));
    }
    return color;
}

//load function.
void loadLine(std::array <sf::VertexArray, 512> &ar)
{
    std::array<float, 512> height;
    for (int i = 0; i < 512; i++)
        height[i] = (float)(256 + (cos(i * (M_PI / 32))) * 32);
    for (int i = 0; i < 512; i++)
    {
        ar[i][0].position = sf::Vector2f((float)i, height[i]);
        ar[i][1].position = sf::Vector2f((float)i, (height[i]-32));
        ar[i][0].color = colorLoad(i);
        ar[i][1].color = ar[i][0].color;
    }
}

//Shows the function.
void draw(sf::RenderWindow &window,std::array <sf::VertexArray, 512>& ar)
{
    for (unsigned int i = 0; i < 512; i++)
        window.draw(ar[i]);
}

//Moves the colors of the sinusoidal function.
void colorWave(std::array <sf::VertexArray, 512>& ar, sf::Clock &clockColorWave)
{
    if (clockColorWave.getElapsedTime() >= sf::milliseconds(7))
    {
        for (int i = 0; i < 511; i++)
        {
            ar[i][0].color = ar[i + 1][0].color;
            ar[i][1].color = ar[i + 1][0].color;
        }
        ar[511][0].color = ar[0][0].color;
        ar[511][1].color = ar[0][0].color;
        clockColorWave.restart();
    }
}

//Moves the sinusoidal function.
void moveWave(std::array <sf::VertexArray, 512>& ar, sf::Clock& clockMoveWave)
{
    if (clockMoveWave.getElapsedTime() >= sf::milliseconds(12))
    {
        for (int i = 0; i < 512; i++)
        {
            ar[i][0].position.x++;
            if (ar[i][0].position.x >= 512)
                ar[i][0].position.x = 0;
            ar[i][1].position.x = ar[i][0].position.x;
        }
        clockMoveWave.restart();
    }
}

//Estimates the time the program should sleep.
sf::Time sleepTime(sf::Clock &clockWait)
{
    if (sf::microseconds(16'666) <= clockWait.getElapsedTime())
        return sf::milliseconds(0);
    else
        return (sf::microseconds(16'666) - clockWait.getElapsedTime());
}

//Program event loop.
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
   
    sf::RenderWindow window(sf::VideoMode(511, 512), "Profile Picture");
    sf::Clock clockColorWave, clockMoveWave, clockWait;
    std::array < sf::VertexArray, 512 > ar;
    ar.fill(sf::VertexArray(sf::Lines, 2)); 

    window.setFramerateLimit(60);

    sf::Image icone;
    if (icone.loadFromFile("data/icone.png"))
        window.setIcon(icone.getSize().x, icone.getSize().y, icone.getPixelsPtr());

    loadLine(ar);
    while (window.isOpen())
    {
        sf::sleep(sleepTime(clockWait));
        clockWait.restart();
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        colorWave(ar, clockColorWave);
        moveWave(ar, clockMoveWave);

        draw(window, ar);
        window.display();
    }

    return 0;
}