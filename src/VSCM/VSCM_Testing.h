#ifndef VSCM_Testing_H
#define VSCM_Testing_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "vscm.h"

#define VMECLK_FREQ							50000000
#define VSCM_SYSCLK_FREQ					125000000

#define VSCM_TESTSTATE_MSG					1

#define BTN_VSCM_TESTING_START			100
#define BTN_VSCM_TESTING_CONTINUE		101
#define BTN_VSCM_TESTING_STOP				102
#define BTN_VSCM_ENTERINPUT				104

// Testing thresholds
#define VSCM_TEST_BOARDID					0x5653434D

#define VSCM_TEST_LOOPBACK_TOGGLE_NUM	10

#define	VSCM_TEST_BOARDPOS				6

#define VSCM_TEST_LOCALOSC50_MIN			(50000000*0.9)
#define VSCM_TEST_LOCALOSC50_MAX			(50000000*1.1)

#define VSCM_TEST_LOCAL125OSC_MIN		(125000000*0.9)
#define VSCM_TEST_LOCAL125OSC_MAX		(125000000*1.1)

#define VSCM_TEST_P0250OSC_MIN			(250000000*0.9)
#define VSCM_TEST_P0250OSC_MAX			(250000000*1.1)

#define VSCM_TEST_P0SWBTRIG2_MIN			(1000*0.9)
#define VSCM_TEST_P0SWBTRIG2_MAX			(1000*1.1)

#define VSCM_PULSER_HIGH_MIN				0.5
#define VSCM_PULSER_HIGH_MAX				0.7

#define VSCM_PULSER_LOW_MIN				0.3
#define VSCM_PULSER_LOW_MAX				0.5

#define VSCM_TEST_INPUTCURRENT5V_MIN	0.8
#define VSCM_TEST_INPUTCURRENT5V_MAX	1.5

#define VSCM_TEST_INPUTCURRENT12VN_MIN	0.025
#define VSCM_TEST_INPUTCURRENT12VN_MAX	0.25

#define VSCM_TEST_INPUTCURRENT12VP_MIN	0.025
#define VSCM_TEST_INPUTCURRENT12VP_MAX	0.25

// Supported testing states
enum VSCMTestingStates
{
	EVSCMInitialize,
	EVSCMBoardId,
	EVSCMBoardPos,
	EVSCMVmeDataBits,
	EVSCMCheckSpiFlash,
	EVSCMClockLocal50,
	EVSCMClockP0,
	EVSCMClockLocal250,
	EVSCMCheckFrontPanelLvds,
	EVSCMCheckP0SwBStatus,
	EVSCMCheckP0SwBToken,
	EVSCMCheckP0SwBTrig,
	EVSCMCheckP0SwBSync,
	EVSCMCheckP0SwBTrig2,
	EVSCMCheckSram,
	EVSCMCheckHfcb1U1,
	EVSCMCheckHfcb1U2,
	EVSCMCheckHfcb1U3,
	EVSCMCheckHfcb1U4,
	EVSCMCheckHfcb2U1,
	EVSCMCheckHfcb2U2,
	EVSCMCheckHfcb2U3,
	EVSCMCheckHfcb2U4,
	EVSCMStoreSerialNumber,
	EVSCMCheckPulser1Low,
	EVSCMCheckPulser2Low,
	EVSCMCheckPulser1High,
	EVSCMCheckPulser2High,
	EVSCMCheckPulser1Cal,
	EVSCMCheckPulser2Cal,
	EVSCMInputCurrent5V,
	EVSCMInputCurrent12VN,
	EVSCMInputCurrent12VP,
	EVSCMSaveTestResults,
	EVSCMComplete
};

// Testing state sequence
int VSCMTestSequence[] = {
	EVSCMInitialize,
	EVSCMCheckSpiFlash,
	EVSCMBoardId,
	EVSCMBoardPos,
	EVSCMVmeDataBits,
	EVSCMClockLocal50,
	EVSCMClockP0,
	EVSCMClockLocal250,
	EVSCMCheckFrontPanelLvds,
	EVSCMCheckP0SwBTrig,
	EVSCMCheckP0SwBSync,
	EVSCMCheckP0SwBTrig2,
	EVSCMCheckP0SwBToken,
	EVSCMCheckP0SwBStatus,
	EVSCMCheckSram,
	EVSCMCheckPulser1Low,
	EVSCMCheckPulser1High,
	EVSCMCheckPulser1Cal,
	EVSCMCheckPulser2Low,
	EVSCMCheckPulser2High,
	EVSCMCheckPulser2Cal,
	EVSCMCheckHfcb1U1,
	EVSCMCheckHfcb1U2,
	EVSCMCheckHfcb1U3,
	EVSCMCheckHfcb1U4,
	EVSCMCheckHfcb2U1,
	EVSCMCheckHfcb2U2,
	EVSCMCheckHfcb2U3,
	EVSCMCheckHfcb2U4,
	EVSCMInputCurrent5V,
	EVSCMInputCurrent12VN,
	EVSCMInputCurrent12VP,
	EVSCMStoreSerialNumber,
	EVSCMSaveTestResults,
	EVSCMComplete
};

class VSCM_Testing	: public TGCompositeFrame
{
public:
	VSCM_Testing(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (VSCM_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonStart = new TGTextButton(pTF1, "Start", BTN_VSCM_TESTING_START), new TGLayoutHints(kLHintsCenterX));
				pButtonStart->SetWidth(200);
				pButtonStart->Associate(this);

			pTF1->AddFrame(pButtonContinue = new TGTextButton(pTF1, "Continue", BTN_VSCM_TESTING_CONTINUE), new TGLayoutHints(kLHintsCenterX));
				pButtonContinue->Associate(this);
				pButtonContinue->SetEnabled(kFALSE);

			pTF1->AddFrame(pButtonStop = new TGTextButton(pTF1, "Stop", BTN_VSCM_TESTING_STOP), new TGLayoutHints(kLHintsCenterX));
				pButtonStop->Associate(this);
				pButtonStop->SetEnabled(kFALSE);

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTF1->AddFrame(pTextViewDebug = new TGTextView(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(new TGLabel(pTF1, "User Input: "), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
			pTF1->AddFrame(pTextEntryDebug = new TGTextEntry(pTF1), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonUserInput = new TGTextButton(pTF1, "Enter Input", BTN_VSCM_ENTERINPUT));
				pButtonUserInput->Associate(this);
				pButtonUserInput->SetEnabled(kFALSE);
	}

	void SetNextTestingState(int nextState)
	{
		nextTestingState = nextState;
		bPromptInputReady = kFALSE;
		bPromptContinueReady = kFALSE;

		SendMessage(this, MK_MSG(kC_USER, (EWidgetMessageTypes)VSCM_TESTSTATE_MSG), nextTestingState, 0);
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

	double Testing_MinMaxRangeDouble(const char *measurement, const char *units, double min, double max, double val, Bool_t bInput)
	{
		TString str = strPromptInput;
		
		AddTextLine(str.Format("********** %s **********", measurement));

		if(bInput)
		{
			if(!bPromptInputReady || !str.IsFloat())
			{
				TestingPromptInput(str.Format("Enter VSCM %s(in %s): ", measurement, units));
				return 0.0;
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
			return 0.0;
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
			return 0.0;
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);

		return val;
	}

	void Testing_Initialize()
	{
		TDatime t;
		TString str;

		strSerialNumber = "none";

		AddTextLine("VSCM Testing Initialzed...");
		AddTextLine(str.Format("Test Data/Time: %s", t.AsString()));

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
		unsigned int BoardId = pM->ReadReg32(&pRegs->BoardId);
		str.Form("   BoardId(0x%08X) == 0x%08X...", VSCM_TEST_BOARDID, BoardId);
		if(BoardId == VSCM_TEST_BOARDID)
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

		str.Form("   Firmware revision = 0x%08X", pM->ReadReg32(&pRegs->FirmwareRev));
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
		unsigned int BoardPos = pM->ReadReg32(&pRegs->Geo) & 0x1F;
		str.Form("   BoardPosition(%d) == %d...", VSCM_TEST_BOARDPOS, BoardPos);
		if(BoardPos == VSCM_TEST_BOARDPOS)
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
			pM->WriteReg32(&pRegs->TriggerWindow, (1<<i));
			pM->WriteReg32(&pRegs->AD32, 0);
			result = pM->ReadReg32(&pRegs->TriggerWindow);

			str.Form("   Wrote 0x%08X, Read 0x%08X...", 1<<i, result);
			if((unsigned int)(1<<i) != result)
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

	void Testing_CheckLocal50MHzOsc()
	{
		///////////////////////////////////
		// Checking 50MHz Oscillator
		///////////////////////////////////
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		unsigned int ref = pM->ReadReg32(&pRegs->ScalerVmeClk);

		Testing_MinMaxRangeInt32("CheckLocal50MHzOsc", "", (int)VSCM_TEST_LOCALOSC50_MIN, (int)VSCM_TEST_LOCALOSC50_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP0250MHzOsc()
	{
		///////////////////////////////////
		// Checking P0 250 Oscillator
		///////////////////////////////////
		AddTextLine("********** CheckP0250MHzOsc **********");
		pM->WriteReg32(&pRegs->ClockCfg, 0x00000003);
		pM->WriteReg32(&pRegs->ClockCfg, 0x00000001);

		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000001);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000001);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->ScalerVmeClk) / VMECLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Fssr[0].ScalerRef) / scale;

		Testing_MinMaxRangeInt32("CheckP0250MHzOsc", "", (int)VSCM_TEST_P0250OSC_MIN, (int)VSCM_TEST_P0250OSC_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckLocal125MHzOsc()
	{
		///////////////////////////////////
		// Checking Local 125 Oscillator
		///////////////////////////////////
		AddTextLine("********** CheckLocal125MHzOsc **********");
		pM->WriteReg32(&pRegs->ClockCfg, 0x00000002);
		pM->WriteReg32(&pRegs->ClockCfg, 0x00000000);

		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000001);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000001);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->ScalerVmeClk) / VMECLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Fssr[0].ScalerRef) / scale;

		Testing_MinMaxRangeInt32("CheckLocal125MHzOsc", "", (int)VSCM_TEST_LOCAL125OSC_MIN, (int)VSCM_TEST_LOCAL125OSC_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP0SwBSdlink_Sync()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B Sdlink->Sync Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBSdlink_Sync **********");
		pM->WriteReg32(&pRegs->SdLink, IO_MUX_0);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		for(int i = 0; i < VSCM_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->SdLink, IO_MUX_1);
			pM->WriteReg32(&pRegs->SdLink, IO_MUX_0);
		}
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);

		result = pM->ReadReg32(&pRegs->ScalerSync);

		str.Form("   Toggled SWB Sdlink %u times...Received %u SWB Sync toggles...", VSCM_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == VSCM_TEST_LOOPBACK_TOGGLE_NUM)
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

		pM->WriteReg32(&pRegs->Trigout, IO_MUX_0);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		for(int i = 0; i < VSCM_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->Trigout, IO_MUX_1);
			pM->WriteReg32(&pRegs->Trigout, IO_MUX_0);
		}
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);

		result = pM->ReadReg32(&pRegs->ScalerTrig1);

		str.Form("   Toggled SWB TrigOut %u times...Received %u SWB Trig1 toggles...", VSCM_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == VSCM_TEST_LOOPBACK_TOGGLE_NUM)
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
		unsigned int result = 0;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B TokenOut->TokenIn Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBTokenOut_TokenIn **********");

		pM->WriteReg32(&pRegs->TokenOut, IO_MUX_0);
		pM->WriteReg32(&pRegs->FpOutput[0], IO_MUX_TOKENIN);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		for(int i = 0; i < VSCM_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->TokenOut, IO_MUX_1);
			pM->WriteReg32(&pRegs->TokenOut, IO_MUX_0);
		}
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);

		result = pM->ReadReg32(&pRegs->ScalerFpOutput[0]);

		str.Form("   Toggled SWB TokenOut %u times...Received %u SWB TokenIn toggles...", VSCM_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == VSCM_TEST_LOOPBACK_TOGGLE_NUM)
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

		pM->WriteReg32(&pRegs->SwBGpio, IO_MUX_0 | (1<<24));	// Output '0' on SW GPIO 0, Input on GPIO 1
		pM->WriteReg32(&pRegs->FpOutput[0], IO_MUX_SWB_GPIO1);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		for(int i = 0; i < VSCM_TEST_LOOPBACK_TOGGLE_NUM; i++)
		{
			pM->WriteReg32(&pRegs->SwBGpio, IO_MUX_1 | (1<<24));
			pM->WriteReg32(&pRegs->SwBGpio, IO_MUX_0 | (1<<24));
		}
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);

		result = pM->ReadReg32(&pRegs->ScalerFpOutput[0]);

		str.Form("   Toggled SWB SE1 %u times...Received %u SWB SE0 toggles...", VSCM_TEST_LOOPBACK_TOGGLE_NUM, result);

		if(result == VSCM_TEST_LOOPBACK_TOGGLE_NUM)
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

		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->ScalerVmeClk) / VMECLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->ScalerTrig2) / scale;

		Testing_MinMaxRangeInt32("CheckP0SwBTrig2", "", (int)VSCM_TEST_P0SWBTRIG2_MIN, (int)VSCM_TEST_P0SWBTRIG2_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckFrontPanelLvds()
	{
		unsigned int result, i;
		TString str;

		///////////////////////////////////
		// Checking Front Panel LVDS Loopback
		///////////////////////////////////
		AddTextLine("********** CheckFrontPanelLvds **********");

		for(i = 0; i < 4; i++)
			pM->WriteReg32(&pRegs->FpOutput[i], IO_MUX_0);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);
		for(int j = 0; j < VSCM_TEST_LOOPBACK_TOGGLE_NUM; j++)
		{
			for(i = 0; i < 4; i++)
			{
				pM->WriteReg32(&pRegs->FpOutput[i], IO_MUX_1);
				pM->WriteReg32(&pRegs->FpOutput[i], IO_MUX_0);
			}
		}
		pM->WriteReg32(&pRegs->ScalerLatch, 0x80000000);

		for(i = 0; i < 4; i++)
		{
			result = pM->ReadReg32(&pRegs->ScalerFpInput[i]);

			str.Form("   Toggled FPOutput%d %u times...Received %u FPInput%d toggles...", i, VSCM_TEST_LOOPBACK_TOGGLE_NUM, result, i);

			if(result == VSCM_TEST_LOOPBACK_TOGGLE_NUM)
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

	void Testing_CheckSram()
	{
		unsigned int result, i;
		TString str;

		///////////////////////////////////
		// Checking 18Mbit SRAM
		///////////////////////////////////
		AddTextLine("********** CheckSram **********");
		pM->WriteReg32(&pRegs->Reset, 1);
		pM->Delay(10);

		for(i = 0; i < 32; i++)
		{
			pM->WriteReg32(&pRegs->SramDbgAdr, 0x10);
			pM->WriteReg32(&pRegs->SramDbgData, (1<<i));

			pM->WriteReg32(&pRegs->SramDbgAdr, 0x20);
			pM->WriteReg32(&pRegs->SramDbgData, 0);

			pM->WriteReg32(&pRegs->SramDbgAdr, 0x10);
			result = pM->ReadReg32(&pRegs->SramDbgData);

			str.Form("   Wrote 0x%08X, Read 0x%08X...", 1<<i, result);
			if((unsigned int)(1<<i) != result)
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
			str += "PASSED";
			AddTextLine(str);
		}

		for(i = 0; i < 19; i++)
		{
			pM->WriteReg32(&pRegs->SramDbgAdr, (1<<i));
			pM->WriteReg32(&pRegs->SramDbgData, (1<<i));
		}

		for(i = 0; i < 19; i++)
		{
			pM->WriteReg32(&pRegs->SramDbgAdr, (1<<i));
			result = pM->ReadReg32(&pRegs->SramDbgData);

			str.Form("   Wrote 0x%08X, Read 0x%08X (@adr=0x%08X)...", 1<<i, result, 1<<i);
			if((unsigned int)(1<<i) != result)
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

	void FssrSetBcoClock(unsigned int bco_period)
	{
		pM->WriteReg32(&pRegs->FssrClkCfg, bco_period);
	}

	void FssrSetChipId(int hfcb, int u1, int u2, int u3, int u4)
	{
		if(hfcb == 0)
			pM->WriteReg32(&pRegs->FssrAddrH1, (u4<<24) | (u3<<16) | (u2<<8) | (u1<<0));
		else
			pM->WriteReg32(&pRegs->FssrAddrH2, (u4<<24) | (u3<<16) | (u2<<8) | (u1<<0));
	}

	void FssrReset()
	{
		pM->WriteReg32(&pRegs->FssrSerCfg, 0xF<<28);
		pM->Delay(1);
		pM->WriteReg32(&pRegs->FssrSerCfg, 0);
		pM->Delay(1);
	}

	void FssrSetControl(int i, unsigned int val)
	{
		FssrTransfer(i, FSSR_ADDR_REG_DCR, FSSR_CMD_WRITE, 8, &val);
	}

	void FssrSetActiveLines(int i, unsigned int lines)
	{
		unsigned int reg = lines & 0x3;
		FssrTransfer(i, FSSR_ADDR_REG_ALINES, FSSR_CMD_WRITE, 2, &reg);
	}

	
	void FssrRejectHits(int i, int reject)
	{
		if(reject)
			FssrTransfer(i, FSSR_ADDR_REG_REJECTHITS, FSSR_CMD_SET, 1, NULL);
		else
			FssrTransfer(i, FSSR_ADDR_REG_REJECTHITS, FSSR_CMD_RESET, 1, NULL);
	}

	void FssrSetThreshold(int id, unsigned int idx, unsigned int thr)
	{
		unsigned int reg = thr;
	
		FssrTransfer(id, FSSR_ADDR_REG_DISC_THR0+idx, FSSR_CMD_WRITE, 8, &reg);
	}

	void FssrInjectSelect(int id, unsigned int *mask)
	{
		FssrTransfer(id, FSSR_ADDR_REG_INJECT, FSSR_CMD_WRITE, 128, mask);
	}

	void FssrKillSelect(int id, unsigned int *mask)
	{
		FssrTransfer(id, FSSR_ADDR_REG_KILL, FSSR_CMD_WRITE, 128, mask);
	}

	void FssrScr(int id)
	{
		pM->WriteReg32(&pRegs->FssrSerClk, 0x100 | FSSR_SCR_BCONUM_START);
		FssrTransfer(id, FSSR_ADDR_REG_SCR, FSSR_CMD_SET, 1, NULL);
		pM->WriteReg32(&pRegs->FssrSerClk, 0);
	}

	void FssrSendData(int id, int send)
	{
		if(send)
			FssrTransfer(id, FSSR_ADDR_REG_SENDDATA, FSSR_CMD_SET, 1, NULL);
		else
			FssrTransfer(id, FSSR_ADDR_REG_SENDDATA, FSSR_CMD_RESET, 1, NULL);
	}

	void FssrTransfer(unsigned char Sel, unsigned char Addr, unsigned char Cmd, unsigned char nBits, unsigned int *pData)
	{
		unsigned int SerCfgReg = 0;
		unsigned int rsp[4];
		int i;
	
		SerCfgReg |= (Sel & 0xF)<<24;
		SerCfgReg |= (Addr & 0x1F)<<0;
		SerCfgReg |= (Cmd & 0x7)<<8;
		SerCfgReg |= (nBits & 0xFF)<<16;
		SerCfgReg |= (1<<15);

		if(pData && nBits > 0)	pM->WriteReg32(&pRegs->FssrSerData[0], pData[0]);
		if(pData && nBits > 32)	pM->WriteReg32(&pRegs->FssrSerData[1], pData[1]);
		if(pData && nBits > 64) pM->WriteReg32(&pRegs->FssrSerData[2], pData[2]);
		if(pData && nBits > 96) pM->WriteReg32(&pRegs->FssrSerData[3], pData[3]);

		if(!FssrWaitReady())
			printf("Error: FSSR_Transfer() not ready to start.\n");
		
		pM->WriteReg32(&pRegs->FssrSerCfg, SerCfgReg);
	
		if(!FssrWaitReady())
			printf("Error: FSSR_Transfer() did not end.\n");

		if(pData && (Cmd == FSSR_CMD_READ))
		{
			rsp[0] = pM->ReadReg32(&pRegs->FssrSerData[0]);
			rsp[1] = pM->ReadReg32(&pRegs->FssrSerData[1]);
			rsp[2] = pM->ReadReg32(&pRegs->FssrSerData[2]);
			rsp[3] = pM->ReadReg32(&pRegs->FssrSerData[3]);
			for(i = 0; i < nBits; i++)
			{
				if(i >= 96)
				{
					if(i == 96) pData[3] = 0;
					if(rsp[0] & (1<<(127-i)))
						pData[3] |= 1<<(i-96);
				}
				else if(i >= 64)
				{
					if(i == 64) pData[2] = 0;
					if(rsp[1] & (1<<(95-i)))
						pData[2] |= 1<<(i-64);
				}
				else if(i >= 32)
				{
					if(i == 32) pData[1] = 0;
					if(rsp[2] & (1<<(63-i)))
						pData[1] |= 1<<(i-32);
				}
				else
				{
					if(i == 0) pData[0] = 0;
					if(rsp[3] & (1<<(31-i)))
						pData[0] |= 1<<i;
				}
			}
		}
	}

	int FssrWaitReady(void)
	{
		int i;
		unsigned int reg;

		for(i = 0; i < 50; i++)
		{
			reg = pM->ReadReg32(&pRegs->FssrSerCfg);
			if(reg & (1<<14))
				return 1;
			gSystem->Sleep(1);
		}
		printf("Error: FSSRTransfer() interface timeout(0x%08X).\n", reg);
		return 0;
	}

	void Testing_CheckHfcb(int hfcb, int chipid)
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking Hfcb Interface
		///////////////////////////////////
		if(!chipid)
		{
			if(!bPromptInputReady)
			{
				str.Form("********** CheckHfcb%d,U%d **********", hfcb+1, chipid+1);
				AddTextLine(str);
				str.Form("   Connect HFCB to interface %d", hfcb+1);
				TestingPromptInput(str);
				return;
			}
		}
		else
		{
			str.Form("********** CheckHfcb%d,U%d **********", hfcb+1, chipid+1);
			AddTextLine(str);
		}

		FssrSetBcoClock(16);	// 8MHz BCO Clock
		FssrSetChipId(0, 0x9, 0xA, 0xB, 0xC);
		FssrSetChipId(1, 0x9, 0xA, 0xB, 0xC);
		FssrReset();
		
		pM->WriteReg32(&pRegs->FssrSerClk, 0);

		int id = hfcb*4+chipid;
		unsigned int KillMask[4], InjectMask[4];
	
		KillMask[0] = 0;
		KillMask[1] = 0;
		KillMask[2] = 0;
		KillMask[3] = 0;

		InjectMask[0] = 0;
		InjectMask[1] = 0;
		InjectMask[2] = 0;
		InjectMask[3] = 0;

		FssrSetControl(id, FSSR_DCR_MOD256 | 0xF);
		FssrSetActiveLines(id, FSSR_ALINES_6);
		FssrRejectHits(id, 1);
		FssrSetThreshold(id, 0, 255);
		FssrInjectSelect(id, InjectMask);
		FssrKillSelect(id, KillMask);
		FssrRejectHits(id, 0);
		FssrScr(id);
		FssrSendData(id, 1);

		////////////////////////////////////////
		// NO DATA EXPECTED
		////////////////////////////////////////
		AddTextLine("   *** FSSR DATA QUIET CHECK ***");
		pM->WriteReg32(&pRegs->ScalerLatch, 0x000000FF);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000000);
		gSystem->Sleep(100);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x000000FF);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000000);

		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerRef);
		str.Form("      Reference time    = %10u...", result);
		if((result < VSCM_SYSCLK_FREQ*0.9) || (result > VSCM_SYSCLK_FREQ*1.2))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		double scale = VSCM_SYSCLK_FREQ / (double)result;

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerStatusWord) * scale);
		str.Form("      StatusWordCount   = %10u...", result);
		if((result < 35000000*0.9) || (result > 35000000*1.1))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerEvent) * scale);
		str.Form("      EventWordCount    = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerWords) * scale);
		str.Form("      TotalWordCount    = %10u...", result);
		if((result < 35000000*0.9) || (result > 35000000*1.1))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerIdle) * scale);
		str.Form("      IdleWordCount     = %10u...", result);
		if((result < (128000000-35000000)*0.9) || (result > (128000000-35000000)*1.1))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerAqBco);
		str.Form("      AcqBcoCount       = %10u", result);
		AddTextLine(str);
		
		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerMarkErr);
		str.Form("      MarkErrors        = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerEncErr);
		str.Form("      StripEncodeErrors = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerChipIdErr);
		str.Form("      ChipIdErrors      = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerGotHit);
		str.Form("      GotHit            = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerCoreTalking);
		str.Form("      CoreTalking       = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);


		////////////////////////////////////////
		// LOTS OF DATA EXPECTED
		////////////////////////////////////////
		AddTextLine("   *** FSSR DATA BUSY CHECK ***");
		FssrSetThreshold(id, 0, 5);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x000000FF);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000000);
		gSystem->Sleep(100);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x000000FF);
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->ScalerLatch, 0x00000000);

		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerRef);
		str.Form("      Reference time    = %10u...", result);
		if((result < VSCM_SYSCLK_FREQ*0.9) || (result > VSCM_SYSCLK_FREQ*1.2))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		scale = VSCM_SYSCLK_FREQ / (double)result;

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerStatusWord) * scale);
		str.Form("      StatusWordCount   = %10u...", result);
		if((result < 35000000/32) || (result > 35000000/4))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerEvent) * scale);
		str.Form("      EventWordCount    = %10u...", result);
		if(result < 35000000*0.6)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerWords) * scale);
		str.Form("      TotalWordCount    = %10u...", result);
		if((result < 35000000*0.9) || (result > 35000000*1.1))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = (unsigned int)(pM->ReadReg32(&pRegs->Fssr[id].ScalerIdle) * scale);
		str.Form("      IdleWordCount     = %10u...", result);
		if((result < (128000000-35000000)*0.9) || (result > (128000000-35000000)*1.1))
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerAqBco);
		str.Form("      AcqBcoCount       = %10u", result);
		AddTextLine(str);
		
		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerMarkErr);
		str.Form("      MarkErrors        = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerEncErr);
		str.Form("      StripEncodeErrors = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerChipIdErr);
		str.Form("      ChipIdErrors      = %10u...", result);
		if(result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerGotHit);
		str.Form("      GotHit            = %10u...", result);
		if(!result)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		/////////////
		result = pM->ReadReg32(&pRegs->Fssr[id].ScalerCoreTalking);
		str.Form("      CoreTalking       = %10u...", result);
		if(!result)
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

	void Testing_CheckPuslerLow(int pulser)
	{
		if(pulser == 0)
		{
			pM->WriteReg32(&pRegs->DacCfg, (0<<16) | 0x80000D20);
			DacOffsetLow[0] = Testing_MinMaxRangeDouble("Pulser 1 Low", "Volts", VSCM_PULSER_LOW_MIN, VSCM_PULSER_LOW_MAX, 0, kTRUE);
		}
		else
		{
			pM->WriteReg32(&pRegs->DacCfg, (16383<<16) | 0x80000D20);
			DacOffsetLow[1] = Testing_MinMaxRangeDouble("Pulser 2 Low", "Volts", VSCM_PULSER_LOW_MIN, VSCM_PULSER_LOW_MAX, 0, kTRUE);
		}
	}

	void Testing_CheckPuslerHigh(int pulser)
	{
		if(pulser == 0)
		{
			pM->WriteReg32(&pRegs->DacCfg, (0<<16) | 0x80000D1F);
			DacOffsetHigh[0] = Testing_MinMaxRangeDouble("Pulser 1 High", "Volts", VSCM_PULSER_HIGH_MIN, VSCM_PULSER_HIGH_MAX, 0, kTRUE);
		}
		else
		{
			pM->WriteReg32(&pRegs->DacCfg, (16383<<16) | 0x80000D1F);
			DacOffsetHigh[1] = Testing_MinMaxRangeDouble("Pulser 2 High", "Volts", VSCM_PULSER_HIGH_MIN, VSCM_PULSER_HIGH_MAX, 0, kTRUE);
		}
	}

	void Testing_CheckPulserCal(int pulser)
	{
		TString str;

		///////////////////////////////////
		// Checking Pulser Gain Calibration
		///////////////////////////////////
		AddTextLine("********** CheckPulserGain **********");
		
		double counts = (0.5 - DacOffsetLow[pulser]) * 64.0 / (DacOffsetHigh[pulser] - DacOffsetLow[pulser]);
		int result = (int)(counts - 32);

		DacGainCorrection[pulser] = result;
		
		pM->WriteReg32(&pRegs->DacCfg, (0<<16) | 0x80000D00 | (result & 0x3F));

		AddTextLine(str.Format("   Pulser %d Gain Calibration Constant = %d", pulser, result));

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void SpiFlashSelect(int sel)
	{
		if(sel)
			pM->WriteReg32(&pRegs->SpiFlash, 0x0);
		else
			pM->WriteReg32(&pRegs->SpiFlash, 0x4);
	}

	unsigned char SpiFlashTransferByte(unsigned char data)
	{
		int i;
		unsigned char rsp = 0;
		for(i = 0; i < 8; i++)
		{
			pM->WriteReg32(&pRegs->SpiFlash, ((data>>7)&0x1));
			rsp = (rsp<<1) | (pM->ReadReg32(&pRegs->SpiFlash) & 0x1);
			pM->WriteReg32(&pRegs->SpiFlash, 0x2|((data>>7)&0x1));
			data<<=1;
		}
		return rsp;
	}
		
	void Testing_CheckSpiFlash()
	{
		TString str;
		unsigned int result;

		///////////////////////////////////
		// Checking Spi Flash Id
		///////////////////////////////////
		AddTextLine("********** CheckSpiFlash **********");

		SpiFlashSelect(0);
		pM->Delay(20);
		SpiFlashSelect(1);
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xFF);
		SpiFlashTransferByte(0xFF);
		SpiFlashSelect(0);

		SpiFlashSelect(1);
		SpiFlashTransferByte(0x9F);	// Read ID Cmd
		result = SpiFlashTransferByte(0xFF);
		result |= SpiFlashTransferByte(0xFF)<<8;
		result |= SpiFlashTransferByte(0xFF)<<16;
		result |= SpiFlashTransferByte(0xFF)<<24;
		SpiFlashSelect(0);

		str.Form("   Spi Flash Id = 0x%08X...", result);
		if(result != 0x001740EF)
		{
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		str += "PASSED";
		AddTextLine(str);

		//////////////////////////
		//////////////////////////
		//////////////////////////
		//////////////////////////
		printf("SPI Config Dump:\n");
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x03);	// Read Continuous
		SpiFlashTransferByte(0x7F);
		SpiFlashTransferByte(0xF0);
		SpiFlashTransferByte(0x00);

		for(int i = 0; i < 256; i++)
		{
			if(!(i % 16))
				printf("\n0x%04X: ", i);

			unsigned char val = SpiFlashTransferByte(0xFF);

			printf("%02X ", (unsigned int)val);
		}
		SpiFlashSelect(0);
		printf("\n\n");
		//////////////////////////
		//////////////////////////
		//////////////////////////
		//////////////////////////
		
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_StoreSerialNumber()
	{
		TString str = strPromptInput;
		int i;
		unsigned char buf[256];

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

		SpiFlashSelect(1);
		SpiFlashTransferByte(0x06);	// Write enable
		SpiFlashSelect(0);
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x20);	// Erase last chip sector
		SpiFlashTransferByte(0x7F);
		SpiFlashTransferByte(0xF0);
		SpiFlashTransferByte(0x00);
		SpiFlashSelect(0);
		pM->Delay(500);	// 400ms Max sector erase time

		SpiFlashSelect(1);
		SpiFlashTransferByte(0x06);	// Write enable
		SpiFlashSelect(0);
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x02);	// Page program
		SpiFlashTransferByte(0x7F);
		SpiFlashTransferByte(0xF0);
		SpiFlashTransferByte(0x00);
		for(i = 0; i < 256; i++)
		{
			if(i < str.Length())
				buf[i] = str[i];
			else if(i == str.Length())
				buf[i] = 0x00;
			else if(i == 128)
			{
				int val = (DacGainCorrection[0] + DacGainCorrection[1]) / 2;
				buf[i] = val & 0x3F;
			}
			else
				buf[i] = 0xFF;
		}
		for(i = 0; i < 256; i++)
			SpiFlashTransferByte(buf[i]);
		SpiFlashSelect(0);
		pM->Delay(10);	// 3ms Max erase+program time

		str.Form("   Verifying...");
		SpiFlashSelect(1);
		SpiFlashTransferByte(0x03);	// Read Continuous
		SpiFlashTransferByte(0x7F);
		SpiFlashTransferByte(0xF0);
		SpiFlashTransferByte(0x00);

		for(i = 0; i < 256; i++)
		{
			unsigned char val = SpiFlashTransferByte(0xFF);
			if(val != buf[i])
			{
				SpiFlashSelect(0);
				AddTextLine(str.Format("Wrote 0x%02X, Read 0x%02X[@offset %d]...FAILED", (unsigned int)buf[i], (unsigned int)val, i));
				TestingStop();
				return;
			}
		}
		SpiFlashSelect(0);
		str += "PASSED";
		AddTextLine(str);
		
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void Testing_Complete()
	{
		AddTextLine("VSCM Testing Complete. Unit PASSED");
		TestingStop();
	}

	void ExecNextTestingState(int curState)
	{
		if(!pButtonStop->IsEnabled())
			return;

		switch(VSCMTestSequence[curState])
		{
			case EVSCMInitialize:			Testing_Initialize(); break;
			case EVSCMBoardId:				Testing_CheckBoardId(); break;
			case EVSCMBoardPos:				Testing_CheckBoardPos(); break;
			case EVSCMVmeDataBits:			Testing_CheckVmeDataBits(); break;
			case EVSCMClockLocal50:			Testing_CheckLocal50MHzOsc(); break;
			case EVSCMClockP0:				Testing_CheckP0250MHzOsc(); break;
			case EVSCMClockLocal250:		Testing_CheckLocal125MHzOsc(); break;
			case EVSCMCheckP0SwBStatus:		Testing_CheckP0SwBStatusIO(); break;
			case EVSCMCheckP0SwBToken:		Testing_CheckP0SwBTokenOut_TokenIn(); break;
			case EVSCMCheckP0SwBTrig:		Testing_CheckP0SwBTrigOut_Trig1(); break;
			case EVSCMCheckP0SwBSync:		Testing_CheckP0SwBSdlink_Sync(); break;
			case EVSCMCheckP0SwBTrig2:		Testing_CheckP0SwBTrig2(); break;
			case EVSCMCheckFrontPanelLvds:	Testing_CheckFrontPanelLvds(); break;
			case EVSCMCheckSram:			Testing_CheckSram(); break;
			case EVSCMSaveTestResults:		TestingSave(); break;
			case EVSCMCheckHfcb1U1:			Testing_CheckHfcb(0,0); break;
			case EVSCMCheckHfcb1U2:			Testing_CheckHfcb(0,1); break;
			case EVSCMCheckHfcb1U3:			Testing_CheckHfcb(0,2); break;
			case EVSCMCheckHfcb1U4:			Testing_CheckHfcb(0,3); break;
			case EVSCMCheckHfcb2U1:			Testing_CheckHfcb(1,0); break;
			case EVSCMCheckHfcb2U2:			Testing_CheckHfcb(1,1); break;
			case EVSCMCheckHfcb2U3:			Testing_CheckHfcb(1,2); break;
			case EVSCMCheckHfcb2U4:			Testing_CheckHfcb(1,3); break;
			case EVSCMCheckPulser1Low:		Testing_CheckPuslerLow(0); break;
			case EVSCMCheckPulser2Low:		Testing_CheckPuslerLow(1); break;
			case EVSCMCheckPulser1High:		Testing_CheckPuslerHigh(0); break;
			case EVSCMCheckPulser2High:		Testing_CheckPuslerHigh(1); break;
			case EVSCMCheckPulser1Cal:		Testing_CheckPulserCal(0); break;
			case EVSCMCheckPulser2Cal:		Testing_CheckPulserCal(1); break;
			case EVSCMCheckSpiFlash:		Testing_CheckSpiFlash(); break;
			case EVSCMStoreSerialNumber:	Testing_StoreSerialNumber(); break;
			case EVSCMInputCurrent5V:		Testing_MinMaxRangeDouble("+5V Input Current", "Amps", VSCM_TEST_INPUTCURRENT5V_MIN, VSCM_TEST_INPUTCURRENT5V_MAX, 0, kTRUE); break;
			case EVSCMInputCurrent12VN:		Testing_MinMaxRangeDouble("-12V Input Current", "Amps", VSCM_TEST_INPUTCURRENT12VN_MIN, VSCM_TEST_INPUTCURRENT12VN_MAX, 0, kTRUE); break;
			case EVSCMInputCurrent12VP:		Testing_MinMaxRangeDouble("+12V Input Current", "Amps", VSCM_TEST_INPUTCURRENT12VP_MIN, VSCM_TEST_INPUTCURRENT12VP_MAX, 0, kTRUE); break;
			case EVSCMComplete:				Testing_Complete(); break;
		}
	}

	void TestingStop()
	{
		AddTextLine("Testing quitting...");

		pButtonStart->SetEnabled(kTRUE);
		pButtonContinue->SetEnabled(kFALSE);
		pButtonStop->SetEnabled(kFALSE);
		pButtonUserInput->SetEnabled(kFALSE);
	}

	void TestingSave()
	{
		TString str;

		str.Form("VSCM_TestResult_%s.txt", strSerialNumber.Data());
		AddTextLine("********** Saving Test Results **********");
		AddTextLine(str.Format("   Saving to file: %s", str.Data()));
		pTextViewDebug->GetText()->Save(str.Data());

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void AddTextLine(const char *pText)
	{
		pTextViewDebug->AddLine(pText);
		pTextViewDebug->ScrollUp(200);//->ScrollDown(50);
		pTextViewDebug->Update();
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_USER:
			switch(GET_SUBMSG(msg))
			{
				case VSCM_TESTSTATE_MSG:
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
					case BTN_VSCM_TESTING_START:
						pButtonStart->SetEnabled(kFALSE);
						pButtonContinue->SetEnabled(kFALSE);
						pButtonStop->SetEnabled(kTRUE);
						pTextViewDebug->Clear();
						SetNextTestingState(0);
						break;

					case BTN_VSCM_TESTING_CONTINUE:
						pButtonContinue->SetEnabled(kFALSE);
						bPromptContinueReady = kTRUE;
						ExecNextTestingState(nextTestingState);
						break;

					case BTN_VSCM_TESTING_STOP:
						TestingStop();
						break;

					case BTN_VSCM_ENTERINPUT:
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

	double				DacOffsetLow[2];
	double				DacOffsetHigh[2];
	int					DacGainCorrection[2];

	ModuleFrame			*pM;
	VSCM_regs			*pRegs;

	TGTextView			*pTextViewDebug;

	TGTextEntry			*pTextEntryDebug;

	TGTextButton		*pButtonStart;
	TGTextButton		*pButtonContinue;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonUserInput;	
};

#endif
