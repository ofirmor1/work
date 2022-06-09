#include <stdlib.h>
#include "game.h"
#define MAX_SCORE 100
#define NUMBER_OF_PLAYERS 4
	
int main(void)
{
	Game* newGame = NULL;
	newGame = CreateGame(NUMBER_OF_PLAYERS, MAX_SCORE);
	if(newGame)
	{
		StartGame(newGame);
		DestroyGame(newGame);
		
	}
	
	return 0;
}
