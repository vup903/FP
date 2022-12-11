#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

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
};

Button::Button(string buttonFile, float x_axis, float y_axis)
{
    buttonTexture.loadFromFile(buttonFile);
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(sf::Vector2f(x_axis, y_axis));
    buttonWidth = static_cast<float>(buttonSize.x);
    buttonHeight = static_cast<float>(buttonSize.y);
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(1890, 1417), "PAC MAN IN IMPERIAL HAREN", sf::Style::Close);
    sf::Event event;

    sf::Texture menuTexture;
    //圖片檔的絕對路徑
    menuTexture.loadFromFile("/Users/lbjessie/Desktop/首頁.png");

    sf::Vector2u textureSize = menuTexture.getSize();
    float rectWidth = static_cast<float>(textureSize.x);
    float rectHeight = static_cast<float>(textureSize.y);

    sf::RectangleShape menuShape(sf::Vector2f(rectWidth, rectHeight));
    menuShape.setTexture(&menuTexture);

    //圖片檔的絕對路徑
    Button startGame("/Users/lbjessie/Desktop/startGame.png", 400, 900);
    Button gameRule("/Users/lbjessie/Desktop/gameRule.png", 1100, 900);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(menuShape);
        window.draw(startGame.getSprite());
        window.draw(gameRule.getSprite());
        window.display();
    }

    return 0;
}
