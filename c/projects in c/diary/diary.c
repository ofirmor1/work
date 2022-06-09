#include <stdio.h>
#include <stdlib.h>
#include "diary.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 15794
#define NO_OVERLAP 0
#define OVERLAP 1
#define _meeting _ptrStruct->m_meetings /*short name for further use in _ptrStruct->m_meetings*/

struct Meeting
{	
	float m_startTime;
	float m_endTime;
	int m_room;
};

struct DayMeetings
{	
	size_t m_size;
	size_t m_originalSize;
	size_t m_numOfMeetings;
	int m_magicNumber;
	size_t m_blockSize;	
	Meeting** m_meetings; /*pointer to array of pointers to structs of 								meetings*/
};

/*****************************************************************/
DayMeetings* CreateDayMeetings(size_t _size, size_t _blockSize) 
{
	DayMeetings *ptrStruct;
	int *ptrMeeting;
		if(0 == _size && 0 == _blockSize)
		{
			return NULL;
		}
	
	ptrStruct = (DayMeetings*) malloc (sizeof(DayMeetings));
	if(ptrStruct == NULL)
	{
		return NULL;
	}
	ptrStruct->m_meetings = (Meeting**)malloc(sizeof(Meeting*)*_size);
	if(ptrStruct->m_meetings == NULL)
	{
		free(ptrStruct);
		return NULL;
	}	
	ptrStruct->m_originalSize=_size;
	ptrStruct->m_blockSize=_blockSize;
	ptrStruct->m_numOfMeetings = 0;
	ptrStruct->m_size=_size;
	ptrStruct->m_magicNumber=MAGIC_NUMBER;
	
	return ptrStruct;
}
/*****************************************************************/
Meeting *CreateMeeting(float _startTime, float _endTime, int _room, ADTErr* status)
{
	Meeting *ptrMeeting;

	if (_startTime > 23.99 || _startTime < 0.0) /*export to function1*/
	{	
		*status = ERR_INVALID_START_TIME;
		return NULL;
	}
	if (_endTime <= 0.0 || _endTime > 23.99)
	{
		*status = ERR_INVALID_END_TIME;
		return NULL;
	}
	if(_startTime>=_endTime )
	{
		*status = ERR_INVALID_TIME;
		return NULL;
	}	

	
	ptrMeeting=(Meeting*)malloc(sizeof(Meeting));
	if(NULL == ptrMeeting)
	{
		*status = ERR_NOT_INITIALIZED;
		return NULL;
	}
	
	ptrMeeting->m_startTime =_startTime;
	ptrMeeting->m_endTime =_endTime;
	ptrMeeting->m_room =_room;

	*status = ERR_OK;
	return ptrMeeting;	
}

/*****************************************************************/
void DayMeetingsDestroy(DayMeetings* _ptrStruct)
{	
	int i; /*index of meeting */
	if((_ptrStruct == NULL ) || _ptrStruct->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	_ptrStruct->m_magicNumber=0;
	for(i = 0; i < _ptrStruct->m_numOfMeetings; i++)
	{
		free(_meeting[i]);
	}
	free(_meeting);
	free(_ptrStruct);
}
/*****************************************************************/
ADTErr AddMeeting (DayMeetings* _ptrStruct, Meeting* _ptrMeeting)
{
	Meeting** temp;
	int index; /* index of a new meeting*/
	size_t newSize;

	if(NULL == _ptrStruct || NULL == _ptrMeeting )
	{
		return ERR_NOT_INITIALIZED;
	}	
	if( CheckOverLap(_ptrStruct, _ptrMeeting->m_startTime, 
	                _ptrMeeting->m_endTime)==OVERLAP)
	{
		return ERR_OVERLAP;
	}

	if (_ptrStruct->m_size == _ptrStruct->m_numOfMeetings)
	{
		if (_ptrStruct->m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		newSize = _ptrStruct->m_blockSize + _ptrStruct->m_size;
		temp = (Meeting**)realloc(_meeting,newSize*sizeof(Meeting*));
		if(NULL == temp)
		{
			return ERR_REALLOCATION_FAILED;
		}
		_meeting = temp;
		_ptrStruct->m_size = newSize;
	}
	
	index = IndexOfNewMeeting(_meeting, _ptrStruct->
	m_numOfMeetings,_ptrMeeting->m_startTime);
	
	MoveMeetingRight(_meeting, index, _ptrStruct->m_numOfMeetings);

	_meeting[index]=_ptrMeeting;

	_ptrStruct->m_numOfMeetings++;
	
	return ERR_OK;		
}

/*****************************************************************/
void DayMeetingsPrint(DayMeetings* _ptrStruct)
{
	int i, room;
	float startTime, endTime;
	if (_ptrStruct->m_numOfMeetings == 0)
	{
		printf("No appointments for today\n");
		return;
	}

	for (i = 0; i < _ptrStruct->m_numOfMeetings; i++)
	{
		startTime= _ptrStruct->m_meetings[i]->m_startTime;
		endTime= _meeting[i]->m_endTime;
		room= _meeting[i]->m_room;
		printf("\t\t\n");
		printf("Meeting number:%d\t\n\n ",i+1);
		printf("Start time: %.2f \n",startTime);
		printf("End time: %.2f \n",endTime);
		printf("Room number: %d \n",room);		
		printf("\n");
	}
	printf("\n");
}
/*****************************************************************/
ADTErr RemoveMeeting(DayMeetings* _ptrStruct, float _startTime)
{
	ADTErr status;
	int index; /*index of a meeting*/
	size_t newSize;
	Meeting* ptrMeeting;   
	Meeting** temp;
	
	if( _ptrStruct == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_ptrStruct->m_numOfMeetings == 0)
	{
		return ERR_NO_MEETINGS_TODAY;
	}
	if (_startTime > 23.99 || _startTime < 0.0)
	{
		return ERR_INVALID_START_TIME;
	}	
	ptrMeeting = FindMeeting(_ptrStruct, _startTime, &index, &status);
	
	if(ptrMeeting == NULL)
	{
	 	return ERR_MEETING_NOT_FOUND;
	}

	free(_ptrStruct->m_meetings[index]);

	MoveMeetingLeft(_ptrStruct->m_meetings, index, _ptrStruct->m_numOfMeetings);
	
	_ptrStruct->m_numOfMeetings--;

	newSize = _ptrStruct->m_size - _ptrStruct->m_blockSize;
 
	if(_ptrStruct->m_originalSize < _ptrStruct->m_size  && 
	  _ptrStruct->m_size - _ptrStruct->m_numOfMeetings >= 2*_ptrStruct->m_blockSize)
	{
		temp=(Meeting**) realloc(_ptrStruct->m_meetings,newSize*sizeof(Meeting*));
		if( temp != NULL)
		{
			_ptrStruct->m_meetings = temp;
			_ptrStruct->m_size = newSize;
		}
	}
	return ERR_OK;
}

/*****************************************************************/
Meeting* FindMeeting(DayMeetings* _ptrStruct,float _startTime, int* _i,ADTErr* _status)
{
	int i;

	if (_startTime > 23.99||_startTime < 0.0)
	{
		*_status = ERR_INVALID_START_TIME;
		return NULL;
	}		
	for (i = 0; i < _ptrStruct->m_numOfMeetings; i++)
	{
		if(_startTime == _ptrStruct->m_meetings[i]->m_startTime)
		{
			*_i = i;
			return _ptrStruct->m_meetings[i];
		}
	}
	*_status = ERR_MEETING_NOT_FOUND;
	return NULL;	
}


/*****************************************************************/
int IndexOfNewMeeting(Meeting** _meetings, size_t _numOfMeetings, float _startTime)
{
	int i; /* index of a new meeting*/
	if (_numOfMeetings==0)
	{
		return 0;
	}
	for(i=0; i<_numOfMeetings;i++)
	{
		if(_startTime< _meetings[i]->m_startTime)
		{
			return i;
		}
	}	
}
/*****************************************************************/
void MoveMeetingRight(Meeting** _meetings, int _index, size_t _numberOfMeetings)
{
	int j;

	if(_index == _numberOfMeetings)
	{
		return;
	}
	for(j=_numberOfMeetings ;j>_index; j--)
	{
		_meetings[j]=_meetings[j-1];
		
	}
}
/*****************************************************************/
void MoveMeetingLeft(Meeting** _meetings, int _i, size_t _numberOfMeetings)
{

	if(_i == _numberOfMeetings-1)
	{
		return;
	}
	for(_i; _i<_numberOfMeetings-1 ; _i++)
	{
		_meetings[_i] = _meetings[_i+1];
	} 
}
/*****************************************************************/
int CheckOverLap(DayMeetings* _ptrStruct, float _startTime, float _endTime)
{
	int i;
	/*float meetingDuration = _endTime - _startTime;*/
	if(_ptrStruct->m_numOfMeetings==0)
	{
		return NO_OVERLAP;	
	}
	for (i = 0; i <_ptrStruct->m_numOfMeetings; i++)
	{
		if((_startTime >= _meeting[i]->m_startTime && _startTime <= _meeting[i]->m_endTime) || (_endTime <= _meeting[i]->m_endTime && _endTime >= _meeting[i]->m_startTime))
		{
			return OVERLAP;
		}
	}
	
	return NO_OVERLAP;
}
/*****************************************************************/
void PrintOneMeeting(DayMeetings* _ptrStruct, int _index)
{
	float startTime;
	float endTime;
	int room;
	if (_ptrStruct == NULL)
	{
		return;
	}

	if (_ptrStruct->m_numOfMeetings == 0)
	{
		printf("No meetings today\n");
		return;
	}
		startTime = _meeting[_index]->m_startTime;
		endTime = _meeting[_index]->m_endTime;
		room = _meeting[_index]->m_room;
		printf("-------------------\n");
		printf("Meeting no.%d\n-------------------\n",_index+1);
		printf("Start time  : %.2f \n",startTime);
		printf("End time    : %.2f \n",endTime);
		printf("Room number : %d \n",room);		
		printf("\n");
				
}
/*****************************************************************/
void PrintErr(ADTErr status)
{
	switch (status)
	{
		case ERR_UNDERFLOW:
			printf ("No meeting to delete.\n");
			break;
		case ERR_OVERFLOW:
			printf ("Diary is fully booked.\n");
			break;
		case ERR_INVALID_START_TIME: 
			printf ("Invalid start time.\n");
			break;
		case ERR_INVALID_END_TIME:
			printf ("Invalid end time.\n");
			break;
		case ERR_INVALID_TIME:
			printf ("Illegal meeting range.\n");
			break;
		case ERR_OVERLAP:
			printf ("Overlaping an existing meeting.\n");
			break;
		case ERR_MEETING_NOT_FOUND:
			printf ("Meeting was not found.\n");
			break;
		case ERR_NO_MEETINGS_TODAY:
			printf ("No meetings entered yet.\n");
			break;
		case ERR_OK:
			printf ("Done\n");
			break;
	}
}

size_t NumOfMeetings(DayMeetings* _ptrStruct)
{
	return _ptrStruct->m_numOfMeetings;
}

size_t Size(DayMeetings* _ptrStruct)
{
	return _ptrStruct->m_size;
}
