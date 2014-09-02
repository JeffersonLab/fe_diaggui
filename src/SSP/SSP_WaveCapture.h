#ifndef SSP_WaveCapture_H
#define SSP_WaveCapture_H

#include "RootHeader.h"
#include "VMERemote.h"
#include "ssp.h"

class SSP_WaveCapture	: public TGCompositeFrame
{
public:
	SSP_WaveCapture(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (SSP_regs *)pM->BaseAddr;

		TGCompositeFrame *pF1, *pF2, *pF3;

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pF1->AddFrame(pComboWaveSelect = new TGComboBox(pF1, CMB_WAVESEL), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				for(int i = 0; i < 8; i++)
					pComboWaveSelect->AddEntry(Form("Fiber %d", i), i);
				pComboWaveSelect->AddEntry(Form("VXS0,1"), 8);
				pComboWaveSelect->AddEntry(Form("GTP"), 9);
				pComboWaveSelect->Resize(100, 20);
				pComboWaveSelect->Select(0);
				pComboWaveSelect->Associate(this);
			pF1->AddFrame(pButtonAutoTrigger = new TGTextButton(pF1, new TGHotString("Update Mode: Manual"), BTN_WAVE_AUTOTRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoTrigger->SetWidth(80);
				pButtonAutoTrigger->SetEnabled(kTRUE);
				pButtonAutoTrigger->AllowStayDown(kTRUE);
				pButtonAutoTrigger->Associate(this);
			pF1->AddFrame(pButtonStartTrigger = new TGTextButton(pF1, new TGHotString("Start Trigger"), BTN_WAVE_STARTTRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonStartTrigger->Associate(this);
			pF1->AddFrame(pButtonStopTrigger = new TGTextButton(pF1, new TGHotString("Stop Trigger"), BTN_WAVE_STOPTRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonStopTrigger->SetEnabled(kFALSE);
				pButtonStopTrigger->Associate(this);
			pF1->AddFrame(pButtonForceTrigger = new TGTextButton(pF1, new TGHotString("Force Trigger"), BTN_WAVE_FORCETRIG), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));		
				pButtonForceTrigger->Associate(this);
			pF1->AddFrame(pButtonAutoZoom = new TGTextButton(pF1, new TGHotString("Auto Zoom")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));		
				pButtonAutoZoom->AllowStayDown(kTRUE);

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pF1->AddFrame(pF2 = new TGVerticalFrame(pF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pF2->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pF2, 800, 600), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pCanvas->GetCanvas()->SetBorderMode(0);
				pF2->AddFrame(pF3 = new TGHorizontalFrame(pF2), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pLabelThreshold = new TGLabel(pF3, new TGString("Trig Threshold >= ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pF3->AddFrame(pNumberThreshold = new TGNumberEntry(pF3, 0, 6, -1, TGNumberFormat::kNESInteger), new TGLayoutHints(kLHintsLeft));
						pNumberThreshold->SetWidth(80);
					pF3->AddFrame(pButtonCloneGraph = new TGTextButton(pF3, new TGHotString("Copy"), BTN_GRAPH_CLONE), new TGLayoutHints(kLHintsLeft));
						pButtonCloneGraph->Associate(this);
			pF1->AddFrame(pTextViewRawData = new TGTextView(pF1, 150), new TGLayoutHints(kLHintsLeft | kLHintsExpandY));
			
		pGraph = new TH1D("h1", "h1", 1, 0.0, 4.0);
		pGraph->SetStats(kFALSE);
		
		pCanvas->GetCanvas()->cd();
		pGraph->Draw("L");
		pGraph->GetXaxis()->SetTitle("Time(ns)");

		ResizeGraph();
		DrawGraph();
		
		pTimerUpdate = new TTimer(this, 100, kTRUE);
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_COMBOBOX:
				switch(parm1)
				{
					case CMB_WAVESEL:
						ResizeGraph();
						break;
				}
				break;
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_WAVE_AUTOTRIG:
						if(pButtonAutoTrigger->IsDown())
							pButtonAutoTrigger->SetText(new TGHotString("Update Mode: Auto"));
						else
							pButtonAutoTrigger->SetText(new TGHotString("Update Mode: Manual"));
						break;
					case BTN_WAVE_STARTTRIG:
						pButtonStartTrigger->SetEnabled(kFALSE);
						pButtonStopTrigger->SetEnabled(kTRUE);
						SetSSPWaveTrigger();
						pTimerUpdate->Start(100, kTRUE);
						break;
					case BTN_WAVE_STOPTRIG:
						pButtonStartTrigger->SetEnabled(kTRUE);
						pButtonStopTrigger->SetEnabled(kFALSE);
						pTimerUpdate->TurnOff();
						break;
					case BTN_WAVE_FORCETRIG:
						pButtonForceTrigger->SetEnabled(kFALSE);
						SetSSPWaveTrigger(kTRUE);
						pTimerUpdate->Start(100, kTRUE);
						break;
					case BTN_GRAPH_CLONE:
						pCanvas->GetCanvas()->DrawClone();
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
			}
			break;
		default:
			break;
		}
		return kTRUE;
	}
	
	virtual Bool_t HandleTimer(TTimer *t)
	{
		int idx = pComboWaveSelect->GetSelected();
		if(pTimerUpdate->HasTimedOut())
		{
			unsigned int status = pM->ReadReg32(&pRegs->Ser[idx].MonStatus);

			if(status & 0x1)
			{
				UpdateSSPWaveCaptures();
				if(pButtonAutoTrigger->IsDown())
				{
					SetSSPWaveTrigger();
					pTimerUpdate->Start(100, kTRUE);
				}
				else
				{
					pButtonStartTrigger->SetEnabled(kTRUE);
					pButtonStopTrigger->SetEnabled(kFALSE);
				}
			}
			else
				pTimerUpdate->Start(100, kTRUE);
		}
		return kTRUE;
	}

	void SetSSPWaveTrigger(Bool_t force = kFALSE)
	{
		int idx = pComboWaveSelect->GetSelected();
		
		pM->ReadReg32(&pRegs->Ser[idx].MonData[2]);
		
		if(force)
			pM->WriteReg32(&pRegs->Ser[idx].MonThr[0], 0);
		else
			pM->WriteReg32(&pRegs->Ser[idx].MonThr[0], pNumberThreshold->GetIntNumber());

		pM->WriteReg32(&pRegs->Ser[idx].MonMask[0], 0x0);
		pM->WriteReg32(&pRegs->Ser[idx].MonMask[1], 0x0);
		pM->WriteReg32(&pRegs->Ser[idx].MonMask[2], 0x0);
		
		pM->WriteReg32(&pRegs->Ser[idx].MonCtrl, 0x0);
		pM->WriteReg32(&pRegs->Ser[idx].MonCtrl, 0x1);
	}

	void UpdateSSPWaveCaptures()
	{
		unsigned int val;
		unsigned int min = 0xFFFFFFFF, max = 0x0;
		int npoints = GetNPoints();
		int idx = pComboWaveSelect->GetSelected();
		
		pTextViewRawData->Clear();
		pTextViewRawData->AddLineFast("Raw Data:");

		pM->WriteReg32(&pRegs->Ser[idx].MonCtrl, 0x0);

		for(int i = 0; i < npoints; i++)
		{
			if((0 <= idx) && (idx < 8))
			{
				if(i & 0x1)
				{
					val = pM->ReadReg32(&pRegs->Ser[idx].MonData[1]);
					pM->ReadReg32(&pRegs->Ser[idx].MonData[2]);
				}
				else
					val = pM->ReadReg32(&pRegs->Ser[idx].MonData[0]);
			}
			else
			{
				val = pM->ReadReg32(&pRegs->Ser[idx].MonData[0]);
				pM->ReadReg32(&pRegs->Ser[idx].MonData[1]);
			}
			
			pTextViewRawData->AddLineFast(Form("%4d: 0x%08X", i, val));
			
			val = val % 0x1000000;

			if(val < min)
				min = val;
			if(val > max)
				max = val;

			pGraph->SetBinContent(i+1, (double)val);
		}
		
		if(pButtonAutoZoom->IsDown())
		{
			pGraph->GetXaxis()->SetRangeUser(0.0, 4092.0);
			pGraph->GetYaxis()->SetRangeUser((double)min, (double)max);
		}
		
		DrawGraph();
		pButtonForceTrigger->SetEnabled(kTRUE);
		pTextViewRawData->Update();
	}
	
	int GetNPoints()
	{
		int idx = pComboWaveSelect->GetSelected();
		if((idx >= 0) && (idx <= 7))
			return 1024;
		else
			return 512;
	}

	void ResizeGraph()
	{
		int idx = pComboWaveSelect->GetSelected();
		const char *name[] = {
				"Fiber 0 Serdes Data",
				"Fiber 1 Serdes Data",
				"Fiber 2 Serdes Data",
				"Fiber 3 Serdes Data",
				"Fiber 4 Serdes Data",
				"Fiber 5 Serdes Data",
				"Fiber 6 Serdes Data",
				"Fiber 7 Serdes Data",
				"VXS Lane 0,1 Serdes Data",
				"GTP Serdes Data"
			};
			
		int npoints = GetNPoints();
		
		pGraph->SetBins(npoints, 0.0, 4.0*npoints);
		
		for(int i = 0; i < npoints+2; i++)
			pGraph->SetBinContent(i, 0.0);
		
		pGraph->SetTitle(name[idx]);
		
		DrawGraph();
	}

	void DrawGraph()
	{
		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();
	}

private:
	enum
	{
		BTN_WAVE_AUTOTRIG,
		BTN_WAVE_STARTTRIG,
		BTN_WAVE_STOPTRIG,
		BTN_WAVE_FORCETRIG,
		BTN_GRAPH_CLONE,
		CMB_WAVESEL
	};
	
	ModuleFrame				*pM;
	SSP_regs					*pRegs;

	TTimer					*pTimerUpdate;

	TGTextView				*pTextViewRawData;

	TGTextButton			*pButtonAutoTrigger;
	TGTextButton			*pButtonStartTrigger;
	TGTextButton			*pButtonStopTrigger;
	TGTextButton			*pButtonForceTrigger;
	TGTextButton			*pButtonAutoZoom;
	TGComboBox				*pComboWaveSelect;
	
	TRootEmbeddedCanvas	*pCanvas;
	TH1D						*pGraph;
	TGNumberEntry			*pNumberThreshold;
	TGLabel					*pLabelThreshold;
	TGTextButton			*pButtonCloneGraph;
};

#endif
