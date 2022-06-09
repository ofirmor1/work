#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GenericQueue.h"
#include "IP.h"

#define IP_ADD_LEN 12
#define BUF_LEN 4
#define NUM_OF_IPs 100
#define IP_ADD "224.0.0."


struct GroupIPs
{
    Queue* m_ips;
};

void IPs_Init(Queue* group_ips)
{
	char buffer[BUF_LEN];
	int index;
	char* ipaddr;
	
	for (index = 1; index <= NUM_OF_IPs; index++)
	{
		ipaddr = calloc(IP_ADD_LEN,sizeof(char));

		strcpy(ipaddr,IP_ADD);
		sprintf(buffer,"%d",index);
		strcat(ipaddr,buffer);
		QueueInsert(group_ips,ipaddr);
	}
}

GroupIPs* IPs_Create()
{
    GroupIPs* groopIPs;
    groopIPs = (GroupIPs*)malloc(sizeof(GroupIPs));
    if(NULL == groopIPs)
    {
        return NULL;
    }
    groopIPs->m_ips = QueueCreate(NUM_OF_IPs);
    if(NULL == groopIPs->m_ips)
    {
        free(groopIPs);
        return NULL;
    }
    IPs_Init(groopIPs->m_ips);

    return groopIPs;
}

static void Destroy_Item(void* _item)
{
    free(_item);
}
static int Print_Item(const void* _item, void* _contex)
{
    printf("%s \n", (char*)_item);
}
static void IPs_Print(GroupIPs* group_ips)
{
    QueueForEach(group_ips->m_ips, Print_Item, NULL);
}

void IPs_Destroy(GroupIPs* group_ips)
{
    QueueDestroy(&(group_ips->m_ips), Destroy_Item);
}

void IPs_RemoveIP(GroupIPs* group_ips, char* ip)
{
    char* tmp;
    QueueRemove(group_ips->m_ips, (void*)&tmp);
    strcpy(ip, tmp);
}

void IPs_InsertIP(GroupIPs* group_ips, char* ip)
{
    QueueInsert(group_ips->m_ips, (void*)ip);
}



