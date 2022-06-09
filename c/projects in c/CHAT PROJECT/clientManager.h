#ifndef __CLIENT_MANAGER__
#define __CLIENT_MANAGER__

#define IP "127.0.0.1"
#define PORT 2000
#define USERNAME_LEN 10
#define PASSWORD_LEN 10
#define GROUP_NAME_LEN 20
#define IP_LEN 20
#define BUFFER_LEN 50

typedef struct Groupids Groupids;

/***************************************************************************************************************************************************/
/**
 * @brief function to run client manager
 */
static void ClientManager_Run();
/***************************************************************************************************************************************************/
/**
 * @brief fuction to make a registration to app.
 * 
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param _password char password
 * @param _logstatus 1 - case login , 0 - case logout
 * @param _userGroups pointer to list of pointers to user groups
 * @return int 1 when register succeed.
 */
static int ClientManager_Register(int _serverSock, char _username[USERNAME_LEN], char _password[PASSWORD_LEN], int* _logstatus, List** _userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief function to login app.
 * 
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param _password char password
 * @param logStatus 1 - case login , 0 - case logout
 * @param userGroups pointer to list of pointers to user groups
 * @param counter int counter to count num of login attempts.
 * @return int 1 on success login, 0 - otherwise.
 */
static int ClientManager_Login(int _serverSock, char _username[USERNAME_LEN], char _password[PASSWORD_LEN] ,int* logStatus, List** userGroups, int counter);
/***************************************************************************************************************************************************/
/**
 * @brief fucntion to remove all user groups in case he chooses to logout.
 * 
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_RemoveAllGroups(int _serverSock, char _username[USERNAME_LEN], List** userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief fucntion to remove a specific user group when choose to leave.
 * @param _groupName char name of group
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_RemoveGroup(char _groupName[GROUP_NAME_LEN], List** userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief function to make a logout, destroy all user groups, and change the log status to not logged(0);
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param logStatus 1 - case login , 0 - case logout
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_LogOut(int _serverSock, char _username[USERNAME_LEN], int* logStatus, List** userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief function to call the right function cased on client choise in main menu.
 *         1)register
 *         2)login
 *         3)Exit
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param choice  UserChoise type, the client choice to do.
 * @param logStatus 1 - case login , 0 - case logout
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_MainMenu(int _serverSock, char _username[USERNAME_LEN],UserChoise choice, int *logStatus, List** userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _buffer pointer to buffer packed and send to server.
 * @param _groupName char pointer to name of group
 * @param _username char pinter to  username 
 * @param _serverSock int sock of server
 * @param userGroups pointer to list of pointers to user groups
 */
static int join(char* _buffer, char* _groupName, char* _username, int _serverSock, List** userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _serverSock int sock of server
 * @param userGroups pointer to list of pointers to user groups
 * @param _username char username 
 */
static void ClientManager_LeaveGroup(int _serverSock, List** userGroups, char _username[USERNAME_LEN]);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _serverSock int sock of server
 * @param _username char pinter to username
 */
static void ClientManager_ShowGroups(int _serverSock, char* _username);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param choice  UserChoise type, the client choice to do.
 * @param logStatus 1 - case login , 0 - case logout
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_GroupsMenu(int _ServerSock, char _username[USERNAME_LEN], UserChoise choice, int *logStatus, List** userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_JoinGroup(int _ServerSock, char _username[USERNAME_LEN], List** _userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _serverSock int sock of server
 * @param _username char username 
 * @param userGroups pointer to list of pointers to user groups
 */
static void ClientManager_CreateGroup(int _serverSock, char _username[USERNAME_LEN], List** _userGroups);
/***************************************************************************************************************************************************/
/**
 * @brief 
 * @param _buffer pointer to buffer packed and send to server.
 * @param _groupName char pointer to name of group
 * @param _username char pinter to  username 
 * @param _serverSock int sock of server
 * @param userGroups pointer to list of pointers to user groups
 */
static int createGroup(char* _buffer, char* _groupName, char* _username, int _serverSock, List** userGroups)
/***************************************************************************************************************************************************/


#endif /*ifndef __CLIENT_MANAGER__*/

