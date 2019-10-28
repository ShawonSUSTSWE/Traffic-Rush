#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <sstream>
#include <string.h>
#include <random>
#include <fstream>
#include "time.h"
#include <Windows.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::RectangleShape car(sf::Vector2f(100.f, 100.0f));
    car.setFillColor(sf::Color::Magenta);
    car.setPosition(500.f,500.f);
    sf::Texture cartexture;
    cartexture.loadFromFile("car-top-view-vehicle-overhead-260nw-1251380068.jpg");
    car.setTexture(&cartexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                car.move(0.0f, -5.0f);
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                car.move(0.0f, 5.0f);
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                car.move(-5.0f, 0.0f);
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                car.move(5.0f, 0.0f);

        }


        window.clear();
        window.draw(car);
        window.display();
    }

    return 0;
}
