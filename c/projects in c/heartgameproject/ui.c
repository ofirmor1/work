#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "vector.h"
#include "ui.h"
#include "card.h"
#include "myitoa.h"

void UIPrintHand(Vector* _hand)
{
	int i, temp;
	size_t handSize;
	VectorItemsNum(_hand, &handSize);
	for(i = 0; i < handSize; ++i)
	{
		printf("(%d)  ",i);
	}
	printf("\n");
	for(i = 0; i < handSize; ++i)
	{
		VectorGet(_hand, i, &temp);
		UIPrintCard(temp);
	}
	printf("\n");
}

void UIPrintCard(int _card)
{
	int suit, number;
	char* symbol;
	char* color;
	char sign[10];
	color = NORMAL;
	suit = SUIT(_card);
	number = RANK(_card);
	if(_card == NO_CARD)
	{
		printf(" ");
		return;
	}
	switch(suit)
	{
		case HEART:
		symbol = HEART_SYMBOL;
		color = RED;
		break;
		
		case SPADE:
		symbol = SPADE_SYMBOL;
		break;
		
		case DIAMOND:
		symbol = DIAMOND_SYMBOL;
		color = RED;
		break;
		
		case CLUB:
		symbol = CLUB_SYMBOL;
		break;
	}
	switch(number)
	{
		case JACK:
		strcpy(sign,"J");
		break;
		
		case QWEEN:
		strcpy(sign,"Q");
		break;
		
		case KING:
		strcpy(sign,"K");
		break;
		
		case ACE:
		strcpy(sign,"A");
		break;
		
		default:
		strcpy(sign,"");
		Itoa(number + 2, sign);
		break;
	}
	
	printf("%s%s %s%s  ", color, symbol, sign, NORMAL);
}

void Exit(int* _exit)
{
	char choise[10];
	printf("\nPlay another round? (y / n)\n");
	scanf("%s",choise);
	if(strcmp(choise,"y") == 0)
	{
		*_exit = 0;
	}
	else
	{
		*_exit = 1;
	}
}

void UIPrintScore(char* _name,int _score)
{
	printf("%s Score: %d\n", _name, _score);
}

void UINewLine()
{
	printf("\n");
}

void UIPrintSeries(int _series[], int _size)
{
	int index;
	for(index = 0; index < SPACES; index++)
	{
		printf(" ");
	}
	UIPrintCard(_series[2]);
	printf("\n\n");
	UIPrintCard(_series[1]);
	for(index = 0; index < 2 * SPACES - 1; index++)
	{
		printf(" ");
	}
	UIPrintCard(_series[3]);
	printf("\n\n");
	for(index = 0; index < SPACES; index++)
	{
		printf(" ");
	}
	UIPrintCard(_series[0]);
	printf("\n--------------");
	printf("\n");
}

void UICleanScreen()
{
	system("clear");
}


void UISleep(int _sec)
{
	sleep(_sec);
}

void UIChoose2Club(int* _cardIndex)
{
	do
	{
		printf("choose card (2 CLUB)\n");
		scanf("%d",_cardIndex);
	}while(*_cardIndex < 0 || *_cardIndex > 12);
}

void UIChooseCard(int* _cardIndex, Suit _suitNumber)
{
	char* symbol;
	switch(_suitNumber)
	{
		case HEART:
		symbol = HEART_SYMBOL; 
		break;
		
		case SPADE: 
		symbol = SPADE_SYMBOL; 
		break;
		
		case DIAMOND: 
		symbol = DIAMOND_SYMBOL; 
		break;
		
		case CLUB: 
		symbol = CLUB_SYMBOL; 
		break;
		
		default: 
		symbol = "";
		break;
	}
	do
	{
		printf("choose card %s\n",symbol);
		scanf("%d",_cardIndex);
	}while(*_cardIndex < 0 || *_cardIndex > 12);
}

