#include <stdio.h>
#include <stdlib.h>
#include "diary.h"
#include "ADTDefs.h"
int room;
float startTime;
float endTime;
int main()
{
	DayMeetings* ptrStruct;
	Meeting* ptrMeeting;
    int ch, exit = 0;
    ADTErr status;
    int meetingIndex;
	ptrStruct=CreateDayMeetings(3, 4); 
    while (!exit)
	{
		printf("\n\n\t********************************\n");
		printf("\t    Daily Appointment Diary\n");
		printf("\t********************************");
		printf("\n\n\t\t:MAIN MENU:");
		printf("\n\n\tPress <1> To ADD APPOINTMENT\t");
		printf("\n\tPress <2> To REMOVE APPOINTMENT\t");
	 	printf("\n\tPress <3> To Find Meeting APPOINTMENT\t");
		printf("\n\tPress <4> To Print All Meetings For Today\t\t");
		printf("\n\tPress <5> To Delete All Meetings For Today\t\t");
		printf("\n\tPress <6> To EXIT\t\t");   
		printf("\n\n\tENTER YOUR CHOICE:");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1:
			printf ( "\n\tENTER BEGIN HOUR OF YOUR MEETING:[hh.mm]:");
			scanf("%f",&startTime);
			printf ( "\n\tENTER END HOUR OF YOUR MEETING:[hh.mm]:");
			scanf("%f",&endTime);
			printf ( "\n\tENTER ROOM NUMBER {1,2,3}:");
			scanf("%d",&room);
			ptrMeeting = CreateMeeting(startTime, endTime, room, &status);
		    status = AddMeeting (ptrStruct, ptrMeeting);
		    if(status != ERR_OK)
		    {
		    	putchar('\n');
		    	PrintErr(status);
		    	putchar('\n');
		    }
		    PrintErr(AddMeeting (ptrStruct,ptrMeeting));	
		    printf("\nYOUR MEETING IS ADDED SUCCESSFULLY...\n");
		    printf("\nA MEETING SCHEDULED IN ROOM NUMBER %d\n", room);
		    break;
		case 2:
	   	    printf("please enter start time of the meeting to remove\n");
			scanf("%f",&startTime);
			printf ("\n");
			PrintErr(RemoveMeeting (ptrStruct,startTime));
		    break;
		case 3:
	   		printf ("\n");			
			printf("please enter start time of the meeting to find\n");			
			scanf("%f",&startTime);
		    FindMeeting(ptrStruct,startTime, &meetingIndex ,&status);
			PrintOneMeeting(ptrStruct, meetingIndex);
		    break;
		case 4:
			DayMeetingsPrint(ptrStruct);
			break;
		case 5:
			DayMeetingsDestroy(ptrStruct);
			printf ("All meetings deleted.\n");
		case 6: 
			exit = 1;
			break;
		default:
		    printf("\nYOU ENTERED WRONG CHOICE..");
		    printf("\nPRESS ANY KEY TO TRY AGAIN");
		    break;
		}
	}
}
