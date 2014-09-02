#ifndef SSP_HPS_TrgHist_H
#define SSP_HPS_TrgHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "ssp.h"

#define UDPATETIME_MAX			60
//#define FADC250_CH_BINS_PER_SEC	32*1024*1024

class SSP_HPS_TrgHist	: public TGCompositeFrame
{
public:
	SSP_HPS_TrgHist(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		static int inst = 0;

		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (SSP_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pTF1->AddFrame(pButtonNormalize = new TGTextButton(pTF1, new TGHotString("Normalize")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonNormalize->AllowStayDown(kTRUE);
			pTF1->AddFrame(pButtonAutoUpdate = new TGTextButton(pTF1, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
				pButtonAutoUpdate->Associate(this);
			pTF1->AddFrame(pButtonManualUpdate = new TGTextButton(pTF1, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonManualUpdate->Associate(this);
			pTF1->AddFrame(pSliderUpdateTime = new TGHSlider(pTF1, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);
				pSliderUpdateTime->Associate(this);

		TGCanvas *pTGCanvas;
		AddFrame(pTGCanvas = new TGCanvas(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTGCanvas->SetContainer(pTF1 = new TGVerticalFrame(pTGCanvas->GetViewPort()));
				pTF1->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pTF1, 1300, 2300));//, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		//AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 100, 100), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

			TLegend *pLegend;

		gStyle->SetPalette(1, NULL);

		pCanvas->GetCanvas()->Divide(1,4);

		pCanvas->GetCanvas()->cd(1);
		pHistLatency[0] = new TH1I("TopClusterLatency", "ClusterLatency", 1024, 0.0, 4.0*1024.0);
		pHistLatency[0]->GetXaxis()->SetTitle("Latency(ns)");
		pHistLatency[0]->GetXaxis()->SetRangeUser(0.0, 4096.0);
		pHistLatency[0]->GetYaxis()->SetTitle("Counts");
		pHistLatency[0]->GetYaxis()->CenterTitle();
		pHistLatency[0]->SetLineColor(kBlue);
		pHistLatency[0]->SetStats(0);
		pHistLatency[0]->Draw();
		pHistLatency[1] = new TH1I("BotClusterLatency", "ClusterLatency", 1024, 0.0, 4.0*1024.0);
		pHistLatency[1]->GetXaxis()->SetTitle("Latency(ns)");
		pHistLatency[1]->GetXaxis()->SetRangeUser(0.0, 4096.0);
		pHistLatency[1]->GetYaxis()->SetTitle("Counts");
		pHistLatency[1]->GetYaxis()->CenterTitle();
		pHistLatency[1]->SetLineColor(kRed);
		pHistLatency[1]->SetStats(0);
		pHistLatency[1]->Draw("same");
		pLegend = new TLegend(0.8,0.8,0.9,0.9);
		pLegend->AddEntry(pHistLatency[0], "TopClusters");
		pLegend->AddEntry(pHistLatency[1], "BotClusters");
		pLegend->Draw();

		pCanvas->GetCanvas()->cd(2);
		pHistPosition = new TH2I("ClusterPosition", "ClusterPosition;X;Y", 46, -23.0, 23.0, 11, -5.0, 6.0);
		pHistPosition->SetStats(0);
		pHistPosition->GetXaxis()->CenterLabels();
		pHistPosition->GetXaxis()->SetNdivisions(46, kFALSE);
		pHistPosition->GetXaxis()->SetTickLength(1);
		pHistPosition->GetYaxis()->CenterLabels();
		pHistPosition->GetYaxis()->SetNdivisions(11, kFALSE);
		pHistPosition->GetYaxis()->SetTickLength(1);
		pHistPosition->Draw("COLZTEXT");

		pCanvas->GetCanvas()->cd(3);
		pHistEnergy[0] = new TH1I("TopClusterEnergy", "ClusterEnergy", 1024, 0.0, 8.0*1024.0);
		pHistEnergy[0]->GetXaxis()->SetTitle("Energy(MeV)");
		pHistEnergy[0]->GetXaxis()->SetRangeUser(0.0, 8192.0);
		pHistEnergy[0]->GetYaxis()->SetTitle("Counts");
		pHistEnergy[0]->GetYaxis()->CenterTitle();
		pHistEnergy[0]->SetLineColor(kBlue);
		pHistEnergy[0]->SetStats(0);
		pHistEnergy[0]->Draw();
		pHistEnergy[1] = new TH1I("BotClusterEnergy", "ClusterEnergy", 1024, 0.0, 8.0*1024.0);
		pHistEnergy[1]->GetXaxis()->SetTitle("Energy(MeV)");
		pHistEnergy[1]->GetXaxis()->SetRangeUser(0.0, 8192.0);
		pHistEnergy[1]->GetYaxis()->SetTitle("Counts");
		pHistEnergy[1]->GetYaxis()->CenterTitle();
		pHistEnergy[1]->SetLineColor(kRed);
		pHistEnergy[1]->SetStats(0);
		pHistEnergy[1]->Draw("same");
		pLegend = new TLegend(0.8,0.8,0.9,0.9);
		pLegend->AddEntry(pHistEnergy[0], "TopClusters");
		pLegend->AddEntry(pHistEnergy[1], "BotClusters");
		pLegend->Draw();

		pCanvas->GetCanvas()->cd(4);
		pHistNHits[0] = new TH1I("TopClusterNHits", "ClusterNHits", 16, 0.0, 16.0);
		pHistNHits[0]->GetXaxis()->SetTitle("NHits");
		pHistNHits[0]->GetXaxis()->SetRangeUser(0.0, 16.0);
		pHistNHits[0]->GetYaxis()->SetTitle("Counts");
		pHistNHits[0]->GetYaxis()->CenterTitle();
		pHistNHits[0]->SetLineColor(kBlue);
		pHistNHits[0]->SetStats(0);
		pHistNHits[0]->Draw();
		pHistNHits[1] = new TH1I("BotClusterNHits", "ClusterNHits", 16, 0.0, 16.0);
		pHistNHits[1]->GetXaxis()->SetTitle("NHits");
		pHistNHits[1]->GetXaxis()->SetRangeUser(0.0, 16.0);
		pHistNHits[1]->GetYaxis()->SetTitle("Counts");
		pHistNHits[1]->GetYaxis()->CenterTitle();
		pHistNHits[1]->SetLineColor(kRed);
		pHistNHits[1]->SetStats(0);
		pHistNHits[1]->Draw("same");
		pLegend = new TLegend(0.8,0.8,0.9,0.9);
		pLegend->AddEntry(pHistNHits[0], "TopClusters");
		pLegend->AddEntry(pHistNHits[1], "BotClusters");
		pLegend->Draw();

		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);

		inst++;
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
						UpdateHistogram();
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
			UpdateHistogram();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	void UpdateLatencyHistogram()
	{
		unsigned int buf[1024];

		pCanvas->GetCanvas()->cd(1);

		pM->BlkReadReg32(&pRegs->HpsClusterTop.HistLatency, buf, 1024, CRATE_MSG_FLAGS_NOADRINC);
		for(int i = 0; i < 1024; i++)
		{
			if(buf[i] > 0x80000000)
				pHistLatency[0]->SetBinContent(i, 0x7FFFFFFF);
			else
				pHistLatency[0]->SetBinContent(i, buf[i]);
		}

		pM->BlkReadReg32(&pRegs->HpsClusterBot.HistLatency, buf, 1024, CRATE_MSG_FLAGS_NOADRINC);
		for(int i = 0; i < 1024; i++)
		{
			if(buf[i] > 0x80000000)
				pHistLatency[1]->SetBinContent(i, 0x7FFFFFFF);
			else
				pHistLatency[1]->SetBinContent(i, buf[i]);
		}

		double max = (pHistLatency[0]->GetMaximum() > pHistLatency[1]->GetMaximum()) ?
		              pHistLatency[0]->GetMaximum() : pHistLatency[1]->GetMaximum();

		pHistLatency[0]->GetYaxis()->SetRangeUser(0.0, max);
		pHistLatency[1]->GetYaxis()->SetRangeUser(0.0, max);

		pHistLatency[0]->GetYaxis()->UnZoom();
		pHistLatency[1]->GetYaxis()->UnZoom();

		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();
	}

	void UpdatePositionHistogram()
	{
		unsigned int buf[1024];

		pCanvas->GetCanvas()->cd(3);

		pM->BlkReadReg32(&pRegs->HpsClusterTop.HistPosition, &buf[0], 512, CRATE_MSG_FLAGS_NOADRINC);
		pM->BlkReadReg32(&pRegs->HpsClusterBot.HistPosition, &buf[512], 512, CRATE_MSG_FLAGS_NOADRINC);

		pHistPosition->Reset();

		int x, y;
		for(int i = 0; i < 1024; i++)
		{
			if(buf[i] > 0x80000000)
				buf[i] = 0x7FFFFFFF;

			x = (i>>0) & 0x3F;
			y = (i>>6) & 0x7;

			if(x & 0x20) x |= 0xFFFFFFC0;
			if(i >= 512) y = -y;

			pHistPosition->Fill(x, y, buf[i]);
		}

		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();
	}

	void UpdateEnergyHistogram()
	{
		unsigned int buf[1024];

		pCanvas->GetCanvas()->cd(3);

		pM->BlkReadReg32(&pRegs->HpsClusterTop.HistEnergy, buf, 1024, CRATE_MSG_FLAGS_NOADRINC);
		for(int i = 0; i < 1024; i++)
		{
			if(buf[i] > 0x80000000)
				pHistEnergy[0]->SetBinContent(i, 0x7FFFFFFF);
			else
				pHistEnergy[0]->SetBinContent(i, buf[i]);
		}

		pM->BlkReadReg32(&pRegs->HpsClusterBot.HistEnergy, buf, 1024, CRATE_MSG_FLAGS_NOADRINC);
		for(int i = 0; i < 1024; i++)
		{
			if(buf[i] > 0x80000000)
				pHistEnergy[1]->SetBinContent(i, 0x7FFFFFFF);
			else
				pHistEnergy[1]->SetBinContent(i, buf[i]);
		}

		double max = (pHistEnergy[0]->GetMaximum() > pHistEnergy[1]->GetMaximum()) ?
		              pHistEnergy[0]->GetMaximum() : pHistEnergy[1]->GetMaximum();

		pHistEnergy[0]->GetYaxis()->SetRangeUser(0.0, max);
		pHistEnergy[1]->GetYaxis()->SetRangeUser(0.0, max);

		pHistEnergy[0]->GetYaxis()->UnZoom();
		pHistEnergy[1]->GetYaxis()->UnZoom();

		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();
	}

	void UpdateNHitsHistogram()
	{
		unsigned int buf[16];

		pCanvas->GetCanvas()->cd(4);

		pM->BlkReadReg32(&pRegs->HpsClusterTop.HistNHits, buf, 16, CRATE_MSG_FLAGS_NOADRINC);
		for(int i = 0; i < 16; i++)
		{
			if(buf[i] > 0x80000000)
				pHistNHits[0]->SetBinContent(i, 0x7FFFFFFF);
			else
				pHistNHits[0]->SetBinContent(i, buf[i]);
		}

		pM->BlkReadReg32(&pRegs->HpsClusterBot.HistNHits, buf, 16, CRATE_MSG_FLAGS_NOADRINC);
		for(int i = 0; i < 16; i++)
		{
			if(buf[i] > 0x80000000)
				pHistNHits[1]->SetBinContent(i, 0x7FFFFFFF);
			else
				pHistNHits[1]->SetBinContent(i, buf[i]);
		}

		double max = (pHistNHits[0]->GetMaximum() > pHistNHits[1]->GetMaximum()) ?
		              pHistNHits[0]->GetMaximum() : pHistNHits[1]->GetMaximum();

		pHistNHits[0]->GetYaxis()->SetRangeUser(0.0, max);
		pHistNHits[1]->GetYaxis()->SetRangeUser(0.0, max);

		pHistNHits[0]->GetYaxis()->UnZoom();
		pHistNHits[1]->GetYaxis()->UnZoom();

		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();
	}

	void UpdateHistogram(Bool_t bReadout = kTRUE)
	{
		pM->WriteReg32(&pRegs->HpsClusterTop.HistCtrl, 0);	// disable histograms
		pM->WriteReg32(&pRegs->HpsClusterBot.HistCtrl, 0);	// disable histograms

		UpdateLatencyHistogram();
		UpdatePositionHistogram();
		UpdateEnergyHistogram();
		UpdateNHitsHistogram();

		pM->WriteReg32(&pRegs->HpsClusterTop.HistCtrl, 0xF);	// enable histograms
		pM->WriteReg32(&pRegs->HpsClusterBot.HistCtrl, 0xF);	// enable histograms
/*
		unsigned int buf[1024];

		if(bReadout)
			pM->WriteReg32(&pRegs->hist_ctrl, 0);	// disable histograms

		for(int i = 0; i < 16; i++)
		{
			pHist[i]->ResetStats();

			if(bReadout)
			{
				pM->BlkReadReg32(&pRegs->hist_data[i], buf, 1024, CRATE_MSG_FLAGS_NOADRINC);
				if(pButtonNormalize->IsDown() == kTRUE)
				{
					double norm_bin, sum = 0;
					for(int j = 0; j < 1024; j++)
						sum += buf[j];

					for(int j = 0; j < 1024; j++)
					{
						if(buf[j] == 0xFFFFFFFF)
						{
							printf("FADC250_TrgHist: normalization failure - overflowed bins\n");
							break;
						}
						if(sum <= 0.0)
						{
							printf("FADC250_TrgHist: normalization failure - no time elapsed\n");
							break;
						}
						norm_bin = (double)buf[j] * FADC250_CH_BINS_PER_SEC / sum;
						pHist[i]->SetBinContent(j, norm_bin);
					}
					pHist[i]->GetYaxis()->SetTitle("Rate(Hz)");
				}
				else
				{
					for(int j = 0; j < 1024; j++)
					{
						if(buf[j] > 0x80000000)
							pHist[i]->SetBinContent(j, 0x7FFFFFFF);
						else
							pHist[i]->SetBinContent(j, buf[j]);
					}
					pHist[i]->GetYaxis()->SetTitle("Counts");
				}
			}
			else
			{
				for(int j = 0; j < 1024; j++)
					pHist[i]->SetBinContent(j, 0);
			}
			pCanvas->GetCanvas()->cd(i+1);
			pCanvas->GetCanvas()->Modified();
			pCanvas->GetCanvas()->Update();
		}

		if(bReadout)
			pM->WriteReg32(&pRegs->hist_ctrl, 1);	// enable histograms
*/
	}

private:

	enum Buttons
	{
		BTN_AUTOUPDATE		= 1002,
		BTN_MANUALUPDATE	= 1003,
		SDR_UPDATETIME		= 1100
	};
	
	ModuleFrame				*pM;
	SSP_regs					*pRegs;

	TTimer					*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvas;

	TGTextView				*pTextScalers;

	TH1I						*pHistLatency[2];
	TH2I						*pHistPosition;
	TH1I						*pHistEnergy[2];
	TH1I						*pHistNHits[2];

	TGSlider					*pSliderUpdateTime;

	TGTextButton			*pButtonAutoUpdate;
	TGTextButton			*pButtonManualUpdate;
	TGTextButton			*pButtonNormalize;
};

#endif
