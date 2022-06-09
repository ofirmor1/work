#include "round.h"
#include "vector.h"
#include "players.h"
#include "deck.h"
#include "card.h"
#include "ui.h"

#define CARDS_IN_DECK 52
#define HAND_SIZE 13
#define NUM_OF_TRICKS 13
#define NUM_OF_DECKS 1
#define FIRST_TURN_PASS 3
#define NUM_OF_PLAYERS 4
#define CARDS_TO_PASS 3
#define DOWN -1
#define UP 1


static void TurnPlay(Player** _playerArr, int _playerIndexToPassCard);

static void Trick(Player** _playerArr, int _numOfPlayers, int* _whoLost, int* _isHeartAllowed, int _trickNumber);

static int PlayerWith2Club(Player** _playersArr);

static void GetMaxScore(Player** _playerArr, int _numOfPlayers, int* _maxScore);

static void CalcScores(Player** _playerArr, int _size, int series[], int* _whoLost, Suit _seriesSuit);

static ADTErr ChooseFrom(Player* _player, int _handSize, int _from, int _to, int _jump, int* _cardIndex);

static ADTErr GetCardByRule(Player* _player, int _from, int _to, int* _cardIndex, Suit _suit);
/************************************************************************/
ADTErr CreateRound(Player** _playerArr, int _numOfPlayers)
{
	int index, j, card;
	Vector* deck = CreateDeck();
	if(NULL == deck || NULL == _playerArr)
	{
		return ERR_NOT_INITIALIZED;
	}
	Shuffle(deck);
	for(index = 0; index < _numOfPlayers; index++)
	{
		for(j = 0; j < HAND_SIZE; j++)
		{
			DealCard(deck, &card);
			PlayerTakeCard (_playerArr[index], card);
		}
	}
	DestroyDeck(deck);
	return ERR_OK;
}
/************************************************************************/
ADTErr StartRound(Player** _playerArr, int _numOfPlayers, int _roundNumber, int* _maxScore)
{
	int index;
	int lostPlayer = 0;
	int isHeartAllowed = 0;
	int PossiblePasses[] = {1,3,2,0};
	int PlayerToPassCard = PossiblePasses[_roundNumber];
	
	if(NULL == _playerArr || NULL == _maxScore)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	TurnPlay(_playerArr, PlayerToPassCard);
	lostPlayer = PlayerWith2Club(_playerArr);
	
	for(index = 0; index < NUM_OF_TRICKS; index++)
	{
		Trick(_playerArr, _numOfPlayers, &lostPlayer, &isHeartAllowed,index);
	}
	
	PrintPlayerScores(_playerArr, _numOfPlayers);
	UINewLine();
	GetMaxScore(_playerArr, _numOfPlayers, _maxScore);
	
	return ERR_OK;
}
/************************************************************************/

static void Trick(Player** _playerArr, int _numOfPlayers, int* _whoLost, int* _HeartAllowed, int _trickNumber)
{
	int i = 0;
	int card = 0;
	funcPtr func = NULL;
	int series[] = {-1,-1,-1,-1};
	int currentPlayer = *_whoLost;
	Suit _seriesSuit = NO_SERIES;
	
	while(i < _numOfPlayers)
	{
		/*first turn, the player with 2 clubs has to trhow this card*/
		if(_trickNumber == 0 && currentPlayer == *_whoLost)
		{
			_seriesSuit = CARD_2_CLUBS;
		}
		
		func = IsHuman(_playerArr[currentPlayer]) ? PlayerChooseCard : BotChooseCard;

		PlayerThrowCard(_playerArr[currentPlayer], func, &card, _seriesSuit, *_HeartAllowed);
		series[currentPlayer] = card;
		if(card < NUM_OF_CARDS)
		{
			*_HeartAllowed = 1;
		}
		if(i == 0)
		{
			_seriesSuit = SUIT(card);
		}
		
		UICleanScreen();
		UINewLine();
		UIPrintSeries(series, _numOfPlayers);
		UISleep(2);
		currentPlayer = (currentPlayer + 1) % _numOfPlayers;
		i++;
	}
	CalcScores(_playerArr,_numOfPlayers, series, _whoLost, _seriesSuit);
}

/************************************************************************/
static void TurnPlay(Player** _playerArr, int _playerIndexToPassCard) 
{
	int i, j, card, isHeartAllowd = 1;
	/*cardsToPass is a Matrix to store 3 cards to pass that has been chosen by each player or bot)*/
	int cardsToPass[NUM_OF_PLAYERS][CARDS_TO_PASS];
	funcPtr func = NULL;
	if(cardsToPass == 0)
	{
		return;
	}
	for(i = 0; i < NUM_OF_PLAYERS; i++)
	{
		func = IsHuman(_playerArr[i]) ? PlayerChooseCard: BotChooseCard;
		for(j = 0; j < CARDS_TO_PASS; j++)
		{
			PlayerThrowCard(_playerArr[i], func, &card, NO_SERIES,1);
			cardsToPass[i][j] = card;
		}
	}
		/*players get card from the player in place {1,3,2,0} according to the round number*/
	for(i = 0; i < NUM_OF_PLAYERS; i++)
	{
		for(j = 0; j < CARDS_TO_PASS; j++)
		{
			card = cardsToPass[i][j];
			PlayerTakeCard(_playerArr[(i+ _playerIndexToPassCard)% NUM_OF_PLAYERS], card);
		}
	}	
}
/************************************************************************/
static ADTErr GetCardByRule(Player* _player, int _from, int _to, int* _cardIndex, Suit _suit)
{
	int i, card, index;
	for(i = _from; i < _to; ++i)
	{
		if(SearchCard(_player, i, &index))
		{
			do
			{
				UIChooseCard(_cardIndex, _suit);
				PlayerGetCardAtIndex(_player,*_cardIndex,&card);
			}while(card < _from || card >= _to);

			return ERR_OK;
		}
	}
	return ERR_WRONG_INDEX;
}
/************************************************************************/
static int PlayerWith2Club(Player** _playersArr)
{
	int i;
	int index;
	for(i = 0; i < NUM_OF_PLAYERS; i++)
	{
		if(SearchCard(_playersArr[i],NUM_OF_CARDS * CLUB,&index))
		{
			return i;
		}
	}
	return i;
}
/************************************************************************/
ADTErr PlayerChooseCard(Player* _player, int _handSize, int* _cardIndex,Suit _suit, int _isHeartAllowed)
{
	int card, from, to;
	ADTErr err;
	if(_player == NULL || _cardIndex == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_handSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	PrintPlayerHand(_player);
	/*case only 2 club is allowed */
	if(_suit == CARD_2_CLUBS)
	{
		do
		{
			UIChoose2Club(_cardIndex);
			PlayerGetCardAtIndex(_player,*_cardIndex,&card);
		}while(card != NUM_OF_CARDS * CLUB);
		return ERR_OK;
	}
	if(_suit == NO_SERIES)
	{
		/* case no series and hearts aren't allowed */
		if(_isHeartAllowed == 0)
		{
			if(GetCardByRule(_player,NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_SUITES,_cardIndex,_suit) == ERR_OK)
			{
				return ERR_OK;
			}
		}
		/* case no series and hearts are allowed */
		GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _suit);
		return ERR_OK;
	}
	from = _suit * NUM_OF_CARDS;
	to = from + NUM_OF_CARDS;
	err = GetCardByRule(_player, from, to, _cardIndex, _suit);
	if(err == ERR_OK)
	{
		return ERR_OK;
	}
	/* case series is set but you don't have a suitable card */
	GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _suit);

	return ERR_OK;
}

/************************************************************************/

static ADTErr ChooseFrom(Player* _player, int _handSize, int _from, int _to, int _jump, int* _cardIndex)
{
	int i, index;
	for(i = _from; i != _to; i += _jump)
	{
		if(SearchCard(_player, i, &index))
		{
			*_cardIndex = index;
			return ERR_OK;
		}
	}
	return ERR_WRONG_INDEX;
}
/************************************************************************/
ADTErr BotChooseCard(Player* _player, int _handSize, int* _cardIndex, Suit _suit, int _isHeartsAllowed)
{
	ADTErr err;
	int from,to;
	if(_player == NULL || _cardIndex == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_handSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	/* case only 2 club is allowed */
	if(_suit == CARD_2_CLUBS)
	{
		return ChooseFrom(_player, _handSize, NUM_OF_CARDS * CLUB, NUM_OF_CARDS * CLUB + 1, UP, _cardIndex);
	}
	if(_suit == NO_SERIES)
	{
		/* case no series and hearts aren't allowed */
		if(!_isHeartsAllowed)
		{
			if(ChooseFrom(_player, _handSize, NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_SUITES, UP, _cardIndex) == ERR_OK)
			{
				return ERR_OK;
			}
		}
		/* case no series and you have only hearts */
		if(ChooseFrom(_player, _handSize, 0, NUM_OF_CARDS * NUM_OF_SUITES, UP, _cardIndex) != ERR_OK)
		{
			return ERR_OK;
		}
	}
	from = _suit * NUM_OF_CARDS;
	to = from + NUM_OF_CARDS;
	
	/* case series is set */
	err = ChooseFrom(_player, _handSize, from, to , UP, _cardIndex);
	if(err != ERR_OK)
	{
		/* case series is set but you don't have a suitable card */
		if(ChooseFrom(_player, _handSize, NUM_OF_CARDS -1 , -1, DOWN , _cardIndex) != ERR_OK)
		{
			ChooseFrom(_player, _handSize, NUM_OF_CARDS * NUM_OF_SUITES -1, -1 , DOWN, _cardIndex);
		}
	}
	return ERR_OK;
}
/************************************************************************/
static void GetMaxScore(Player** _playerArr, int _numOfPlayers, int* _maxScore)
{
	int i;
	for(i = 0; i < _numOfPlayers; i++)
	{
		if(PlayerScore(_playerArr[i]) > *_maxScore)
		{
			*_maxScore = PlayerScore(_playerArr[i]);
		}
	}
}
/************************************************************************/
static void CalcScores(Player** _playerArr, int _size, int series[], int* _whoLost, Suit _seriesSuit)
{
	int i;
	int trickScore = 0;
	int maxCard = 0;
	for(i = 0; i < _size; ++i)
	{
		if(series[i] == SPADE * NUM_OF_CARDS + QWEEN)
		{
			trickScore += NUM_OF_CARDS;
		}
		else if(series[i] < NUM_OF_CARDS)
		{
			trickScore++;
		}
		
		if(SUIT(series[i]) == _seriesSuit)
		{
			if(series[i] > maxCard)
			{
				maxCard = series[i];
				*_whoLost = i;
			}
		}
	}
	AddScoreToPlayer(_playerArr[*_whoLost],trickScore);
}
/************************************************************************/
