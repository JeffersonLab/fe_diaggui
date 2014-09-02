#ifndef DCRB_Scalers_H
#define DCRB_Scalers_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "DCRB.h"

#define UDPATETIME_MAX	60

class DCRB_Scalers	: public TGCompositeFrame
{
public:
	DCRB_Scalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (DCRB_regs *)pM->BaseAddr;
		
		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrameButtons->AddFrame(pButtonAutoUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
				pButtonAutoUpdate->Associate(this);
			pFrameButtons->AddFrame(pButtonManualUpdate = new TGTextButton(pFrameButtons, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonManualUpdate->Associate(this);
			pFrameButtons->AddFrame(pSliderUpdateTime = new TGHSlider(pFrameButtons, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);
				pSliderUpdateTime->Associate(this);
			pFrameButtons->AddFrame(pTextTrig1Scaler = new TGTextEntry(pFrameButtons, "Trig1 Scaler: 0"), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pTextTrig1Scaler->SetEnabled(kFALSE);
				pTextTrig1Scaler->SetWidth(150);
			pFrameButtons->AddFrame(pTextTrig2Scaler = new TGTextEntry(pFrameButtons, "Trig2 Scaler: 0"), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pTextTrig2Scaler->SetEnabled(kFALSE);
				pTextTrig2Scaler->SetWidth(150);

		AddFrame(pCanvasScalers = new TRootEmbeddedCanvas("DCRB Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasScalers->GetCanvas()->SetBorderMode(0);
			pCanvasScalers->GetCanvas()->Divide(3, 2);

				pHistScalers[0] = new TH1I("TDC Channels 0-15", NULL, 16, 0, 16);
				pHistScalers[1] = new TH1I("TDC Channels 16-31", NULL, 16, 16, 32);
				pHistScalers[2] = new TH1I("TDC Channels 32-47", NULL, 16, 32, 48);
				pHistScalers[3] = new TH1I("TDC Channels 48-63", NULL, 16, 48, 64);
				pHistScalers[4] = new TH1I("TDC Channels 64-79", NULL, 16, 64, 80);
				pHistScalers[5] = new TH1I("TDC Channels 80-95", NULL, 16, 80, 96);

				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j < 2; j++)
					{
						pHistScalers[j*3+i]->SetStats(kFALSE);
						pHistScalers[j*3+i]->SetNdivisions(16);
						pHistScalers[j*3+i]->SetFillColor(4);
					}
				}

		UpdateScalers();

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);
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
						UpdateScalers();
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
			UpdateScalers();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	char *ReadNormalizedScaler(char *buf, char *prefix, unsigned int ref, unsigned int scaler)
	{
		double normalized = 100.0e6 * (double)scaler / (double)ref;
		sprintf(buf, "%s = %08X, %.3fHz", prefix, scaler, normalized);
		return buf;
	}

	void UpdateScalers()
	{
		int i, j;

		pM->WriteReg32(&pRegs->ScalerLatch, 0);
		for(i = 0; i < 6; i++)
		{
			pHistScalers[i]->Clear();
			for(j = 0; j < 16; j++)
				pHistScalers[i]->SetBinContent(j+1, pM->ReadReg32(&pRegs->Scalers[i*16+j]));
		}

		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 2; j++)
			{
				pCanvasScalers->GetCanvas()->cd(j*3+i+1);
				pHistScalers[j*3+i]->GetXaxis()->CenterLabels();
				pHistScalers[j*3+i]->GetXaxis()->SetTitle("TDC Channel");
				pHistScalers[j*3+i]->GetXaxis()->CenterTitle();
				pHistScalers[j*3+i]->GetYaxis()->SetTitle("Count");
				pHistScalers[j*3+i]->GetXaxis()->CenterTitle();
				pHistScalers[j*3+i]->Draw("bar");
			}
		}
		pCanvasScalers->GetCanvas()->Modified();
		pCanvasScalers->GetCanvas()->Update();

		char buf[30];
		sprintf(buf, "Trig1 Scaler: %u", pM->ReadReg32(&pRegs->Trig1Scaler));
		pTextTrig1Scaler->SetText(buf, kFALSE);
		sprintf(buf, "Trig2 Scaler: %u", pM->ReadReg32(&pRegs->Trig2Scaler));
		pTextTrig2Scaler->SetText(buf, kFALSE);
	}

private:
	
	enum Buttons
	{
		BTN_LOGMODE,
		BTN_AUTOUPDATE,
		BTN_MANUALUPDATE,
		SDR_UPDATETIME
	};

	
	ModuleFrame			*pM;
	DCRB_regs			*pRegs;

	TH1I				*pHistScalers[6];

	TTimer				*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvasScalers;

	TGHorizontalFrame	*pFrameButtons;

	TGSlider			*pSliderUpdateTime;
	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;
	TGTextEntry			*pTextTrig1Scaler;
	TGTextEntry			*pTextTrig2Scaler;
};

#endif
