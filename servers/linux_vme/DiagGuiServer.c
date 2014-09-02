#include <sys/mman.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "CrateMsgTypes.h"
#include "jvme.h"

void sig_handler(int signo);

ServerCBFunctions gCrateServerCBFcn;

int swap32(int val)
{
	return DW_SWAP(val);
}

short swap16(short val)
{
	return HW_SWAP(val);
}

int Vme_Read16(Cmd_Read16 *pCmd_Read16, Cmd_Read16_Rsp *pCmd_Read16_Rsp)
{
	short *pRd;
	short *pWr = (short *)((long)pCmd_Read16_Rsp->vals);
	int c = pCmd_Read16->cnt;
	int size = 4+2*c;

	vmeBusToLocalAdrs(0x39, (char *)((long)pCmd_Read16->addr),(char **)&pRd);

	pCmd_Read16_Rsp->cnt = c;	
	
	vmeBusLock();
	if(pCmd_Read16->flags & CRATE_MSG_FLAGS_ADRINC)
		while(c--) *pWr++ = swap16(*pRd++);
	else
		while(c--) *pWr++ = swap16(*pRd);
	vmeBusUnlock();

	return size;
}

int Vme_Write16(Cmd_Write16 *pCmd_Write16)
{
	short *pRd = pCmd_Write16->vals;
	short *pWr;
	int c = pCmd_Write16->cnt;
	
	vmeBusToLocalAdrs(0x39, (char *)((long)pCmd_Write16->addr),(char **)&pWr);

	vmeBusLock();
	if(pCmd_Write16->flags & CRATE_MSG_FLAGS_ADRINC)
		while(c--) *pWr++ = swap16(*pRd++);
	else
		while(c--) *pWr = swap16(*pRd++);
	vmeBusUnlock();

	return 0;
}

int Vme_Read32(Cmd_Read32 *pCmd_Read32, Cmd_Read32_Rsp *pCmd_Read32_Rsp)
{
	int *pRd;
	int *pWr = pCmd_Read32_Rsp->vals;
	int c = pCmd_Read32->cnt;
	int size = 4+4*c;

	vmeBusToLocalAdrs(0x39, (char *)((long)pCmd_Read32->addr),(char **)&pRd);

	pCmd_Read32_Rsp->cnt = c;	

	vmeBusLock();
	if(pCmd_Read32->flags & CRATE_MSG_FLAGS_ADRINC)
		while(c--) *pWr++ = swap32(*pRd++);
	else
		while(c--) *pWr++ = swap32(*pRd);
	vmeBusUnlock();

	return size;
}

int Vme_Write32(Cmd_Write32 *pCmd_Write32)
{
	int *pRd = pCmd_Write32->vals;
	int *pWr;
	int c = pCmd_Write32->cnt;
	
	vmeBusToLocalAdrs(0x39, (char *)((long)pCmd_Write32->addr),(char **)&pWr);

	vmeBusLock();
	if(pCmd_Write32->flags & CRATE_MSG_FLAGS_ADRINC)
		while(c--) *pWr++ = swap32(*pRd++);
	else
		while(c--) *pWr = swap32(*pRd++);
	vmeBusUnlock();

	return 0;
}

int Vme_ReadScalers(Cmd_ReadScalers_Rsp *pCmd_ReadScalers_Rsp)
{
	int len = 0;
	
	pCmd_ReadScalers_Rsp->cnt = len>>2;
		
	return len+4;
}

int Vme_Delay(Cmd_Delay *pCmd_Delay)
{
	usleep(1000*pCmd_Delay->ms);
	
	return 0;
}

int main(int argc, char *argv[])
{
	int stat;
	
	if(signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("signal");
		exit(0);
	}

	vmeSetQuietFlag(1);
	stat = vmeOpenDefaultWindows();
	if(stat != OK)
		goto CLOSE;

//	stat = crateShmCreate();
//	if(stat != OK)
//		goto CLOSE;

// Run socket server
	gCrateServerCBFcn.Read16 = Vme_Read16;
	gCrateServerCBFcn.Write16 = Vme_Write16;
	gCrateServerCBFcn.Read32 = Vme_Read32;
	gCrateServerCBFcn.Write32 = Vme_Write32;
	gCrateServerCBFcn.Delay = Vme_Delay;
	gCrateServerCBFcn.ReadScalers = Vme_ReadScalers;
	
	printf("Starting CrateMsgServer...");
	CrateMsgServerStart(&gCrateServerCBFcn, CRATEMSG_LISTEN_PORT);
	printf("Done.\n");

	while(1)
		sleep(1);
	
CLOSE:
	vmeOpenDefaultWindows();
	
	return 0;
}

void closeup()
{
	vmeOpenDefaultWindows();
	printf("DiagGUI server closed...\n");
}

void sig_handler(int signo)
{
	printf("%s: signo = %d\n",__FUNCTION__,signo);
	switch(signo)
	{
		case SIGINT:
			closeup();
			exit(1);  /* exit if CRTL/C is issued */
	}
}
