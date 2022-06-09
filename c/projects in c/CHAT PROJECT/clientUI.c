#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientUI.h"
#include "Chat.h"

#define CREATEGROUP 1
#define JOINGROUP 2
#define LEAVEGROUP 3
#define LOGOUT 4
#define EXITAPP 5 
#define USERNAME_MIN_LEN 4
#define USERNAME_MAX_LEN 10
#define PASSWORD_MIN_LEN 6
#define PASSWORD_MAX_LEN 10
/***********************************************************************/
UserChoise ClientUI_HomePage()
{
    UserChoise mainMenu;
    while(1)
    {
        UICleanScreen();
        printf("-----Welcome to our awesome chat App!-----\n\n   choose an action from the menu below:\n\n");
        printf("(1) Register\n");
        printf("(2) LOGIN\n");
        printf("(3) EXIT\n");
        printf("\naction: ");
        scanf("%u", &mainMenu);
        switch(mainMenu)
        {
            case REGISTER:
                return mainMenu;
            case LOGIN:
                return mainMenu;
            case EXIT:
                puts("Thank you for using awesome chat App..\nApp is closing.. good bye!");
                sleep(2);
                exit(0);
            default:
                printf("wrong choise, please try again\n");
		sleep(6);
		ClientUI_HomePage();
                break;

                
        }
    }
}

void ClientUI_Counter(int counter)
{
    printf("You have left %d attempts\n", counter);
}

void ClientUI_Print(char* _username, int msg)
{
    switch (msg)
    {
    case REG_ERR: printf("username is occuppied, please try again\n"); break;
    case REG_SUCCESS: printf("\nYou registered successfully!\n your username is : %s\nwe transfer you to the main menu.\n", _username); break;
    case LOGIN_ERR: printf("wrong user name or password, please try again\n");break;
    case LOGIN_SUCCESS: printf("User %s Loged in!\n", _username);break;
    case JOIN_GROUP_ERR_ALREADY_IN: printf("you're already joined this group\n");break;
    case JOIN_GROUP_ERR_NOT_FOUND: printf("group not found, please try again\n");break;
    case LEAVE_GROUP_ERR: printf("couldn't find that group name");break;
    case LEAVE_GROUP_SUCCESS: printf("you left group: %s", _username);break;
    case CREATE_GROUP_ERR: printf("Group %s not found\n", _username);break;
    case LOG_OUT_SUCCESS: printf("Successfully Loged out!\n");break;
    case JOIN_GROUP_SUCCESS: printf("You joined group : %s!\n", _username); break;
    default:
        break;
    }
}
/***********************************************************************/
void ClientUI_UserDetails(char* _username, char* _password)
{
    while(1)
    {
        fflush(stdin);
        fflush(stdout);
        printf("please enter your Username (between 4-10 chars): \n");
        scanf("%s", _username);
        if(strlen(_username) < USERNAME_MIN_LEN)
        {
            printf("too short username, please try again\n");
            continue;
        }
        else if (strlen(_username) > USERNAME_MAX_LEN)
        {
            printf("too long username, please try again\n");
            continue;
        }
        else
        {
            break;
        }
    } 

    while(1)
    {
        fflush(stdin);
        fflush(stdout);
        printf("please enter your Password (between 6-10 chars): \n");
        scanf("%s", _password);
        if(strlen(_password) < PASSWORD_MIN_LEN)
        {
            printf("too short password, please try again");
            continue;
        }
        else if (strlen(_password) > PASSWORD_MAX_LEN)
        {
            printf("too long password, please try again");
            continue;
        }
        else
        {
            break;
        }
    } 
}

UserChoise ClientUI_GroupsMenu()
{
    UserChoise groupMenu;
    while(1)
    {
        UICleanScreen();
        printf("(1) Create Group\n");
        printf("(2) Join Group\n");
        printf("(3) Leave Group\n");
        printf("(4) Logout User\n");
        scanf("%u", &groupMenu);
        switch(groupMenu)
        {
            case CREATEGROUP:
                return CREATE_GROUP;
            case JOINGROUP:
                return JOIN_GROUP;
            case LEAVEGROUP:
                return LEAVE_GROUP;
            case LOGOUT:
                return LOG_OUT;
            default:
                printf("wrong choise, please try again\n");
                break;
        }
    }
}

/***********************************************************************/
void ClientUI_groupDetails(char* _groupName)
{
    while(1)
    {
        fflush(stdin);
        fflush(stdout);
        printf("please enter Group name (between 4-10 chars): \n");
        scanf("%s", _groupName);
        if(strlen(_groupName) < USERNAME_MIN_LEN)
        {
            printf("too short group name, please try again\n");
            continue;
        }
        else if (strlen(_groupName) > USERNAME_MAX_LEN)
        {
            printf("too long group name, please try again\n");
            continue;
        }
        else
        {
            break;
        }
    } 
}

/***********************************************************************/  
void UICleanScreen()
{
    system("clear");
}



