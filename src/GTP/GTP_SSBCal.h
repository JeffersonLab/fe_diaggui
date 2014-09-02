#ifndef GTP_SSBCAL_H
#define GTP_SSBCAL_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "gtp.h"

class GTP_SSBCal	: public TGCompositeFrame
{
public:
	GTP_SSBCal(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;
		
		TGCompositeFrame *pF1, *pF2;
		AddFrame(pF1 = new TGGroupFrame(this, "BCAL Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(new TGLabel(pF2, new TGString("Delay(ticks): ")), new TGLayoutHints(kLHintsLeft));
				pF2->AddFrame(pNumberDelay = new TGNumberEntry(pF2, 0, 4, NUM_DELAY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 255.0));
					pNumberDelay->Associate(this);
				pF2->AddFrame(pLabelDelay = new TGLabel(pF2, new TGString(" Actual Delay = 9999ns")), new TGLayoutHints(kLHintsLeft));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(new TGLabel(pF2, new TGString("Integration Width(ticks): ")), new TGLayoutHints(kLHintsLeft));
				pF2->AddFrame(pNumberWidth = new TGNumberEntry(pF2, 0, 4, NUM_WIDTH, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 255.0));
					pNumberWidth->Associate(this);
				pF2->AddFrame(pLabelWidth = new TGLabel(pF2, new TGString(" Actual Integration Width = 9999ns")), new TGLayoutHints(kLHintsLeft));
				
		AddFrame(pF1 = new TGGroupFrame(this, "BCAL Energy Scalers", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(pButtonUpdateScalers = new TGTextButton(pF2, new TGHotString("Update Scalers"), BTN_UPDATE_SCALERS));
					pButtonUpdateScalers->Associate(this);
		
			pF1->AddFrame(pCanvasEnergy = new TRootEmbeddedCanvas("c1", pF1, 600, 400), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvasEnergy->GetCanvas()->SetBorderMode(0);
				pCanvasEnergy->GetCanvas()->Divide(2,1);

				double bins[32+1];
				for(int i = 0; i < 33; i++)
				{
					if(!i)
						bins[i] = 1.0;
					else
						bins[i] = bins[i-1]*2.0;
				}
				
				TVirtualPad *pPad = pCanvasEnergy->GetCanvas()->cd(1);
					pH_Rate = new TH1D("bcalrate", ";ADC Integral;Rate(Hz)", 32, bins);
					pH_Rate->SetFillColor(49);
					pH_Rate->SetStats(0);
					pH_Rate->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_Rate->GetXaxis()->CenterLabels();
					pH_Rate->GetXaxis()->SetLabelSize(0.04);
					pH_Rate->Draw("bar2");
					pPad->SetLogx(1);
					pPad->SetLogy(1);

				pPad = pCanvasEnergy->GetCanvas()->cd(2);
					pH_Hits = new TH1D("bcalhits", ";ADC Integral;Hits", 32, bins);
					pH_Hits->SetFillColor(50);
					pH_Hits->SetStats(0);
					pH_Hits->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_Hits->GetXaxis()->CenterLabels();
					pH_Hits->GetXaxis()->SetLabelSize(0.04);
					pH_Hits->Draw("bar2");
					pPad->SetLogx(1);
					pPad->SetLogy(1);

		AddFrame(pF1 = new TGGroupFrame(this, "BCAL Hit Scalers", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pF1->AddFrame(pCanvasHits = new TRootEmbeddedCanvas("c1", pF1, 600, 400), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvasHits->GetCanvas()->SetBorderMode(0);
				pCanvasHits->GetCanvas()->Divide(2,1);

				pPad = pCanvasHits->GetCanvas()->cd(1);
					pH_ModuleRate = new TH1D("bcalmodulehitrate", ";Module Hits;Rate(Hz)", 32, 0.0, 32.0);
					pH_ModuleRate->SetFillColor(49);
					pH_ModuleRate->SetStats(0);
					pH_ModuleRate->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_ModuleRate->GetXaxis()->CenterLabels();
					pH_ModuleRate->GetXaxis()->SetLabelSize(0.04);
					pH_ModuleRate->Draw("bar2");
					pPad->SetLogy(1);

				pPad = pCanvasHits->GetCanvas()->cd(2);
					pH_ModuleHits = new TH1D("bcalmodulehits", ";Module Hits;Hits", 32, 0.0, 32.0);
					pH_ModuleHits->SetFillColor(50);
					pH_ModuleHits->SetStats(0);
					pH_ModuleHits->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_ModuleHits->GetXaxis()->CenterLabels();
					pH_ModuleHits->GetXaxis()->SetLabelSize(0.04);
					pH_ModuleHits->Draw("bar2");
					pPad->SetLogy(1);

		UpdateScalers();
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

		// BCAL Energy
		pPad = pCanvasEnergy->GetCanvas()->cd(1);
		pH_Rate->Reset();
		bin = 1.0;
		for(i = 0; i < 32; i++)
		{
			pH_Rate->Fill(bin, pGtpScalers->BCalEnergy[i]);	// need to normalize to Hz
			bin = bin * 2.0;
		}
		pPad->Modified();
		pPad->Update();

		pPad = pCanvasEnergy->GetCanvas()->cd(2);
		pH_Hits->Reset();
		bin = 1.0;
		for(i = 0; i < 32; i++)
		{
			pH_Hits->Fill(bin, pGtpScalers->BCalEnergy[i]);
			bin = bin * 2.0;
		}
		pPad->Modified();
		pPad->Update();

		// BCAL Module Hits
		pPad = pCanvasHits->GetCanvas()->cd(1);
		pH_ModuleRate->Reset();
		for(i = 0; i < 32; i++)
			pH_ModuleRate->Fill(i, pGtpScalers->BCalHitModules[i]);	// need to normalize to Hz
		pPad->Modified();
		pPad->Update();

		pPad = pCanvasHits->GetCanvas()->cd(2);
		pH_ModuleHits->Reset();
		for(i = 0; i < 32; i++)
			pH_ModuleHits->Fill(i, pGtpScalers->BCalHitModules[i]);
		pPad->Modified();
		pPad->Update();

		delete pScalers;
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		int v;

		if((GET_MSG(msg) == kC_TEXTENTRY) && (GET_SUBMSG(msg) == kTE_TEXTCHANGED))
		{
			switch(parm1)
			{
				case NUM_DELAY:
				{
					pM->WriteReg32(&pRegs->BCal.Delay, pNumberDelay->GetIntNumber());
					v = pM->ReadReg32(&pRegs->BCal.Delay);
					pNumberDelay->SetIntNumber(v);
					pLabelDelay->SetText(Form("Actual Delay = %dns", v*4));
					break;
				}
				case NUM_WIDTH:
				{
					pM->WriteReg32(&pRegs->BCal.Width, pNumberWidth->GetIntNumber());
					v = pM->ReadReg32(&pRegs->BCal.Width);
					pNumberWidth->SetIntNumber(v);
					pLabelWidth->SetText(Form("Actual Delay = %dns", v*4));
					break;
				}
				default:
					printf("textentry id %d selected\n", (int)parm1);
					break;
			}
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
	
	TGNumberEntry			*pNumberDelay;
	TGNumberEntry			*pNumberWidth;

	TGLabel					*pLabelDelay;
	TGLabel					*pLabelWidth;

	TRootEmbeddedCanvas	*pCanvasHits;
	TRootEmbeddedCanvas	*pCanvasEnergy;
	
	TH1D						*pH_Rate;
	TH1D						*pH_Hits;
	TH1D						*pH_ModuleRate;
	TH1D						*pH_ModuleHits;

	TGTextButton			*pButtonUpdateScalers;
	TGTextButton			*pButtonUpdateHitScalers;
};

#endif
