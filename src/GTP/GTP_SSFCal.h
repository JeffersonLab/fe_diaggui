#ifndef GTP_SSFCAL_H
#define GTP_SSFCAL_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "gtp.h"

class GTP_SSFCal	: public TGCompositeFrame
{
public:
	GTP_SSFCal(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;
		
		TGCompositeFrame *pF1, *pF2;
		AddFrame(pF1 = new TGGroupFrame(this, "FCAL Energy Scalers", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(pButtonUpdateScalers = new TGTextButton(pF2, new TGHotString("Update Scalers"), BTN_UPDATE_SCALERS));
					pButtonUpdateScalers->Associate(this);
		
			pF1->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pF1, 600, 400), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvas->GetCanvas()->SetBorderMode(0);
				pCanvas->GetCanvas()->Divide(2,1);

				double bins[32+1];
				for(int i = 0; i < 33; i++)
				{
					if(!i)
						bins[i] = 1.0;
					else
						bins[i] = bins[i-1]*2.0;
				}
				
				TVirtualPad *pPad = pCanvas->GetCanvas()->cd(1);
					pH_Rate = new TH1D("fcalrate", ";ADC Integral;Rate(Hz)", 32, bins);
					pH_Rate->SetFillColor(49);
					pH_Rate->SetStats(0);
					pH_Rate->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_Rate->GetXaxis()->CenterLabels();
					pH_Rate->GetXaxis()->SetLabelSize(0.04);
					pH_Rate->Draw("bar2");
					pPad->SetLogx(1);
					pPad->SetLogy(1);

				pPad = pCanvas->GetCanvas()->cd(2);
					pH_Hits = new TH1D("fcalhits", ";ADC Integral;Hits", 32, bins);
					pH_Hits->SetFillColor(50);
					pH_Hits->SetStats(0);
					pH_Hits->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_Hits->GetXaxis()->CenterLabels();
					pH_Hits->GetXaxis()->SetLabelSize(0.04);
					pH_Hits->Draw("bar2");
					pPad->SetLogx(1);
					pPad->SetLogy(1);
					
		UpdateScalers();
	}

	void PrintScalers(GtpScalers *pGtpScalers)
	{
		int i;
		
		printf("SysClk50 = %u\n", pGtpScalers->SysClk50);
		printf("GClk = %u\n", pGtpScalers->GClk);
		printf("Sync = %u\n", pGtpScalers->Sync);
		printf("Trig1 = %u\n", pGtpScalers->Trig1);
		printf("Trig2 = %u\n", pGtpScalers->Trig2);
		printf("FpIn[4] = %u\n", i, pGtpScalers->FpIn[i]);
		printf("FpOut[4] = %u\n", i, pGtpScalers->FpOut[i]);
		printf("Busy = %u\n", pGtpScalers->Busy);
		printf("BusyCycles = %u\n", pGtpScalers->BusyCycles);
		for(i = 0; i < 32; i++) printf("FCalEnergy[%d] = %u\n", i, pGtpScalers->FCalEnergy[i]);
//		for(i = 0; i < 32; i++) printf("BCalEnergy[%d] = %u\n", i, pGtpScalers->BCalEnergy[i]);
//		for(i = 0; i < 16; i++) printf("BCalCosmic[%d] = %u\n", i, pGtpScalers->BCalCosmic[i]);
//		for(i = 0; i < 32; i++) printf("TOF[%d] = %u\n", i, pGtpScalers->TOF[i]);
//		for(i = 0; i < 32; i++) printf("TagM[%d] = %u\n", i, pGtpScalers->TagM[i]);
//		for(i = 0; i < 32; i++) printf("TagH[%d] = %u\n", i, pGtpScalers->TagH[i]);
//		for(i = 0; i < 32; i++) printf("PS[%d] = %u\n", i, pGtpScalers->PS[i]);
//		for(i = 0; i < 32; i++) printf("ST[%d] = %u\n", i, pGtpScalers->ST[i]);
/*		for(i = 0; i < 16; i++)
		{
			printf("Trig_BCalCosmic[%d] = %u\n", i, pGtpScalers->Trig_BCalCosmic[i]);
			printf("Trig_BFCal[%d] = %u\n", i, pGtpScalers->Trig_BFCal[i]);
			printf("Trig_TAGM[%d] = %u\n", i, pGtpScalers->Trig_TAGM[i]);
			printf("Trig_TAGH[%d] = %u\n", i, pGtpScalers->Trig_TAGH[i]);
			printf("Trig_PS[%d] = %u\n", i, pGtpScalers->Trig_PS[i]);
			printf("Trig_ST[%d] = %u\n", i, pGtpScalers->Trig_ST[i]);
			printf("Trig_TOF[%d] = %u\n", i, pGtpScalers->Trig_TOF[i]);
			printf("Trig[%d] = %u\n", i, pGtpScalers->Trig[i]);
		}
*/
	}

	void UpdateScalers()
	{
		TVirtualPad *pPad;
		unsigned int *pScalers;
		int len, i;
		double bin;

		if(!pM->pCrateMsgClient->ReadScalers(&pScalers, &len))
			return;

		GtpScalers *pGtpScalers = (GtpScalers *)pScalers;

		PrintScalers(pGtpScalers);
		
		// BCAL Energy
		pPad = pCanvas->GetCanvas()->cd(1);
		pH_Rate->Reset();
		bin = 1.0;
		for(i = 0; i < 32; i++)
		{
			pH_Rate->Fill(bin, pGtpScalers->FCalEnergy[i]);	// need to normalize to Hz
			bin = bin * 2.0;
		}
		pPad->Modified();
		pPad->Update();

		pPad = pCanvas->GetCanvas()->cd(2);
		pH_Hits->Reset();
		bin = 1.0;
		for(i = 0; i < 32; i++)
		{
			pH_Hits->Fill(bin, pGtpScalers->FCalEnergy[i]);
			bin = bin * 2.0;
		}
		pPad->Modified();
		pPad->Update();

		delete pScalers;
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		int v;

		if((GET_MSG(msg) == kC_TEXTENTRY) && (GET_SUBMSG(msg) == kTE_TEXTCHANGED))
		{
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_COMBOBOX))
		{
			switch(parm1)
			{
				default:
					printf("combo id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			switch(parm1)
			{
				case BTN_UPDATE_SCALERS:
					UpdateScalers();
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
			}
		}
		return kTRUE;
	}

private:
	enum
	{
		NUM_DELAY,
		NUM_WIDTH,
		BTN_UPDATE_SCALERS
	};

	ModuleFrame				*pM;
	Gtp_regs					*pRegs;
	
	TRootEmbeddedCanvas	*pCanvas;
	
	TH1D						*pH_Rate;
	TH1D						*pH_Hits;

	TGTextButton			*pButtonUpdateScalers;
};

#endif
