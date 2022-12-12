#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "./maze.h"
#include "./menu.h"
#include "./ghost.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1890, 1417), "PAC MAN IN IMPERIAL HAREN", sf::Style::Close);
    sf::Event event;

    /*宣告的部分*/
    /*fileName放圖黨的絕對路徑*/
    Maze maze("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/磚牆素材.png");

    Ghost que("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/皇后方形.png", 55, 55);
    Ghost ann("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/安陵容方形.png", 1155, 1265);
    Ghost hua("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/華妃方形.png", 1155, 55);
    Ghost chi("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/齊妃方形.png", 55, 1265);

    Menu menu("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/首頁.png");
    Button startGame("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/startGame.png", 400, 900);
    Button gameRule("/Users/lbjessie/Desktop/大三上/程式設計/demo/image/gameRule.png", 1100, 900);

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*如果要看迷宮，就用這段程式碼
        maze.drawWall(&window);
         */

        /*如果要看幽靈，就用這段程式碼，可以跟迷宮一起看
        que.drawGhost(&window);
        ann.drawGhost(&window);
        hua.drawGhost(&window);
        chi.drawGhost(&window);
         */

        /*如果要看首頁，就用這段程式碼，不能跟迷宮和幽靈一起看，會重疊，到時候應該要寫按鈕事件切換
        startGame.drawButton(&window);
        gameRule.drawButton(&window);
        menu.drawMenu(&window);
         */
        window.display();
    }

    return 0;
}