#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "ADTDefs.h"
#include "card.h"
#include "vector.h"
#include "deck.h"
#define CARDS_IN_DECK 52
#define NUM_OF_DECKS 1




static ADTErr FillDeck(Vector* _deck);
/************************************************************************/
Vector* CreateDeck()
{
	size_t sizeOfDeck;
	Vector* deckPtr;

	sizeOfDeck = NUM_OF_DECKS * CARDS_IN_DECK;

	deckPtr = VectorCreate(sizeOfDeck, 0);
	if (NULL == deckPtr)
	{
		return NULL;	
	}
	FillDeck (deckPtr);
	return deckPtr;		
}
/************************************************************************/
void DestroyDeck(Vector* _deck)
{	
	if (NULL == _deck)
	{
		return;
	}
	VectorDestroy(_deck);
}
/************************************************************************/
ADTErr Shuffle(Vector* _deck)
{
	size_t sizeOfDeck, index, randIndex;
	int card1 , card2;

	if (NULL == _deck)
	{
		return ERR_NOT_INITIALIZED;
	}

	sizeOfDeck = NUM_OF_DECKS * CARDS_IN_DECK;

	srand(time(NULL));
	for (index=0; index< sizeOfDeck; index++)
	{
		randIndex = rand() % sizeOfDeck;

		VectorGet(_deck, randIndex, &card1);
		VectorGet(_deck, index, &card2);
		
		VectorSet(_deck, randIndex, card2);
		VectorSet(_deck, index, card1);
	}
	return ERR_OK;	
}
/************************************************************************/
ADTErr DealCard(Vector* _deck, int* _card)
{
	ADTErr status;
	if (NULL == _deck)
	{
		return ERR_NOT_INITIALIZED;
	}
	status = VectorDelete(_deck, _card);
	
	return status;
}
/************************************************************************/
static ADTErr FillDeck (Vector* _deck)
{
	int index;
	ADTErr status;
	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	for(index = 0; index < CARDS_IN_DECK; index++)
	{
		status = VectorAdd(_deck, index);
		if(status != ERR_OK)
		{
			return status;
		}
	}
	return ERR_OK;
}
/************************************************************************/



