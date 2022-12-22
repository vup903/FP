#include "./Button.h"

Button::Button(std::string buttonFile, float x_axis, float y_axis)
{
    buttonTexture.loadFromFile(buttonFile);
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setScale(sf::Vector2f(0.26, 0.26));
    buttonSprite.setPosition(sf::Vector2f(x_axis, y_axis));
}

bool Button::buttonPressed(sf::Vector2f mousePos)
{
    return(buttonSprite.getGlobalBounds().contains(mousePos));
}