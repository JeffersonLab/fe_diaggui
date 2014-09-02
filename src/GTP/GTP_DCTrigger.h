#ifndef GTP_DCTrigger_H
#define GTP_DCTrigger_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "gtp.h"

class GTP_DCTrigger	: public TGCompositeFrame
{
public:
	GTP_DCTrigger(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;

		TGCompositeFrame		*pF1;

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pF1->AddFrame(pButtonAutoTrigger = new TGTextButton(pF1, new TGHotString("Update Mode: Manual"), BTN_WAVE_AUTOTRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoTrigger->SetWidth(80);
				pButtonAutoTrigger->SetEnabled(kTRUE);
				pButtonAutoTrigger->AllowStayDown(kTRUE);
				pButtonAutoTrigger->Associate(this);
			pF1->AddFrame(pButtonStartTrigger = new TGTextButton(pF1, new TGHotString("Start Trigger"), BTN_WAVE_STARTTRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonStartTrigger->Associate(this);
			pF1->AddFrame(pButtonStopTrigger = new TGTextButton(pF1, new TGHotString("Stop Trigger"), BTN_WAVE_STOPTRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonStopTrigger->SetEnabled(kFALSE);
				pButtonStopTrigger->Associate(this);
			pF1->AddFrame(pButtonForceTrigger = new TGTextButton(pF1, new TGHotString("Force Trigger"), BTN_WAVE_FORCETRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));		
				pButtonForceTrigger->Associate(this);
			pF1->AddFrame(pButtonTest = new TGTextButton(pF1, new TGHotString("Test"), BTN_TEST), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));		
				pButtonTest->Associate(this);

			pF1->AddFrame(pLabelThreshold = new TGLabel(pF1, new TGString("HitThreshold(0):")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			pF1->AddFrame(pSliderThreshold = new TGHSlider(pF1, 100, kSlider1 | kScaleBoth, SDR_TRG_THRESHOLD), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderThreshold->SetRange(0, 6);
				pSliderThreshold->SetPosition(0);
				pSliderThreshold->Associate(this);			

		for(int i = 0; i < 2; i++)
		{
			AddFrame(pCanvas[i] = new TRootEmbeddedCanvas("DCTrigger", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvas[i]->GetCanvas()->SetBorderMode(0);
			
				pCanvas[i]->GetCanvas()->SetMargin(0.05, 0.1, 0.05, 0.05);
				
				pScalers[i] = new TH2Poly();
				Honeycomb(pScalers[i], -0.5, -0.5773502692, 0.5773502692, 112, 6);
				pScalers[i]->GetXaxis()->SetNdivisions(112, kTRUE);
				pScalers[i]->GetXaxis()->SetLabelSize(0.04);
				//pScalers[i]->GetXaxis()->SetTickLength(1);
				pScalers[i]->GetYaxis()->SetNdivisions(6, kTRUE);
				pScalers[i]->GetYaxis()->SetLabelSize(0.04);
				//pScalers[i]->GetYaxis()->SetTickLength(1);
				pScalers[i]->SetStats(kFALSE);
				pScalers[i]->SetBarOffset(0.0);
				pScalers[i]->SetBarWidth(0.25);
		}
		pScalers[0]->SetTitle("SuperLayer-1");
//		pScalers[0]->SetTitleSize(0.002);
		pScalers[1]->SetTitle("SuperLayer-2");
//		pScalers[1]->SetTitleSize(0.002);
		
		UpdateDCHitPlot(kFALSE);
		
		pTimerUpdate = new TTimer(this, 100, kTRUE);
	}

	void Honeycomb(TH2Poly *pH, Double_t xstart, Double_t ystart, Double_t a, Int_t k, Int_t s)
	{
		// Bins the histogram using a honeycomb structure
		// Add the bins
		Double_t x[6], y[6];
		Double_t xloop, yloop, xtemp;
		xloop = xstart; yloop = ystart + a/2.0;
		for(int sCounter = 0; sCounter < s; sCounter++)
		{
			xtemp = xloop; // Resets the temp variable

			for(int kCounter = 0; kCounter <  k; kCounter++)
			{
				// Go around the hexagon
				x[0] = xtemp;
				y[0] = yloop;
				x[1] = x[0];
				y[1] = y[0] + a;
				x[2] = x[1] + a*TMath::Sqrt(3)/2.0;
				y[2] = y[1] + a/2.0;
				x[3] = x[2] + a*TMath::Sqrt(3)/2.0;
				y[3] = y[1];
				x[4] = x[3];
				y[4] = y[0];
				x[5] = x[2];
				y[5] = y[4] - a/2.0;

				pH->AddBin(6, x, y);

				// Go right
				xtemp += a*TMath::Sqrt(3);
			}

			// Increment the starting position
			if (sCounter%2 == 1) xloop += a*TMath::Sqrt(3)/2.0;
			else                 xloop -= a*TMath::Sqrt(3)/2.0;
			yloop += 1.5*a;
		}
		x[0] = -1.0; y[0] = 0.0;
		x[1] = -1.0; y[1] = 0.05;
		x[2] = -0.95; y[2] = 0.05;
		x[3] = -0.95; y[3] = 0.0;
		pH->AddBin(4, x, y);

		x[0] = -0.95; y[0] = 0.0;
		x[1] = -0.95; y[1] = 0.05;
		x[2] = -0.90; y[2] = 0.05;
		x[3] = -0.90; y[3] = 0.0;
		pH->AddBin(4, x, y);
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_HSLIDER:
			switch(parm1)
			{
				case SDR_TRG_THRESHOLD:
				{
					TGString *pStr = new TGString;
					pStr->Form("HitThreshold(%d):", pSliderThreshold->GetPosition());
					pLabelThreshold->SetText(pStr);
					break;
				}
				default:
					printf("slider id %d pressed\n", (int)parm1);
					break;
			}
			break;
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_WAVE_AUTOTRIG:
						if(pButtonAutoTrigger->IsDown())
							pButtonAutoTrigger->SetText(new TGHotString("Update Mode: Auto"));
						else
							pButtonAutoTrigger->SetText(new TGHotString("Update Mode: Manual"));
						break;
					case BTN_WAVE_STARTTRIG:
						pButtonStartTrigger->SetEnabled(kFALSE);
						pButtonStopTrigger->SetEnabled(kTRUE);
						SetTrigger();
						pTimerUpdate->Start(100, kTRUE);
						break;
					case BTN_WAVE_STOPTRIG:
						pButtonForceTrigger->SetEnabled(kTRUE);
						pButtonStartTrigger->SetEnabled(kTRUE);
						pButtonStopTrigger->SetEnabled(kFALSE);
						pTimerUpdate->TurnOff();
						break;
					case BTN_WAVE_FORCETRIG:
						pButtonForceTrigger->SetEnabled(kFALSE);
						SetTrigger(kTRUE);
						pTimerUpdate->Start(100, kTRUE);
						break;
					case BTN_TEST:
						Test();
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
///////////////////////////////////////

	void Test()
	{
		unsigned int result = pM->ReadReg32(&pRegs->Trg.DcMonData[0]);
		printf("Test() returned 0x%08X\n", result);
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
			//poll trigger ready bit...should add a DCTrig status and poll that instead of serdes mon
			unsigned int status = pM->ReadReg32(&pRegs->Trg.StatusDcMon);

			if(status & 0x80)
			{
				UpdateDCHitPlot();
				if(pButtonAutoTrigger->IsDown())
				{
					SetTrigger();
					pTimerUpdate->Start(100, kTRUE);
				}
				else
				{
					pButtonForceTrigger->SetEnabled(kTRUE);
					pButtonStartTrigger->SetEnabled(kTRUE);
					pButtonStopTrigger->SetEnabled(kFALSE);
				}
			}
			else
				pTimerUpdate->Start(100, kTRUE);
		}
		return kTRUE;
	}

	void SetTrigger(Bool_t force = kFALSE)
	{
		// setup monitor...
		pM->WriteReg32(&pRegs->Trg.CtrlDcMon, 0);			// disable dc trig mon
		
		pM->WriteReg32(&pRegs->Trg.CtrlDcTrg, pSliderThreshold->GetPosition());
		
		for(int i = 0; i < 14; i++)
			pM->WriteReg32(&pRegs->Trg.DcMonMask[i], 0);

		pM->WriteReg32(&pRegs->Trg.CtrlDcMon, 0x73FFF);			// enable dc trig mon - SL1 and SL2
//		pM->WriteReg32(&pRegs->Trg.CtrlDcMon, 0x33FFF);			// enable dc trig mon - SL1
//		pM->WriteReg32(&pRegs->Trg.CtrlDcMon, 0x53FFF);			// enable dc trig mon - SL2
	}

#define DCHIT_PLOT_MIN	-512
#define DCHIT_PLOT_MAX	2048

	void UpdateDCHitPlot(Bool_t readRegs = kTRUE)
	{
		int i, j, k, ch;

		for(k = 0; k < 2; k++)
		for(i = 0; i < 112; i++)
		for(j = 0; j < 6; j++)
			sl_hits[k][i][j] = DCHIT_PLOT_MIN;
		
		if(readRegs)
			pM->WriteReg32(&pRegs->Trg.CtrlDcMon, 0);			// disable dc trig mon

		for(i = 0; i < 14; i++)
		{
			unsigned int hits[512];
			if(readRegs)
				pM->BlkReadReg32(&pRegs->Trg.DcMonData[i], hits, 512, CRATE_MSG_FLAGS_NOADRINC);
			else
				memset(hits, 0, sizeof(hits));
			
			for(j = 0; j < 512; j++)
			{
				unsigned int h = hits[j] & 0xFFFFFF;
				unsigned int idx = (hits[j]>>24) & 0x3;

				if(!h)
					continue;

				for(k = 0; k < 24; k++)
				{
					if(h & (1<<k))
					{
						ch = idx*24+k;
						int x = 16.0*(i%7)+(ch/6);
						int y = (ch % 6);
						
						if(y < 3)
							y = y*2+1;
						else
							y = (y-3)*2;
						
						if(sl_hits[i/7][x][y] == DCHIT_PLOT_MIN)
						{
							if(j*8 > DCHIT_PLOT_MAX)
								sl_hits[i/7][x][y] = DCHIT_PLOT_MAX;
							else
								sl_hits[i/7][x][y] = j*8;
						}
					}
				}
			}
		}

		for(i = 0; i < 2; i++)
		{
			pScalers[i]->Reset("");
			for(j = 0; j < 112; j++)
			for(k = 0; k < 6; k++)
				pScalers[i]->Fill(-0.25+(double)j, 0.866*k, sl_hits[i][j][k]);

			pScalers[i]->Fill(-0.975, 0.025, DCHIT_PLOT_MIN);
			pScalers[i]->Fill(-0.925, 0.025, DCHIT_PLOT_MAX);

			pCanvas[i]->GetCanvas()->cd();
			pCanvas[i]->GetCanvas()->Clear();
			pScalers[i]->Draw("COLZTEXT");
			//pScalers[i]->GetZaxis()->SetLabelSize(0.06);
			pCanvas[i]->GetCanvas()->Modified();
			pCanvas[i]->GetCanvas()->Update();
		}
		
		pButtonForceTrigger->SetEnabled(kTRUE);
	}
	
private:

	enum
	{
		BTN_WAVE_AUTOTRIG,
		BTN_WAVE_STARTTRIG,
		BTN_WAVE_STOPTRIG,
		BTN_WAVE_FORCETRIG,
		BTN_TEST,
		SDR_TRG_THRESHOLD
	};
	
	int 						sl_hits[2][112][6];

	ModuleFrame				*pM;
	Gtp_regs					*pRegs;

	TTimer					*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvas[2];
	
	TH2Poly					*pScalers[2];

	TGTextButton			*pButtonAutoTrigger;
	TGTextButton			*pButtonStartTrigger;
	TGTextButton			*pButtonStopTrigger;
	TGTextButton			*pButtonForceTrigger;
	TGTextButton			*pButtonTest;
	
	TGLabel					*pLabelThreshold;

	TGSlider					*pSliderThreshold;
};

#endif
