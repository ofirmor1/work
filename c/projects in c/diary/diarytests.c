#include <stdio.h>
#include <stdlib.h>
#include "ADTDefs.h"
#include "diary.h"
ADTErr status;


/******************************CREATE TESTS****************************/
void CheckCreateNull ()
{
	if(CreateDayMeetings(0,0)==NULL)
	{
		printf("%30.20s - %s\n","CheckCreateNull","Pass");		
	}
	else
	{
		printf("%30.20s - %s\n","CheckCreateNull","Fail");	
	}
}
/**********************************************************************/
void CheckCreateSize1Blocksize0 ()
{
	if(CreateDayMeetings(1,0)!=NULL)
	{
		printf("%30.20s - %s\n","CheckCreateSize1Blocksize0","Pass");		
	}
	else
	{
		printf("%30.20s - %s\n","CheckCreateSize1Blocksize0","Fail");	
	}
}
/**********************************************************************/
void CheckCreateSize0Blocksize1 ()
{
	if(CreateDayMeetings(0,1)!=NULL)
	{
		printf("%30.20s - %s\n","CheckCreateSize0Blocksize1","Pass");		
	}
	else
	{
		printf("%30.20s - %s\n","CheckCreateSize0Blocksize1","Fail");	
	}
}
/**********************************************************************/
void CheckCreateSizeUnder0 ()
{
	if(CreateDayMeetings(-1,1)==NULL)
	{
		printf("%30.20s - %s\n","CheckCreateSizeUnder0","Pass");		
	}
	else
	{
		printf("%30.20s - %s\n","CheckCreateSizeUnder0","Fail");	
	}
}
/**********************************************************************/
void CheckCreateIsWorking ()
{
	if(CreateDayMeetings(6,2)!=NULL)
	{
		printf("%30.20s - %s\n","CheckCreateIsWorking","Pass");		
	}
	else
	{
		printf("%30.20s - %s\n","CheckCreateIsWorking","Fail");	
	}
}
/******************************DESTROY TESTS***************************/
void CheckDestroyIsNull()
{
	DayMeetingsDestroy(NULL);
	printf("%30.20s - %s\n","CheckDestroyIsNull","Pass");	
}	
/**********************************************************************/
void CheckDestroyIsWorking()
{
	DayMeetings *ptrStruct;
	ptrStruct = CreateDayMeetings(2,1);
	DayMeetingsDestroy(ptrStruct);
	printf("%30.20s - %s\n","CheckDestroyIsWorking","Pass");	
}
/**********************************************************************/
void CheckDDestroy()
{
	DayMeetings *ptrStruct;
	ptrStruct = CreateDayMeetings(2,1);
	DayMeetingsDestroy(ptrStruct);
	DayMeetingsDestroy(ptrStruct);
	printf("%30.20s - %s\n","CheckDDestroy","Pass");
}
/**********************CREATE MEETING TESTS***************************/
void CheckCreateMeetingIsWorking()
{
	if(NULL!=CreateMeeting(10.32,10.90,1,&status))
	{
		printf("%30.30s - %s\n","CheckCreateMeetingIsWorking","Pass");
	}
	else
	{
	printf("%30.30s - %s\n","CheckCreateMeetingIsWorking","Fail");
	}	
}
/**********************************************************************/
void CheckCreateMeetingInvalidSrartTime()
{
	if(CreateMeeting(26.20,10.90,1,&status)==NULL)
	{
		printf("%30.30s - %s\n","CheckCreateMeetingInvalidSrartTime","Pass");
	}
	else
	{
	printf("%30.30s - %s\n","CheckCreateMeetingInvalidSrartTime","Fail");
	}

}
/**********************************************************************/
void CheckCreateMeetingInvalidEndTime()
{
	if(CreateMeeting(26.20,-23.20,1,&status)==NULL)
	{
		printf("%30.30s - %s\n","CheckCreateMeetingInvalidEndTime","Pass");
	}
	else
	{
	printf("%30.30s - %s\n","CheckCreateMeetingInvalidEndTime","Fail");
	}
}
/**********************************************************************/
void CheckCreateEndTimeIsEarlierThanStartTime()
{
	if(CreateMeeting(18.00,05.20,1,&status)==NULL)
	{
		printf("%30.30s - %s\n","CheckCreateEndTimeIsEarlierThanStartTime","Pass");
	}
	else
	{
	printf("%30.30s - %s\n","CheckCreateEndTimeIsEarlierThanStartTime","Fail");
	}
}
/**********************ADD MEETING TESTS*****************************/
void CheckAddMeetingDayMeetingsNull()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(0,0);
	ptrMeeting = CreateMeeting(10.32,10.90,1,&status);
	
	if(AddMeeting(ptrStruct,ptrMeeting)==ERR_NOT_INITIALIZED)
	{
		printf("%30.30s - %s\n","CheckAddMeetingDayMeetingsNull","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckAddMeetingDayMeetingsNull","Fail");
	}
}
/**********************************************************************/
void CheckAddMeetingMeetingNull()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(2,1);
	ptrMeeting = CreateMeeting(10.32,8.27,1,&status);
	
	if(AddMeeting(ptrStruct,ptrMeeting)==ERR_NOT_INITIALIZED)
	{
		printf("%30.30s - %s\n","CheckAddMeetingMeetingNull","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckAddMeetingMeetingNull","Fail");
	}

}
/**********************************************************************/
void CheckAddMeetingOverlap()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(2,1);
	ptrMeeting = CreateMeeting(10.01,10.45,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(10.45,13.22,1,&status);

	if(AddMeeting(ptrStruct,ptrMeeting)==ERR_OVERLAP)
	{
		printf("%30.30s - %s\n","CheckAddMeetingOverlap","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckAddMeetingOverlap","Fail");
	}
}
/**********************************************************************/
void CheckAddMeetingOverflow()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(1,0);
	ptrMeeting = CreateMeeting(10.12,10.20,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(08.75,09.38,1,&status);
	if(AddMeeting(ptrStruct,ptrMeeting) == ERR_OVERFLOW)
	{
		printf("%30.30s - %s\n","CheckAddMeetingOverflow","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckAddMeetingOverflow","Fail");
	}	
}
/**********************************************************************/
void CheckAddMeetingIsWorking()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(4,4);
	ptrMeeting = CreateMeeting(9.3,10.5,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(10.52,14.30,1,&status);
	if(AddMeeting(ptrStruct,ptrMeeting)==ERR_OK)
	{
		printf("%30.30s - %s\n","CheckAddMeetingIsworking","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckAddMeetingIsworking","Fail");
	}
	DayMeetingsPrint(ptrStruct);	
}

/************************FIND MEETING TESTS***************************/
void CheckFindMeetingNull()
{
	int i;
	DayMeetings* ptrStruct;

	ptrStruct = CreateDayMeetings(1,4);
	if(FindMeeting(ptrStruct,28.15,&i,&status) == 0)
	{
		printf("%30.30s - %s\n","CheckFindMeetingNull","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckFindMeetingNull","Fail");
	}		
}
/**********************************************************************/
void CheckFindMeetingNotFound()
{
	int i;
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(1,4);
	ptrMeeting = CreateMeeting(8.27,9.50,4,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(10.45,11.30,4,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	if(FindMeeting(ptrStruct,10.27,&i,&status)==0)
	{
		printf("%30.30s - %s\n","CheckFindMeetingNotFound","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckFindMeetingNotFound","Fail");
	}		
}
/**********************************************************************/
void CheckFindMeetingFound()
{
	int i;
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(4,4);
	ptrMeeting = CreateMeeting(10.74,10.90,4,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(10.27,13.58,4,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	if(FindMeeting(ptrStruct,10.74,&i,&status)!=0)
	{
		printf("%30.30s - %s\n","CheckFindMeetingFound","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckFindMeetingFound","Fail");
	}		
}
/*********************NUM OF MEETINGS TESTS**********************/
void CheckNumOfMeetings()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;
	int flag=0;

	ptrStruct = CreateDayMeetings(2,2);
	if(NumOfMeetings(ptrStruct) == 0)
	{
		flag++;	
	}
	ptrMeeting = CreateMeeting(10.18,10.80,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	if(NumOfMeetings(ptrStruct) == 1)
	{
		flag++;
	}
	
	RemoveMeeting (ptrStruct, 10.18);	
	if(NumOfMeetings(ptrStruct) == 0)
	{
		flag++;	
	}
	printf("%d\n", flag);
	if(flag==3)
	{
		printf("%30.30s - %s\n","CheckNumOfMeetings","Pass");
	}
	else
	{
		printf("%30.30s - %s\n","CheckNumOfMeetings","Fail");
	}
}

void CheckPrintMeetings()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;
	ptrStruct = CreateDayMeetings(0,5);
	ptrMeeting = CreateMeeting(10.18,10.80,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(5.10,10.80,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	RemoveMeeting (ptrStruct, 10.18);
	RemoveMeeting (ptrStruct, 10.18);
	ptrMeeting = CreateMeeting(13.10,15.10,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(5.00,07.00,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	DayMeetingsPrint(ptrStruct);
	printf("%d\n",status);
}
/***********************REMOVE MEETING TEST**************************/
void CheckRemoveMeetingNull()
{
	DayMeetings* ptrStruct;

	if(RemoveMeeting (NULL, 12.30) == ERR_NOT_INITIALIZED)
	{
		printf("%30.30s - %s\n","CheckRemoveMeetingNull","Pass");
	}
	else
		printf("%30.30s - %s\n","CheckRemoveMeetingNull","Fail");
}
/**********************************************************************/
void CheckRemoveMeetingInvalidStartTime()
{
	Meeting* ptrMeeting;
	DayMeetings* ptrStruct;
	ptrStruct = CreateDayMeetings(2,2);
	ptrMeeting = CreateMeeting(10.74,10.90,4,&status);
	AddMeeting(ptrStruct,ptrMeeting);

	if(RemoveMeeting (ptrStruct, 28.20) == ERR_INVALID_START_TIME)
	{
		printf("%30.30s - %s\n","CheckRemoveMeetingInvalidStartTime","Pass");
	}
	else
		printf("%30.30s - %s\n","CheckRemoveMeetingInvalidStartTime","Fail");	
}
/**********************************************************************/
void CheckRemoveMeetingNoMeetings()
{
	DayMeetings* ptrStruct;
	ptrStruct = CreateDayMeetings(2,2);	
	
	
	if(RemoveMeeting (ptrStruct, 12.10) == ERR_NO_MEETINGS_TODAY)
	{
		printf("%30.30s - %s\n","CheckRemoveMeetingNoMeetings","Pass");
	}
	else
		printf("%30.30s - %s\n","CheckRemoveMeetingNoMeetings","Fail");
}
/**********************************************************************/
void CheckRemoveMeetingNotFound()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(2,2);
	ptrMeeting = CreateMeeting(09.10,10.00,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);		

	if(RemoveMeeting (ptrStruct, 12.10) ==ERR_MEETING_NOT_FOUND)
	{
		printf("%30.30s - %s\n","CheckRemoveMeetinNotFound","Pass");
	}
	else
		printf("%30.30s - %s\n","CheckRemoveMeetinNotFound","Fail");
}
/**********************************************************************/
void CheckRemoveMeetingIsWorking()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(3,2);
	ptrMeeting = CreateMeeting(13.40,14.40,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	
	ptrMeeting = CreateMeeting(14.50,15.15,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	
	ptrMeeting = CreateMeeting(16.20,18.34,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);	
}

/**********************************************************************/
void CheckRemoveMeetingRealloc()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;

	ptrStruct = CreateDayMeetings(2,1);
	ptrMeeting = CreateMeeting(13.40,14.40,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(14.50,15.15,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	ptrMeeting = CreateMeeting(16.20,18.34,1,&status);
	AddMeeting(ptrStruct,ptrMeeting);
	RemoveMeeting (ptrStruct, 14.50);
	RemoveMeeting (ptrStruct, 16.20);
	if(Size(ptrStruct) == 2)
	{
		printf("%30.30s - %s\n","CheckRemoveMeetingRealloc","Pass");
	}
	else
		printf("%30.30s - %s\n","CheckRemoveMeetingRealloc","Fail");

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN DAIRY TESTS~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main (void)
{
	printf("/~~~~~~~~~~~~~~~~~~CREATE TESTS~~~~~~~~~~~~~~~/\n");
	CheckCreateNull ();
	CheckCreateSize1Blocksize0 ();
	CheckCreateSize0Blocksize1 ();
	CheckCreateSizeUnder0 ();
	CheckCreateIsWorking();
	printf("\n/~~~~~~~~~~~~~~~~DESTROY TESTS~~~~~~~~~~~~~~~/\n");
	CheckDestroyIsNull();
	CheckDestroyIsWorking();
	CheckDDestroy();
	printf("\n/~~~~~~~~~~~~CREATE MEETING TESTS~~~~~~~~~~~~/\n");
	CheckCreateMeetingIsWorking();
	CheckCreateMeetingInvalidSrartTime();
	CheckCreateMeetingInvalidEndTime();
	CheckCreateEndTimeIsEarlierThanStartTime();
	printf("\n/~~~~~~~~~~~~~~ADD MEETING TESTS~~~~~~~~~~~~~/\n");
	CheckAddMeetingDayMeetingsNull();
	CheckAddMeetingMeetingNull();
	CheckAddMeetingOverlap();
	CheckAddMeetingOverflow();
	CheckAddMeetingIsWorking();
	printf("\n/~~~~~~~~~~~~~~~~FIND MEETING TESTS~~~~~~~~~~~~~~~/\n");
	CheckFindMeetingNull();
	CheckFindMeetingNotFound();
	CheckFindMeetingFound();
	printf("\n/~~~~~~~~~~~~~~~~NUM OF MEETING TEST~~~~~~~~~~~~~~~/\n");
	CheckNumOfMeetings();
	CheckPrintMeetings();
	printf("\n/~~~~~~~~~~~~~~~~REMOVE MEETING TESTS~~~~~~~~~~~~~~~/\n");
	CheckRemoveMeetingNull();
	CheckRemoveMeetingInvalidStartTime();
	CheckRemoveMeetingNoMeetings();
	CheckRemoveMeetingNotFound();
	CheckRemoveMeetingIsWorking();
	CheckRemoveMeetingRealloc();
	
	

}
