#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/mman.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CrateMsgTypes.h"

static ServerCBFunctions gServerCBFucntions;
short gListenPort;

typedef struct
{
	int sock;
	CrateMsgStruct msg;
} SocketThreadStruct;

int CrateMsg_Read16(CrateMsgStruct *msg, int swap)
{
	if(swap)
	{
		msg->msg.m_Cmd_Read16.cnt = DW_SWAP(msg->msg.m_Cmd_Read16.cnt);
		msg->msg.m_Cmd_Read16.addr = DW_SWAP(msg->msg.m_Cmd_Read16.addr);
		msg->msg.m_Cmd_Read16.flags = DW_SWAP(msg->msg.m_Cmd_Read16.flags);
	}
	if(gServerCBFucntions.Read16)
		return (*gServerCBFucntions.Read16)(&msg->msg.m_Cmd_Read16, &msg->msg.m_Cmd_Read16_Rsp);
	
	return 0;
}

int CrateMsg_Write16(CrateMsgStruct *msg, int swap)
{
	int i;
	
	if(swap)
	{
		msg->msg.m_Cmd_Write16.cnt = DW_SWAP(msg->msg.m_Cmd_Write16.cnt);
		msg->msg.m_Cmd_Write16.addr = DW_SWAP(msg->msg.m_Cmd_Write16.addr);
		msg->msg.m_Cmd_Write16.flags = DW_SWAP(msg->msg.m_Cmd_Write16.flags);
		
		for(i = msg->msg.m_Cmd_Write16.cnt-1; i >= 0; i--)
			msg->msg.m_Cmd_Write16.vals[i] = HW_SWAP(msg->msg.m_Cmd_Write16.vals[i]);		
	}
	if(gServerCBFucntions.Write16)
		(*gServerCBFucntions.Write16)(&msg->msg.m_Cmd_Write16);
	
	return 0;
}

int CrateMsg_Read32(CrateMsgStruct *msg, int swap)
{
	if(swap)
	{
		msg->msg.m_Cmd_Read32.cnt = DW_SWAP(msg->msg.m_Cmd_Read32.cnt);
		msg->msg.m_Cmd_Read32.addr = DW_SWAP(msg->msg.m_Cmd_Read32.addr);
		msg->msg.m_Cmd_Read32.flags = DW_SWAP(msg->msg.m_Cmd_Read32.flags);
	}
	if(gServerCBFucntions.Read32)
		return (*gServerCBFucntions.Read32)(&msg->msg.m_Cmd_Read32, &msg->msg.m_Cmd_Read32_Rsp);
	
	return 0;
}

int CrateMsg_Write32(CrateMsgStruct *msg, int swap)
{
	int i;
	
	if(swap)
	{
		msg->msg.m_Cmd_Write32.cnt = DW_SWAP(msg->msg.m_Cmd_Write32.cnt);
		msg->msg.m_Cmd_Write32.addr = DW_SWAP(msg->msg.m_Cmd_Write32.addr);
		msg->msg.m_Cmd_Write32.flags = DW_SWAP(msg->msg.m_Cmd_Write32.flags);
		
		for(i = msg->msg.m_Cmd_Write32.cnt-1; i >= 0; i--)
			msg->msg.m_Cmd_Write32.vals[i] = DW_SWAP(msg->msg.m_Cmd_Write32.vals[i]);
	}
	if(gServerCBFucntions.Write32)
		(*gServerCBFucntions.Write32)(&msg->msg.m_Cmd_Write32);
	
	return 0;
}

int CrateMsg_Delay(CrateMsgStruct *msg, int swap)
{
	if(swap)
		msg->msg.m_Cmd_Delay.ms = DW_SWAP(msg->msg.m_Cmd_Delay.ms);
	if(gServerCBFucntions.Delay)
		(*gServerCBFucntions.Delay)(&msg->msg.m_Cmd_Delay);
	
	return 0;
}

int CrateMsg_ReadScalers(CrateMsgStruct *msg, int swap)
{
	if(gServerCBFucntions.Delay)
		return (*gServerCBFucntions.ReadScalers)(&msg->msg.m_Cmd_ReadScalers_Rsp);
	
	return 0;
}

void *ConnectionThread(void *parm)
{
	int swap, result, val;
	SocketThreadStruct *pParm = (SocketThreadStruct *)parm;

	val = CRATEMSG_HDR_ID;
	if(send(pParm->sock, &val, 4, 0) <= 0) 
	{
		printf("Error in %s: failed to send HDRID\n", __FUNCTION__);
		goto ConnectionThread_exit;
	}
	
	if(recv(pParm->sock, &val, 4, 0) != 4)
	{
		printf("Error in %s: failed to recv HDRID\n", __FUNCTION__);
		goto ConnectionThread_exit;
	}

	// determine sender endianess...
	if(val == CRATEMSG_HDR_ID)
	{
		printf("swap=0\n");
		swap = 0;
	}
	else if(val == DW_SWAP(CRATEMSG_HDR_ID))
	{
		printf("swap=1\n");
		swap = 1;
	}
	else
	{
		printf("Error in %s: bad recv HDRID\n", __FUNCTION__);
		goto ConnectionThread_exit;
	}
	
	while(1)
	{
		if(recv(pParm->sock, (char *)&pParm->msg, 8, 0) != 8)
			break;
		
		if(swap)
		{
			pParm->msg.len = DW_SWAP(pParm->msg.len);
			pParm->msg.type = DW_SWAP(pParm->msg.type);
		}
		
		if( (pParm->msg.len > MAX_MSG_SIZE) || (pParm->msg.len < 0) )
			break;
		
		if(pParm->msg.len && (recv(pParm->sock, (char *)&pParm->msg.msg, pParm->msg.len, 0) != pParm->msg.len))
			break;
		
		result = -1;	
		if(pParm->msg.type == CRATEMSG_TYPE_READ16)
			result = CrateMsg_Read16(&pParm->msg, swap);
		else if(pParm->msg.type == CRATEMSG_TYPE_WRITE16)
			result = CrateMsg_Write16(&pParm->msg, swap);
		else if(pParm->msg.type == CRATEMSG_TYPE_READ32)
			result = CrateMsg_Read32(&pParm->msg, swap);
		else if(pParm->msg.type == CRATEMSG_TYPE_WRITE32)
			result = CrateMsg_Write32(&pParm->msg, swap);
		else if(pParm->msg.type == CRATEMSG_TYPE_DELAY)
			result = CrateMsg_Delay(&pParm->msg, swap);
		else if(pParm->msg.type == CRATEMSG_TYPE_READSCALERS)
			result = CrateMsg_ReadScalers(&pParm->msg, swap);
		else
		{
			printf("Error in %s: unhandled message type %u\n", __FUNCTION__, pParm->msg.type);
			break;
		}
		
		if(result < 0)
		{
			printf("Error in %s: failed to process msg type %u\n", __FUNCTION__, pParm->msg.type);
			break;
		}
		else if(result > 0)
		{
			pParm->msg.len = result;
			pParm->msg.type = CMD_RSP(pParm->msg.type);
			if(send(pParm->sock, &pParm->msg, pParm->msg.len+8, 0) <= 0) 
			{
				printf("Error in %s: failed to send msg type %u\n", __FUNCTION__, pParm->msg.type);
				break;
			}
		}
	}
	
ConnectionThread_exit:
	printf("Closing connection...\n");
	
	close(pParm->sock);
	free(pParm);
	
	pthread_exit(NULL);
	
	return 0;
}

void *ListenerThread(void *p)
{
	pthread_t cThread;
	SocketThreadStruct *pcThreadParm;
	socklen_t sockAddrSize = sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;
	struct sockaddr_in serverAddr;
	int lsock, csock;

	memset((char *)&serverAddr, 0, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(gListenPort);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if(lsock == -1)
	{
		printf("Error in %s: create socket failed\n", __FUNCTION__);
		return 0;
	}
	
	if(bind(lsock, (struct sockaddr *)&serverAddr, sockAddrSize) == -1)
	{
		printf("Error in %s: bind() failed\n", __FUNCTION__);
		close(lsock);
		return 0;
	}
	
	if(listen(lsock, 1) == -1)
	{
		printf("Error in %s: listen() failed\n", __FUNCTION__);
		close(lsock);
		return 0;
	}

	while(1)
	{
		csock = accept(lsock, (struct sockaddr *)&clientAddr, &sockAddrSize);
		if(csock < 0)
		{
			printf("Error in %s: accept() failed\n", __FUNCTION__);
			break;
		}
		pcThreadParm = (SocketThreadStruct *)malloc(sizeof(SocketThreadStruct));;
		pcThreadParm->sock = csock;
		if(!pcThreadParm)
		{
			printf("Error in %s: malloc() failed\n", __FUNCTION__);
			break;
		}
		pthread_create(&cThread, NULL, ConnectionThread, (void *)pcThreadParm);
	}
	close(lsock);
	
	return 0;
}

int CrateMsgServerStart(ServerCBFunctions *pCB, unsigned short listen_port)
{
	pthread_t gListenerThread;
	
	gListenPort = listen_port;

	memcpy(&gServerCBFucntions, pCB, sizeof(ServerCBFunctions));
	
	pthread_create(&gListenerThread, NULL, ListenerThread, NULL);
	
	return 0;
}
