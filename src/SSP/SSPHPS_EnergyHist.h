#ifndef SSPHPS_EnergyHist_H
#define SSPHPS_EnergyHist_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ssp.h"
#include "VMERemote.h"

#define UDPATETIME_MAX		60

#define ENERGY_BIN_MEV_DFT	50

class SSPHPS_EnergyHist	: public TGCompositeFrame
{
public:
	SSPHPS_EnergyHist(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr) : TGCompositeFrame(p, 400, 400)
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
			tF1->AddFrame(new TGLabel(tF1, new TGString("Energy Bin(MeV):")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			tF1->AddFrame(pNumberEnergyBinMeV = new TGNumberEntry(tF1, ENERGY_BIN_MEV_DFT, 4, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 1, 1000), new TGLayoutHints(kLHintsRight));
				pNumberEnergyBinMeV->SetWidth(100);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			tF1->AddFrame(new TGLabel(tF1, new TGString("Elapsed Time Top:")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			tF1->AddFrame(pLabelElapsedTimeTop = new TGLabel(tF1, new TGString("0")), new TGLayoutHints(kLHintsRight, 0, 0, 2, 0));
				pLabelElapsedTimeTop->SetWidth(150);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			tF1->AddFrame(new TGLabel(tF1, new TGString("Elapsed Time Bottom:")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			tF1->AddFrame(pLabelElapsedTimeBot = new TGLabel(tF1, new TGString("0")), new TGLayoutHints(kLHintsRight, 0, 0, 2, 0));
				pLabelElapsedTimeBot->SetWidth(150);

		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			tF1->AddFrame(pCanvasTopClusterEnergyHist = new TRootEmbeddedCanvas(0, tF1, 100, 100), new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pCanvasTopClusterEnergyHist->GetCanvas()->SetBorderMode(0);
			tF1->AddFrame(pCanvasBotClusterEnergyHist = new TRootEmbeddedCanvas(0, tF1, 100, 100), new TGLayoutHints(kLHintsRight | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pCanvasBotClusterEnergyHist->GetCanvas()->SetBorderMode(0);


		pCanvasTopClusterEnergyHist->GetCanvas()->cd();
		pHistTopClusterEnergy = new TH1I("Top Cluster Energy Distribution", "Top Cluster Distribution;Energy(MeV);Count", 256, 0, 255*ENERGY_BIN_MEV_DFT);
		pHistTopClusterEnergy->SetFillColor(4);
		pHistTopClusterEnergy->Draw("bar0");

		pCanvasBotClusterEnergyHist->GetCanvas()->cd();
		pHistBotClusterEnergy = new TH1I("Bot Cluster Energy Distribution", "Bot Cluster Distribution;Energy(MeV);Count", 256, 0, 255*ENERGY_BIN_MEV_DFT);
		pHistBotClusterEnergy->SetFillColor(4);
		pHistBotClusterEnergy->Draw("bar0");

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
			unsigned int HistogramBufferTop[256];
			unsigned int HistogramBufferBot[256];
			unsigned int TopElapsedTime, BotElapsedTime;

			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TopEnergyHistData, 0);
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.BottomEnergyHistData, 0);
			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TopEnergyHistTime, &TopElapsedTime);
			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.BottomEnergyHistTime, &BotElapsedTime);
			pVMEClient->BlkReadVME32((unsigned int)&pSSPregs->HPSRegs.TopEnergyHistData, HistogramBufferTop, 256, 1);
			pVMEClient->BlkReadVME32((unsigned int)&pSSPregs->HPSRegs.BottomEnergyHistData, HistogramBufferBot, 256, 1);
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TopEnergyHistData, 1);
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.BottomEnergyHistData, 1);

			pHistTopClusterEnergy->Reset();
			pHistBotClusterEnergy->Reset();
			pHistTopClusterEnergy->SetBins(256, 0.0, 255.0 * pNumberEnergyBinMeV->GetIntNumber());
			pHistBotClusterEnergy->SetBins(256, 0.0, 255.0 * pNumberEnergyBinMeV->GetIntNumber());
			for(int i = 0; i < 256; i++)
			{
				pHistTopClusterEnergy->SetBinContent(i, HistogramBufferTop[i]);
				pHistBotClusterEnergy->SetBinContent(i, HistogramBufferBot[i]);
			}
			TGString *pStr;
			
			pStr = new TGString;
			pStr->Format("%.3f(sec)", (double)TopElapsedTime * 4.0);
			pLabelElapsedTimeTop->SetText(pStr);

			pStr = new TGString;
			pStr->Format("%.3f(sec)", (double)BotElapsedTime * 4.0);
			pLabelElapsedTimeBot->SetText(pStr);
		}
		pCanvasTopClusterEnergyHist->GetCanvas()->Modified();
		pCanvasTopClusterEnergyHist->GetCanvas()->Update();

		pCanvasBotClusterEnergyHist->GetCanvas()->Modified();
		pCanvasBotClusterEnergyHist->GetCanvas()->Update();
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
	TGNumberEntry		*pNumberEnergyBinMeV;
	TGLabel				*pLabelElapsedTimeTop;
	TGLabel				*pLabelElapsedTimeBot;

	double				EnergyBinMeV;

	TH1I				*pHistTopClusterEnergy;
	TH1I				*pHistBotClusterEnergy;

	TRootEmbeddedCanvas *pCanvasTopClusterEnergyHist;
	TRootEmbeddedCanvas *pCanvasBotClusterEnergyHist;
};

#endif
