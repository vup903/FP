#pragma once
#include <iostream>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Ghost
{
    sf::Texture ghostTexture;
    sf::Sprite ghostSpr;

	bool movement_mode;
	bool use_door;

	unsigned char direction;
	unsigned char frightened_mode;
	unsigned char frightened_speed_timer;
	unsigned char id;
	unsigned short animation_timer;

	Position home;
	Position home_exit;
	Position position;
	Position target;
public:
	Ghost(unsigned char i_id);
    void init();

	bool pacman_collision(const Position& i_pacman_position);

	float get_target_distance(unsigned char i_direction);

	void draw(sf::RenderWindow& i_window);
	void reset(const Position& i_home, const Position& i_home_exit);
	void set_position(short i_x, short i_y);
	void switch_mode();
	void update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman);
	void update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position);

	Position get_position();
};