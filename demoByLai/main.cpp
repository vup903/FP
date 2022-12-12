#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "./maze.h"
#include "./button.h"
#include "./background.h"
#include "./ghost.h"
#include "./pac.h"
#include "./scoreBoard.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1890, 1417), "PAC MAN IN IMPERIAL HAREN", sf::Style::Close);
    sf::Event event;

    /*宣告的部分*/
    /*fileName放圖檔的絕對路徑*/

    //地圖宣告
    Maze maze("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/磚牆素材.png");
    Ghost que("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/皇后方形.png", 55, 55);
    Ghost ann("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/安陵容方形.png", 1155, 1265);
    Ghost hua("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/華妃方形.png", 1155, 55);
    Ghost chi("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/齊妃方形.png", 55, 1265);
    Pac pac("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/甄嬛方形.png", 605, 605);

    //首頁宣告
    Background menuImage("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/首頁.png");
    Button startGame("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/startGame.png", 400, 900);
    Button gameRule("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/gameRule.png", 1100, 900);

    //勝利畫面
    Background winImage("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/勝利畫面.png");
    Button reStart("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/重新開始.png", 1350, 1200);

    //失敗畫面
    Background loseImage("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/失敗畫面.png");
    //Button reStart("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/重新開始.png", 1350, 1200);

    ScoreBoard scoreBoard;
    float i = 0;
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //看遊戲畫面
        /*
        maze.drawWall(&window);
        que.drawGhost(&window);
        ann.drawGhost(&window);
        hua.drawGhost(&window);
        chi.drawGhost(&window);
        pac.drawPac(&window);
        scoreBoard.drawScoreBoard(i, &window);
         */

        //看首頁
        /*
        menuImage.drawbg(&window);
        startGame.drawButton(&window);
        gameRule.drawButton(&window);
         */

        //看勝利畫面

        winImage.drawbg(&window);
        reStart.drawButton(&window);


        //看失敗畫面
        /*
        loseImage.drawbg(&window);
        reStart.drawButton(&window);
         */

        window.display();
    }
    return 0;
}
