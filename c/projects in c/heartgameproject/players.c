#include "players.h"
#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include "card.h"
#include "ui.h"
#include "myitoa.h"
#include "sortalgorithem.h"
#include <time.h>
#define HAND_SIZE	13
#define BLOCK_SIZE	4
#define STRING_NAME 15
#define MAGIC_NUMBER 65498


struct Player
{
	Vector* m_hand;
	char m_name[STRING_NAME];
	int m_score;
	int m_isHuman;
	int m_magicNumber;
};

Player* CreatePlayer(int _playerIndex,int _isHuman)
{
	char name[STRING_NAME];
	char s1[] = "Bot Player ";
	char s2[] = "My";
	Player* newPlayer = (Player*)calloc(1, sizeof(Player));
	if(newPlayer == NULL)
	{
		return NULL;
	}
	newPlayer->m_hand = VectorCreate(HAND_SIZE, BLOCK_SIZE);
	if(newPlayer->m_hand == NULL)
	{
		free(newPlayer);
		return NULL;
	}
	newPlayer->m_magicNumber = MAGIC_NUMBER;
	if(_playerIndex > 0)
	{
		Itoa(_playerIndex, name);
		strcpy(newPlayer->m_name,s1);
		strcat(newPlayer->m_name,name);
	}
	else
	{
		strcpy(newPlayer->m_name,s2);
	}
	newPlayer->m_isHuman = _isHuman;
	return newPlayer;
}

void DestroyPlayer (Player* _player)
{
	if(_player && _player->m_magicNumber == MAGIC_NUMBER)
	{
		if(_player->m_hand)
		{
			VectorDestroy(_player->m_hand);
		}
		_player->m_magicNumber = 0;
		free(_player);
	}
}

int IsHuman(Player* _player)
{
	if(_player == NULL)
	{
		return 0;
	}
	return _player->m_isHuman;
}

int SearchCard(Player* _player, int _cardToFind, int* _FoundCardIndex)
{
	int i, card;
	size_t size;
	*_FoundCardIndex = -1;
	if(_player != NULL && _player->m_hand != NULL)
	{
		VectorItemsNum(_player->m_hand,&size);
		for(i = 0; i < size; ++i)
		{
			VectorGet(_player->m_hand, i, &card);
			if(card == _cardToFind)
			{
				*_FoundCardIndex = i;
				return 1;
			}
		}
	}
	return 0;
}

ADTErr PlayerTakeCard(Player* _player, int _card)
{
	ADTErr err;
	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorAdd(_player->m_hand, _card);
	SortPlayerHand(_player);
	
	return err;
}

static void SortPlayerHand(Player* _player)
{
	size_t handSize;
	if(_player == NULL)
	{
		return;
	}
	VectorItemsNum(_player->m_hand,&handSize);
	if(handSize > 1)
	{
		QuickSort(_player->m_hand,0,handSize - 1);
	}
}

int PlayerScore(Player* _player)
{
	if(_player)
	{
		return _player->m_score;
	}
	return -1;
}

int AddScoreToPlayer(Player* _player, int _score)
{
	if(_player)
	{
		_player->m_score += _score;
	}
}

ADTErr PlayerThrowCard(Player* _player, funcPtr _func, int* _card, Suit _suit, int _isHeartAllowed)
{
	ADTErr err;
	int temp1, temp2;
	size_t handSize;
	int cardIndex;
	if(_player == NULL || _func == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_player->m_hand, &handSize);
	err = (*_func)(_player, handSize, &cardIndex, _suit, _isHeartAllowed);
	if(err != ERR_OK)
	{
		return err;
	}
	VectorGet(_player->m_hand, cardIndex, _card);
	if(handSize > 1)
	{
		VectorGet(_player->m_hand, handSize - 1, &temp2);
		VectorSet(_player->m_hand, cardIndex, temp2);
	}
	VectorDelete(_player->m_hand, &temp1);
	SortPlayerHand(_player);
	
	return ERR_OK;
}

void PrintPlayerHand(Player* _player)
{
	UIPrintHand(_player->m_hand);
}

void PrintPlayerScores(Player** _playerArr, int _size)
{
	int i;
	if(_playerArr)
	{
		for(i = 0; i < _size; ++i)
		{
			if(_playerArr[i] != NULL)
			{
				UIPrintScore(_playerArr[i]->m_name, _playerArr[i]->m_score);
			}
		}
	}
}

ADTErr PlayerGetCardAtIndex(Player* _player, int _index, int* _card)
{
	if(_player == NULL || _card == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorGet(_player->m_hand, _index, _card);
}



