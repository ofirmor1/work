#ifndef __PLAYERS_H__
#define __PLAYERS_H__
#include "card.h"
#include "vector.h"
#include "ADTDefs.h"


typedef struct Player Player;
typedef ADTErr(*funcPtr)(Player*, int, int*, Suit, int);

/*Description: creates a new player.
INPUT: player number, player name, if machine (0) or human (1) & max Num Of Suit Cards
OUTPUT: returns player pointer.
ERROR: return NULL if:
_playerNumber > num of players,
isHuman diffrent from 0 or 1'
if char ponter is NULL.  
*/ 
Player* CreatePlayer(int _playerIndex,int _isHuman);
/*Description: free memory of player & players arrays.
INPUT: pointer to player
OUTPUT: void
ERROR: retern if * _player is NULL

*/ 
void DestroyPlayer (Player* _player);
/*Description: gets a new card
INPUT: pointer to player and card 
OUTPUT: ADTErr status
ERROR: in case of error, the function will be return without releasing the memory
*/ 
ADTErr PlayerTakeCard(Player* _player, int _card);

ADTErr PlayerThrowCard(Player* _player, funcPtr _func, int* _card, Suit _suit, int _isHeartAllowed);

int SearchCard(Player* _player, int _cardToFind, int* _FoundCardIndex);

/*Description: Deal a card
INPUT: pointer to player and pointer to output card 
OUTPUT: ADTErr status
ERROR: return ERR_NOT_INITIALIZED if * _player is NULL
	   _card: 1 to 52. if not- will return ERR_INVALID_CARD
	   else return ERR_OK 
*/ 
size_t GiveCard (Player* _player, Suit* _suit);
/*Description:
INPUT:pointer to player !!!!!check is there is max num addedScore!!!!!
OUTPUT: ADTErr status
ERROR: return ERR_NOT_INITIALIZED if * _player is NULL
	   else return ERR_OK 
*/ 
ADTErr UpdateScore(Player* _player, int _addedScore);
/*Description: check if the player hold specific card
INPUT: pointer to player & card for check
OUTPUT: 1 if found else 0
ERROR:return ERR_NOT_INITIALIZED if * _player is NULL
_card: 1 to 52. if not- will return ERR_INVALID_CARD
else ERR_OK
*/ 
int IsFoundSpecialCard (Player* _player, int _specialCard);

int PlayerScore(Player* _player);
int AddScoreToPlayer(Player* _player, int _score);
static void SortPlayerHand(Player* _player);
void PrintPlayerHand(Player* _player);
void PrintPlayerScores(Player** _playerArr, int _size);
int IsHuman(Player* _player);
ADTErr PlayerGetCardAtIndex(Player* _player, int _index, int* _card);

#endif /*#ifndef __PLAYERS_H__*/
