#ifndef __IP__
#define __IP__

#define NUM_OF_IPs 100
#define IP_ADD "224.0.0."

typedef struct GroupIPs GroupIPs;

/******************************************************/
/**
 * @brief create queue of ips
 * @return pointer of GroupIPs struct
 */
GroupIPs* IPs_Create();
/******************************************************/

/**
 * @brief destroy queue of ips
 * @param group_ips pointer to GroupIPs struct
 */
void IPs_Destroy(GroupIPs* group_ips);
/******************************************************/
/**
 * @brief insert ip addr to the end of the queue
 * @param group_ips pointer to GroupIPs struct
 * @param ip char pointer to ip addr
 */

void IPs_InsertIP(GroupIPs* group_ips, char* ip);
/******************************************************/

/**
 * @brief pull ip addr from queue and remove it
 * @param group_ips pointer to GroupIPs struct
 * @param ip pointer to char pointer to hold ip addr
 */
void IPs_RemoveIP(GroupIPs* group_ips, char* ip);
/******************************************************/


#endif /*#ifndef __IPs__*/
