#ifndef VTP_HPS_TrgHist_H
#define VTP_HPS_TrgHist_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"

#define HODO_NSCALERS                     9
#define HODO_CLW                          5.0
#define HODO_H                            10.0
#define HODO_L2_OFFSET                    5.63

#define UDPATETIME_MAX                    60

#define VTP_HPS_TRIG_INFO_S_TOTAL         0.0
#define VTP_HPS_TRIG_INFO_S_ENMINMAX_PASS 1.0
#define VTP_HPS_TRIG_INFO_S_XMIN_PASS     2.0
#define VTP_HPS_TRIG_INFO_S_PDE_PASS      3.0
#define VTP_HPS_TRIG_INFO_S_HL1_PASS      4.0
#define VTP_HPS_TRIG_INFO_S_HL2_PASS      5.0
#define VTP_HPS_TRIG_INFO_S_HL1L2_PASS    6.0
#define VTP_HPS_TRIG_INFO_S_HL1xL2_PASS   7.0
#define VTP_HPS_TRIG_INFO_S_HL1xXxL2_PASS 8.0
#define VTP_HPS_TRIG_INFO_S_PASS          9.0
#define VTP_HPS_TRIG_INFO_S_TI           10.0
#define VTP_HPS_TRIG_INFO_P_TOTAL        11.0
#define VTP_HPS_TRIG_INFO_P_SUMPASS      12.0
#define VTP_HPS_TRIG_INFO_P_DIFPASS      13.0
#define VTP_HPS_TRIG_INFO_P_EDPASS       14.0
#define VTP_HPS_TRIG_INFO_P_COPPASS      15.0
#define VTP_HPS_TRIG_INFO_P_PASS         16.0
#define VTP_HPS_TRIG_INFO_P_TI           17.0
#define VTP_HPS_TRIG_INFO_MULT_PASS      18.0
#define VTP_HPS_TRIG_INFO_MULT_TI        19.0
#define VTP_HPS_TRIG_INFO_LED            20.0
#define VTP_HPS_TRIG_INFO_LED_TI         21.0
#define VTP_HPS_TRIG_INFO_HODOSCOPE      22.0
#define VTP_HPS_TRIG_INFO_HODOSCOPE_TI   23.0
#define VTP_HPS_TRIG_INFO_PULSER         24.0
#define VTP_HPS_TRIG_INFO_PULSER_TI      25.0
#define VTP_HPS_TRIG_INFO_L1A            26.0

#define CMB_HISTSRC                     3000
#define CMB_ID_SEL_HISTSRC_S0           0
#define CMB_ID_SEL_HISTSRC_S1           1
#define CMB_ID_SEL_HISTSRC_S2           2
#define CMB_ID_SEL_HISTSRC_S3           3
#define CMB_ID_SEL_HISTSRC_P0           4
#define CMB_ID_SEL_HISTSRC_P1           5
#define CMB_ID_SEL_HISTSRC_P2           6
#define CMB_ID_SEL_HISTSRC_P3           7
#define CMB_ID_SEL_HISTSRC_FEE          8
#define CMB_ID_SEL_HISTSRC_ALL          15


class VTP_HPS_TrgHist : public TGCompositeFrame
{
public:
  VTP_HPS_TrgHist(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
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
      pTF1->AddFrame(new TGLabel(pTF1, new TGString("Histogram Source:")), new TGLayoutHints(kLHintsLeft, 2, 2, 4, 0));
      pTF1->AddFrame(pComboHistSrc = new TGComboBox(pTF1, CMB_HISTSRC), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
        pComboHistSrc->Resize(150,20);
        pComboHistSrc->AddEntry("ALL CLUSTERS", CMB_ID_SEL_HISTSRC_ALL);
        pComboHistSrc->AddEntry("S0  CLUSTERS", CMB_ID_SEL_HISTSRC_S0);
        pComboHistSrc->AddEntry("S1  CLUSTERS", CMB_ID_SEL_HISTSRC_S1);
        pComboHistSrc->AddEntry("S2  CLUSTERS", CMB_ID_SEL_HISTSRC_S2);
        pComboHistSrc->AddEntry("S3  CLUSTERS", CMB_ID_SEL_HISTSRC_S3);
        pComboHistSrc->AddEntry("P0  CLUSTERS", CMB_ID_SEL_HISTSRC_P0);
        pComboHistSrc->AddEntry("P1  CLUSTERS", CMB_ID_SEL_HISTSRC_P1);
        pComboHistSrc->AddEntry("P2  CLUSTERS", CMB_ID_SEL_HISTSRC_P2);
        pComboHistSrc->AddEntry("P3  CLUSTERS", CMB_ID_SEL_HISTSRC_P3);
        pComboHistSrc->AddEntry("FEE  CLUSTERS", CMB_ID_SEL_HISTSRC_FEE);
        pComboHistSrc->Associate(this);
        pComboHistSrc->Select(CMB_ID_SEL_HISTSRC_ALL);
      pTF1->AddFrame(pSliderUpdateTime = new TGHSlider(pTF1, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
        pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//        pSliderUpdateTime->SetEnabled(kFALSE);
        pSliderUpdateTime->SetPosition(1);
        pSliderUpdateTime->Associate(this);

    // Use a resizable frame instead of viewport
    AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 1300, 2300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    gStyle->SetPalette(1, NULL);
    gStyle->SetPaintTextFormat(".0f");

    pPadTriggerInfo  = new TPad("padTriggerInfo", "padTriggerInfo", 0.0,  0.75, 1.0,   1.00);
    pPadHodoTop      = new TPad("padHodoeTop",    "padHodoTop",     0.53, 0.65, 0.955, 0.75);
    pPadCalorimeter  = new TPad("padCalorimeter", "padCalorimeter", 0.0,  0.35, 1.0,   0.65);
    pPadHodoBot      = new TPad("padHodoBot",     "padHodoBot",     0.53, 0.25, 0.955, 0.35);
    pPadClusterHist  = new TPad("padClusterHist", "padClusterHist", 0.0,  0.00, 1.0,   0.25);

    pPadTriggerInfo->Draw();
    pPadHodoTop->Draw();
    pPadCalorimeter->Draw();
    pPadHodoBot->Draw();
    pPadClusterHist->Draw();

    //////////////////////////////////    
    // Trigger Info Canvas
    //////////////////////////////////    
    const char *trigger_info_bins[] = {
      "S_Total", "S_ENMinMaxPass", "&XMinPass", "&S_PDEPass", "&S_Hl1Pass", "&S_Hl2Pass", "&S_Hl12Pass", "&S_Hl1<->2Pass", "&S_Hl1<-X->2Pass", "S_Pass", "S_TI",
      "P_Total", "P_SumPass", "P_DifPass", "P_EDPass", "P_CopPass", "P_Pass", "P_TI",
      "Mult", "Mult_TI",
      "LED", "LED_TI",
      "COSMIC", "COSMIC_TI",
      "HODOSCOPE", "HODOSCOPE_TI",
      "PULSER", "PULSER_TI",
      "L1A"
    };

    pPadTriggerInfo->cd();
    pPadTriggerInfo->SetLogy(1);
    for(int i=0;i<8;i++)
    {
      pHistTriggerInfo[i] = new TH1F(Form("Trigger Info %d,%d", inst, i), "Trigger Info;;Hz", sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0]), 0.0, (double)sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0]));
      pHistTriggerInfo[i]->SetLineColor(kBlack);
      pHistTriggerInfo[i]->SetFillColor(kBlue);
      pHistTriggerInfo[i]->SetBarWidth(0.12);
      pHistTriggerInfo[i]->SetBarOffset(i*0.125);
      pHistTriggerInfo[i]->SetFillColor(i+1);
      pHistTriggerInfo[i]->SetNdivisions(sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0]));
      pHistTriggerInfo[i]->SetStats(0);
      for(int j = 0; j < (int)(sizeof(trigger_info_bins)/sizeof(trigger_info_bins[0])); j++)
        pHistTriggerInfo[i]->GetXaxis()->SetBinLabel(j+1, trigger_info_bins[j]);
      if(!i)
        pHistTriggerInfo[i]->Draw("B TEXT");
      else
        pHistTriggerInfo[i]->Draw("B,same");
    }

    //////////////////////////////////
    // Hoodscope Canvas
    //////////////////////////////////
    TText *t = new TText;
    t->SetNDC(kTRUE);

    for(int i=0;i<4;i++)
    {
      pHistHodoscope[i] = new TH2Poly();
      HodoHist(pHistHodoscope[i], i < 2 ? 1 : 0);
      pHistHodoscope[i]->GetXaxis()->SetLabelSize(0);
      pHistHodoscope[i]->GetYaxis()->SetLabelSize(0);
      pHistHodoscope[i]->GetYaxis()->SetNdivisions(2, kFALSE);
      pHistHodoscope[i]->SetStats(0);
      pHistHodoscope[i]->SetMinimum(0);
      pHistHodoscope[i]->SetMaximum(1E7);
    }
    pPadHodoTop->cd();
    pPadHodoTop->cd()->SetLogz(1);
    pPadHodoTop->cd()->SetTopMargin(0.15);
    pHistHodoscope[HODO_TOP]->SetTitle("Hodoscope Top");
    pHistHodoscope[HODO_TOP_CLUSTERED]->SetTitle("Hodoscope Top");
    pHistHodoscope[HODO_TOP]->SetMarkerSize(4);
    pHistHodoscope[HODO_TOP]->Draw("COL,L,TEXT");
    pHistHodoscope[HODO_TOP_CLUSTERED]->Draw("COL,L,SAME");
    t->SetTextAlign(31);
    t->DrawTextNDC(0.08,0.27,"L1");
    t->DrawTextNDC(0.08,0.63,"L2");

    pPadHodoBot->cd();
    pPadHodoBot->cd()->SetLogz(1);
    pPadHodoBot->cd()->SetTopMargin(0.15);
    pHistHodoscope[HODO_BOT]->SetTitle("Hodoscope Bottom");
    pHistHodoscope[HODO_BOT_CLUSTERED]->SetTitle("Hodoscope Bottom");
    pHistHodoscope[HODO_BOT]->SetMarkerSize(4);
    pHistHodoscope[HODO_BOT]->Draw("COL,L,TEXT");
    pHistHodoscope[HODO_BOT_CLUSTERED]->Draw("COL,L,SAME");
    t->SetTextAlign(31);
    t->DrawTextNDC(0.08,0.27,"L1");
    t->DrawTextNDC(0.08,0.63,"L2");

    //////////////////////////////////
    // Cluster Position Canvas
    //////////////////////////////////
    pPadCalorimeter->cd(); 
    pPadCalorimeter->cd()->SetLogz(1); 
    pHistPosition = new TH2F("ClusterPosition", "ClusterPosition;X;Y", 46, -22.0, 24.0, 11, -5.0, 6.0);
    pHistPosition->SetStats(0);
    pHistPosition->GetXaxis()->CenterLabels();
    pHistPosition->GetXaxis()->SetNdivisions(46, kFALSE);
    pHistPosition->GetXaxis()->SetTickLength(1);
    pHistPosition->GetYaxis()->CenterLabels();
    pHistPosition->GetYaxis()->SetNdivisions(11, kFALSE);
    pHistPosition->GetYaxis()->SetTickLength(1);
    pHistPosition->SetMinimum(0);
    pHistPosition->SetMaximum(1E7);
    pHistPosition->Draw("COLZ");

    int x = -23;
    for(int n = 1; n <= 46; n++)
    {
      pHistPosition->GetXaxis()->SetBinLabel(n,Form("%d", x));
      x++;
      if(x == 0) x++;
    }
    
    pPadClusterHist->cd();
    pPadClusterHist->Divide(3,1);
    //////////////////////////////////    
    // Cluster Energy
    //////////////////////////////////    
    pPadClusterHist->cd(1);
    pPadClusterHist->cd(1)->SetLogy(1);

    pHistEnergyT = new TH1F("ClusterEnergy", "ClusterEnergy", 1024, 0.0, 8.0*1024.0);
    pHistEnergyT->GetXaxis()->SetTitle("Energy(MeV)");
    pHistEnergyT->GetXaxis()->SetRangeUser(0.0, 8192.0);
    pHistEnergyT->GetYaxis()->SetTitle("Counts");
    pHistEnergyT->GetYaxis()->CenterTitle();
    pHistEnergyT->GetYaxis()->SetRangeUser(0.1,100.0E6);
    pHistEnergyT->SetLineColor(kBlue);
    pHistEnergyT->SetStats(0);
    pHistEnergyT->Draw();

    pHistEnergyB = new TH1F("ClusterEnergy", "ClusterEnergy", 1024, 0.0, 8.0*1024.0);
    pHistEnergyB->GetXaxis()->SetTitle("Energy(MeV)");
    pHistEnergyB->GetXaxis()->SetRangeUser(0.0, 8192.0);
    pHistEnergyB->GetYaxis()->SetTitle("Counts");
    pHistEnergyB->GetYaxis()->CenterTitle();
    pHistEnergyB->GetYaxis()->SetRangeUser(0.1,100.0E6);
    pHistEnergyB->SetLineColor(kRed);
    pHistEnergyB->SetStats(0);
    pHistEnergyB->Draw("SAME");

    pLegend = new TLegend(0.7,0.8,0.9,0.9);
    pLegend->AddEntry(pHistEnergyT, "Top Clusters");
    pLegend->AddEntry(pHistEnergyB, "Bot Clusters");
    pLegend->Draw();

    //////////////////////////////////    
    // Cluster NHits
    //////////////////////////////////    
    pPadClusterHist->cd(2);
    pPadClusterHist->cd(2)->SetLogy(1);

    pHistNHitsT = new TH1F("ClusterNHitsTop", "ClusterNHits", 9, 0.0, 9.0);
    pHistNHitsT->GetXaxis()->SetTitle("NHits");
    pHistNHitsT->GetXaxis()->SetRangeUser(0.0, 9.0);
    pHistNHitsT->GetXaxis()->CenterLabels();
    pHistNHitsT->GetYaxis()->SetTitle("Counts");
    pHistNHitsT->GetYaxis()->CenterTitle();
    pHistNHitsT->GetYaxis()->SetRangeUser(0.1,100.0E6);
    pHistNHitsT->SetLineColor(kBlue);
    pHistNHitsT->SetStats(0);
    pHistNHitsT->Draw();

    pHistNHitsB = new TH1F("ClusterNHitsBot", "ClusterNHits", 9, 0.0, 9.0);
    pHistNHitsB->GetXaxis()->SetTitle("NHits");
    pHistNHitsB->GetXaxis()->SetRangeUser(0.0, 9.0);
    pHistNHitsB->GetXaxis()->CenterLabels();
    pHistNHitsB->GetYaxis()->SetTitle("Counts");
    pHistNHitsB->GetYaxis()->CenterTitle();
    pHistNHitsB->GetYaxis()->SetRangeUser(0.1,100.0E6);
    pHistNHitsB->SetLineColor(kRed);
    pHistNHitsB->SetStats(0);
    pHistNHitsB->Draw("SAME");

    pLegend = new TLegend(0.7,0.8,0.9,0.9);
    pLegend->AddEntry(pHistNHitsT, "Top Clusters");
    pLegend->AddEntry(pHistNHitsB, "Bot Clusters");
    pLegend->Draw();

    //////////////////////////////////    
    // Cluster Latency
    //////////////////////////////////    
    pPadClusterHist->cd(3);
    pPadClusterHist->cd(3)->SetLogy(1);

    pHistLatencyT = new TH1F("ClusterLatencyTop", "ClusterLatency", 1024, 0.0, 4.0*1024.0);
    pHistLatencyT->GetXaxis()->SetTitle("Latency(ns)");
    pHistLatencyT->GetXaxis()->SetRangeUser(0.0, 4096.0);
    pHistLatencyT->GetYaxis()->SetTitle("Counts");
    pHistLatencyT->GetYaxis()->CenterTitle();
    pHistLatencyT->GetYaxis()->SetRangeUser(0.1,100.0E6);
    pHistLatencyT->SetLineColor(kBlue);
    pHistLatencyT->SetStats(0);
    pHistLatencyT->Draw();

    pHistLatencyB = new TH1F("ClusterLatencyBot", "ClusterLatency", 1024, 0.0, 4.0*1024.0);
    pHistLatencyB->GetXaxis()->SetTitle("Latency(ns)");
    pHistLatencyB->GetXaxis()->SetRangeUser(0.0, 4096.0);
    pHistLatencyB->GetYaxis()->SetTitle("Counts");
    pHistLatencyB->GetYaxis()->CenterTitle();
    pHistLatencyB->GetYaxis()->SetRangeUser(0.1,100.0E6);
    pHistLatencyB->SetLineColor(kRed);
    pHistLatencyB->SetStats(0);
    pHistLatencyB->Draw("SAME");

    pLegend = new TLegend(0.7,0.8,0.9,0.9);
    pLegend->AddEntry(pHistLatencyT, "Top Clusters");
    pLegend->AddEntry(pHistLatencyB, "Bot Clusters");
    pLegend->Draw();

    pCanvas->GetCanvas()->cd();
    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
		
//    gVirtualX->GrabButton(GetId(), kButton1, kAnyModifier, kButtonPressMask, kNone, kNone);
//    gVirtualX->GrabButton(GetId(), kButton2, kAnyModifier, kButtonPressMask, kNone, kNone);
    gVirtualX->GrabButton(GetId(), kButton3, kAnyModifier, kButtonPressMask, kNone, kNone);

    pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);

    // Setup histograms to bin what we've selected by default
    SetSelectedHistogram(pComboHistSrc->GetSelected());
    cluster_x_sel = 0;
    cluster_y_sel = 0;
    cluster_sel_enabled = 0;

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
            UpdateHistogram();
            break;
          default:
            printf("button id %d pressed\n", (int)parm1);
            break;
        }
        break;

			case kCM_COMBOBOX:
        switch(parm1)
        {
          case CMB_HISTSRC:
            SetSelectedHistogram(pComboHistSrc->GetSelected());
            break;

          default:
            printf("combobox id %d pressed\n", (int)parm1);
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

  void UpdateLatencyHistogram(float scale, Bool_t normalize)
  {
    volatile unsigned int *HpsMon_HistLatencyT   = (volatile unsigned int *)((int)pM->BaseAddr + 0x573C);
    volatile unsigned int *HpsMon_HistLatencyB   = (volatile unsigned int *)((int)pM->BaseAddr + 0x5740);
    unsigned int buft[1024], bufb[1024];
    float val;

    pM->BlkReadReg32(HpsMon_HistLatencyT, buft, 1024, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(HpsMon_HistLatencyB, bufb, 1024, CRATE_MSG_FLAGS_NOADRINC);
    
    pPadClusterHist->cd(3);
    pHistLatencyT->Reset();
    pHistLatencyB->Reset();

    if(normalize)
    {
      pHistLatencyT->GetYaxis()->SetTitle("Hz");
      pHistLatencyB->GetYaxis()->SetTitle("Hz");
    }
    else
    {
      pHistLatencyT->GetYaxis()->SetTitle("Counts");
      pHistLatencyB->GetYaxis()->SetTitle("Counts");
    }
    
    for(int i = 0; i < 1024; i++)
    {
      val = (float)buft[i];
      if(normalize) val *= scale;
      pHistLatencyT->Fill(4*i, val);

      val = (float)bufb[i];
      if(normalize) val *= scale;
      pHistLatencyB->Fill(4*i, val);
    }

    pPadClusterHist->cd(3)->Modified();
  }

  void UpdatePositionHistogram(float scale, Bool_t normalize)
  {
    volatile unsigned int *HpsMon_HistPositionT  = (volatile unsigned int *)((int)pM->BaseAddr + 0x5724);
    volatile unsigned int *HpsMon_HistPositionB  = (volatile unsigned int *)((int)pM->BaseAddr + 0x5728);
    unsigned int buf[1024];
    float rate_top = 0.0, rate_bot = 0.0;
    static bool called=0;

    static TPaveText tt1(0.1,0.9,0.3,1.0,"NDC");
    static TPaveText tt2(0.7,0.91,0.9,0.99,"NDC");
    static TPaveText ttT(-22+13+0.05,6-5,-22+22,7-5-0.05);
    static TPaveText ttB(-22+13+0.05,4-5+0.05,-22+22,5-5);
    static TPaveText ttM(-22+0+0.05,5-5+0.05,-22+13,6-5);
    static TPaveText ttSel(10,5-5+0.05,22,6-5);
    static TBox bb;
    static TLine ll;

    if (!called)
    {
        called=1;
        bb.SetFillStyle(1001);
        bb.SetFillColor(kWhite);
        bb.SetLineWidth(1);
        bb.SetLineColor(kBlack);
        tt1.SetBorderSize(0);
        tt2.SetBorderSize(0);
        tt1.SetFillColor(kWhite);
        tt2.SetFillColor(kWhite);
        ttT.SetBorderSize(0);
        ttB.SetBorderSize(0);
        ttT.SetFillColor(kWhite);
        ttB.SetFillColor(kWhite);
        ttM.SetBorderSize(0);
        ttM.SetFillColor(kWhite);
        ttM.SetTextColor(kRed);
        ttSel.SetBorderSize(0);
        ttSel.SetFillColor(kWhite);
        ttSel.SetTextColor(kRed);
    }

    float max=0.0;
    
    pM->BlkReadReg32(HpsMon_HistPositionT, &buf[0], 512, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(HpsMon_HistPositionB, &buf[512], 512, CRATE_MSG_FLAGS_NOADRINC);

    pPadCalorimeter->cd();
    pHistPosition->Reset();

    int x, y;
    float x_rates[46];
    memset(x_rates, 0, sizeof(x_rates));
    for(int i = 0; i < 1024; i++)
    {
      float val = (float)buf[i];

      if(normalize) val *= scale;

      if(val > max) max = val;

      x = (i>>0) & 0x3F;
      y = (i>>6) & 0xF;

      if(x & 0x20) x |= 0xFFFFFFC0;
      if(y & 0x08) y |= 0xFFFFFFF0;

      x_rates[x+22]+= val;

      if(y > 0) rate_top += val;
      else      rate_bot += val;

      pHistPosition->Fill(x, y, val);
    }

    printf("cluster column rates:\n");
    for(int i=0; i<46; i++)
    {
      int x = (i < 23) ? i-23 : i-22;
      printf("ix %4d = %f\n", x, x_rates[i]);
    }

    bb.DrawBox(-9+0.05,-1,0,1.97);
    bb.DrawBox(-24,0,24.05,0.97);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmin(),pHistPosition->GetYaxis()->GetXmin(),
                pHistPosition->GetXaxis()->GetXmax(),pHistPosition->GetYaxis()->GetXmin());
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmin(),pHistPosition->GetYaxis()->GetXmax(),
                pHistPosition->GetXaxis()->GetXmax(),pHistPosition->GetYaxis()->GetXmax());
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmin(),pHistPosition->GetYaxis()->GetXmin(),
                pHistPosition->GetXaxis()->GetXmin(),0);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmax(),pHistPosition->GetYaxis()->GetXmin(),
                pHistPosition->GetXaxis()->GetXmax(),0);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmin(),pHistPosition->GetYaxis()->GetXmax(),
                pHistPosition->GetXaxis()->GetXmin(),1);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmax(),pHistPosition->GetYaxis()->GetXmax(),
                pHistPosition->GetXaxis()->GetXmax(),1);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmax(),0,0,0);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmax(),1,0,1);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmin(),0,-9,0);
    ll.DrawLine(pHistPosition->GetXaxis()->GetXmin(),1,-9,1);
    ll.DrawLine(-9,-1,0,-1);
    ll.DrawLine(-9,2,0,2);
    ll.DrawLine(-9,1,-9,2);
    ll.DrawLine(-9,-1,-9,0);
    ll.DrawLine(0,-1,0,0);
    ll.DrawLine(0,1,0,2);
                
    tt1.Clear();
    tt2.Clear();
    ttT.Clear();
    ttB.Clear();
    ttM.Clear();
    ttSel.Clear();

    if(cluster_sel_enabled)
      ttSel.AddText(Form("SEL ENABLED X,Y = %d,%d",(cluster_x_sel>0)?cluster_x_sel:cluster_x_sel-1, cluster_y_sel));

    if(normalize)
    {
      tt1.AddText(Form("Total Rate:  %.1E Hz",rate_top+rate_bot));
      tt2.AddText(Form("Total Rate:  %.1f kHz",(rate_top+rate_bot)/1000.0));
      ttT.AddText(Form("%.2f kHz",rate_top/1000.0));
      ttB.AddText(Form("%.2f kHz",rate_bot/1000.0));
      ttM.AddText(Form("MAX SINGLE CRYSTAL = %.2f kHz",(float)max/1000));
    }
    else
    {
      tt1.AddText(Form("Total Count:  %.1E",rate_top+rate_bot));
      ttM.AddText(Form("MAX SINGLE CRYSTAL = %.2f count",(float)max));
    }
    tt1.Draw();
    tt2.Draw();
    ttT.Draw();
    ttB.Draw();
    ttM.Draw();
    ttSel.Draw();
    pPadCalorimeter->cd()->Modified();
  }

  void UpdateEnergyHistogram(float scale, Bool_t normalize)
  {
    volatile unsigned int *HpsMon_HistEnergyT    = (volatile unsigned int *)((int)pM->BaseAddr + 0x572C);
    volatile unsigned int *HpsMon_HistEnergyB    = (volatile unsigned int *)((int)pM->BaseAddr + 0x5730);
    unsigned int buft[1024], bufb[1024];
    float val;

    pM->BlkReadReg32(HpsMon_HistEnergyT, buft, 1024, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(HpsMon_HistEnergyB, bufb, 1024, CRATE_MSG_FLAGS_NOADRINC);
    
    pPadClusterHist->cd(1);
    pHistEnergyT->Reset();
    pHistEnergyB->Reset();

    if(normalize)
    {
      pHistEnergyT->GetYaxis()->SetTitle("Hz");
      pHistEnergyB->GetYaxis()->SetTitle("Hz");
    }
    else
    {
      pHistEnergyT->GetYaxis()->SetTitle("Counts");
      pHistEnergyB->GetYaxis()->SetTitle("Counts");
    }
    
    for(int i = 0; i < 1024; i++)
    {
      val = (float)buft[i];
      if(normalize) val *= scale;
      pHistEnergyT->Fill(8*i, val);

      val = (float)bufb[i];
      if(normalize) val *= scale;
      pHistEnergyB->Fill(8*i, val);
    }

    pPadClusterHist->cd(1)->Modified();
  }

  void UpdateNHitsHistogram(float scale, Bool_t normalize)
  {
    volatile unsigned int *HpsMon_HistNHitsT     = (volatile unsigned int *)((int)pM->BaseAddr + 0x5734);
    volatile unsigned int *HpsMon_HistNHitsB     = (volatile unsigned int *)((int)pM->BaseAddr + 0x5738);
    unsigned int buft[16], bufb[16];
    float val;

    pM->BlkReadReg32(HpsMon_HistNHitsT, buft, 16, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(HpsMon_HistNHitsB, bufb, 16, CRATE_MSG_FLAGS_NOADRINC);
    
    pPadClusterHist->cd(2);
    pHistNHitsT->Reset();
    pHistNHitsB->Reset();

    if(normalize)
    {
      pHistNHitsT->GetYaxis()->SetTitle("Hz");
      pHistNHitsT->GetYaxis()->SetTitle("Hz");
    }
    else
    {
      pHistNHitsB->GetYaxis()->SetTitle("Counts");
      pHistNHitsB->GetYaxis()->SetTitle("Counts");
    }
    
    for(int i = 0; i < 16; i++)
    {
      val = (float)buft[i];
      if(normalize) val *= scale;
      pHistNHitsT->Fill(i, val);

      val = (float)bufb[i];
      if(normalize) val *= scale;
      pHistNHitsB->Fill(i, val);
    }

    pPadClusterHist->cd(2)->Modified();
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

    pPadTriggerInfo->cd();
    for(int i=0;i<8;i++)
    {
      pHistTriggerInfo[i]->Reset();

      if(normalize)
        pHistTriggerInfo[i]->SetTitle(Form("Trigger Rate Info;;Hz"));
      else
        pHistTriggerInfo[i]->SetTitle(Form("Trigger Rate Info;;Count"));
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

    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_MULT_PASS, mult_pass);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_MULT_TI, mult_ti);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_LED, led);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_LED_TI, led_ti);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_HODOSCOPE, hodoscope);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_HODOSCOPE_TI, hodoscope_ti);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_PULSER, pulser);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_PULSER_TI, pulser_ti);
    pHistTriggerInfo[0]->Fill(VTP_HPS_TRIG_INFO_L1A, l1a);

    pPadTriggerInfo->cd()->Modified();
  }
  
  void UpdateHodoscopeHistogram(float scale, Bool_t normalize)
  {
    volatile unsigned int *HpsMon_HodoscopeT     = (volatile unsigned int *)((int)pM->BaseAddr + 0x5744);
    volatile unsigned int *HpsMon_HodoscopeB     = (volatile unsigned int *)((int)pM->BaseAddr + 0x5748);
    unsigned int buft[18], bufb[18];
    Double_t x_l1, x_l2, val1, val2;

    pM->BlkReadReg32(HpsMon_HodoscopeT, buft, 18, CRATE_MSG_FLAGS_NOADRINC);
    pM->BlkReadReg32(HpsMon_HodoscopeB, bufb, 18, CRATE_MSG_FLAGS_NOADRINC);

    pPadHodoTop->cd();
    pHistHodoscope[HODO_TOP]->Reset("");
    pHistHodoscope[HODO_TOP_CLUSTERED]->Reset("");
    x_l1 = 0;
    x_l2 = HODO_L2_OFFSET;
    for(int i=0;i<9;i++)
    {
      val1 = normalize ? buft[i] * scale : buft[i];
      val2 = normalize ? buft[9+i] * scale : buft[9+i];

      x_l1+= Hodoscope_w_l1[i]/2.0;
      x_l2+= Hodoscope_w_l2[i]/2.0;
      if(i & 0x1)
      {
        pHistHodoscope[HODO_TOP_CLUSTERED]->Fill(x_l1,0.5*HODO_H, val1);
        pHistHodoscope[HODO_TOP_CLUSTERED]->Fill(x_l2,1.5*HODO_H, val2);
      }
      else
      {
        pHistHodoscope[HODO_TOP]->Fill(x_l1,0.5*HODO_H, val1);
        pHistHodoscope[HODO_TOP]->Fill(x_l2,1.5*HODO_H, val2);
      }
      x_l1+= Hodoscope_w_l1[i]/2.0;
      x_l2+= Hodoscope_w_l2[i]/2.0;
    }
    pPadHodoTop->cd()->Modified();


    pPadHodoBot->cd();
    pHistHodoscope[HODO_BOT]->Reset("");
    pHistHodoscope[HODO_BOT_CLUSTERED]->Reset("");
    x_l1 = 0;
    x_l2 = HODO_L2_OFFSET;
    for(int i=0;i<9;i++)
    {
      val1 = normalize ? bufb[i] * scale : bufb[i];
      val2 = normalize ? bufb[9+i] * scale : bufb[9+i];

      x_l1+= Hodoscope_w_l1[i]/2.0;
      x_l2+= Hodoscope_w_l2[i]/2.0;
      if(i & 0x1)
      {
        pHistHodoscope[HODO_BOT_CLUSTERED]->Fill(x_l1,0.5*HODO_H, val1);
        pHistHodoscope[HODO_BOT_CLUSTERED]->Fill(x_l2,1.5*HODO_H, val2);
      }
      else
      {
        pHistHodoscope[HODO_BOT]->Fill(x_l1,0.5*HODO_H, val1);
        pHistHodoscope[HODO_BOT]->Fill(x_l2,1.5*HODO_H, val2);
      }
      x_l1+= Hodoscope_w_l1[i]/2.0;
      x_l2+= Hodoscope_w_l2[i]/2.0;
    }
    pPadHodoBot->cd()->Modified();
  }

  void UpdateHistogram(Bool_t bReadout = kTRUE)
  {
    volatile unsigned int *HpsMon_HistCtrl       = (volatile unsigned int *)((int)pM->BaseAddr + 0x5700);
    volatile unsigned int *HpsMon_HistTime       = (volatile unsigned int *)((int)pM->BaseAddr + 0x5720);

    pM->WriteReg32(HpsMon_HistCtrl, 0x00);  // disable histograms

    Bool_t normalize = pButtonNormalize->IsDown();
    
    unsigned int ref = pM->ReadReg32(HpsMon_HistTime);
    float scale = ref;
    if(normalize && (scale <= 0.0))
    {
      printf("SSP cluster histogram reference time invalid. not normalizing data.\n");
      normalize = kFALSE;
    }
    else
    {
      scale = scale * 256.0f / 250.0E6;
      scale = 1.0f / scale;
    }


    UpdateLatencyHistogram(scale, normalize);
    UpdatePositionHistogram(scale, normalize);
    UpdateEnergyHistogram(scale, normalize);
    UpdateNHitsHistogram(scale, normalize);
    UpdateHodoscopeHistogram(scale, normalize);

    pM->WriteReg32(HpsMon_HistCtrl, 0xFFFFFFFF);  // enable histograms

    // scalers
    UpdateScalers(pButtonNormalize->IsDown());

    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
  }


  void SetSelectedHistogram(int sel)
  {
    volatile unsigned int *HpsMon_HistSel        = (volatile unsigned int *)((int)pM->BaseAddr + 0x5704);
    int val = (sel & 0xF)<<11;
    val|= cluster_sel_enabled ? 1 : 0;
    val|= (cluster_x_sel & 0x3f)<<5;
    val|= (cluster_y_sel & 0xf)<<1;
    pM->WriteReg32(HpsMon_HistSel, val);
  }

  void HodoHist(TH2Poly *pH, int tiles_nclusters)
  {
    Double_t x_pos_l1 = 0.0;
    Double_t x_pos_l2 = HODO_L2_OFFSET;
    Double_t x[4], y[4];

    for(int i=0;i<HODO_NSCALERS;i++)
    {
      x[0] = x_pos_l1;                   y[0] = 0.0;
      x[1] = x_pos_l1;                   y[1] = HODO_H;
      x[2] = x_pos_l1+Hodoscope_w_l1[i]; y[2] = HODO_H;
      x[3] = x_pos_l1+Hodoscope_w_l1[i]; y[3] = 0.0;
      if(tiles_nclusters && !(i&0x1))      pH->AddBin(4,x,y);
      else if(!tiles_nclusters && (i&0x1)) pH->AddBin(4,x,y);
      x_pos_l1+= Hodoscope_w_l1[i];
    }

    for(int i=0;i<HODO_NSCALERS;i++)
    {
      x[0] = x_pos_l2;                   y[0] = HODO_H*2;
      x[1] = x_pos_l2;                   y[1] = HODO_H;
      x[2] = x_pos_l2+Hodoscope_w_l2[i]; y[2] = HODO_H;
      x[3] = x_pos_l2+Hodoscope_w_l2[i]; y[3] = HODO_H*2;
      if(tiles_nclusters && !(i&0x1))      pH->AddBin(4,x,y);
      else if(!tiles_nclusters && (i&0x1)) pH->AddBin(4,x,y);
      x_pos_l2+= Hodoscope_w_l2[i];
    } 
  }

	virtual Bool_t HandleButton(Event_t *event)
	{
		TGCompositeFrame::HandleButton(event);

		if(event->fCode == kButton3)
    {
      float xmin = 0.103, xmax = 0.896, ymin = 0.396, ymax = 0.631;
      float x = (float)event->fX / (float)GetWidth();
      float y = (float)event->fY / (float)GetHeight();

      if(x>=xmin && x<=xmax && y>=ymin && y<=ymax)
      {
        float xscale = round(46.0*(x-xmin)/(xmax-xmin)-0.5);
        float yscale = round(-11.0*(y-ymin)/(ymax-ymin)+0.5);
        cluster_x_sel = -22.0 + xscale;
        cluster_y_sel =   5.0 + yscale;

        if(cluster_sel_enabled)
          cluster_sel_enabled = 0;
        else
          cluster_sel_enabled = 1;
      
        printf("kButton3: %d event->fX,fY(%d,%d), x,y(%f,%f), ix,iy(%d,%d)\n", cluster_sel_enabled, event->fX, event->fY, x, y, cluster_x_sel, cluster_y_sel);

        SetSelectedHistogram(pComboHistSrc->GetSelected());
      }
      else
        printf("kButton3: invalid: event->fX,fY(%d,%d), x,y(%f,%f)\n", event->fX, event->fY, x, y);
        
    }
		return kTRUE;
	}


private:

  enum Buttons
  {
    BTN_AUTOUPDATE    = 1002,
    BTN_MANUALUPDATE  = 1003,
    SDR_UPDATETIME    = 1100
  };

  const Double_t Hodoscope_w_l1[HODO_NSCALERS] = {
      15.7-HODO_CLW/2,  // Tile 1
      HODO_CLW,
      34.1-HODO_CLW,    // Tile 2
      HODO_CLW,
      44.0-HODO_CLW,    // Tile 3
      HODO_CLW,
      44.0-HODO_CLW,    // Tile 4
      HODO_CLW,
      44.0-HODO_CLW/2   // Tile 5
    };

  const Double_t Hodoscope_w_l2[HODO_NSCALERS] = {
      19.0-HODO_CLW/2,  // Tile 1
      HODO_CLW,
      44.0-HODO_CLW,    // Tile 2
      HODO_CLW,
      44.0-HODO_CLW,    // Tile 3
      HODO_CLW,
      44.0-HODO_CLW,    // Tile 4
      HODO_CLW,
      30.8-HODO_CLW/2   // Tile 5
    };

  const int HODO_TOP           = 0;
  const int HODO_BOT           = 1;
  const int HODO_TOP_CLUSTERED = 2;
  const int HODO_BOT_CLUSTERED = 3;

  int cluster_x_sel;
  int cluster_y_sel;
  int cluster_sel_enabled;
 
 
  ModuleFrame         *pM;

  TTimer              *pTimerUpdate;

  TRootEmbeddedCanvas *pCanvas;

  TPad                *pPadTriggerInfo;
  TPad                *pPadHodoTop;
  TPad                *pPadCalorimeter;
  TPad                *pPadHodoBot;
  TPad                *pPadClusterHist;

  TH1F                *pHistLatencyT, *pHistLatencyB;
  TH1F                *pHistEnergyT, *pHistEnergyB;
  TH1F                *pHistNHitsT, *pHistNHitsB;
  TH2F                *pHistPosition;
  TH1F                *pHistTriggerInfo[8];
  TH2Poly             *pHistHodoscope[4];
  
  TGSlider            *pSliderUpdateTime;

  TGTextButton        *pButtonAutoUpdate;
  TGTextButton        *pButtonManualUpdate;
  TGTextButton        *pButtonNormalize;

  TGComboBox          *pComboHistSrc;
};

#endif

