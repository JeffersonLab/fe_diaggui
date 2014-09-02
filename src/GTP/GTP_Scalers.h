#ifndef GTP_Scalers_H
#define GTP_Scalers_H

#include <stdlib.h>
#include "RootHeader.h"
#include "gtp.h"
#include "ModuleFrame.h"

#define BTN_LOGMODE			1000
#define BTN_AUTOUPDATE		1001
#define BTN_MANUALUPDATE	1002

#define SDR_UPDATETIME		1100

#define UDPATETIME_MAX	60

class GTP_Scalers	: public TGCompositeFrame
{
public:
	GTP_Scalers(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr, unsigned int mode = 0) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Mode = mode;
		pVMEClient = pClient;
		pGTPregs = (GTP_regs *)baseAddr;

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


	unsigned int ReadReg32(volatile unsigned int *p)
	{
		unsigned int val = 0xFFFFFFFF;
		pVMEClient->ReadVME32((unsigned int)p, &val);	
		return val;
	}

	char *ReadNormalizedScaler(char *buf, char *prefix, unsigned int ref, unsigned int scaler)
	{
		double normalized = 250.0e6 * (double)scaler / (double)ref;
		sprintf(buf, "%s = %08X, %.3fHz", prefix, scaler, normalized);
		return buf;
	}

	void UpdateTextView(Bool_t bInit = kFALSE)
	{
		char buf[100];

		pTextScalers->Clear();
		pTextScalers->AddLineFast("------ FPGA Scalers ------");

		unsigned int ref, temp;

		if(!bInit)
			pVMEClient->WriteVME32((unsigned int)&pGTPregs->scaler_latch, 1);

		ref = ReadReg32(&pGTPregs->scaler_sync) << 16;
		ref = ref + ReadReg32(&pGTPregs->scaler_c250);
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Clk250           ", ref, ref));
		
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Test Trig Out    ", ref, ReadReg32(&pGTPregs->scaler_trig1)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Trig Out 3       ", ref, ReadReg32(&pGTPregs->fiber_stat1)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "Trig 1           ", ref, ReadReg32(&pGTPregs->scaler_trig2)));
		
		pTextScalers->AddLineFast(" ");
		temp = ReadReg32(&pGTPregs->pp7_msb) << 16;
		temp = temp + ReadReg32(&pGTPregs->error_pp[6]);
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "PP7 Errors Ext   ", ref, temp));
		
		temp = ReadReg32(&pGTPregs->pp8_msb) << 16;
		temp = temp + ReadReg32(&pGTPregs->error_pp[7]);
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "PP8 Errors Ext   ", ref, temp));

		pTextScalers->AddLineFast(" ");
		pTextScalers->AddLineFast("Sum Over Threshold");
		char combine[32], trig_num[4];
		for (int i=0; i<8; i++)
		{
			strcpy(combine,"VXS Payload Port "); itoa(i+1,trig_num,10); strcat(combine,trig_num);
			pTextScalers->AddLineFast(ReadNormalizedScaler(buf, combine, ref, ReadReg32(&pGTPregs->scaler_pp[i])));
		}
		for (int i=0; i<8; i++)
		{
			strcpy(combine,"VXS Payload Port "); itoa(i+9,trig_num,10); strcat(combine,trig_num);
			pTextScalers->AddLineFast(ReadNormalizedScaler(buf, combine, ref, ReadReg32(&pGTPregs->scaler_pp[i+8])));
		}
			
		
		pTextScalers->AddLineFast(" ");
		pTextScalers->AddLineFast("Payload Port Receive Errors");
		for (int i=0; i<8; i++)
		{
			strcpy(combine,"Receive Error PP "); itoa(i+1,trig_num,10); strcat(combine,trig_num);
			pTextScalers->AddLineFast(ReadNormalizedScaler(buf, combine, ref, ReadReg32(&pGTPregs->error_pp[i])));
		}
		for (int i=0; i<8; i++)
		{
			strcpy(combine,"Receive Error PP "); itoa(i+9,trig_num,10); strcat(combine,trig_num);
			pTextScalers->AddLineFast(ReadNormalizedScaler(buf, combine, ref, ReadReg32(&pGTPregs->error_pp[i+8])));
		}
		
		pTextScalers->Update();
	}

private:
	VMERemote			*pVMEClient;
	GTP_regs			*pGTPregs;

	TTimer				*pTimerUpdate;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameText;

	TGTextView			*pTextScalers;

	TGSlider			*pSliderUpdateTime;
	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;

	unsigned int		Mode;
};

#endif
