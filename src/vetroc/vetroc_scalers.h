#ifndef vetroc_scalers_H
#define vetroc_scalers_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "vetroc.h"

#define UDPATETIME_MAX	60

class vetroc_scalers	: public TGCompositeFrame
{
public:
	vetroc_scalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (vetroc_regs *)pM->BaseAddr;
		
		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrameButtons->AddFrame(pButtonAutoUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
				pButtonAutoUpdate->Associate(this);
			pFrameButtons->AddFrame(pButtonManualUpdate = new TGTextButton(pFrameButtons, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonManualUpdate->Associate(this);				
			pFrameButtons->AddFrame(pButtonCheckEvent = new TGTextButton(pFrameButtons, new TGHotString("Check Event"), BTN_CHECKEVENT), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonCheckEvent->Associate(this);
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

		AddFrame(pCanvasScalers = new TRootEmbeddedCanvas("VETROC Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasScalers->GetCanvas()->SetBorderMode(0);
			pCanvasScalers->GetCanvas()->Divide(4, 2);

				pHistScalers[0] = new TH1I("TDC Channels 0-15", NULL, 16, 0, 16);
				pHistScalers[1] = new TH1I("TDC Channels 16-31", NULL, 16, 16, 32);
				pHistScalers[2] = new TH1I("TDC Channels 32-47", NULL, 16, 32, 48);
				pHistScalers[3] = new TH1I("TDC Channels 48-63", NULL, 16, 48, 64);
				pHistScalers[4] = new TH1I("TDC Channels 64-79", NULL, 16, 64, 80);
				pHistScalers[5] = new TH1I("TDC Channels 80-95", NULL, 16, 80, 96);
				pHistScalers[6] = new TH1I("TDC Channels 96-111", NULL, 16, 96, 112);
				pHistScalers[7] = new TH1I("TDC Channels 112-127", NULL, 16, 112, 128);

				for(int i = 0; i < 4; i++)
				{
					for(int j = 0; j < 2; j++)
					{
						pHistScalers[j*4+i]->SetStats(kFALSE);
						pHistScalers[j*4+i]->SetNdivisions(16);
						pHistScalers[j*4+i]->SetFillColor(4);
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
					case BTN_CHECKEVENT:
						CheckEvent();
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

	void CheckEvent()
	{
		int nwords = pM->ReadReg32((volatile unsigned int *)&pRegs->EB.FifoWordCnt);
		int l = 1;
		printf("nwords = %d\n", nwords);
		
		if(nwords > 50) nwords = 50;
		while(nwords--)
		{
			printf("%08X ", pM->ReadReg32((volatile unsigned int *)0x08000000));
			if(!(l++ % 8) || !nwords) printf("\n");
		}
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

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 1);
		for(i = 0; i < 8; i++)
		{
			pHistScalers[i]->Clear();
			for(j = 0; j < 16; j++)
				pHistScalers[i]->SetBinContent(j+1, pM->ReadReg32(&pRegs->Tdc[i].Scalers[j]));
		}
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 3);
		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 2; j++)
			{
				pCanvasScalers->GetCanvas()->cd(j*4+i+1);
				pHistScalers[j*4+i]->GetXaxis()->CenterLabels();
				pHistScalers[j*4+i]->GetXaxis()->SetTitle("TDC Channel");
				pHistScalers[j*4+i]->GetXaxis()->CenterTitle();
				pHistScalers[j*4+i]->GetYaxis()->SetTitle("Count");
				pHistScalers[j*4+i]->GetXaxis()->CenterTitle();
				pHistScalers[j*4+i]->Draw("bar");
			}
		}
		pCanvasScalers->GetCanvas()->Modified();
		pCanvasScalers->GetCanvas()->Update();

		pTextTrig1Scaler->SetText(Form("Trig Scaler: %u", pM->ReadReg32(&pRegs->Sd.Scalers[VETROC_SCALER_TRIG])), kFALSE);
	}

private:
	
	enum Buttons
	{
		BTN_LOGMODE,
		BTN_AUTOUPDATE,
		BTN_MANUALUPDATE,
		SDR_UPDATETIME,
		BTN_CHECKEVENT
	};

	
	ModuleFrame				*pM;
	vetroc_regs				*pRegs;

	TH1I						*pHistScalers[8];

	TTimer					*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvasScalers;

	TGHorizontalFrame		*pFrameButtons;

	TGSlider					*pSliderUpdateTime;
	TGTextButton			*pButtonAutoUpdate;
	TGTextButton			*pButtonManualUpdate;
	TGTextButton			*pButtonCheckEvent;
	TGTextEntry				*pTextTrig1Scaler;
	TGTextEntry				*pTextTrig2Scaler;
};

#endif
