#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "./Headers/Global.h"
#include "./Headers/DrawText.h"
#include "./Headers/Pacman.h"
#include "./Headers/Ghost.h"
#include "./Headers/GhostManager.h"
#include "./Headers/ConvertSketch.h"
#include "./Headers/DrawMap.h"
#include "./Headers/MapCollision.h"
#include "./Headers/background.h"
#include "./Headers/button.h"
#include "./Headers/scoreBoard.h"

sf::Keyboard keyboard;
sf::Mouse mouse; //336*352
sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
// 首頁宣告
Background menuImage("/Users/lbjessie/Downloads/FP-main/FP-main/Resources/Images/mainpage.png");
Button startGame("/Users/lbjessie/Downloads/FP-main/FP-main/Resources/Images/startGame.png", 36, 230);
Button gameRule("/Users/lbjessie/Downloads/FP-main/FP-main/Resources/Images/gameRule.png", 200, 230);

// 勝利畫面
Background winImage("/Users/lbjessie/Downloads/FP-main/FP-main/Resources/Images/win.png");
Button reStart("/Users/lbjessie/Downloads/FP-main/FP-main/Resources/Images/restart.png", 200, 300);

// 失敗畫面
Background loseImage("/Users/lbjessie/Downloads/FP-main/FP-main/Resources/Images/lose.png");
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
	int exp = 0;
	// Is the game won?
	bool game_won = 0;

	// Used to make the game framerate-independent.
	unsigned lag = 0;

	unsigned char level = 0;
	// Resizing the window. //672*704
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	// Similar to lag, used to make the game framerate-independent.
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	// It's not exactly like the map from the original Pac-Man game, but it's close enough.
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

	// Initial ghost positions.
	std::array<Position, 4> ghost_positions;

	// SFML thing. Stores events, I think.
	sf::Event event;


	GhostManager ghost_manager;

	Pacman pacman;

	// Generating a random seed.
	srand(static_cast<unsigned>(time(0)));

	map = convert_sketch(map_sketch, ghost_positions, pacman);

	ghost_manager.reset(level, ghost_positions);

	// Get the current time and store it in a variable.
	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		window.clear(sf::Color::Black);
		SwitchUI(exp, type);
		while (window.pollEvent(event))
        {
            if (event.type == event.Closed)
                window.close();
                
            if (mouse.isButtonPressed(mouse.Left) and mouse.getPosition(window).x >= 72 and mouse.getPosition(window).y >= 460 and mouse.getPosition(window).x <= 272 and mouse.getPosition(window).y <= 536 and type == 1)
            {
                type = 2;
				map = convert_sketch(map_sketch, ghost_positions, pacman);
				ghost_manager.reset(level, ghost_positions);
				pacman.reset();
				lag =0;
				level = 0;
				game_won = 0;
            }
            else if (mouse.isButtonPressed(mouse.Left) and mouse.getPosition(window).x >= 400 and mouse.getPosition(window).y >= 600 and mouse.getPosition(window).x <= 600 and mouse.getPosition(window).y <= 676 and (type == 3 or type == 4))
            {
                type = 1;
            }

            if (event.type == event.KeyPressed)
            {
                if (event.key.code == keyboard.Escape) //按ESC離開遊戲
                {
                    window.close();
                }
            }
        }
		while (type == 2)
		{
			{
				// Here we're calculating the lag.
				unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

				lag += delta_time;

				previous_time += std::chrono::microseconds(delta_time);

				// While the lag exceeds the maximum allowed frame duration.
				while (FRAME_DURATION <= lag)
				{
					// We decrease the lag.
					lag -= FRAME_DURATION;

					while (1 == window.pollEvent(event))
					{
						switch (event.type)
						{
						case sf::Event::Closed:
						{
							// Making sure the player can close the window.
							window.close();
						}
						}
					}

					if (0 == game_won && 0 == pacman.get_dead())
					{
						game_won = 1;

						pacman.update(level, map);

						ghost_manager.update(level, map, pacman);

						// We're checking every cell in the map.
						for (const std::array<Cell, MAP_HEIGHT> &column : map)
						{
							for (const Cell &cell : column)
							{
								if (Cell::Pellet == cell) // And if at least one of them has a pellet.
								{
									game_won = 0; // The game is not yet won.

									break;
								}
							}

							if (0 == game_won)
							{
								break;
							}
						}

						if (1 == game_won)
						{
							pacman.set_animation_timer(0);
						}
					}
					else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) // Restarting the game.
					{
						game_won = 0;

						if (1 == pacman.get_dead())
						{
							level = 0;
						}
						else
						{
							// After each win we reduce the duration of attack waves and energizers.
							level++;
						}

						map = convert_sketch(map_sketch, ghost_positions, pacman);

						ghost_manager.reset(level, ghost_positions);

						pacman.reset();
					}

					// I don't think anything needs to be explained here.
					if (FRAME_DURATION > lag)
					{
						window.clear();

						if (0 == game_won && 0 == pacman.get_dead())
						{
							draw_map(map, window);

							ghost_manager.draw(window);

							draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Level: " + std::to_string(1 + level), window);
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
			}
			window.display();
		}
		if(type != 2){
			window.display();
		}
	}
}