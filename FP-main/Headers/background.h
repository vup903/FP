#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/*如果要看首頁，main.cpp我有用註解寫，拿掉註解就可以了*/
class Background{
private:
    sf::Texture bgTexture;
    sf::RectangleShape bgShape;

public:
    Background(string bgFile);
    void drawbg(RenderWindow *window);
};

Background::Background(string bgFile)
{
    bgTexture.loadFromFile(bgFile);
    sf::Vector2u textureSize = bgTexture.getSize();
    float rectWidth = static_cast<float>(textureSize.x/2);
    float rectHeight = static_cast<float>(textureSize.y/2);

    bgShape.setSize(sf::Vector2f(rectWidth, rectHeight));
    bgShape.setTexture(&bgTexture);
};

void Background::drawbg(sf::RenderWindow *window)
{
    window->draw(bgShape);
}