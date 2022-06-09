#ifndef __client_UI__
#define __client_UI__
#include "Chat.h"

/***********************************************************************/
/**
 * @brief function to display menu to user and get his choise
 * 
 * @return user choise from menu:
*           1 - register
            2 - login
            3 - exit
 */
UserChoise ClientUI_HomePage();
/***********************************************************************/
/**
 * @brief Get the username and password the user entered
 * @param _userName char pointer to username that the user enter
 * @param _password char pointer to username that the user enter
 * @return None(void)
 */
void ClientUI_UserDetails(char* _userName, char* _password);
/***********************************************************************/ 
/**
 * @brief Function to clean the screen
 * @return None(void)
 */
void UICleanScreen();
void ClientUI_Print(char* _userName, int msg);
void ClientUI_Counter(int counter);

#endif /*#ifndef __client_UI__*/



