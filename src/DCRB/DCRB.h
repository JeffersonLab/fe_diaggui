#ifndef DCRB_H
#define DCRB_H

/* Config Peripheral: Board information, fpga flash update */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int EnableN;
  /* 0x0004-0x0007 */ volatile unsigned int DeadCycles;
  /* 0x0008-0x000B */ volatile unsigned int TriggerWidth;
  /* 0x000C-0x00FF */          unsigned int Reserved0[(0x0100-0x000C)/4];
  /* 0x0100-0x013F */ volatile unsigned int Scalers[16];
  /* 0x0140-0x01FF */          unsigned int Reserved1[(0x0200-0x0140)/4];
} DcrbTdc_regs;

/* Config Peripheral: Board information, fpga flash update */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int BoardId;
  /* 0x0004-0x0007 */ volatile unsigned int FirmwareRev;
  /* 0x0008-0x000B */ volatile unsigned int SpiCtrl;
  /* 0x000C-0x000F */ volatile unsigned int SpiStatus;
  /* 0x0010-0x0013 */ volatile unsigned int ICapCtrl;
  /* 0x0014-0x0017 */ volatile unsigned int ICapDataWr;
  /* 0x0018-0x001B */ volatile unsigned int ICapDataRd;
  /* 0x001C-0x001F */ volatile unsigned int ICapStatus;
  /* 0x0020-0x0023 */ volatile unsigned int Reset;
  /* 0x0024-0x0027 */ volatile unsigned int DacThreshold;
  /* 0x0028-0x002B */ volatile unsigned int DacLow;
  /* 0x002C-0x002F */ volatile unsigned int DacHigh;
  /* 0x0030-0x0033 */ volatile unsigned int DacOffset;
  /* 0x0034-0x00FF */          unsigned int Reserved0[(0x0100-0x0034)/4];
} DcrbCfg_regs;

/* Clock Peripheral: Clock configuration interface */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int Ctrl;
  /* 0x0004-0x0007 */ volatile unsigned int Status;
  /* 0x0008-0x00FF */          unsigned int Reserved0[(0x0100-0x0008)/4];
} DcrbClk_regs;

#define DCRB_SCALER_SYSCLK50		0
#define DCRB_SCALER_GCLK125		1
#define DCRB_SCALER_SYNC			2
#define DCRB_SCALER_TRIG1			3
#define DCRB_SCALER_TRIG2			4
#define DCRB_SCALER_SWA_GPIO1		14
#define DCRB_SCALER_SWB_GPIO1		15
#define DCRB_SCALER_TOKENIN		16
#define DCRB_SCALER_BUSY			17

#define DCRB_OUTPUT_DCE0			0
#define DCRB_OUTPUT_DCE1			1
#define DCRB_OUTPUT_DCE2			2
#define DCRB_OUTPUT_FCE0			3
#define DCRB_OUTPUT_FCE1			4
#define DCRB_OUTPUT_FCE2			5
#define DCRB_OUTPUT_SWA_GPIO0		6
#define DCRB_OUTPUT_SWB_GPIO0		7
#define DCRB_OUTPUT_TRIGOUT		8
#define DCRB_OUTPUT_SDLINK			9
#define DCRB_OUTPUT_TOKENOUT		10
#define DCRB_OUTPUT_TOKENIN		11
#define DCRB_OUTPUT_TRIG			15
#define DCRB_OUTPUT_SYNC			16

#define DCRB_SD_MUX_0				0
#define DCRB_SD_MUX_1				1
#define DCRB_SD_MUX_SYNC			2
#define DCRB_SD_MUX_TRIG1			3
#define DCRB_SD_MUX_TRIG2			4
#define DCRB_SD_MUX_TOKENIN		5
#define DCRB_SD_MUX_SWAGPIO1		6
#define DCRB_SD_MUX_SWBGPIO1		7
#define DCRB_SD_MUX_SYSCLK_125	16
#define DCRB_SD_MUX_GCLK_125		17
#define DCRB_SD_MUX_PULSER			18
#define DCRB_SD_MUX_BUSY			19
#define DCRB_SD_MUX_TOKENOUT		20

/* SD Peripheral: Internal signal muxing, scalers, pulser */
typedef struct
{
  /* 0x0000-0x0043 */ volatile unsigned int SrcSel[17];
  /* 0x003C-0x007F */          unsigned int Reserved0[(0x0080-0x0044)/4];
  /* 0x0080-0x0083 */ volatile unsigned int PulserPeriod;
  /* 0x0084-0x0087 */ volatile unsigned int PulserLowCycles;
  /* 0x0088-0x008B */ volatile unsigned int PulserNPulses;
  /* 0x008C-0x008F */ volatile unsigned int PulserStart;
  /* 0x0090-0x0093 */ volatile unsigned int PulserDone;
  /* 0x0094-0x00FF */          unsigned int Reserved1[(0x0100-0x0094)/4];
  /* 0x0100-0x0103 */ volatile unsigned int ScalerLatch;
  /* 0x0104-0x018F */ volatile unsigned int Scalers[35];
  /* 0x0190-0x01FF */          unsigned int Reserved2[(0x0200-0x0190)/4];
} DcrbSd_regs;

/* Serdes Peripheral: Fiber & VXS serdes controls and monitors */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int Ctrl;
  /* 0x0004-0x0007 */ volatile unsigned int CtrlTile0;
  /* 0x0008-0x000B */ volatile unsigned int CtrlTile1;
  /* 0x000C-0x000F */ volatile unsigned int DrpCtrl;
  /* 0x0010-0x0013 */ volatile unsigned int Status;
  /* 0x0014-0x0017 */ volatile unsigned int DrpStatus;
  /* 0x0018-0x001B */ volatile unsigned int ErrTile0;
  /* 0x001C-0x001F */ volatile unsigned int ErrTile1;
  /* 0x0020-0x0023 */ volatile unsigned int CrateId;
  /* 0x0024-0x002F */          unsigned int Reserved0[(0x0030-0x0024)/4];
  /* 0x0030-0x0033 */ volatile unsigned int MonCtrl;
  /* 0x0034-0x0037 */ volatile unsigned int MonStatus;
  /* 0x0038-0x003F */          unsigned int Reserved1[(0x0040-0x0038)/4];
  /* 0x0040-0x004B */ volatile unsigned int MonMask[3];
  /* 0x004C-0x005F */          unsigned int Reserved2[(0x0060-0x004C)/4];
  /* 0x0060-0x006B */ volatile unsigned int MonVal[3];
  /* 0x006C-0x007F */          unsigned int Reserved3[(0x0080-0x006C)/4];
  /* 0x0080-0x0083 */ volatile unsigned int MonThr[1];
  /* 0x0084-0x008F */          unsigned int Reserved4[(0x0090-0x0084)/4];
  /* 0x0090-0x009B */ volatile unsigned int MonData[3];
  /* 0x009C-0x00FF */          unsigned int Reserved5[(0x0100-0x009C)/4];
} DcrbSerdes_regs;

/* HPS Event Builder */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int Lookback;
  /* 0x0004-0x0007 */ volatile unsigned int WindowWidth;
  /* 0x0008-0x000B */ volatile unsigned int BlockCfg;
  /* 0x000C-0x000F */ volatile unsigned int AD32;
  /* 0x0010-0x0013 */ volatile unsigned int Adr32M;
  /* 0x0014-0x0017 */ volatile unsigned int Interrupt;
  /* 0x0018-0x001B */ volatile unsigned int ReadoutCfg;
  /* 0x001C-0x001F */ volatile unsigned int ReadoutStatus;
  /* 0x0020-0x0023 */ volatile unsigned int FifoBlockCnt;
  /* 0x0024-0x0027 */ volatile unsigned int FifoWordCnt;
  /* 0x0028-0x002B */ volatile unsigned int FifoEventCnt;
  /* 0x002C-0x002F */ volatile unsigned int Reserved0[(0x0030-0x002C)/4];
  /* 0x0030-0x0033 */ volatile unsigned int SramAddr;
  /* 0x0034-0x0037 */ volatile unsigned int SramDinL;
  /* 0x0038-0x003B */ volatile unsigned int SramDinH;
  /* 0x003C-0x003F */ volatile unsigned int SramDoutL;
  /* 0x0040-0x0043 */ volatile unsigned int SramDoutH;
  /* 0x0044-0x0047 */ volatile unsigned int SramCtrl;
  /* 0x0048-0x00FF */ volatile unsigned int Reserved1[(0x0100-0x0048)/4];
} DcrbEB_regs;

/* DCRB memory structure */
typedef struct
{
  /* 0x0000-0x00FF */ DcrbCfg_regs		Cfg;
  /* 0x0100-0x01FF */ DcrbClk_regs		Clk;
  /* 0x0200-0x03FF */ DcrbSd_regs		Sd;
  /* 0x0400-0x04FF */ DcrbEB_regs		EB;
  /* 0x0500-0x06FF */ DcrbSerdes_regs	Ser[2];
  /* 0x0700-0x0FFF */ unsigned int		Reserved0[(0x1000-0x0700)/4];
  /* 0x1000-0x11FF */ DcrbTdc_regs		Tdc[6];
} DCRB_regs;

#endif
