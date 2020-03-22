/*
 * =====================================================================================
 *
 *       Filename:  ipmath.c
 *
 *    Description:  IP mathematics related functions
 *
 *        Version:  1.0
 *        Created:  03/19/2020 06:13:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karan Raval (), karanraval72@yahoo.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<math.h>
#include<string.h>

#define MAX 16
#define LOG 0 // 0 - Disable ; 1 - Enable

/* Function declarations */
void GetBroadcastAddress(char *ip_addr, char mask, char *op_addr);
unsigned long int GetIpIntegral(char *ip_addr);
void GetDottedIpformat(unsigned int ip_addr, char *buf);
void GetNwId(char *ip_addr, char mask, char *nw_id);
unsigned int GetIntMask(char mask);
unsigned int GetSubnetCardinality(char msk);
int CheckIpsubnetMembership(char *nw_id, char mask, char *check_ip);

int main(int argv, char **argc)
{
    if(argv != 2){
        printf("Usage : ./a.out <ip_addr in dotted decimal>\n");
        return 0 ;
    }
    char ipaddr_buf[MAX];
    char nw_id[MAX];
    char *ip_addr = argc[1];
    char mask = 20;
    char check_ip[MAX], network_id[MAX];
    char new_mask = 20;
    memset(ipaddr_buf, 0, MAX);
    GetBroadcastAddress(ip_addr, mask, ipaddr_buf);
    GetNwId(ip_addr, mask, nw_id);
    printf("Ip address is %s and it's Broadcast address is %s\n",ip_addr, ipaddr_buf);
    printf("Ip address is %s and it's NW id is %s\n",ip_addr, nw_id);
    printf("Max devices can be connected are %d\n",GetSubnetCardinality(mask));
    printf("Enter ipv4 address and nw id\n");
    scanf("%s %s",check_ip,network_id);
    if(CheckIpsubnetMembership(network_id, new_mask, check_ip))
        printf("Ip address belogns to the Nw_id\n");
    else
        printf("Ip address doesn't belong to Nw_id\n");
    return 0;
}
unsigned int GetIntMask(char mask)
{
   unsigned int mask_int =0;
   char i;
   for(i=0 ; i<mask ; i++){
       mask_int = mask_int | (1<<(31-i)) ;
   }
   return mask_int;
}
unsigned long int GetIpIntegral(char *ip_addr)
{
#if LOG
   printf("In GetIpIntegral...\n");
#endif
   int buf[4] ={0};
   int i,j=0;
   unsigned long int ip_int;
   for(i=0;ip_addr[i];i++){
       if(ip_addr[i] == '.'){
           i++;
           j++;
       }
       buf[j] = buf[j] * 10 + ip_addr[i] - 48 ;
   }
   ip_int = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
   return ip_int;
}
void GetDottedIpformat(unsigned int ip_addr, char *buf)
{
#if LOG
    printf("In GetDottedIpformat..\n");
#endif
    int temp[4];
    temp[0] = ip_addr >> 24 & 0xFF;
    temp[1] = ip_addr >> 16 & 0xFF;
    temp[2] = ip_addr >> 8 & 0xFF;
    temp[3] = ip_addr & 0xFF;
#if LOG
    printf("%d\n%d\n%d\n%d\n", temp[0], temp[1], temp[2], temp[3]);
#endif
    sprintf(buf, "%d.%d.%d.%d",temp[0], temp[1], temp[2], temp[3]);
#if LOG
    printf("buf = %s\n",buf);
#endif
}
void GetBroadcastAddress(char *ip_addr, char mask, char *op_addr)
{
#if LOG
   printf("In GetBroadcastAddress..\n");
#endif
   unsigned long int ip_int;
   unsigned int mask_int;
   ip_int = GetIpIntegral(ip_addr);
   mask_int = GetIntMask(mask);
#if LOG
   printf("ip_int = %lu\nmask_int =  %u\n", ip_int, mask_int);
#endif
   ip_int = ip_int | (~mask_int); 
#if LOG
   printf("ip_int = %lu\nmask_int =  %u\n", ip_int, mask_int);
#endif
   GetDottedIpformat(ip_int, op_addr);
   return;
}
void GetNwId(char *ip_addr, char mask, char *nw_id)
{
 #if LOG
    printf("In GetNwId...\n");
 #endif
    unsigned long int ip_int;
    unsigned mask_int;
    //Converting ip address into integer equivalent
    ip_int = GetIpIntegral(ip_addr);
    //Convering mask value into it's integer equivalent
    mask_int = GetIntMask(mask);
    ip_int = ip_int & (mask_int);
    //Converting integer ip address into dotted decimal format
    GetDottedIpformat(ip_int, nw_id);
    return;
}
unsigned int GetSubnetCardinality(char msk)
{
#if LOG
    printf("In GetSubnetCardinality...\n");
#endif
    unsigned int mask_int;
    mask_int = GetIntMask(msk);
    mask_int = (((~mask_int) + 1) - 2);
    return mask_int;
}
int CheckIpsubnetMembership(char *nw_id, char mask, char *check_ip)
{
    char temp[MAX];
    GetNwId(check_ip, mask, temp);
    if(strcmp(nw_id, temp))
        return 0;
    else
        return 1;
}
