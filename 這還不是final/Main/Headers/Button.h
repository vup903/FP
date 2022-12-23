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

public:
    Button(string buttonFile, float, float);
    void drawButton(sf::RenderWindow *window){ window->draw(buttonSprite); }
    bool buttonPressed(sf::Vector2f mousePos);
};