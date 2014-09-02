#ifndef CRATEMSGTYPES_H
#define CRATEMSGTYPES_H

#define CRATEMSG_LISTEN_PORT			6102
#define MAX_MSG_SIZE						10000

#define CRATEMSG_HDR_ID					0x12345678

#define CRATEMSG_TYPE_READ16			0x01
#define CRATEMSG_TYPE_WRITE16			0x02
#define CRATEMSG_TYPE_READ32			0x03
#define CRATEMSG_TYPE_WRITE32			0x04
#define CRATEMSG_TYPE_DELAY			0x05
#define CRATEMSG_TYPE_READSCALERS	0x06


#define CMD_RSP(cmd)						(cmd | 0x80000000)

#define DW_SWAP(v)						( ((v>>24) & 0x000000FF) |\
												  ((v<<24) & 0xFF000000) |\
												  ((v>>8)  & 0x0000FF00) |\
												  ((v<<8)  & 0x00FF0000) )

#define HW_SWAP(v)						( ((v>>8) & 0x00FF) |\
												  ((v<<8) & 0xFF00) )
                					  
/*****************************************************/
/*********** Some Board Generic Commands *************/
/*****************************************************/

#define CRATE_MSG_FLAGS_NOADRINC		0x0
#define CRATE_MSG_FLAGS_ADRINC		0x1
#define CRATE_MSG_FLAGS_USEDMA		0x2

typedef struct
{
	int cnt;
	int addr;
	int flags;
} Cmd_Read16;

typedef struct
{
	int cnt;
	short vals[1];
} Cmd_Read16_Rsp;

typedef struct
{
	int cnt;
	int addr;
	int flags;
	short vals[1];
} Cmd_Write16;

typedef struct
{
	int cnt;
	int addr;
	int flags;
} Cmd_Read32;

typedef struct
{
	int cnt;
	int vals[1];
} Cmd_Read32_Rsp;

typedef struct
{
	int cnt;
	int addr;
	int flags;
	int vals[1];
} Cmd_Write32;

typedef struct
{
	int ms;
} Cmd_Delay;

typedef struct
{
	int cnt;
	unsigned int vals[1];
} Cmd_ReadScalers_Rsp;

/*****************************************************/
/*************** Main message structure **************/
/*****************************************************/
typedef struct
{
	int len;
	int type;
  
	union
	{
		Cmd_Read16				m_Cmd_Read16;
		Cmd_Read16_Rsp			m_Cmd_Read16_Rsp;
		Cmd_Write16				m_Cmd_Write16;
		Cmd_Read32				m_Cmd_Read32;
		Cmd_Read32_Rsp			m_Cmd_Read32_Rsp;
		Cmd_Write32				m_Cmd_Write32;
		Cmd_Delay				m_Cmd_Delay;
		Cmd_ReadScalers_Rsp	m_Cmd_ReadScalers_Rsp;
		unsigned char			m_raw[MAX_MSG_SIZE];
	} msg;
} CrateMsgStruct;

/*****************************************************/
/************* Server message interface **************/
/*****************************************************/
typedef struct
{
	int (*Read16)(Cmd_Read16 *pCmd_Read16, Cmd_Read16_Rsp *pCmd_Read16_Rsp);
	int (*Write16)(Cmd_Write16 *pCmd_Write16);
	int (*Read32)(Cmd_Read32 *pCmd_Read32, Cmd_Read32_Rsp *pCmd_Read32_Rsp);
	int (*Write32)(Cmd_Write32 *pCmd_Write32);
	int (*Delay)(Cmd_Delay *pCmd_Delay);
	int (*ReadScalers)(Cmd_ReadScalers_Rsp *pCmd_ReadScalers_Rsp);
} ServerCBFunctions;

int CrateMsgServerStart(ServerCBFunctions *pCB, unsigned short listen_port);

/******************************************************
*******************************************************
******************************************************/

#endif
