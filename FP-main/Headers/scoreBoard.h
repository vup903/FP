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
    float score;

public:
    ScoreBoard();
    void drawScoreBoard(float score, RenderWindow *window);
};

ScoreBoard::ScoreBoard()
{
    score = 50;
    font.loadFromFile("/Users/lbjessie/Desktop/大三上/程式設計/demo/54938565040.ttf");
    text.setFont(font);
    text.setCharacterSize(60);
    text.setStyle(Text::Bold);
    text.setString(std::to_string(score));
    text.setPosition(sf::Vector2f(1300, 1265));
}

void ScoreBoard::drawScoreBoard(float score, sf::RenderWindow *window)
{
    text.setString(std::to_string(score));
    window->draw(text);
}