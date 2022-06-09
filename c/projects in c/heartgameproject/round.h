#ifndef __ROUND_H__
#define __ROUND_H__
#include "players.h"

/*
Description: create new round:create new deck->shuffle->deal to player->destroy deck after finish dealing.
Input: pointer to array pointers of players, number of players
Output: ADTErr
ERROR: if (_deck || players array == NULL) return ERR_NOT_INITIALIZED, else return ERR_OK
*/

ADTErr CreateRound(Player** _playerArr, int _numOfPlayers);

/*
Description: start a new round
Input: pointer to array pointers of players, number Of Players, round Number, pointer to max score 
Output: ADTErr
ERROR: if (max score || players array == NULL) return ERR_NOT_INITIALIZED, else return ERR_OK
*/

ADTErr StartRound(Player** _playerArr, int _numOfPlayers, int _roundNumber, int* _maxScore);


ADTErr BotChooseCard(Player* _player, int _handSize, int* _cardIndex, Suit _suit, int _isHeartsAllowed);


/*************************************************/
/*
Description: player choose a card following the game rules
Input: pointer to player, hand size, pointer to card index, suit, is heart allowed
Output: ADTErr
ERROR: if (_player || _cardIndex == NULL) return ERR_NOT_INITIALIZED, else return ERR_OK
*/

ADTErr PlayerChooseCard(Player* _player, int _handSize, int* _cardIndex,Suit _suit, int _isHeartAllowed);

/*************************************************/
/*
Description: computer choose card automaticly. the card chosen accoridng to the game rules and a specifiec strategy. 
Input: pointer to player, hand size, pointer to card index, suit, is heart allowed.
Output: ADTErr
ERROR: if (_player || _cardIndex == NULL) return ERR_NOT_INITIALIZED, else return ERR_OK
*/
/*
ADTErr ComputerChooseCard(Player* _player, int handSize, int* _cardIndex,int isHeartAllowed ,Suit _seriesNumber);*/



#endif/*#ifndef __ROUND_H__*/
