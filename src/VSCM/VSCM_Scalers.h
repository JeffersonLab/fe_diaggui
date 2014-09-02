#ifndef VSCM_Scalers_H
#define VSCM_Scalers_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "vscm.h"

#define UDPATETIME_MAX	60

class VSCM_Scalers	: public TGCompositeFrame
{
public:
	VSCM_Scalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (VSCM_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrameButtons->AddFrame(pButtonAutoUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
			pFrameButtons->AddFrame(pButtonManualUpdate = new TGTextButton(pFrameButtons, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			pFrameButtons->AddFrame(pSliderUpdateTime = new TGHSlider(pFrameButtons, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);

			pButtonAutoUpdate->Associate(this);
			pButtonManualUpdate->Associate(this);
			pSliderUpdateTime->Associate(this);

		AddFrame(pFrameText = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameText->AddFrame(pTextScalers = new TGTextView(pFrameText), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		UpdateTextView(kTRUE);

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
						UpdateTextView();
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
			UpdateTextView();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	char *ReadNormalizedScaler(char *buf, const char *prefix, unsigned int ref, unsigned int scaler)
	{
		double normalized = 100.0e6 * (double)scaler / (double)ref;
		sprintf(buf, "%s = %08X, %.3fHz", prefix, scaler, normalized);
		return buf;
	}

	void UpdateTextView(Bool_t bInit = kFALSE)
	{
		char buf[100];

		pTextScalers->Clear();
		pTextScalers->AddLineFast("------ FPGA Scalers ------");

		unsigned int ref;

		if(!bInit)
			pM->WriteReg32(&pRegs->ScalerLatch, 0xFFFFFFFF);
		ref = pM->ReadReg32(&pRegs->ScalerVmeClk);
		
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Clk100    ", ref, ref));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Sync      ", ref, pM->ReadReg32(&pRegs->ScalerSync)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Trig 1    ", ref, pM->ReadReg32(&pRegs->ScalerTrig1)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Trig 2    ", ref, pM->ReadReg32(&pRegs->ScalerTrig2)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPOUTPUT0 ", ref, pM->ReadReg32(&pRegs->ScalerFpOutput[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPOUTPUT1 ", ref, pM->ReadReg32(&pRegs->ScalerFpOutput[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPOUTPUT2 ", ref, pM->ReadReg32(&pRegs->ScalerFpOutput[2])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPOUTPUT3 ", ref, pM->ReadReg32(&pRegs->ScalerFpOutput[3])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPINPUT0  ", ref, pM->ReadReg32(&pRegs->ScalerFpInput[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPINPUT1  ", ref, pM->ReadReg32(&pRegs->ScalerFpInput[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPINPUT2  ", ref, pM->ReadReg32(&pRegs->ScalerFpInput[2])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FPINPUT3  ", ref, pM->ReadReg32(&pRegs->ScalerFpInput[3])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Busy      ", ref, pM->ReadReg32(&pRegs->ScalerBusy)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Busy Time ", ref, pM->ReadReg32(&pRegs->ScalerBusyCycles)));

		pTextScalers->Update();
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
	VSCM_regs			*pRegs;

	TTimer				*pTimerUpdate;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameText;

	TGTextView			*pTextScalers;

	TGSlider			*pSliderUpdateTime;
	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;
};

#endif
