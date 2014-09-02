#ifndef SSP_Scalers_H
#define SSP_Scalers_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ssp.h"
#include "VMERemote.h"

#define UDPATETIME_MAX	60

class SSP_Scalers	: public TGCompositeFrame
{
public:
	SSP_Scalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (SSP_regs *)pM->BaseAddr;

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
			pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0);

		ref = pM->ReadReg32(&pRegs->Sd.ScalerSysclk);

		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Clk62.5       ", ref, ref));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Clk250        ", ref, pM->ReadReg32(&pRegs->Sd.ScalerGclk)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Sync          ", ref, pM->ReadReg32(&pRegs->Sd.ScalerSync)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Trig 1        ", ref, pM->ReadReg32(&pRegs->Sd.ScalerTrig[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Trig 2        ", ref, pM->ReadReg32(&pRegs->Sd.ScalerTrig[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "NIM 0         ", ref, pM->ReadReg32(&pRegs->Sd.ScalerGpio[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "NIM 1         ", ref, pM->ReadReg32(&pRegs->Sd.ScalerGpio[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS IN 0  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsIn[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS IN 1  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsIn[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS IN 2  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsIn[2])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS IN 3  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsIn[3])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS IN 4  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsIn[4])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS OUT 0 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsOut[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS OUT 1 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsOut[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS OUT 2 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsOut[2])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS OUT 3 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsOut[3])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "FP LVDS OUT 4 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerLvdsOut[4])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "SWA 0         ", ref, pM->ReadReg32(&pRegs->Sd.ScalerSwAGpio[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "SWA 1         ", ref, pM->ReadReg32(&pRegs->Sd.ScalerSwAGpio[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "SWB 0         ", ref, pM->ReadReg32(&pRegs->Sd.ScalerSwBGpio[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "SWB 1         ", ref, pM->ReadReg32(&pRegs->Sd.ScalerSwBGpio[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Token In      ", ref, pM->ReadReg32(&pRegs->Sd.ScalerTokenIn)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Token Out     ", ref, pM->ReadReg32(&pRegs->Sd.ScalerTokenOut)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Busy          ", ref, pM->ReadReg32(&pRegs->Sd.ScalerBusy)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "BusyTime      ", ref, pM->ReadReg32(&pRegs->Sd.ScalerBusyCycles)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 0  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 1  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 2  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[2])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 3  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[3])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 4  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[4])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 5  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[5])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 6  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[6])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS IN 7  ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsIn[7])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 0 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[0])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 1 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[1])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 2 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[2])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 3 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[3])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 4 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[4])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 5 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[5])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 6 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[6])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "P2 LVDS OUT 7 ", ref, pM->ReadReg32(&pRegs->Sd.ScalerP2LvdsOut[7])));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "SD LINK       ", ref, pM->ReadReg32(&pRegs->Sd.ScalerSdLink)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "TRIGOUT       ", ref, pM->ReadReg32(&pRegs->Sd.ScalerTrigOut)));
		
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
	SSP_regs				*pRegs;

	TTimer				*pTimerUpdate;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameText;

	TGTextView			*pTextScalers;

	TGSlider				*pSliderUpdateTime;
	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;

	unsigned int		Mode;
};

#endif
