#ifndef __GAME_H__
#define __GAME_H__
#include "ADTDefs.h"

typedef struct Game Game;

/*Description: creates a new game and players.
INPUT: number of players 
OUTPUT: return game pointer.
ERROR: return NULL if _numOfPlayers =0;
*/
Game* CreateGame(int _numOfPlayers, int _maxScore);

void StartGame(Game* _game);
/*Description: start running.
INPUT: pointer to game & pointer to function that declare who is the winner
OUTPUT: void.
ERROR: in case of error, the function will return:
if _game = NULL or *WhoISTheWinner == NULL - ERR_NOT_INITIALIZED
*/
ADTErr RunGame (Game* _game , int(*WhoISTheWinner)(int*));
/*Description: free memory of the game features.
INPUT: pointer to game
OUTPUT: void.
ERROR: in case of error, the function will be return without releasing the memory
*/
void DestroyGame (Game* _game);

#endif /*#ifndef __GAME_H__*/

