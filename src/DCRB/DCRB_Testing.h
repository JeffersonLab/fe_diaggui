#ifndef DCRB_Testing_H
#define DCRB_Testing_H

#include <math.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRB.h"

#define DCRB_BASE_ADDR_A32			0x08000000

#define READOUT_BUF_SIZE			2*1024*1024

class DCRB_Testing : public TGCompositeFrame
{
public:
	DCRB_Testing(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		TGCompositeFrame *tF1, *tF2;
		int i;

		SetLayoutManager(new TGVerticalLayout(this));
		pM = pModule;
		pRegs = (DCRB_regs *)pM->BaseAddr;
		
		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(pTextViewTesting = new TGTextView(tF1), new TGLayoutHints(kLHintsExpandX));
				pTextViewTesting->SetHeight(50);
			tF1->AddFrame(pButtonStart = new TGTextButton(tF1, "Start", BTN_STARTTEST), new TGLayoutHints(kLHintsNormal));
				pButtonStart->SetWidth(120);
				pButtonStart->Associate(this);
			tF1->AddFrame(pButtonStop = new TGTextButton(tF1, "Stop", BTN_STOPTEST), new TGLayoutHints(kLHintsNormal));
				pButtonStop->SetWidth(120);
				pButtonStop->Associate(this);
				pButtonStop->SetEnabled(kFALSE);
			tF1->AddFrame(pButtonContinue = new TGTextButton(tF1, "Continue", BTN_CONTINUETEST), new TGLayoutHints(kLHintsNormal));
				pButtonContinue->SetWidth(120);
				pButtonContinue->Associate(this);
				pButtonContinue->SetEnabled(kFALSE);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(new TGLabel(tF1, "Test Results Filename:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
			tF1->AddFrame(pTextEntryResultsFile = new TGTextEntry(tF1, "STB_TestResult", EDT_RESULTSFILENAME), new TGLayoutHints(kLHintsRight));
				pTextEntryResultsFile->SetWidth(200);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(new TGLabel(tF1, "Test Pulse Count:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF1->AddFrame(pNumEntryTestPulseCount = new TGNumberEntry(tF1, 1000, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 99999.0), new TGLayoutHints(kLHintsRight));
					pNumEntryTestPulseCount->SetWidth(85);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(new TGLabel(tF1, "TDC Checking(trg->pulse timing in ns)):"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsRight));
				tF2->AddFrame(new TGLabel(tF2, "Min:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pNumEntryTDCTmin = new TGNumberEntry(tF2, -1000, 4, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -32000, 0), new TGLayoutHints(kLHintsRight));
					pNumEntryTDCTmin->SetWidth(85);
			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsRight));
				tF2->AddFrame(new TGLabel(tF2, "Max:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pNumEntryTDCTmax = new TGNumberEntry(tF2, -1000, 4, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, -32000, 0), new TGLayoutHints(kLHintsRight));
					pNumEntryTDCTmax->SetWidth(85);
			tF1->AddFrame(pButtonTDCEnable = new TGTextButton(tF1, "Enable"), new TGLayoutHints(kLHintsRight, 2, 0, 2));
				pButtonTDCEnable->AllowStayDown(kTRUE);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(new TGLabel(tF1, "Scaler Checking(hit counts):"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsRight));
				tF2->AddFrame(new TGLabel(tF2, "Min:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pNumEntryScalermin = new TGNumberEntry(tF2, 1000, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 99999.0), new TGLayoutHints(kLHintsRight));
					pNumEntryScalermin->SetWidth(85);
			tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsRight));
				tF2->AddFrame(new TGLabel(tF2, "Max:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF2->AddFrame(pNumEntryScalermax = new TGNumberEntry(tF2, 1000, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 99999.0), new TGLayoutHints(kLHintsRight));
					pNumEntryScalermax->SetWidth(85);
			tF1->AddFrame(pButtonScalerEnable = new TGTextButton(tF1, "Enable"), new TGLayoutHints(kLHintsRight, 2, 0, 2));
				pButtonScalerEnable->AllowStayDown(kTRUE);
				pButtonScalerEnable->SetDown(kTRUE);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(new TGLabel(tF1, "Discriminator Threshold(mV):"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
				tF1->AddFrame(pNumEntryThreshold = new TGNumberEntry(tF1, 100, 4, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 175.0), new TGLayoutHints(kLHintsRight));
					pNumEntryThreshold->SetWidth(85);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(new TGLabel(tF1, "Calibration Pulser:"), new TGLayoutHints(kLHintsLeft, 2, 0, 2));
			tF1->AddFrame(pButtonCalSequential = new TGTextButton(tF1, "Sequential", BTN_SEQUENTIAL), new TGLayoutHints(kLHintsRight, 2, 0, 2));
				pButtonCalSequential->AllowStayDown(kTRUE);
				pButtonCalSequential->SetDown(kFALSE);
				pButtonCalSequential->Associate(this);
			tF1->AddFrame(pButtonCalSimultaneous = new TGTextButton(tF1, "Simultaneous", BTN_SIMULTANEOUS), new TGLayoutHints(kLHintsRight, 2, 0, 2));
				pButtonCalSimultaneous->AllowStayDown(kTRUE);
				pButtonCalSimultaneous->SetDown(kTRUE);
				pButtonCalSimultaneous->Associate(this);

		AddFrame(pCanvasScalers = new TRootEmbeddedCanvas("DCRB Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasScalers->GetCanvas()->SetBorderMode(0);
				pHistScalers = new TH1I("DCRB Scalers", "DCRB Scalers;Channel;Hits", 96, 0, 95);
				pHistScalers->SetFillColor(4);
/*
		AddFrame(pCanvasTDCMin = new TRootEmbeddedCanvas("DCRB TDC Min", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasTDCMin->GetCanvas()->SetBorderMode(0);
				pHistTDCMin = new TH1I("DCRB TDC Min", "DCRB TDC Min;Channel;Tmin(ns)", 96, 0, 95);
				pHistTDCMin->SetFillColor(4);

		AddFrame(pCanvasTDCMax = new TRootEmbeddedCanvas("DCRB TDC Max", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasTDCMax->GetCanvas()->SetBorderMode(0);
				pHistTDCMax = new TH1I("DCRB TDC Max", "DCRB TDC Max;Channel;Tmax(ns)", 96, 0, 95);
				pHistTDCMax->SetFillColor(4);

		AddFrame(pCanvasTDCRMS = new TRootEmbeddedCanvas("DCRB TDC RMS", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasTDCRMS->GetCanvas()->SetBorderMode(0);
				pHistTDCRMS = new TH1I("DCRB TDC RMS", "DCRB TDC RMS;Channel;Trms(ns)", 96, 0, 95);
				pHistTDCRMS->SetFillColor(4);

		AddFrame(pCanvasTDCHits = new TRootEmbeddedCanvas("DCRB TDC Hits", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasTDCHits->GetCanvas()->SetBorderMode(0);
				pHistTDCHits = new TH1I("DCRB TDC Hits", "DCRB TDC Hits;Channel;Hits", 96, 0, 95);
				pHistTDCHits->SetFillColor(4);
*/
		for(i = 0; i < 96; i++)
		{
			pHistScalers->SetBinContent(i, 0);
/*			pHistTDCMin->SetBinContent(i, 0);
			pHistTDCMax->SetBinContent(i, 0);
			pHistTDCRMS->SetBinContent(i, 0);
			pHistTDCHits->SetBinContent(i, 0);*/
		}
		pCanvasScalers->GetCanvas()->cd();
		pHistScalers->Draw("bar0");
/*		pCanvasTDCMin->GetCanvas()->cd();
		pHistTDCMin->Draw("bar0");
		pCanvasTDCMax->GetCanvas()->cd();
		pHistTDCMax->Draw("bar0");
		pCanvasTDCRMS->GetCanvas()->cd();
		pHistTDCRMS->Draw("bar0");
		pCanvasTDCHits->GetCanvas()->cd();
		pHistTDCHits->Draw("bar0");
*/	}

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
					case BTN_SEQUENTIAL:
						pButtonCalSequential->SetDown(kTRUE);
						pButtonCalSimultaneous->SetDown(kFALSE);
						break;
					case BTN_SIMULTANEOUS:
						pButtonCalSequential->SetDown(kFALSE);
						pButtonCalSimultaneous->SetDown(kTRUE);
						break;
					case BTN_STARTTEST:
						pButtonStart->SetEnabled(kFALSE);
						pButtonStop->SetEnabled(kTRUE);
//						pButtonCalSequential->SetEnabled(kFALSE);
//						pButtonCalSimultaneous->SetEnabled(kFALSE);
						pNumEntryThreshold->SetEditable(kFALSE);
						pTextEntryResultsFile->SetEnabled(kFALSE);
						pNumEntryTestPulseCount->SetEditable(kFALSE);
						pNumEntryTDCTmax->SetEditable(kFALSE);
						pNumEntryTDCTmin->SetEditable(kFALSE);
						pNumEntryScalermax->SetEditable(kFALSE);
						pNumEntryScalermin->SetEditable(kFALSE);
//						pButtonTDCEnable->SetEnabled(kFALSE);
//						pButtonScalerEnable->SetEnabled(kFALSE);

						gbStopHit = kFALSE;
						RunTest();

						pButtonStart->SetEnabled(kTRUE);
						pButtonStop->SetEnabled(kFALSE);
//						pButtonCalSequential->SetEnabled(kTRUE);
//						pButtonCalSimultaneous->SetEnabled(kTRUE);
						pNumEntryThreshold->SetEditable(kTRUE);
						pTextEntryResultsFile->SetEnabled(kTRUE);
						pNumEntryTestPulseCount->SetEditable(kTRUE);
						pNumEntryTDCTmax->SetEditable(kTRUE);
						pNumEntryTDCTmin->SetEditable(kTRUE);
						pNumEntryScalermax->SetEditable(kTRUE);
						pNumEntryScalermin->SetEditable(kTRUE);
//						pButtonTDCEnable->SetEnabled(kTRUE);
//						pButtonScalerEnable->SetEnabled(kTRUE);
						break;
					case BTN_STOPTEST:
						sprintf(buf, "*** STOP PRESSED - QUITTING TEST ***");
						pTextViewTesting->AddLine(buf);
						pTextViewTesting->ScrollUp(50);
						gbStopHit = kTRUE;
						break;
					case BTN_CONTINUETEST:
						gbContinueHit = kTRUE;
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
				break;
			}
			break;
		}
		return kTRUE;
	}

	void RunTest()
	{
		unsigned int val;
		char buf[200];

		pTextViewTesting->AddLine("Setup pulser: desired pulse shape/height");
		pTextViewTesting->AddLine("Setup pulser: Manual burst mode, 10us period");
		pTextViewTesting->AddLine("Setup pulser: ChA 1us delay LVDS into DCRB trigger input");
		pTextViewTesting->AddLine("Setup pulser: ChB 0us delay LVDS into DCRB calibration input");
		pTextViewTesting->ScrollUp(100);

		sprintf(buf, "Opening results file: %s", pTextEntryResultsFile->GetText());
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollUp(100);

		for(int i = 0; i < 96; i++)
		{
			pHistScalers->SetBinContent(i, 0);
/*			pHistTDCMin->SetBinContent(i, 0);
			pHistTDCMax->SetBinContent(i, 0);
			pHistTDCRMS->SetBinContent(i, 0);
			pHistTDCHits->SetBinContent(i, 0);*/
		}
/*		pCanvasTDCMin->GetCanvas()->Modified();
		pCanvasTDCMax->GetCanvas()->Modified();
		pCanvasTDCRMS->GetCanvas()->Modified();
		pCanvasTDCHits->GetCanvas()->Modified();*/
		pCanvasScalers->GetCanvas()->Modified();
/*		pCanvasTDCMin->GetCanvas()->Update();
		pCanvasTDCMax->GetCanvas()->Update();
		pCanvasTDCRMS->GetCanvas()->Update();
		pCanvasTDCHits->GetCanvas()->Update();*/
		pCanvasScalers->GetCanvas()->Update();

		FILE *f = fopen(pTextEntryResultsFile->GetText(), "a+t");
		if(!f)
		{
			sprintf(buf, "Failed to open.");
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollUp(100);
			return;
		}

		TDatime t;
		fprintf(f, "// File: %s\n", pTextEntryResultsFile->GetText());
		fprintf(f, "// Tested: %s\n", t.AsString());
		fprintf(f, "// Pulse Count: %ld\n", pNumEntryTestPulseCount->GetIntNumber());
		fprintf(f, "// TDC Checks: %s Max: %ld Min %ld\n", pButtonTDCEnable->IsDown() ? "Enabled" : "Disabled", pNumEntryTDCTmax->GetIntNumber(), pNumEntryTDCTmin->GetIntNumber());
		fprintf(f, "// Scaler Checks: %s Max: %ld Min %ld\n", pButtonScalerEnable->IsDown() ? "Enabled" : "Disabled", pNumEntryScalermax->GetIntNumber(), pNumEntryScalermin->GetIntNumber());
		fprintf(f, "// Discriminator Threshold: %ldmV\n", pNumEntryThreshold->GetIntNumber());
		fprintf(f, "// Calibration Pulser Mode: %s\n", pButtonCalSequential->IsDown() ? "Sequential" : "Simultaneous");

		pM->WriteReg32(&pRegs->DACConfig, ((unsigned int)pNumEntryThreshold->GetIntNumber() * 24489360)>>18);
		pM->WriteReg32(&pRegs->ADR32, ((DCRB_BASE_ADDR_A32>>16) & 0xFF80) | 0x0001);
		pM->WriteReg32(&pRegs->LookBack, 2000);
		pM->WriteReg32(&pRegs->WindowWidth, 2000);
		pM->WriteReg32(&pRegs->BlockConfig, 1);
		pM->WriteReg32(&pRegs->TDCConfig, 32);
		pM->WriteReg32(&pRegs->ClockConfig, 0);
		pM->WriteReg32(&pRegs->ReadoutConfig, 0x00000001);
		pM->WriteReg32(&pRegs->ChDisable[0], 0);
		pM->WriteReg32(&pRegs->ChDisable[1], 0);
		pM->WriteReg32(&pRegs->ChDisable[2], 0);
		pM->WriteReg32(&pRegs->TriggerSource, 0x11);
		
		for(int i = 0; i < 6; i++)
		{
			if(pButtonCalSequential->IsDown())
				pM->WriteReg32(&pRegs->TestPulseConfig, 1<<(i+6));
			else
				pM->WriteReg32(&pRegs->TestPulseConfig, 0x3F<<6);

			if(pButtonTDCEnable->IsDown())
			{
				pM->WriteReg32(&pRegs->Reset, 1);
				val = pM->ReadReg32(&pRegs->TriggerSource);
				pM->WriteReg32(&pRegs->TriggerSource, val | 0x800);
			}

			if(pButtonScalerEnable->IsDown())
				pM->WriteReg32(&pRegs->ScalerLatch, 0);

			sprintf(buf, "Send manual burst of %ld pulses", pNumEntryTestPulseCount->GetIntNumber());
			pTextViewTesting->AddLine(buf);
			pTextViewTesting->ScrollUp(100);

			gbContinueHit = kFALSE;
			pButtonContinue->SetEnabled(kTRUE);
			while(!gbContinueHit)
			{
				gSystem->ProcessEvents();
				if(gbStopHit)
				{
					pButtonContinue->SetEnabled(kFALSE);
					fclose(f);
					return;
				}
			}
			pButtonContinue->SetEnabled(kFALSE);

			if(pButtonScalerEnable->IsDown())
			{
				pM->WriteReg32(&pRegs->ScalerLatch, 0);
				if(pButtonCalSequential->IsDown())
				{
					for(int j = 0; j < 16; j++)
						pHistScalers->SetBinContent(i*16+j, pM->ReadReg32(&pRegs->Scalers[i*16+j]));
				}
				else
				{
					for(int j = 0; j < 96; j++)
						pHistScalers->SetBinContent(j, pM->ReadReg32(&pRegs->Scalers[j]));
				}
				pCanvasScalers->GetCanvas()->Modified();
				pCanvasScalers->GetCanvas()->Update();
			}

			if(pButtonTDCEnable->IsDown())
			{
				val = pM->ReadReg32(&pRegs->FifoEventCnt);
				if(val != pNumEntryTestPulseCount->GetIntNumber())
				{
					sprintf(buf, "Error: received %d events, but expected %ld", val, pNumEntryTestPulseCount->GetIntNumber());
					pTextViewTesting->AddLine(buf);
					pTextViewTesting->ScrollUp(100);
					fclose(f);
					return;
				}

				val = pM->ReadReg32(&pRegs->FifoWordCnt);
				sprintf(buf, "FIFO Event Buffer Length: %u\n", val);
				pTextViewTesting->AddLine(buf);
				pTextViewTesting->ScrollUp(100);

				unsigned int *pReadoutBuffer = (unsigned int *)malloc(READOUT_BUF_SIZE);

				int ReadoutBufferLength, bytes_left = -1;
				unsigned int tdcMin[96], tdcMax[96], tdcHit[96], tdcRMS[96];
				memset(tdcMin, 0, sizeof(tdcMin));
				memset(tdcMax, 0, sizeof(tdcMax));
				memset(tdcHit, 0, sizeof(tdcHit));
				memset(tdcRMS, 0, sizeof(tdcRMS));
				//if(pM->pVMEClient->BlkReadVME_DMA(DCRB_BASE_ADDR_A32, pReadoutBuffer, READOUT_BUF_SIZE, VME_DMA_BLT32, &bytes_left) && bytes_left >= 0)
				if(0)	// need to fix this....
				{
					ReadoutBufferLength = (READOUT_BUF_SIZE-bytes_left)/4;

					for(int j = 0; j < ReadoutBufferLength; j++)
					{
						if(pReadoutBuffer[j] & 0x80000000)					// Data type define flag
						{
							if(((pReadoutBuffer[j]>>27) & 0xF) == 0x08)		// TDC hit
							{
								unsigned int ch = (pReadoutBuffer[j]>>16) & 0x7F;
								unsigned int t = pReadoutBuffer[j] & 0xFFFF;

								if(ch < 96)
								{
									tdcHit[ch]++;
									if((tdcMin[ch] == 0) || (t < tdcMin[ch]))
										tdcMin[ch] = t;
									if((tdcMax[ch] == 0) || (t > tdcMax[ch]))
										tdcMax[ch] = t;
									tdcRMS[ch] += t*t;
								}
								else
								{
									sprintf(buf, "Error: invalid tdc channel reported %u\n", ch);
									pTextViewTesting->AddLine(buf);
									pTextViewTesting->ScrollUp(100);
								}
							}
						}
					}

					if(pButtonCalSequential->IsDown())
					{
						for(int j = 0; j < 16; j++)
						{
							pHistTDCMin->SetBinContent(i*16+j, tdcMin[i*16+j]);
							pHistTDCMax->SetBinContent(i*16+j, tdcMax[i*16+j]);
							pHistTDCRMS->SetBinContent(i*16+j, sqrt((float)tdcRMS[i*16+j]));
							pHistTDCHits->SetBinContent(i*16+j, tdcHit[i*16+j]);
						}
					}
					else
					{
						for(int j = 0; j < 96; j++)
						{
							pHistTDCMin->SetBinContent(j, tdcMin[j]);
							pHistTDCMax->SetBinContent(j, tdcMax[j]);
							pHistTDCRMS->SetBinContent(j, sqrt((float)tdcRMS[j]));
							pHistTDCHits->SetBinContent(j, tdcHit[j]);
						}
					}
					pCanvasTDCMin->GetCanvas()->Modified();
					pCanvasTDCMax->GetCanvas()->Modified();
					pCanvasTDCRMS->GetCanvas()->Modified();
					pCanvasTDCHits->GetCanvas()->Modified();
					pCanvasTDCMin->GetCanvas()->Update();
					pCanvasTDCMax->GetCanvas()->Update();
					pCanvasTDCRMS->GetCanvas()->Update();
					pCanvasTDCHits->GetCanvas()->Update();
				}
				else
				{
					sprintf(buf, "Error: BlkReadVME_DMA failed\n");
					pTextViewTesting->AddLine(buf);
					pTextViewTesting->ScrollUp(100);
				}
				free(pReadoutBuffer);
				
				///////// RANGE CHECKING FOR TDC DATA /////////////
				///////// RANGE CHECKING FOR TDC DATA /////////////
				///////// RANGE CHECKING FOR TDC DATA /////////////
				///////// RANGE CHECKING FOR TDC DATA /////////////
				///////// RANGE CHECKING FOR TDC DATA /////////////
				///////// RANGE CHECKING FOR TDC DATA /////////////
			}

			if(!pButtonCalSequential->IsDown())
				break;
		}

		Bool_t bFailed = kFALSE;

		if(pButtonScalerEnable->IsDown())
		{
			for(int i = 0; i < 96; i++)
			{
				int counts = (int)pHistScalers->GetBinContent(i);
				fprintf(f, "Scaler channel %d: %u received, %lu expected", i, counts, pNumEntryTestPulseCount->GetIntNumber());
				if(counts < pNumEntryScalermin->GetIntNumber())
				{
					fprintf(f, " Failed min check (%lu)", pNumEntryScalermin->GetIntNumber());
					bFailed = kTRUE;
				}
				if(counts > pNumEntryScalermax->GetIntNumber())
				{
					fprintf(f, " Failed max check (%lu)", pNumEntryScalermax->GetIntNumber());
					bFailed = kTRUE;
				}
				fprintf(f, "\n");
			}
		}

		sprintf(buf, "Testing Completed: Status = %s", bFailed ? "FAILED" : "PASSED");
		fprintf(f, "%s\n", buf);
		pTextViewTesting->AddLine(buf);
		pTextViewTesting->ScrollUp(100);

		fclose(f);
	}

private:

	enum Buttons
	{
		BTN_STARTTEST,
		BTN_STOPTEST,
		BTN_CONTINUETEST,
		BTN_SEQUENTIAL,
		BTN_SIMULTANEOUS,
		EDT_RESULTSFILENAME
	};
	
	ModuleFrame			*pM;
	DCRB_regs			*pRegs;

	TGTextButton		*pButtonCalSequential;
	TGTextButton		*pButtonCalSimultaneous;
	TGTextButton		*pButtonTDCEnable;
	TGTextButton		*pButtonScalerEnable;
	TGTextEntry			*pTextEntryResultsFile;
	TGNumberEntry		*pNumEntryTestPulseCount;
	TGNumberEntry		*pNumEntryTDCTmin;
	TGNumberEntry		*pNumEntryTDCTmax;
	TGNumberEntry		*pNumEntryScalermin;
	TGNumberEntry		*pNumEntryScalermax;
	TGNumberEntry		*pNumEntryThreshold;
	TRootEmbeddedCanvas	*pCanvasTDCMin;
	TRootEmbeddedCanvas	*pCanvasTDCMax;
	TRootEmbeddedCanvas	*pCanvasTDCRMS;
	TRootEmbeddedCanvas	*pCanvasTDCHits;
	TRootEmbeddedCanvas	*pCanvasScalers;
	TH1I				*pHistScalers;
	TH1I				*pHistTDCHits;
	TH1I				*pHistTDCRMS;
	TH1I				*pHistTDCMax;
	TH1I				*pHistTDCMin;
	TGTextButton		*pButtonStart;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonContinue;
	TGTextView			*pTextViewTesting;

	Bool_t				gbContinueHit;
	Bool_t				gbStopHit;
};

#endif
