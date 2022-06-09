#ifndef __deck_H__
#define __deck_H__
#include "card.h"
#include "vector.h"
#include "ADTDefs.h"




/*Description: creates new deck
INPUT: num Of Decks
OUTPUT: pointer to deck
ERROR: if _numOfDecks = 0, return NULL  
*/ 
Vector* CreateDeck();


/*Description: free memory of the deck
INPUT: pointer to deck
OUTPUT: void
ERROR: in case of error, the function will be return without releasing the memory 
*/ 
void DestroyDeck(Vector* _deck);


/*Description: Shuffles all cards in deck
INPUT: pointer to deck
OUTPUT: ADTErr
ERROR: in case of _deck= NULL - the function will return ERR_NOT_INITIALIZED
	   else- ERR_OK 
*/ 
ADTErr Shuffle(Vector* _deck);


/*Description: gives card from top of deck
INPUT: pointer to deck
OUTPUT: number of the card
ERROR: in case of _deck= NULL the function will return -1; 
*/ 
ADTErr DealCard(Vector* _deck, int* _card);

#endif /*#ifndef __deck_H__*/
