#ifndef VTP_HPS_TrgScalers_H
#define VTP_HPS_TrgScalers_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"

#define UDPATETIME_MAX                    60

#define VTP_HPS_TRIG_INFO_S0_TOP          0.0
#define VTP_HPS_TRIG_INFO_S1_TOP          1.0
#define VTP_HPS_TRIG_INFO_S2_TOP          2.0
#define VTP_HPS_TRIG_INFO_S3_TOP          3.0
#define VTP_HPS_TRIG_INFO_S0_BOT          4.0
#define VTP_HPS_TRIG_INFO_S1_BOT          5.0
#define VTP_HPS_TRIG_INFO_S2_BOT          6.0
#define VTP_HPS_TRIG_INFO_S3_BOT          7.0
#define VTP_HPS_TRIG_INFO_P0              8.0
#define VTP_HPS_TRIG_INFO_P1              9.0
#define VTP_HPS_TRIG_INFO_P2             10.0
#define VTP_HPS_TRIG_INFO_P3             11.0
#define VTP_HPS_TRIG_INFO_MULTS          12.0
#define VTP_HPS_TRIG_INFO_LED            13.0
#define VTP_HPS_TRIG_INFO_COSMIC         14.0
#define VTP_HPS_TRIG_INFO_HODOSCOPE      15.0
#define VTP_HPS_TRIG_INFO_PULSER         16.0
#define VTP_HPS_TRIG_INFO_L1A            17.0

class VTP_HPS_TrgScalers : public TGCompositeFrame
{
public:
  VTP_HPS_TrgScalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
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

    gStyle->SetPalette(1, NULL);
    gStyle->SetPaintTextFormat(".0f");

    pPadTriggers     = new TPad("padTriggers",    "padTriggers",    0.0,  0.75, 1.0,   1.00);
    pPadSinglesTop   = new TPad("padSinglesTop",  "padSinglesTop",  0.0,  0.50, 1.0,   0.75);
    pPadSinglesBot   = new TPad("padSinglesBot",  "padSinglesBot",  0.0,  0.25, 1.0,   0.50);
    pPadPairs        = new TPad("padPairs",       "padPairs",       0.0,  0.00, 1.0,   0.25);

    pPadSinglesTop->Draw();
    pPadSinglesBot->Draw();
    pPadPairs->Draw();
    pPadTriggers->Draw();

    //////////////////////////////////    
    // Trigger Info Canvas
    //////////////////////////////////    
    const char *trigger_info_bins[] = {
      "S0Top","S1Top","S2Top","S3Top","S0Bot","S1Bot","S2Bot","S3Bot","P0","P1","P2","P3","Mult","LED","COSMIC","HODOSCOPE","PULSER","L1A"};

    pPadTriggers->cd();
    pPadTriggers->SetLogy(1);

    pHistTriggers = new TH1F(Form("Trigger Info %d,%d", inst, i), "Trigger Info;;Hz", sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0]), 0.0, (double)sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0]));
    pHistTriggers->SetLineColor(kBlack);
    pHistTriggers->SetFillColor(kBlue);
    pHistTriggers->SetNdivisions(sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0]));
    pHistTriggers->SetStats(0);
    for(int j=0; j<(int)(sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0])); j++)
      pHistTriggers->GetXaxis()->SetBinLabel(j+1, trigger_info_bins[j]);
    pHistTriggers->Draw("B TEXT");

    //////////////////////////////////    
    // Singles Info Canvas
    //////////////////////////////////    
    const char *singles_bins[] = {
      "Total","ENMinMax","XMin","PDE","HL1","HL2","HL1L2","HL1xL2","HL1xXxL2","Pass","TI"};

    // Singles Top
    pPadSinglesTop->cd();
    pPadSinglesTop->Divide(4,1);
    for(int j=0; j<4; j++)
    {
      pPadSinglesTop->cd(j+1);
      pPadSinglesTop->cd(j+1)->SetLogy(1);

      pHistSinglesTop[j] = new TH1F(Form("Singles %d Top",j), Form("Singles %d Top",j), sizeof(singles_bins)/sizeof(singles_bins[0]), 0.0, (double)sizeof(singles_bins)/sizeof(singles_bins[0]));
      pHistSinglesTop[j]->SetLineColor(kBlack);
      pHistSinglesTop[j]->SetFillColor(kRed);
      pHistSinglesTop[j]->SetNdivisions(sizeof(singles_bins)/sizeof(singles_bins[0]));
      pHistSinglesTop[j]->SetStats(0);
      for(int i=0; i<(int)(sizeof(singles_bins)/sizeof(singles_bins[0])); i++)
        pHistSinglesTop[j]->GetXaxis()->SetBinLabel(i+1, singles_bins[i]);
      pHistSinglesTop[j]->GetYaxis()->SetRangeUser(0.1,100.0E6);
      pHistSinglesTop[j]->Draw("B TEXT");
    }

    // Singles Bot
    pPadSinglesBot->cd();
    pPadSinglesBot->Divide(4,1);
    for(int j=0; j<4; j++)
    {
      pPadSinglesBot->cd(j+1);
      pPadSinglesBot->cd(j+1)->SetLogy(1);

      pHistSinglesBot[j] = new TH1F(Form("Singles %d Bot",j), Form("Singles %d Bot",j), sizeof(singles_bins)/sizeof(singles_bins[0]), 0.0, (double)sizeof(singles_bins)/sizeof(singles_bins[0]));
      pHistSinglesBot[j]->SetLineColor(kBlack);
      pHistSinglesBot[j]->SetFillColor(kRed);
      pHistSinglesBot[j]->SetNdivisions(sizeof(singles_bins)/sizeof(singles_bins[0]));
      pHistSinglesBot[j]->SetStats(0);
      for(int i=0; i<(int)(sizeof(singles_bins)/sizeof(singles_bins[0])); i++)
        pHistSinglesBot[j]->GetXaxis()->SetBinLabel(i+1, singles_bins[i]);
      pHistSinglesBot[j]->GetYaxis()->SetRangeUser(0.1,100.0E6);
      pHistSinglesBot[j]->Draw("B TEXT");
    }

    //////////////////////////////////    
    // Pairs Info Canvas
    //////////////////////////////////    
    const char *pairs_bins[] = {
      "Total","Sum","Diff","EnergyDist","Coplanarity","Pass","TI"};

    pPadPairs->cd();
    pPadPairs->Divide(4,1);
    for(int j=0; j<4; j++)
    {
      pPadPairs->cd(j+1);
      pPadPairs->cd(j+1)->SetLogy(1);

      pHistPairs[j] = new TH1F(Form("Pair %d",j), Form("Pair %d",j), sizeof(pair_bins)/sizeof(pair_bins[0]), 0.0, (double)sizeof(pair_bins)/sizeof(pair_bins[0]));
      pHistPairs[j]->SetLineColor(kBlack);
      pHistPairs[j]->SetFillColor(kRed);
      pHistPairs[j]->SetNdivisions(sizeof(pair_bins)/sizeof(pair_bins[0]));
      pHistPairs[j]->SetStats(0);
      for(i; i<(int)(sizeof(pair_bins)/sizeof(pair_bins[0])); i++)
        pHistPairs[j]->GetXaxis()->SetBinLabel(i+1, pair_bins[i]);
      pHistPairs[j]->GetYaxis()->SetRangeUser(0.1,100.0E6);
      pHistPairs[j]->Draw("B TEXT");
    }

    pCanvas->GetCanvas()->cd();
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
//              pSliderUpdateTime->SetEnabled(kTRUE);
              pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
            }
            else
            {
              pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Manual"));
//              pSliderUpdateTime->SetEnabled(kFALSE);
              pTimerUpdate->TurnOff();
            }
            break;
          case BTN_MANUALUPDATE:
            Update();
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
      Update();
      if(pButtonAutoUpdate->IsDown())
        pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
    }
    return kTRUE;
  }

  void UpdateScalers(Bool_t normalize)
  {
    volatile unsigned int *HpsMon_ScalerDisable = (volatile unsigned int *)((int)pM->BaseAddr + 0x208);
    double s_total[8], s_enminmax_pass[8], s_xmin_pass[8], s_pde_pass[8];
    double s_hl1_pass[8], s_hl2_pass[8], s_hl1l2_pass[8], s_hl1xl2_pass[8];
    double s_hl1xXxl2_pass[8], s_pass[8], s_ti[8];
    double p_total[4], p_sumpass[4], p_difpass[4], p_edpass[4];
    double p_coppass[4], p_pass[4], p_ti[4];
    double mult_pass, mult_ti;
    double led, led_ti;
    double hodoscope, hodoscope_ti;
    double pulser, pulser_ti;
    double l1a, busclk;
    double ref = 1.0;


    pM->WriteReg32(HpsMon_ScalerDisable, 1);
    l1a = (double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x278));
    busclk = (double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x270));

    if(normalize)
    {
      if(!busclk)
        printf("ERROR: reference clock=0, normalization will not be done.");
      else
        ref = 33.33E6 / busclk;
    }

    for(int i=0;i<8;i++)
    {
      s_total[i]         = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5940));
      s_enminmax_pass[i] = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5948));
      s_xmin_pass[i]     = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x594C));
      s_pde_pass[i]      = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5950));
      s_hl1_pass[i]      = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5954));
      s_hl2_pass[i]      = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5958));
      s_hl1l2_pass[i]    = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5960));
      s_hl1xl2_pass[i]    = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5960));
      s_hl1xXxl2_pass[i]   = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5964));
      s_pass[i]          = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x80*i + 0x5944));
      s_ti[i]            = 0;  //(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i +
    }

    for(int i=0;i<4;i++)
    {
      p_total[i]         = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x20));
      p_sumpass[i]       = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x24));
      p_difpass[i]       = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x28));
      p_edpass[i]        = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x2C));
      p_coppass[i]       = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x30));
      p_pass[i]          = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x34));
      p_ti[i]            = 0;   //(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x40*i + 0x
    }

    mult_pass            = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x5E70));
    mult_ti              = 0;   //(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x

    led                  = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x5E2C));
    led_ti               = 0;   //(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x

    hodoscope            = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x5E38));
    hodoscope_ti         = 0;   //(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x

    pulser               = ref*(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x5E3C));
    pulser_ti            = 0;   //(double)pM->ReadReg32((volatile unsigned int *)((int)pM->BaseAddr + 0x

    pM->WriteReg32(HpsMon_ScalerDisable, 0);

    // Triggers
    pPadTriggers->cd();
    pHistTriggers->Reset();
    if(normalize)
      pHistTriggers->SetTitle(Form("Trigger Rate Info;;Hz"));
    else
      pHistTriggers->SetTitle(Form("Trigger Rate Info;;Count"));

    // Singles Top
    pPadSinglesTop->cd();
    for(int i=0; i<4; i++)
    {
      pHistSinglesTop[i]->Reset();
      if(normalize)
        pHistSinglesTop[i]->SetTitle(Form("Singles %d Top;;Hz"));
      else
        pHistSinglesTop[i]->SetTitle(Form("Singles %d Top;;Count"));
    }
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_MULT_PASS, mult_pass);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_MULT_TI, mult_ti);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_LED, led);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_LED_TI, led_ti);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_HODOSCOPE, hodoscope);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_HODOSCOPE_TI, hodoscope_ti);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_PULSER, pulser);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_PULSER_TI, pulser_ti);
    pHistTriggers->Fill(VTP_HPS_TRIG_INFO_L1A, l1a);


    // Singles Bot
    pPadSinglesBot->cd();
    for(int i=0; i<4; i++)
    {
      pHistSinglesBot[i]->Reset();
      if(normalize)
        pHistSinglesBot[i]->SetTitle(Form("Singles %d Bot;;Hz"));
      else
        pHistSinglesBot[i]->SetTitle(Form("Singles %d Bot;;Count"));
    }

    // Pairs
    pPadPairs->cd();
    for(int i=0; i<4; i++)
    {
      pHistPairs[i]->Reset();
      if(normalize)
        pHistPairs[i]->SetTitle(Form("Pairs %d Bot;;Hz"));
      else
        pHistPairs[i]->SetTitle(Form("Pairs %d Bot;;Count"));
    }
      
    for(int i=0;i<8;i++)
    {
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_TOTAL, s_total[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_ENMINMAX_PASS, s_enminmax_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_XMIN_PASS, s_xmin_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_PDE_PASS, s_pde_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_HL1_PASS, s_hl1_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_HL2_PASS, s_hl2_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_HL1L2_PASS, s_hl1l2_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_HL1xL2_PASS, s_hl1xl2_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_HL1xXxL2_PASS, s_hl1xXxl2_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_PASS, s_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_S_TI, s_ti[i]);
    }

    for(int i=0;i<4;i++)
    {
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_TOTAL, p_total[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_SUMPASS, p_sumpass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_DIFPASS, p_difpass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_EDPASS, p_edpass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_COPPASS, p_coppass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_PASS, p_pass[i]);
      pHistTriggerInfo[i]->Fill(VTP_HPS_TRIG_INFO_P_TI, p_ti[i]);
    }

    pPadTriggerInfo->cd()->Modified();
  }
  
  void Update(Bool_t bReadout = kTRUE)
  {
    // scalers
    UpdateScalers(pButtonNormalize->IsDown());

    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
  }

	virtual Bool_t HandleButton(Event_t *event)
	{
		TGCompositeFrame::HandleButton(event);

		if(event->fCode == kButton3)
      printf("kButton3: event->fX,fY = (%d,%d)\n", event->fx, event->fy);
			//UpdateCursor(event->fX+pCTraces->GetHScrollbar()->GetPosition());
		return kTRUE;
	}

private:

  enum Buttons
  {
    BTN_AUTOUPDATE    = 1002,
    BTN_MANUALUPDATE  = 1003,
    SDR_UPDATETIME    = 1100
  };

  ModuleFrame         *pM;

  TTimer              *pTimerUpdate;

  TRootEmbeddedCanvas *pCanvas;

  TPad                *pPadSinglesTop;
  TPad                *pPadSinglesBot;
  TPad                *pPadPairs;  
  TPad                *pPadTriggers;

  TH1F                *pHistSinglesTop[4];
  TH1F                *pHistSinglesBot[4];
  TH1F                *pHistPairs[4];
  TH1F                *pHistTriggers;
  
  TGSlider            *pSliderUpdateTime;

  TGTextButton        *pButtonAutoUpdate;
  TGTextButton        *pButtonManualUpdate;
  TGTextButton        *pButtonNormalize;
};

#endif

