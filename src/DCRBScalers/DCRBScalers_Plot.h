#ifndef DCRBScalers_Plot_H
#define DCRBScalers_Plot_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"

#define TRIGSRC_SWSYNC		0x800
#define TRIGSRC_SWTRIG		0x008

typedef struct
{
/* 0x0000-0x0003 */ volatile unsigned int FirmwareRev;
/* 0x0004-0x0007 */ volatile unsigned int BoardID;
/* 0x0008-0x000B */ volatile unsigned int GrpBusyFifo;
/* 0x000C-0x000F */ volatile unsigned int GrpBusyTrig;
/* 0x0010-0x0013 */ volatile unsigned int GrpErrorFifo;
/* 0x0014-0x0017 */ volatile unsigned int SpiFlash;
/* 0x0018-0x001B */ volatile unsigned int ICap;
/* 0x001C-0x001F */ volatile unsigned int Adr32M;
/* 0x0020-0x0023 */ volatile unsigned int LookBack;
/* 0x0024-0x0027 */ volatile unsigned int WindowWidth;
/* 0x0028-0x002B */ volatile unsigned int BlockConfig;
/* 0x002C-0x002F */ volatile unsigned int TDCConfig;
/* 0x0030-0x0033 */ volatile unsigned int ClockConfig;
/* 0x0034-0x0037 */ volatile unsigned int TestPulseConfig;
/* 0x0038-0x003B */ volatile unsigned int DACConfig;
/* 0x003C-0x003F */ volatile unsigned int TriggerBusyThreshold;
/* 0x0040-0x0043 */ volatile unsigned int TriggerSource;
/* 0x0044-0x0047 */ volatile unsigned int ADR32;
/* 0x0048-0x004B */ volatile unsigned int Interrupt;
/* 0x004C-0x004F */ volatile unsigned int InterruptAck;
/* 0x0050-0x0053 */ volatile unsigned int Geo;
/* 0x0054-0x0057 */ volatile unsigned int FifoWordCnt;
/* 0x0058-0x005B */ volatile unsigned int FifoEventCnt;
/* 0x005C-0x005F */ volatile unsigned int ReadoutConfig;
/* 0x0060-0x0063 */ volatile unsigned int SRAMDebugAddr;
/* 0x0064-0x0067 */ volatile unsigned int SRAMDebugData;
/* 0x0068-0x006B */ volatile unsigned int Reset;
/* 0x006C-0x0077 */ volatile unsigned int ChDisable[3];
/* 0x0078-0x007B */ volatile unsigned int ScalerLatch;
/* 0x007C-0x007F */ volatile unsigned int Reserved1[(0x0080-0x007C)/4];
/* 0x0080-0x0083 */ volatile unsigned int FifoBlockCnt;
/* 0x0084-0x0087 */ volatile unsigned int InterruptWordCnt;
/* 0x0088-0x008B */ volatile unsigned int InterruptEventCnt;
/* 0x008C-0x008F */ volatile unsigned int InterruptBlockCnt;
/* 0x0090-0x0093 */ volatile unsigned int BusyWordCnt;
/* 0x0094-0x0097 */ volatile unsigned int BusyEventCnt;
/* 0x0098-0x009B */ volatile unsigned int BusyBlockCnt;
/* 0x009C-0x009F */ volatile unsigned int TriggerCtrl;
/* 0x00A0-0x00A3 */ volatile unsigned int GtpCtrl;
/* 0x00A4-0x00A7 */ volatile unsigned int GtpCtrlTile0;
/* 0x00A8-0x00AB */ volatile unsigned int GtpDrpCtrl;
/* 0x00AC-0x00AF */ volatile unsigned int GtpStatus;
/* 0x00B0-0x00B3 */ volatile unsigned int SoftErrCnt;
/* 0x00B4-0x00B7 */ volatile unsigned int PrbsErrCnt;
/* 0x00B8-0x0107 */ volatile unsigned int Reserved3[(0x0108-0x00B8)/4];
/* 0x0108-0x010B */ volatile unsigned int SwAGpio;
/* 0x010C-0x010F */ volatile unsigned int SwBGpio;
/* 0x0110-0x0113 */ volatile unsigned int TokenInCfg;
/* 0x0114-0x0117 */ volatile unsigned int TokenOutCfg;
/* 0x0118-0x011B */ volatile unsigned int SdLinkCfg;
/* 0x011C-0x011F */ volatile unsigned int TrigOutCfg;
/* 0x0120-0x0123 */ volatile unsigned int PulserPeriod;
/* 0x0124-0x0127 */ volatile unsigned int PulserLow;
/* 0x0128-0x012B */ volatile unsigned int PulserNPulses;
/* 0x012C-0x012F */ volatile unsigned int PulserStart;
/* 0x0130-0x0133 */ volatile unsigned int PulserStatus;
/* 0x0134-0x0FE7 */ volatile unsigned int Reserved4[(0x0FE8-0x0134)/4];
/* 0x0FE8-0x0FEB */ volatile unsigned int BusyScaler;
/* 0x0FEC-0x0FEF */ volatile unsigned int BusyCyclesScaler;
/* 0x0FF0-0x0FF3 */ volatile unsigned int VmeClkScaler;
/* 0x0FF4-0x0FF7 */ volatile unsigned int SyncScaler;
/* 0x0FF8-0x0FFB */ volatile unsigned int Trig1Scaler;
/* 0x0FFC-0x0FFF */ volatile unsigned int Trig2Scaler;
/* 0x1000-0x117F */ volatile unsigned int Scalers[96];
} DCRB_regs_v1;

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
			pRegs[i] = (DCRB_regs_v1 *)0x0;

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
			pFrame->AddFrame(pLabelThreshold = new TGLabel(pFrame, new TGString(Form("DACThreshold (%d):", GetThreshold()))), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			pFrame->AddFrame(pSliderThreshold = new TGHSlider(pFrame, 100, kSlider1 | kScaleBoth, SDR_THRESHOLD), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderThreshold->SetRange(0, THRESHOLD_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderThreshold->SetPosition(0);
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

		if(!stricmp(pParam1, "A24BaseAddr0") && count) pRegs[0] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr1") && count) pRegs[1] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr2") && count) pRegs[2] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr3") && count) pRegs[3] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr4") && count) pRegs[4] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr5") && count) pRegs[5] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr6") && count) pRegs[6] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr7") && count) pRegs[7] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr8") && count) pRegs[8] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr9") && count) pRegs[9] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr10") && count) pRegs[10] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr11") && count) pRegs[11] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr12") && count) pRegs[12] = (DCRB_regs_v1 *)val;
		else if(!stricmp(pParam1, "A24BaseAddr13") && count) pRegs[13] = (DCRB_regs_v1 *)val;
//		else if(!stricmp(pParam1, "DacThreshold") && count) SetThreshold(val);
		else
			return kFALSE;

		int thr = GetThreshold();
		pLabelThreshold->SetText(Form("DACThreshold (%dmV):", thr));
		pSliderThreshold->SetPosition(thr);
				
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
						//if(pButtonLocalTest->IsDown())
						//	SetLocalTest(kTRUE);
						//else
						//	SetLocalTest(kFALSE);
						break;
					case BTN_REMOTE_TST:
						//if(pButtonRemoteTest->IsDown())
						//	SetRemoteTest(kTRUE);
						//else
						//	SetRemoteTest(kFALSE);
						break;
					case BTN_DCRBSCALERS_RESET:
						//SetReset();
						break;
				
					case BTN_HARDRESET_SER:
						//HardReset();
						break;
						
					case BTN_SOFTRESET_SER:
						//SoftReset();
						break;
						
					case BTN_SMARTRESET_SER:
						//SmartReset();
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

	unsigned int GetThreshold()
	{
		unsigned int val = 0;
		
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				val = pM->ReadReg32(&pRegs[i]->DACConfig);
				val = (val<<18) / 24489360;
				printf("%d: GetThreshold() = %dmV\n", i, val);
			}
		}
		return val;
	}

	void SetLocalTest(Bool_t en)
	{
/*
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
*/
	}
	
	void SetRemoteTest(Bool_t en)
	{
/*
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
*/
	}
	
	void SetReset()
	{
/*
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
*/
	}

	void HardReset()
	{
/*
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
*/
	}

	void SoftReset()
	{
/*
		for(int i = 0; i < MAX_DCRB_NUM; i++)
		{
			if(pRegs[i])
			{
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x202);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x200);
				pM->WriteReg32(&pRegs[i]->GtpCtrl, 0x000);
			}
		}
*/
	}

	void SmartReset()
	{
/*
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
*/
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
	DCRB_regs_v1			*pRegs[MAX_DCRB_NUM];

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
