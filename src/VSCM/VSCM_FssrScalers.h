#ifndef VSCM_FssrScalers_H
#define VSCM_FssrScalers_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "vscm.h"

#define UDPATETIME_MAX	60

class VSCM_FssrScalers	: public TGCompositeFrame
{
public:
	VSCM_FssrScalers(const TGWindow *p, ModuleFrame *pModule, unsigned int idx) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (VSCM_regs *)pM->BaseAddr;
		FSSRIdx = idx;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pTF1->AddFrame(pButtonAutoUpdate = new TGTextButton(pTF1, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
			pTF1->AddFrame(pButtonManualUpdate = new TGTextButton(pTF1, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			pTF1->AddFrame(pSliderUpdateTime = new TGHSlider(pTF1, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);

			pButtonAutoUpdate->Associate(this);
			pButtonManualUpdate->Associate(this);
			pSliderUpdateTime->Associate(this);

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTF1->AddFrame(pTextScalers = new TGTextView(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		AddFrame(pCanvasScalers = new TRootEmbeddedCanvas("DCRB Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasScalers->GetCanvas()->SetBorderMode(0);
			pCanvasScalers->GetCanvas()->Divide(3, 2);

			char buf[100];
			sprintf(buf, "FSSR Channels %d-%d", FSSRIdx*128, FSSRIdx*128+127);
			//pHistScalers = new TH1I(buf, NULL, 128, FSSRIdx*128, FSSRIdx*128+128);
			pHistScalers = new TH1I(buf, NULL, 128, 0, 127);
			pHistScalers->SetStats(kFALSE);
			pHistScalers->SetNdivisions(128);
			pHistScalers->SetFillColor(4);

		UpdateScalers();

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
						UpdateScalers();
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
			UpdateScalers();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	char *ReadNormalizedScaler(char *buf, const char *prefix, unsigned int ref, unsigned int scaler)
	{
		double normalized = 125.0e6 * (double)scaler / (double)ref;
		sprintf(buf, "%s = %08X, %.3fHz", prefix, scaler, normalized);
		return buf;
	}

	void UpdateScalers()
	{
		char buf[100];
		unsigned int ref/*, refHist*/;

		pM->WriteReg32(&pRegs->ScalerLatch, 0xFF & ~(1<<FSSRIdx));
		ref = pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerRef);
//		refHist = ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerStripTime);
		
		pTextScalers->Clear();
		switch(FSSRIdx)
		{
			case FSSR_H1_U1_IDX: pTextScalers->AddLineFast("------ HFCB 1 U1 Scalers ------"); break;
			case FSSR_H1_U2_IDX: pTextScalers->AddLineFast("------ HFCB 1 U2 Scalers ------"); break;
			case FSSR_H1_U3_IDX: pTextScalers->AddLineFast("------ HFCB 1 U3 Scalers ------"); break;
			case FSSR_H1_U4_IDX: pTextScalers->AddLineFast("------ HFCB 1 U4 Scalers ------"); break;
			case FSSR_H2_U1_IDX: pTextScalers->AddLineFast("------ HFCB 2 U1 Scalers ------"); break;
			case FSSR_H2_U2_IDX: pTextScalers->AddLineFast("------ HFCB 2 U2 Scalers ------"); break;
			case FSSR_H2_U3_IDX: pTextScalers->AddLineFast("------ HFCB 2 U3 Scalers ------"); break;
			case FSSR_H2_U4_IDX: pTextScalers->AddLineFast("------ HFCB 2 U4 Scalers ------"); break;
		}
		pTextScalers->AddLineFast("");
		sprintf(buf, "LastStatusWord = 0x%08X", pM->ReadReg32(&pRegs->Fssr[FSSRIdx].LastStatusWord)); pTextScalers->AddLineFast(buf);
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "StatusWords   ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerStatusWord)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "EventWords    ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerEvent)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "TotalWords    ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerWords)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "IdleWords     ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerIdle)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "AcqBCO        ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerAqBco)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "MarkErrors    ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerMarkErr)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "StripEncErrors", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerEncErr)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "ChipIdErrors  ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerChipIdErr)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "GotHit        ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerGotHit)));
		pTextScalers->AddLineFast(ReadNormalizedScaler(buf, "HistTime      ", ref, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerStripTime)));
		pTextScalers->Update();

		pHistScalers->Clear();
		for(int i = 0; i < 128; i++)
			pHistScalers->SetBinContent(i+1, pM->ReadReg32(&pRegs->Fssr[FSSRIdx].ScalerStrip));

		pM->WriteReg32(&pRegs->ScalerLatch, 0xFF);

		pCanvasScalers->GetCanvas()->cd();
//		pHistScalers->GetXaxis()->CenterLabels();
		pHistScalers->GetXaxis()->SetTitle("FSSR Channel");
		pHistScalers->GetXaxis()->CenterTitle();
		pHistScalers->GetYaxis()->SetTitle("Count");
		pHistScalers->GetXaxis()->CenterTitle();
		pHistScalers->Draw("bar");
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

	ModuleFrame				*pM;
	VSCM_regs				*pRegs;

	TTimer					*pTimerUpdate;

	TGTextView				*pTextScalers;

	TGSlider					*pSliderUpdateTime;
	TGTextButton			*pButtonAutoUpdate;
	TGTextButton			*pButtonManualUpdate;

	TRootEmbeddedCanvas	*pCanvasScalers;
	TH1I						*pHistScalers;

	unsigned int			FSSRIdx;
};

#endif
