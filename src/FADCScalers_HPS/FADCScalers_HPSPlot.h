#ifndef FADCScalers_HPSPlot_H
#define FADCScalers_HPSPlot_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "fadc.h"

#define UDPATETIME_MAX		60

#define MAX_FADC_NUM			14

class FADCScalers_HPSPlot	: public TGCompositeFrame
{
public:
	FADCScalers_HPSPlot(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		for(int i = 0; i < MAX_FADC_NUM; i++)
			pRegs[i] = (fadc_struct *)0x0;

		TGCompositeFrame		*pFrame;
		
		AddFrame(pFrame = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrame->AddFrame(pButtonAutoUpdate = new TGTextButton(pFrame, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
				pButtonAutoUpdate->Associate(this);
			pFrame->AddFrame(pButtonManualUpdate = new TGTextButton(pFrame, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonManualUpdate->Associate(this);
			pFrame->AddFrame(pSliderUpdateTime = new TGHSlider(pFrame, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);
				pSliderUpdateTime->Associate(this);
				
		AddFrame(pFrame = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrame->AddFrame(pButtonNormalize = new TGTextButton(pFrame, new TGHotString("NormalizeScalers")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonNormalize->AllowStayDown(kTRUE);
				
		AddFrame(pCanvasScalers = new TRootEmbeddedCanvas("DCRB Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasScalers->GetCanvas()->SetBorderMode(0);
			pCanvasScalers->GetCanvas()->cd();
			
			pScalers = new TH2I("FADC ECAL Scalers", ";X;Y", 46, -22.0, 24.0, 5, 1, 6.0);
			pScalers->SetStats(0);
			pScalers->GetXaxis()->CenterLabels();
			pScalers->GetXaxis()->SetNdivisions(46, kFALSE);
			pScalers->GetXaxis()->SetTickLength(1);
			pScalers->GetYaxis()->CenterLabels();
			pScalers->GetYaxis()->SetNdivisions(5, kFALSE);
			pScalers->GetYaxis()->SetTickLength(1);
			pScalers->Draw("COLZTEXT");
		
		UpdateScalers();

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);
	}

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		int val = 0;
		int count;
		
		if(!strncmp(pParam2, "0X", 2))
			count	= sscanf(pParam2, "0X%X", &val);
		else
			count = sscanf(pParam2, "%u", &val);

		if(!stricmp(pParam1, "A24BaseAddrSl3") && count) pRegs[0] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl4") && count) pRegs[1] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl5") && count) pRegs[2] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl6") && count) pRegs[3] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl7") && count) pRegs[4] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl8") && count) pRegs[5] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl9") && count) pRegs[6] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl14") && count) pRegs[7] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl15") && count) pRegs[8] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl16") && count) pRegs[9] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl17") && count) pRegs[10] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl18") && count) pRegs[11] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl19") && count) pRegs[12] = (fadc_struct *)val;
		else if(!stricmp(pParam1, "A24BaseAddrSl20") && count) pRegs[13] = (fadc_struct *)val;
		else
			return kFALSE;

		return kTRUE;
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
		unsigned int scalers[MAX_FADC_NUM][16];
		unsigned int refscalers[MAX_FADC_NUM];

		for(i = 0; i < MAX_FADC_NUM; i++)
		{
			if(pRegs[i])
			{
				pM->WriteReg32(&pRegs[i]->scaler_ctrl, 0x3);	// enable, latch
				pM->WriteReg32(&pRegs[i]->scaler_ctrl, 0x5);	// reset
			}
		}
		
		memset(scalers, 0, sizeof(scalers));
		for(i = 0; i < MAX_FADC_NUM; i++)
		{
			if(pRegs[i])
			{
				refscalers[i] = pM->ReadReg32(&pRegs[i]->time_count);
				
				pM->BlkReadReg32(&pRegs[i]->scaler[0], scalers[i], 16, CRATE_MSG_FLAGS_ADRINC);
			}
		}
		
		if(pButtonNormalize->IsDown())
		{
			for(i = 0; i < MAX_FADC_NUM; i++)
			{
				if(pRegs[i] && refscalers[i])
				{
					for(j = 0; j < 16; j++)
					{
						double norm = 500.0e3 * (double)scalers[i][j] / (double)refscalers[i];
						scalers[i][j] = (unsigned int)norm;
					}
				}
			}
		}

		pScalers->Reset();
		int ch = 0;
		int val;
		for(int x = -22; x <= 23; x++)
		{
			for(int y = 1; y <= 5; y++)
			{
				if((y == 1) && ((x <= -1) && (x >= -9)))
					continue;
				
					val = scalers[ch / 16][ch % 16];
					pScalers->Fill(x, y, val);
				ch++;
			}
		}
		pCanvasScalers->GetCanvas()->Modified();
		pCanvasScalers->GetCanvas()->Update();
	}

private:

	enum Buttons
	{
		BTN_LOGMODE,
		BTN_AUTOUPDATE,
		BTN_MANUALUPDATE,
		SDR_UPDATETIME
	};

	ModuleFrame					*pM;
	fadc_struct					*pRegs[MAX_FADC_NUM];

	TH2I							*pScalers;

	TTimer						*pTimerUpdate;

	TRootEmbeddedCanvas		*pCanvasScalers;

	TGSlider						*pSliderUpdateTime;
	TGTextButton				*pButtonAutoUpdate;
	TGTextButton				*pButtonManualUpdate;
	TGTextButton				*pButtonNormalize;
};

#endif
