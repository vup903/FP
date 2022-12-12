#pragma once
#include <iostream>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/*如果要看精靈，main.cpp我有用註解寫，拿掉註解就可以了*/
class Pac{
private:
    sf::Texture pacTexture;
    sf::Sprite pacSpr;

    void init(float pacPos_x, float pacPos_y);

public:
    Pac(string pacFile, float pacPos_x, float pacPos_y);
    void drawPac(RenderWindow *window) { window->draw(pacSpr); }
};

void Pac::init(float pacPos_x, float pacPos_y)
{
    pacSpr.setScale(sf::Vector2f(0.2, 0.2));
    pacSpr.setPosition(sf::Vector2f(pacPos_x, pacPos_y));
}

Pac::Pac(string pacFile, float pacPos_x, float pacPos_y)
{
    pacTexture.loadFromFile(pacFile);
    std::cout << "Pac class OK \n";
    pacSpr.setTexture(pacTexture);
    init(pacPos_x, pacPos_y);
}