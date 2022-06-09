#include <stdlib.h>
#include "Group.h"
#include <string.h>
#define IP_SIZE 15
#define CHAR_NUM 15
#define PORT_ID "2000"


struct Group
{
    char m_groupname[CHAR_NUM];
    char m_groupIP[IP_SIZE];
    char*  m_port;
    int  m_numOfMembers;
};

/***********************************Group Create**************************************************/
Group * CreateGroup(char * _groupName, char * _groupIP)
{
    Group * newGroup = (Group*) malloc(sizeof(Group));
    if(newGroup == NULL)
    {
        return NULL;
    }

    strcpy(newGroup -> m_groupname, _groupName);
    strcpy(newGroup -> m_groupIP, _groupIP);
    newGroup -> m_port = PORT_ID;
    newGroup -> m_numOfMembers = 0;

    return newGroup;
}

/***********************************Group Destroy*************************************************/
void DestroyGroup(Group ** _group)
{
    if(_group == NULL || *_group == NULL)
    {
        return;
    }

    free(*_group);
    *_group == NULL;
}

/***********************************Group Get*****************************************************/
char * GetGroupIP(Group * _group)
{
    return _group -> m_groupIP;
}

char * GetGroupName(Group * _group)
{
    return _group -> m_groupname;
}

char* GetGroupPort(Group * _group)
{
    return _group -> m_port;
}

int GetNumOfMembers(Group * _group)
{
    return _group -> m_numOfMembers;
}

int PlusMemberToCount(Group * _group)
{
    _group -> m_numOfMembers += 1;
    return _group -> m_numOfMembers;
}

int MinusMemberFromCount(Group * _group)
{
    _group -> m_numOfMembers -= 1;
    if(_group -> m_numOfMembers == 0)
    {
        DestroyGroup(&_group);
        return 0;
    }
    return _group -> m_numOfMembers;
}
