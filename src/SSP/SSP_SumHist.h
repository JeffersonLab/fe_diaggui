#ifndef SSP_SumHist_H
#define SSP_SumHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "ssp.h"

#define SSP_SUMHIST_NBINS		32
#define UDPATETIME_MAX			60

class SSP_SumHist	: public TGCompositeFrame
{
public:
	SSP_SumHist(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		static int inst = 0;
		int i;

		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (SSP_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pTF1->AddFrame(pButtonNormalize = new TGTextButton(pTF1, new TGHotString("Normalize")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonNormalize->AllowStayDown(kTRUE);
			pTF1->AddFrame(pButtonAutoUpdate = new TGTextButton(pTF1, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
				pButtonAutoUpdate->Associate(this);
			pTF1->AddFrame(pButtonManualUpdate = new TGTextButton(pTF1, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonManualUpdate->Associate(this);
			pTF1->AddFrame(pSliderUpdateTime = new TGHSlider(pTF1, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);
				pSliderUpdateTime->Associate(this);

		AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 100, 100), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		for(i = 0; i < SSP_SUMHIST_NBINS+1; i++)
			pHistBins[i] = pow(2.0, i);

		for(i = 0; i < 1; i++)
		{
			pHist[i] = new TH1I(Form("ssp-h%d,%d", inst, i), Form("Integral: Fiber %d", i), SSP_SUMHIST_NBINS, pHistBins);
			pHist[i]->GetXaxis()->SetTitle("Pulse Integral");
			pHist[i]->GetXaxis()->SetRangeUser(pHistBins[0], pHistBins[SSP_SUMHIST_NBINS]);
			pHist[i]->GetYaxis()->SetTitle("Counts");
			pHist[i]->GetYaxis()->SetTitleOffset(1.25);
			pHist[i]->GetYaxis()->CenterTitle();
			pHist[i]->SetFillColor(2);
			pHist[i]->ResetStats();

			pCanvas->GetCanvas()->cd(i+1);
			pCanvas->GetCanvas()->SetLogx(1);
			pHist[i]->Draw("bar0");
			pCanvas->GetCanvas()->Modified();
			pCanvas->GetCanvas()->Update();
		}

//		UpdateHistogram(kFALSE);

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);

		inst++;
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_AUTOUPDATE:
						if(pButtonAutoUpdate->IsDown())
						{
							pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Auto"));
//							pSliderUpdateTime->SetEnabled(kTRUE);
							pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
						}
						else
						{
							pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Manual"));
//							pSliderUpdateTime->SetEnabled(kFALSE);
							pTimerUpdate->TurnOff();
						}
						break;
					case BTN_MANUALUPDATE:
						UpdateHistogram();
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
				break;
			case kC_HSLIDER:
				switch(parm1)
				{
					case SDR_UPDATETIME:
						pTimerUpdate->TurnOff();
						pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
						break;
					default:
						printf("slider id %d pressed\n", (int)parm1);
						break;
				}
				break;
			}
			break;
		}
		return kTRUE;
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
			UpdateHistogram();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	void UpdateHistogram(Bool_t bReadout = kTRUE)
	{
		unsigned int buf[SSP_SUMHIST_NBINS];

		if(bReadout)
			pM->WriteReg32(&pRegs->Trg.HistCtrl, 0);	// disable histograms

		for(int i = 0; i < 1; i++)
		{
			pHist[i]->ResetStats();

			if(bReadout)
			{
				pM->BlkReadReg32(&pRegs->Trg.SumHistData, buf, SSP_SUMHIST_NBINS, CRATE_MSG_FLAGS_NOADRINC);
				for(int j = 0; j < SSP_SUMHIST_NBINS; j++)
				{
					if(buf[j] > 0x80000000)
						pHist[i]->SetBinContent(j+1, 0x7FFFFFFF);
					else
						pHist[i]->SetBinContent(j+1, buf[j]);
				}
				pHist[i]->GetYaxis()->SetTitle("Counts");
			}
			else
			{
				for(int j = 0; j < SSP_SUMHIST_NBINS+2; j++)
					pHist[i]->SetBinContent(j, 0);
			}
			pCanvas->GetCanvas()->cd(i+1);
			pCanvas->GetCanvas()->Modified();
			pCanvas->GetCanvas()->Update();
		}

		if(bReadout)
			pM->WriteReg32(&pRegs->Trg.HistCtrl, 1);	// enable histograms
	}

private:

	enum Buttons
	{
		BTN_AUTOUPDATE		= 1002,
		BTN_MANUALUPDATE	= 1003,
		SDR_UPDATETIME		= 1100
	};
	
	ModuleFrame			*pM;
	SSP_regs				*pRegs;

	TTimer				*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvas;

	TGTextView			*pTextScalers;

	TH1I					*pHist[1];

	double				pHistBins[SSP_SUMHIST_NBINS+1];

	TGSlider				*pSliderUpdateTime;

	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;
	TGTextButton		*pButtonNormalize;
};

#endif
