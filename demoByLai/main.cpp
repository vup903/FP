#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "./maze.h"
#include "./button.h"
#include "./background.h"
#include "./ghost.h"
#include "./pac.h"
#include "./scoreBoard.h"

using namespace std;

sf::RenderWindow window(sf::VideoMode(1890, 1417), "PAC MAN IN IMPERIAL HAREN", sf::Style::Close);
sf::Event event;
sf::Keyboard keyboard;
sf::Mouse mouse;

/*宣告的部分*/
/*fileName放圖檔的絕對路徑*/

// 地圖宣告
Maze maze("demo/Image/image/wall.png");
Ghost que("demo/Image/image/que.png", 55, 55);
Ghost ann("demo/Image/image/ann.png", 1155, 1265);
Ghost hua("demo/Image/image/hua.png", 1155, 55);
Ghost chi("demo/Image/image/chi.png", 55, 1265);
Pac pac("demo/Image/image/pac.png", 605, 605);

// 首頁宣告
Background menuImage("demo/Image/image/mainpage.png");
Button startGame("demo/Image/image/startGame.png", 400, 900);
Button gameRule("demo/Image/image/gameRule.png", 1100, 900);

// 勝利畫面
Background winImage("demo/Image/image/win.png");
Button reStart("demo/Image/image/restart.png", 1350, 1200);

// 失敗畫面
Background loseImage("demo/Image/image/lose.png");
// Button reStart("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/重新開始.png", 1350, 1200);

ScoreBoard scoreBoard;

void SwitchUI(int num, int type) // 切換UI： 1, 2, 3, 4, 分別代表menu, playing, win, lose
{
    switch (type)
    {
    case 1:
        menuImage.drawbg(&window);
        startGame.drawButton(&window);
        gameRule.drawButton(&window);
        break;
    case 2:
        maze.drawWall(&window);
        que.drawGhost(&window);
        ann.drawGhost(&window);
        hua.drawGhost(&window);
        chi.drawGhost(&window);
        pac.drawPac(&window);
        scoreBoard.drawScoreBoard(num, &window);
        break;
    case 3:
        winImage.drawbg(&window);
        reStart.drawButton(&window);
        break;
    case 4:
        loseImage.drawbg(&window);
        reStart.drawButton(&window);
        break;
    }
}

int main()
{

    float exp = 50;
    int type = 1;
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        SwitchUI(exp, type);
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed)
                window.close();

            if (mouse.isButtonPressed(mouse.Left) and mouse.getPosition(window).x >= 400 and mouse.getPosition(window).y >= 900 and mouse.getPosition(window).x <= 800 and mouse.getPosition(window).y <= 1050 and type == 1)
            {
                type = 2;
            }
            else if (mouse.isButtonPressed(mouse.Left) and mouse.getPosition(window).x >= 1350 and mouse.getPosition(window).y >= 1200 and mouse.getPosition(window).x <= 1750 and mouse.getPosition(window).y <= 1350 and (type == 3 or type == 4))
            {
                type = 1;
            }

            if (event.type == event.KeyPressed)
            {
                if (event.key.code == keyboard.Escape) // 按ESC離開遊戲
                {
                    window.close();
                }
                else if (event.key.code == keyboard.D) // 條件應改為經驗值>=100
                {
                    type = 3;
                }
                else if (event.key.code == keyboard.F) // 條件應改為經驗值<=0
                {
                    type = 4;
                }
            }
        }
        window.display();
    }
    return 0;
}
