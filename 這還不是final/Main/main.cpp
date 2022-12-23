#include <array>
#include <chrono>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>

#include "./Headers/Global.h"
#include "./Headers/Pacman.h"
#include "./Headers/Background.hpp"
#include "./Headers/Ghost.h"
#include "./Headers/GhostManager.h"
#include "./Headers/ConvertSketch.h"
#include "./Headers/DrawMap.h"
#include "./Headers/Button.h"
#include "./Headers/ScoreBoard.hpp"

string path = "./Resources/Images/";
sf::Keyboard keyboard;
sf::Mouse mouse;
sf::RenderWindow window(sf::VideoMode(CELL_SIZE *MAP_WIDTH *SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "PacMan in Imperial Haren", sf::Style::Close);

// 首頁宣告
Background menuImage(path + "mainpage.png");
Button startGame(path + "startGame.png", 36, 230);
Button stopGame(path + "stopGame.png", 196, 230);

// 勝利畫面
Background winImage(path + "win.png");
Button reStart(path + "restart.png", 196, 242);

// 失敗畫面
Background loseImage(path + "lose.png");
ScoreBoard scoreBoard;

void SwitchUI(int num, int type) // 切換UI： 1, 2, 3, 4, 分別代表menu, playing, win, lose
{
	switch (type)
	{
	case 1:
		menuImage.drawbg(&window);
		startGame.drawButton(&window);
		stopGame.drawButton(&window);
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
	int type = 1;
	int score;
	bool game_won = 0;
	unsigned lag = 0;
	unsigned char level = 0;

	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	std::array<std::string, MAP_HEIGHT> map_sketch = {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "};

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	std::array<Position, 4> ghost_positions;

	sf::Event event;

	GhostManager ghost_manager;

	Pacman pacman;

	srand(static_cast<unsigned>(time(0)));

	map = convert_sketch(map_sketch, ghost_positions, pacman);

	ghost_manager.reset(level, ghost_positions);

	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		window.clear(sf::Color::Black);
		SwitchUI(score, type);
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();

            if(mouse.isButtonPressed(mouse.Left))
            {
                if (type == 1)
                {
                    if (startGame.buttonPressed(window.mapPixelToCoords(mouse.getPosition(window))))
                    {
                        lag = 0;
                        level = 0;
                        game_won = 0;
                        type = 2;
                    }
                    if (stopGame.buttonPressed(window.mapPixelToCoords(mouse.getPosition(window))))
                    {
                        window.close();
                    }
                }
                else if (type == 3 or type == 4)
                {
                    if (reStart.buttonPressed(window.mapPixelToCoords(mouse.getPosition(window))))
                        type = 1;
                }
            }

			// 按ESC離開遊戲
			if (event.type == event.KeyPressed)
			{
				if (event.key.code == keyboard.Escape)
				{
					window.close();
				}
			}
		}
		while (type == 2)
		{
			unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();
			score = 185;
			lag += delta_time;

			previous_time += std::chrono::microseconds(delta_time);

			while (FRAME_DURATION <= lag)
			{
				lag -= FRAME_DURATION;

				while (1 == window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
					{
						window.close();
					}
					}
				}

				if (0 == game_won && 0 == pacman.get_dead())
				{
					game_won = 1;

					pacman.update(level, map);

					ghost_manager.update(level, map, pacman);

					// 檢查每個cell，如果還有豆豆存在即未勝利
					for (const std::array<Cell, MAP_HEIGHT> &column : map)
					{
						for (const Cell &cell : column)
						{
							if (Cell::Pellet == cell)
							{
								game_won = 0;
								score -= 1;
							}
							if (Cell::Energizer == cell)
							{
								game_won = 0;
								score -= 10;
							}
						}
					}
					if (1 == game_won)
					{
						pacman.set_animation_timer(0);
					}
				}
				if (mouse.isButtonPressed(mouse.Left))
                    if (startGame.buttonPressed(window.mapPixelToCoords(mouse.getPosition(window))))
                    {
                        game_won = 0;

                        map = convert_sketch(map_sketch, ghost_positions, pacman);

                        ghost_manager.reset(level, ghost_positions);

                        pacman.reset();
                    }

				if (FRAME_DURATION > lag)
				{
					window.clear();

					if (0 == game_won && 0 == pacman.get_dead())
					{
						draw_map(map, window);

						ghost_manager.draw(window);

                        scoreBoard.drawScoreBoard(score, &window);
                    }

					pacman.draw(game_won, window);

					if (1 == pacman.get_animation_over())
					{
						if (1 == game_won)
						{
							type = 3;
						}
						else
						{
							type = 4;
						}
					}
				}
			}
			window.display();
		}
		if (type != 2)
		{
			window.display();
		}
	}
}
