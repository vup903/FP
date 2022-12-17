#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

class Game
{
	private:
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;
		
		sf::Texture ghostTexture;
    	sf::Sprite ghostSpr;
    	
    	sf::Texture pacTexture;
    	sf::Sprite pacSpr;
    	sf::Sprite foodSpr;
    	sf::Texture foodTexture;
    	
    	
    	int points;
    	float enemySpawnTimer;
    	float enemySpawnTimerMax;
    	int maxEnemies;

    	float foodSpawnTimer;
    	float foodSpawnTimerMax;
    	int maxFoods;
    	
    	bool endGame = 0;
    	
    	vector<sf::Sprite> foods;
    	vector<sf::Sprite> enemies;
		
		void initVariables();
		void initWindow();
		void initEnemies(string);
		void initPac(string);
		void initFood(string);
		
	public:
		Game(){
			this -> initVariables();
			this -> initWindow();
			this -> initPac("C:/Users/Hsiang/Desktop/test/image/main.png");
			this -> initEnemies("C:/Users/Hsiang/Desktop/test/image/anne.png");
			this -> initFood("C:/Users/Hsiang/Desktop/test/image/food.png");
		}
		~Game(){
			delete this -> window;
		}
		
		const bool running() const;
		
		void update();
		void render();
		void spawnEnemy();
		void updateEnemies();
		void renderEnemies();
		void updatePac();
		void renderPac();
		void spawnFood();
		void updateFoods();
		void renderFoods();
		
		
		void pollEvents();
};


