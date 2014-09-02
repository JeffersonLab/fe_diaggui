#ifndef GTP_SSHITPATTERN_H
#define GTP_SSHITPATTERN_H

#include "ModuleFrame.h"
#include "RootHeader.h"
#include "gtp.h"

#define GTP_HITPATTER_TYPE_TOF	0
#define GTP_HITPATTER_TYPE_PS		1
#define GTP_HITPATTER_TYPE_ST		2
#define GTP_HITPATTER_TYPE_TAGH	3
#define GTP_HITPATTER_TYPE_TAGM	4

class GTP_SSHitPattern	: public TGCompositeFrame
{
public:
	GTP_SSHitPattern(const TGWindow *p, ModuleFrame *pModule, int type) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));


		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;
		Type = type;

		if(type == GTP_HITPATTER_TYPE_TOF)
		{
			Name = "TOF";
			NBins = 32;
			NDiv = 16;
		}
		else if(type == GTP_HITPATTER_TYPE_PS)
		{
			Name = "PS";
			NBins = 16;
			NDiv = 16;
		}
		else if(type == GTP_HITPATTER_TYPE_ST)
		{
			Name = "ST";
			NBins = 32;
			NDiv = 16;
		}
		else if(type == GTP_HITPATTER_TYPE_TAGH)
		{
			Name = "TAGH";
			NBins = 32;
			NDiv = 16;
		}
		else if(type == GTP_HITPATTER_TYPE_TAGM)
		{
			Name = "TAGM";
			NBins = 32;
			NDiv = 16;
		}
		else
		{
			Name = "unknown";
			NBins = 32;
			NDiv = 16;
		}
		
		TGCompositeFrame *pF1, *pF2;
		AddFrame(pF1 = new TGGroupFrame(this, Form("%s Config", Name.Data()), kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(new TGLabel(pF2, new TGString("Delay(ticks): ")), new TGLayoutHints(kLHintsLeft));
				pF2->AddFrame(pNumberDelay = new TGNumberEntry(pF2, 0, 4, NUM_DELAY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 255.0));
					pNumberDelay->Associate(this);
				pF2->AddFrame(pLabelDelay = new TGLabel(pF2, new TGString(" Actual Delay = 9999ns")), new TGLayoutHints(kLHintsLeft));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(new TGLabel(pF2, new TGString("Pulse Width Extension(ticks): ")), new TGLayoutHints(kLHintsLeft));
				pF2->AddFrame(pNumberWidth = new TGNumberEntry(pF2, 0, 4, NUM_WIDTH, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0.0, 255.0));
					pNumberWidth->Associate(this);
				pF2->AddFrame(pLabelWidth = new TGLabel(pF2, new TGString(" Actual Width Extension = 9999ns")), new TGLayoutHints(kLHintsLeft));
		
		AddFrame(pF1 = new TGGroupFrame(this, Form("%s Scalers", Name.Data()), kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(pButtonUpdateScalers = new TGTextButton(pF2, new TGHotString("Update Scalers"), BTN_UPDATE_SCALERS));
					pButtonUpdateScalers->Associate(this);
		
			pF1->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pF1, 600, 400), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvas->GetCanvas()->SetBorderMode(0);
				pCanvas->GetCanvas()->Divide(2,1);
				
				TVirtualPad *pPad = pCanvas->GetCanvas()->cd(1);
					pH_Rate = new TH1D(Form("%srate", Name.Data()), ";;Rate(Hz)", NBins, 0.0, (double)NBins);
					pH_Rate->SetFillColor(49);
					pH_Rate->SetStats(0);
					pH_Rate->GetXaxis()->SetNdivisions(NDiv, kFALSE);
					pH_Rate->GetXaxis()->CenterLabels();
					pH_Rate->GetXaxis()->SetLabelSize(0.04);
					pH_Rate->GetYaxis()->SetLabelSize(0.04);
					pH_Rate->Draw("bar2");
					pPad->SetLogy(1);
					pPad->Modified();
					pPad->Update();

				pPad = pCanvas->GetCanvas()->cd(2);
					pH_Hits = new TH1D(Form("%shits", Name.Data()), ";;Hits", NBins, 0.0, (double)NBins);
					pH_Hits->SetFillColor(50);
					pH_Hits->SetStats(0);
					pH_Hits->GetXaxis()->SetNdivisions(NDiv, kFALSE);
					pH_Hits->GetXaxis()->CenterLabels();
					pH_Hits->GetXaxis()->SetLabelSize(0.04);
					pH_Rate->GetYaxis()->SetLabelSize(0.04);
					pH_Hits->Draw("bar2");
					pPad->SetLogy(1);
					pPad->Modified();
					pPad->Update();
					
		UpdateScalers();
	}
	
	void UpdateScalers()
	{
		TVirtualPad *pPad;
		unsigned int *pScalers;
		unsigned int *pScalersToPlot = NULL;
		int len, i;

		if(!pM->pCrateMsgClient->ReadScalers(&pScalers, &len))
			return;

		GtpScalers *pGtpScalers = (GtpScalers *)pScalers;

		if(Type == GTP_HITPATTER_TYPE_TOF)
			pScalersToPlot = pGtpScalers->TOF;
		else if(Type == GTP_HITPATTER_TYPE_PS)
			pScalersToPlot = pGtpScalers->PS;
		else if(Type == GTP_HITPATTER_TYPE_ST)
			pScalersToPlot = pGtpScalers->ST;
		else if(Type == GTP_HITPATTER_TYPE_TAGH)
			pScalersToPlot = pGtpScalers->TagH;
		else if(Type == GTP_HITPATTER_TYPE_TAGM)
			pScalersToPlot = pGtpScalers->TagM;

		if(pScalersToPlot)
		{
			// Normalized to Hz

			double norm_factor;

			pPad = pCanvas->GetCanvas()->cd(1);
			pH_Rate->Reset();
			if( (pGtpScalers->SysClk50 != 0) && (pGtpScalers->SysClk50 != 0xFFFFFFFF) )
			{
				norm_factor = 50.0E6 / pGtpScalers->SysClk50;
				for(i = 0; i < NBins; i++)
					pH_Rate->Fill(i, norm_factor * (double)pScalersToPlot[i]);	// need to normalize to Hz
			}
			else
			{
				for(i = 0; i < NBins; i++)
					pH_Rate->Fill(i, -1);	// normalization factor unknown...so set erroneous value...
			}
			pPad->Modified();
			pPad->Update();

			// Raw values
			pPad = pCanvas->GetCanvas()->cd(2);
			pH_Hits->Reset();
			for(i = 0; i < NBins; i++)
				pH_Hits->Fill(i, pScalersToPlot[i]);
			pPad->Modified();
			pPad->Update();
		}
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
					if(Type == GTP_HITPATTER_TYPE_TOF)
						pM->WriteReg32(&pRegs->TOF.Delay, pNumberDelay->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_PS)
						pM->WriteReg32(&pRegs->PS.Delay, pNumberDelay->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_ST)
						pM->WriteReg32(&pRegs->ST.Delay, pNumberDelay->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_TAGH)
						pM->WriteReg32(&pRegs->TagH.Delay, pNumberDelay->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_TAGM)
						pM->WriteReg32(&pRegs->TagM.Delay, pNumberDelay->GetIntNumber());

					if(Type == GTP_HITPATTER_TYPE_TOF)
						v = pM->ReadReg32(&pRegs->TOF.Delay);
					else if(Type == GTP_HITPATTER_TYPE_PS)
						v = pM->ReadReg32(&pRegs->PS.Delay);
					else if(Type == GTP_HITPATTER_TYPE_ST)
						v = pM->ReadReg32(&pRegs->ST.Delay);
					else if(Type == GTP_HITPATTER_TYPE_TAGH)
						v = pM->ReadReg32(&pRegs->TagH.Delay);
					else if(Type == GTP_HITPATTER_TYPE_TAGM)
						v = pM->ReadReg32(&pRegs->TagM.Delay);

					pNumberDelay->SetIntNumber(v);
					pLabelDelay->SetText(Form("Actual Delay = %dns", (int)v*4));

					break;
				}
				case NUM_WIDTH:
				{
					if(Type == GTP_HITPATTER_TYPE_TOF)
						pM->WriteReg32(&pRegs->TOF.Width, pNumberWidth->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_PS)
						pM->WriteReg32(&pRegs->PS.Width, pNumberWidth->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_ST)
						pM->WriteReg32(&pRegs->ST.Width, pNumberWidth->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_TAGH)
						pM->WriteReg32(&pRegs->TagH.Width, pNumberWidth->GetIntNumber());
					else if(Type == GTP_HITPATTER_TYPE_TAGM)
						pM->WriteReg32(&pRegs->TagM.Width, pNumberWidth->GetIntNumber());

					if(Type == GTP_HITPATTER_TYPE_TOF)
						v = pM->ReadReg32(&pRegs->TOF.Width);
					else if(Type == GTP_HITPATTER_TYPE_PS)
						v = pM->ReadReg32(&pRegs->PS.Width);
					else if(Type == GTP_HITPATTER_TYPE_ST)
						v = pM->ReadReg32(&pRegs->ST.Width);
					else if(Type == GTP_HITPATTER_TYPE_TAGH)
						v = pM->ReadReg32(&pRegs->TagH.Width);
					else if(Type == GTP_HITPATTER_TYPE_TAGM)
						v = pM->ReadReg32(&pRegs->TagM.Width);

					pNumberWidth->SetIntNumber(v);
					pLabelWidth->SetText(Form("Actual Delay = %dns", (int)pNumberWidth->GetIntNumber()*4));

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
	TString					Name;
	int						Type;
	int						NBins;
	int						NDiv;
	
	TGNumberEntry			*pNumberDelay;
	TGNumberEntry			*pNumberWidth;

	TGLabel					*pLabelDelay;
	TGLabel					*pLabelWidth;

	TRootEmbeddedCanvas	*pCanvas;
	
	TH1D						*pH_Rate;
	TH1D						*pH_Hits;

	TGTextButton			*pButtonUpdateScalers;
};

#endif
