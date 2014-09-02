#ifndef FADC250_TrgHist_H
#define FADC250_TrgHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "fadc.h"

#define UDPATETIME_MAX			60
#define FADC250_CH_BINS_PER_SEC	32*1024*1024

class FADC250_TrgHist	: public TGCompositeFrame
{
public:
	FADC250_TrgHist(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		static int inst = 0;
		int i;

		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (fadc_struct *)pM->BaseAddr;

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

		TGCanvas *pTGCanvas;
		AddFrame(pTGCanvas = new TGCanvas(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTGCanvas->SetContainer(pTF1 = new TGVerticalFrame(pTGCanvas->GetViewPort()));
				pTF1->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pTF1, 1000, 6000));//, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		//AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 100, 100), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

			pCanvas->GetCanvas()->Divide(2,8);

			for(i = 0; i < 16; i++)
			{
				pHist[i] = new TH1I(Form("fadc250-h%d,%d", inst, i), Form("FADC Ch%d", i), 1024, 0.0, 8*1024.0);
				pHist[i]->GetXaxis()->SetTitle("Pulse Energy(MeV)");
				pHist[i]->GetXaxis()->SetRangeUser(0.0, 8192.0);
				pHist[i]->GetYaxis()->SetTitle("Counts");
//				pHist[i]->GetYaxis()->SetTitleOffset(1.75);
				pHist[i]->GetYaxis()->CenterTitle();
				pHist[i]->SetFillColor(2);
				pHist[i]->ResetStats();

				pCanvas->GetCanvas()->cd(i+1);
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
		unsigned int buf[1024];

		if(bReadout)
			pM->WriteReg32(&pRegs->hist_ctrl, 0);	// disable histograms

		for(int i = 0; i < 16; i++)
		{
			pHist[i]->ResetStats();

			if(bReadout)
			{
				pM->BlkReadReg32(&pRegs->hist_data[i], buf, 1024, CRATE_MSG_FLAGS_NOADRINC);
				if(pButtonNormalize->IsDown() == kTRUE)
				{
					double norm_bin, sum = 0;
					for(int j = 0; j < 1024; j++)
						sum += buf[j];

					for(int j = 0; j < 1024; j++)
					{
						if(buf[j] == 0xFFFFFFFF)
						{
							printf("FADC250_TrgHist: normalization failure - overflowed bins\n");
							break;
						}
						if(sum <= 0.0)
						{
							printf("FADC250_TrgHist: normalization failure - no time elapsed\n");
							break;
						}
						norm_bin = (double)buf[j] * FADC250_CH_BINS_PER_SEC / sum;
						pHist[i]->SetBinContent(j, norm_bin);
					}
					pHist[i]->GetYaxis()->SetTitle("Rate(Hz)");
				}
				else
				{
					for(int j = 0; j < 1024; j++)
					{
						if(buf[j] > 0x80000000)
							pHist[i]->SetBinContent(j, 0x7FFFFFFF);
						else
							pHist[i]->SetBinContent(j, buf[j]);
					}
					pHist[i]->GetYaxis()->SetTitle("Counts");
				}
			}
			else
			{
				for(int j = 0; j < 1024; j++)
					pHist[i]->SetBinContent(j, 0);
			}
			pCanvas->GetCanvas()->cd(i+1);
			pCanvas->GetCanvas()->Modified();
			pCanvas->GetCanvas()->Update();
		}

		if(bReadout)
			pM->WriteReg32(&pRegs->hist_ctrl, 1);	// enable histograms
	}

private:

	enum Buttons
	{
		BTN_AUTOUPDATE		= 1002,
		BTN_MANUALUPDATE	= 1003,
		SDR_UPDATETIME		= 1100
	};
	
	ModuleFrame			*pM;
	fadc_struct			*pRegs;

	TTimer				*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvas;

	TGTextView			*pTextScalers;

	TH1I				*pHist[16];

	TGSlider			*pSliderUpdateTime;

	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;
	TGTextButton		*pButtonNormalize;
};

#endif
