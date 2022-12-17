#include <iostream>
#include <string>


#include "Game.h"

using namespace std;

int main()
{
	Game game;
    
    srand(static_cast<unsigned>(time(NULL)));
    while(game.running()){
    	game.update();
    	
    	game.render();
	}
    
    return 0;
}

