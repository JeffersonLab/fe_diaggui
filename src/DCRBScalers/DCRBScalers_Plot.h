#ifndef DCRBScalers_Plot_H
#define DCRBScalers_Plot_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "DCRB.h"

#define UDPATETIME_MAX		60
#define THRESHOLD_MAX		200

#define MAX_DCRB_NUM			14

class DCRBScalers_Plot	: public TGCompositeFrame
{
public:
	DCRBScalers_Plot(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		for(int i = 0; i < MAX_DCRB_NUM; i++)
			pRegs[i] = (DCRB_regs *)0x0;

		TGCompositeFrame		*pFrame;
		
		AddFrame(pFrame = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrame->AddFrame(pButtonBinaryClip = new TGTextButton(pFrame, new TGHotString("BinaryClip"), BTN_BINARYCLIP), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonBinaryClip->AllowStayDown(kTRUE);
				//pButtonBinaryClip->Associate(this);
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
			pFrame->AddFrame(pLabelThreshold = new TGLabel(pFrame, new TGString("DACThreshold (default):")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			pFrame->AddFrame(pSliderThreshold = new TGHSlider(pFrame, 100, kSlider1 | kScaleBoth, SDR_THRESHOLD), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderThreshold->SetRange(0, THRESHOLD_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderThreshold->SetPosition(5);
				pSliderThreshold->Associate(this);			

		AddFrame(pFrame = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrame->AddFrame(pButtonNormalize = new TGTextButton(pFrame, new TGHotString("NormalizeScalers")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonNormalize->AllowStayDown(kTRUE);
			pFrame->AddFrame(pButtonLocalTest = new TGTextButton(pFrame, new TGHotString("LocalTest"), BTN_LOCAL_TST), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonLocalTest->AllowStayDown(kTRUE);
				pButtonLocalTest->Associate(this);
			pFrame->AddFrame(pButtonRemoteTest = new TGTextButton(pFrame, new TGHotString("RemoteTest"), BTN_REMOTE_TST), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonRemoteTest->AllowStayDown(kTRUE);
				pButtonRemoteTest->Associate(this);
			pFrame->AddFrame(pButtonReset = new TGTextButton(pFrame, new TGHotString("Reset"), BTN_DCRBSCALERS_RESET), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonReset->Associate(this);

			TGTextButton *pB;
			pFrame->AddFrame(pB = new TGTextButton(pFrame, new TGHotString("HardReset"), BTN_HARDRESET_SER), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pB->Associate(this);
			pFrame->AddFrame(pB = new TGTextButton(pFrame, new TGHotString("SoftReset"), BTN_SOFTRESET_SER), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pB->Associate(this);
			pFrame->AddFrame(pB = new TGTextButton(pFrame, new TGHotString("SmartReset"), BTN_SMARTRESET_SER), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pB->Associate(this);
				
		for(int i = 0; i < 2; i++)
		{
		AddFrame(pCanvasScalers[i] = new TRootEmbeddedCanvas("DCRB Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasScalers[i]->GetCanvas()->SetBorderMode(0);
			
//				pCanvasScalers[i]->GetCanvas()->SetMargin(0.05, 0.1, 0.05, 0.05);
				
				//pScalers[i] = new TH2I("", "", 112, 0, 112, 6, 0, 6);
				pScalers[i] = new TH2Poly();
				Honeycomb(pScalers[i], -0.5, -0.5773502692, 0.5773502692, 112, 6);
				pScalers[i]->GetXaxis()->SetNdivisions(112, kTRUE);
				//pScalers[i]->GetXaxis()->SetTickLength(1);
				pScalers[i]->GetYaxis()->SetNdivisions(6, kTRUE);
				//pScalers[i]->GetYaxis()->SetTickLength(1);
				pScalers[i]->SetStats(kFALSE);
				pScalers[i]->SetBarOffset(0.0);
				pScalers[i]->SetBarWidth(0.25);
		}
		pScalers[0]->SetTitle("SuperLayer-1");
//		pScalers[0]->SetTitleSize(0.002);
		pScalers[1]->SetTitle("SuperLayer-2");
//		pScalers[1]->SetTitleSize(0.002);

		UpdateScalers();

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);
	}

	void Honeycomb(TH2Poly *pH, Double_t xstart, Double_t ystart, Double_t a, Int_t k, Int_t s)
	{
		// Bins the histogram using a honeycomb structure
		// Add the bins
		Double_t x[6], y[6];
		Double_t xloop, yloop, xtemp;
		xloop = xstart; yloop = ystart + a/2.0;
		for (int sCounter = 0; sCounter < s; sCounter++) {

			xtemp = xloop; // Resets the temp variable

			for (int kCounter = 0; kCounter <  k; kCounter++) {

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
	}

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		int val = 0;
		int count;
		
		if(!strncmp(pParam2, "0X", 2))
			count	= sscanf(pParam2, "0X%X", &val);
		else
			count = sscanf(pParam2, "%u", &val);

		if(!stricmp(pParam1, "A24BaseAddr0") && count) pRegs[0] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr1") && count) pRegs[1] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr2") && count) pRegs[2] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr3") && count) pRegs[3] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr4") && count) pRegs[4] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr5") && count) pRegs[5] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr6") && count) pRegs[6] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr7") && count) pRegs[7] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr8") && count) pRegs[8] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr9") && count) pRegs[9] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr10") && count) pRegs[10] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr11") && count) pRegs[11] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr12") && count) pRegs[12] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "A24BaseAddr13") && count) pRegs[13] = (DCRB_regs *)val;
		else if(!stricmp(pParam1, "DacThreshold") && count) SetThreshold(val);
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
					case BTN_LOCAL_TST:
						if(pButtonLocalTest->IsDown())
							SetLocalTest(kTRUE);
						else
							SetLocalTest(kFALSE);
						break;
					case BTN_REMOTE_TST:
						if(pButtonRemoteTest->IsDown())
							SetRemoteTest(kTRUE);
						else
							SetRemoteTest(kFALSE);
						break;
					case BTN_DCRBSCALERS_RESET:
						SetReset();
						break;
				
					case BTN_HARDRESET_SER:
						HardReset();
						break;
						
					case BTN_SOFTRESET_SER:
						SoftReset();
						break;
						
					case BTN_SMARTRESET_SER:
						SmartReset();
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
				case SDR_THRESHOLD:
				{
					TGString *pStr = new TGString;
					pStr->Form("DACThreshold (%dmV):", pSliderThreshold->GetPosition());
					SetThreshold(pSliderThreshold->GetPosition());
					pLabelThreshold->SetText(pStr);
					break;
				}
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

	void SetThreshold(unsigned int val)
	{
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
				pM->WriteReg32(&pRegs[i]->DACConfig, ((unsigned int)val * 24489360)>>18);
		}
	}

	void SetLocalTest(Bool_t en)
	{
		unsigned int val;
		
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				val = pM->ReadReg32(&pRegs[i]->TestPulseConfig);
				if(en)
					val |= 0x3f<<0;
				else
					val &= ~(0x3f<<0);
				pM->WriteReg32(&pRegs[i]->TestPulseConfig, val);
			}
		}
	}
	
	void SetRemoteTest(Bool_t en)
	{
		unsigned int val;
		
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				val = pM->ReadReg32(&pRegs[i]->TestPulseConfig);
				if(en)
					val |= 0x3f<<6;
				else
					val &= ~(0x3f<<6);
				pM->WriteReg32(&pRegs[i]->TestPulseConfig, val);
			}
		}
	}
	
	void SetReset()
	{
		unsigned int val;
		
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				pM->WriteReg32(&pRegs[i]->Reset, 1);
				pM->WriteReg32(&pRegs[i]->Reset, 0);
				
				val = pM->ReadReg32(&pRegs[i]->ClockConfig) & 0xFFFFFFFC;
				pM->WriteReg32(&pRegs[i]->ClockConfig, val | 0x3);
				pM->WriteReg32(&pRegs[i]->ClockConfig, val | 0x1);
				pM->WriteReg32(&pRegs[i]->TestPulseConfig, 0x3f);
				
				pM->WriteReg32(&pRegs[i]->TriggerCtrl, 0x800);

				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x203);
			}
		}
	}

	void HardReset()
	{
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x203);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x202);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x200);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x000);
			}
		}
	}

	void SoftReset()
	{
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x202);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x200);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x000);
			}
		}
	}

	void SmartReset()
	{
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i] && !(pM->ReadReg32(&pRegs[i]->GtpStatus) & 0x1000))
			{
				printf("Resetting dcrb serdes %d\n", i);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x202);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x200);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x000);
			}
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
		int i, j, k;
		unsigned int scalers[MAX_DCRB_NUM][96];
		unsigned int refscalers[MAX_DCRB_NUM];

		for(i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
				pM->WriteReg32(&pRegs[i]->ScalerLatch, 0);
		}
		
		memset(scalers, 0, sizeof(scalers));
		for(i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				refscalers[i] = pM->ReadReg32(&pRegs[i]->VmeClkScaler);
				pM->BlkReadReg32(&pRegs[i]->Scalers[0], scalers[i], 96, CRATE_MSG_FLAGS_ADRINC);
			}
		}
		
		if(pButtonNormalize->IsDown())
		{
			for(i = 0; i < MAX_DCRB_NUM; i++)
			{
				if(pRegs[i] && refscalers[i])
				{
					for(j = 0; j < 96; j++)
					{
						double norm = 125.0e6 * (double)scalers[i][j] / (double)refscalers[i];
						scalers[i][j] = (unsigned int)norm;
					}
				}
			}
		}

		for(i = 0; i < 2; i++)
		{
			pScalers[i]->Reset("");
			for(j = 0; j < 7; j++)
			{
				if(pRegs[j+i*7])
				{
					for(k = 0; k < 96; k++)
					{
						double x = 16.0*j+(int)(k/6);
						double y = ((double)(k % 3)) * 1.732;
						
						if((k % 6) < 3)
						{
							x-= 0.5;
							y+= 0.866;
						}
						
						if(pButtonBinaryClip->IsDown())
						{
							if(scalers[j+i*7][k])
								pScalers[i]->Fill(x, y);
						}
						else
							pScalers[i]->Fill(x, y, (double)scalers[j+i*7][k]);
					}
				}
			}
			pCanvasScalers[i]->GetCanvas()->cd();
			pCanvasScalers[i]->GetCanvas()->Clear();
			pScalers[i]->Draw("COLZTEXT");
			pScalers[i]->GetZaxis()->SetLabelSize(0.06);
			pCanvasScalers[i]->GetCanvas()->Modified();
			pCanvasScalers[i]->GetCanvas()->Update();
		}
	}

private:

	enum Buttons
	{
		BTN_LOGMODE,
		BTN_AUTOUPDATE,
		BTN_MANUALUPDATE,
		BTN_BINARYCLIP,
		BTN_LOCAL_TST,
		BTN_REMOTE_TST,
		BTN_DCRBSCALERS_RESET,
		BTN_HARDRESET_SER,
		BTN_SOFTRESET_SER,
		BTN_SMARTRESET_SER,
		SDR_UPDATETIME,
		SDR_THRESHOLD
	};

	ModuleFrame				*pM;
	DCRB_regs				*pRegs[MAX_DCRB_NUM];

	TH2Poly					*pScalers[2];

	TTimer					*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvasScalers[2];

	TGLabel					*pLabelThreshold;
	TGSlider					*pSliderUpdateTime;
	TGSlider					*pSliderThreshold;
	TGTextButton			*pButtonAutoUpdate;
	TGTextButton			*pButtonManualUpdate;
	TGTextButton			*pButtonBinaryClip;
	TGTextButton			*pButtonLocalTest;
	TGTextButton			*pButtonRemoteTest;
	TGTextButton			*pButtonReset;
	TGTextButton			*pButtonNormalize;
};

#endif
