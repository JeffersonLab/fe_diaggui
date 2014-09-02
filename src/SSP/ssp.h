#ifndef SSP_H
#define SSP_H

// Sd_regs->SrcSel[] IDs
#define SD_SRC_LVDSOUT0			0
#define SD_SRC_LVDSOUT1			1
#define SD_SRC_LVDSOUT2			2
#define SD_SRC_LVDSOUT3			3
#define SD_SRC_LVDSOUT4			4
#define SD_SRC_GPIO0				5
#define SD_SRC_GPIO1				6
#define SD_SRC_P2_LVDSOUT0		7
#define SD_SRC_P2_LVDSOUT1		8
#define SD_SRC_P2_LVDSOUT2		9
#define SD_SRC_P2_LVDSOUT3		10
#define SD_SRC_P2_LVDSOUT4		11
#define SD_SRC_P2_LVDSOUT5		12
#define SD_SRC_P2_LVDSOUT6		13
#define SD_SRC_P2_LVDSOUT7		14
#define SD_SRC_TRIG				15
#define SD_SRC_SYNC				16

#define SD_SRC_NUM				17

// Sd_regs->SrcSel[] values
#define SD_SRC_SEL_0				0
#define SD_SRC_SEL_1				1
#define SD_SRC_SEL_SYNC			2
#define SD_SRC_SEL_TRIG1		3
#define SD_SRC_SEL_TRIG2		4
#define SD_SRC_SEL_LVDSIN0		5
#define SD_SRC_SEL_LVDSIN1		6
#define SD_SRC_SEL_LVDSIN2		7
#define SD_SRC_SEL_LVDSIN3		8
#define SD_SRC_SEL_LVDSIN4		9
#define SD_SRC_SEL_P2LVDSIN0	10
#define SD_SRC_SEL_P2LVDSIN1	11
#define SD_SRC_SEL_P2LVDSIN2	12
#define SD_SRC_SEL_P2LVDSIN3	13
#define SD_SRC_SEL_P2LVDSIN4	14
#define SD_SRC_SEL_P2LVDSIN5	15
#define SD_SRC_SEL_P2LVDSIN6	16
#define SD_SRC_SEL_P2LVDSIN7	17
#define SD_SRC_SEL_PULSER		18
#define SD_SRC_SEL_BUSY			19
#define SD_SRC_SEL_TRIGGER0	20
#define SD_SRC_SEL_TRIGGER1	21
#define SD_SRC_SEL_TRIGGER2	22
#define SD_SRC_SEL_TRIGGER3	23
#define SD_SRC_SEL_TRIGGER4	24
#define SD_SRC_SEL_TRIGGER5	25
#define SD_SRC_SEL_TRIGGER6	26
#define SD_SRC_SEL_TRIGGER7	27

#define SD_SRC_SEL_NUM			28

// Sd_regs->Scalers[] IDs
#define SD_SCALER_SYSCLK		0
#define SD_SCALER_GCLK			1
#define SD_SCALER_SYNC			2
#define SD_SCALER_TRIG1			3
#define SD_SCALER_TRIG2			4
#define SD_SCALER_GPIO0			5
#define SD_SCALER_GPIO1			6
#define SD_SCALER_LVDSIN0		7
#define SD_SCALER_LVDSIN1		8
#define SD_SCALER_LVDSIN2		9
#define SD_SCALER_LVDSIN3		10
#define SD_SCALER_LVDSIN4		11
#define SD_SCALER_LVDSOUT0		12
#define SD_SCALER_LVDSOUT1		13
#define SD_SCALER_LVDSOUT2		14
#define SD_SCALER_LVDSOUT3		15
#define SD_SCALER_LVDSOUT4		16
#define SD_SCALER_BUSY			17
#define SD_SCALER_BUSYCYCLES	18
#define SD_SCALER_P2_LVDSIN0	19
#define SD_SCALER_P2_LVDSIN1	20
#define SD_SCALER_P2_LVDSIN2	21
#define SD_SCALER_P2_LVDSIN3	22
#define SD_SCALER_P2_LVDSIN4	23
#define SD_SCALER_P2_LVDSIN5	24
#define SD_SCALER_P2_LVDSIN6	25
#define SD_SCALER_P2_LVDSIN7	26
#define SD_SCALER_P2_LVDSOUT0	27
#define SD_SCALER_P2_LVDSOUT1	28
#define SD_SCALER_P2_LVDSOUT2	29
#define SD_SCALER_P2_LVDSOUT3	30
#define SD_SCALER_P2_LVDSOUT4	31
#define SD_SCALER_P2_LVDSOUT5	32
#define SD_SCALER_P2_LVDSOUT6	33
#define SD_SCALER_P2_LVDSOUT7	34

#define SD_SCALER_NUM			35

#define SD_PULSER_DONE			0x1
#define SD_PULSER_FREQ_MIN		0.01
#define SD_PULSER_FREQ_MAX		25E6

#define CLK_CTRL_DRPDWE				0x00200000
#define CLK_CTRL_DRPDEN				0x00400000
#define CLK_CTRL_CLKLOAD			0x10000000
#define CLK_CTRL_GCLKRST			0x80000000

#define CLK_STATUS_DRPRDY			0x00010000
#define CLK_STATUS_GCLKLOCKED		0x00020000

#define SSPCFG_SPI_NCSSET			0x00000100
#define SSPCFG_SPI_NCSCLR			0x00000200
#define SSPCFG_SPI_START			0x00000400
#define SSPCFG_SPI_DONE				0x00000800

#define TRG_CTRL_FIBER_EN0			0x00000001
#define TRG_CTRL_FIBER_EN1			0x00000002
#define TRG_CTRL_FIBER_EN2			0x00000004
#define TRG_CTRL_FIBER_EN3			0x00000008
#define TRG_CTRL_FIBER_EN4			0x00000010
#define TRG_CTRL_FIBER_EN5			0x00000020
#define TRG_CTRL_FIBER_EN6			0x00000040
#define TRG_CTRL_FIBER_EN7			0x00000080

#define TRG_CTRL_GTPSRC_FIBER0	0
#define TRG_CTRL_GTPSRC_FIBER1	1
#define TRG_CTRL_GTPSRC_FIBER2	2
#define TRG_CTRL_GTPSRC_FIBER3	3
#define TRG_CTRL_GTPSRC_FIBER4	4
#define TRG_CTRL_GTPSRC_FIBER5	5
#define TRG_CTRL_GTPSRC_FIBER6	6
#define TRG_CTRL_GTPSRC_FIBER7	7
#define TRG_CTRL_GTPSRC_SUM		8

#define TRG_CTRL_GTPSRC_NUM		9

#define TRG_SUMHISTCTRL_EN			0x00000001

#define SSP_SER_FIBER0				0
#define SSP_SER_FIBER1				1
#define SSP_SER_FIBER2				2
#define SSP_SER_FIBER3				3
#define SSP_SER_FIBER4				4
#define SSP_SER_FIBER5				5
#define SSP_SER_FIBER6				6
#define SSP_SER_FIBER7				7
#define SSP_SER_VXS0					8
#define SSP_SER_VXSGTP				9

#define SSP_SER_NUM					10

#define SSP_SER_CTRL_POWERDN		0x00000001
#define SSP_SER_CTRL_GTXRST		0x00000002
#define SSP_SER_CTRL_LINKRST		0x00000200
#define SSP_SER_CTRL_ERRCNT_RST	0x00000400
#define SSP_SER_CTRL_ERRCNT_EN	0x00000800

// Serdes Peripheral: Fiber & VXS serdes controls and monitors
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/*	0x0004-0x0007 */	unsigned int CtrlTile0;
/*	0x0008-0x000B */	unsigned int CtrlTile1;
/*	0x000C-0x000F */	unsigned int DrpCtrl;
/*	0x0010-0x0013 */	unsigned int Status;
/*	0x0014-0x0017 */	unsigned int DrpStatus;
/*	0x0018-0x001B */	unsigned int ErrTile0;
/*	0x001C-0x001F */	unsigned int ErrTile1;
/*	0x0020-0x002F */	unsigned int Reserved0[(0x0030-0x0020)/4];
/*	0x0030-0x0033 */	unsigned int MonCtrl;
/*	0x0034-0x0037 */	unsigned int MonStatus;
/* 0x0038-0x003F */	unsigned int Reserved1[(0x0040-0x0038)/4];
/*	0x0040-0x004B */	unsigned int MonMask[3];
/* 0x004C-0x005F */	unsigned int Reserved2[(0x0060-0x004C)/4];
/* 0x0060-0x006B */	unsigned int MonVal[3];
/* 0x006C-0x007F */	unsigned int Reserved3[(0x0080-0x006C)/4];
/* 0x0080-0x0083 */	unsigned int MonThr[1];
/* 0x0084-0x008F */	unsigned int Reserved4[(0x0090-0x0084)/4];
/* 0x0090-0x009B */	unsigned int MonData[3];
/* 0x009C-0x00FF */	unsigned int Reserved5[(0x0100-0x009C)/4];
} Serdes_regs;

// SD Peripheral: Internal signal muxing, scalers, pulser
typedef struct
{
/* 0x0000-0x003B */	unsigned int SrcSel[17];
/* 0x003C-0x007F */	unsigned int Reserved0[(0x0080-0x0044)/4];
/* 0x0080-0x0083 */	unsigned int PulserPeriod;
/* 0x0084-0x0087 */	unsigned int PulserLowCycles;
/* 0x0088-0x008B */	unsigned int PulserNPulses;
/* 0x008C-0x008F */	unsigned int PulserStart;
/* 0x0090-0x0093 */	unsigned int PulserDone;
/* 0x0094-0x00FF */	unsigned int Reserved1[(0x0100-0x0094)/4];
/* 0x0100-0x0103 */	unsigned int ScalerLatch;
/* 0x0104-0x018F */	unsigned int Scalers[35];
/* 0x0190-0x01FF */	unsigned int Reserved2[(0x0200-0x0190)/4];
} Sd_regs;

// Clock Peripheral: Clock configuration interface
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x0007 */	unsigned int Status;
/* 0x0008-0x00FF */	unsigned int Reserved0[(0x0100-0x0008)/4];
} Clk_regs;

// Config Peripheral: Board information, fpga flash update
typedef struct
{
/* 0x0000-0x0003 */	unsigned int BoardId;
/* 0x0004-0x0007 */	unsigned int FirmwareRev;
/* 0x0008-0x000B */	unsigned int SpiCtrl;
/* 0x000C-0x000F */	unsigned int SpiStatus;
/* 0x0010-0x0013 */	unsigned int ICapCtrl;
/* 0x0014-0x0017 */	unsigned int ICapWr;
/* 0x0018-0x001B */	unsigned int ICapRd;
/* 0x001C-0x001F */	unsigned int ICapStatus;
/* 0x0020-0x00FF */	unsigned int Reserved0[(0x0100-0x0020)/4];
} SspCfg_regs;

// Trigger Peripheral: Trigger configuration, status
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x000F */	unsigned int Reserved0[(0x0010-0x0004)/4];
/* 0x0010-0x0013 */	unsigned int HistCtrl;
/* 0x0014-0x0017 */	unsigned int SumHistThr;
/* 0x0018-0x001B */	unsigned int SumHistWindow;
/* 0x001C-0x0023 */	unsigned int Reserved1[(0x0024-0x001C)/4];
/* 0x0024-0x0027 */	unsigned int SumHistData;
/* 0x0028-0x00FF */	unsigned int Reserved2[(0x0100-0x0028)/4];
} Trg_regs;


/* HPS Singles Peripheral */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int Ctrl;
  /* 0x0004-0x0007 */ volatile unsigned int Latency;
  /* 0x0008-0x0017 */ volatile unsigned int Reserved0[(0x0018-0x0008)/4];
  /* 0x0018-0x001B */ volatile unsigned int ClusterEmin;
  /* 0x001C-0x001F */ volatile unsigned int ClusterEmax;
  /* 0x0020-0x0023 */ volatile unsigned int ClusterNHitsmin;
  /* 0x0024-0x007F */          unsigned int Reserved1[(0x0080-0x0024)/4];
  /* 0x0080-0x0083 */ volatile unsigned int ScalerSinglesPass;
  /* 0x0084-0x0087 */ volatile unsigned int ScalerSinglesTot;
  /* 0x0088-0x00FF */          unsigned int Reserved2[(0x0100-0x0088)/4];
} Hps_regs;

/* HPS Cluster Peripheral */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int HistCtrl;
  /* 0x0004-0x000F */ volatile unsigned int Reserved0[(0x0010-0x0004)/4];
  /* 0x0010-0x0013 */ volatile unsigned int HistLatency;
  /* 0x0014-0x0017 */ volatile unsigned int HistPosition;
  /* 0x0018-0x001B */ volatile unsigned int HistEnergy;
  /* 0x001C-0x001F */ volatile unsigned int HistNHits;
  /* 0x0020-0x00FF */          unsigned int Reserved1[(0x0100-0x0020)/4];
} HpsCluster_regs;

/* HPS Pairs Peripheral */
typedef struct
{
  /* 0x0000-0x0003 */ volatile unsigned int Ctrl;
  /* 0x0004-0x0007 */ volatile unsigned int Latency;
  /* 0x0008-0x000B */ volatile unsigned int ClusterDelay;
  /* 0x000C-0x000F */ volatile unsigned int ClusterTimeCoincidence;
  /* 0x0010-0x0013 */ volatile unsigned int ClusterSummax;
  /* 0x0014-0x0017 */ volatile unsigned int ClusterDiffmax;
  /* 0x0018-0x001B */ volatile unsigned int ClusterEmin;
  /* 0x001C-0x001F */ volatile unsigned int ClusterEmax;
  /* 0x0020-0x0023 */ volatile unsigned int ClusterNHitsmin;
  /* 0x0024-0x0027 */ volatile unsigned int ClusterCoplanarTol;
  /* 0x0028-0x0028 */ volatile unsigned int ClusterEDFactor;
  /* 0x002C-0x002F */ volatile unsigned int ClusterEDmin;
  /* 0x0030-0x007F */          unsigned int Reserved0[(0x0080-0x0030)/4];
  /* 0x0080-0x0083 */ volatile unsigned int ScalerPairsPass;
  /* 0x0084-0x0087 */ volatile unsigned int ScalerSumPass;
  /* 0x0088-0x008B */ volatile unsigned int ScalerDiffPass;
  /* 0x008C-0x008F */ volatile unsigned int ScalerEDPass;
  /* 0x0090-0x0093 */ volatile unsigned int ScalerCoplanarPass;
  /* 0x0094-0x0097 */ volatile unsigned int ScalerTriggerPass;
  /* 0x0098-0x00FF */          unsigned int Reserved1[(0x0100-0x0098)/4];
} HpsPair_regs;

/* SSP memory structure */
typedef struct
{
  /* 0x0000-0x00FF */ SspCfg_regs     Cfg;
  /* 0x0100-0x01FF */ Clk_regs        Clk;
  /* 0x0200-0x03FF */ Sd_regs         Sd;
  /* 0x0400-0x04FF */ Trg_regs        Trg;
  /* 0x0500-0x05FF */ Hps_regs        HpsSingles;
  /* 0x0600-0x06FF */ HpsCluster_regs HpsClusterTop;
  /* 0x0700-0x07FF */ HpsCluster_regs HpsClusterBot;
  /* 0x0800-0x08FF */ HpsPair_regs    HpsPairs;
  /* 0x0900-0x0FFF */ unsigned int    Reserved0[(0x1000-0x0900)/4];
  /* 0x1000-0x19FF */ Serdes_regs     Ser[10];
  /* 0x1A00-0xFFFF */ unsigned int    Reserved1[(0x10000-0x1A00)/4];
} SSP_regs;

#define SYSCLK_FREQ				50000000
#define GCLK_FREQ					250000000

#define SSP_CLKSRC_DISABLED	0
#define SSP_CLKSRC_SWB			1
#define SSP_CLKSRC_P2			2
#define SSP_CLKSRC_LOCAL		3

#define SSP_CFG_BOARDID			0x53535020	// "SSP "

#define SPI_CMD_RD				0x03
#define SPI_CMD_GETID			0x9F
#define SPI_CMD_GETSTATUS		0xD7
#define SPI_CMD_WRBUF1			0x84
#define SPI_CMD_PGBUF1ERASE	0x83

#define SPI_BYTE_LENGTH			8*1024*1024
#define SPI_MFG_ATMEL			0x1F
#define SPI_DEVID_AT45DB642D	0x2800

unsigned int sspReadReg(unsigned int *addr);
void sspWriteReg(unsigned int *addr, unsigned int val);

// Firmware update routines
int sspFirmwareUpdateVerify(const char *filename);
int sspFirmwareUpdate(const char *filename);
int sspFirmwareRead(const char *filename);
int sspFirmwareVerify(const char *filename);

// Firmware update utility routines
void sspSelectSpi(int sel);
void sspFlashGetId(unsigned char *rsp);
void sspReloadFirmware();
unsigned char sspFlashGetStatus();
unsigned char sspTransferSpi(unsigned char data);

// Pulser routines
int sspPulserStatus();
void sspPulserStart();
void sspPulserSetup(float freq, float duty, unsigned npulses);

// Scaler routines
void sspPrintScalers();

// SSP configuration
int sspInit(unsigned int addr, int iFlag);
int sspSetClkSrc(int src);
int sspGetClkStatus();
int sspSetIOSrc(int ioport, int signal);
void sspPrintIOSrc();
void sspTriggerSetup(int fiber_mask, int gtp_src);

// SSP serdes
int sspSerdesGetErrorCount(int ser, int lane);
void sspSerdesEnable(int mask);
void sspSerdesResetErrorCount(int mask);
void sspSerdesPrintStatus(int mask);

#endif
