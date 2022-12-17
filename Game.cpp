#include "Game.h"

void Game::initVariables(){
	this -> window = nullptr;
	this -> points = 0;
	this -> enemySpawnTimerMax = 100.f;
	this -> enemySpawnTimer = this -> enemySpawnTimerMax;
	this -> maxEnemies = 10;
	
	this -> foodSpawnTimerMax = 10.f;
	this -> foodSpawnTimer = this -> foodSpawnTimerMax;
	this -> maxFoods = 20;
}

void Game::initWindow(){
	this -> videoMode.height = 1417;
	this -> videoMode.width = 1890;
	this -> window = new sf::RenderWindow(this -> videoMode, "PAC MAN IN IMPERIAL HAREN", sf::Style::Close);
	this -> window -> setFramerateLimit(60);
}

const bool Game::running() const{
	if(endGame == 0){
		return this -> window -> isOpen();
	}
	else{
		return 0;
	}
}

void Game::pollEvents(){
	while(this -> window -> pollEvent(this -> ev)){
		switch(this -> ev.type){
			case sf::Event::Closed:
				this -> window -> close();
				break;
		}
	}
}

void Game::update(){
	this -> pollEvents();
	
	this -> updateEnemies();
	this -> updateFoods();
	
	this -> updatePac();
}

void Game::render(){
	this -> window -> clear();
	
	this -> renderFoods();
	this -> renderEnemies();
	this -> renderPac();
	
	this -> window -> display();
}

void Game::initEnemies(string ghostFile){
	this -> ghostTexture.loadFromFile(ghostFile);
    this -> ghostSpr.setTexture(ghostTexture);
    this -> ghostSpr.setScale(sf::Vector2f(0.1, 0.1));
}

void Game::spawnEnemy(){
	this -> ghostSpr.setPosition(
		static_cast<float>(rand() % static_cast<int>((this -> window -> getSize().x) - (this -> ghostSpr.getTexture()->getSize().x * ghostSpr.getScale().x))),
		0
	);
	
	this -> enemies.push_back(this -> ghostSpr);
}

void Game::updateEnemies(){
	
	if(this -> enemies.size() < this -> maxEnemies){
		if(this -> enemySpawnTimer >= this -> enemySpawnTimerMax){
			this -> spawnEnemy();
			this -> enemySpawnTimer = 0.f;
		}
		else{
			this -> enemySpawnTimer += 1.f;
		}
	}
	
	for(int i = 0; i < this -> enemies.size(); i++){
		bool deleted = false;
		
		this -> enemies[i].move(1, 1);
		
		if(this -> pacSpr.getGlobalBounds().intersects(this -> enemies[i].getGlobalBounds())){
			endGame = 1;
		}
		
		if(this -> enemies[i].getPosition().x > 1900){
			deleted = true;
		}
		else if(this -> enemies[i].getPosition().y > 1300){
			deleted = true;
		}
		
		if(deleted){
			this -> enemies.erase(this -> enemies.begin() + i);
		}
	}
	
}

void Game::renderEnemies(){
	for(int i = 0; i < this -> enemies.size(); i++){
		this -> window -> draw(enemies[i]);
	}
}

void Game::initPac(string pacFile){
	this -> pacTexture.loadFromFile(pacFile);
    this -> pacSpr.setTexture(pacTexture);
    this -> pacSpr.setScale(sf::Vector2f(0.3, 0.3));
}

void Game::updatePac(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		this -> pacSpr.move(5,0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		this -> pacSpr.move(0,5);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		this -> pacSpr.move(-5,0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		this -> pacSpr.move(0,-5);
	}
	
	if(pacSpr.getPosition().x < -100){
		this -> pacSpr.move(2000,0);
	}
	else if(pacSpr.getPosition().x > 1900){
		this -> pacSpr.move(-2000,0);
	}
	if(pacSpr.getPosition().y < -100){
		this -> pacSpr.move(0,1450);
	}
	if(pacSpr.getPosition().y > 1300){
		this -> pacSpr.move(0,-1450);
	}
} 

void Game::renderPac(){
	this -> window -> draw(this -> pacSpr);
}

void Game::initFood(string foodFile){
	this -> foodTexture.loadFromFile(foodFile);
    this -> foodSpr.setTexture(foodTexture);
    this -> foodSpr.setScale(sf::Vector2f(0.1, 0.1));
}

void Game::spawnFood(){
	this -> foodSpr.setPosition(
		static_cast<float>(rand() % static_cast<int>((this -> window -> getSize().x) - (this -> foodSpr.getTexture()->getSize().x * ghostSpr.getScale().x))),
		static_cast<float>(rand() % static_cast<int>((this -> window -> getSize().y) - (this -> foodSpr.getTexture()->getSize().y * ghostSpr.getScale().y)))
	);
	
	this -> foods.push_back(this -> foodSpr);
}

void Game::updateFoods(){
	if(this -> foods.size() < this -> maxFoods){
		if(this -> foodSpawnTimer >= this -> foodSpawnTimerMax){
			this -> spawnFood();
			this -> foodSpawnTimer = 0.f;
		}
		else{
			this -> foodSpawnTimer += 1.f;
		}
	}
	
	for(int i = 0; i < this -> foods.size(); i++){
		bool deleted = false;
		
		if(this -> pacSpr.getGlobalBounds().intersects(this -> foods[i].getGlobalBounds())){
			deleted = true;
			points++;
		}
		
		if(deleted){
			this -> foods.erase(this -> foods.begin() + i);
		}
	}
}

void Game::renderFoods(){
	for(int j = 0; j < this -> foods.size(); j++){
		this -> window -> draw(foods[j]);
	}
}





