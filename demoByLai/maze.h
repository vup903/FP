#pragma once
#include <iostream>
#include <string>
#include <array>
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/*如果要看迷宮，main.cpp我有用註解寫，拿掉註解就可以了*/
class Maze
{
private:
    sf::RectangleShape wallShapeArr[23*24];
    static int mazeW, mazeH;
    int wallShapeCount = 0;
    sf::Texture wallTexture;

    bool isDot(string str);
    RectangleShape getWallShape(int col,int row,sf::RectangleShape wallShape);
    CircleShape getDots(int col, int row, string str);

public:     
    static Maze* instance;
    string mazePattern[25] =
    { "#######################" , // 0   // #= Bricks
      "#Q   S    W#Q    S   W#" , // 1   // X= Ghosts direction condition
      "#@### #### # #### ###@#" , // 2   // c= Pacman char
      "# ### #### # #### ### #" , // 3   // Q=RD
      "#D   X S  A A  S X   F#" , // 4   // W=LD
      "# ### # ####### # ### #" , // 5   // E=RU
      "#E   F# ####### #D   R#" , // 6   // R=LU
      "##### #E  W#Q  R# #####" , // 7   //-------
      "##### #### # #### #####" , // 8   // A=LRU 
      "##### #Q  AGA  W# #####" , // 9   // S=LRD
      "##### # ###-### # #####" , // 10  // D=UDR
      "0====X F#BP*IC#D X====0" , // 11  // F=UDL
      "##### # ####### # #####" , // 12  // G=LR   
      "##### #D0001000F# #####" , // 13  // 1=Fruit location
      "##### # ####### # #####" , // 14  // L=Low speed in tunel for ghosts
      "##### # ####### # #####" , // 15  // BPIC=Ghosts char
      "#Q   X A  W#Q  A X   W#" , // 16
      "# ### #### # #### ### #" , // 17
      "#E W#D S  AcA  S F#Q R#" , // 18
      "### # # ####### # # ###" , // 19
      "#Q A R#E  W#Q  R#E A W#" , // 20
      "# ######## # ######## #" , // 24
      "#@######## # ########@#" , // 22
      "#E        A A        R#" , // 23
      "#######################" };// 24
    // 01234567890123456789012 
     
    string mazeGrid[23][25];
    CircleShape  dotsArr[222]; // 222 dots
    int dotsCount = 0;

    Maze(string fileName);
    ~Maze(){};

    void initMaze(string fileName);
    void drawWall(RenderWindow *window);
    void redrawDot();
};

Maze::Maze(string fileName)
{
    cout << "Maze class OK"<<endl;
    initMaze(fileName);
    instance = this;
}

bool Maze::isDot(string str)
{
    return str != "0" && str != "=" &&
           str != "B" && str != "P" &&
           str != "I" && str != "C" &&
           str != "G" && str != "*" &&
           str != "1" && str != "-" && str!="c";
}

RectangleShape Maze::getWallShape(int col,int row,sf::RectangleShape wallShape)
{
    wallShape.setPosition(col*55, row*55);
    return wallShape;
}

CircleShape Maze::getDots(int col, int row, string str)
{
    float radius = 3;  int offset = 12;
    Color color = Color::Yellow;
    if (str == "@")
    {
        radius = 10; offset = 6;
    }
    CircleShape _dot;
    _dot.setRadius(radius);
    _dot.setFillColor(color);
    _dot.setPosition(col * 55 + offset, row * 55 + offset);
    return _dot;
}

void Maze::initMaze(string fileName)
{
    int colum = 0; int row = 0;
    wallTexture.loadFromFile(fileName, sf::IntRect(0, 0, 400, 400));
    sf::RectangleShape wallShape(sf::Vector2f (55, 55));
    wallShape.setTexture(&wallTexture);

    for (int i = 0; i < (Maze::mazeW*Maze::mazeH); i++)
    {
        if (colum >= Maze::mazeW)
        {
            colum = 0; row++;
            // cout << mazePattern[row] << endl;
        }
        string str = mazePattern[row].substr(colum, 1);
        mazeGrid[colum][row] = str;
        if (str == "#")
        {
            wallShapeArr[wallShapeCount] = getWallShape(colum,row,wallShape);
            wallShapeCount++;
        }
        else
        {
            if (isDot(str))
            {
                dotsArr[dotsCount] = getDots(colum, row, str);
                dotsCount++;
            }
        }
        colum++;
    }
}

void Maze::drawWall( RenderWindow *window )
{
    int i = 0;
    for ( i = 0; i < wallShapeCount; i++)
    {
        window->draw (wallShapeArr[i]);
        if (i < dotsCount)
        {
            window->draw(dotsArr[i]);
        }
    }
}

void Maze::redrawDot()
{
    for (int i = 0; i < dotsCount; i++)
    {
        CircleShape dot = dotsArr[i];
        dot.setFillColor(Color::Yellow);
        dotsArr[i] = dot;
    }
}

Maze *Maze::instance;
int Maze::mazeW = 23;
int Maze::mazeH = 25;
