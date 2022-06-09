#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"
#include "game.h"
#include "round.h"
#define BLOCK_SIZE 4
#define MAGIC_NUMBER 65484


struct Game
{
	Player** m_players;
	int m_numOfPlayers;
	int m_maxscore;
	int startPlayer;
	int m_magicNumber;
};

static ADTErr InitializePlayers(int _numOfPlayers, Game* _newGame);
/*****************************************************************************/
Game* CreateGame(int _numOfPlayers, int _maxScore)
{
	Game* newGame;
	if (_numOfPlayers <= 0)
	{
		return NULL;
	}

	newGame = (Game*) malloc (sizeof(Game));
	if (NULL == newGame)
	{
		return NULL;
	}

	newGame->m_players= (Player**) malloc (_numOfPlayers * sizeof(Player*));
	if (NULL == newGame->m_players)
	{
		free (newGame);
		return NULL;
	}
	newGame->m_maxscore = _maxScore;
	newGame->m_numOfPlayers = _numOfPlayers;
	newGame->m_magicNumber = MAGIC_NUMBER;

	if	(InitializePlayers(_numOfPlayers, newGame) != ERR_OK)
	{
		return NULL;
	}
	
	return newGame;
}
/*****************************************************************************/
void StartGame(Game* _game)
{
	int maxScore = 0, roundNumber = 0;
	int wantToExit = 0;
	if (NULL == _game)
	{
		return;
	}
	while(maxScore < _game->m_maxscore && wantToExit != 1)
	{
		UICleanScreen();
		if(CreateRound(_game->m_players, _game->m_numOfPlayers) !=  ERR_OK)
		{
			return;
		}
		StartRound(_game->m_players, _game->m_numOfPlayers , roundNumber, &maxScore);
		roundNumber = (roundNumber + 1) % _game->m_numOfPlayers;
		Exit(&wantToExit);
		UICleanScreen();
	}
	
}
/*****************************************************************************/
void DestroyGame(Game* _game)
{
	int playerIndex;
	if (NULL == _game ||  _game->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	if(_game->m_players != NULL)
	{
		for (playerIndex = 0 ; playerIndex<_game->m_numOfPlayers; playerIndex++)
		{
			free(_game->m_players[playerIndex]);
		}
		free(_game->m_players);
	}
	_game->m_magicNumber = 0;
	free(_game);
}
/*****************************************************************************/
static ADTErr InitializePlayers(int _numOfPlayers, Game* _newGame)
{
	
	int isHuman = 1;
	int playerIndex, j;
	for(playerIndex = 0; playerIndex < _numOfPlayers; playerIndex++)
	{
		_newGame->m_players[playerIndex] = CreatePlayer(playerIndex, isHuman);
		isHuman = 0;
		/*if allocation fail -> destroy all players we created so far and free memory of players array and memory of game*/
		if(NULL == _newGame->m_players[playerIndex])
		{
			for(j = 0;j < playerIndex; j++)
			{
				DestroyPlayer(_newGame->m_players[j]);
			}
			free(_newGame->m_players);
			free(_newGame);
			return ERR_ALLOCATION_FAILED;
		}
	}
	return ERR_OK;
}
/*****************************************************************************/

