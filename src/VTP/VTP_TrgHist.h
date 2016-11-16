#ifndef VTP_TrgHist_H
#define VTP_TrgHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"

#define UDPATETIME_MAX							60

class VTP_TrgHist	: public TGCompositeFrame
{
public:
	VTP_TrgHist(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		static int inst = 0;

		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pTF1->AddFrame(pButtonNormalize = new TGTextButton(pTF1, new TGHotString("Normalize")), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonNormalize->AllowStayDown(kTRUE);
				pButtonNormalize->SetDown(kTRUE);
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
				pSliderUpdateTime->SetPosition(1);
				pSliderUpdateTime->Associate(this);

		// Use a resizable frame instead of viewport
		AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 1300, 2300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		gStyle->SetPalette(1, NULL);

		pCanvas->GetCanvas()->Divide(1,3);

		//////////////////////////////////		
		// Peak Position Canvas
		//////////////////////////////////		
      pCanvas->GetCanvas()->cd(1)->Divide(3, 1);
            
		pCanvas->GetCanvas()->cd(1)->cd(1);
      pCanvas->GetCanvas()->cd(1)->cd(1)->SetLogy(1);
      pHistPeak_U = new TH1F("U Peak Rates", "U Peak Rates", 36, 0.0, 36.0);
      pHistPeak_U->GetXaxis()->SetTitle("U Peak Rates(Hz)");
      pHistPeak_U->GetXaxis()->SetRangeUser(0.0, 36.0);
      pHistPeak_U->GetYaxis()->SetTitle("Counts");
      pHistPeak_U->GetYaxis()->CenterTitle();
      pHistPeak_U->SetLineColor(kBlue);
      pHistPeak_U->Draw();

      pCanvas->GetCanvas()->cd(1)->cd(2);
      pCanvas->GetCanvas()->cd(1)->cd(2)->SetLogy(1);
      pHistPeak_V = new TH1F("V Peak Rates", "V Peak Rates", 36, 0.0, 36.0);
      pHistPeak_V->GetXaxis()->SetTitle("V Peak Rates(Hz)");
      pHistPeak_V->GetXaxis()->SetRangeUser(0.0, 36.0);
      pHistPeak_V->GetYaxis()->SetTitle("Counts");
      pHistPeak_V->GetYaxis()->CenterTitle();
      pHistPeak_V->SetLineColor(kBlue);
      pHistPeak_V->Draw();
        
      pCanvas->GetCanvas()->cd(1)->cd(3);
      pCanvas->GetCanvas()->cd(1)->cd(3)->SetLogy(1);
      pHistPeak_W = new TH1F("W Peak Rates", "W Peak Rates", 36, 0.0, 36.0);
      pHistPeak_W->GetXaxis()->SetTitle("W Peak Rates(Hz)");
      pHistPeak_W->GetXaxis()->SetRangeUser(0.0, 36.0);
      pHistPeak_W->GetYaxis()->SetTitle("Counts");
      pHistPeak_W->GetYaxis()->CenterTitle();
      pHistPeak_W->SetLineColor(kBlue);
      pHistPeak_W->Draw();
      
      
      //////////////////////////////////     
      // Peak Position Canvas
      //////////////////////////////////     
      pCanvas->GetCanvas()->cd(2)->Divide(3, 1);
            
      pCanvas->GetCanvas()->cd(2)->cd(1);
      pCanvas->GetCanvas()->cd(2)->cd(1)->SetLogz(1);
      pHistCluster = new TH2F("Cluster Rates", "Cluster Rates", 36, 0.0, 36.0, 36, 0.0, 36.0);
      pHistCluster->SetStats(0);
      pHistCluster->GetXaxis()->CenterLabels();
      pHistCluster->GetXaxis()->SetNdivisions(36, kFALSE);
      pHistCluster->GetXaxis()->SetTickLength(1);
      pHistCluster->GetYaxis()->CenterLabels();
      pHistCluster->GetYaxis()->SetNdivisions(36, kFALSE);
      pHistCluster->GetYaxis()->SetTickLength(1);
      pHistCluster->Draw("COLZ");
      
      
      
      pCanvas->GetCanvas()->cd();
		pCanvas->GetCanvas()->Modified();
		pCanvas->GetCanvas()->Update();

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);

		ECtrig0_HistCtrl		   = (volatile unsigned int *)((int)pM->BaseAddr + 0x14110);
		ECtrig0_HistPeak	      = (volatile unsigned int *)((int)pM->BaseAddr + 0x14118);
      ECtrig0_HistCluster     = (volatile unsigned int *)((int)pM->BaseAddr + 0x1411C);
		ECtrig0_RefTime		   = (volatile unsigned int *)((int)pM->BaseAddr + 0x14114);

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

  void UpdatePositionHistogram(float scale, Bool_t normalize)
  {
    unsigned int buf[4096];
    int i, u, v;

    // Update peaks
    pM->BlkReadReg32(ECtrig0_HistPeak, buf, 256, CRATE_MSG_FLAGS_NOADRINC);

    for(i = 0; i < 256; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      if(i>=0 && i<=35)
        pHistPeak_U->Fill(i, val);
      
      if(i>=64 && i<=99)
        pHistPeak_V->Fill(i-64, val);
      
      if(i>=128 && i<=163)
        pHistPeak_W->Fill(i-128, val);
    }
    
    // Update clusters
    pM->BlkReadReg32(ECtrig0_HistCluster, &buf[0], 1024, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(ECtrig0_HistCluster, &buf[1024], 1024, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(ECtrig0_HistCluster, &buf[2048], 1024, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(ECtrig0_HistCluster, &buf[3072], 1024, CRATE_MSG_FLAGS_NOADRINC);

    pCanvas->GetCanvas()->cd(2);
    pHistCluster->SetMinimum(0);
    pHistCluster->Reset();
    
    for(i = 0; i < 4096; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      u = i%64;
      v = i/64;
      pHistCluster->Fill(u, v, val);
    }
    
    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
  }

	void UpdateHistogram(Bool_t bReadout = kTRUE)
	{
		// histograms
		pM->WriteReg32(ECtrig0_HistCtrl, 0x00);	// disable histograms

		Bool_t normalize = pButtonNormalize->IsDown();
		
		unsigned int ref = pM->ReadReg32(ECtrig0_RefTime);
		float scale = ref;
		if(normalize && (scale <= 0.0))
		{
			printf("VTP ectrig cluster histogram reference time invalid. not normalizing data.\n");
			normalize = kFALSE;
		}
		else
		{
			scale = scale * 256.0f / 250.0E6;
			scale = 1.0f / scale;
		}

		UpdatePositionHistogram(scale, normalize);

		pM->WriteReg32(ECtrig0_HistCtrl, 0x7);	// enable histograms
	}

private:

	enum Buttons
	{
		BTN_AUTOUPDATE		= 1002,
		BTN_MANUALUPDATE	= 1003,
		SDR_UPDATETIME		= 1100
	};
	
   volatile unsigned int   *ECtrig0_HistCtrl;
   volatile unsigned int   *ECtrig0_HistPeak;
   volatile unsigned int   *ECtrig0_HistCluster;
   volatile unsigned int   *ECtrig0_RefTime;
	
	ModuleFrame				*pM;

	TTimer					*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvas;
	TRootEmbeddedCanvas	*pCanvasRates;

	TH2F						*pHistCluster;
   
   TH1F                 *pHistPeak_U;
   TH1F                 *pHistPeak_V;
   TH1F                 *pHistPeak_W;

	TGSlider					*pSliderUpdateTime;

	TGTextButton			*pButtonAutoUpdate;
	TGTextButton			*pButtonManualUpdate;
	TGTextButton			*pButtonNormalize;
};

#endif
