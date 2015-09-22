#ifndef vetroc_H
#define vetroc_H

typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int EnableN;
  /* 0x0004-0x0007 */ volatile unsigned int TriggerWidth;
  /* 0x0008-0x007F */          unsigned int Reserved0[(0x0080-0x0008)/4];
  /* 0x0080-0x00BF */ volatile unsigned int Scalers[16];
  /* 0x00C0-0x00FF */          unsigned int Reserved1[(0x0100-0x00C0)/4];
} vetrocTdc_regs;

/* Clock Peripheral: Clock configuration interface */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int BoardId;
  /* 0x0004-0x0007 */ volatile unsigned int FirmwareRev;
  /* 0x0008-0x000B */ volatile unsigned int Ctrl;
  /* 0x000C-0x000F */ volatile unsigned int Status;
  /* 0x0010-0x0013 */ volatile unsigned int SpiCtrl;
  /* 0x0014-0x0017 */ volatile unsigned int SpiStatus;
  /* 0x0018-0x00FF */          unsigned int Reserved0[(0x0100-0x0018)/4];
} vetrocClk_regs;

#define VETROC_SCALER_GCLK125		0
#define VETROC_SCALER_SYNC			1
#define VETROC_SCALER_TRIG			2
#define VETROC_SCALER_BUSYCYCLES	3
#define VETROC_SCALER_FPIN1		4
#define VETROC_SCALER_FPIN2		5
#define VETROC_SCALER_FPIN3		6
#define VETROC_SCALER_FPIN4		7
#define VETROC_SCALER_FPIN5		8
#define VETROC_SCALER_FPIN6		9
#define VETROC_SCALER_FPIN7		10
#define VETROC_SCALER_FPIN8		11
#define VETROC_SCALER_TOKENFI		12
#define VETROC_SCALER_SYNCFI		13
#define VETROC_SCALER_TRIG1F		14
#define VETROC_SCALER_TRIG2F		15
#define VETROC_SCALER_STATAIN		16
#define VETROC_SCALER_STATBIN		17
#define VETROC_SCALER_FPOUT1		18
#define VETROC_SCALER_FPOUT2		19
#define VETROC_SCALER_FPOUT3		20
#define VETROC_SCALER_FPOUT4		21
#define VETROC_SCALER_FPOUT5		22
#define VETROC_SCALER_FPOUT6		23
#define VETROC_SCALER_FPOUT7		24
#define VETROC_SCALER_FPOUT8		25
#define VETROC_SCALER_TOKENFO		26
#define VETROC_SCALER_TRIGFO		27
#define VETROC_SCALER_SDLINKF		28
#define VETROC_SCALER_STATAOUT	29
#define VETROC_SCALER_BUSYOUT		30

#define VETROC_OUTPUT_FPOUT1		0
#define VETROC_OUTPUT_FPOUT2		1
#define VETROC_OUTPUT_FPOUT3		2
#define VETROC_OUTPUT_FPOUT4		3
#define VETROC_OUTPUT_FPOUT5		4
#define VETROC_OUTPUT_FPOUT6		5
#define VETROC_OUTPUT_FPOUT7		6
#define VETROC_OUTPUT_FPOUT8		7
#define VETROC_OUTPUT_TOKENFO		8
#define VETROC_OUTPUT_TRIGFO		9
#define VETROC_OUTPUT_SDLINKF		10
#define VETROC_OUTPUT_STATAOUT	11
#define VETROC_OUTPUT_BUSYOUT		12
#define VETROC_OUTPUT_TRIG			13
#define VETROC_OUTPUT_SYNC			14

#define VETROC_SD_MUX_0				0
#define VETROC_SD_MUX_1				1
#define VETROC_SD_MUX_FPIN1		2
#define VETROC_SD_MUX_FPIN2		3
#define VETROC_SD_MUX_FPIN3		4
#define VETROC_SD_MUX_FPIN4		5
#define VETROC_SD_MUX_FPIN5		6
#define VETROC_SD_MUX_FPIN6		7
#define VETROC_SD_MUX_FPIN7		8
#define VETROC_SD_MUX_FPIN8		9
#define VETROC_SD_MUX_TOKENFI		10
#define VETROC_SD_MUX_SYNCFI		11
#define VETROC_SD_MUX_TRIG1F		12
#define VETROC_SD_MUX_TRIG2F		13
#define VETROC_SD_MUX_STATAIN		14
#define VETROC_SD_MUX_STATBIN		15
#define VETROC_SD_MUX_PULSER		18
#define VETROC_SD_MUX_BUSY			19

/* SD Peripheral: Internal signal muxing, scalers, pulser */
typedef struct
{
  /* 0x0000-0x0007 */          unsigned int Reserved0[(0x0008-0x0000)/4];
  /* 0x0008-0x0043 */ volatile unsigned int SrcSel[15];
  /* 0x0044-0x007F */          unsigned int Reserved1[(0x0080-0x0044)/4];
  /* 0x0080-0x0083 */ volatile unsigned int PulserPeriod;
  /* 0x0084-0x0087 */ volatile unsigned int PulserLowCycles;
  /* 0x0088-0x008B */ volatile unsigned int PulserNPulses;
  /* 0x008C-0x008F */ volatile unsigned int PulserStart;
  /* 0x0090-0x0093 */ volatile unsigned int PulserDone;
  /* 0x0094-0x00FF */          unsigned int Reserved2[(0x0100-0x0094)/4];
  /* 0x0100-0x0103 */ volatile unsigned int ScalerLatch;
  /* 0x0104-0x0107 */          unsigned int Reserved3[(0x0108-0x0104)/4];
  /* 0x0108-0x0183 */ volatile unsigned int Scalers[31];
  /* 0x0184-0x01FF */          unsigned int Reserved4[(0x0200-0x0184)/4];
} vetrocSd_regs;

/* Serdes Peripheral: Fiber & VXS serdes controls and monitors */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int Ctrl;
  /* 0x000C-0x0004 */          unsigned int Reserved0[(0x000C-0x0004)/4];
  /* 0x000C-0x000F */ volatile unsigned int DrpCtrl;
  /* 0x0010-0x0013 */ volatile unsigned int Status;
  /* 0x0014-0x0017 */ volatile unsigned int DrpStatus;
  /* 0x0018-0x00FF */          unsigned int Reserved1[(0x0100-0x0018)/4];
} vetrocSerdes_regs;

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
  /* 0x002C-0x002F */ volatile unsigned int TrigFifoBusyThreshold;
  /* 0x0030-0x0033 */ volatile unsigned int SramAddr;
  /* 0x0034-0x0037 */ volatile unsigned int SramDinL;
  /* 0x0038-0x003B */ volatile unsigned int SramDinH;
  /* 0x003C-0x003F */ volatile unsigned int SramDoutL;
  /* 0x0040-0x0043 */ volatile unsigned int SramDoutH;
  /* 0x0044-0x0047 */ volatile unsigned int SramCtrl;
  /* 0x0048-0x00FF */ volatile unsigned int Reserved1[(0x0100-0x0048)/4];
} vetrocEB_regs;

/* DCRB memory structure */
typedef struct
{
  /* 0x0000-0x00FF */ vetrocClk_regs		Clk;
  /* 0x0100-0x01FF */ unsigned int			Reserved0[(0x0200-0x0100)/4];
  /* 0x0200-0x03FF */ vetrocSd_regs			Sd;
  /* 0x0400-0x04FF */ vetrocSerdes_regs	Ser;
  /* 0x0500-0x0FFF */ unsigned int			Reserved1[(0x1000-0x0500)/4];
  /* 0x1000-0x17FF */ vetrocTdc_regs		Tdc[8];
  /* 0x1800-0x1FFF */ unsigned int			Reserved2[(0x2000-0x1800)/4];
  /* 0x2000-0x20FF */ vetrocEB_regs			EB;
} vetroc_regs;

#endif
