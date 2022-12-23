#pragma once
#include <iostream>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/*如果要看精靈，main.cpp我有用註解寫，拿掉註解就可以了*/
class ScoreBoard{
private:
    sf::Font font;
    sf::Text text;

public:
    ScoreBoard();
    void drawScoreBoard(int score, RenderWindow *window);
};

ScoreBoard::ScoreBoard()
{
    font.loadFromFile("54938565040.ttf");
    text.setFont(font);
    text.setCharacterSize(10);
    text.setStyle(Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(10, 320));
}

void ScoreBoard::drawScoreBoard(int score, sf::RenderWindow *window)
{
    text.setString("Score: " + std::to_string(score));
    window->draw(text);
}
