#ifndef DSC2_Scalers_H
#define DSC2_Scalers_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "dsc2.h"

class DSC2_Scalers : public TGCompositeFrame
{
public:
	DSC2_Scalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (DSC2_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrameButtons->AddFrame(pButtonAutoUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
				pButtonAutoUpdate->Associate(this);
			pFrameButtons->AddFrame(pButtonManualUpdate = new TGTextButton(pFrameButtons, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonManualUpdate->Associate(this);
			pFrameButtons->AddFrame(pLabelScalerInterval = new TGLabel(pFrameButtons, "Read Interval(sec):"), new TGLayoutHints(kLHintsCenterY | kLHintsNormal, 2));
			pFrameButtons->AddFrame(pNumEntryScalerInterval = new TGNumberEntry(pFrameButtons, 1, 3, NUM_SCALERINTERVAL, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 1.0, 1000.0), new TGLayoutHints(kLHintsNormal));
				pNumEntryScalerInterval->SetWidth(70);
				pNumEntryScalerInterval->SetEditable(kFALSE);
				pNumEntryScalerInterval->Associate(this);

		AddFrame(pFrameScalers = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameScalers->AddFrame(pTopLeftFrame = new TGVerticalFrame(pFrameScalers), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pTopLeftFrame->AddFrame(pVMEScalerCanvas = new TRootEmbeddedCanvas("VME Gated Scalers", pTopLeftFrame, 300, 300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pVMEScalerCanvas->GetCanvas()->SetBorderMode(0);

			pFrameScalers->AddFrame(pTopRightFrame = new TGVerticalFrame(pFrameScalers), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pTopRightFrame->AddFrame(pEXTScalerCanvas = new TRootEmbeddedCanvas("Externally Gated Scalers", pTopRightFrame, 300, 300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pEXTScalerCanvas->GetCanvas()->SetBorderMode(0);

		char buf[100];
		
		sprintf(buf, "TDC VME Gated Scalers: 0x%08X@%s", pM->BaseAddr, pM->GetName());
		pTDCVMEScalerHist = new TH1I(buf, NULL, 16, 1, 17);
		pTDCVMEScalerHist->SetStats(kFALSE);
		pTDCVMEScalerHist->SetNdivisions(16);
		pTDCVMEScalerHist->SetFillColor(4);
		pTDCVMEScalerHist->SetBarWidth(0.4);
		pTDCVMEScalerHist->SetBarOffset(0.05);

		sprintf(buf, "TRG VME Gated Scalers: 0x%08X@%s", pM->BaseAddr, pM->GetName());
		pTRGVMEScalerHist = new TH1I(buf, NULL, 16, 1, 17);
		pTRGVMEScalerHist->SetStats(kFALSE);
		pTRGVMEScalerHist->SetNdivisions(16);
		pTRGVMEScalerHist->SetFillColor(8);
		pTRGVMEScalerHist->SetBarWidth(0.4);
		pTRGVMEScalerHist->SetBarOffset(0.55);

		sprintf(buf, "TDC External Gated Scalers: 0x%08X@%s", pM->BaseAddr, pM->GetName());
		pTDCEXTScalerHist = new TH1I(buf, NULL, 16, 1, 17);
		pTDCEXTScalerHist->SetStats(kFALSE);
		pTDCEXTScalerHist->SetNdivisions(16);
		pTDCEXTScalerHist->SetFillColor(4);
		pTDCEXTScalerHist->SetBarWidth(0.4);
		pTDCEXTScalerHist->SetBarOffset(0.05);
		
		sprintf(buf, "TRG External Gated Scalers: 0x%08X@%s", pM->BaseAddr, pM->GetName());
		pTRGEXTScalerHist = new TH1I(buf, NULL, 16, 1, 17);
		pTRGEXTScalerHist->SetStats(kFALSE);
		pTRGEXTScalerHist->SetNdivisions(16);
		pTRGEXTScalerHist->SetFillColor(8);
		pTRGEXTScalerHist->SetBarWidth(0.4);
		pTRGEXTScalerHist->SetBarOffset(0.55);

		pVMEScalerLegend = new TLegend(0.63, 0.79, 0.9, 0.9);
		pVMEScalerLegend->AddEntry(pTDCVMEScalerHist, "TDC VME Gate Scaler", "f");
		pVMEScalerLegend->AddEntry(pTRGVMEScalerHist, "TRIG VME Gate Scaler", "f");
		pEXTScalerLegend = new TLegend(0.63, 0.79, 0.9, 0.9);
		pEXTScalerLegend->AddEntry(pTDCEXTScalerHist, "TDC External Gate Scaler", "f");
		pEXTScalerLegend->AddEntry(pTRGEXTScalerHist, "TRIG External Gate Scaler", "f");

		UpdateVMEGateHistograms();
		UpdateEXTGateHistograms();

		pTimerUpdate = new TTimer(this, pNumEntryScalerInterval->GetIntNumber() * 1000);
	}

private:
	Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
			ReadoutVMEScalers();
			ReadoutExternalScalers();

			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(pNumEntryScalerInterval->GetIntNumber() * 1000, kTRUE);

			return kTRUE;
		}
		return kFALSE;
	}

	Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
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
						pNumEntryScalerInterval->SetEditable(kTRUE);
						pTimerUpdate->Start(pNumEntryScalerInterval->GetIntNumber() * 1000, kTRUE);
					}
					else
					{
						pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Manual"));
						pNumEntryScalerInterval->SetEditable(kFALSE);
						pTimerUpdate->TurnOff();
					}
					break;
				case BTN_MANUALUPDATE:
					ReadoutVMEScalers();
					ReadoutExternalScalers();
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
				}
				break;
			}
		case kC_TEXTENTRY:
			switch(GET_SUBMSG(msg))
			{
			case kTE_ENTER:
			case kTE_TAB:
			case kTE_TEXTCHANGED:
				switch(parm1)
				{
				case NUM_SCALERINTERVAL:
					pTimerUpdate->Stop();
					pTimerUpdate->Start(pNumEntryScalerInterval->GetIntNumber() * 1000, kTRUE);
					break;
				}
				break;
			}
			break;
		}
		return kTRUE;
	}

	Bool_t ReadoutVMEScalers()
	{
		unsigned int RefScaler;
		unsigned int Scalers[32];

		pM->WriteReg32(&pRegs->ScalerLatchGrp2, 0x1);
		if(!pM->BlkReadReg32(&pRegs->TrgScalerGrp2[0], &Scalers[0], 32, CRATE_MSG_FLAGS_ADRINC))
			return kFALSE;
		RefScaler = pM->ReadReg32(&pRegs->refScalerGrp2);

		pTDCVMEScalerHist->Clear();
		pTRGVMEScalerHist->Clear();

		double t_ref = (double)RefScaler / DSC_REFERENCE_RATE;
		for(int i = 0; i < 16; i++)
		{
			if(t_ref >= 0.0)
			{
				double result = (double)Scalers[i] / t_ref;
				pTDCVMEScalerHist->SetBinContent(i+1, (unsigned int)result);
				result = (double)Scalers[i+16] / t_ref;
				pTRGVMEScalerHist->SetBinContent(i+1, (unsigned int)result);
			}
			else
			{
				pTDCVMEScalerHist->SetBinContent(i+1, 0);
				pTRGVMEScalerHist->SetBinContent(i+1, 0);
			}
		}
		UpdateVMEGateHistograms();

		return kTRUE;
	}

	Bool_t ReadoutExternalScalers()
	{
		unsigned int RefScaler;
		unsigned int Scalers[32];

		pM->WriteReg32(&pRegs->ScalerLatchGrp1, 0x1);
		if(!pM->BlkReadReg32(&pRegs->TrgScalerGrp1[0], &Scalers[0], 32, CRATE_MSG_FLAGS_ADRINC))
			return kFALSE;
		RefScaler = pM->ReadReg32(&pRegs->refScalerGrp1);

		pTDCEXTScalerHist->Clear();
		pTRGEXTScalerHist->Clear();

		double t_ref = (double)RefScaler / DSC_REFERENCE_RATE;
		for(int i = 0; i < 16; i++)
		{
			if(t_ref >= 0.0)
			{
				double result = (double)Scalers[i] / t_ref;
				pTDCEXTScalerHist->SetBinContent(i+1, (unsigned int)result);
				result = (double)Scalers[i+16] / t_ref;
				pTRGEXTScalerHist->SetBinContent(i+1, (unsigned int)result);
			}
			else
			{
				pTDCVMEScalerHist->SetBinContent(i+1, 0);
				pTRGVMEScalerHist->SetBinContent(i+1, 0);
			}
		}
		UpdateEXTGateHistograms();

		return kTRUE;
	}

	void UpdateVMEGateHistograms()
	{
		pVMEScalerCanvas->GetCanvas()->cd();

		pTDCVMEScalerHist->GetXaxis()->CenterLabels();
		pTDCVMEScalerHist->GetXaxis()->SetTitle("Discriminator Channel");
		pTDCVMEScalerHist->GetXaxis()->CenterTitle();
		pTDCVMEScalerHist->GetYaxis()->SetTitle("Rate(Hz)");
		pTDCVMEScalerHist->GetYaxis()->CenterTitle();

		pTRGVMEScalerHist->GetXaxis()->CenterLabels();
		pTRGVMEScalerHist->GetXaxis()->SetTitle("Discriminator Channel");
		pTRGVMEScalerHist->GetXaxis()->CenterTitle();
		pTRGVMEScalerHist->GetYaxis()->SetTitle("Rate(Hz)");
		pTRGVMEScalerHist->GetYaxis()->CenterTitle();

		if(pTDCVMEScalerHist->GetMaximum() > pTRGVMEScalerHist->GetMaximum())
		{
			pTDCVMEScalerHist->Draw("bar2");
			pTRGVMEScalerHist->Draw("bar2,same");
		}
		else
		{
			pTRGVMEScalerHist->Draw("bar2");
			pTDCVMEScalerHist->Draw("bar2,same");
		}
		pVMEScalerLegend->Draw();

		pVMEScalerCanvas->GetCanvas()->Modified();
		pVMEScalerCanvas->GetCanvas()->Update();
	}

	void UpdateEXTGateHistograms()
	{
		pEXTScalerCanvas->GetCanvas()->cd();
		pTDCEXTScalerHist->GetXaxis()->CenterLabels();
		pTDCEXTScalerHist->GetXaxis()->SetTitle("Discriminator Channel");
		pTDCEXTScalerHist->GetXaxis()->CenterTitle();
		pTDCEXTScalerHist->GetYaxis()->SetTitle("Rate(Hz)");
		pTDCEXTScalerHist->GetYaxis()->CenterTitle();

		pTRGEXTScalerHist->GetXaxis()->CenterLabels();
		pTRGEXTScalerHist->GetXaxis()->SetTitle("Discriminator Channel");
		pTRGEXTScalerHist->GetXaxis()->CenterTitle();
		pTRGEXTScalerHist->GetYaxis()->SetTitle("Rate(Hz)");
		pTRGEXTScalerHist->GetYaxis()->CenterTitle();

		if(pTDCEXTScalerHist->GetMaximum() > pTRGEXTScalerHist->GetMaximum())
		{
			pTDCEXTScalerHist->Draw("bar2");
			pTRGEXTScalerHist->Draw("bar2,same");
		}
		else
		{
			pTRGEXTScalerHist->Draw("bar2");
			pTDCEXTScalerHist->Draw("bar2,same");
		}
		pEXTScalerLegend->Draw();

		pEXTScalerCanvas->GetCanvas()->Modified();
		pEXTScalerCanvas->GetCanvas()->Update();
	}

	enum Buttons
	{
		NUM_SCALERINTERVAL,
		BTN_AUTOUPDATE,
		BTN_MANUALUPDATE
	};

	ModuleFrame				*pM;
	DSC2_regs				*pRegs;

	TTimer					*pTimerUpdate;

	TGTextButton			*pButtonAutoUpdate;
	TGTextButton			*pButtonManualUpdate;

	TH1I					*pTDCVMEScalerHist;
	TH1I					*pTRGVMEScalerHist;
	TH1I					*pTDCEXTScalerHist;
	TH1I					*pTRGEXTScalerHist;
	TLegend					*pVMEScalerLegend;
	TLegend					*pEXTScalerLegend;

	TGHorizontalFrame		*pFrameButtons;
	TGHorizontalFrame		*pFrameScalers;
	TGVerticalFrame			*pTopLeftFrame;
	TGVerticalFrame			*pTopRightFrame;

	TRootEmbeddedCanvas		*pVMEScalerCanvas;
	TRootEmbeddedCanvas		*pEXTScalerCanvas;
	TGLabel					*pLabelScalerInterval;
	TGNumberEntry			*pNumEntryScalerInterval;
};

#endif
