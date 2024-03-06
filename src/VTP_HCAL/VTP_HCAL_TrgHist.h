#ifndef VTP_HCAL_TrgHist_H
#define VTP_HCAL_TrgHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"

#define UDPATETIME_MAX                    60

class VTP_HCAL_TrgHist : public TGCompositeFrame
{
public:
  VTP_HCAL_TrgHist(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
  {
    static int inst = 0;

    SetLayoutManager(new TGVerticalLayout(this));

    pM = pModule;

    TGCompositeFrame *pTF1;
    TLegend *pLegend;

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
    AddFrame(pC = new TRootEmbeddedCanvas("c1", this, 1300, 2300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    gStyle->SetPalette(1, NULL);
    gStyle->SetPaintTextFormat(".0f");

    pC->GetCanvas()->SetBorderMode(0);
    pC->GetCanvas()->Divide(1,2,0.01,0.01);
    pC->GetCanvas()->cd(2)->Divide(2,1,0.01,0.01);

    // Cluster Position
    pC->GetCanvas()->cd(1);
    pC->GetCanvas()->cd(1)->SetLogz(1);
    pH_Position = new TH2F("ClusterPosition","ClusterPosition;COL;ROW",12,0.0,12.0,24,0.0,24.0);
    pH_Position->SetStats(0);
    pH_Position->GetXaxis()->CenterLabels();
    pH_Position->GetXaxis()->CenterTitle();
    pH_Position->GetXaxis()->SetNdivisions(12, kFALSE);
    pH_Position->GetXaxis()->SetTickLength(1);
    //for(int i=1;i<=12;i++) pH_Position->GetXaxis()->SetBinLabel(i,Form("%d",30-i));

    pH_Position->GetYaxis()->CenterLabels();
    pH_Position->GetYaxis()->CenterTitle();
    pH_Position->GetYaxis()->SetNdivisions(24, kFALSE);
    pH_Position->GetYaxis()->SetTickLength(1);
    //for(int i=1;i<=24;i++) pH_Position->GetYaxis()->SetBinLabel(i,Form("%d",i-1));
    
    pH_Position->GetZaxis()->SetLabelSize(0.03);
    pH_Position->SetBarOffset(0.10);
    pH_Position->SetBarWidth(0.10);
    pH_Position->SetTitle("HCAL Clusters");
    pH_Position->Draw("COLZ L");

    // Cluster Energy
    pC->GetCanvas()->cd(2)->cd(1);
    pH_Energy = new TH1F("ClusterEnergy","ClusterEnergy;MeV;Hz",1024,0.0,8192.0);
    pH_Energy->SetStats(0);
    pH_Energy->SetFillColor(kBlue);
    pH_Energy->SetLineColor(kBlack);
    pH_Energy->Draw("HIST BAR");

    // Cluster Nhits
    pC->GetCanvas()->cd(2)->cd(2);
    pH_Nhits = new TH1F("NHits",";NHits;Hz",10,0.0,10.0);
    pH_Nhits->GetXaxis()->SetNdivisions(10);
    pH_Nhits->GetXaxis()->CenterLabels();
    pH_Nhits->SetStats(0);
    pH_Nhits->SetFillColor(kBlue);
    pH_Nhits->SetLineColor(kBlack);
    pH_Nhits->Draw("HIST BAR");

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
              pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
            }
            else
            {
              pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Manual"));
              pTimerUpdate->TurnOff();
            }
            break;
          case BTN_MANUALUPDATE:
            refresh_scalers();
            break;
          case BTN_SAVE:
            button_Save();
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
      refresh_scalers();
      if(pButtonAutoUpdate->IsDown())
        pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
    }
    return kTRUE;
  }

  int read_scalers()
  {
    unsigned int *buf;
    int len;
    unsigned int val[1];

    memset(&vtp_ref, 0, sizeof(vtp_ref));
    memset(vtp_pos, 0, sizeof(vtp_pos));
    memset(vtp_energy, 0, sizeof(vtp_energy));
    memset(vtp_nhits, 0, sizeof(vtp_nhits));
    
    // Disable scalers
    val[0] = 0x0;
    pM->WriteReg32((volatile unsigned int *)0x4810, val[0]);

    // Read scaler values
    // cluster nhits histogram
    pM->BlkReadReg32((volatile unsigned int *)0x481C, &vtp_nhits[0], 16, CRATE_MSG_FLAGS_NOADRINC);

    // cluster energy histogram
    pM->BlkReadReg32((volatile unsigned int *)0x4818, &vtp_energy[0], 1024, CRATE_MSG_FLAGS_NOADRINC);

    // cluster position histogram
    pM->BlkReadReg32((volatile unsigned int *)0x4814, &vtp_pos[0], 512, CRATE_MSG_FLAGS_NOADRINC);

    // reference time scaler
    pM->BlkReadReg32((volatile unsigned int *)0x4820, &vtp_ref);

    // Reset & enable scalers
    val[0] = 0xF;
    pM->WriteReg32((volatile unsigned int *)0x4810, val[0]);
    return 0;
  }

  void normalize_scalers()
  {
    float ref, scaled;

    if(vtp_ref)
    {
      printf("Error in %s: vtp_ref=%d not valid\n", __func__,vtp_ref);
      ref = 1;
    }
    else
      ref = 1000000.0 / (float)vtp_ref;

    for(int i=0;i<16;i++)
      vtp_nhits[i] = (unsigned int)((float)vtp_nhits[i]*ref);

    for(int i=0;i<1024;i++)
      vtp_energy[i] = (unsigned int)((float)vtp_energy[i]*ref);

    for(int i=0;i<512;i++)
      vtp_pos[i] = (unsigned int)((float)vtp_pos[i]*ref);
  }

  void sum_scalers()
  {
    vtp_pos_tot = 0.0;

    for(int i=0;i<512;i++)
      vtp_pos_tot+= (Double_t)vtp_pos[i];
  }

  void draw_scalers()
  {
    static Bool_t called = kFALSE;
    
    pH_Position->Reset("");
    pH_Position->SetMaximum(1000000.0);
    pH_Position->SetMinimum(0.0);
    for(int ix=0;ix<12;ix++)
    for(int iy=0;iy<24;iy++)
    for(int i=0;i<512;i++)
    {
      int row=(i>>0)&0x1F;
      int col=(i>>5)&0xF;
      if((row<24) && (col<12))
        pH_Position->Fill(col,row,vtp_pos[i]);
    }

    pH_Energy->Reset("");
    for(int i=0;i<1024;i++)
      pH_Energy->Fill(i, vtp_energy[i]);
     
    pH_Nhits->Reset("");
    for(int i=0;i<16;i++)
      pH_Nhits->Fill(i, vtp_nhits[i]);

    pC->GetCanvas()->cd(1)->Modified();
    pC->GetCanvas()->cd(2)->cd(1)->Modified();
    pC->GetCanvas()->cd(2)->cd(2)->Modified();
    
    pC->GetCanvas()->Update();
  }

  void refresh_scalers()
  {
    read_scalers();
    normalize_scalers();
    sum_scalers();
    draw_scalers();
  }

  void button_Save()
  {
    TTimeStamp tt;
    TString tstub=tt.AsString("lc");
    tstub.ReplaceAll(" ","_");
    gPad->SaveAs(Form("%s/screenshots/HCAL_VTP_SCALERS_%s.png", gSystem->Getenv("HOME"), tstub.Data()));
  }

private:

  enum Buttons
  {
    BTN_AUTOUPDATE,
    BTN_MANUALUPDATE,
    BTN_SAVE,
    SDR_UPDATETIME
  };

  ModuleFrame         *pM;

  TTimer              *pTimerUpdate;

  TRootEmbeddedCanvas *pC;

  TH2F *pH_Position;
  TH1F *pH_Nhits;
  TH1F *pH_Energy;

  unsigned int vtp_nhits[16];
  unsigned int vtp_energy[1024];
  unsigned int vtp_pos[512];
  unsigned int vtp_ref;
  Double_t vtp_pos_tot;

  TGSlider            *pSliderUpdateTime;

  TGTextButton        *pButtonAutoUpdate;
  TGTextButton        *pButtonManualUpdate;
  TGTextButton        *pButtonNormalize;
};

#endif

