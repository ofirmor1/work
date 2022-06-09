#ifndef __CARD_H__
#define __CARD_H__
#define SUIT(i) (i/NUM_OF_CARDS)
#define RANK(i) (i%NUM_OF_CARDS)


typedef enum
{
	NO_SERIES = -1,
	HEART =0,
	DIAMOND=1,
	SPADE=2,
	CLUB=3,
	NUM_OF_SUITES,
	CARD_2_CLUBS
}Suit;

typedef enum
{
	TWO =0,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EGHIT,
	NINE,
	TEN,
	JACK,
	QWEEN,
	KING,
	ACE,
	NUM_OF_CARDS
}Rank;
   

#endif /*#ifndef __CARD_H__*/
