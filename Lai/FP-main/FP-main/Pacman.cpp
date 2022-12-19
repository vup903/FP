#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "./Headers/Global.h"
#include "./Headers/Pacman.h"
#include "./Headers/MapCollision.h"

Pacman::Pacman()
{
    animation_over = false;
    dead = false;
    direction = false;
    energizer_timer = false;
    position.x = 0;
    position.y = 0;
    //路徑要調
    pacTexture.loadFromFile("Resources/image/甄嬛方形.png");
    pacSpr.setTexture(pacTexture);
    //setScale可能要多試幾次 不同電腦的視窗大小好像會不一樣 但用這個函數畫質應該不會降低
    pacSpr.setScale(sf::Vector2f(0.1, 0.1));
}

bool Pacman::get_animation_over()
{
	return animation_over;
}

bool Pacman::get_dead()
{
	return dead;
}

unsigned char Pacman::get_direction()
{
	return direction;
}

unsigned short Pacman::get_energizer_timer()
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));
	pacSpr.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory)
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
		{
			animation_timer++;
			i_window.draw(pacSpr);
		}
		else
		{
			animation_over = 1;
		}
	}
	else
	{
        i_window.draw(pacSpr);
		animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
	}
}

void Pacman::reset()
{
	animation_over = 0;
	dead = 0;
	direction = 0;
	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer)
{
	animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead)
{
	dead = i_dead;

	if (1 == dead)
	{
		//Making sure that the animation starts from the beginning.
		animation_timer = 0;
	}
}

void Pacman::set_position(short i_x, short i_y)
{
	position = {i_x, i_y};
}

void Pacman::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	std::array<bool, 4> walls{};
	walls[0] = map_collision(0, 0, PACMAN_SPEED + position.x, position.y, i_map);
	walls[1] = map_collision(0, 0, position.x, position.y - PACMAN_SPEED, i_map);
	walls[2] = map_collision(0, 0, position.x - PACMAN_SPEED, position.y, i_map);
	walls[3] = map_collision(0, 0, position.x, PACMAN_SPEED + position.y, i_map);

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
		{
			direction = 0;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction])
	{
		switch (direction)
		{
			case 0:
			{
				position.x += PACMAN_SPEED;

				break;
			}
			case 1:
			{
				position.y -= PACMAN_SPEED;

				break;
			}
			case 2:
			{
				position.x -= PACMAN_SPEED;

				break;
			}
			case 3:
			{
				position.y += PACMAN_SPEED;
			}
		}
	}

	if (-CELL_SIZE >= position.x)
	{
		position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	}
	else if (CELL_SIZE * MAP_WIDTH <= position.x)
	{
		position.x = PACMAN_SPEED - CELL_SIZE;
	}

	if (1 == map_collision(1, 0, position.x, position.y, i_map)) //When Pacman eats an energizer...
	{
		//He becomes energized!
		energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));
	}
	else
	{
		energizer_timer = std::max(0, energizer_timer - 1);
	}
}

Position Pacman::get_position()
{
	return position;
}
