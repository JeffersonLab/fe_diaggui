#ifndef SSPHPS_PositionHist_H
#define SSPHPS_PositionHist_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ssp.h"
#include "VMERemote.h"

#define UDPATETIME_MAX		60

class SSPHPS_PositionHist	: public TGCompositeFrame
{
public:
	SSPHPS_PositionHist(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pVMEClient = pClient;
		pSSPregs = (SSP_regs *)baseAddr;

		TGCompositeFrame *tF1;

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			tF1->AddFrame(pButtonAutoUpdate = new TGTextButton(tF1, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
			tF1->AddFrame(pButtonManualUpdate = new TGTextButton(tF1, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			tF1->AddFrame(pSliderUpdateTime = new TGHSlider(tF1, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);

			pButtonAutoUpdate->Associate(this);
			pButtonManualUpdate->Associate(this);
			pSliderUpdateTime->Associate(this);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			tF1->AddFrame(new TGLabel(tF1, new TGString("Elapsed Time Top:")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			tF1->AddFrame(pLabelElapsedTimeTop = new TGLabel(tF1, new TGString("0")), new TGLayoutHints(kLHintsRight, 0, 0, 2, 0));
				pLabelElapsedTimeTop->SetWidth(150);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			tF1->AddFrame(new TGLabel(tF1, new TGString("Elapsed Time Bottom:")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			tF1->AddFrame(pLabelElapsedTimeBot = new TGLabel(tF1, new TGString("0")), new TGLayoutHints(kLHintsRight, 0, 0, 2, 0));
				pLabelElapsedTimeBot->SetWidth(150);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			tF1->AddFrame(pCanvasPositionHist = new TRootEmbeddedCanvas(0, tF1, 100, 100), new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pCanvasPositionHist->GetCanvas()->SetBorderMode(0);

		gStyle->SetPalette(1, NULL);

		pCanvasPositionHist->GetCanvas()->cd();
		pHistClusterPosition = new TH2I("Cluster Distribution", "Cluster Distribution;X;Y", 46, -22.0, 24.0, 11, -5.0, 6.0);

		pHistClusterPosition->GetXaxis()->CenterLabels();
		pHistClusterPosition->GetXaxis()->SetNdivisions(46, kFALSE);
		pHistClusterPosition->GetXaxis()->SetTickLength(1);
		pHistClusterPosition->GetYaxis()->CenterLabels();
		pHistClusterPosition->GetYaxis()->SetNdivisions(11, kFALSE);
		pHistClusterPosition->GetYaxis()->SetTickLength(1);
		pHistClusterPosition->Draw("COLZTEXT");

		UpdateHistograms(kTRUE);

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
						UpdateHistograms();
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
			UpdateHistograms();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	void UpdateHistograms(Bool_t bInit = kFALSE)
	{
		if(!bInit)
		{
			unsigned int HistogramBufferTop[1024];
			unsigned int HistogramBufferBot[1024];
			unsigned int TopElapsedTime, BotElapsedTime;

			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TopPositionHistData, 0);
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.BottomPositionHistData, 0);
			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TopPositionHistTime, &TopElapsedTime);
			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.BottomPositionHistTime, &BotElapsedTime);
			pVMEClient->BlkReadVME32((unsigned int)&pSSPregs->HPSRegs.TopPositionHistData, HistogramBufferTop, 1024, 1);
			pVMEClient->BlkReadVME32((unsigned int)&pSSPregs->HPSRegs.BottomPositionHistData, HistogramBufferBot, 1024, 1);
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TopPositionHistData, 1);
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.BottomPositionHistData, 1);

			pHistClusterPosition->Reset();

			double tscale;
			int x, y;
			for(int i = 0; i < 1024; i++)
			{
				if(TopElapsedTime) tscale = 250.0E6 / TopElapsedTime;
				else tscale = 1;
				x = (i>>0) & 0x3f;
				y = (i>>6) & 0xf;
				if(x & 0x20) x |= 0xFFFFFFC0;
				if(y & 0x08) y |= 0xFFFFFFF0;
				pHistClusterPosition->Fill(x, y, tscale*(double)HistogramBufferTop[i]);

				if(BotElapsedTime) tscale = 250.0E6 / BotElapsedTime;
				else tscale = 1;
				x = (i>>0) & 0x3f;
				y = (i>>6) & 0xf;
				if(x & 0x20) x |= 0xFFFFFFC0;
				if(y & 0x08) y |= 0xFFFFFFF0;
				pHistClusterPosition->Fill(x, y, tscale*(double)HistogramBufferBot[i]);
			}
			TGString *pStr;
			
			pStr = new TGString;
			pStr->Format("%.3f(sec)", (double)TopElapsedTime * 4.0E-9);
			pLabelElapsedTimeTop->SetText(pStr);

			pStr = new TGString;
			pStr->Format("%.3f(sec)", (double)BotElapsedTime * 4.0E-9);
			pLabelElapsedTimeBot->SetText(pStr);
		}
		pCanvasPositionHist->GetCanvas()->Modified();
		pCanvasPositionHist->GetCanvas()->Update();
	}

private:

	enum Buttons
	{
		BTN_LOGMODE,
		BTN_AUTOUPDATE,
		BTN_MANUALUPDATE,
		SDR_UPDATETIME,
		EDT_ENERGYBIN
	};

	VMERemote			*pVMEClient;
	SSP_regs			*pSSPregs;

	TTimer				*pTimerUpdate;

	TGSlider			*pSliderUpdateTime;
	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;
	TGLabel				*pLabelElapsedTimeTop;
	TGLabel				*pLabelElapsedTimeBot;

	TH2I				*pHistClusterPosition;

	TRootEmbeddedCanvas *pCanvasPositionHist;
};

#endif
