#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/*如果要看首頁，main.cpp我有用註解寫，拿掉註解就可以了*/
/*按鈕和首頁底圖我用不同的class寫的*/
class Button{
private:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::Vector2u buttonSize = buttonTexture.getSize();
    float buttonWidth = static_cast<float>(buttonSize.x);
    float buttonHeight = static_cast<float>(buttonSize.y);

public:
    Button(string buttonFile, float, float);
    //~Button();
    sf::Sprite getSprite(){ return buttonSprite; }
    void drawButton(sf::RenderWindow *window);
};

Button::Button(std::string buttonFile, float x_axis, float y_axis)
{
    buttonTexture.loadFromFile(buttonFile);
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(sf::Vector2f(x_axis, y_axis));
    buttonWidth = static_cast<float>(buttonSize.x);
    buttonHeight = static_cast<float>(buttonSize.y);
}

void Button::drawButton(sf::RenderWindow *window)
{
    window->draw(buttonSprite);
}

class Menu{
private:
    sf::Texture menuTexture;
    sf::RectangleShape menuShape;

public:
    Menu(string menuFile);
    void drawMenu(RenderWindow *window);
};

Menu::Menu(string menuFile)
{
    menuTexture.loadFromFile(menuFile);
    sf::Vector2u textureSize = menuTexture.getSize();
    float rectWidth = static_cast<float>(textureSize.x);
    float rectHeight = static_cast<float>(textureSize.y);

    menuShape.setSize(sf::Vector2f(rectWidth, rectHeight));
    menuShape.setTexture(&menuTexture);
};

void Menu::drawMenu(sf::RenderWindow *window)
{
    window->draw(menuShape);
}