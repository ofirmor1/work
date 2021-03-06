#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__



typedef enum
{
    /* General ADT Errors */
    ERR_OK =0,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
	ERR_LIST_IS_EMPTY,
	ERR_DUPLICATE,
	ERR_INVALID_CARD,
	ERR_INVALID_SUIT,
	ERR_INVALID_NUM_OF_DECKS,
    ERR_IS_EMPTY,
    ERR_ERROR,
    ERR_SORTED
} ADTErr;

#endif /*#ifndef __ADTDEFS_H__*/
