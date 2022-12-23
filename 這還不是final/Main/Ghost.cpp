#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "./Headers/Global.h"
#include "./Headers/Pacman.h"
#include "./Headers/Ghost.h"
#include "./Headers/MapCollision.h"

Ghost::Ghost(unsigned char i_id) : id(i_id)
{
	switch (id)
	{
	case 0:
	{
		ghostTexture.loadFromFile("./Resources/Images/chi.png");
		break;
	}
	case 1:
	{
		ghostTexture.loadFromFile("./Resources/Images/ann.png");
		break;
	}
	case 2:
	{
		ghostTexture.loadFromFile("./Resources/Images/que.png");
		break;
	}
	case 3:
	{
		ghostTexture.loadFromFile("./Resources/Images/hua.png");
	}
	}
	ghostSpr.setTexture(ghostTexture);
	ghostSpr.setScale(sf::Vector2f(0.09, 0.09));
}

bool Ghost::pacman_collision(const Position &i_pacman_position)
{
	if (position.x > i_pacman_position.x - CELL_SIZE && position.x < CELL_SIZE + i_pacman_position.x)
	{
		if (position.y > i_pacman_position.y - CELL_SIZE && position.y < CELL_SIZE + i_pacman_position.y)
		{
			return 1;
		}
	}

	return 0;
}

float Ghost::get_target_distance(unsigned char i_direction)
{
	short x = position.x;
	short y = position.y;

	switch (i_direction)
	{
	case 0:
	{
		x += GHOST_SPEED;

		break;
	}
	case 1:
	{
		y -= GHOST_SPEED;

		break;
	}
	case 2:
	{
		x -= GHOST_SPEED;

		break;
	}
	case 3:
	{
		y += GHOST_SPEED;
	}
	}

	return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));
}

void Ghost::draw(sf::RenderWindow &i_window)
{
	ghostSpr.setPosition(position.x, position.y);
	i_window.draw(ghostSpr);
	animation_timer = (1 + animation_timer) % (GHOST_ANIMATION_FRAMES * GHOST_ANIMATION_SPEED);
}

void Ghost::reset(const Position &i_home, const Position &i_home_exit)
{
	movement_mode = 0;
	use_door = 0 < id;

	direction = 0;
	frightened_mode = 0;
	frightened_speed_timer = 0;

	animation_timer = 0;

	home = i_home;
	home_exit = i_home_exit;
	target = i_home_exit;
}

void Ghost::set_position(short i_x, short i_y)
{
	position = {i_x, i_y};
}

void Ghost::switch_mode()
{
	movement_mode = 1 - movement_mode;
}

void Ghost::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map, Ghost &i_ghost_0, Pacman &i_pacman)
{
	bool move = 0;

	unsigned char available_ways = 0;
	unsigned char speed = GHOST_SPEED;

	std::array<bool, 4> walls{};

	if (0 == frightened_mode && i_pacman.get_energizer_timer() == ENERGIZER_DURATION / pow(2, i_level))
	{
		frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

		frightened_mode = 1;
	}
	else if (0 == i_pacman.get_energizer_timer() && 1 == frightened_mode)
	{
		frightened_mode = 0;
	}

	if (2 == frightened_mode && 0 == position.x % GHOST_ESCAPE_SPEED && 0 == position.y % GHOST_ESCAPE_SPEED)
	{
		speed = GHOST_ESCAPE_SPEED;
	}

	update_target(i_pacman.get_direction(), i_ghost_0.get_position(), i_pacman.get_position());

	walls[0] = map_collision(0, use_door, speed + position.x, position.y, i_map);
	walls[1] = map_collision(0, use_door, position.x, position.y - speed, i_map);
	walls[2] = map_collision(0, use_door, position.x - speed, position.y, i_map);
	walls[3] = map_collision(0, use_door, position.x, speed + position.y, i_map);

	if (1 != frightened_mode)
	{
		unsigned char optimal_direction = 4;

		move = 1;

		for (unsigned char a = 0; a < 4; a++)
		{
			if (a == (2 + direction) % 4)
			{
				continue;
			}
			else if (0 == walls[a])
			{
				if (4 == optimal_direction)
				{
					optimal_direction = a;
				}

				available_ways++;

				if (get_target_distance(a) < get_target_distance(optimal_direction))
				{
					optimal_direction = a;
				}
			}
		}

		if (1 < available_ways)
		{
			direction = optimal_direction;
		}
		else
		{
			if (4 == optimal_direction)
			{
				direction = (2 + direction) % 4;
			}
			else
			{
				direction = optimal_direction;
			}
		}
	}
	else
	{
		unsigned char random_direction = rand() % 4;

		if (0 == frightened_speed_timer)
		{
			move = 1;

			frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

			for (unsigned char a = 0; a < 4; a++)
			{
				if (a == (2 + direction) % 4)
				{
					continue;
				}
				else if (0 == walls[a])
				{
					available_ways++;
				}
			}

			if (0 < available_ways)
			{
				while (1 == walls[random_direction] || random_direction == (2 + direction) % 4)
				{
					random_direction = rand() % 4;
				}

				direction = random_direction;
			}
			else
			{
				direction = (2 + direction) % 4;
			}
		}
		else
		{
			frightened_speed_timer--;
		}
	}

	if (1 == move)
	{
		switch (direction)
		{
		case 0:
		{
			position.x += speed;

			break;
		}
		case 1:
		{
			position.y -= speed;

			break;
		}
		case 2:
		{
			position.x -= speed;

			break;
		}
		case 3:
		{
			position.y += speed;
		}
		}

		if (-CELL_SIZE >= position.x)
		{
			position.x = CELL_SIZE * MAP_WIDTH - speed;
		}
		else if (position.x >= CELL_SIZE * MAP_WIDTH)
		{
			position.x = speed - CELL_SIZE;
		}
	}

	if (1 == pacman_collision(i_pacman.get_position()))
	{
		if (0 == frightened_mode)
		{
			i_pacman.set_dead(1);
		}
		else
		{
			use_door = 1;

			frightened_mode = 2;

			target = home;
		}
	}
}

void Ghost::update_target(unsigned char i_pacman_direction, const Position &i_ghost_0_position, const Position &i_pacman_position)
{
	if (1 == use_door)
	{
		if (position == target)
		{
			if (home_exit == target)
			{
				use_door = 0;
			}
			else if (home == target)
			{
				frightened_mode = 0;

				target = home_exit;
			}
		}
	}
	else
	{
		if (0 == movement_mode)
		{
			switch (id)
			{
			case 0:
			{
				target = {CELL_SIZE * (MAP_WIDTH - 1), 0};

				break;
			}
			case 1:
			{
				target = {0, 0};

				break;
			}
			case 2:
			{
				target = {CELL_SIZE * (MAP_WIDTH - 1), CELL_SIZE * (MAP_HEIGHT - 1)};

				break;
			}
			case 3:
			{
				target = {0, CELL_SIZE * (MAP_HEIGHT - 1)};
			}
			}
		}
		else
		{
			switch (id)
			{
			case 0:
			{
				target = i_pacman_position;

				break;
			}
			case 1:
			{
				target = i_pacman_position;

				switch (i_pacman_direction)
				{
				case 0:
				{
					target.x += CELL_SIZE * GHOST_1_CHASE;

					break;
				}
				case 1:
				{
					target.y -= CELL_SIZE * GHOST_1_CHASE;

					break;
				}
				case 2:
				{
					target.x -= CELL_SIZE * GHOST_1_CHASE;

					break;
				}
				case 3:
				{
					target.y += CELL_SIZE * GHOST_1_CHASE;
				}
				}

				break;
			}
			case 2:
			{
				target = i_pacman_position;

				switch (i_pacman_direction)
				{
				case 0:
				{
					target.x += CELL_SIZE * GHOST_2_CHASE;

					break;
				}
				case 1:
				{
					target.y -= CELL_SIZE * GHOST_2_CHASE;

					break;
				}
				case 2:
				{
					target.x -= CELL_SIZE * GHOST_2_CHASE;

					break;
				}
				case 3:
				{
					target.y += CELL_SIZE * GHOST_2_CHASE;
				}
				}

				target.x += target.x - i_ghost_0_position.x;
				target.y += target.y - i_ghost_0_position.y;

				break;
			}
			case 3:
			{
				if (CELL_SIZE * GHOST_3_CHASE <= sqrt(pow(position.x - i_pacman_position.x, 2) + pow(position.y - i_pacman_position.y, 2)))
				{
					target = i_pacman_position;
				}
				else
				{
					target = {0, CELL_SIZE * (MAP_HEIGHT - 1)};
				}
			}
			}
		}
	}
}

Position Ghost::get_position()
{
	return position;
}
