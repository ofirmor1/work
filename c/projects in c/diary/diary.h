#ifndef __DIARY_H__
#define __DIARY_H__
#include <stdio.h>
#include <stdlib.h>
#include "ADTDefs.h"


typedef struct DayMeetings DayMeetings;
typedef struct Meeting Meeting;

/*****************************************************************/
/*
Description: The function create a diary struct and array of pinters to meetings
input: size of an array and block size to extend the array in case numOfMeetings==size;
output: pointer of the struct
check: if (size == 0 || blocksize == 0) --> Error. return NULL if allocation failed
*/
DayMeetings* CreateDayMeetings(size_t _size, size_t _blockSize); 
/*****************************************************************/
/*
Description: the function allocate a meeting in size of struct, and set the meeting parameters.
input: 
output: pointer of struct
check: check parameters validation - (_end - _begin > 0),23.99 > _begin > 0.0 , 23.99 > end > 0.0
*/
Meeting *CreateMeeting(float _begin, float _end, int _room, ADTErr* status);
/*****************************************************************/
/*
Description: The function free the struct and the array of meetings
input: pointer of struct type
output:	no output
check: memory will not be released in case of failure to destroy.
*/
void DayMeetingsDestroy(DayMeetings* _ptrStruct);
/*****************************************************************/
/*
Description: The function add a meeting to the diary.
input: pointer type DM and a pointer to meeting.	
output: return error status - ADTErr.
check: ERR_OK - meeting added succsefully
		ERR_REALLOCATION_FAILED - reallocation failed
		ERR_NOT_INITIALIZED - pointers arguments NULL
*/
ADTErr AddMeeting (DayMeetings* _ptrStruct, Meeting* _ptrMeeting);
/*****************************************************************/
/*
Description
input: 
output: pointer of the struct
check: 
*/
ADTErr RemoveMeeting(DayMeetings* _ptrStruct, float _startTime);
/*****************************************************************/
/*
Description: The function print today meetings
input: DM pointer
output: no output
check: ..
*/
void DayMeetingsPrint(DayMeetings* _ptrStruct);
/*****************************************************************/
/*
Description: Find a meeting by _startTime
input:  DM struct pointer, start time of a meeteing to search, index pointer, status to output
output: pointer to the meeting that found.
check: check arguments and return status
ERR_INVALID_START_TIME - start time is invalid
ERR_MEETING_NOT_FOUND - no meeting found
*/
Meeting* FindMeeting(DayMeetings* _ptrStatus,float _startTime, int* _i,ADTErr* _status);
/*****************************************************************/
/*
Description: Return index of new meeting in meetings array
input: meetings array pointer, num of meetings, start time
output: index of new meeting
check: pointer is not NULL, parameters check.
*/
int IndexOfNewMeeting(Meeting** _meetings, size_t _numOfMeetings, float _startTime);
/*****************************************************************/
/*
Description
input: 
output: pointer of the struct
check: 
*/
void MoveMeetingRight(Meeting** _meetings, int _index, size_t _numberOfMeetings);
/*****************************************************************/
/*
Description
input: 
output: pointer of the struct
check: 
*/
void MoveMeetingLeft(Meeting** _meetings, int _i, size_t _numberOfMeetings);
/*****************************************************************/
/*
Description: check overlap of two meetings
input: 
output: pointer of the struct
check: 
*/
int CheckOverLap(DayMeetings* _ptrStruct, float _startTime, float _endTime);
/*****************************************************************/
/*
Description: Print one meeting details(start,end,room)
input: DM pointer, index of a meeting
output: no output
check: pointer in not NULL, num of meeting > 0
*/
void PrintOneMeeting(DayMeetings* _ptrStruct, int _i);
/*****************************************************************/
/*
Description: Function to print ERROR STATUS
input: status variable type ADTErr	 
output: no output
check: ..
*/
void PrintErr(ADTErr status);



#endif /*#ifndef __DIARY_H__*/
