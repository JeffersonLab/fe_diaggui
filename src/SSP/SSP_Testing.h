#ifndef SSP_Testing_H
#define SSP_Testing_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"

#define SYSCLK_FREQ                     62500000

#define DDR2_I2C_SLADDR         0x50
#define DDR2_I2C_RD                     0x01
#define DDR2_I2C_WR                     0x00

#define I2C_SR_TXEMPTY          0x00000080

#define I2C_CR_EN                       0x01
#define I2C_CR_TXRST            0x02
#define I2C_CR_MSMS                     0x04
#define I2C_CR_TX                       0x08
#define I2C_CR_RSTA                     0x20

#define SWx_GPIO_NOEx           0x80
#define MUX_SRC_0                       0
#define MUX_SRC_1                       1
#define MUX_SRC_SYNC            2
#define MUX_SRC_TRIG1           3
#define MUX_SRC_TRIG2           4
#define MUX_SRC_FPINPUT0        5
#define MUX_SRC_FPINPUT1        6
#define MUX_SRC_FPINPUT2        7
#define MUX_SRC_FPINPUT3        8
#define MUX_SRC_FPINPUT4        9
#define MUX_SRC_GPIO0           10
#define MUX_SRC_GPIO1           11
#define MUX_SRC_SWAGPIO0        12
#define MUX_SRC_SWAGPIO1        13
#define MUX_SRC_SWBGPIO0        14
#define MUX_SRC_SWBGPIO1        15
#define MUX_SRC_PULSER          16
#define MUX_SRC_TOKENOUT        17
#define MUX_SRC_TOKENIN         18
#define MUX_SRC_BUSY            19
#define MUX_SRC_P2LVDSIN0       20
#define MUX_SRC_P2LVDSIN1       21
#define MUX_SRC_P2LVDSIN2       22
#define MUX_SRC_P2LVDSIN3       23
#define MUX_SRC_P2LVDSIN4       24
#define MUX_SRC_P2LVDSIN5       25
#define MUX_SRC_P2LVDSIN6       26
#define MUX_SRC_P2LVDSIN7       27
#define MUX_SRC_SUMDISC         28


#define CLKSRC_DISABLED         0
#define CLKSRC_SWB                      1
#define CLKSRC_P2                       2
#define CLKSRC_LOCAL            3

#define GPIO_GCLKPLL_LOCKED     0x00000001
#define GPIO_IDELAY_RDY         0x00000002
#define GPIO_GCLKPLL_RESET      0x00000004
#define GPIO_HB_LED                     0x00000008
#define GPIO_I2C_RESET          0x00000010
#define GPIO_I2C_INT_N          0x00000020
#define GPIO_CLK_SOUT0          0x00000040
#define GPIO_CLK_SOUT1          0x00000080
#define GPIO_CLK_SIN0           0x00000100
#define GPIO_CLK_SIN1           0x00000200
#define GPIO_CLK_LOAD           0x00000400
#define GPIO_CLK_CONF           0x00000800
#define GPIO_LINKSTATUS0        0x00001000
#define GPIO_LINKSTATUS1        0x00002000
#define GPIO_LINKSTATUS2        0x00004000
#define GPIO_LINKSTATUS3        0x00008000
#define GPIO_LINKSTATUS4        0x00010000
#define GPIO_LINKSTATUS5        0x00020000
#define GPIO_LINKSTATUS6        0x00040000
#define GPIO_LINKSTATUS7        0x00080000
#define GPIO_PLL_LOL            0x00100000
#define GPIO_TESTING            0x80000000

typedef struct
{
/* 0x0000-0x0003 */ unsigned int Data;
/* 0x0004-0x0007 */ unsigned int Tri;
/* 0x0008-0x01FF */ unsigned int Reserved0[(0x0200-0x0008)/4];
} SSPTesting_XpsGpio_regs;

typedef struct
{
/* 0x0000-0x001B */ unsigned int Reserved0[(0x001C-0x0000)/4];
/* 0x001C-0x001F */ unsigned int DGIER;
/* 0x0020-0x0023 */ unsigned int IPISR;
/* 0x0024-0x0027 */ unsigned int Reserved1[(0x0028-0x0024)/4];
/* 0x0028-0x002B */ unsigned int IPIER;
/* 0x002C-0x003F */ unsigned int Reserved2[(0x0040-0x002C)/4];
/* 0x0040-0x0043 */ unsigned int SRR;
/* 0x0044-0x005F */ unsigned int Reserved3[(0x0060-0x0044)/4];
/* 0x0060-0x0063 */ unsigned int CR;
/* 0x0064-0x0067 */ unsigned int SR;
/* 0x0068-0x006B */ unsigned int DTR;
/* 0x006C-0x006F */ unsigned int DRR;
/* 0x0070-0x0073 */ unsigned int SSR;
/* 0x0074-0x0077 */ unsigned int TXFIFO;
/* 0x0078-0x007B */ unsigned int RXFIFO;
/* 0x007C-0x01FF */ unsigned int Reserved4[(0x0200-0x007C)/4];
} SSPTesting_XpsSpi_regs;

typedef struct
{
/* 0x0000-0x001B */ unsigned int Reserved0[(0x001C-0x0000)/4];
/* 0x001C-0x001F */ unsigned int GIE;
/* 0x0020-0x0023 */ unsigned int ISR;
/* 0x0024-0x0027 */ unsigned int Reserved1[(0x0028-0x0024)/4];
/* 0x0028-0x002B */ unsigned int IER;
/* 0x002C-0x003F */ unsigned int Reserved2[(0x0040-0x002C)/4];
/* 0x0040-0x0043 */ unsigned int SOFTR;
/* 0x0044-0x00FF */ unsigned int Reserved3[(0x0100-0x0044)/4];
/* 0x0100-0x0103 */ unsigned int CR;
/* 0x0104-0x0107 */ unsigned int SR;
/* 0x0108-0x010B */ unsigned int TX_FIFO;
/* 0x010C-0x010F */ unsigned int RX_FIFO;
/* 0x0110-0x0113 */ unsigned int ADR;
/* 0x0114-0x0117 */ unsigned int TX_FIFO_OCY;
/* 0x0118-0x011B */ unsigned int RX_FIFO_OCY;
/* 0x011C-0x011F */ unsigned int TEN_ADR;
/* 0x0120-0x0123 */ unsigned int RX_FIFO_PIRQ;
/* 0x0124-0x0127 */ unsigned int GPO;
/* 0x0128-0x01FF */ unsigned int Reserved4[(0x0200-0x0128)/4];
} SSPTesting_XpsI2C_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int ScalerLatch;
/* 0x0004-0x0007 */ unsigned int ScalerSysclk;
/* 0x0008-0x000B */ unsigned int ScalerGclk;
/* 0x000C-0x000F */ unsigned int ScalerSync;
/* 0x0010-0x0017 */ unsigned int ScalerTrig[2];
/* 0x0018-0x001F */ unsigned int ScalerGpio[2];
/* 0x0020-0x0033 */ unsigned int ScalerLvdsIn[5];
/* 0x0034-0x0047 */ unsigned int ScalerLvdsOut[5];
/* 0x0048-0x004F */ unsigned int ScalerSwAGpio[2];
/* 0x0050-0x0057 */ unsigned int ScalerSwBGpio[2];
/* 0x0058-0x005B */ unsigned int ScalerTokenIn;
/* 0x005C-0x005F */ unsigned int ScalerTokenOut;
/* 0x0060-0x0063 */ unsigned int ScalerBusy;
/* 0x0064-0x0067 */ unsigned int ScalerBusyCycles;
/* 0x0068-0x0087 */ unsigned int ScalerP2LvdsIn[8];
/* 0x0088-0x00A7 */ unsigned int ScalerP2LvdsOut[8];
/* 0x00A8-0x00AB */ unsigned int ScalerSdLink;
/* 0x00AC-0x00AF */ unsigned int ScalerTrigOut;
/* 0x00B0-0x00FF */ unsigned int Reserved0[(0x0100-0x00B0)/4];
/* 0x0100-0x0113 */ unsigned int LvdsOutSrc[5];
/* 0x0114-0x011B */ unsigned int GpioSrc[2];
/* 0x011C-0x0123 */ unsigned int SwAGpioSrc[2];
/* 0x0124-0x012B */ unsigned int SwBGpioSrc[2];
/* 0x012C-0x012F */ unsigned int TokenOutSrc;
/* 0x0130-0x0133 */ unsigned int SdLinkSrc;
/* 0x0134-0x0137 */ unsigned int TrigOutSrc;
/* 0x0138-0x0157 */ unsigned int P2LvdsOutSrc[8];
/* 0x0158-0x015B */ unsigned int SyncSrc;
/* 0x015C-0x015F */ unsigned int TrigSrc;
/* 0x0160-0x0163 */ unsigned int TokenInSrc;
/* 0x0164-0x017F */ unsigned int Reserved1[(0x0180-0x0164)/4];
/* 0x0180-0x0183 */ unsigned int PulserStart;
/* 0x0184-0x0187 */ unsigned int PulserPeriod;
/* 0x0188-0x018B */ unsigned int PulserHighCycles;
/* 0x018C-0x018F */ unsigned int PulserNPulses;
/* 0x0190-0x0193 */ unsigned int PulserStatus;
/* 0x0194-0x01FF */ unsigned int Reserved2[(0x0200-0x0194)/4];
} SSPTesting_Sd_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int BoardId;
/* 0x0004-0x0007 */ unsigned int FirmwareRev;
/* 0x0008-0x000B */ unsigned int Adr32M;
/* 0x000C-0x000F */ unsigned int Adr32;
/* 0x0010-0x0013 */ unsigned int VmeCfg;
/* 0x0014-0x0017 */ unsigned int Interrupt;
/* 0x0018-0x01FF */ unsigned int Reserved0[(0x0200-0x0018)/4];
} SSPTesting_SSPCfg_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int Ctrl;
/* 0x0004-0x0007 */ unsigned int TxRxSettings0;
/* 0x0008-0x000B */ unsigned int TxRxSettings1;
/* 0x000C-0x000F */ unsigned int DrpCtrl;
/* 0x0010-0x0013 */ unsigned int DrpStatus;
/* 0x0014-0x0017 */ unsigned int Status;
/* 0x0018-0x001B */ unsigned int SoftErrors0;
/* 0x001C-0x001F */ unsigned int SoftErrors1;
/* 0x0020-0x0023 */ unsigned int PrbsErrors0;
/* 0x0024-0x0027 */ unsigned int PrbsErrors1;
/* 0x0028-0x002B */ unsigned int RefTime;
/* 0x002C-0x002F */ unsigned int GClkFibTime;
/* 0x0030-0x01FF */ unsigned int Reserved0[(0x0200-0x0030)/4];
} SSPTesting_GtxQsfp_regs;

typedef struct
{
/* 0x0000-0x001F */ unsigned int Fiber[8];
/* 0x0020-0x0023 */ unsigned int SumDiscMode;
/* 0x0024-0x0027 */ unsigned int SumDiscThreshold;
/* 0x0028-0x002B */ unsigned int SumDiscWidth;
/* 0x002C-0x002F */ unsigned int Ctrl;
/* 0x0030-0x0033 */ unsigned int ILASumData;
/* 0x0034-0x0037 */ unsigned int ILASumThreshold;
/* 0x0038-0x003B */ unsigned int ILACtrl;
/* 0x003C-0x003F */ unsigned int ILAStatus;
/* 0x0040-0x01FF */ unsigned int Reserved0[(0x0200-0x0040)/4];
} SSPTesting_Trig_regs;

typedef struct
{
/* 0x0000-0x01FF */ SSPTesting_SSPCfg_regs         SSPCfg;
/* 0x0200-0x03FF */ SSPTesting_XpsI2C_regs         I2CIOExp;
/* 0x0400-0x05FF */ SSPTesting_XpsSpi_regs         SpiFlash;
/* 0x0600-0x07FF */ SSPTesting_XpsGpio_regs        Gpio;
/* 0x0800-0x0BFF */ unsigned int							Reserved1[(0x0C00-0x0800)/4];
/* 0x0C00-0x0DFF */ SSPTesting_Sd_regs					Sd;
/* 0x0E00-0x0FFF */ SSPTesting_Trig_regs				Trigger;
/* 0x1000-0x23FF */ SSPTesting_GtxQsfp_regs			GtxQsfp[10];
/* 0x2400-0x25FF */ SSPTesting_XpsI2C_regs			I2CDDR2;
/* 0x2600-0x2FFF */ unsigned int							Reserved2[(0x3000-0x2600)/4];
/* 0x3000-0x3FFF */ unsigned int							Bram[(0x4000-0x3000)/4];
} SSPTesting_SSP_regs;


#define CMD_SDRAM_STATUS	100
#define CMD_SDRAM_TEST0		101
#define CMD_SDRAM_TEST1		102
#define CMD_SDRAM_I2C_TEST	103
#define CMD_CLK_SET			105

#define SDRAM_TEST_LEN		1048576

#define SSP_TESTSTATE_MSG				1

#define SDRAM_TEST_WORD_NUM				4

#define BTN_SSP_TESTING_START			100
#define BTN_SSP_TESTING_CONTINUE		101
#define BTN_SSP_TESTING_STOP			102
#define BTN_SSP_TESTING_SAVE			103
#define BTN_SSP_ENTERINPUT				104

// Testing thresholds
#define SSP_TEST_INPUTCURRENT5V_MIN		4.0
#define SSP_TEST_INPUTCURRENT5V_MAX		8.0
#define SSP_TEST_INPUTCURRENT12VN_MIN	0.1
#define SSP_TEST_INPUTCURRENT12VN_MAX	0.5

#define SSP_TEST_VOLTAGE3P3V_MIN		3.135
#define SSP_TEST_VOLTAGE3P3V_MAX		3.465
#define SSP_TEST_VOLTAGE2P5V_MIN		2.375
#define SSP_TEST_VOLTAGE2P5V_MAX		2.625
#define SSP_TEST_VOLTAGE1P8V_MIN		1.71
#define SSP_TEST_VOLTAGE1P8V_MAX		1.89
#define SSP_TEST_VOLTAGE1P5V_MIN		1.425
#define SSP_TEST_VOLTAGE1P5V_MAX		1.575
#define SSP_TEST_VOLTAGE1V_MIN			0.95
#define SSP_TEST_VOLTAGE1V_MAX			1.05

#define SSP_TEST_BOARDID				0x00535350

#define SSP_TEST_BOARDPOS				(pM->BaseAddr>>19)

#define SSP_TEST_P0SWBTRIG2_MIN			(1000*0.9)
#define SSP_TEST_P0SWBTRIG2_MAX			(1000*1.1)

#define SSP_TEST_LOCALOSC50_MIN			(62500000*0.9)
#define SSP_TEST_LOCALOSC50_MAX			(62500000*1.1)

#define SSP_TEST_LOCALNOOSC_MIN			0
#define SSP_TEST_LOCALNOOSC_MAX			0

#define SSP_TEST_LOCAL250OSC_MIN		(250000000*0.99)
#define SSP_TEST_LOCAL250OSC_MAX		(250000000*1.01)

#define SSP_TEST_P0250OSC_MIN			(250000000*0.99)
#define SSP_TEST_P0250OSC_MAX			(250000000*1.01)

#define SSP_TEST_P2OSC_MIN				(240000000*0.99)
#define SSP_TEST_P2OSC_MAX				(240000000*1.01)

#define SSP_TEST_LOOPBACK_TOGGLE_NUM	10

// Supported testing states
enum SSPTestingStates
{
	ESSPInitialize,
	ESSPInputCurrent5V,
	ESSPInputCurrent12VN,
	ESSPVoltage3p3V,
	ESSPVoltage2p5V,
	ESSPVoltage1p8V,
	ESSPVoltage1p5V,
	ESSPVoltage1V,
	ESSPBoardId,
	ESSPBoardPos,
	ESSPVmeDataBits,
	ESSPClockP2,
	ESSPClockP0,
	ESSPClockLocal250,
	ESSPClockLocal50,
	ESSPCheckP0SwAStatus,
	ESSPCheckP0SwBStatus,
	ESSPCheckP0SwBToken,
	ESSPCheckP0SwBTrig,
	ESSPCheckP0SwBSync,
	ESSPCheckP0SwBTrig2,
	ESSPCheckFrontPanelLvds,
	ESSPCheckP2Lvds,
	ESSPCheckP0SwALanes01,
	ESSPCheckP0SwALanes23,
	ESSPCheckFiber0Lanes,
	ESSPCheckFiber1Lanes,
	ESSPCheckFiber2Lanes,
	ESSPCheckFiber3Lanes,
	ESSPCheckFiber4Lanes,
	ESSPCheckFiber5Lanes,
	ESSPCheckFiber6Lanes,
	ESSPCheckFiber7Lanes,
	ESSPCheckFiberLeds,
	ESSPCheckSdram,
	ESSPCheckSdramI2C,
	ESSPCheckIOExpander,
	ESSPCheckFrontPanelNim,
	ESSPCheckSpiFlash,
	ESSPStoreSerialNumber,
	ESSPSaveTestResults,
	ESSPComplete
};

// Testing state sequence
int SSPTestSequence[] = {
		ESSPInitialize,
		ESSPCheckSpiFlash,
		ESSPStoreSerialNumber,
		ESSPBoardId,
		ESSPBoardPos,
		ESSPVmeDataBits,
		ESSPClockLocal50,
		ESSPClockP0,
/*		ESSPClockP2,*/
		ESSPClockLocal250,
		ESSPCheckSdram,
		ESSPCheckSdramI2C,
/*		ESSPCheckIOExpander,*/
		ESSPCheckP0SwAStatus,
		ESSPCheckP0SwBStatus,
		ESSPCheckFrontPanelLvds,
/*		ESSPCheckP2Lvds,*/
		ESSPCheckP0SwALanes01,
		ESSPCheckP0SwALanes23,
		ESSPCheckFiber0Lanes,
		ESSPCheckFiber1Lanes,
		ESSPCheckFiber2Lanes,
		ESSPCheckFiber3Lanes,
		ESSPCheckFiber4Lanes,
		ESSPCheckFiber5Lanes,
		ESSPCheckFiber6Lanes,
		ESSPCheckFiber7Lanes,
		ESSPCheckP0SwBToken,
		ESSPCheckP0SwBTrig,
		ESSPCheckP0SwBSync,
/*		ESSPCheckP0SwBTrig2,*/
/*		ESSPCheckFrontPanelNim,*/
		ESSPCheckFiberLeds,
		ESSPInputCurrent5V,
/*		ESSPInputCurrent12VN,*/
/*		ESSPVoltage3p3V,
		ESSPVoltage2p5V,
		ESSPVoltage1p8V,
		ESSPVoltage1p5V,
		ESSPVoltage1V,*/
		ESSPSaveTestResults,
		ESSPComplete
	};

class SSP_Testing	: public TGCompositeFrame
{
public:
	SSP_Testing(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (SSPTesting_SSP_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonStart = new TGTextButton(pTF1, "Start", BTN_SSP_TESTING_START), new TGLayoutHints(kLHintsCenterX));
				pButtonStart->SetWidth(200);
				pButtonStart->Associate(this);

			pTF1->AddFrame(pButtonContinue = new TGTextButton(pTF1, "Continue", BTN_SSP_TESTING_CONTINUE), new TGLayoutHints(kLHintsCenterX));
				pButtonContinue->Associate(this);
				pButtonContinue->SetEnabled(kFALSE);

			pTF1->AddFrame(pButtonStop = new TGTextButton(pTF1, "Stop", BTN_SSP_TESTING_STOP), new TGLayoutHints(kLHintsCenterX));
				pButtonStop->Associate(this);
				pButtonStop->SetEnabled(kFALSE);

			pTF1->AddFrame(pButtonSave = new TGTextButton(pTF1, "Save", BTN_SSP_TESTING_SAVE), new TGLayoutHints(kLHintsCenterX));
				pButtonSave->Associate(this);
				pButtonSave->SetEnabled(kFALSE);

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTF1->AddFrame(pTextViewDebug = new TGTextView(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(new TGLabel(pTF1, "User Input: "), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
			pTF1->AddFrame(pTextEntryDebug = new TGTextEntry(pTF1), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonUserInput = new TGTextButton(pTF1, "Enter Input", BTN_SSP_ENTERINPUT));
				pButtonUserInput->Associate(this);
				pButtonUserInput->SetEnabled(kFALSE);
	}

	int SelectClkSrc(int src)
	{
		pM->WriteReg32(&pRegs->Bram[1], src);
		pM->WriteReg32(&pRegs->Bram[0], CMD_CLK_SET);
		pM->Delay(500);
		if(pM->ReadReg32(&pRegs->Bram[0]))
		{
			AddTextLine("      FAILED");
			TestingStop();
			return 1;
		}
		return 0;
/*
		str += "PASSED";
		AddTextLine(str);

		if((src < CLKSRC_DISABLED) || (src > CLKSRC_LOCAL))
		{
			printf("Error: SelectClkSrc() invalid clock source\n");
			return;
		}

		pM->RMWReg32(&pRegs->Gpio.Data, GPIO_GCLKPLL_RESET, GPIO_GCLKPLL_RESET);

		for(i = 0; i < 4; i++)
		{
			pM->RMWReg32(&pRegs->Gpio.Data, 0, GPIO_CLK_SOUT0 | GPIO_CLK_SOUT1 | GPIO_CLK_SIN0 | GPIO_CLK_SIN1 | GPIO_CLK_LOAD | GPIO_CLK_CONF);

			if(i & 0x1)
				pM->RMWReg32(&pRegs->Gpio.Data, GPIO_CLK_SOUT0, GPIO_CLK_SOUT0);
			if(i & 0x2)
				pM->RMWReg32(&pRegs->Gpio.Data, GPIO_CLK_SOUT1, GPIO_CLK_SOUT1);
			if(src & 0x1)
				pM->RMWReg32(&pRegs->Gpio.Data, GPIO_CLK_SIN0, GPIO_CLK_SIN0);
			if(src & 0x2)
				pM->RMWReg32(&pRegs->Gpio.Data, GPIO_CLK_SIN1, GPIO_CLK_SIN1);

			pM->RMWReg32(&pRegs->Gpio.Data, GPIO_CLK_LOAD, GPIO_CLK_LOAD);
			pM->RMWReg32(&pRegs->Gpio.Data, 0, GPIO_CLK_LOAD);
			pM->RMWReg32(&pRegs->Gpio.Data, GPIO_CLK_CONF, GPIO_CLK_CONF);
			pM->RMWReg32(&pRegs->Gpio.Data, 0, GPIO_CLK_CONF);
		}

		pM->RMWReg32(&pRegs->Gpio.Data, 0, GPIO_GCLKPLL_RESET);
		gSystem->Sleep(100);
		pM->RMWReg32(&pRegs->Gpio.Data, GPIO_PLL_LOL, GPIO_PLL_LOL);
		pM->RMWReg32(&pRegs->Gpio.Data, 0, GPIO_PLL_LOL);
		*/
	}

	void SetNextTestingState(int nextState)
	{
		nextTestingState = nextState;
		bPromptInputReady = kFALSE;
		bPromptContinueReady = kFALSE;

		SendMessage(this, MK_MSG(kC_USER, (EWidgetMessageTypes)SSP_TESTSTATE_MSG), nextTestingState, 0);
	}

	void TestingPromptContinue(const char *prompt)
	{
		AddTextLine(prompt);
		pButtonContinue->SetEnabled(kTRUE);
	}

	void TestingPromptInput(const char *prompt)
	{
		AddTextLine(prompt);
		pButtonUserInput->SetEnabled(kTRUE);
	}

	void Testing_CheckP2Lvds()
	{
		unsigned int result, i;
		TString str;

		///////////////////////////////////
		// Checking P2 LVDS Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP2Lvds **********");

		for(i = 0; i < 8; i++)
			pM->WriteReg32(&pRegs->Sd.P2LvdsOutSrc[i], MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int j = 0; j < SSP_TEST_LOOPBACK_TOGGLE_NUM; j++)
		{
			for(i = 0; i < 8; i++)
			{
				pM->WriteReg32(&pRegs->Sd.P2LvdsOutSrc[i], MUX_SRC_1);
				pM->WriteReg32(&pRegs->Sd.P2LvdsOutSrc[i], MUX_SRC_0);
			}
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		for(i = 0; i < 8; i++)
		{
			result = pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[i]);

			str.Form("   Toggled P2Output%d %u times...Received %u P2Input%d toggles...", i, SSP_TEST_LOOPBACK_TOGGLE_NUM, result, i);

			if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
			{
				str += "PASSED";
				AddTextLine(str);
			}
			else
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckFrontPanelLvds()
	{
		unsigned int result, i;
		TString str;

		///////////////////////////////////
		// Checking Front Panel LVDS Loopback
		///////////////////////////////////
		AddTextLine("********** CheckFrontPanelLvds **********");

		for(i = 0; i < 5; i++)
			pM->WriteReg32(&pRegs->Sd.LvdsOutSrc[i], MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int j = 0; j < SSP_TEST_LOOPBACK_TOGGLE_NUM; j++)
		{
			for(i = 0; i < 5; i++)
			{
				pM->WriteReg32(&pRegs->Sd.LvdsOutSrc[i], MUX_SRC_1);
				pM->WriteReg32(&pRegs->Sd.LvdsOutSrc[i], MUX_SRC_0);
			}
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		for(i = 0; i < 5; i++)
		{
			result = pM->ReadReg32(&pRegs->Sd.ScalerLvdsIn[i]);

			str.Form("   Toggled FPOutput%d %u times...Received %u FPInput%d toggles...", i, SSP_TEST_LOOPBACK_TOGGLE_NUM, result, i);

			if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
			{
				str += "PASSED";
				AddTextLine(str);
			}
			else
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckP0SwBSdlink_Sync()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B Sdlink->Sync Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBSdlink_Sync **********");

		pM->WriteReg32(&pRegs->Sd.SdLinkSrc, MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int i = 0; i < SSP_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->Sd.SdLinkSrc, MUX_SRC_1);
			pM->WriteReg32(&pRegs->Sd.SdLinkSrc, MUX_SRC_0);
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		result = pM->ReadReg32(&pRegs->Sd.ScalerSync);

		str.Form("   Toggled SWB Sdlink %u times...Received %u SWB Sync toggles...", SSP_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();

while(1)
{
			pM->WriteReg32(&pRegs->Sd.SdLinkSrc, MUX_SRC_1);
gSystem->Sleep(1);
			pM->WriteReg32(&pRegs->Sd.SdLinkSrc, MUX_SRC_0);
gSystem->Sleep(1);
}
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckP0SwBTrigOut_Trig1()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B TrigOut->Trig1 Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBTrigOut_Trig1 **********");

		pM->WriteReg32(&pRegs->Sd.TrigOutSrc, MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int i = 0; i < SSP_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->Sd.TrigOutSrc, MUX_SRC_1);
			pM->WriteReg32(&pRegs->Sd.TrigOutSrc, MUX_SRC_0);
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		result = pM->ReadReg32(&pRegs->Sd.ScalerTrig[0]);

		str.Form("   Toggled SWB TrigOut %u times...Received %u SWB Trig1 toggles...", SSP_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckP0SwBTokenOut_TokenIn()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B TokenOut->TokenIn Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBTokenOut_TokenIn **********");

		pM->WriteReg32(&pRegs->Sd.TokenOutSrc, MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int i = 0; i < SSP_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->Sd.TokenOutSrc, MUX_SRC_1);
			pM->WriteReg32(&pRegs->Sd.TokenOutSrc, MUX_SRC_0);
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		result = pM->ReadReg32(&pRegs->Sd.ScalerTokenIn);

		str.Form("   Toggled SWB TokenOut %u times...Received %u SWB TokenIn toggles...", SSP_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckP0SwAStatusIO()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch A SDA/SCL Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwAStatusIO **********");

		pM->WriteReg32(&pRegs->Sd.SwAGpioSrc[0], SWx_GPIO_NOEx);
		pM->WriteReg32(&pRegs->Sd.SwAGpioSrc[1], MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int i = 0; i < SSP_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->Sd.SwAGpioSrc[1], MUX_SRC_1);
			pM->WriteReg32(&pRegs->Sd.SwAGpioSrc[1], MUX_SRC_0);
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		result = pM->ReadReg32(&pRegs->Sd.ScalerSwAGpio[0]);

		str.Form("   Toggled SWA SE1 %u times...Received %u SWA SE0 toggles...", SSP_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckP0SwBStatusIO()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B SDA/SCL Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBStatusIO **********");

		pM->WriteReg32(&pRegs->Sd.SwBGpioSrc[0], SWx_GPIO_NOEx);
		pM->WriteReg32(&pRegs->Sd.SwBGpioSrc[1], MUX_SRC_0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		for(int i = 0; i < SSP_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->Sd.SwBGpioSrc[1], MUX_SRC_1);
			pM->WriteReg32(&pRegs->Sd.SwBGpioSrc[1], MUX_SRC_0);
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		result = pM->ReadReg32(&pRegs->Sd.ScalerSwBGpio[0]);

		str.Form("   Toggled SWB SE1 %u times...Received %u SWB SE0 toggles...", SSP_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == SSP_TEST_LOOPBACK_TOGGLE_NUM)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}
	
	void Testing_CheckP0SwBTrig2()
	{
		///////////////////////////////////
		// Checking P0 Switch B Trig2
		///////////////////////////////////
		if(!bPromptInputReady)
		{
			AddTextLine("********** CheckP0SwBTrig2 **********");
			TestingPromptInput("   Connect P0 Trig2 1kHz LVDS clock to SWB FP.");
			return;
		}

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.ScalerSysclk) / SYSCLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.ScalerTrig[1]) / scale;

		Testing_MinMaxRangeInt32("CheckP0SwBTrig2", "", (int)SSP_TEST_P0SWBTRIG2_MIN, (int)SSP_TEST_P0SWBTRIG2_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP2Osc()
	{
		///////////////////////////////////
		// Checking P2 Oscillator
		///////////////////////////////////
		if(!bPromptInputReady)
		{
			AddTextLine("********** CheckP2Osc **********");
			TestingPromptInput("   Connect P2 240MHz clock.");
			return;
		}

		if(SelectClkSrc(CLKSRC_P2))
			return;

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.ScalerSysclk) / SYSCLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.ScalerGclk) / scale;

		Testing_MinMaxRangeInt32("CheckP2Osc", "", (int)SSP_TEST_P2OSC_MIN, (int)SSP_TEST_P2OSC_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP0250MHzOsc()
	{
		///////////////////////////////////
		// Checking P0 250 Oscillator
		///////////////////////////////////
		AddTextLine("********** CheckP0250MHzOsc **********");
		if(SelectClkSrc(CLKSRC_SWB))
			return;

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.ScalerSysclk) / SYSCLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.ScalerGclk) / scale;
		printf("Testing_CheckP0250MHzOsc() ref=%lf\n", ref);
		Testing_MinMaxRangeInt32("CheckP0250MHzOsc", "", (int)SSP_TEST_P0250OSC_MIN, (int)SSP_TEST_P0250OSC_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckLocal250MHzOsc()
	{
		///////////////////////////////////
		// Checking Local 250 Oscillator
		///////////////////////////////////
		AddTextLine("********** CheckLocal250MHzOsc **********");
		if(SelectClkSrc(CLKSRC_LOCAL))
			return;

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.ScalerSysclk) / SYSCLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.ScalerGclk) / scale;

		Testing_MinMaxRangeInt32("CheckLocal250MHzOsc", "", (int)SSP_TEST_LOCAL250OSC_MIN, (int)SSP_TEST_LOCAL250OSC_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckLocal50MHzOsc()
	{
		///////////////////////////////////
		// Checking 50MHz Oscillator
		///////////////////////////////////
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);
		unsigned int ref = pM->ReadReg32(&pRegs->Sd.ScalerSysclk);

		Testing_MinMaxRangeInt32("CheckLocal50MHzOsc", "", (int)SSP_TEST_LOCALOSC50_MIN, (int)SSP_TEST_LOCALOSC50_MAX, (int)ref, kFALSE);
	}
	
	void Testing_CheckVmeDataBits()
	{
		TString str;

		///////////////////////////////////
		// Checking Vme Data Bits
		///////////////////////////////////
		AddTextLine("********** CheckVmeDataBits **********");

		unsigned int result;
		for(int i = 0; i < 32; i++)
		{
			pM->WriteReg32(&pRegs->SSPCfg.Adr32, (1<<i));
			pM->WriteReg32(&pRegs->SSPCfg.Adr32M, 0);
			result = pM->ReadReg32(&pRegs->SSPCfg.Adr32);

			str.Form("   Wrote 0x%08X, Read 0x%08X...", 1<<i, result);
			if((1<<i) != result)
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
			str += "PASSED";
			AddTextLine(str);
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void SpiFlashSelect(int sel)
	{
		if(sel)
			pM->WriteReg32(&pRegs->SpiFlash.SSR, 0x0);
		else
			pM->WriteReg32(&pRegs->SpiFlash.SSR, 0x1);
	}

	unsigned char SpiFlashTransferByte(unsigned char data)
	{
		pM->WriteReg32(&pRegs->SpiFlash.DTR, data);
		for(int i = 0; i < 5; i++)
		{
			if(!(pM->ReadReg32(&pRegs->SpiFlash.SR) & 0x1))
				break;
		}
		return pM->ReadReg32(&pRegs->SpiFlash.DRR) & 0xFF;
	}

	void Testing_CheckSpiFlash()
	{
		TString str;
		unsigned int result;

		///////////////////////////////////
		// Checking Spi Flash Id
		///////////////////////////////////
		AddTextLine("********** CheckSpiFlash **********");

		pM->WriteReg32(&pRegs->SpiFlash.SRR, 0x0000000A);
		pM->WriteReg32(&pRegs->SpiFlash.CR, 0xE6);
		SpiFlashSelect(0);
		pM->Delay(20);
		SpiFlashSelect(1);
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xFF);
		SpiFlashSelect(0);
/*
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x03);	// Read Continuous
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xF8);
		SpiFlashTransferByte(0x00);
		printf("\nSPI Config page: ");
		for(i = 0; i < 64; i++)
		{
			result = SpiFlashTransferByte(0xFF);
			printf("%02X ", result);
		}
		printf("\n");
		SpiFlashSelect(0);
*/

//while(1)
//{
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x9F);	// Read ID Cmd
		result = SpiFlashTransferByte(0xFF);
		result |= SpiFlashTransferByte(0xFF)<<8;
		result |= SpiFlashTransferByte(0xFF)<<16;
		result |= SpiFlashTransferByte(0xFF)<<24;
		SpiFlashSelect(0);
//printf("SpiFlashId = %08X\n", result);
//gSystem->Sleep(100);
//}
		str.Form("   Spi Flash Id = 0x%08X...", result);
		if(result != 0x0000281F)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_StoreSerialNumber()
	{
		TString str = strPromptInput;
		int i;
		unsigned int result;

		///////////////////////////////////
		// Erase SPI parameter page, Store S/N
		///////////////////////////////////
		if(!bPromptInputReady)
		{
			AddTextLine("********** StoreSerialNumber **********");
			TestingPromptInput("   Enter Serial Number: ");
			return;
		}

		strSerialNumber = strPromptInput;
		AddTextLine(str.Format("   Writing serial number: %s to flash", str.Data()));
		
		pM->WriteReg32(&pRegs->SpiFlash.SRR, 0x0000000A);
		pM->WriteReg32(&pRegs->SpiFlash.CR, 0xE6);
		pM->WriteReg32(&pRegs->SpiFlash.SSR, 0x1);

		SpiFlashSelect(1);
		SpiFlashTransferByte(0x84);	// Buffer 1 Write
		SpiFlashTransferByte(0x00);
		SpiFlashTransferByte(0x00);
		SpiFlashTransferByte(0x00);
		for(i = 0; i < 1056; i++)
		{
			if(i < str.Length())
				SpiFlashTransferByte(str[i]);
			else if(i == str.Length())
				SpiFlashTransferByte(0x00);
			else
				SpiFlashTransferByte(0xFF);
		}
		SpiFlashSelect(0);

		SpiFlashSelect(1);
		SpiFlashTransferByte(0x83);	// Buffer 1 -> flash page write w/Erase
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xF8);
		SpiFlashTransferByte(0x00);
		SpiFlashSelect(0);

		pM->Delay(50);	// 40ms Max erase+program time

		SpiFlashSelect(1);
		SpiFlashTransferByte(0xD7);	// Status Read
		result = SpiFlashTransferByte(0xFF);
		SpiFlashSelect(0);
		str.Form("      Spi Status(0x%02X)...", result);
		if((result & 0xBF) != 0xBC)
		{
			str.Form("   FAILED", result);
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);
		
		AddTextLine("   Verifying flash write...");
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x60);	// Page/buffer 1 compare
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xF8);
		SpiFlashTransferByte(0x00);
		SpiFlashSelect(0);

		pM->Delay(1);	// 400us Max compare time

		str.Form("      Spi Status(0x%02X)...", result);
		if((result & 0xFF) != 0xBC)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckIOExpander()
	{
		TString str;

		///////////////////////////////////
		// Checking IO Exander I2C
		///////////////////////////////////
		AddTextLine("********** CheckIOExpander **********");
/*
		str.Form("   Checking Sdram SPD...");
		pM->WriteReg32(&pRegs->Bram[1], 18);
		pM->WriteReg32(&pRegs->Bram[0], CMD_SDRAM_I2C_TEST);
		pM->pVMEClient->Delay(500);
		if(pM->ReadReg32(&pRegs->Bram[0]))
		{
			str += "timeout. FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		result = pM->ReadReg32(&pRegs->Bram[1]);
		str.Form("   Response length = %d", result);
		if(result != 18)
		{
			str += "!= 18. FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += " ok.";
		AddTextLine(str);

		memset(buf, 0, sizeof(buf));
		for(i = 0; i < 18; i++)
		{
			if(!(i & 0x3))
				result = pM->ReadReg32(&pRegs->Bram[2+i/4]);
			
			if((i & 0x3) == 3) buf[i] = (result>>0)&0xFF;
			if((i & 0x3) == 2) buf[i] = (result>>8)&0xFF;
			if((i & 0x3) == 1) buf[i] = (result>>16)&0xFF;
			if((i & 0x3) == 0) buf[i] = (result>>24)&0xFF;
		}

		str.Form("   SDRAM Part = %18s...", buf);
		if(strncmp(buf, sdramPart, 18))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);
*/
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckSdramI2C()
	{
		TString str;
		int i;
		unsigned int result;
		const char *sdramPart = "16HTF51264HZ-800C1";
		char buf[50];

		///////////////////////////////////
		// Checking DDR2 Sdram I2C Eeprom
		///////////////////////////////////
		AddTextLine("********** CheckSdramI2C **********");
		str.Form("   Checking Sdram SPD...");
		pM->WriteReg32(&pRegs->Bram[1], 18);
		pM->WriteReg32(&pRegs->Bram[0], CMD_SDRAM_I2C_TEST);
		pM->Delay(500);
		if(pM->ReadReg32(&pRegs->Bram[0]))
		{
			str += "timeout. FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		result = pM->ReadReg32(&pRegs->Bram[1]);
		str.Form("   Response length = %d", result);
		if(result != 18)
		{
			str += "!= 18. FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += " ok.";
		AddTextLine(str);

		memset(buf, 0, sizeof(buf));
		for(i = 0; i < 18; i++)
		{
			if(!(i & 0x3))
				result = pM->ReadReg32(&pRegs->Bram[2+i/4]);
			
			if((i & 0x3) == 3) buf[i] = (result>>0)&0xFF;
			if((i & 0x3) == 2) buf[i] = (result>>8)&0xFF;
			if((i & 0x3) == 1) buf[i] = (result>>16)&0xFF;
			if((i & 0x3) == 0) buf[i] = (result>>24)&0xFF;
		}

		str.Form("   SDRAM Part = %18s...", buf);
		if(strncmp(buf, sdramPart, 18))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckSdram()
	{
		TString str;
		unsigned int result;
		int i;

		///////////////////////////////////
		// Checking DDR2 Sdram I2C Eeprom
		///////////////////////////////////
		AddTextLine("********** CheckSdram **********");

		str.Form("   Checking Sdram status...");
		pM->WriteReg32(&pRegs->Bram[0], CMD_SDRAM_STATUS);
		pM->Delay(500);
		if(pM->ReadReg32(&pRegs->Bram[0]))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		result = pM->ReadReg32(&pRegs->Bram[2]);
		AddTextLine(str.Format("   CALIB_REG           = 0x%08X...", result));
		AddTextLine(str.Format("      IDELAYCTRL_RDY_O = %d", (result>>25) & 0x1));
		AddTextLine(str.Format("      IDELAYCTRL_RDY_I = %d", (result>>24) & 0x1));
		AddTextLine(str.Format("      MIG_INIT_DONE    = %d", (result>>16) & 0x1));
		if((result & 0x03010000) != 0x03010000)
		{
			AddTextLine("      ...FAILED");
			TestingStop();
			return;
		}
		else
			AddTextLine("      ...PASSED");

		result = pM->ReadReg32(&pRegs->Bram[3]);
		AddTextLine(str.Format("   CALIB_STATUS     = 0x%08X...", result));
		AddTextLine(str.Format("      BIT_ERR_INDEX = %d", (result>>24) & 0x7F));
		AddTextLine(str.Format("      DONE_STATUS   = %d", (result>>16) & 0xF));
		AddTextLine(str.Format("      ERR_STATUS    = %d", (result>>0) & 0xF));
		if((result & 0x000F000F) != 0x000F0000)
		{
			AddTextLine("      ...FAILED");
			TestingStop();
			return;
		}
		else
			AddTextLine("      ...PASSED");

		for(i = 0; i < 8; i++)
			AddTextLine(str.Format("   DQS_GROUP%d     = 0x%08X", i, pM->ReadReg32(&pRegs->Bram[4+i])));
		for(i = 0; i < 8; i++)
			AddTextLine(str.Format("   DQS_TAP_CNT%d   = 0x%08X", i, pM->ReadReg32(&pRegs->Bram[12+i])));
		for(i = 0; i < 8; i++)
			AddTextLine(str.Format("   GATE_TAP_CNT%d  = 0x%08X", i, pM->ReadReg32(&pRegs->Bram[20+i])));
		for(i = 0; i < 64; i++)
			AddTextLine(str.Format("   DQ_TAP_CNT%2d   = 0x%08X", i, pM->ReadReg32(&pRegs->Bram[28+i])));



		str.Form("   Checking Sdram read/write 0...");
		pM->WriteReg32(&pRegs->Bram[1], SDRAM_TEST_LEN);
		pM->WriteReg32(&pRegs->Bram[0], CMD_SDRAM_TEST0);
		pM->Delay(1000);
		if(pM->ReadReg32(&pRegs->Bram[0]) || pM->ReadReg32(&pRegs->Bram[1]))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		str.Form("   Checking Sdram read/write 1...");
		pM->WriteReg32(&pRegs->Bram[1], SDRAM_TEST_LEN);
		pM->WriteReg32(&pRegs->Bram[0], CMD_SDRAM_TEST1);
		pM->Delay(1000);
		if(pM->ReadReg32(&pRegs->Bram[0]) || pM->ReadReg32(&pRegs->Bram[1]))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckBoardPos()
	{
		TString str;

		///////////////////////////////////
		// Checking BoardPos
		///////////////////////////////////
		AddTextLine("********** CheckBoardPos **********");
		unsigned int BoardPos = (pM->ReadReg32(&pRegs->SSPCfg.VmeCfg) >> 8) & 0x1F;
		str.Form("   BoardPosition(%d) == %d...", SSP_TEST_BOARDPOS, BoardPos);
		if(BoardPos == SSP_TEST_BOARDPOS)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckFiberLeds()
	{
		TString str = strPromptInput;

		///////////////////////////////////
		// Checking Fiber LEDs
		///////////////////////////////////
		if(!bPromptInputReady)
		{
			AddTextLine("********** CheckFiberLeds **********");
			TestingPromptInput("   Are all fiber LEDs on (enter 'y' or 'n'): ");
			return;
		}

		if(str.EqualTo("y", TString::kIgnoreCase))
		{
			str = "   y...PASSED";
			AddTextLine(str);
		}
		else
		{
			str = "   n...FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckBoardId()
	{
		TString str;

		///////////////////////////////////
		// Checking BoardId
		///////////////////////////////////
		AddTextLine("********** CheckBoardId **********");
		unsigned int BoardId = pM->ReadReg32(&pRegs->SSPCfg.BoardId);
		str.Form("   BoardId(0x%08X) == 0x%08X...", SSP_TEST_BOARDID, BoardId);
		if(BoardId == SSP_TEST_BOARDID)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		str.Form("   Firmware revision = 0x%08X", pM->ReadReg32(&pRegs->SSPCfg.FirmwareRev));
		AddTextLine(str);

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckFrontPanelNim()
	{
		TString str = strPromptInput;

		///////////////////////////////////
		// Checking Front Panel NIM
		///////////////////////////////////
		if(!bPromptInputReady)
		{
			AddTextLine("********** CheckFrontPanelNim **********");
			pM->WriteReg32(&pRegs->Sd.GpioSrc[0], MUX_SRC_PULSER);
			pM->WriteReg32(&pRegs->Sd.GpioSrc[1], MUX_SRC_PULSER);
			pM->WriteReg32(&pRegs->Sd.PulserPeriod, 62500);
			pM->WriteReg32(&pRegs->Sd.PulserHighCycles, 31250);
			pM->WriteReg32(&pRegs->Sd.PulserNPulses, 0xFFFFFFFF);
			TestingPromptInput("   Are GPIO NIM 0 & 1 toggling ~1kHz, ~50% duty, NIM (enter 'y' or 'n'): ");
			return;
		}

		if(str.EqualTo("y", TString::kIgnoreCase))
		{
			str = "   y...PASSED";
			AddTextLine(str);
		}
		else
		{
			str = "   n...FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_CheckTransceiver(const char *measurement, SSPTesting_GtxQsfp_regs *pGtx, int nlanes)
	{
		unsigned int result, i;
		TString str;

		///////////////////////////////////
		// Checking Gtx Loopback
		///////////////////////////////////
		str.Form("********** %s **********", measurement);
		AddTextLine(str);

		pM->WriteReg32(&pGtx->Ctrl, 0x00000203);
		pM->WriteReg32(&pGtx->Ctrl, 0x00000202);
		pM->WriteReg32(&pGtx->Ctrl, 0x00000200);
		pM->WriteReg32(&pGtx->Ctrl, 0x00000000);

		pM->RMWReg32(&pGtx->Ctrl, 0x80000000, 0x80000000);
		pM->Delay(500);
		pM->RMWReg32(&pGtx->Ctrl, 0x80000000, 0x80000000);
		pM->Delay(500);

		// Latch error counter after 1s
		pM->RMWReg32(&pGtx->Ctrl, 0x80000000, 0x80000000);
		pM->Delay(1000);
		pM->RMWReg32(&pGtx->Ctrl, 0x80000000, 0x80000000);

		for(i = 0; i < nlanes; i++)
		{
			result = (pM->ReadReg32(&pGtx->Status)>>(4+i)) & 0x1;
			str.Form("   Lane %d  up = %d...", i, result);
			if(result)
			{
				str += "PASSED";
				AddTextLine(str);
			}
			else
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}

			if(nlanes == 4)	// check errors on fiber
			{
				if(i == 0)
					result = (pM->ReadReg32(&pGtx->SoftErrors0)>>0) & 0xFFFF;
				else if(i == 1)
					result = (pM->ReadReg32(&pGtx->SoftErrors0)>>16) & 0xFFFF;
				else if(i == 2)
					result = (pM->ReadReg32(&pGtx->SoftErrors1)>>0) & 0xFFFF;
				else if(i == 3)
					result = (pM->ReadReg32(&pGtx->SoftErrors1)>>16) & 0xFFFF;

				str.Form("   Errors = %u...", result);
				if(result == 0)
				{
					str += "PASSED";
					AddTextLine(str);
				}
				else
				{
					str += "FAILED";
					AddTextLine(str);
					TestingStop();
					return;
				}
			}
		}

		result = (pM->ReadReg32(&pGtx->Status)>>12) & 0x1;
		str.Form("   Channel up = %d...", result);
		if(result)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_MinMaxRangeInt32(const char *measurement, const char *units, int min, int max, int val, Bool_t bInput)
	{
		TString str = strPromptInput;

		AddTextLine(str.Format("********** %s **********", measurement));

		if(bInput)
		{
			if(!bPromptInputReady || !str.IsDec())
			{
				TestingPromptInput(str.Format("Enter SSP %s(in %s): ", measurement, units));
				return;
			}
			val = str.Atoi();
		}

		///////////////////////////////////
		// Checking min range
		///////////////////////////////////
		str.Form("   min(%d) >= %d...", min, val);
		if(val >= min)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		///////////////////////////////////
		// Checking max range
		///////////////////////////////////
		str.Form("   max(%d) <= %d...", max, val);
		if(val <= max)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_MinMaxRangeDouble(const char *measurement, const char *units, double min, double max, double val, Bool_t bInput)
	{
		TString str = strPromptInput;
		
		AddTextLine(str.Format("********** %s **********", measurement));

		if(bInput)
		{
			if(!bPromptInputReady || !str.IsFloat())
			{
				TestingPromptInput(str.Format("Enter SSP %s(in %s): ", measurement, units));
				return;
			}
			val = str.Atof();
		}

		///////////////////////////////////
		// Checking min range
		///////////////////////////////////
		str.Form("   min(%f) <= %f...", min, val);
		if(val >= min)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		///////////////////////////////////
		// Checking max range
		///////////////////////////////////
		str.Form("   max(%f) >= %f...", max, val);
		if(val <= max)
		{
			str += "PASSED";
			AddTextLine(str);
		}
		else
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_Initialize()
	{
		TDatime t;
		TString str;

		strSerialNumber = "none";

		AddTextLine("SSP Testing Initialzed...");
		AddTextLine(str.Format("Test Data/Time: %s", t.AsString()));

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_Complete()
	{
		AddTextLine("SSP Testing Complete. Unit PASSED");
		TestingStop();
	}

	void ExecNextTestingState(int curState)
	{
		if(!pButtonStop->IsEnabled())
			return;

		switch(SSPTestSequence[curState])
		{
			case ESSPInitialize:				Testing_Initialize(); break;
			case ESSPInputCurrent5V:		Testing_MinMaxRangeDouble("+5V Input Current", "Amps", SSP_TEST_INPUTCURRENT5V_MIN, SSP_TEST_INPUTCURRENT5V_MAX, 0, kTRUE); break;
			case ESSPInputCurrent12VN:		Testing_MinMaxRangeDouble("-12V Input Current", "Amps", SSP_TEST_INPUTCURRENT12VN_MIN, SSP_TEST_INPUTCURRENT12VN_MAX, 0, kTRUE); break;
			case ESSPVoltage3p3V:			Testing_MinMaxRangeDouble("+3.3V Rail", "Volts", SSP_TEST_VOLTAGE3P3V_MIN, SSP_TEST_VOLTAGE3P3V_MAX, 0, kTRUE); break;
			case ESSPVoltage2p5V:			Testing_MinMaxRangeDouble("+2.5V Rail", "Volts", SSP_TEST_VOLTAGE2P5V_MIN, SSP_TEST_VOLTAGE2P5V_MAX, 0, kTRUE); break;
			case ESSPVoltage1p8V:			Testing_MinMaxRangeDouble("+1.8V Rail", "Volts", SSP_TEST_VOLTAGE1P8V_MIN, SSP_TEST_VOLTAGE1P8V_MAX, 0, kTRUE); break;
			case ESSPVoltage1p5V:			Testing_MinMaxRangeDouble("+1.5V Rail", "Volts", SSP_TEST_VOLTAGE1P5V_MIN, SSP_TEST_VOLTAGE1P5V_MAX, 0, kTRUE); break;
			case ESSPVoltage1V:				Testing_MinMaxRangeDouble("+1.0V Rail", "Volts", SSP_TEST_VOLTAGE1V_MIN, SSP_TEST_VOLTAGE1V_MAX, 0, kTRUE); break;
			case ESSPBoardId:					Testing_CheckBoardId(); break;
			case ESSPBoardPos:				Testing_CheckBoardPos(); break;
			case ESSPVmeDataBits:			Testing_CheckVmeDataBits(); break;
			case ESSPClockP2:					Testing_CheckP2Osc(); break;
			case ESSPClockP0:					Testing_CheckP0250MHzOsc(); break;
			case ESSPClockLocal250:			Testing_CheckLocal250MHzOsc(); break;
			case ESSPClockLocal50:			Testing_CheckLocal50MHzOsc(); break;
			case ESSPCheckP0SwAStatus:		Testing_CheckP0SwAStatusIO(); break;
			case ESSPCheckP0SwBStatus:		Testing_CheckP0SwBStatusIO(); break;
			case ESSPCheckP0SwBToken:		Testing_CheckP0SwBTokenOut_TokenIn(); break;
			case ESSPCheckP0SwBTrig:		Testing_CheckP0SwBTrigOut_Trig1(); break;
			case ESSPCheckP0SwBSync:		Testing_CheckP0SwBSdlink_Sync(); break;
			case ESSPCheckP0SwBTrig2:		Testing_CheckP0SwBTrig2(); break;
			case ESSPCheckFrontPanelLvds:	Testing_CheckFrontPanelLvds(); break;
			case ESSPCheckP2Lvds:			Testing_CheckP2Lvds(); break;
			case ESSPCheckP0SwALanes01:	Testing_CheckTransceiver("P0 Switch A Lanes 0,1", &pRegs->GtxQsfp[8], 2); break;
			case ESSPCheckP0SwALanes23:	Testing_CheckTransceiver("P0 Switch A Lanes 2,3", &pRegs->GtxQsfp[9], 2); break;
			case ESSPCheckFiber0Lanes:		Testing_CheckTransceiver("Fiber 0", &pRegs->GtxQsfp[0], 4); break;
			case ESSPCheckFiber1Lanes:		Testing_CheckTransceiver("Fiber 1", &pRegs->GtxQsfp[1], 4); break;
			case ESSPCheckFiber2Lanes:		Testing_CheckTransceiver("Fiber 2", &pRegs->GtxQsfp[2], 4); break;
			case ESSPCheckFiber3Lanes:		Testing_CheckTransceiver("Fiber 3", &pRegs->GtxQsfp[3], 4); break;
			case ESSPCheckFiber4Lanes:		Testing_CheckTransceiver("Fiber 4", &pRegs->GtxQsfp[4], 4); break;
			case ESSPCheckFiber5Lanes:		Testing_CheckTransceiver("Fiber 5", &pRegs->GtxQsfp[5], 4); break;
			case ESSPCheckFiber6Lanes:		Testing_CheckTransceiver("Fiber 6", &pRegs->GtxQsfp[6], 4); break;
			case ESSPCheckFiber7Lanes:		Testing_CheckTransceiver("Fiber 7", &pRegs->GtxQsfp[7], 4); break;
			case ESSPCheckFiberLeds:		Testing_CheckFiberLeds(); break;
			case ESSPCheckSdramI2C:			Testing_CheckSdramI2C(); break;
			case ESSPCheckSdram:				Testing_CheckSdram(); break;
			case ESSPCheckFrontPanelNim:	Testing_CheckFrontPanelNim(); break;
			case ESSPCheckIOExpander:		Testing_CheckIOExpander(); break;
			case ESSPCheckSpiFlash:			Testing_CheckSpiFlash(); break;
			case ESSPStoreSerialNumber:	Testing_StoreSerialNumber(); break;
			case ESSPSaveTestResults:		TestingSave(); break;
			case ESSPComplete:				Testing_Complete(); break;
		}
	}

	void TestingStop()
	{
		AddTextLine("Testing quitting...");

		pM->RMWReg32(&pRegs->Gpio.Data, 0, GPIO_TESTING);

		pButtonStart->SetEnabled(kTRUE);
		pButtonContinue->SetEnabled(kFALSE);
		pButtonStop->SetEnabled(kFALSE);
		pButtonSave->SetEnabled(kTRUE);
		pButtonUserInput->SetEnabled(kFALSE);
	}

	void TestingSave()
	{
		TString str;

		str.Form("SSP_TestResult_%s.txt", strSerialNumber.Data());
		AddTextLine("********** Saving Test Results **********");
		AddTextLine(str.Format("   Saving to file: %s", str.Data()));
		pTextViewDebug->GetText()->Save(str.Data());

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void AddTextLine(const char *pText)
	{
		pTextViewDebug->AddLine(pText);
		pTextViewDebug->ScrollDown(50);
		pTextViewDebug->Update();
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_USER:
			switch(GET_SUBMSG(msg))
			{
				case SSP_TESTSTATE_MSG:
					ExecNextTestingState(parm1);
					break;
			}
			break;

		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_SSP_TESTING_START:
						pButtonStart->SetEnabled(kFALSE);
						pButtonContinue->SetEnabled(kFALSE);
						pButtonStop->SetEnabled(kTRUE);
						pButtonSave->SetEnabled(kFALSE);
						pTextViewDebug->Clear();
						SetNextTestingState(0);
						pM->RMWReg32(&pRegs->Gpio.Data, GPIO_TESTING, GPIO_TESTING);
						pM->RMWReg32(&pRegs->Gpio.Data, GPIO_TESTING, GPIO_TESTING);
						pM->RMWReg32(&pRegs->Gpio.Data, GPIO_TESTING, GPIO_TESTING);
						pM->RMWReg32(&pRegs->Gpio.Data, GPIO_TESTING, GPIO_TESTING);
						break;

					case BTN_SSP_TESTING_CONTINUE:
						pButtonContinue->SetEnabled(kFALSE);
						bPromptContinueReady = kTRUE;
						ExecNextTestingState(nextTestingState);
						break;

					case BTN_SSP_TESTING_STOP:
						TestingStop();
						break;

					case BTN_SSP_ENTERINPUT:
						pButtonUserInput->SetEnabled(kFALSE);
						strPromptInput = pTextEntryDebug->GetText();
						pTextEntryDebug->Clear();
						//AddTextLine(strPromptInput);
						bPromptInputReady = kTRUE;
						ExecNextTestingState(nextTestingState);
						break;

					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
			}
			break;
		}
		return kTRUE;
	}
private:
	Bool_t				bPromptContinueReady;
	Bool_t				bPromptInputReady;
	int					nextTestingState;
	TString				strPromptInput;
	TString				strSerialNumber;

	ModuleFrame			*pM;
	SSPTesting_SSP_regs		*pRegs;

	TGTextView			*pTextViewDebug;

	TGTextEntry			*pTextEntryDebug;

	TGTextButton		*pButtonStart;
	TGTextButton		*pButtonContinue;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonSave;
	TGTextButton		*pButtonUserInput;
};

#endif
