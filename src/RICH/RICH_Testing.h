#ifndef RICH_Testing_H
#define RICH_Testing_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "richLib.h"

#define RICH_SYSCLK_FREQ					125000000

#define RICH_TESTSTATE_MSG					1

#define BTN_RICH_TESTING_START			100
#define BTN_RICH_TESTING_CONTINUE		101
#define BTN_RICH_TESTING_STOP				102
#define BTN_RICH_ENTERINPUT				104

// Testing thresholds - NOTE: these need to be trimmed
#define RICH_TEST_BOARDID					0x52494348

#define RICH_PULSER_FREQ					100000
#define RICH_PULSER_FREQ_MIN				(RICH_PULSER_FREQ*0.99)
#define RICH_PULSER_FREQ_MAX				(RICH_PULSER_FREQ*1.01)

#define RICH_TEST_CURRENT5V_MIN			0.5
#define RICH_TEST_CURRENT5V_MAX			1.0

#define RICH_TEST_TEMPFPGA_MIN			30
#define RICH_TEST_TEMPFPGA_MAX			60

#define RICH_TEST_VOLTAGEVCCINT_MIN		0.95
#define RICH_TEST_VOLTAGEVCCINT_MAX		1.05

#define RICH_TEST_VOLTAGEVCCAUX_MIN		1.7
#define RICH_TEST_VOLTAGEVCCAUX_MAX		1.9

#define RICH_TEST_VOLTAGE5V_MIN			4.9
#define RICH_TEST_VOLTAGE5V_MAX			5.1

#define RICH_TEST_VOLTAGE3_3V_MIN		3.2
#define RICH_TEST_VOLTAGE3_3V_MAX		3.4

#define RICH_TEST_VOLTAGE1_0VMGT_MIN	0.95
#define RICH_TEST_VOLTAGE1_0VMGT_MAX	1.05

#define RICH_TEST_VOLTAGE1_2VMGT_MIN	1.15
#define RICH_TEST_VOLTAGE1_2VMGT_MAX	1.25

#define RICH_TEST_TEMPLTM1_MIN			30.0
#define RICH_TEST_TEMPLTM1_MAX			60.0

#define RICH_TEST_TEMPLTM2_MIN			30.0
#define RICH_TEST_TEMPLTM2_MAX			60.0

#define RICH_TEST_INTADCRMS_MIN			1.0
#define RICH_TEST_INTADCRMS_MAX			4.0

#define RICH_TEST_EXTADCRMS_MIN			1.0
#define RICH_TEST_EXTADCRMS_MAX			4.0

#define RICH_TEST_NOISESCALER_MIN		1000
#define RICH_TEST_NOISESCALER_MAX		100000000

// Supported testing states
enum RICHTestingStates
{
	ERICHInitialize,
	ERICHBoardId,
	ERICHCheckSpiFlash,
	ERICHInputCurrent5V,
	ERICHCheckTempFPGA,
	ERICHCheckVoltageVCCINT,
	ERICHCheckVoltageVCCAUX,
	ERICHCheckVoltage5V,
	ERICHCheckVoltage3_3V,
	ERICHCheckVoltage1_0VMGT,
	ERICHCheckVoltage1_2VMGT,
	ERICHCheckTempLTM1,
	ERICHCheckTempLTM2,
	ERICHCheckIO0,
	ERICHCheckIO1,
	ERICHCheckSlowControl,
	ERICHCheckDynControl,
	ERICHCheckScalerNoise,
	ERICHCheckScalerPulser,
	ERICHCheckInternalADC,
	ERICHCheckExternalADC,
	ERICHStoreSerialNumber,
	ERICHSaveTestResults,
	ERICHComplete
};

// Testing state sequence
int RICHTestSequence[] = {
	ERICHInitialize,
/*	
	ERICHBoardId,
	ERICHCheckSpiFlash,
*/
	ERICHInputCurrent5V,
	ERICHCheckTempFPGA,
	ERICHCheckVoltageVCCINT,
	ERICHCheckVoltageVCCAUX,
	ERICHCheckVoltage5V,
	ERICHCheckVoltage3_3V,
	ERICHCheckVoltage1_0VMGT,
	ERICHCheckVoltage1_2VMGT,
	ERICHCheckTempLTM1,
	ERICHCheckTempLTM2,
	ERICHCheckIO0,
	ERICHCheckIO1,
/*
	ERICHCheckSlowControl,
	ERICHCheckDynControl,
	ERICHCheckScalerNoise,
	ERICHCheckScalerPulser,
	ERICHCheckInternalADC,
	ERICHCheckExternalADC,
	ERICHStoreSerialNumber,
	ERICHSaveTestResults,
*/
	ERICHComplete
};

class RICH_Testing	: public TGCompositeFrame
{
public:
	RICH_Testing(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (RICH_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonStart = new TGTextButton(pTF1, "Start", BTN_RICH_TESTING_START), new TGLayoutHints(kLHintsCenterX));
				pButtonStart->SetWidth(200);
				pButtonStart->Associate(this);

			pTF1->AddFrame(pButtonContinue = new TGTextButton(pTF1, "Continue", BTN_RICH_TESTING_CONTINUE), new TGLayoutHints(kLHintsCenterX));
				pButtonContinue->Associate(this);
				pButtonContinue->SetEnabled(kFALSE);

			pTF1->AddFrame(pButtonStop = new TGTextButton(pTF1, "Stop", BTN_RICH_TESTING_STOP), new TGLayoutHints(kLHintsCenterX));
				pButtonStop->Associate(this);
				pButtonStop->SetEnabled(kFALSE);

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTF1->AddFrame(pTextViewDebug = new TGTextView(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(new TGLabel(pTF1, "User Input: "), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
			pTF1->AddFrame(pTextEntryDebug = new TGTextEntry(pTF1), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonUserInput = new TGTextButton(pTF1, "Enter Input", BTN_RICH_ENTERINPUT));
				pButtonUserInput->Associate(this);
				pButtonUserInput->SetEnabled(kFALSE);
	}

	void SetNextTestingState(int nextState)
	{
		nextTestingState = nextState;
		bPromptInputReady = kFALSE;
		bPromptContinueReady = kFALSE;

		SendMessage(this, MK_MSG(kC_USER, (EWidgetMessageTypes)RICH_TESTSTATE_MSG), nextTestingState, 0);
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
				TestingPromptInput(str.Format("Enter RICH %s(in %s): ", measurement, units));
				return;
			}
			val = str.Atoi();
		}

		///////////////////////////////////
		// Checking min range
		///////////////////////////////////
		str.Form("   min(%d) >= %d %s...", min, val, units);
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
		str.Form("   max(%d) <= %d %s...", max, val, units);
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
				TestingPromptInput(str.Format("Enter RICH %s(in %s): ", measurement, units));
				return 0.0;
			}
			val = str.Atof();
		}

		///////////////////////////////////
		// Checking min range
		///////////////////////////////////
		str.Form("   min(%f) <= %f %s...", min, val, units);
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
		str.Form("   max(%f) >= %f %s...", max, val, units);
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

		AddTextLine("RICH Testing Initialzed...");
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
		unsigned int BoardId = pM->ReadReg32(&pRegs->Clk.BoardId);
		str.Form("   BoardId(0x%08X) == 0x%08X...", RICH_TEST_BOARDID, BoardId);
		if(BoardId == RICH_TEST_BOARDID)
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

//		str.Form("   Firmware revision = 0x%08X", pM->ReadReg32(&pRegs->Cfg.FirmwareRev) & 0xFFFF);
		AddTextLine(str);

		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x80000000);
		pM->WriteReg32(&pRegs->Clk.Ctrl, 0x00000000);
		pM->Delay(10);
//		pM->WriteReg32(&pRegs->Cfg.Reset, 1);
		pM->Delay(10);
//		pM->WriteReg32(&pRegs->Cfg.Reset, 0);
		pM->Delay(10);
		
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}
	
	float Get_FPGATemp()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (0<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 503.975 / 65536.0 - 273.15;
		return v;
	}

	float Get_VCCINT()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (1<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 3.0 / 65536.0;
		return v;
	}

	float Get_VCCAUX()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (2<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 3.0 / 65536.0;
		return v;
	}

	float Get_5V()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (16<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 1.0 / 65536.0;
		v = v + (v / 237.0) * 1240.0;
		return v;
	}

	float Get_3_3V()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (24<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 1.0 / 65536.0;
		v = v + (v / 249.0) * 825.0;
		return v;
	}

	float Get_1_0VMGT()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (17<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 1.0 / 65536.0;
		v = v + (v / 1000.0) * 249.0;
		return v;
	}

	float Get_1_2VMGT()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (22<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 1.0 / 65536.0;
		v = v + (v / 604.0) * 301.0;
		return v;
	}

	float Get_LTMTemp1()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (18<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 1.0 / 65536.0;
		v = 27.0 + (0.598 - v) / 0.002;
		return v;
	}

	float Get_LTMTemp2()
	{
		pM->WriteReg32(&pRegs->Testing.XAdcCtrl, 0x01000000 | (26<<16));
		
		float v = (float)(pM->ReadReg32(&pRegs->Testing.XAdcStatus) & 0xFFFF) * 1.0 / 65536.0;
		v = 27.0 + (0.598 - v) / 0.002;
		return v;
	}

	void Set_Pulser(float freq, float duty)
	{
		if(freq <= 0.0)
		{
			printf("Error in %s: freq invalid, setting to 1Hz", __FUNCTION__);
			freq = 1.0;
		}

		if((duty <= 0.0) || (duty >= 1.0))
		{
			printf("Error in %s: duty invalid, setting to 50%", __FUNCTION__);
			duty = 0.5;
		}

		freq = 125000000 / freq;
		pM->WriteReg32(&pRegs->Sd.PulserPeriod, (int)freq);

		duty = freq * (1.0 - duty);
		pM->WriteReg32(&pRegs->Sd.PulserLowCycles, (int)duty);

		pM->WriteReg32(&pRegs->Sd.PulserNCycles, 0xFFFFFFFF);
	}

	void Testing_CheckIO(int n)
	{
		Set_Pulser(RICH_PULSER_FREQ, 0.5);
		pM->WriteReg32(&pRegs->Sd.OutSrc[n], SD_SRC_SEL_PULSER);
		
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x1);	// pause scalers
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x2);	// reset scalers
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x0);	// enable scalers
		gSystem->Sleep(1000);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x1);	// pause scalers
		
		double scale = (double)pM->ReadReg32(&pRegs->Sd.Scaler_GClk125) / 125000000.0;
		double ref = (double)pM->ReadReg32(&pRegs->Sd.Scaler_Input[n]);
		if(scale) ref = ref / scale;

		Testing_MinMaxRangeInt32(Form("CheckIO %d", n), "", RICH_PULSER_FREQ_MIN, RICH_PULSER_FREQ_MAX, (int)ref, kFALSE);
	}

	void SCRegs_Clear()
	{
		int val;

		/* set rst_sc low */
		val = pM_ReadReg32(&pRegs->MAROC_Cfg.SerCtrl);
		val &= 0xFFFFFFFE;
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl, val);

		/* set rst_sc high */
		val |= 0x00000001;
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl, val);
	}

	Bool_t SCRegs_Shift(MAROC_Regs *wr_regs, MAROC_Regs *rd_regs)
	{
		int i, val;
		
		/* write settings to FPGA shift register */
		pM->WriteReg32(&pRegs->MAROC_Cfg.Regs.Global0.val, wr_regs->Global0.val);
		pM->WriteReg32(&pRegs->MAROC_Cfg.Regs.Global1.val, wr_regs->Global1.val);
		pM->WriteReg32(&pRegs->MAROC_Cfg.Regs.DAC.val, wr_regs->DAC.val);
		
		for(i = 0; i < 32; i++)
			pM->WriteReg32(&pRegs->MAROC_Cfg.Regs.CH[i].val, wr_regs->CH[i].val);
		
		/* do shift register transfer */
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl);
		val |= 0x00000002;
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl, val);
		
		/* check for shift register transfer completion */
		for(i = 10; i > 0; i--)
		{
			val = pM_ReadReg32(&pRegs->MAROC_Cfg.SerStatus);
			if(!(val & 0x00000001))
				break;
			
			if(!i)
			{
				printf("Error in %s: timeout on serial transfer...\n", __FUNCTION__);
				return kFALSE;
			}
			gSystem->Sleep(1);
		}

		/* read back settings from FPGA shift register */
		rd_regs->Global0.val = pM_ReadReg32(&pRegs->MAROC_Cfg.Regs.Global0.val);
		rd_regs->Global1.val = pM_ReadReg32(&pRegs->MAROC_Cfg.Regs.Global1.val);
		rd_regs->DAC.val = pM_ReadReg32(&pRegs->MAROC_Cfg.Regs.DAC.val);
		
		for(i = 0; i < 32; i++)
			rd_regs->CH[i].val = pM_ReadReg32(&pRegs->MAROC_Cfg.Regs.CH[i].val);
		
		return kTRUE;
	}
	

	void Testing_CheckSlowControl()
	{
		MAROC_Regs maroc_regs_wr, maroc_regs_rd[3];
		TString str;
		unsigned int val;
		int i;

		///////////////////////////////////
		// Checking SlowControl
		///////////////////////////////////
		AddTextLine("********** CheckSlowControl **********");


		///////////////////////////////////
		str.Form("   slow control reset...");
		
		memset(&maroc_regs_wr, 0, sizeof(maroc_regs_wr));
		
		SCRegs_Clear();
		
		if(!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[1]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[2])
			)
		{
			str += "slow control timeout. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		if(memcmp(&maroc_regs_wr, &maroc_regs_rd[2], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[1], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[0], sizeof(maroc_regs_wr))
			)
		{
			str += "comparison failed. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		str += "OK";
		AddTextLine(str);
		///////////////////////////////////


		///////////////////////////////////
		str.Form("   slow control write zeros...");
		
		memset(&maroc_regs_wr, 0, sizeof(maroc_regs_wr));
		
		SCRegs_Clear();
		
		if(!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[2]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[2]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[1]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0])
			)
		{
			str += "slow control timeout. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		if(memcmp(&maroc_regs_wr, &maroc_regs_rd[0], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[1], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[2], sizeof(maroc_regs_wr))
			)
		{
			str += "comparison failed. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		str += "OK";
		AddTextLine(str);
		///////////////////////////////////



		///////////////////////////////////
		str.Form("   slow control 0s and 1s...", min, val, units);
		
		memset(&maroc_regs_wr, 0x55, sizeof(maroc_regs_wr));
		
		SCRegs_Clear();
		
		if(!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[2]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[2]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[1]) ||
			!SCRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0])
			)
		{
			str += "slow control timeout. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		if(memcmp(&maroc_regs_wr, &maroc_regs_rd[0], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[1], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[2], sizeof(maroc_regs_wr))
			)
		{
			str += "comparison failed. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		str += "OK";
		AddTextLine(str);
		///////////////////////////////////

		str += "PASSED";
		AddTextLine(str);
		
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

	void DynRegs_Clear()
	{
		int val;

		/* set rst_r low */
		val = pM->ReadReg32(&pRegs->MAROC_Cfg.SerCtrl);
		val &= 0xFFFFFFFB;
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl, val);

		/* set rst_r high */
		val |= 0x00000004;
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl, val);
	}

	Bool_t DynRegs_Shift(MAROC_DyRegs wr, MAROC_DyRegs *rd1, MAROC_DyRegs *rd2, MAROC_DyRegs *rd3)
	{
		int i, val;
		
		/* write settings to FPGA shift register */
		pM->WriteReg32(&pRegs->MAROC_Cfg.DyRegs_WrAll.Ch0_31_Hold1, wr.Ch0_31_Hold1);
		pM->WriteReg32(&pRegs->MAROC_Cfg.DyRegs_WrAll.Ch32_63_Hold1, wr.Ch32_63_Hold1);
		pM->WriteReg32(&pRegs->MAROC_Cfg.DyRegs_WrAll.Ch0_31_Hold2, wr.Ch0_31_Hold2);
		pM->WriteReg32(&pRegs->MAROC_Cfg.DyRegs_WrAll.Ch32_63_Hold2, wr.Ch32_63_Hold2);

		/* do shift register transfer */
		val = pM->ReadReg32(&pRegs->MAROC_Cfg.SerCtrl);
		val |= 0x00000008;
		pM->WriteReg32(&pRegs->MAROC_Cfg.SerCtrl, val);
		
		/* check for shift register transfer completion */
		for(i = 10; i > 0; i--)
		{
			val = pM->ReadReg32(&pRegs->MAROC_Cfg.SerStatus);
			if(!(val & 0x00000002))
				break;
			
			if(!i)
			{
				printf("Error in %s: timeout on serial transfer...\n", __FUNCTION__);
				return kFALSE;
			}
			gSystem->Sleep(1);
		}

		/* read back settings from FPGA shift register */
		if(rd1)
		{
			rd1->Ch0_31_Hold1 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[0].Ch0_31_Hold1);
			rd1->Ch32_63_Hold1 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[0].Ch32_63_Hold1);
			rd1->Ch0_31_Hold2 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[0].Ch0_31_Hold2);
			rd1->Ch32_63_Hold2 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[0].Ch32_63_Hold2);
		}

		if(rd2)
		{
			rd2->Ch0_31_Hold1 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[1].Ch0_31_Hold1);
			rd2->Ch32_63_Hold1 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[1].Ch32_63_Hold1);
			rd2->Ch0_31_Hold2 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[1].Ch0_31_Hold2);
			rd2->Ch32_63_Hold2 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[1].Ch32_63_Hold2);
		}

		if(rd3)
		{
			rd3->Ch0_31_Hold1 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[2].Ch0_31_Hold1);
			rd3->Ch32_63_Hold1 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[2].Ch32_63_Hold1);
			rd3->Ch0_31_Hold2 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[2].Ch0_31_Hold2);
			rd3->Ch32_63_Hold2 = pM->ReadReg32(&pRegs->MAROC_Cfg.DyRegs_Rd[2].Ch32_63_Hold2);
		}
		return kTRUE;
	}

	void Testing_CheckDynControl()
	{
		MAROC_DyRegs maroc_regs_wr, maroc_regs_rd[3];
		TString str;
		unsigned int val;
		int i;

		///////////////////////////////////
		// Checking DynamicControl
		///////////////////////////////////
		AddTextLine("********** CheckDynControl **********");


		///////////////////////////////////
		str.Form("   dynamic control reset...");
		
		memset(&maroc_regs_wr, 0, sizeof(maroc_regs_wr));
		
		DynRegs_Clear();
		
		if(!DynRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0], &maroc_regs_rd[1], &maroc_regs_rd[2]) ||
			!DynRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0], &maroc_regs_rd[1], &maroc_regs_rd[2])
			)
		{
			str += "dynamic control timeout. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		if(memcmp(&maroc_regs_wr, &maroc_regs_rd[2], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[1], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[0], sizeof(maroc_regs_wr))
			)
		{
			str += "comparison failed. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		str += "OK";
		AddTextLine(str);
		///////////////////////////////////


		///////////////////////////////////
		str.Form("   dynamic control write zeros...");
		
		memset(&maroc_regs_wr, 0, sizeof(maroc_regs_wr));
		
		DynRegs_Clear();
		
		if(!DynRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0], &maroc_regs_rd[1], &maroc_regs_rd[2]) ||
			!DynRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0], &maroc_regs_rd[1], &maroc_regs_rd[2])
			)
		{
			str += "slow control timeout. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		if(memcmp(&maroc_regs_wr, &maroc_regs_rd[0], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[1], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[2], sizeof(maroc_regs_wr))
			)
		{
			str += "comparison failed. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		str += "OK";
		AddTextLine(str);
		///////////////////////////////////


		///////////////////////////////////
		str.Form("   slow control set channel...", min, val, units);
		
		memset(&maroc_regs_wr, 0x0, sizeof(maroc_regs_wr));
		maroc_regs_wr.Ch0_31_Hold1 = 0x00000001
		
		DynRegs_Clear();
		
		if(!DynRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0], &maroc_regs_rd[1], &maroc_regs_rd[2]) ||
			!DynRegs_Shift(&maroc_regs_wr, &maroc_regs_rd[0], &maroc_regs_rd[1], &maroc_regs_rd[2])
			)
		{
			str += "slow control timeout. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		if(memcmp(&maroc_regs_wr, &maroc_regs_rd[0], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[1], sizeof(maroc_regs_wr)) ||
		   memcmp(&maroc_regs_wr, &maroc_regs_rd[2], sizeof(maroc_regs_wr))
			)
		{
			str += "comparison failed. ";
			str += "FAILED";
			AddTextLine(str);
			TestingStop();
			return;
		}
		
		str += "OK";
		AddTextLine(str);
		///////////////////////////////////

		str += "PASSED";
		AddTextLine(str);
		
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}


	void Testing_CheckScalerNoise()
	{
		TString str;
		MAROC_Regs regs, rd_regs;
		int i;

		///////////////////////////////////
		// Checking Scaler Noise
		///////////////////////////////////
		AddTextLine("********** CheckScalerNoise **********");

		regs->Global0.bits.cmd_fsu = 1;
		regs->Global0.bits.cmd_ss = 1;
		regs->Global0.bits.cmd_fsb = 1;
		regs->Global0.bits.swb_buf_250f = 0;
		regs->Global0.bits.swb_buf_500f = 0;
		regs->Global0.bits.swb_buf_1p = 0;
		regs->Global0.bits.swb_buf_2p = 0;
		regs->Global0.bits.ONOFF_ss = 1;
		regs->Global0.bits.sw_ss_300f = 1;
		regs->Global0.bits.sw_ss_600f = 1;
		regs->Global0.bits.sw_ss_1200f = 0;
		regs->Global0.bits.EN_ADC = 1;	// 1=enable,0=disable ADC
		regs->Global0.bits.H1H2_choice = 0;
		regs->Global0.bits.sw_fsu_20f = 1;
		regs->Global0.bits.sw_fsu_40f = 1;
		regs->Global0.bits.sw_fsu_25k = 0;
		regs->Global0.bits.sw_fsu_50k = 0;
		regs->Global0.bits.sw_fsu_100k = 0;
		regs->Global0.bits.sw_fsb1_50k = 0;
		regs->Global0.bits.sw_fsb1_100k = 0;
		regs->Global0.bits.sw_fsb1_100f = 1;
		regs->Global0.bits.sw_fsb1_50f = 1;
		regs->Global0.bits.cmd_fsb_fsu = 0;
		regs->Global0.bits.valid_dc_fs = 1;
		regs->Global0.bits.sw_fsb2_50k = 0;
		regs->Global0.bits.sw_fsb2_100k = 0;
		regs->Global0.bits.sw_fsb2_100f = 0;
		regs->Global0.bits.sw_fsb2_50f = 1;
		regs->Global0.bits.valid_dc_fsb2 = 0;
		regs->Global0.bits.ENb_tristate = 1;
		regs->Global0.bits.polar_discri = 0;
		regs->Global0.bits.inv_discriADC = 0;
		regs->Global1.bits.d1_d2 = 0;
		regs->Global1.bits.cmd_CK_mux = 0;
		regs->Global1.bits.ONOFF_otabg = 0;
		regs->Global1.bits.ONOFF_dac = 0;
		regs->Global1.bits.small_dac = 0; /* 0=2.3mV/DAC LSB, 1=1.1mV/DAC LSB */
		regs->Global1.bits.enb_outADC = 0;
		regs->Global1.bits.inv_startCmptGray = 0;
		regs->Global1.bits.ramp_8bit = 0;
		regs->Global1.bits.ramp_10bit = 0;
		regs->DAC.bits.DAC0 = 200; /* with small_dac = 0,  pedestal < ~200, signal ~200 to ~500, 500fC/pulse injected */
		regs->DAC.bits.DAC1 = 0;

		for(i = 0; i < 64; i++)
		{
			if(!(i & 0x1))
			{
				regs->CH[i>>1].bits.Gain0 = 64; /* Gain 64 = unity */
				regs->CH[i>>1].bits.Sum0 = 0;
				regs->CH[i>>1].bits.CTest0 = 0;
				regs->CH[i>>1].bits.MaskOr0 = 0;
			}
			else
			{
				regs->CH[i>>1].bits.Gain1 = 64; /* Gain 64 = unity */
				regs->CH[i>>1].bits.Sum1 = 0;
				regs->CH[i>>1].bits.CTest1 = 0;
				regs->CH[i>>1].bits.MaskOr1 = 0;
			}
		}

		SCRegs_Clear();
		SCRegs_Shift(&regs, &rd_regs);
		SCRegs_Shift(&regs, &rd_regs);
		SCRegs_Shift(&regs, &rd_regs);
		
		rich_write32(&pRICH_regs->Sd.ScalerLatch, 0x1);	// halt scaler counting
		rich_write32(&pRICH_regs->Sd.ScalerLatch, 0x2);	// resets scalers
		rich_write32(&pRICH_regs->Sd.ScalerLatch, 0x0);	// enable scaler counting
		gSystem->Sleep(1000);
		rich_write32(&pRICH_regs->Sd.ScalerLatch, 0x1);	// halt scaler counting

		for(j = 0; j < 64; j++)
		{
			for(i = 0; i < 3; i++)
			{
				val = rich_read32(&pRICH_regs->MAROC_Proc[i].Scalers[j]);
				str = Form("MAROC %2d, CH %2d: count = %u", i, j, val);

				if( (val < RICH_TEST_NOISESCALER_MIN) ||
				    (val > RICH_TEST_NOISESCALER_MAX)
				    )
				{
					str += "FAILED.";
					AddTextLine(str);
					TestingStop();
					return;
				}
				else
				{
					str += "ok.";
					AddTextLine(str);
				}
			}
		}
	
		str += "PASSED";
		AddTextLine(str);
		
		AddTextLine("");
		SetNextTestingState(nextTestingState+1);
	}

/*
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
*/
	void Testing_Complete()
	{
		AddTextLine("RICH Testing Complete. Unit PASSED");
		TestingStop();
	}

	void ExecNextTestingState(int curState)
	{
		if(!pButtonStop->IsEnabled())
			return;

		switch(RICHTestSequence[curState])
		{
			case ERICHInitialize:						Testing_Initialize(); break;
			case ERICHBoardId:							Testing_CheckBoardId(); break;
//			case ERICHCheckSpiFlash:					Testing_
			case ERICHInputCurrent5V:					Testing_MinMaxRangeDouble("+5V Input Current", "A", RICH_TEST_CURRENT5V_MIN, RICH_TEST_CURRENT5V_MAX, 0, kTRUE); break;
			case ERICHCheckTempFPGA:					Testing_MinMaxRangeDouble("FPGA Temp", "C", RICH_TEST_TEMPFPGA_MIN, RICH_TEST_TEMPFPGA_MAX, Get_FPGATemp(), kFALSE); break;
			case ERICHCheckVoltageVCCINT:				Testing_MinMaxRangeDouble("VCCINT Rail", "V", RICH_TEST_VOLTAGEVCCINT_MIN, RICH_TEST_VOLTAGEVCCINT_MAX, Get_VCCINT(), kFALSE); break;
			case ERICHCheckVoltageVCCAUX:				Testing_MinMaxRangeDouble("VCCAUX Rail", "V", RICH_TEST_VOLTAGEVCCAUX_MIN, RICH_TEST_VOLTAGEVCCAUX_MAX, Get_VCCAUX(), kFALSE); break;
			case ERICHCheckVoltage5V:					Testing_MinMaxRangeDouble("+5V Rail", "V", RICH_TEST_VOLTAGE5V_MIN, RICH_TEST_VOLTAGE5V_MAX, Get_5V(), kFALSE); break;
			case ERICHCheckVoltage3_3V:				Testing_MinMaxRangeDouble("+3.3V Rail", "V", RICH_TEST_VOLTAGE3_3V_MIN, RICH_TEST_VOLTAGE3_3V_MAX, Get_3_3V(), kFALSE); break;
			case ERICHCheckVoltage1_0VMGT:			Testing_MinMaxRangeDouble("+1.0V MGT Rail", "V", RICH_TEST_VOLTAGE1_0VMGT_MIN, RICH_TEST_VOLTAGE1_0VMGT_MAX, Get_1_0VMGT(), kFALSE); break;
			case ERICHCheckVoltage1_2VMGT:			Testing_MinMaxRangeDouble("+1.2V MGT Rail", "V", RICH_TEST_VOLTAGE1_2VMGT_MIN, RICH_TEST_VOLTAGE1_2VMGT_MAX, Get_1_2VMGT(), kFALSE); break;
			case ERICHCheckTempLTM1:					Testing_MinMaxRangeDouble("LTM Temp 1", "C", RICH_TEST_TEMPLTM1_MIN, RICH_TEST_TEMPLTM1_MAX, Get_LTMTemp1(), kFALSE); break;
			case ERICHCheckTempLTM2:					Testing_MinMaxRangeDouble("LTM Temp 2", "C", RICH_TEST_TEMPLTM2_MIN, RICH_TEST_TEMPLTM2_MAX, Get_LTMTemp2(), kFALSE); break;
			case ERICHCheckIO0:							Testing_CheckIO(0); break;
			case ERICHCheckIO1:							Testing_CheckIO(1); break;
			case ERICHCheckSlowControl:				Testing_CheckSlowControl(); break;
			case ERICHCheckDynControl:					Testing_CheckDynControl(); break;
			case ERICHCheckScalerNoise:				Testing_CheckScalerNoise(); break;
//			case ERICHCheckScalerPulser:				Testing_
//			case ERICHCheckInternalADC:				Testing_
//			case ERICHCheckExternalADC:				Testing_
//			case ERICHStoreSerialNumber:				Testing_
//			case ERICHSaveTestResults:					Testing_
			case ERICHComplete:							Testing_Complete(); break;
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

		str.Form("RICH_TestResult_%s.txt", strSerialNumber.Data());
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
				case RICH_TESTSTATE_MSG:
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
					case BTN_RICH_TESTING_START:
						pButtonStart->SetEnabled(kFALSE);
						pButtonContinue->SetEnabled(kFALSE);
						pButtonStop->SetEnabled(kTRUE);
						pTextViewDebug->Clear();
						SetNextTestingState(0);
						break;

					case BTN_RICH_TESTING_CONTINUE:
						pButtonContinue->SetEnabled(kFALSE);
						bPromptContinueReady = kTRUE;
						ExecNextTestingState(nextTestingState);
						break;

					case BTN_RICH_TESTING_STOP:
						TestingStop();
						break;

					case BTN_RICH_ENTERINPUT:
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
	RICH_regs			*pRegs;

	TGTextView			*pTextViewDebug;

	TGTextEntry			*pTextEntryDebug;

	TGTextButton		*pButtonStart;
	TGTextButton		*pButtonContinue;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonUserInput;	
};

#endif
