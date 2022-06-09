#ifndef __UI_H__
#define __UI_H__
#include "card.h"
#include "vector.h"

#define NO_CARD	-1
#define SPACES	5

/* prints a single card by its number sign and color
input - int card
output - none */
void UIPrintHand(Vector* _hand);

/* prints players hand of cards
input - pointer to vector
output - none */
void UIPrintCard(int _card);

/* asks the player if wants to play another round
input - pointer to int
output - none - puts the answer in an int pointer that was given */
void Exit(int* _exit);

/* prints player score
input - pointer to char name, int score
output - none */
void UIPrintScore(char* _name,int _score);

/* prints the series
input - int array,int size
output - none */
void UIPrintSeries(int _series[], int _size);

/* prints new line */
void UINewLine();

/* clean the screen */
void UICleanScreen();

/* sleep for x seconds
input - int sec
output - none */
void UISleep(int _sec);

/* prints choose 2 club */
void UIChoose2Club(int* _cardIndex);

/* Description: prints choose card*/
void UIChooseCard(int* _cardIndex, Suit _suitNumber);

/* COLORS */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"

/* SUITES SYMBOLS */
#if defined(_WIN32) || defined(__MSDOS__)
#define SPADE_SYMBOL "\x06"
#define CLUB_SYMBOL "\x05"
#define HEART_SYMBOL "\x03"
#define DIAMOND_SYMBOL "\x04"
#else
#define SPADE_SYMBOL "\xE2\x99\xA0"
#define CLUB_SYMBOL "\xE2\x99\xA3"
#define HEART_SYMBOL "\xE2\x99\xA5"
#define DIAMOND_SYMBOL "\xE2\x99\xA6"
#endif



#endif /*#ifndef __UI_H__*/
