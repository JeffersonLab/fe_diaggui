#ifndef SSP_Testing_H
#define SSP_Testing_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include"ssp.h"

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

#define SSP_TEST_LOCAL250OSC_MIN		(250000000*0.999)
#define SSP_TEST_LOCAL250OSC_MAX		(250000000*1.001)

#define SSP_TEST_P0250OSC_MIN			(250000000*0.999)
#define SSP_TEST_P0250OSC_MAX			(250000000*1.001)

#define SSP_TEST_P2OSC_MIN				(240000000*0.999)
#define SSP_TEST_P2OSC_MAX				(240000000*1.001)

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
		ESSPClockP2,
		ESSPClockLocal250,
		ESSPCheckSdram,
		ESSPCheckSdramI2C,
/*		ESSPCheckIOExpander,*/
		ESSPCheckP0SwAStatus,
		ESSPCheckP0SwBStatus,
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
		ESSPCheckP0SwBToken,
		ESSPCheckP0SwBTrig,
		ESSPCheckP0SwBSync,
		ESSPCheckP0SwBTrig2,
		ESSPCheckFrontPanelNim,
		ESSPCheckFiberLeds,
		ESSPInputCurrent5V,
		ESSPInputCurrent12VN,
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
		pRegs = (SSP_regs *)pM->BaseAddr;

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
		pM->pVMEClient->Delay(500);
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
		pM->pVMEClient->Delay(20);
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

		SpiFlashSelect(1);
		SpiFlashTransferByte(0x9F);	// Read ID Cmd
		result = SpiFlashTransferByte(0xFF);
		result |= SpiFlashTransferByte(0xFF)<<8;
		result |= SpiFlashTransferByte(0xFF)<<16;
		result |= SpiFlashTransferByte(0xFF)<<24;
		SpiFlashSelect(0);

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

		pM->pVMEClient->Delay(50);	// 40ms Max erase+program time

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

		pM->pVMEClient->Delay(1);	// 400us Max compare time

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
		pM->pVMEClient->Delay(500);
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
		pM->pVMEClient->Delay(1000);
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
		pM->pVMEClient->Delay(1000);
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

	void Testing_CheckTransceiver(const char *measurement, GtxQsfp_regs *pGtx, int nlanes)
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
		pM->pVMEClient->Delay(500);
		pM->RMWReg32(&pGtx->Ctrl, 0x80000000, 0x80000000);
		pM->pVMEClient->Delay(500);

		// Latch error counter after 1s
		pM->RMWReg32(&pGtx->Ctrl, 0x80000000, 0x80000000);
		pM->pVMEClient->Delay(1000);
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
	SSP_regs				*pRegs;

	TGTextView			*pTextViewDebug;

	TGTextEntry			*pTextEntryDebug;

	TGTextButton		*pButtonStart;
	TGTextButton		*pButtonContinue;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonSave;
	TGTextButton		*pButtonUserInput;
};

#endif
