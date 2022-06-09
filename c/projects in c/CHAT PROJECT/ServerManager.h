#ifndef __SERVERMANAGER_H__
#define __SERVERMANAGER_H__
#include <stdlib.h>
#include "GroupsManager.h"
#include "UserManager.h"
#include "Protocols.h"



typedef struct ServerManager ServerManager;


ServerManager* createServerManager();


int regisNewUser(struct usageDetails *details, void* bufBack, UsersManager* userManager);

int LogInUser(struct usageDetails *details, void* bufBack, UsersManager* userManager, int _clientID);

int createGroup(struct IPsAnswer *IPdetails,struct usageDetails *_details,
 	void* _bufBack, UsersManager* _userManager, GroupsManager *_groupsManager);

int joinGroup(struct IPsAnswer *IPdetails, struct usageDetails *_details,
	 void* _bufBack, UsersManager* _userManager, GroupsManager *_groupsManager);
int showGroups(struct usageDetails *_details, void* _bufBack,GroupsManager *_groupsManager);

#endif

