#ifndef DCRB_Testing_H
#define DCRB_Testing_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRB.h"

#define VMECLK_FREQ							50000000
#define DCRB_SYSCLK_FREQ					125000000

#define DCRB_TESTSTATE_MSG					1

#define BTN_DCRB_TESTING_START			100
#define BTN_DCRB_TESTING_CONTINUE		101
#define BTN_DCRB_TESTING_STOP				102
#define BTN_DCRB_ENTERINPUT				104

// Testing thresholds
#define DCRB_TEST_BOARDID					0x44438242

#define DCRB_TEST_BOARDPOS					4

#define DCRB_FE_PULSER_COUNT				1000000
#define DCRB_FE_PULSER_FREQ				1000000
#define DCRB_FE_PULSER_FREQ_MIN			DCRB_FE_PULSER_COUNT
#define DCRB_FE_PULSER_FREQ_MAX			DCRB_FE_PULSER_COUNT

#define DCRB_TEST_TRIG2_MIN				(1000*0.9)
#define DCRB_TEST_TRIG2_MAX				(1000*1.1)

#define DCRB_TEST_LOCALOSC50_MIN			(50000000*0.9)
#define DCRB_TEST_LOCALOSC50_MAX			(50000000*1.1)

#define DCRB_TEST_LOCAL125OSC_MIN		(125000000*0.9)
#define DCRB_TEST_LOCAL125OSC_MAX		(125000000*1.1)

#define DCRB_TEST_P0125OSC_MIN			(250000000*0.9)
#define DCRB_TEST_P0125OSC_MAX			(250000000*1.1)

#define DCRB_TEST_P0SWBTRIG2_MIN			(1000*0.9)
#define DCRB_TEST_P0SWBTRIG2_MAX			(1000*1.1)

#define DCRB_PULSER_HIGH_MIN				0.5
#define DCRB_PULSER_HIGH_MAX				0.7

#define DCRB_PULSER_LOW_MIN				0.3
#define DCRB_PULSER_LOW_MAX				0.5

#define DCRB_TEST_INPUTCURRENT5V_MIN	2.0
#define DCRB_TEST_INPUTCURRENT5V_MAX	5.0

#define DCRB_TEST_INPUTCURRENT12VN_MIN	0.35
#define DCRB_TEST_INPUTCURRENT12VN_MAX	0.65

#define DCRB_TEST_INPUTCURRENT12VP_MIN	0.35
#define DCRB_TEST_INPUTCURRENT12VP_MAX	0.65

// Supported testing states
enum DCRBTestingStates
{
	EDCRBInitialize,
	EDCRBBoardId,
	EDCRBBoardPos,
	EDCRBVmeDataBits,
	EDCRBCheckSpiFlash,
	EDCRBClockLocal50,
	EDCRBClockP0,
	EDCRBClockLocal125,
	EDCRBCheckP0SwBTrig2,
	EDCRBCheckP0SwBSync,
	EDCRBCheckP0SwBTrig,
	EDCRBCheckP0SwBToken,
	EDCRBCheckP0SwAGpio0_SwAGpio1,
	EDCRBCheckP0SwBGpio0_SwAGpio1,
	EDCRBCheckSwASerial,
	EDCRBCheckSram,
	EDCRBFEPulser_AboveThr,
	EDCRBDCPulser_AboveThr,
	EDCRBStoreSerialNumber,
	EDCRBInputCurrent5V,
	EDCRBInputCurrent12VN,
	EDCRBInputCurrent12VP,
	EDCRBSaveTestResults,
	EDCRBComplete
};

// Testing state sequence
int DCRBTestSequence[] = {
	EDCRBInitialize,
	EDCRBCheckSpiFlash,
	EDCRBBoardId,
	EDCRBBoardPos,
	EDCRBVmeDataBits,
	EDCRBClockLocal50,
	EDCRBClockLocal125,
	EDCRBFEPulser_AboveThr,
	EDCRBDCPulser_AboveThr,
	EDCRBCheckSram,
	EDCRBClockP0,
	EDCRBCheckSwASerial,
	EDCRBCheckP0SwBTrig2,
	EDCRBCheckP0SwBSync,
	EDCRBCheckP0SwBTrig,
	EDCRBCheckP0SwBToken,
	EDCRBCheckP0SwAGpio0_SwAGpio1,
	EDCRBCheckP0SwBGpio0_SwAGpio1,
	EDCRBInputCurrent5V,
	EDCRBInputCurrent12VN,
	EDCRBInputCurrent12VP,
	EDCRBStoreSerialNumber,
	EDCRBSaveTestResults,
	EDCRBComplete
};

class DCRB_Testing	: public TGCompositeFrame
{
public:
	DCRB_Testing(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (DCRB_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonStart = new TGTextButton(pTF1, "Start", BTN_DCRB_TESTING_START), new TGLayoutHints(kLHintsCenterX));
				pButtonStart->SetWidth(200);
				pButtonStart->Associate(this);

			pTF1->AddFrame(pButtonContinue = new TGTextButton(pTF1, "Continue", BTN_DCRB_TESTING_CONTINUE), new TGLayoutHints(kLHintsCenterX));
				pButtonContinue->Associate(this);
				pButtonContinue->SetEnabled(kFALSE);

			pTF1->AddFrame(pButtonStop = new TGTextButton(pTF1, "Stop", BTN_DCRB_TESTING_STOP), new TGLayoutHints(kLHintsCenterX));
				pButtonStop->Associate(this);
				pButtonStop->SetEnabled(kFALSE);

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTF1->AddFrame(pTextViewDebug = new TGTextView(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(new TGLabel(pTF1, "User Input: "), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
			pTF1->AddFrame(pTextEntryDebug = new TGTextEntry(pTF1), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonUserInput = new TGTextButton(pTF1, "Enter Input", BTN_DCRB_ENTERINPUT));
				pButtonUserInput->Associate(this);
				pButtonUserInput->SetEnabled(kFALSE);
	}

	void SetNextTestingState(int nextState)
	{
		nextTestingState = nextState;
		bPromptInputReady = kFALSE;
		bPromptContinueReady = kFALSE;

		SendMessage(this, MK_MSG(kC_USER, (EWidgetMessageTypes)DCRB_TESTSTATE_MSG), nextTestingState, 0);
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
				TestingPromptInput(str.Format("Enter DCRB %s(in %s): ", measurement, units));
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
				TestingPromptInput(str.Format("Enter DCRB %s(in %s): ", measurement, units));
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

		AddTextLine("DCRB Testing Initialzed...");
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
		unsigned int BoardId = pM->ReadReg32(&pRegs->Cfg.BoardId);
		str.Form("   BoardId(0x%08X) == 0x%08X...", DCRB_TEST_BOARDID, BoardId);
		if(BoardId == DCRB_TEST_BOARDID)
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

		str.Form("   Firmware revision = 0x%08X", pM->ReadReg32(&pRegs->Cfg.FirmwareRev) & 0xFFFF);
		AddTextLine(str);

		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x80000000);
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x00000000);
		pM->Delay(10);
		pM->WriteReg32(&pRegs->Cfg.Reset, 1);
		pM->Delay(10);
		pM->WriteReg32(&pRegs->Cfg.Reset, 0);
		pM->Delay(10);
		
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
		unsigned int BoardPos = (pM->ReadReg32(&pRegs->Cfg.FirmwareRev)>>24) & 0x1F;
		str.Form("   BoardPosition(%d) == %d...", DCRB_TEST_BOARDPOS, BoardPos);
		if(BoardPos == DCRB_TEST_BOARDPOS)
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
			pM->WriteReg32(&pRegs->EB.Adr32M, (1<<i));
			pM->WriteReg32(&pRegs->EB.ReadoutCfg, 0);
			result = pM->ReadReg32(&pRegs->EB.Adr32M);

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
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		unsigned int ref = pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SYSCLK50]);

		Testing_MinMaxRangeInt32("CheckLocal50MHzOsc", "", (int)DCRB_TEST_LOCALOSC50_MIN, (int)DCRB_TEST_LOCALOSC50_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP0SwB125MHzOsc()
	{
		///////////////////////////////////
		// Checking P0 SwB 125 Oscillator
		///////////////////////////////////
		AddTextLine("********** CheckP0SwB125MHzOsc **********");
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0xC0000000);
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x40000000);

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SYSCLK50]) / VMECLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_GCLK125]) / scale;

		Testing_MinMaxRangeInt32("CheckP0SwB125MHzOsc", "", (int)DCRB_TEST_LOCAL125OSC_MIN, (int)DCRB_TEST_LOCAL125OSC_MAX, (int)ref, kFALSE);
	}
	
	void Testing_CheckLocal125MHzOsc()
	{
		///////////////////////////////////
		// Checking Local 125 Oscillator
		///////////////////////////////////
		AddTextLine("********** CheckLocal125MHzOsc **********");
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x80000000);
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x00000000);

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SYSCLK50]) / VMECLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_GCLK125]) / scale;

		Testing_MinMaxRangeInt32("CheckLocal125MHzOsc", "", (int)DCRB_TEST_LOCAL125OSC_MIN, (int)DCRB_TEST_LOCAL125OSC_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP0SwBTrig2()
	{
		///////////////////////////////////
		// Checking P0 Switch B Trig2
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBTrig2 **********");
		AddTextLine("   Verify: Connect P0 Trig2 1kHz LVDS clock to SWB FP.");

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		double ref = 0.0;
		double scale = (double)pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SYSCLK50]) / VMECLK_FREQ;
		if(scale != 0.0)
			ref = (double)pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_TRIG2]) / scale;

		Testing_MinMaxRangeInt32("CheckP0SwBTrig2", "", (int)DCRB_TEST_TRIG2_MIN, (int)DCRB_TEST_TRIG2_MAX, (int)ref, kFALSE);
	}

	void Testing_CheckP0SwBSdlink_Sync()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B Sdlink->Sync Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBSdlink_Sync **********");
		pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_SDLINK], DCRB_SD_MUX_PULSER);
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, 10);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, 5);
		pM->WriteReg32(&pRegs->Sd.PulserNPulses, DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);	// allow to finish so pulser can be reset
		
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		pM->WriteReg32(&pRegs->Sd.PulserStart, 0);
		pM->Delay(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		
		int ref = pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SYNC]);
		
		Testing_MinMaxRangeInt32("CheckP0SwBSdlink_Sync", "", DCRB_FE_PULSER_COUNT, DCRB_FE_PULSER_COUNT, ref, kFALSE);
	}

	void Testing_CheckP0SwBTrigOut_Trig1()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B TrigOut->Trig1 Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBTrigOut_Trig1 **********");

		pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_TRIGOUT], DCRB_SD_MUX_PULSER);
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, 10);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, 5);
		pM->WriteReg32(&pRegs->Sd.PulserNPulses, DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);	// allow to finish so pulser can be reset
		
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		pM->WriteReg32(&pRegs->Sd.PulserStart, 0);
		pM->Delay(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		
		int ref = pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_TRIG1]);

		Testing_MinMaxRangeInt32("CheckP0SwBTrigOut_Trig1", "", DCRB_FE_PULSER_COUNT, DCRB_FE_PULSER_COUNT, ref, kFALSE);
	}

	void Testing_CheckP0SwBTokenOut_TokenIn()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B TokenOut->TokenIn Loopback
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBTokenOut_TokenIn **********");

		pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_TOKENOUT], DCRB_SD_MUX_PULSER);
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, 10);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, 5);
		pM->WriteReg32(&pRegs->Sd.PulserNPulses, DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);	// allow to finish so pulser can be reset
		
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		pM->WriteReg32(&pRegs->Sd.PulserStart, 0);
		pM->Delay(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		
		int ref = pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_TOKENIN]);

		Testing_MinMaxRangeInt32("CheckP0SwBTokenOut_TokenIn", "", DCRB_FE_PULSER_COUNT, DCRB_FE_PULSER_COUNT, ref, kFALSE);
	}
	
	void Testing_CheckP0SwAGpio0_SwAGpio1()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch A Gpio0->Gpio0
		///////////////////////////////////
		AddTextLine("********** CheckP0SwAGpio0_Gpio1 **********");

		pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_SWA_GPIO0], DCRB_SD_MUX_PULSER);
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, 10);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, 5);
		pM->WriteReg32(&pRegs->Sd.PulserNPulses, DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);	// allow to finish so pulser can be reset
		
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		pM->WriteReg32(&pRegs->Sd.PulserStart, 0);
		pM->Delay(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		
		int ref = pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SWA_GPIO1]);

		Testing_MinMaxRangeInt32("CheckP0SwAGpio0_Gpio1", "", DCRB_FE_PULSER_COUNT, DCRB_FE_PULSER_COUNT, ref, kFALSE);
	}

	void Testing_CheckP0SwBGpio0_SwAGpio1()
	{
		unsigned int result;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B Gpio0->Gpio0
		///////////////////////////////////
		AddTextLine("********** CheckP0SwBGpio0_Gpio1 **********");

		pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_SWB_GPIO0], DCRB_SD_MUX_PULSER);
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, 10);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, 5);
		pM->WriteReg32(&pRegs->Sd.PulserNPulses, DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);	// allow to finish so pulser can be reset
		
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		pM->WriteReg32(&pRegs->Sd.PulserStart, 0);
		pM->Delay(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		
		int ref = pM->ReadReg32(&pRegs->Sd.Scalers[DCRB_SCALER_SWB_GPIO1]);

		Testing_MinMaxRangeInt32("CheckP0SwBGpio0_Gpio1", "", DCRB_FE_PULSER_COUNT, DCRB_FE_PULSER_COUNT, ref, kFALSE);
	}

	void Testing_CheckSwASerial()
	{
		unsigned int status0, status1;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch A Serial loopback
		///////////////////////////////////
		AddTextLine("********** CheckSwASerial **********");

		pM->WriteReg32(&pRegs->Ser[0].Ctrl, 0x401);
		pM->WriteReg32(&pRegs->Ser[1].Ctrl, 0x401);
		pM->WriteReg32(&pRegs->Ser[0].Ctrl, 0x400);
		pM->WriteReg32(&pRegs->Ser[1].Ctrl, 0x400);
		pM->Delay(100);
		pM->WriteReg32(&pRegs->Ser[0].Ctrl, 0x800);
		pM->WriteReg32(&pRegs->Ser[1].Ctrl, 0x800);
		pM->Delay(100);
		
		status0 = pM->ReadReg32(&pRegs->Ser[0].Status);
		status1 = pM->ReadReg32(&pRegs->Ser[1].Status);
		
		str.Form("   Channel 0 status = 0x%08X...", status0);
		if((status0 & 0x3033) == 0x3030)
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

		str.Form("   Channel 1 status = 0x%08X...", status1);
		if((status1 & 0x3033) == 0x3030)
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

	void Testing_CheckSram()
	{
		int i;
		Long64_t val, result;
		TString str;

		///////////////////////////////////
		// Checking 18Mbit SRAM
		///////////////////////////////////
		AddTextLine("********** CheckSram **********");
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x80000000);
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x00000000);
		pM->Delay(10);
		pM->WriteReg32(&pRegs->Cfg.Reset, 1);
		pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_TRIG], 0);
		pM->Delay(10);
		pM->WriteReg32(&pRegs->Cfg.Reset, 0);
		pM->Delay(10);

		val = 1;
		for(i = 0; i < 36; i++)
		{
			pM->WriteReg32(&pRegs->EB.SramAddr, 0x10);
			pM->WriteReg32(&pRegs->EB.SramDinL, (int)val);
			pM->WriteReg32(&pRegs->EB.SramDinH, (int)(val>>32));
			pM->WriteReg32(&pRegs->EB.SramCtrl, 0x1);	// write

			pM->WriteReg32(&pRegs->EB.SramAddr, 0x20);
			pM->WriteReg32(&pRegs->EB.SramDinL, 0);
			pM->WriteReg32(&pRegs->EB.SramDinH, 0);
			pM->WriteReg32(&pRegs->EB.SramCtrl, 0x1);	// write

			pM->WriteReg32(&pRegs->EB.SramAddr, 0x10);
			pM->WriteReg32(&pRegs->EB.SramCtrl, 0x2);	// read
			result = (Long64_t)pM->ReadReg32(&pRegs->EB.SramDoutL);
			result |= ((Long64_t)pM->ReadReg32(&pRegs->EB.SramDoutH))<<32;

			str.Form("   Wrote 0x%09llX, Read 0x%09llX...", val, result);
			if(val != result)
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
			else
			{
				str += "PASSED";
				AddTextLine(str);
			}
			val<<=1;
		}

		val = 1;
		for(i = 0; i < 19; i++)
		{
			pM->WriteReg32(&pRegs->EB.SramAddr, (int)val);
			pM->WriteReg32(&pRegs->EB.SramDinL, (int)val);
			pM->WriteReg32(&pRegs->EB.SramDinH, 0);
			pM->WriteReg32(&pRegs->EB.SramCtrl, 0x1);	// write
			val<<=1;
		}

		val = 1;
		for(i = 0; i < 19; i++)
		{
			pM->WriteReg32(&pRegs->EB.SramAddr, (int)val);
			pM->WriteReg32(&pRegs->EB.SramCtrl, 0x2);	// read
			result = (Long64_t)pM->ReadReg32(&pRegs->EB.SramDoutL);
			result |= ((Long64_t)pM->ReadReg32(&pRegs->EB.SramDoutH))<<32;

			str.Form("   Wrote 0x%09llX, Read 0x%08llX (@adr=0x%09llX)...", val, result, val);
			if(val != result)
			{
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
			else
			{
				str += "PASSED";
				AddTextLine(str);
			}
			val<<=1;
		}
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}
	
	void StartPulser()
	{
		pM->WriteReg32(&pRegs->Sd.PulserStart, 0);
	}

	void SetupPulser(int grp_mask, double offset_mv, double low_mv, double high_mv, int width, double period, int count)
	{
		printf("mask=0x%02X,offset=%d,low=%d,high=%d,width=%d,period=%d\n", grp_mask, (int)offset_mv, (int)low_mv, (int)high_mv, width, (int)period);
		pM->WriteReg32(&pRegs->Cfg.DacLow, low_mv+2048.0);
		pM->WriteReg32(&pRegs->Cfg.DacHigh, high_mv+2048.0);
		pM->WriteReg32(&pRegs->Cfg.DacOffset, offset_mv+2048.0);

		if(count < 0)
			pM->WriteReg32(&pRegs->Sd.PulserNPulses, 0xFFFFFFFF);
		else
		{
			pM->WriteReg32(&pRegs->Sd.PulserPeriod, 1);
			pM->WriteReg32(&pRegs->Sd.PulserNPulses, 0);
			pM->WriteReg32(&pRegs->Sd.PulserNPulses, count);
		}

		int per = (int)(period*125000000.0);
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, per);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, per-width);

		if(grp_mask & 0x1)	pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_DCE0], 18);
		else						pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_DCE0], 0);
			
		if(grp_mask & 0x2)	pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_DCE1], 18);
		else						pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_DCE1], 0);

		if(grp_mask & 0x4)	pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_DCE2], 18);
		else						pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_DCE2], 0);

		if(grp_mask & 0x8)	pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_FCE0], 18);
		else						pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_FCE0], 0);
			
		if(grp_mask & 0x10)	pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_FCE1], 18);
		else						pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_FCE1], 0);

		if(grp_mask & 0x20)	pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_FCE2], 18);
		else						pM->WriteReg32(&pRegs->Sd.SrcSel[DCRB_OUTPUT_FCE2], 0);
	}

	void SetThreshold(double mv)
	{
		int dac;
		mv = (mv * 8.06) + 2048.0;
		
		if(mv < 0.0) dac = 0;
		else if(mv > 4095.0) dac = 4095;
		else dac = (int)mv;
		
		pM->WriteReg32(&pRegs->Cfg.DacThreshold, dac);
	}

	void Testing_DCPulser_AboveThr()
	{
		unsigned int result, group;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B SDA/SCL Loopback
		///////////////////////////////////
		AddTextLine("********** DCPulser_AboveThreshold **********");

		SetThreshold(200);

		SetupPulser(0x07, 2000.0, 1000.0, 1010.0, 2, 1.0/((double)DCRB_FE_PULSER_FREQ), DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);
	
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		StartPulser();
		pM->Delay(2000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
	
		str.Form("   DC pulser counts sent = %u", DCRB_FE_PULSER_COUNT);
		AddTextLine(str);

		for(int i = 0; i < 96; i++)
		{
			unsigned int cnt = pM->ReadReg32(&pRegs->Tdc[i/16].Scalers[i%16]);
		
			str.Form("   Channel %d count = count = %u...", i, cnt);
		
			if(cnt == DCRB_FE_PULSER_COUNT)
			{
				str += "PASSED";
				AddTextLine(str);
			}
			else
			{
				SetupPulser(0x07, 2000.0, 1000.0, 1010.0, 2, 1.0/((double)DCRB_FE_PULSER_FREQ), 0xFFFFFFFF);
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}
	
	void Testing_FEPulser_AboveThr()
	{
		unsigned int result, group;
		TString str;

		///////////////////////////////////
		// Checking P0 Switch B SDA/SCL Loopback
		///////////////////////////////////
		AddTextLine("********** FEPulser_AboveThreshold **********");

		SetThreshold(-50);

		SetupPulser(0x38, 2000.0, 1000.0, 1050.0, 2, 1.0/((double)DCRB_FE_PULSER_FREQ), DCRB_FE_PULSER_COUNT);
		pM->Delay(1000);
	
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000000);	// clear & enable
		StartPulser();
		pM->Delay(2000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x00000001);	// disable
	
		str.Form("   FE pulser counts sent = %u", DCRB_FE_PULSER_COUNT);
		AddTextLine(str);

		for(int i = 0; i < 96; i++)
		{
			unsigned int cnt = pM->ReadReg32(&pRegs->Tdc[i/16].Scalers[i%16]);
		
			str.Form("   Channel %d count = count = %u...", i, cnt);
		
			if(cnt == DCRB_FE_PULSER_COUNT)
			{
				str += "PASSED";
				AddTextLine(str);
			}
			else
			{
				SetupPulser(0x38, 2000.0, 1000.0, 1050.0, 2, 1.0/((double)DCRB_FE_PULSER_FREQ), 0xFFFFFFFF);
				str += "FAILED";
				AddTextLine(str);
				TestingStop();
				return;
			}
		}

		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void SpiFlashSelect(int sel)
	{
		if(sel)
			pM->WriteReg32(&pRegs->Cfg.SpiCtrl, 0x200);
		else
			pM->WriteReg32(&pRegs->Cfg.SpiCtrl, 0x100);
	}

	unsigned char SpiFlashTransferByte(unsigned char data)
	{
		int i;
		int rsp = 0;
		
		pM->WriteReg32(&pRegs->Cfg.SpiCtrl, data | 0x400);
		for(i = 0; i < 8; i++)
		{
			rsp = pM->ReadReg32(&pRegs->Cfg.SpiStatus);
			
			if(rsp & 0x800)
				break;
		}
		return rsp & 0xFF;
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
		if(result != 0x10172020)
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
			TestingPromptInput("   Enter Serial Number(Format: CEM-XXXX) ");
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
		AddTextLine("DCRB Testing Complete. Unit PASSED");
		TestingStop();
	}

	void ExecNextTestingState(int curState)
	{
		if(!pButtonStop->IsEnabled())
			return;

		switch(DCRBTestSequence[curState])
		{
			case EDCRBInitialize:						Testing_Initialize(); break;
			case EDCRBBoardId:							Testing_CheckBoardId(); break;
			case EDCRBBoardPos:							Testing_CheckBoardPos(); break;
			case EDCRBVmeDataBits:						Testing_CheckVmeDataBits(); break;
			case EDCRBClockLocal50:						Testing_CheckLocal50MHzOsc(); break;
			case EDCRBClockLocal125:					Testing_CheckLocal125MHzOsc(); break;
			case EDCRBClockP0:							Testing_CheckP0SwB125MHzOsc(); break;
			case EDCRBCheckP0SwBTrig2:					Testing_CheckP0SwBTrig2(); break;
			case EDCRBCheckP0SwBSync:					Testing_CheckP0SwBSdlink_Sync(); break;
			case EDCRBCheckP0SwBTrig:					Testing_CheckP0SwBTrigOut_Trig1(); break;
			case EDCRBCheckP0SwBToken:					Testing_CheckP0SwBTokenOut_TokenIn(); break;
			case EDCRBCheckP0SwAGpio0_SwAGpio1:		Testing_CheckP0SwAGpio0_SwAGpio1(); break;
			case EDCRBCheckP0SwBGpio0_SwAGpio1:		Testing_CheckP0SwBGpio0_SwAGpio1(); break;
			case EDCRBCheckSwASerial:					Testing_CheckSwASerial(); break;
			case EDCRBCheckSram:							Testing_CheckSram(); break;
			case EDCRBSaveTestResults:					TestingSave(); break;
			case EDCRBCheckSpiFlash:					Testing_CheckSpiFlash(); break;
			case EDCRBStoreSerialNumber:				Testing_StoreSerialNumber(); break;
			case EDCRBInputCurrent5V:					Testing_MinMaxRangeDouble("+5V Input Current", "Amps", DCRB_TEST_INPUTCURRENT5V_MIN, DCRB_TEST_INPUTCURRENT5V_MAX, 0, kTRUE); break;
			case EDCRBInputCurrent12VN:				Testing_MinMaxRangeDouble("-12V Input Current", "Amps", DCRB_TEST_INPUTCURRENT12VN_MIN, DCRB_TEST_INPUTCURRENT12VN_MAX, 0, kTRUE); break;
			case EDCRBInputCurrent12VP:				Testing_MinMaxRangeDouble("+12V Input Current", "Amps", DCRB_TEST_INPUTCURRENT12VP_MIN, DCRB_TEST_INPUTCURRENT12VP_MAX, 0, kTRUE); break;
			case EDCRBFEPulser_AboveThr:				Testing_FEPulser_AboveThr(); break;
			case EDCRBDCPulser_AboveThr:				Testing_DCPulser_AboveThr(); break;
			case EDCRBComplete:							Testing_Complete(); break;
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

		str.Form("DCRB_TestResult_%s.txt", strSerialNumber.Data());
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
				case DCRB_TESTSTATE_MSG:
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
					case BTN_DCRB_TESTING_START:
						pButtonStart->SetEnabled(kFALSE);
						pButtonContinue->SetEnabled(kFALSE);
						pButtonStop->SetEnabled(kTRUE);
						pTextViewDebug->Clear();
						SetNextTestingState(0);
						break;

					case BTN_DCRB_TESTING_CONTINUE:
						pButtonContinue->SetEnabled(kFALSE);
						bPromptContinueReady = kTRUE;
						ExecNextTestingState(nextTestingState);
						break;

					case BTN_DCRB_TESTING_STOP:
						TestingStop();
						break;

					case BTN_DCRB_ENTERINPUT:
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
	DCRB_regs			*pRegs;

	TGTextView			*pTextViewDebug;

	TGTextEntry			*pTextEntryDebug;

	TGTextButton		*pButtonStart;
	TGTextButton		*pButtonContinue;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonUserInput;	
};

#endif
