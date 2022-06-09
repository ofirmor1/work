#include <stdlib.h>
#include <stdio.h>
#include "ADTDefs.h"
#include "vector.h"
#include "players.h"

#define NUM_OF_PLAYERS 4

/****************************PLAYERS**************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~Create tests~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckCreateNull()
{
	Player* playerPtr;
	if(NULL == CreatePlayer(-1, 1))
	{
		printf("%35.35s - %s\n","CheckCreateNull","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CheckCreateNull","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CreatePlayerIndexUnder0()
{
	if(NULL == CreatePlayer(-1, -1))
	{
		printf("%35.35s - %s\n","CreatePlayerIndexUnder0","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CreatePlayerIndexUnder0","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CreatePlayerisHumanUnder0()
{
	if(NULL == CreatePlayer(1, -1))
	{
		printf("%35.35s - %s\n","CreatePlayerisHumanUnder0","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CreatePlayerisHumanUnder0","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckCreateIsWorking()
{
	if(NULL != CreatePlayer(3 ,1))
	{
		printf("%35.35s - %s\n","CheckCreateIsWorking","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CheckCreateIsWorking","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~Destroy tests~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckDestroyIsNull()
{
	DestroyPlayer(NULL);
	printf("%35.35s - %s\n","CheckDestroyIsNull","Pass");	
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/	
void CheckDestroyIsWorking()
{
	Player* newPlayer;
	newPlayer = CreatePlayer(2,1);
	DestroyPlayer(newPlayer);
	printf("%35.35s - %s\n","CheckDestroyIsWorking","Pass");
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckDoubleDestroy()
{
	Player* newPlayer;
	newPlayer = CreatePlayer(2,1);
	DestroyPlayer(newPlayer);
	DestroyPlayer(newPlayer);
	printf("%35.35s - %s\n","CheckDoubleDestroy","Pass");	
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr PlayerTakeCardIsWorking()

{
	ADTErr status;
	Player* newPlayer;
	newPlayer = CreatePlayer(2,1);
	if(status = PlayerTakeCard(newPlayer, 5) == ERR_OK)
	{
		printf("%35.35s - %s\n","PlayerTakeCardIsWorking","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","PlayerTakeCardIsWorking","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr PlayerTakeCardNULL()
{
	ADTErr status;
	Player* newPlayer;
	newPlayer = CreatePlayer(2,1);
	if(status = PlayerTakeCard(NULL, 5) == ERR_NOT_INITIALIZED)
	{
		printf("%35.35s - %s\n","PlayerTakeCardNULL","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","PlayerTakeCardNULL","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr SortPlayerHand()
{
	Player* newPlayer;
	newPlayer = CreatePlayer(2,1);
	PlayerTakeCard(newPlayer, 5);
	PlayerTakeCard(newPlayer, 3);
	PlayerTakeCard(newPlayer, 17);
	PlayerTakeCard(newPlayer, 2);
	/*PrintPlayerHand(newPlayer);*/
	printf("%35.35s - %s\n","SortPlayerHand","Pass");	
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckAddScoreToPlayerNull()
{
	Player* playerPtr;
	if(AddScoreToPlayer(NULL, 1) == -1)
	{
		printf("%35.35s - %s\n","CheckAddScoreToPlayerNull","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CheckAddScoreToPlayerNull","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckIsScoreAddedToPlayer()
{
	Player* newPlayer;
	newPlayer = CreatePlayer(2,1);
	AddScoreToPlayer(newPlayer , 5);
	if(GetPlayerScore(newPlayer) == 5)
	{
		printf("%35.35s - %s\n","CheckIsScoreAddedToPlayer","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CheckIsScoreAddedToPlayer","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckSearchCardNULL()
{
	Player* newPlayer;
	int foundCardIndex;
	newPlayer = CreatePlayer(2,1);
	PlayerTakeCard(newPlayer, 5);
	if(SearchCard(NULL, 5, &foundCardIndex) == 0)
	{
		printf("%35.35s - %s\n","CheckSearchCardNULL","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CheckSearchCardNULL","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CheckSearchCardIsWorking()
{
	Player* newPlayer;
	int foundCardIndex;
	newPlayer = CreatePlayer(2,1);
	PlayerTakeCard(newPlayer, 5);/*2*/
	PlayerTakeCard(newPlayer, 3);/*1*/
	PlayerTakeCard(newPlayer, 17);
	PlayerTakeCard(newPlayer, 2);/*0*/
	SearchCard(newPlayer, 5, &foundCardIndex);
	if(foundCardIndex == 2)
	{
		printf("%35.35s - %s\n","CheckSearchCardIsWorking","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","CheckSearchCardIsWorking","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int IsFoundSpecialCardWorking()
{
	Player* newPlayer;
	int foundCardIndex;
	newPlayer = CreatePlayer(2,1);
	PlayerTakeCard(newPlayer, 2);
	if(IsFoundSpecialCard(newPlayer, 2) == 0)
	{
		printf("%35.35s - %s\n","IsFoundSpecialCardWorking","Pass");		
	}
	else
	{
		printf("%35.35s - %s\n","IsFoundSpecialCardWorking","Fail");	
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(void)
{
	printf("/****************************PLAYERS**************************/\n");
	printf("/~~~~~~~~~~~~~~~~~~~~~~~~~CREATE TESTS~~~~~~~~~~~~~~~~~~~~~~~~/\n");
	CheckCreateNull ();
	CreatePlayerIndexUnder0();
	CreatePlayerisHumanUnder0();
	CheckCreateIsWorking();
	printf("/~~~~~~~~~~~~~~~~~~~~~~~~~DESTROY TESTS~~~~~~~~~~~~~~~~~~~~~~~~/\n");
	CheckDestroyIsNull();
	CheckDestroyIsWorking();
	CheckDoubleDestroy();
	printf("/~~~~~~~~~~~~~~~~~~~~~PLAYER GET CARD TESTS~~~~~~~~~~~~~~~~~~~~/\n");
	PlayerTakeCardIsWorking();
	PlayerTakeCardNULL();
	SortPlayerHand();
	printf("/~~~~~~~~~~~~~~~~~~~~~ADD SCORE TO PLAYER TESTS~~~~~~~~~~~~~~~~~~~~/\n");
	CheckAddScoreToPlayerNull();
	CheckIsScoreAddedToPlayer();
	CheckSearchCardNULL();
	CheckSearchCardIsWorking();
}
