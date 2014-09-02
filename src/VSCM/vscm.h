#ifndef VSCM_H
#define VSCM_H

#define FSSR_SCR_BCONUM_START		240

#define FSSR_SEL_HFCB1_U1			0
#define FSSR_SEL_HFCB1_U2			1
#define FSSR_SEL_HFCB1_U3			2
#define FSSR_SEL_HFCB1_U4			3
#define FSSR_SEL_HFCB2_U1			4
#define FSSR_SEL_HFCB2_U2			5
#define FSSR_SEL_HFCB2_U3			6
#define FSSR_SEL_HFCB2_U4			7
#define FSSR_SEL_ALL				8

#define FSSR_CMD_READ				0x4
#define FSSR_CMD_WRITE				0x1
#define FSSR_CMD_SET				0x2
#define FSSR_CMD_RESET				0x5
#define FSSR_CMD_DEFAULT			0x6

#define FSSR_ADDR_REG_DISC_THR0		0x08
#define FSSR_ADDR_REG_DISC_THR1		0x09
#define FSSR_ADDR_REG_DISC_THR2		0x0A
#define FSSR_ADDR_REG_DISC_THR3		0x0B
#define FSSR_ADDR_REG_DISC_THR4		0x0C
#define FSSR_ADDR_REG_DISC_THR5		0x0D
#define FSSR_ADDR_REG_DISC_THR6		0x0E
#define FSSR_ADDR_REG_DISC_THR7		0x0F
#define FSSR_ADDR_REG_ALINES		0x10
#define FSSR_ADDR_REG_KILL			0x11
#define FSSR_ADDR_REG_INJECT		0x12
#define FSSR_ADDR_REG_SENDDATA		0x13
#define FSSR_ADDR_REG_REJECTHITS	0x14
#define FSSR_ADDR_REG_WILDREG		0x15
#define FSSR_ADDR_REG_SPR			0x18
#define FSSR_ADDR_REG_DCR			0x1B
#define FSSR_ADDR_REG_SCR			0x1C
#define FSSR_ADDR_REG_AQBCO			0x1E

#define FSSR_ALINES_6				0x3

#define FSSR_DCR_MOD256				0x10

#define IO_MUX_0				0
#define IO_MUX_1				1
#define IO_MUX_PULSER			2
#define IO_MUX_FPINPUT0			3
#define IO_MUX_FPINPUT1			4
#define IO_MUX_FPINPUT2			5
#define IO_MUX_FPINPUT3			6
#define IO_MUX_SWB_SYNC			7
#define IO_MUX_SWB_TRIG1		8
#define IO_MUX_SWB_TRIG2		9
#define IO_MUX_SWA_GPIO0		10
#define IO_MUX_SWA_GPIO1		11
#define IO_MUX_SWB_GPIO0		12
#define IO_MUX_SWB_GPIO1		13
#define IO_MUX_BUSY				14
#define IO_MUX_FSSRHIT			15
#define IO_MUX_DAC_TRIGGER		16
#define IO_MUX_DAC_TRIGGER_DLY	17
#define IO_MUX_BCOCLK			18
#define IO_MUX_TOKENOUT			19
#define IO_MUX_TOKENIN			20

#define FSSR_H1_U1_IDX		0
#define FSSR_H1_U2_IDX		1
#define FSSR_H1_U3_IDX		2
#define FSSR_H1_U4_IDX		3
#define FSSR_H2_U1_IDX		4
#define FSSR_H2_U2_IDX		5
#define FSSR_H2_U3_IDX		6
#define FSSR_H2_U4_IDX		7

typedef struct
{
/* 0x0000-0x0003 */	unsigned int LastStatusWord;
/* 0x0004-0x0007 */ unsigned int ScalerStatusWord;
/* 0x0008-0x000B */ unsigned int ScalerEvent;
/* 0x000C-0x000F */ unsigned int ScalerWords;
/* 0x0010-0x0013 */ unsigned int ScalerIdle;
/* 0x0014-0x0017 */ unsigned int ScalerAqBco;
/* 0x0018-0x001B */ unsigned int ScalerMarkErr;
/* 0x001C-0x001F */ unsigned int ScalerEncErr;
/* 0x0020-0x0023 */ unsigned int ScalerChipIdErr;
/* 0x0024-0x0027 */ unsigned int Dummy1[(0x0028-0x0024)/4];
/* 0x0028-0x002B */ unsigned int ScalerGotHit;
/* 0x002C-0x002F */ unsigned int ScalerStrip;
/* 0x0030-0x0033 */ unsigned int ScalerRef;
/* 0x0034-0x0037 */ unsigned int ScalerStripTime;
/* 0x0038-0x003B */ unsigned int ScalerCoreTalking;
/* 0x003C-0x00FF */ unsigned int Dummy2[(0x0100-0x003C)/4];
} FssrStatus;

typedef struct
{
/* 0x0000-0x0003 */	volatile unsigned int FirmwareRev;
/* 0x0004-0x0007 */ volatile unsigned int BoardId;
/* 0x0008-0x0013 */ volatile unsigned int Dummy0[(0x0014-0x0008)/4];
/* 0x0014-0x0017 */ volatile unsigned int SpiFlash;
/* 0x0018-0x001B */ volatile unsigned int TokenIn;
/* 0x001C-0x001F */ volatile unsigned int TokenOut;
/* 0x0020-0x0023 */ volatile unsigned int SdLink;
/* 0x0024-0x0027 */ volatile unsigned int Trigout;
/* 0x0028-0x002B */ volatile unsigned int BlockCfg;
/* 0x002C-0x002F */ volatile unsigned int Dummy2[(0x0030-0x002C)/4];
/* 0x0030-0x0033 */ volatile unsigned int ClockCfg;
/* 0x0034-0x0037 */ volatile unsigned int AD32M;
/* 0x0038-0x003B */ volatile unsigned int Dummy3[(0x003C-0x0038)/4];
/* 0x003C-0x003F */ volatile unsigned int TrigBusyThr;
/* 0x0040-0x0043 */ volatile unsigned int TrigSrc;
/* 0x0044-0x0047 */ volatile unsigned int AD32;
/* 0x0048-0x004B */ volatile unsigned int Interrupt;
/* 0x004C-0x004F */ volatile unsigned int InterruptAck;
/* 0x0050-0x0053 */ volatile unsigned int Geo;
/* 0x0054-0x0057 */ volatile unsigned int FifoWordCnt;
/* 0x0058-0x005B */ volatile unsigned int FifoEventCnt;
/* 0x005C-0x005F */ volatile unsigned int ReadoutCfg;
/* 0x0060-0x0063 */ volatile unsigned int SramDbgAdr;
/* 0x0064-0x0067 */ volatile unsigned int SramDbgData;
/* 0x0068-0x006B */ volatile unsigned int Reset;
/* 0x006C-0x006F */ volatile unsigned int FssrClkCfg;
/* 0x0070-0x0077 */ volatile unsigned int Dummy4[(0x0078-0x0070)/4];
/* 0x0078-0x007B */ volatile unsigned int ScalerLatch;
/* 0x007C-0x007F */ volatile unsigned int Dummy5[(0x0080-0x007C)/4];
/* 0x0080-0x0083 */ volatile unsigned int FssrSerCfg;
/* 0x0084-0x0093 */ volatile unsigned int FssrSerData[4];
/* 0x0094-0x0097 */ volatile unsigned int DacCfg;
/* 0x0098-0x009B */ volatile unsigned int DacCh0;
/* 0x009C-0x009F */ volatile unsigned int DacCh1;
/* 0x00A0-0x00A3 */ volatile unsigned int FssrSerClk;
/* 0x00A4-0x00A7 */ volatile unsigned int FssrAddrH1;
/* 0x00A8-0x00AB */ volatile unsigned int FssrAddrH2;
/* 0x00AC-0x00FF */ volatile unsigned int Dummy6[(0x0100-0x00AC)/4];
/* 0x0100-0x0103 */ volatile unsigned int Trigger;
/* 0x0104-0x0107 */ volatile unsigned int Sync;
/* 0x0108-0x010B */ volatile unsigned int SwAGpio;
/* 0x010C-0x010F */ volatile unsigned int SwBGpio;
/* 0x0110-0x011F */ volatile unsigned int Dummy7[(0x0120-0x0110)/4];
/* 0x0120-0x0123 */ volatile unsigned int PulserPeriod;
/* 0x0124-0x0127 */ volatile unsigned int PulserHigh;
/* 0x0128-0x0137 */ volatile unsigned int FpInput[4];
/* 0x0138-0x0147 */ volatile unsigned int FpOutput[4];
/* 0x0148-0x014B */ volatile unsigned int TriggerWindow;
/* 0x014C-0x014F */ volatile unsigned int DACTrigger;
/* 0x0150-0x0153 */ volatile unsigned int PulserN;
/* 0x0154-0x0157 */ volatile unsigned int PulserStart;
/* 0x0158-0x015B */ volatile unsigned int PulserStatus;
/* 0x015C-0x0FC7 */ volatile unsigned int Dummy8[(0x0FC8-0x015C)/4];
/* 0x0FC8-0x0FD7 */ volatile unsigned int ScalerFpOutput[4];
/* 0x0FD8-0x0FE7 */ volatile unsigned int ScalerFpInput[4];
/* 0x0FE8-0x0FEB */ volatile unsigned int ScalerBusy;
/* 0x0FEC-0x0FEF */ volatile unsigned int ScalerBusyCycles;
/* 0x0FF0-0x0FF3 */ volatile unsigned int ScalerVmeClk;
/* 0x0FF4-0x0FF7 */ volatile unsigned int ScalerSync;
/* 0x0FF8-0x0FFB */ volatile unsigned int ScalerTrig1;
/* 0x0FFC-0x0FFF */ volatile unsigned int ScalerTrig2;
/* 0x1000-0x10FF */ volatile FssrStatus Fssr[8];
} VSCM_regs;

unsigned int VSCM_ReadReg(unsigned int addr);
void VSCM_WriteReg(unsigned int addr, unsigned int val);	

#endif
