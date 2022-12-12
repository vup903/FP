#pragma once
#include <iostream>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/*如果要看幽靈，main.cpp我有用註解寫，拿掉註解就可以了*/
class Ghost{
private:
    sf::Texture ghostTexture;
    sf::Sprite ghostSpr;

    void init(float ghostPos_x, float ghostPos_y) {
        ghostSpr.setScale(sf::Vector2f(0.1, 0.1));
        ghostSpr.setPosition(sf::Vector2f(ghostPos_x, ghostPos_y));
    }
public:
    Ghost(string ghostFile, float ghostPos_x, float ghostPos_y) {
        ghostTexture.loadFromFile(ghostFile);
        std::cout << "Ghost class OK \n";
        ghostSpr.setTexture(ghostTexture);
        init(ghostPos_x, ghostPos_y);
    };

    void drawGhost(RenderWindow *window) {
        window->draw(ghostSpr);
    }
};
