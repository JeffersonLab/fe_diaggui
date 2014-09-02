#ifndef GTP_H
#define GTP_H

// Structure returned by ReadScalers() tcp server routine
typedef struct
{
	unsigned int SysClk50;
	unsigned int GClk;
	unsigned int Sync;
	unsigned int Trig1;
	unsigned int Trig2;
	unsigned int FpIn[4];
	unsigned int FpOut[4];
	unsigned int Busy;
	unsigned int BusyCycles;
	unsigned int FCalEnergy[32];
	unsigned int BCalEnergy[32];
	unsigned int BCalHitModules[32];
	unsigned int TOF[32];
	unsigned int TagM[32];
	unsigned int TagH[32];
	unsigned int PS[32];
	unsigned int ST[32];
	unsigned int Trig_BCal[32];
	unsigned int Trig_BFCal[32];
	unsigned int Trig_TAGM[32];
	unsigned int Trig_TAGH[32];
	unsigned int Trig_PS[32];
	unsigned int Trig_ST[32];
	unsigned int Trig_TOF[32];
	unsigned int Trig[32];
} GtpScalers;

#define GTP_ADDR		0xF8010000

// NOTE: SERINDEX should be set to: VXS payload number - 1
#define SS_BCAL_SERINDEX		14	// PP15
#define SS_FCAL0_SERINDEX		12	// PP13
#define SS_FCAL1_SERINDEX		10	// PP11
#define SS_TAGM_SERINDEX		8	// PP9
#define SS_TAGH_SERINDEX		6	// PP7
#define SS_PS_SERINDEX			4	// PP5
#define SS_ST_SERINDEX			2	// PP3
#define SS_TOF_SERINDEX			0	// PP1

#define GTP_SER_VXS0		0
#define GTP_SER_VXS1		1
#define GTP_SER_VXS2		2
#define GTP_SER_VXS3		3
#define GTP_SER_VXS4		4
#define GTP_SER_VXS5		5
#define GTP_SER_VXS6		6
#define GTP_SER_VXS7		7
#define GTP_SER_VXS8		8
#define GTP_SER_VXS9		9
#define GTP_SER_VXS10	10
#define GTP_SER_VXS11	11
#define GTP_SER_VXS12	12
#define GTP_SER_VXS13	13
#define GTP_SER_VXS14	14
#define GTP_SER_VXS15	15

// Serdes Peripheral: Fiber & VXS serdes controls and monitors
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x000F */	unsigned int Reserved0[(0x0010-0x0004)/4];
/* 0x0010-0x0013 */	unsigned int Status;
/* 0x0014-0x0017 */	unsigned int Reserved1[(0x0018-0x0014)/4];
/* 0x0018-0x001B */	unsigned int ErrTile0;
/* 0x001C-0x001F */	unsigned int ErrTile1;
/* 0x0020-0x002F */	unsigned int Reserved2[(0x0030-0x0020)/4];
/* 0x0030-0x0033 */	unsigned int MonCtrl;
/* 0x0034-0x0037 */	unsigned int MonStatus;
/* 0x0038-0x003F */	unsigned int Reserved3[(0x0040-0x0038)/4];
/* 0x0040-0x004B */	unsigned int MonMask[3];
/* 0x004C-0x005F */	unsigned int Reserved4[(0x0060-0x004C)/4];
/* 0x0060-0x006B */	unsigned int MonVal[3];
/* 0x006C-0x007F */	unsigned int Reserved5[(0x0080-0x006C)/4];
/* 0x0080-0x0083 */	unsigned int MonThr[1];
/* 0x0084-0x008F */	unsigned int Reserved6[(0x0090-0x0084)/4];
/* 0x0090-0x009B */	unsigned int MonData[3];
/* 0x009C-0x00FF */	unsigned int Reserved7[(0x0100-0x009C)/4];
} GtpSerdes_regs;

// GXB Reconfig Peripheral: Serdes debug interface
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Status;
/* 0x0004-0x0007 */	unsigned int Ctrl;
/* 0x0008-0x000B */	unsigned int Ctrl2;
/* 0x000C-0x000F */	unsigned int TxRxIn;
/* 0x0010-0x0013 */	unsigned int TxRxOut;
/* 0x0014-0x00FF */	unsigned int Reserved0[(0x0100-0x0014)/4];
} GtpGxbCfg_regs;

#define GTP_CLK_CTRL_P0			0x00000001
#define GTP_CLK_CTRL_INT		0x00000002

#define GTP_CLK_CTRL_RESET		0x80000000

// Clock Peripheral: Clock configuration interface
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x0007 */	unsigned int Status;
/* 0x0008-0x00FF */	unsigned int Reserved0[(0x0100-0x0008)/4];
} GtpClk_regs;

// GtpTrigger_regs->Ctrl bits (for Hall D GTP definitions)
//    '1' - enables subsystem data stream
//    '0' - disables subsystem data stream
#define GTP_TRG_CTRL_BCAL_E	0x00000001
#define GTP_TRG_CTRL_BCAL_H	0x00000002
#define GTP_TRG_CTRL_FCAL		0x00000004
#define GTP_TRG_CTRL_TAGM		0x00000008
#define GTP_TRG_CTRL_TAGH		0x00000010
#define GTP_TRG_CTRL_PS			0x00000020
#define GTP_TRG_CTRL_ST			0x00000040
#define GTP_TRG_CTRL_TOF		0x00000080

// Trigger Peripheral
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x0007 */	unsigned int CtrlDcTrg;								// Hall B DriftChamber only
/* 0x0008-0x000B */	unsigned int CtrlDcMon;								// Hall B DriftChamber only
/* 0x000C-0x000F */	unsigned int StatusDcMon;							// Hall B DriftChamber only
/* 0x0010-0x007F */	unsigned int Reserved0[(0x0080-0x0010)/4];	// Hall B DriftChamber only
/* 0x0080-0x00FF */	unsigned int DcMonData[(0x0100-0x0080)/4];	// Hall B DriftChamber only
/* 0x0100-0x017F */	unsigned int DcMonMask[(0x0180-0x0100)/4];	// Hall B DriftChamber only
/* 0x0180-0x03FF */	unsigned int DcMonVal[(0x0400-0x0180)/4];		// Hall B DriftChamber only
} GtpTrigger_regs;

// GtpSd_regs->SrcSel[] IDs
#define GTP_SD_SRC_TRIG					0
#define GTP_SD_SRC_SYNC					1
#define GTP_SD_SRC_LVDSOUT(n)			(2+n)

// GtpSd_regs->SrcSel[] values
#define GTP_SD_SRC_SEL_0				0
#define GTP_SD_SRC_SEL_1				1
#define GTP_SD_SRC_SEL_SYNC			2
#define GTP_SD_SRC_SEL_TRIG1			3
#define GTP_SD_SRC_SEL_TRIG2			4
#define GTP_SD_SRC_SEL_LVDSIN(n)		(5+n)
#define GTP_SD_SRC_SEL_PULSER			9
#define GTP_SD_SRC_SEL_BUSY			10
#define GTP_SD_SRC_SEL_TRIGGER(n)	(32+n)

// GtpSd_regs->Scalers[] IDs
#define GTP_SD_SCALER_50MHZ			0
#define GTP_SD_SCALER_GCLK				1
#define GTP_SD_SCALER_SYNC				2
#define GTP_SD_SCALER_TRIG1			3
#define GTP_SD_SCALER_TRIG2			4
#define GTP_SD_SCALER_BUSY				5
#define GTP_SD_SCALER_BUSYCYCLES		6
#define GTP_SD_SCALER_FPIN(n)			(7+n)
#define GTP_SD_SCALER_FPOUT(n)		(11+n)

// SD Peripheral
typedef struct
{
/* 0x0000-0x0003 */	unsigned int ScalerLatch;
/* 0x0004-0x003F */	unsigned int Scalers[15];
/* 0x0040-0x00FF */	unsigned int Reserved0[(0x0100-0x0040)/4];
/* 0x0100-0x0103 */	unsigned int PulserPeriod;
/* 0x0104-0x0107 */	unsigned int PulserLowCycles;
/* 0x0108-0x010B */	unsigned int PulserNPulses;
/* 0x010C-0x010F */	unsigned int PulserDone;
/* 0x0110-0x0113 */	unsigned int PulserStart;
/* 0x0114-0x011F */	unsigned int Reserved1[(0x0120-0x0114)/4];
/* 0x0120-0x0137 */	unsigned int SrcSel[6];
/* 0x0138-0x01FF */	unsigned int Reserved2[(0x0200-0x0138)/4];
} GtpSd_regs;

// Event Processor Peripheral
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x0007 */	unsigned int Status;
/* 0x0008-0x000F */	unsigned int Reserved0[(0x0010-0x0008)/4];
/* 0x0010-0x0017 */	unsigned int EvtTime[2];
/* 0x0018-0x001F */	unsigned int Reserved1[(0x0020-0x0018)/4];
/* 0x0020-0x00FF */	unsigned int EvtData[56];
} GtpEvtProc_regs;

// BCal Subsystem Peripheral
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Delay;
/* 0x0004-0x0007 */	unsigned int Width;
/* 0x0008-0x000F */	unsigned int Reserved0[(0x0010-0x0008)/4];
/* 0x0010-0x0013 */	unsigned int HistDataEnergy;
/* 0x0014-0x0017 */	unsigned int HistDataHits;
/* 0x0018-0x00FF */	unsigned int Reserved1[(0x0100-0x0018)/4];
} GtpBCal_regs;

// FCal Subsystem Peripheral
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Delay;
/* 0x0004-0x0007 */	unsigned int Width;
/* 0x0008-0x000F */	unsigned int Reserved0[(0x0010-0x0008)/4];
/* 0x0010-0x0013 */	unsigned int HistDataEnergy;
/* 0x0014-0x00FF */	unsigned int Reserved1[(0x0100-0x0014)/4];
} GtpFCal_regs;

// Hit pattern subsystems (TAGM,TAGH,ST,TOF,PS)
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Delay;
/* 0x0004-0x0007 */	unsigned int Width;
/* 0x0008-0x007F */	unsigned int Reserved0[(0x0080-0x0008)/4];
/* 0x0080-0x00FF */	unsigned int Scalers[32];
} GtpHitPattern_regs;

#define GTP_TRIGBIT_CTRL_BCAL_HITMODULES_EN	0x01
#define GTP_TRIGBIT_CTRL_BFCAL_EN				0x02
#define GTP_TRIGBIT_CTRL_TAGM_PATTERN_EN		0x04
#define GTP_TRIGBIT_CTRL_TAGH_PATTERN_EN		0x08
#define GTP_TRIGBIT_CTRL_PS_COIN_EN				0x10
#define GTP_TRIGBIT_CTRL_ST_NHITS_EN			0x20
#define GTP_TRIGBIT_CTRL_TOF_NHITS_EN			0x40

#define GTP_TRIGBIT_SCALER_BCALHIT	0
#define GTP_TRIGBIT_SCALER_BFCAL		1
#define GTP_TRIGBIT_SCALER_TAGM		2
#define GTP_TRIGBIT_SCALER_TAGH		3
#define GTP_TRIGBIT_SCALER_PS			4
#define GTP_TRIGBIT_SCALER_ST			5
#define GTP_TRIGBIT_SCALER_TOF		6
#define GTP_TRIGBIT_SCALER_TRIGOUT	7

// Hall D Trigger Bit
typedef struct
{
/* 0x0000-0x0003 */	unsigned int Ctrl;
/* 0x0004-0x0007 */	unsigned int TrigOutCtrl;
/* 0x0008-0x000B */	unsigned int TrigOutStatus;
/* 0x000C-0x000F */	unsigned int Reserved0[(0x0010-0x000C)/4];
/* 0x0010-0x0013 */	unsigned int BCalCtrl0;
/* 0x0014-0x0017 */	unsigned int BCalCtrl1;
/* 0x0018-0x001F */	unsigned int Reserved1[(0x0020-0x0018)/4];
/* 0x0020-0x0023 */	unsigned int FCalCtrl;
/* 0x0024-0x002F */	unsigned int Reserved2[(0x0030-0x0024)/4];
/* 0x0030-0x0033 */	unsigned int BFCalCtrl;
/* 0x0034-0x003F */	unsigned int Reserved3[(0x0040-0x0034)/4];
/* 0x0040-0x0043 */	unsigned int PSCtrl;
/* 0x0044-0x004F */	unsigned int Reserved4[(0x0050-0x0044)/4];
/* 0x0050-0x0053 */	unsigned int STCtrl0;
/* 0x0054-0x0057 */	unsigned int STCtrl1;
/* 0x0058-0x005F */	unsigned int Reserved5[(0x0060-0x0058)/4];
/* 0x0060-0x0063 */	unsigned int TOFCtrl0;
/* 0x0064-0x0067 */	unsigned int TOFCtrl1;
/* 0x0068-0x006F */	unsigned int Reserved6[(0x0070-0x0068)/4];
/* 0x0070-0x0073 */	unsigned int TagMCtrl;
/* 0x0074-0x0077 */	unsigned int TagHCtrl;
/* 0x0078-0x007F */	unsigned int Reserved7[(0x0080-0x0078)/4];
/* 0x0080-0x009F */	unsigned int Scalers[8];
/* 0x00A0-0x00FF */	unsigned int Reserved8[(0x0100-0x00A0)/4];
} GtpTrigbit_regs;

// GTP memory structure
typedef struct
{
/* 0x0000-0x00FF */	unsigned int			Reserved0[(0x0100-0x0000)/4];
/* 0x0100-0x01FF */	GtpClk_regs				Clk;
/* 0x0200-0x03FF */	GtpSd_regs				Sd;
/* 0x0400-0x04FF */	unsigned int			Reserved1[(0x0500-0x0400)/4];
/* 0x0500-0x05FF */	GtpGxbCfg_regs			GxbCfgOdd;
/* 0x0600-0x06FF */	GtpGxbCfg_regs			GxbCfgEven;
/* 0x0700-0x0FFF */	unsigned int			Reserved2[(0x1000-0x0700)/4];
/* 0x1000-0x1FFF */	GtpSerdes_regs			Ser[16];
/* 0x2000-0x23FF */	GtpTrigger_regs		Trg;
/* 0x2400-0x24FF */	GtpEvtProc_regs		EvtProc0;							// Hall B DriftChamber only
/* 0x2500-0x25FF */	GtpEvtProc_regs		EvtProc1;							// Hall B DriftChamber only
/* 0x2600-0x2FFF */	unsigned int			Reserved3[(0x3000-0x2600)/4];
/* 0x3000-0x30FF */	GtpBCal_regs			BCal;									// Hall D GTP only
/* 0x3100-0x31FF */	GtpFCal_regs			FCal;									// Hall D GTP only
/* 0x3200-0x32FF */	GtpHitPattern_regs	TagM;									// Hall D GTP only
/* 0x3300-0x33FF */	GtpHitPattern_regs	TagH;									// Hall D GTP only
/* 0x3400-0x34FF */	GtpHitPattern_regs	PS;									// Hall D GTP only
/* 0x3500-0x35FF */	GtpHitPattern_regs	ST;									// Hall D GTP only
/* 0x3600-0x36FF */	GtpHitPattern_regs	TOF;									// Hall D GTP only
/* 0x3700-0x3FFF */	unsigned int			Reserved4[(0x4000-0x3700)/4];
/* 0x4000-0x5FFF */	GtpTrigbit_regs		Trigbits[32];						// Hall D GTP only
/* 0x6000-0xFFFF */	unsigned int			Reserved5[(0x10000-0x6000)/4];
} Gtp_regs;

#endif
