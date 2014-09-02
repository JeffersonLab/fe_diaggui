#ifndef DSC2_Testing_H
#define DSC2_Testing_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "dsc2.h"

#define MAX_WIDTH_INL_TDC			1.5
#define MAX_WIDTH_INL_TRG			3
#define MIN_WIDTH_CHECK				8
#define MAX_WIDTH_CHECK				40
#define NUM_WIDTH_POINTS			64

#define THRESHOLD_RAMP_DELAY		(115.0)
#define THRESHOLD_RAMP_OFFSET		250.0
#define THRESHOLD_TRIG_SLEW			2800	//750.0	// 750mV/4ns
#define THRESHOLD_RAMP_SLEW			1		// 1500mV/1500ns
#define MAX_THRESHOLD_INL			20
#define MIN_THRESHOLD_CHECK			50
#define THRESHOLD_STEP				100//20
#define NUM_THRESHOLD_POINTS		10//50

#define NUM_SCALER_PASSES			25
#define NUM_SCALER_PULSES			30

class DSC2_Testing : public TGCompositeFrame
{
public:
	DSC2_Testing(const TGWindow *p, ModuleFrame *pMFrame) : TGCompositeFrame(p, 400, 400)
	{
		int i;
		TGCompositeFrame *tF1, *tF2;

		SetLayoutManager(new TGVerticalLayout(this));
		pModFrame = pMFrame;
		pDSC2regs = (DSC2_regs *)pModFrame->BaseAddr;

		AddFrame(tF1 = new TGVerticalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
				tF2->AddFrame(new TGLabel(tF2, "VX1290A Base Address(A24 in hex):"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pNumEntryTDCAddr = new TGNumberEntry(tF2, 0x240000, 8, NUM_TDCBASEADDR, TGNumberFormat::kNESHex, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 4294967295.0), new TGLayoutHints(kLHintsRight));
					pNumEntryTDCAddr->SetWidth(85);
					pNumEntryTDCAddr->Associate(this);

			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
				tF2->AddFrame(new TGLabel(tF2, "Test Results Base Filename:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pTextEntryResultsFile = new TGTextEntry(tF2, "DSC2_TestResult", EDT_RESULTSFILENAME), new TGLayoutHints(kLHintsRight));
					pTextEntryResultsFile->SetWidth(200);

			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
				tF2->AddFrame(new TGLabel(tF2, "DSC2 Board Serial Number:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pTextEntrySerialNumber = new TGTextEntry(tF2, "-9999", EDT_SERIALNUM), new TGLayoutHints(kLHintsRight));
					pTextEntrySerialNumber->SetWidth(200);

			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
				tF2->AddFrame(new TGLabel(tF2, "DSC2 Assembly Revision:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pTextEntryAssyRev = new TGTextEntry(tF2, "D", EDT_ASSYREV), new TGLayoutHints(kLHintsRight));
					pTextEntryAssyRev->SetWidth(200);

			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
				tF2->AddFrame(new TGLabel(tF2, "DSC2 Test Selection:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pComboTestSelect = new TGComboBox(tF2, COM_TESTSELECT), new TGLayoutHints(kLHintsRight | kLHintsExpandY));
					pComboTestSelect->SetWidth(200);
					pComboTestSelect->AddEntry(new TGString("Run All Steps"), COM_TESTSELECT_STEP_ALL);
					pComboTestSelect->AddEntry(new TGString("Check Interfaces"), COM_TESTSELECT_STEP_VME_CHECK);
					pComboTestSelect->AddEntry(new TGString("Pulse Width Calibrate"), COM_TESTSELECT_STEP_PW_CAL);
					pComboTestSelect->AddEntry(new TGString("Out->IN1 Test"), COM_TESTSELECT_STEP_IN1);
					pComboTestSelect->AddEntry(new TGString("Out->IN2 Test"), COM_TESTSELECT_STEP_IN2);
					pComboTestSelect->AddEntry(new TGString("Scaler Tests"), COM_TESTSELECT_STEP_SCALER);
					pComboTestSelect->AddEntry(new TGString("Write Assembly Info"), COM_WRITE_ASSY_INFO);
					pComboTestSelect->AddEntry(new TGString("Ch 1 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH1);
					pComboTestSelect->AddEntry(new TGString("Ch 2 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH2);
					pComboTestSelect->AddEntry(new TGString("Ch 3 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH3);
					pComboTestSelect->AddEntry(new TGString("Ch 4 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH4);
					pComboTestSelect->AddEntry(new TGString("Ch 5 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH5);
					pComboTestSelect->AddEntry(new TGString("Ch 6 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH6);
					pComboTestSelect->AddEntry(new TGString("Ch 7 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH7);
					pComboTestSelect->AddEntry(new TGString("Ch 8 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH8);
					pComboTestSelect->AddEntry(new TGString("Ch 9 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH9);
					pComboTestSelect->AddEntry(new TGString("Ch 10 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH10);
					pComboTestSelect->AddEntry(new TGString("Ch 11 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH11);
					pComboTestSelect->AddEntry(new TGString("Ch 12 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH12);
					pComboTestSelect->AddEntry(new TGString("Ch 13 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH13);
					pComboTestSelect->AddEntry(new TGString("Ch 14 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH14);
					pComboTestSelect->AddEntry(new TGString("Ch 15 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH15);
					pComboTestSelect->AddEntry(new TGString("Ch 16 Threshold Scan"), COM_TESTSELECT_STEP_THR_CH16);
					pComboTestSelect->Select(COM_TESTSELECT_STEP_ALL);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			tF1->AddFrame(pCanvasTestResults = new TRootEmbeddedCanvas("DSC2 Test Results", tF1, 800, 600), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvasTestResults->GetCanvas()->SetBorderMode(0);
				pCanvasTestResults->GetCanvas()->cd();
					pPaveTextTitle = new TPaveText(0.0, 0.96, 1.0, 1.0);
						pPaveTextTitle->SetBorderSize(0);
						pPaveTextTitle->AddText("DSC2 Test Report");
						pPaveTextTitle->Draw();

					pPaveTextBoardId			= new TPaveText(0.00, 0.92, 0.50, 0.94);
					pPaveTextTDCId				= new TPaveText(0.50, 0.92, 1.00, 0.94);
					pPaveTextSerialNumber		= new TPaveText(0.00, 0.90, 0.50, 0.92);
					pPaveTextAssemblyRev		= new TPaveText(0.50, 0.90, 1.00, 0.92);
					pPaveTextTestDateTime		= new TPaveText(0.00, 0.88, 0.50, 0.90);
					pPaveTextFirmwareRev		= new TPaveText(0.50, 0.88, 1.00, 0.90);
					//pPaveTextIn1Status			= new TPaveText(0.00, 0.86, 0.50, 0.88);
					//pPaveTextIn2Status			= new TPaveText(0.50, 0.86, 1.00, 0.88);
					pPaveTextDSCCount_TDC		= new TPaveText(0.00, 0.86, 0.50, 0.88);
					pPaveTextTDCCount_TDC		= new TPaveText(0.50, 0.86, 1.00, 0.88);

					pPaveTextDSCCount_TRG		= new TPaveText(0.00, 0.84, 0.50, 0.86);
					pPaveTextTDCCount_TRG		= new TPaveText(0.50, 0.84, 1.00, 0.86);
					pPaveTextTDCWidthINL		= new TPaveText(0.00, 0.82, 0.50, 0.84);
					pPaveTextTRGWidthINL		= new TPaveText(0.50, 0.82, 1.00, 0.84);
					pPaveTextTDCThresholdINL	= new TPaveText(0.00, 0.80, 0.50, 0.82);
					pPaveTextTRGThresholdINL	= new TPaveText(0.50, 0.80, 1.00, 0.82);

					pPaveTextBoardId->SetTextAlign(12);
					pPaveTextTDCId->SetTextAlign(12);
					pPaveTextSerialNumber->SetTextAlign(12);
					pPaveTextAssemblyRev->SetTextAlign(12);
					pPaveTextTestDateTime->SetTextAlign(12);
					pPaveTextFirmwareRev->SetTextAlign(12);
					//pPaveTextIn1Status->SetTextAlign(12);
					//pPaveTextIn2Status->SetTextAlign(12);
					pPaveTextDSCCount_TDC->SetTextAlign(12);
					pPaveTextTDCCount_TDC->SetTextAlign(12);
					pPaveTextDSCCount_TRG->SetTextAlign(12);
					pPaveTextTDCCount_TRG->SetTextAlign(12);
					pPaveTextTDCWidthINL->SetTextAlign(12);
					pPaveTextTRGWidthINL->SetTextAlign(12);
					pPaveTextTDCThresholdINL->SetTextAlign(12);
					pPaveTextTRGThresholdINL->SetTextAlign(12);

					pPaveTextBoardId->SetBorderSize(1);
					pPaveTextTDCId->SetBorderSize(1);
					pPaveTextSerialNumber->SetBorderSize(1);
					pPaveTextAssemblyRev->SetBorderSize(1);
					pPaveTextTestDateTime->SetBorderSize(1);
					pPaveTextFirmwareRev->SetBorderSize(1);
					//pPaveTextIn1Status->SetBorderSize(1);
					//pPaveTextIn2Status->SetBorderSize(1);
					pPaveTextDSCCount_TDC->SetBorderSize(1);
					pPaveTextTDCCount_TDC->SetBorderSize(1);
					pPaveTextDSCCount_TRG->SetBorderSize(1);
					pPaveTextTDCCount_TRG->SetBorderSize(1);
					pPaveTextTDCWidthINL->SetBorderSize(1);
					pPaveTextTRGWidthINL->SetBorderSize(1);
					pPaveTextTDCThresholdINL->SetBorderSize(1);
					pPaveTextTRGThresholdINL->SetBorderSize(1);

					pPaveTextBoardId->SetMargin(0.01);
					pPaveTextTDCId->SetMargin(0.01);
					pPaveTextSerialNumber->SetMargin(0.01);
					pPaveTextAssemblyRev->SetMargin(0.01);
					pPaveTextTestDateTime->SetMargin(0.01);
					pPaveTextFirmwareRev->SetMargin(0.01);
					//pPaveTextIn1Status->SetMargin(0.01);
					//pPaveTextIn2Status->SetMargin(0.01);
					pPaveTextDSCCount_TDC->SetMargin(0.01);
					pPaveTextTDCCount_TDC->SetMargin(0.01);
					pPaveTextDSCCount_TRG->SetMargin(0.01);
					pPaveTextTDCCount_TRG->SetMargin(0.01);
					pPaveTextTDCWidthINL->SetMargin(0.01);
					pPaveTextTRGWidthINL->SetMargin(0.01);
					pPaveTextTDCThresholdINL->SetMargin(0.01);
					pPaveTextTRGThresholdINL->SetMargin(0.01);

					pPaveTextBoardId->Draw();
					pPaveTextTDCId->Draw();
					pPaveTextSerialNumber->Draw();
					pPaveTextAssemblyRev->Draw();
					pPaveTextTestDateTime->Draw();
					pPaveTextFirmwareRev->Draw();
					//pPaveTextIn1Status->Draw();
					//pPaveTextIn2Status->Draw();
					pPaveTextDSCCount_TDC->Draw();
					pPaveTextTDCCount_TDC->Draw();
					pPaveTextDSCCount_TRG->Draw();
					pPaveTextTDCCount_TRG->Draw();
					pPaveTextTDCWidthINL->Draw();
					pPaveTextTRGWidthINL->Draw();
					pPaveTextTDCThresholdINL->Draw();
					pPaveTextTRGThresholdINL->Draw();

					pPadPulseWidthTDC = new TPad("TDC Pulse Widths", "TDC Pulse Widths", 0.0, 0.4, 0.5, 0.8);
						pPadPulseWidthTDC->SetBorderSize(0);
						pPadPulseWidthTDC->Draw();

					pPadPulseWidthTRG = new TPad("TRG Pulse Widths", "TRG Pulse Widths", 0.5, 0.4, 1.0, 0.8);
						pPadPulseWidthTRG->SetBorderSize(0);
						pPadPulseWidthTRG->Draw();

					pPadThresholdTDC = new TPad("TDC Thresholds", "TDC Thresholds", 0.0, 0.0, 0.5, 0.4);
						pPadThresholdTDC->SetBorderSize(0);
						pPadThresholdTDC->Draw();

					pPadThresholdTRG = new TPad("TRG Thresholds", "TRG Thresholds", 0.5, 0.0, 1.0, 0.4);
						pPadThresholdTRG->SetBorderSize(0);
						pPadThresholdTRG->Draw();

			tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsExpandY));
				tF2->AddFrame(pButtonStart = new TGTextButton(tF2, new TGHotString("StartTest"), BTN_STARTTEST), new TGLayoutHints(kLHintsExpandX));
					pButtonStart->Associate(this);
				tF2->AddFrame(pButtonStop = new TGTextButton(tF2, new TGHotString("StopTest"), BTN_STOPTEST), new TGLayoutHints(kLHintsExpandX));
					pButtonStop->SetEnabled(kFALSE);
					pButtonStop->Associate(this);
				tF2->AddFrame(pButtonSaveResults = new TGTextButton(tF2, new TGHotString("SaveResults"), BTN_SAVERESULTS), new TGLayoutHints(kLHintsExpandX));
					pButtonSaveResults->Associate(this);
				tF2->AddFrame(pButtonClearResults = new TGTextButton(tF2, new TGHotString("ClearResults"), BTN_CLEARRESULTS), new TGLayoutHints(kLHintsExpandX));
					pButtonClearResults->Associate(this);
				tF2->AddFrame(pButtonTestContinue = new TGTextButton(tF2, new TGHotString("Continue"), BTN_CONTINUE), new TGLayoutHints(kLHintsExpandX));
					pButtonTestContinue->SetEnabled(kFALSE);
					pButtonTestContinue->Associate(this);
				tF2->AddFrame(pTextViewTesting = new TGTextView(tF2), new TGLayoutHints(kLHintsExpandY));
					pTextViewTesting->SetWidth(250);

		pMGraphPulseWidthTDC = new TMultiGraph("TDC Pulse Widths;", "TDC Pulse Widths;Width Setting(ns);Measured Width(ns)");
			pMGraphPulseWidthTDC->SetMinimum(0);
			pMGraphPulseWidthTDC->SetMaximum(50);
		pMGraphPulseWidthTRG = new TMultiGraph("TRG Pulse Widths", "TRG Pulse Widths;Width Setting(ns);Measured Width(ns)");
			pMGraphPulseWidthTRG->SetMinimum(0);
			pMGraphPulseWidthTRG->SetMaximum(50);
		pMGraphThresholdTDC = new TMultiGraph("TDC Thresholds", "TDC Thresholds;Threshold Setting(-mV); Measure Threshold(-mV)");
			pMGraphThresholdTDC->SetMinimum(0);
			pMGraphThresholdTDC->SetMaximum(1024);
		pMGraphThresholdTRG = new TMultiGraph("TRG Thresholds", "TRG Thresholds;Threshold Setting(-mV); Measure Threshold(-mV)");
			pMGraphThresholdTRG->SetMinimum(0);
			pMGraphThresholdTRG->SetMaximum(1024);

		for(i = 0; i < 16; i++)
		{
			pGraphPulseWidthTDC[i] = new TGraph(NUM_WIDTH_POINTS);
			pGraphPulseWidthTRG[i] = new TGraph(NUM_WIDTH_POINTS);
			pGraphThresholdTDC[i] = new TGraph(NUM_THRESHOLD_POINTS);
			pGraphThresholdTRG[i] = new TGraph(NUM_THRESHOLD_POINTS);

			pGraphPulseWidthTDC[i]->SetLineColor(i+2);
			pGraphPulseWidthTRG[i]->SetLineColor(i+2);
			pGraphThresholdTDC[i]->SetLineColor(i+2);
			pGraphThresholdTRG[i]->SetLineColor(i+2);

			pMGraphPulseWidthTDC->Add(pGraphPulseWidthTDC[i], "l");
			pMGraphPulseWidthTRG->Add(pGraphPulseWidthTRG[i], "l");
			pMGraphThresholdTDC->Add(pGraphThresholdTDC[i], "l");
			pMGraphThresholdTRG->Add(pGraphThresholdTRG[i], "l");
		}

		pGraphPulseWidthIdeal = new TGraph(NUM_WIDTH_POINTS);

		pGraphPulseWidthTDCMaskMin = new TGraph(NUM_WIDTH_POINTS);
		pGraphPulseWidthTDCMaskMin->SetLineColor(2);
		pGraphPulseWidthTDCMaskMin->SetLineWidth(2);
		pGraphPulseWidthTDCMaskMin->SetLineStyle(2);
		pMGraphPulseWidthTDC->Add(pGraphPulseWidthTDCMaskMin, "l");

		pGraphPulseWidthTDCMaskMax = new TGraph(NUM_WIDTH_POINTS);
		pGraphPulseWidthTDCMaskMax->SetLineColor(2);
		pGraphPulseWidthTDCMaskMax->SetLineWidth(2);
		pGraphPulseWidthTDCMaskMax->SetLineStyle(2);
		pMGraphPulseWidthTDC->Add(pGraphPulseWidthTDCMaskMax, "l");

		pGraphPulseWidthTRGMaskMin = new TGraph(NUM_WIDTH_POINTS);
		pGraphPulseWidthTRGMaskMin->SetLineColor(2);
		pGraphPulseWidthTRGMaskMin->SetLineWidth(2);
		pGraphPulseWidthTRGMaskMin->SetLineStyle(2);
		pMGraphPulseWidthTRG->Add(pGraphPulseWidthTRGMaskMin, "l");

		pGraphPulseWidthTRGMaskMax = new TGraph(NUM_WIDTH_POINTS);
		pGraphPulseWidthTRGMaskMax->SetLineColor(2);
		pGraphPulseWidthTRGMaskMax->SetLineWidth(2);
		pGraphPulseWidthTRGMaskMax->SetLineStyle(2);
		pMGraphPulseWidthTRG->Add(pGraphPulseWidthTRGMaskMax, "l");

		double mask_min, mask_max;
		for(i = 0; i < NUM_WIDTH_POINTS; i++)
		{
			if(i < MIN_WIDTH_CHECK)
			{
				mask_min = 0.0;

				if(i < 4)
					mask_max = 4;
				else
					mask_max = i;
			}
			else if(i < MAX_WIDTH_CHECK)
			{
				mask_min = i;
				mask_max = i;
			}
			else
			{
				mask_min = MAX_WIDTH_CHECK;
				mask_max = i;
			}
			pGraphPulseWidthTDCMaskMin->SetPoint(i, i, mask_min-MAX_WIDTH_INL_TDC);
			pGraphPulseWidthTDCMaskMax->SetPoint(i, i, mask_max+MAX_WIDTH_INL_TDC);
			pGraphPulseWidthTRGMaskMin->SetPoint(i, i, mask_min-MAX_WIDTH_INL_TRG);
			pGraphPulseWidthTRGMaskMax->SetPoint(i, i, mask_max+MAX_WIDTH_INL_TRG);
			pGraphPulseWidthIdeal->SetPoint(i, i, i);
		}

		pGraphThresholdIdeal = new TGraph(NUM_THRESHOLD_POINTS);

		pGraphThresholdMaskMin = new TGraph(NUM_THRESHOLD_POINTS);
		pGraphThresholdMaskMin->SetLineColor(2);
		pGraphThresholdMaskMin->SetLineWidth(2);
		pGraphThresholdMaskMin->SetLineStyle(2);
		pMGraphThresholdTDC->Add(pGraphThresholdMaskMin, "l");
		pMGraphThresholdTRG->Add(pGraphThresholdMaskMin, "l");

		pGraphThresholdMaskMax = new TGraph(NUM_THRESHOLD_POINTS);
		pGraphThresholdMaskMax->SetLineColor(2);
		pGraphThresholdMaskMax->SetLineWidth(2);
		pGraphThresholdMaskMax->SetLineStyle(2);
		pMGraphThresholdTDC->Add(pGraphThresholdMaskMax, "l");
		pMGraphThresholdTRG->Add(pGraphThresholdMaskMax, "l");

		for(i = 0; i < NUM_THRESHOLD_POINTS; i++)
		{
			pGraphThresholdMaskMin->SetPoint(i, MIN_THRESHOLD_CHECK+THRESHOLD_STEP*i, MIN_THRESHOLD_CHECK+THRESHOLD_STEP*i-MAX_THRESHOLD_INL);
			pGraphThresholdMaskMax->SetPoint(i, MIN_THRESHOLD_CHECK+THRESHOLD_STEP*i, MIN_THRESHOLD_CHECK+THRESHOLD_STEP*i+MAX_THRESHOLD_INL);
			pGraphThresholdIdeal->SetPoint(i, MIN_THRESHOLD_CHECK+THRESHOLD_STEP*i, MIN_THRESHOLD_CHECK+THRESHOLD_STEP*i);
		}

		pPadPulseWidthTDC->cd();
		pMGraphPulseWidthTDC->Draw("a");

		pPadPulseWidthTRG->cd();
		pMGraphPulseWidthTRG->Draw("a");

		pPadThresholdTDC->cd();
		pMGraphThresholdTDC->Draw("a");

		pPadThresholdTRG->cd();
		pMGraphThresholdTRG->Draw("a");

		ClearResults();
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		char buf[200];

		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_STARTTEST:
						pButtonStart->SetEnabled(kFALSE);
						pButtonStop->SetEnabled(kTRUE);
						gbStopHit = kFALSE;

						if(pComboTestSelect->GetSelected() == COM_TESTSELECT_STEP_VME_CHECK)
							Test_VMECheck();
						else if(pComboTestSelect->GetSelected() == COM_TESTSELECT_STEP_PW_CAL)
							Test_PulseWidth();
						else if( (pComboTestSelect->GetSelected() >= COM_TESTSELECT_STEP_THR_CH1) &&
						         (pComboTestSelect->GetSelected() <= COM_TESTSELECT_STEP_THR_CH16) )
							Test_Threshold(pComboTestSelect->GetSelected() - COM_TESTSELECT_STEP_THR_CH1);
						else if(pComboTestSelect->GetSelected() == COM_TESTSELECT_STEP_SCALER)
							Test_Scalers();
						else if(pComboTestSelect->GetSelected() == COM_WRITE_ASSY_INFO)
							Write_AssyInfo();
						else if(pComboTestSelect->GetSelected() == COM_TESTSELECT_STEP_ALL)
						{
							ClearResults();
							do
							{
								if(!Test_VMECheck()) break;
								if(!Test_PulseWidth()) break;
								if(!Test_Scalers()) break;
								if(!Test_Threshold(0)) break;
								if(!Test_Threshold(1)) break;
								if(!Test_Threshold(2)) break;
								if(!Test_Threshold(3)) break;
								if(!Test_Threshold(4)) break;
								if(!Test_Threshold(5)) break;
								if(!Test_Threshold(6)) break;
								if(!Test_Threshold(7)) break;
								if(!Test_Threshold(8)) break;
								if(!Test_Threshold(9)) break;
								if(!Test_Threshold(10)) break;
								if(!Test_Threshold(11)) break;
								if(!Test_Threshold(12)) break;
								if(!Test_Threshold(13)) break;
								if(!Test_Threshold(14)) break;
								if(!Test_Threshold(15)) break;
								if(!Write_AssyInfo()) break;
							} while(0);
						}

						pButtonStart->SetEnabled(kTRUE);
						pButtonStop->SetEnabled(kFALSE);
						break;
					case BTN_STOPTEST:
						sprintf(buf, "*** STOP PRESSED - QUITTING TEST ***");
						pTextViewTesting->AddLine(buf);
						pTextViewTesting->ScrollDown(50);
						gbStopHit = kTRUE;
						break;
					case BTN_SAVERESULTS:
						sprintf(buf, "%s_sn%s_rev%s.ps", pTextEntryResultsFile->GetText(),
						                                 pTextEntrySerialNumber->GetText(),
														 pTextEntryAssyRev->GetText());
						pCanvasTestResults->GetCanvas()->Print(buf);

//						TPostScript ps(buf, -111);
//						ps.Range(21.59, 27.94);
//						gStyle->SetPaperSize(21.59, 27.94);
//						pCanvasTestResults->GetCanvas()->SetWindowSize(400,400);
//						pCanvasTestResults->GetCanvas()->Draw();
//						ps.Close();
						break;
					case BTN_CLEARRESULTS:
						ClearResults();
						break;
					case BTN_CONTINUE:
						gbContinueHit = kTRUE;
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

	Bool_t CheckDSCBoardId()
	{
		unsigned int val;
		char buf[200];

		val = pModFrame->ReadReg32(&pDSC2regs->boardID);
		sprintf(buf, "Board Id: 0x%08X", val);
		pPaveTextBoardId->Clear();
		pPaveTextBoardId->AddText(buf);
		if(val == 0x44534332)
		{
			sprintf(buf, "Board Id = 0x%08X...ok", val);
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollDown(50);
			pPaveTextBoardId->SetFillColor(3);
			return kTRUE;
		}
		sprintf(buf, "Board Id = 0x%08X...failed", val);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		pPaveTextBoardId->SetFillColor(2);
		return kFALSE;
	}

	Bool_t CheckDSCSerialNumber()
	{
		char buf[200];

		sprintf(buf, "Serial Number: %s", pTextEntrySerialNumber->GetText());
		pPaveTextSerialNumber->Clear();
		pPaveTextSerialNumber->AddText(buf);
		if(strcmp(pTextEntrySerialNumber->GetText(), "-9999") && (strlen(pTextEntrySerialNumber->GetText()) > 0))
		{
			sprintf(buf, "Serial Number = %s...ok", pTextEntrySerialNumber->GetText());
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollDown(50);
			pPaveTextSerialNumber->SetFillColor(3);
			return kTRUE;
		}
		sprintf(buf, "Serial Number = %s...failed", pTextEntrySerialNumber->GetText());
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		pPaveTextSerialNumber->SetFillColor(2);
		return kFALSE;
	}

	Bool_t CheckDSCAssemblyRevision()
	{
		char buf[200];

		sprintf(buf, "Assembly Rev: %s", pTextEntryAssyRev->GetText());
		pPaveTextAssemblyRev->Clear();
		pPaveTextAssemblyRev->AddText(buf);
		if(strlen(pTextEntryAssyRev->GetText()) > 0)
		{
			sprintf(buf, "Assembly Revision = %s...ok", pTextEntryAssyRev->GetText());
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollDown(50);
			pPaveTextAssemblyRev->SetFillColor(3);
			return kTRUE;
		}
		sprintf(buf, "Assembly Revision = %s...failed", pTextEntryAssyRev->GetText());
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		pPaveTextAssemblyRev->SetFillColor(2);
		return kFALSE;
	}

	Bool_t CheckTestDateTime()
	{
		char buf[200];
		TDatime t;

		sprintf(buf, "Test Date/Time: %s", t.AsString());
		pPaveTextTestDateTime->Clear();
		pPaveTextTestDateTime->AddText(buf);
		pPaveTextTestDateTime->SetFillColor(3);
		sprintf(buf, "Test Date/Time = %s...ok", t.AsString());
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		return kTRUE;
	}

	Bool_t CheckDSCFirmwareRevision()
	{
		unsigned int val;
		char buf[200];

		val = pModFrame->ReadReg32(&pDSC2regs->firmwareRev);
		sprintf(buf, "Firmware Rev: 0x%08X", val);
		pPaveTextFirmwareRev->Clear();
		pPaveTextFirmwareRev->AddText(buf);
		if(((val & 0xFFFF) >= 0x0109) && !(val & 0xFFFF0000))
		{
			sprintf(buf, "Firmware Revision = v%d.%d...ok", (val>>8)&0xFF, val&0xFF);
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollDown(50);
			pPaveTextFirmwareRev->SetFillColor(3);
			return kTRUE;
		}
		sprintf(buf, "Firmware Revision = v%d.%d...failed", (val>>8)&0xFF, val&0xFF);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		pPaveTextFirmwareRev->SetFillColor(2);
		return kFALSE;
	}

	Bool_t CheckTDCBoardId()
	{
		unsigned int val;
		unsigned short vme_word;
		char buf[200];

		vme_word = pModFrame->ReadReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x403C));
		val = vme_word & 0xFF;
		vme_word = pModFrame->ReadReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x4038));
		val |= (vme_word & 0xFF)<<8;
		vme_word = pModFrame->ReadReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x4034));
		val |= (vme_word & 0xFF)<<16;

		sprintf(buf, "TDC Board Id: 0x%08X", val);
		pPaveTextTDCId->Clear();
		pPaveTextTDCId->AddText(buf);
		if(val == 0x0001050A)
		{
			sprintf(buf, "TDC Board Id = 0x%08X...ok", val);
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollDown(50);
			pPaveTextTDCId->SetFillColor(3);
			return kTRUE;
		}
		sprintf(buf, "TDC Board Id = 0x%08X...failed", val);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		pPaveTextTDCId->SetFillColor(2);
		return kFALSE;
	}


	Bool_t Test_VMECheck()	
	{
		Bool_t result = kFALSE;
		pTextViewTesting->AddLine("*** Check Interfaces ***");
		pTextViewTesting->ScrollDown(50);

		if(!CheckDSCBoardId() ||
		   !CheckDSCSerialNumber() ||
		   !CheckDSCAssemblyRevision() ||
		   !CheckTestDateTime() ||
		   !CheckDSCFirmwareRevision() ||
		   !CheckTDCBoardId())
		{
			pTextViewTesting->AddLine("*** Check Interfaces FAILED ***");
			pTextViewTesting->ScrollDown(50);
		}
		else
		{
			pTextViewTesting->AddLine("*** Check Interfaces PASSED ***");
			pTextViewTesting->ScrollDown(50);
			result = kTRUE;
		}

		pCanvasTestResults->GetCanvas()->Modified();
		pCanvasTestResults->GetCanvas()->Update();

		return result;
	}

	Bool_t CheckCalibration()
	{
		char buf[200];

		pModFrame->WriteReg32(&pDSC2regs->calCmd, 0xFF);
		pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);

		TTimer calTimer(5000, kFALSE);
		calTimer.Start(5000, kTRUE);

		while(kTRUE)
		{
			if(calTimer.HasTimedOut())
				break;

			if(pModFrame->ReadReg32(&pDSC2regs->calCmd) == 0xFFFFFFFF)
			{
				sprintf(buf, "Pulse width calibration initialization...ok");
				pTextViewTesting->AddLine(buf);
				pTextViewTesting->ScrollDown(50);
				return kTRUE;
			}

			gSystem->ProcessEvents();
			if(gbStopHit)
				return kFALSE;
		}
		sprintf(buf, "Pulse width calibration initialization...failed");
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		return kFALSE;
	}

	Bool_t CheckPulseWidths()
	{
		unsigned int TDCBuffer[128];
		unsigned int LeadingEdge[32];
		unsigned int TrailingEdge[32];
		unsigned int i, j;
		Bool_t result = kTRUE;

		// DSC2 configuration
		for(i = 0; i < 16; i++)
			pModFrame->WriteReg32(&pDSC2regs->threshold[i], 1023 | (1023<<16));
		pModFrame->WriteReg32(&pDSC2regs->chEnable, 0xFFFFFFFF);	// prevent analog inputs from triggering pulsers
		pModFrame->WriteReg32(&pDSC2regs->delay, 0x00000000);		// bypass trigger pulse reshaping
		pModFrame->WriteReg32(&pDSC2regs->testCtrl, 0);				// disable front-panel test input
		
		// TDC configuration
		TDCMicroWrite(0x2200);	// TDC dual edge mode
		TDCMicroWrite(0x0003);	// TDC dual edge mode
		TDCMicroWrite(0x4200);	// TDC enable all channels
		
		pModFrame->Delay(1000);
//FILE *f = fopen("testwidth.txt", "wt");
		for(i = 0; i < NUM_WIDTH_POINTS; i++)
		{
			int num_tries = 3;
			memset(LeadingEdge, 0, sizeof(LeadingEdge));
			memset(TrailingEdge, 0, sizeof(TrailingEdge));

retry_pulsewidth:
			num_tries--;

			memset(TDCBuffer, 0, sizeof(TDCBuffer));
			for(j = 0; j < 32; j++)
			{
				if(!LeadingEdge[j] || !TrailingEdge[j])
				{
					LeadingEdge[j] = 0;
					TrailingEdge[j] = 0;
				}
			}
			
			pModFrame->WriteReg32(&pDSC2regs->pulsewidth, i | (i<<16));
			pModFrame->Delay(1);
			pModFrame->WriteReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x1016), 0x0001);	// TDC clear
			pModFrame->Delay(1);
			pModFrame->WriteReg32(&pDSC2regs->testCtrl, 0);										// sw test pulse
			pModFrame->Delay(1);
			pModFrame->BlkReadReg32((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x0000), TDCBuffer, sizeof(TDCBuffer)/sizeof(TDCBuffer[0]), CRATE_MSG_FLAGS_ADRINC);

/*						fprintf(f, "************* Buffer @ Point %d:\n", i);
						for(int k = 0; k < 128; k++)
						{
							unsigned int ch = (TDCBuffer[k]>>21) & 0x1F;
							unsigned int time = TDCBuffer[k] & 0x1FFFF;

							fprintf(f, "0x%08X", TDCBuffer[k]);
							if(!(TDCBuffer[k] & 0xF8000000) && (TDCBuffer[k] & 0x04000000))
								fprintf(f, "{Trail Ch%d,T%d} ", ch, time);
							if(!(TDCBuffer[k] & 0xF8000000) && !(TDCBuffer[k] & 0x04000000))
								fprintf(f, "{Lead Ch%d,T%d} ", ch, time);
							fprintf(f, "\n");
						}
*/

			for(j = 0; j < sizeof(TDCBuffer)/sizeof(TDCBuffer[0]); j++)
			{
				if( (TDCBuffer[j] & 0xF8000000) == 0xC0000000)
					break;

				if(!(TDCBuffer[j] & 0xF8000000))
				{
					unsigned int ch = (TDCBuffer[j]>>21) & 0x1F;
					unsigned int time = TDCBuffer[j] & 0x1FFFF;

					if(TDCBuffer[j] & 0x04000000)
					{
						if(!TrailingEdge[ch] && LeadingEdge[ch])
						{
							if(time < LeadingEdge[ch])
								TrailingEdge[ch] = time + (1<<17);
							else
								TrailingEdge[ch] = time;
						}
					}
					else if(!LeadingEdge[ch])
						LeadingEdge[ch] = time;
				}
			}
			
			for(int ch = 0; ch < 32; ch++)
			{
				double width = 0;
				if(TrailingEdge[ch] && LeadingEdge[ch])
					width = ((double)TrailingEdge[ch]-(double)LeadingEdge[ch])/40.0;
				else if(num_tries > 0)
					goto retry_pulsewidth;

				if(ch < 16)
					pGraphPulseWidthTDC[ch]->SetPoint(i, i, width);
				else
					pGraphPulseWidthTRG[ch-16]->SetPoint(i, i, width);
			}

			pPadPulseWidthTDC->Modified();
			pPadPulseWidthTRG->Modified();
			pCanvasTestResults->GetCanvas()->Modified();
			pCanvasTestResults->GetCanvas()->Update();

			gSystem->ProcessEvents();
			if(gbStopHit)
				return kFALSE;
		}
//fclose(f);
		char buf[200];
		sprintf(buf, "TDC Width INL: %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f",
			CheckINL(pGraphPulseWidthTDC[0], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[1], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[2], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[3], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[4], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[5], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[6], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[7], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[8], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[9], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[10], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[11], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[12], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[13], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[14], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTDC[15], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK));

		pPaveTextTDCWidthINL->Clear();
		pPaveTextTDCWidthINL->AddText(buf);
		pPaveTextTDCWidthINL->SetFillColor(3);
		for(i = 0; i < 16; i++)
		{
			if(!CheckMask(pGraphPulseWidthTDC[i], pGraphPulseWidthTDCMaskMin, pGraphPulseWidthTDCMaskMax))
			{
				pPaveTextTDCWidthINL->SetFillColor(2);
				result = kFALSE;
			}
		}

		sprintf(buf, "TRG Width INL: %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f",
			CheckINL(pGraphPulseWidthTRG[0], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[1], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[2], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[3], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[4], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[5], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[6], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[7], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[8], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[9], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[10], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[11], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[12], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[13], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[14], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK),
			CheckINL(pGraphPulseWidthTRG[15], pGraphPulseWidthIdeal, MIN_WIDTH_CHECK, MAX_WIDTH_CHECK));

		pPaveTextTRGWidthINL->Clear();
		pPaveTextTRGWidthINL->AddText(buf);
		pPaveTextTRGWidthINL->SetFillColor(3);
		for(i = 0; i < 16; i++)
		{
			if(!CheckMask(pGraphPulseWidthTRG[i], pGraphPulseWidthTRGMaskMin, pGraphPulseWidthTRGMaskMax))
			{
				pPaveTextTRGWidthINL->SetFillColor(2);
				result = kFALSE;
			}
		}

		return result;
	}

	Bool_t CheckThreshold(int ch)
	{
		unsigned int TDCBuffer[128];
		double LeadingEdgeTimes[128];
		unsigned int i, j;
		Bool_t result = kTRUE;

		// DSC2 configuration
		pModFrame->WriteReg32(&pDSC2regs->chEnable, (1<<ch));
		pModFrame->WriteReg32(&pDSC2regs->delay, 0x00000000);			// bypass trigger pulse reshaping
		pModFrame->WriteReg32(&pDSC2regs->testCtrl, 0);					// disable front-panel test input
		pModFrame->WriteReg32(&pDSC2regs->pulsewidth, 10 | (10<<16));	// 10ns pulse widths
		
		// TDC configuration
		TDCMicroWrite(0x2200);	// TDC leading edge mode
		TDCMicroWrite(0x0002);	// TDC leading edge mode
		TDCMicroWrite(0x4200);	// TDC enable all channels

//FILE *f = fopen("testthreshold.txt", "wt");
		for(i = 0; i < NUM_THRESHOLD_POINTS; i++)
		{
			int thr = MIN_THRESHOLD_CHECK+i*THRESHOLD_STEP;

			memset(TDCBuffer, 0, sizeof(TDCBuffer));

			if(ch < 16)
				pModFrame->WriteReg32(&pDSC2regs->threshold[ch%16], thr | (1023<<16));
			else
				pModFrame->WriteReg32(&pDSC2regs->threshold[ch%16], 1023 | (thr<<16));

			if(!i)
				pModFrame->Delay(1000);
			else
				pModFrame->Delay(17);

			pModFrame->WriteReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x1016), 0x0001);	// TDC clear
			pModFrame->Delay(1);
			pModFrame->BlkReadReg32((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x0000), TDCBuffer, sizeof(TDCBuffer)/sizeof(TDCBuffer[0]), CRATE_MSG_FLAGS_ADRINC);

/*						fprintf(f, "************* Ch: %d, Buffer @ Point %d:\n", i, ch);
						for(int k = 0; k < 128; k++)
						{
							unsigned int ch = (TDCBuffer[k]>>21) & 0x1F;
							unsigned int time = TDCBuffer[k] & 0x1FFFF;

							fprintf(f, "0x%08X", TDCBuffer[k]);
							if(!(TDCBuffer[k] & 0xF8000000) && (TDCBuffer[k] & 0x04000000))
								fprintf(f, "{Trail Ch%d,T%d} ", ch, time);
							if(!(TDCBuffer[k] & 0xF8000000) && !(TDCBuffer[k] & 0x04000000))
								fprintf(f, "{Lead Ch%d,T%d} ", ch, time);
							fprintf(f, "\n");
						}
*/

			unsigned int edges = 0;
			for(j = 0; j < sizeof(TDCBuffer)/sizeof(TDCBuffer[0]); j++)
			{
				if( (TDCBuffer[j] & 0xF8000000) == 0xC0000000)
					break;

				if(!(TDCBuffer[j] & 0xF8000000))
				{
					int tdc_ch = (TDCBuffer[j]>>21) & 0x1F;
					unsigned int time = TDCBuffer[j] & 0x1FFFFF;

					if(!(TDCBuffer[j] & 0x04000000))
					{
						if(ch == tdc_ch)
						{
							LeadingEdgeTimes[edges] = (double)time;
							LeadingEdgeTimes[edges] /= 40.0;
							edges++;
						}
					}
				}
			}

			double sum = 0, avg_delta = 0, dsc_thr = 0;
			int count = 0;
			if(edges >= 2)
			{
				for(j = 0; j < edges-1; j++)
					LeadingEdgeTimes[j] = LeadingEdgeTimes[j+1]-LeadingEdgeTimes[j];
				LeadingEdgeTimes[edges-1] = 0.0;

//for(j = 0; j < edges-1; j++)
//	fprintf(f, "Diff[%d] = %f\n", j, LeadingEdgeTimes[j]*0.025);

				for(j = 0; j < edges-2; j++)
				{
					if( (LeadingEdgeTimes[j] > 100) && (LeadingEdgeTimes[j] < 2000) )
					{
						sum+= LeadingEdgeTimes[j];
						count++;
					}
				}
				if(count)
				{
					avg_delta = sum / (double)count;
					dsc_thr = (avg_delta - THRESHOLD_RAMP_DELAY) *
							  (THRESHOLD_TRIG_SLEW * THRESHOLD_RAMP_SLEW) /
							  (THRESHOLD_TRIG_SLEW - THRESHOLD_RAMP_SLEW) - THRESHOLD_RAMP_OFFSET;
				}
			}

			if(ch < 16)
			{
				pGraphThresholdTDC[ch]->SetPoint(i, thr, dsc_thr);
				pPadThresholdTDC->Modified();
			}
			else
			{
				pGraphThresholdTRG[ch-16]->SetPoint(i, thr, dsc_thr);
				pPadThresholdTRG->Modified();
			}
			pCanvasTestResults->GetCanvas()->Modified();
			pCanvasTestResults->GetCanvas()->Update();

			gSystem->ProcessEvents();
			if(gbStopHit)
				return kFALSE;
		}

		char buf[200];
		sprintf(buf, "TDC Threshold INL:");
		for(i = 0; i < 16; i++)
		{
			if(pGraphThresholdTDC[i]->GetY()[0] > 0)
				sprintf(&buf[strlen(buf)], " %.1f", CheckINL(pGraphThresholdTDC[i], pGraphThresholdIdeal, 0, NUM_THRESHOLD_POINTS-1));
			else
				sprintf(&buf[strlen(buf)], " ?");
		}

		pPaveTextTDCThresholdINL->Clear();
		pPaveTextTDCThresholdINL->AddText(buf);
		pPaveTextTDCThresholdINL->SetFillColor(3);
		for(i = 0; i < 16; i++)
		{
			if(pGraphThresholdTDC[i]->GetY()[0] < 0)
				pPaveTextTDCThresholdINL->SetFillColor(19);
			else if(!CheckMask(pGraphThresholdTDC[i], pGraphThresholdMaskMin, pGraphThresholdMaskMax))
			{
				pPaveTextTDCThresholdINL->SetFillColor(2);
				result = kFALSE;
			}
		}

		sprintf(buf, "TRG Threshold INL:");
		for(i = 0; i < 16; i++)
		{
//printf("TRG Threshold INL->pGraphThresholdTRG[%d]->GetY()[0]=%f\n", i, pGraphThresholdTRG[i]->GetY()[0]);
			if(pGraphThresholdTRG[i]->GetY()[0] > 0)
				sprintf(&buf[strlen(buf)], " %.1f", CheckINL(pGraphThresholdTRG[i], pGraphThresholdIdeal, 0, NUM_THRESHOLD_POINTS-1));
			else
				sprintf(&buf[strlen(buf)], " ?");
		}

		pPaveTextTRGThresholdINL->Clear();
		pPaveTextTRGThresholdINL->AddText(buf);
		pPaveTextTRGThresholdINL->SetFillColor(3);
		for(i = 0; i < 16; i++)
		{
			if(pGraphThresholdTRG[i]->GetY()[0] < 0)
				pPaveTextTRGThresholdINL->SetFillColor(19);
			else if(pGraphThresholdTRG[i]->GetY()[0] && !CheckMask(pGraphThresholdTRG[i], pGraphThresholdMaskMin, pGraphThresholdMaskMax))
			{
				pPaveTextTRGThresholdINL->SetFillColor(2);
				result = kFALSE;
			}
		}
//fclose(f);
		return result;
	}

	Bool_t CheckMask(TGraph *pGdata, TGraph *pGmaskMin, TGraph *pGmaskMax)
	{
//		printf("pGdata->GetN() = %d, pGmaskMin->GetN() = %d, pGmaskMax->GetN() = %d\n");
		if( (pGdata->GetN() != pGmaskMin->GetN()) ||
			(pGdata->GetN() != pGmaskMax->GetN()) )
			return kFALSE;

		for(int i = 0; i < pGdata->GetN(); i++)
		{
//			printf("pGdata->GetY()[%d] = %f, pGmaskMin->GetY()[%d] = %f, pGmaskMax->GetY()[%d] = %f\n", i, pGdata->GetY()[i], i, pGmaskMin->GetY()[i], i, pGmaskMax->GetY()[i]);
			if(pGdata->GetY()[i] < pGmaskMin->GetY()[i])
				return kFALSE;
			if(pGdata->GetY()[i] > pGmaskMax->GetY()[i])
				return kFALSE;
		}
		return kTRUE;
	}

	double CheckINL(TGraph *pGdata, TGraph *pGideal, int pStart, int pEnd)
	{
		double result = 0.0;

//		printf("pGdata->GetN() = %d, pGideal->GetN() = %d\n", pGdata->GetN(), pGideal->GetN());
//		printf("pStart = %d, pEnd = %d\n", pStart, pEnd);

		if( (pGdata->GetN() != pGideal->GetN()) ||
		    ((pStart < 0) || (pStart >= pGdata->GetN())) ||
			((pEnd < 0) || (pEnd >= pGdata->GetN())) )
			return -1;

		for(int i = pStart; i < pEnd; i++)
		{
			double diff = fabs(pGdata->GetY()[i] - pGideal->GetY()[i]);
//			printf("pGdata->GetY()[i] = %f, pGideal->GetY()[i] = %f, diff = %f\n", 
//				pGdata->GetY()[i], pGideal->GetY()[i], diff);
			if(diff > result)
				result = diff;
		}
//		printf("result = %f\n", result);
		return result;
	}

	Bool_t CheckScalers()
	{
		unsigned int TDCBuffer[1024];
		unsigned int TDCEdgeCounts[32];
		unsigned int DSCEdgeCounts[32];
		unsigned int i, j;
		Bool_t result = kTRUE;

		// DSC2 configuration
		pModFrame->WriteReg32(&pDSC2regs->chEnable, 0xFFFFFFFF);
		pModFrame->WriteReg32(&pDSC2regs->delay, 0x00000000);			// bypass trigger pulse reshaping
		pModFrame->WriteReg32(&pDSC2regs->testCtrl, 0);					// disable front-panel test input
		pModFrame->WriteReg32(&pDSC2regs->pulsewidth, 10 | (10<<16));	// 10ns pulse widths
		
		// TDC configuration
		TDCMicroWrite(0x2200);	// TDC leading edge mode
		TDCMicroWrite(0x0002);	// TDC leading edge mode
		TDCMicroWrite(0x4200);	// TDC enable all channels

		for(i = 0; i < 16; i++)
			pModFrame->WriteReg32(&pDSC2regs->threshold[i], 100 | (100<<16));

		pModFrame->Delay(1000);

		memset(TDCEdgeCounts, 0, sizeof(TDCEdgeCounts));
		pModFrame->WriteReg32(&pDSC2regs->ScalerLatchGrp2, 0);

		for(i = 0; i < NUM_SCALER_PASSES; i++)
		{
			memset(TDCBuffer, 0, sizeof(TDCBuffer));
			pModFrame->WriteReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x1016), 0x0001);	// TDC clear

			for(j = 0; j < NUM_SCALER_PULSES; j++)
				pModFrame->WriteReg32(&pDSC2regs->testCtrl, 0);		// sw test pulse

			pModFrame->Delay(1);
			pModFrame->BlkReadReg32((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x0000), TDCBuffer, sizeof(TDCBuffer)/sizeof(TDCBuffer[0]), CRATE_MSG_FLAGS_ADRINC);
			for(j = 0; j < sizeof(TDCBuffer)/sizeof(TDCBuffer[0]); j++)
			{
				if( (TDCBuffer[j] & 0xF8000000) == 0xC0000000)
					break;

				if(!(TDCBuffer[j] & 0xF8000000))
				{
					unsigned int tdc_ch = (TDCBuffer[j]>>21) & 0x1F;
					TDCEdgeCounts[tdc_ch]++;
				}
			}

			gSystem->ProcessEvents();
			if(gbStopHit)
				return kFALSE;
		}
		pModFrame->WriteReg32(&pDSC2regs->ScalerLatchGrp2, 0);

		for(i = 0; i < 16; i++)
		{
			DSCEdgeCounts[i] = pModFrame->ReadReg32(&pDSC2regs->TdcScalerGrp2[i]);
			DSCEdgeCounts[i+16] = pModFrame->ReadReg32(&pDSC2regs->TrgScalerGrp2[i]);
		}

		char buf[400];

		pPaveTextDSCCount_TDC->Clear();
		pPaveTextDSCCount_TDC->SetFillColor(3);
		sprintf(buf, "DSC:TDC Scaler Test(%u):", NUM_SCALER_PASSES*NUM_SCALER_PULSES);
		for(i = 0; i < 16; i++)
		{
			sprintf(&buf[strlen(buf)], " %u", DSCEdgeCounts[i]);
			if(DSCEdgeCounts[i] != NUM_SCALER_PASSES*NUM_SCALER_PULSES)
			{
				pPaveTextDSCCount_TDC->SetFillColor(2);
				result = kFALSE;
			}
		}
		pPaveTextDSCCount_TDC->AddText(buf);

		pPaveTextDSCCount_TRG->Clear();
		pPaveTextDSCCount_TRG->SetFillColor(3);
		sprintf(buf, "DSC:TRG Scaler Test(%u):", NUM_SCALER_PASSES*NUM_SCALER_PULSES);
		for(i = 0; i < 16; i++)
		{
			sprintf(&buf[strlen(buf)], " %u", DSCEdgeCounts[i]);
			if(DSCEdgeCounts[i+16] != NUM_SCALER_PASSES*NUM_SCALER_PULSES)
			{
				pPaveTextDSCCount_TRG->SetFillColor(2);
				result = kFALSE;
			}
		}
		pPaveTextDSCCount_TRG->AddText(buf);

		pPaveTextTDCCount_TDC->Clear();
		pPaveTextTDCCount_TDC->SetFillColor(3);
		sprintf(buf, "TDC:TDC Scaler Test(%u):", NUM_SCALER_PASSES*NUM_SCALER_PULSES);
		for(i = 0; i < 16; i++)
		{
			sprintf(&buf[strlen(buf)], " %u", TDCEdgeCounts[i]);
			if(TDCEdgeCounts[i] != NUM_SCALER_PASSES*NUM_SCALER_PULSES)
			{
				pPaveTextTDCCount_TDC->SetFillColor(2);
				result = kFALSE;
			}
		}
		pPaveTextTDCCount_TDC->AddText(buf);

		pPaveTextTDCCount_TRG->Clear();
		pPaveTextTDCCount_TRG->SetFillColor(3);
		sprintf(buf, "TDC:TRG Scaler Test(%u):", NUM_SCALER_PASSES*NUM_SCALER_PULSES);
		for(i = 0; i < 16; i++)
		{
			sprintf(&buf[strlen(buf)], " %u", TDCEdgeCounts[i]);
			if(TDCEdgeCounts[i+16] != NUM_SCALER_PASSES*NUM_SCALER_PULSES)
			{
				pPaveTextTDCCount_TRG->SetFillColor(2);
				result = kFALSE;
			}
		}
		pPaveTextTDCCount_TRG->AddText(buf);

		return result;
	}

	Bool_t Test_PulseWidth()
	{
		Bool_t result = kFALSE;
		pTextViewTesting->AddLine("*** Pulse Width Calibration ***");
		pTextViewTesting->ScrollDown(50);

		pTextViewTesting->AddLine("!!! Disconnect: all inputs |||");
		pTextViewTesting->ScrollDown(50);
		pTextViewTesting->AddLine("!!! Connect: TDC out->TDC ch0-15 !!!");
		pTextViewTesting->ScrollDown(50);
		pTextViewTesting->AddLine("!!! Connect: TRG out->TDC ch16-31 !!!");
		pTextViewTesting->ScrollDown(50);
		WaitForContinue();

		if(!CheckCalibration() ||
		   !CheckPulseWidths())
		{
			pTextViewTesting->AddLine("*** Pulse Width Calibration FAILED ***");
			pTextViewTesting->ScrollDown(50);
		}
		else
		{
			pTextViewTesting->AddLine("*** Pulse Width Calibration PASSED ***");
			pTextViewTesting->ScrollDown(50);
			result = kTRUE;
		}

		TGLongPosition p(0, pTextViewTesting->GetVirtualSize().fHeight);
		pTextViewTesting->ScrollToPosition(p);

		pCanvasTestResults->GetCanvas()->Modified();
		pCanvasTestResults->GetCanvas()->Update();

		return result;
	}

	Bool_t Test_Threshold(int ch)
	{
		Bool_t result = kFALSE;
		char buf[100];
		sprintf(buf, "*** Threshold Scan Channel %d ***", ch+1);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
/*
Arb Function Definition:
Point	Time	Voltage
1		0ns		+250mV
2		5ns		-1250mV
3		20ns	-1250mV
4		25ns	+250mV
5		100ns	+250mV
6		1600ns	-1250mV
7		1700ns	+250mV

Interpolation: ON
Offset: -750mV
Amplitude: 1500mVpp
*/
		sprintf(buf, "!!! Connect: Pulser to channel %d !!!", ch+1);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);
		pTextViewTesting->AddLine("!!! Disconnect: all other inputs |||");
		pTextViewTesting->ScrollDown(50);
		WaitForContinue();

		for(int i = 0; i < NUM_THRESHOLD_POINTS; i++)
		{
			pGraphThresholdTDC[ch]->SetPoint(i, MIN_THRESHOLD_CHECK+i*THRESHOLD_STEP, -1);
			pGraphThresholdTRG[ch]->SetPoint(i, MIN_THRESHOLD_CHECK+i*THRESHOLD_STEP, -1);
		}

		if(!CheckThreshold(ch) ||
		   !CheckThreshold(ch+16))
		{
			pTextViewTesting->AddLine("*** Threshold Scan FAILED ***");
			pTextViewTesting->ScrollDown(50);
		}
		else
		{
			pTextViewTesting->AddLine("*** Threshold Scan PASSED ***");
			pTextViewTesting->ScrollDown(50);
			result = kTRUE;
		}

		pCanvasTestResults->GetCanvas()->Modified();
		pCanvasTestResults->GetCanvas()->Update();

		return result;
	}

	Bool_t Test_Scalers()
	{
		Bool_t result = kFALSE;
		pTextViewTesting->AddLine("*** Scaler Testing ***");
		pTextViewTesting->ScrollDown(50);

		pTextViewTesting->AddLine("!!! Disconnect: all inputs |||");
		pTextViewTesting->ScrollDown(50);
		WaitForContinue();

		if(!CheckScalers())
		{
			pTextViewTesting->AddLine("*** Scaler Testing FAILED ***");
			pTextViewTesting->ScrollDown(50);
		}
		else
		{
			pTextViewTesting->AddLine("*** Scaler Testing PASSED ***");
			pTextViewTesting->ScrollDown(50);
			result = kTRUE;
		}

		pCanvasTestResults->GetCanvas()->Modified();
		pCanvasTestResults->GetCanvas()->Update();

		return result;
	}

	Bool_t Write_AssyInfo()
	{
		TDatime t;
		unsigned int id, result;
		char buf[256];
		int i;

		memset(buf, 0xff, sizeof(buf));

		sprintf(buf, "DSC2,Assy Rev: %s,Serial Num: %s,Test Date: %s", pTextEntryAssyRev->GetText(), pTextEntrySerialNumber->GetText(), t.AsString());
              
		//sprintf(buf, "DSC2,Assy Rev: C,Serial Num: 13,Test Date: Wed Sep 28 16:02:28 2011");
		//sprintf(buf, "DSC2,Assy Rev: C,Serial Num: 20,Test Date: Mon Nov 21 11:41:40 2011");
		//sprintf(buf, "DSC2,Assy Rev: C,Serial Num: 21,Test Date: Fri Nov 18 18:49:54 2011");
		//sprintf(buf, "DSC2,Assy Rev: C,Serial Num: 14,Test Date: Fri Nov 18 19:02:14 2011");
		//sprintf(buf, "DSC2,Assy Rev: C,Serial Num: 29,Test Date: Fri Nov 18 19:08:16 2011");
		//sprintf(buf, "DSC2,Assy Rev: C,Serial Num: 26,Test Date: Fri Oct 14 10:01:05 2011");

		pTextViewTesting->AddLine("*** Storing board assembly info in flash ***");
		pTextViewTesting->ScrollDown(50);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollDown(50);

		pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0x9f);
		pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 2);
		pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x30000);
		pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
		pModFrame->Delay(10);

		result = pModFrame->ReadReg32(&pDSC2regs->calCmd);
		id = pModFrame->ReadReg32(&pDSC2regs->calBuf[2]) & 0xFF;

		if(result != 0xFFFFFFFF)
		{
			pTextViewTesting->AddLine("FlashId=ERROR, no response");
			pTextViewTesting->ScrollDown(50);
			return kFALSE;
		}

		if(id == SPIFLASH_ID_NUMONYX)	// Numonyx
		{
/*
			// Erase sector first...
			pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0x06);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 1);
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x30000);
			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->pVMEClient->Delay(10);

			pModFrame->WriteReg32(&pDSC2regs->calBuf[4], ((CAL_ADDR_NUMONYX+0x1F00)>>0) & 0xFF);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[3], ((CAL_ADDR_NUMONYX+0x1F00)>>8) & 0xFF);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[2], ((CAL_ADDR_NUMONYX+0x1F00)>>16) & 0xFF);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0xD8);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 4);
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x30000);
			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->pVMEClient->Delay(3000);
			gSystem->Sleep(3000);
*/
			pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0x06);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 1);
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x30000);
			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->Delay(10);

			pModFrame->WriteReg32(&pDSC2regs->calBuf[4], ((CAL_ADDR_NUMONYX+0x1F00)>>0) & 0xFF);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[3], ((CAL_ADDR_NUMONYX+0x1F00)>>8) & 0xFF);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[2], ((CAL_ADDR_NUMONYX+0x1F00)>>16) & 0xFF);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0x02);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 256+4);
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x30000);

			for(i = 255; i >= 0; i--)
				pModFrame->WriteReg32(&pDSC2regs->calBuf[5+i], (unsigned int)buf[i]);

			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->Delay(10);
		}
		else if(id == SPIFLASH_ID_ATMEL)	// Atmel
		{
printf("Need to check/erase sector\n");
			// Write Buffer 1
			pModFrame->WriteReg32(&pDSC2regs->calBuf[4], 0x00);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[3], 0x00);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[2], 0x00);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0x84);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 256+4);
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x10000);
			for(i = 255; i >= 0; i--)
				pModFrame->WriteReg32(&pDSC2regs->calBuf[5+i], (unsigned int)buf[i]);
			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->Delay(10);

			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 256+16);
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x20000);
			for(i = 256+16-1; i >= 0; i--)
				pModFrame->WriteReg32(&pDSC2regs->calBuf[i], (unsigned int)buf[i]);
			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->Delay(10);

			// Buffer 1 -> Flash (w/o erase)
			pModFrame->WriteReg32(&pDSC2regs->calCmd, 3 | 0x30000);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[4], 0x00);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[3], 0xFC);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[2], 0x3F);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[1], 0x88);
			pModFrame->WriteReg32(&pDSC2regs->calBuf[0], 4);
			pModFrame->WriteReg32(&pDSC2regs->calExe, 0x01);
			pModFrame->Delay(10);
		}
		else
		{
			pTextViewTesting->AddLine("FlashId=ERROR, bad id");
			pTextViewTesting->ScrollDown(50);
			return kFALSE;
		}
		return kTRUE;
	}

	void WaitForContinue()
	{
		gbContinueHit = kFALSE;

		pTextViewTesting->AddLine("!!! Press Continue when ready !!!");
		pTextViewTesting->ScrollDown(50);

		pButtonTestContinue->SetEnabled(kTRUE);
		while(!gbContinueHit)
			gSystem->ProcessEvents();
		pButtonTestContinue->SetEnabled(kFALSE);
	}

	void TDCMicroWrite(unsigned short val)
	{
		unsigned short rval, i;

		for(i = 0; i < 100; i++)		
		{
			rval = pModFrame->ReadReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x1030));
			if(rval & 0x1)
				break;
		}
		pModFrame->WriteReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x102E), val);
	}

	unsigned short TDCMicroRead()
	{
		unsigned short rval, i;

		for(i = 0; i < 100; i++)		
		{
			rval = pModFrame->ReadReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x1030));
			if(rval & 0x1)
				break;
		}
		rval = pModFrame->ReadReg16((volatile unsigned int *)(pNumEntryTDCAddr->GetIntNumber()+0x102E));
		return rval;
	}

	void ClearResults()
	{
		int i, j;

		pTextViewTesting->Clear();

		pPaveTextBoardId->SetFillColor(19);
		pPaveTextTDCId->SetFillColor(19);
		pPaveTextSerialNumber->SetFillColor(19);
		pPaveTextAssemblyRev->SetFillColor(19);
		pPaveTextTestDateTime->SetFillColor(19);
		pPaveTextFirmwareRev->SetFillColor(19);
		pPaveTextTDCWidthINL->SetFillColor(19);
		pPaveTextTRGWidthINL->SetFillColor(19);
		pPaveTextTDCThresholdINL->SetFillColor(19);
		pPaveTextTRGThresholdINL->SetFillColor(19);
		pPaveTextDSCCount_TDC->SetFillColor(19);
		pPaveTextTDCCount_TDC->SetFillColor(19);
		pPaveTextDSCCount_TRG->SetFillColor(19);
		pPaveTextTDCCount_TRG->SetFillColor(19);

		pPaveTextBoardId->Clear();
		pPaveTextTDCId->Clear();
		pPaveTextSerialNumber->Clear();
		pPaveTextAssemblyRev->Clear();
		pPaveTextTestDateTime->Clear();
		pPaveTextFirmwareRev->Clear();
		//pPaveTextIn1Status->Clear();
		//pPaveTextIn2Status->Clear();
		pPaveTextDSCCount_TDC->Clear();
		pPaveTextTDCCount_TDC->Clear();
		pPaveTextDSCCount_TRG->Clear();
		pPaveTextTDCCount_TRG->Clear();
		pPaveTextTDCWidthINL->Clear();
		pPaveTextTRGWidthINL->Clear();
		pPaveTextTDCThresholdINL->Clear();
		pPaveTextTRGThresholdINL->Clear();

		pPaveTextBoardId->AddText("Board Id: ?");
		pPaveTextTDCId->AddText("TDC Board Id: ?");
		pPaveTextSerialNumber->AddText("Serial Number: ?");
		pPaveTextAssemblyRev->AddText("Assembly Rev: ?");
		pPaveTextTestDateTime->AddText("Test Date/Time: ?");
		pPaveTextFirmwareRev->AddText("Firmware Rev: ?");
		//pPaveTextIn1Status->AddText("In 1 Status: ?");
		//pPaveTextIn2Status->AddText("In 2 Status: ?");
		pPaveTextDSCCount_TDC->AddText("DSC:TDC Scaler Test: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextTDCCount_TDC->AddText("TDC:TDC Scaler Test: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextDSCCount_TRG->AddText("DSC:TRG Scaler Test: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextTDCCount_TRG->AddText("TDC:TRG Scaler Test: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextTDCWidthINL->AddText("TDC Width INL: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextTRGWidthINL->AddText("TRG Width INL: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextTDCThresholdINL->AddText("TDC Threshold INL: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
		pPaveTextTRGThresholdINL->AddText("TDC Threshold INL: ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");

		for(i = 0; i < 16; i++)
		{
			for(j = 0; j < NUM_WIDTH_POINTS; j++)
			{
				pGraphPulseWidthTDC[i]->SetPoint(j, j, -1);
				pGraphPulseWidthTRG[i]->SetPoint(j, j, -1);
			}
			for(j = 0; j < NUM_THRESHOLD_POINTS; j++)
			{
				pGraphThresholdTDC[i]->SetPoint(j, MIN_THRESHOLD_CHECK+j*THRESHOLD_STEP, -1);
				pGraphThresholdTRG[i]->SetPoint(j, MIN_THRESHOLD_CHECK+j*THRESHOLD_STEP, -1);
			}
		}

		pCanvasTestResults->GetCanvas()->Modified();
		pCanvasTestResults->GetCanvas()->Update();
	}

private:

	enum Buttons
	{
		NUM_TDCBASEADDR						= 100,
		BTN_STARTTEST							= 201,
		BTN_STOPTEST							= 202,
		BTN_SAVERESULTS						= 203,
		BTN_CLEARRESULTS						= 204,
		BTN_CONTINUE							= 205,
		EDT_RESULTSFILENAME					= 300,
		EDT_SERIALNUM							= 301,
		EDT_ASSYREV								= 302,
		COM_TESTSELECT							= 400,
		COM_TESTSELECT_STEP_VME_CHECK		= 0,
		COM_TESTSELECT_STEP_ALL				= 1,
		COM_TESTSELECT_STEP_PW_CAL			= 2,
		COM_TESTSELECT_STEP_IN1				= 4,
		COM_TESTSELECT_STEP_IN2				= 5,
		COM_TESTSELECT_STEP_THR_CH1		= 6,
		COM_TESTSELECT_STEP_THR_CH2		= 7,
		COM_TESTSELECT_STEP_THR_CH3		= 8,
		COM_TESTSELECT_STEP_THR_CH4		= 9,
		COM_TESTSELECT_STEP_THR_CH5		= 10,
		COM_TESTSELECT_STEP_THR_CH6		= 11,
		COM_TESTSELECT_STEP_THR_CH7		= 12,
		COM_TESTSELECT_STEP_THR_CH8		= 13,
		COM_TESTSELECT_STEP_THR_CH9		= 14,
		COM_TESTSELECT_STEP_THR_CH10		= 15,
		COM_TESTSELECT_STEP_THR_CH11		= 16,
		COM_TESTSELECT_STEP_THR_CH12		= 17,
		COM_TESTSELECT_STEP_THR_CH13		= 18,
		COM_TESTSELECT_STEP_THR_CH14		= 19,
		COM_TESTSELECT_STEP_THR_CH15		= 20,
		COM_TESTSELECT_STEP_THR_CH16		= 21,
		COM_TESTSELECT_STEP_SCALER			= 22,
		COM_WRITE_ASSY_INFO					= 23
	};
	
	Bool_t					gbContinueHit;
	Bool_t					gbStopHit;

	ModuleFrame				*pModFrame;
	DSC2_regs				*pDSC2regs;

	TRootEmbeddedCanvas		*pCanvasTestResults;
	
	TGNumberEntry			*pNumEntryTDCAddr;

	TGTextEntry				*pTextEntryResultsFile;
	TGTextEntry				*pTextEntrySerialNumber;
	TGTextEntry				*pTextEntryAssyRev;

	TGTextButton			*pButtonStart;
	TGTextButton			*pButtonStop;
	TGTextButton			*pButtonSaveResults;
	TGTextButton			*pButtonClearResults;
	TGTextButton			*pButtonTestContinue;

	TGTextView				*pTextViewTesting;

	TGComboBox				*pComboTestSelect;

	TPad					*pPadPulseWidthTDC;
	TPad					*pPadPulseWidthTRG;
	TPad					*pPadThresholdTDC;
	TPad					*pPadThresholdTRG;

	TPaveText				*pPaveTextTitle;
	TPaveText				*pPaveTextBoardId;
	TPaveText				*pPaveTextTDCId;
	TPaveText				*pPaveTextSerialNumber;
	TPaveText				*pPaveTextAssemblyRev;
	TPaveText				*pPaveTextTestDateTime;
	TPaveText				*pPaveTextFirmwareRev;
	//TPaveText				*pPaveTextIn1Status;
	//TPaveText				*pPaveTextIn2Status;
	TPaveText				*pPaveTextDSCCount_TDC;
	TPaveText				*pPaveTextTDCCount_TDC;
	TPaveText				*pPaveTextDSCCount_TRG;
	TPaveText				*pPaveTextTDCCount_TRG;
	TPaveText				*pPaveTextTDCWidthINL;
	TPaveText				*pPaveTextTRGWidthINL;
	TPaveText				*pPaveTextTDCThresholdINL;
	TPaveText				*pPaveTextTRGThresholdINL;

	TMultiGraph				*pMGraphPulseWidthTDC;
	TMultiGraph				*pMGraphPulseWidthTRG;
	TMultiGraph				*pMGraphThresholdTDC;
	TMultiGraph				*pMGraphThresholdTRG;

	TGraph					*pGraphPulseWidthTDCMaskMin;
	TGraph					*pGraphPulseWidthTRGMaskMin;
	TGraph					*pGraphPulseWidthTDCMaskMax;
	TGraph					*pGraphPulseWidthTRGMaskMax;
	TGraph					*pGraphPulseWidthIdeal;
	TGraph					*pGraphPulseWidthTDC[16];
	TGraph					*pGraphPulseWidthTRG[16];

	TGraph					*pGraphThresholdIdeal;
	TGraph					*pGraphThresholdMaskMin;
	TGraph					*pGraphThresholdMaskMax;
	TGraph					*pGraphThresholdTDC[16];
	TGraph					*pGraphThresholdTRG[16];
};

#endif
