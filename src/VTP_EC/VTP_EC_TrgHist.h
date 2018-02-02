#ifndef VTP_TrgHist_H
#define VTP_TrgHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"

#define UDPATETIME_MAX              60

class VTP_EC_TrgHist  : public TGCompositeFrame
{
public:
  VTP_EC_TrgHist(const TGWindow *p, ModuleFrame *pModule, int ectrig) : TGCompositeFrame(p, 400, 400)
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
//        pSliderUpdateTime->SetEnabled(kFALSE);
          pSliderUpdateTime->SetPosition(1);
          pSliderUpdateTime->Associate(this);

    // Use a resizable frame instead of viewport
    AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 1300, 2300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

//    gStyle->SetPalette(1, NULL);
    pCanvas->GetCanvas()->Divide(1,3);
/*
    pCanvas->GetCanvas()->
    pCanvas->GetCanvas()->Divide(7);
    pCanvas->GetCanvas()-cd(1)->SetPad(0
*/
    //////////////////////////////////    
    // Peak Position Canvas
    //////////////////////////////////    
    pCanvas->GetCanvas()->cd(1)->Divide(3, 1);
          
    pCanvas->GetCanvas()->cd(1)->cd(1);
    pCanvas->GetCanvas()->cd(1)->cd(1)->SetLogy(1);
    pHistPeak_U = new TH1F(Form("UPeak-i%d", inst), "UPeak;UPeakCenter;Rate(Hz)", 36, 0.0, 36.0);
    pHistPeak_U->SetStats(0);
    pHistPeak_U->GetXaxis()->SetRangeUser(0.0, 36.0);
    pHistPeak_U->GetYaxis()->CenterTitle();
    pHistPeak_U->SetLineColor(kBlue);
    pHistPeak_U->Draw();

    pCanvas->GetCanvas()->cd(1)->cd(2);
    pCanvas->GetCanvas()->cd(1)->cd(2)->SetLogy(1);
    pHistPeak_V = new TH1F(Form("VPeak-i%d", inst), "VPeak;VPeakCenter;Rate(Hz)", 36, 0.0, 36.0);
    pHistPeak_V->SetStats(0);
    pHistPeak_V->GetXaxis()->SetRangeUser(0.0, 36.0);
    pHistPeak_V->GetYaxis()->CenterTitle();
    pHistPeak_V->SetLineColor(kBlue);
    pHistPeak_V->Draw();
      
    pCanvas->GetCanvas()->cd(1)->cd(3);
    pCanvas->GetCanvas()->cd(1)->cd(3)->SetLogy(1);
    pHistPeak_W = new TH1F(Form("WPeak-i%d", inst), "WPeak;WPeakCenter;Rate(Hz)", 36, 0.0, 36.0);
    pHistPeak_W->SetStats(0);
    pHistPeak_W->GetXaxis()->SetRangeUser(0.0, 36.0);
    pHistPeak_W->GetYaxis()->CenterTitle();
    pHistPeak_W->SetLineColor(kBlue);
    pHistPeak_W->Draw();
    
    
    //////////////////////////////////     
    // Cluster Information Canvas
    //////////////////////////////////     
    pCanvas->GetCanvas()->cd(2)->Divide(3, 1);
          
    pCanvas->GetCanvas()->cd(2)->cd(1);
    pCanvas->GetCanvas()->cd(2)->cd(1)->SetLogy(1);
    pHistClusterEnergy = new TH1F(Form("Cluster Energy-i%d", inst), "Cluster Energy;Cluster Energy(MeV);Rate(Hz)", 1024, 0.0, 8192.0);
    pHistClusterEnergy->SetStats(0);
    pHistClusterEnergy->GetXaxis()->SetRangeUser(0.0, 8192.0);
    pHistClusterEnergy->GetYaxis()->CenterTitle();
    pHistClusterEnergy->SetLineColor(kBlue);
    pHistClusterEnergy->Draw();

    pCanvas->GetCanvas()->cd(2)->cd(2);
    pCanvas->GetCanvas()->cd(2)->cd(2)->SetLogy(1);
    pHistClusterDalitz = new TH1F(Form("Cluster Dalitz-i%d", inst), "Cluster Dalitz;Daltiz;Rate(Hz)", 1024, 0.0, 128.0);
    pHistClusterDalitz->SetStats(0);
    pHistClusterDalitz->GetXaxis()->SetRangeUser(0.0, 128.0);
    pHistClusterDalitz->GetYaxis()->CenterTitle();
    pHistClusterDalitz->SetLineColor(kBlue);
    pHistClusterDalitz->Draw();
      
    pCanvas->GetCanvas()->cd(2)->cd(3);
    pCanvas->GetCanvas()->cd(2)->cd(3)->SetLogz(1);    
    pHistClusterPosition = new TH2Poly();
    BuildECPolyHist(pHistClusterPosition);
    pHistClusterPosition->SetTitle("Cluster Position;;");
    pHistClusterPosition->SetStats(0);
    pHistClusterPosition->GetXaxis()->SetTickLength(0);
    pHistClusterPosition->GetXaxis()->SetLabelOffset(999);
    pHistClusterPosition->GetYaxis()->SetTickLength(0);
    pHistClusterPosition->GetYaxis()->SetLabelOffset(999);
    pHistClusterPosition->Draw("COLZ L");
    
    //////////////////////////////////     
    // Peak Position Canvas
    //////////////////////////////////     
    pCanvas->GetCanvas()->cd(3)->Divide(3, 1);
          
    pCanvas->GetCanvas()->cd(3)->cd(1);
    pCanvas->GetCanvas()->cd(3)->cd(1)->SetLogy(1);
    pHistClusterLatency = new TH1F(Form("Cluster Latency-i%d", inst), "Cluster Latency;Latency(ns);Rate(Hz)", 1024, 0.0, 8192.0);
    pHistClusterLatency->SetStats(0);
    pHistClusterLatency->GetXaxis()->SetRangeUser(0.0, 8192.0);
    pHistClusterLatency->GetYaxis()->CenterTitle();
    pHistClusterLatency->SetLineColor(kBlue);
    pHistClusterLatency->Draw();
        
    
    
    pCanvas->GetCanvas()->cd();
    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();

    pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);

    if(ectrig == 0)
    {
      ECtrig_HistCtrl            = (volatile unsigned int *)((long)pM->BaseAddr + 0x14110);
      ECtrig_RefTime            = (volatile unsigned int *)((long)pM->BaseAddr + 0x14114);
      ECtrig_HistPeak            = (volatile unsigned int *)((long)pM->BaseAddr + 0x14118);
      ECtrig_HistCluster        = (volatile unsigned int *)((long)pM->BaseAddr + 0x1411C);
      ECtrig_HistClusterEnergy  = (volatile unsigned int *)((long)pM->BaseAddr + 0x14120);
      ECtrig_HistClusterDalitz  = (volatile unsigned int *)((long)pM->BaseAddr + 0x14124);
      ECtrig_HistClusterLatency = (volatile unsigned int *)((long)pM->BaseAddr + 0x14128);
    }
    else
    {
      ECtrig_HistCtrl           = (volatile unsigned int *)((long)pM->BaseAddr + 0x14210);
      ECtrig_RefTime            = (volatile unsigned int *)((long)pM->BaseAddr + 0x14214);
      ECtrig_HistPeak           = (volatile unsigned int *)((long)pM->BaseAddr + 0x14218);
      ECtrig_HistCluster        = (volatile unsigned int *)((long)pM->BaseAddr + 0x1421C);
      ECtrig_HistClusterEnergy  = (volatile unsigned int *)((long)pM->BaseAddr + 0x14220);
      ECtrig_HistClusterDalitz  = (volatile unsigned int *)((long)pM->BaseAddr + 0x14224);
      ECtrig_HistClusterLatency = (volatile unsigned int *)((long)pM->BaseAddr + 0x14228);
    }

    inst++;
  }
  
  void BuildECPolyHist(TH2Poly *pH)
  {
    Double_t x[4], y[4];
    Double_t x_c, y_c;
    
    for(int i = 0; i < 36; i++)
    {
      Bool_t flip = kFALSE;
      for(int j = -i; j <= i; j++)
      {
        x_c = j / TMath::Sqrt(3);
        y_c = i;
        
        if(!flip)
        {
          x[0] = x_c;
          y[0] = y_c;
          x[1] = x_c - 1.0/TMath::Sqrt(3.0);
          y[1] = y_c + 1;
          x[2] = x_c + 1.0/TMath::Sqrt(3.0);
          y[2] = y_c + 1;
          x[3] = x_c;
          y[3] = y_c;
          flip = kTRUE;
        }
        else
        {
          x[0] = x_c;
          y[0] = y_c+1;
          x[1] = x_c - 1.0/TMath::Sqrt(3.0);
          y[1] = y_c;
          x[2] = x_c + 1.0/TMath::Sqrt(3.0);
          y[2] = y_c;
          x[3] = x_c;
          y[3] = y_c+1;
          flip = kFALSE;
        }
        
        pH->AddBin(4,x,y);
      }
    }
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
                pSliderUpdateTime->SetEnabled(kTRUE);
                pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
              }
              else
              {
                pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Manual"));
                pSliderUpdateTime->SetEnabled(kFALSE);
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

  void UpdatePeakPositionHistogram(float scale, Bool_t normalize)
  {
    unsigned int buf[256];
    
    // Update peaks
    pM->BlkReadReg32(ECtrig_HistPeak, buf, 256, CRATE_MSG_FLAGS_NOADRINC);

    pHistPeak_U->Reset();
    pHistPeak_V->Reset();
    pHistPeak_W->Reset();
    if(normalize)
    {
      pHistPeak_U->GetYaxis()->SetTitle("Rate(Hz)");
      pHistPeak_V->GetYaxis()->SetTitle("Rate(Hz)");
      pHistPeak_W->GetYaxis()->SetTitle("Rate(Hz)");
    }
    else
    {
      pHistPeak_U->GetYaxis()->SetTitle("Count");
      pHistPeak_V->GetYaxis()->SetTitle("Count");
      pHistPeak_W->GetYaxis()->SetTitle("Count");
    }

    for(int i = 0; i < 256; i++)
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
  }
  
  void UpdateClusterPositionHistogram(float scale, Bool_t normalize)
  {
    unsigned int buf[1296];
    int u, v;

    // Update clusters
    pM->BlkReadReg32(ECtrig_HistCluster, &buf[0], 1296, CRATE_MSG_FLAGS_NOADRINC);

    pHistClusterPosition->Reset("");
    pHistClusterPosition->SetMinimum(0);
    
    for(int i = 0; i < 1296; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      pHistClusterPosition->SetBinContent(i+1, val);
    }
  }
  
  void UpdateClusterEnergyHistogram(float scale, Bool_t normalize)
  {
    unsigned int buf[1024];

    // Update clusters
    pM->BlkReadReg32(ECtrig_HistClusterEnergy, &buf[0], 1024, CRATE_MSG_FLAGS_NOADRINC);

    pHistClusterEnergy->Reset();
    if(normalize)
      pHistClusterEnergy->GetYaxis()->SetTitle("Rate(Hz)");
    else
      pHistClusterEnergy->GetYaxis()->SetTitle("Count");

    for(int i = 0; i < 1024; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      pHistClusterEnergy->Fill(i*8.0, val);
    }
  }

  void UpdateClusterDalitzHistogram(float scale, Bool_t normalize)
  {
    unsigned int buf[1024];

    // Update clusters
    pM->BlkReadReg32(ECtrig_HistClusterDalitz, &buf[0], 1024, CRATE_MSG_FLAGS_NOADRINC);

    pHistClusterDalitz->Reset();
    if(normalize)
      pHistClusterDalitz->GetYaxis()->SetTitle("Rate(Hz)");
    else
      pHistClusterDalitz->GetYaxis()->SetTitle("Count");
    
    for(int i = 0; i < 1024; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      pHistClusterDalitz->Fill((double)i/8.0, val);
    }
  }

  void UpdateClusterLatencyHistogram(float scale, Bool_t normalize)
  {
    unsigned int buf[1024];

    // Update clusters
    pM->BlkReadReg32(ECtrig_HistClusterLatency, &buf[0], 1024, CRATE_MSG_FLAGS_NOADRINC);

    pHistClusterLatency->Reset();
    if(normalize)
      pHistClusterLatency->GetYaxis()->SetTitle("Rate(Hz)");
    else
      pHistClusterLatency->GetYaxis()->SetTitle("Count");
    
    for(int i = 0; i < 1024; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      pHistClusterLatency->Fill((double)i*8.0, val);
    }
  }

  void UpdateHistogram(Bool_t bReadout = kTRUE)
  {
    // histograms
    pM->WriteReg32(ECtrig_HistCtrl, 0x00);  // disable histograms

    Bool_t normalize = pButtonNormalize->IsDown();
    
    unsigned int ref = pM->ReadReg32(ECtrig_RefTime);
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

    UpdatePeakPositionHistogram(scale, normalize);
    UpdateClusterPositionHistogram(scale, normalize);
    UpdateClusterEnergyHistogram(scale, normalize);
    UpdateClusterDalitzHistogram(scale, normalize);
    UpdateClusterLatencyHistogram(scale, normalize);

    pM->WriteReg32(ECtrig_HistCtrl, 0xFFFFFFFF);  // enable histograms
        
    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
  }

private:

  enum Buttons
  {
    BTN_AUTOUPDATE      = 1002,
    BTN_MANUALUPDATE    = 1003,
    SDR_UPDATETIME      = 1100
  };
  
  volatile unsigned int *ECtrig_HistCtrl;
  volatile unsigned int *ECtrig_RefTime;
  volatile unsigned int *ECtrig_HistPeak;
  volatile unsigned int *ECtrig_HistCluster;
  volatile unsigned int *ECtrig_HistClusterEnergy;
  volatile unsigned int *ECtrig_HistClusterDalitz;
  volatile unsigned int *ECtrig_HistClusterLatency;
  
  ModuleFrame           *pM;

  TTimer                *pTimerUpdate;

  TRootEmbeddedCanvas   *pCanvas;
//  TPad                  *pPad;

  TH2Poly               *pHistClusterPosition;
  TH1F                  *pHistPeak_U;
  TH1F                  *pHistPeak_V;
  TH1F                  *pHistPeak_W;
  TH1F                  *pHistClusterEnergy;
  TH1F                  *pHistClusterDalitz;
  TH1F                  *pHistClusterLatency;

  TGSlider              *pSliderUpdateTime;

  TGTextButton          *pButtonAutoUpdate;
  TGTextButton          *pButtonManualUpdate;
  TGTextButton          *pButtonNormalize;
};

#endif
