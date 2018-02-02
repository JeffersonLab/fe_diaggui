#include <stdio.h>
#include <stdlib.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TPaveText.h>
#include <TH2Poly.h>
#include <TMath.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRootEmbeddedCanvas.h>
#include <TApplication.h>
#include <TClass.h>
#include <TGFileDialog.h>
#include <TGButton.h>
#include <TImage.h>
#include <THashList.h>
#include <TTimeStamp.h>
#include <iostream>
#include "CrateMsgClient.h"

#define SCALER_UPDATE_PERIOD	1000	/* in milliseconds */
#define MSG_PORT              6102
#define THRESHOLD_MAX         200

#define BTN_SAVE              0
#define BTN_INIT              1
#define BTN_EXIT              2
#define SDR_THRESHOLD         3

unsigned int dcrb_addr[14] = {
    0x00180000,   // Slot 3
    0x00200000,   // Slot 4
    0x00280000,   // Slot 5
    0x00300000,   // Slot 6
    0x00380000,   // Slot 7
    0x00400000,   // Slot 8
    0x00480000,   // Slot 9
    0x00700000,   // Slot 14
    0x00780000,   // Slot 15
    0x00800000,   // Slot 16
    0x00880000,   // Slot 17
    0x00900000,   // Slot 18
    0x00980000,   // Slot 19
    0x00A00000    // Slot 20
  };

class dc_scalers_app : public TGMainFrame
{
  private:
    int connect_to_server();
    int read_scalers();

    unsigned int dc_scalers[6][3][14][96];
    unsigned int dc_ref[6][3][14];
    Double_t dc_tot[6][3][2];

    void draw_scalers();
    void normalize_scalers();
    void sum_scalers();
    void Honeycomb(TH2Poly *pH, Double_t xstart, Double_t ystart, Double_t a);
    void SetThreshold(unsigned int thr);
    Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);
    Bool_t HandleTimer(TTimer *t);

    TGSlider *pSliderThreshold;
    TGLabel *pLabelThreshold;
    TTimer *pTimerUpdate;
    CrateMsgClient *crate_dc[6][3];
    TCanvas *pTC;
    TH2Poly *pH[6];
    TRootEmbeddedCanvas *pCanvas;
  public:
    dc_scalers_app(const TGWindow *p, UInt_t w, UInt_t h);
    ~dc_scalers_app();

    void button_init();
    void DoExit();
    void button_Save();
    void refresh_scalers();
};

Bool_t dc_scalers_app::HandleTimer(TTimer *t)
{
  if(pTimerUpdate->HasTimedOut())
  {
    refresh_scalers();
    pTimerUpdate->Start(SCALER_UPDATE_PERIOD, kTRUE);
  }
  return kTRUE;
}
  
Bool_t dc_scalers_app::ProcessMessage(Long_t msg, Long_t parm1, Long_t)
{
  switch(GET_MSG(msg))
  {
    case kC_COMMAND:
      switch(GET_SUBMSG(msg))
      {
        case kCM_BUTTON:
          switch(parm1)
          {
            case BTN_SAVE:
              button_Save();
              break;
            case BTN_INIT:
              button_init();
              break;
            case BTN_EXIT:
              DoExit();
              break;
          }
          break;
      }
      break;
      
    case kC_HSLIDER:
      switch(parm1)
      {
        case SDR_THRESHOLD:
          TGString *pStr = new TGString;
          pStr->Form("DACThreshold (%dmV):", pSliderThreshold->GetPosition());
          pLabelThreshold->SetText(pStr);
          break;
      }
      break;
  }
  return kTRUE;
}

int dc_scalers_app::connect_to_server()
{
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  {
    printf("Connecting to: %s\n", Form("dc%d%d",s+1,r+1));
    crate_dc[s][r] = new CrateMsgClient(Form("dc%d%d",s+1,r+1), MSG_PORT);
  }
  return 0;
}

int dc_scalers_app::read_scalers()
{
  unsigned int *buf;
  int len;
  unsigned int val[1];

  memset(dc_scalers, 0, sizeof(dc_scalers));
  memset(dc_ref, 0, sizeof(dc_ref));
  
  // Disable scalers
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  {
    if(!crate_dc[s][r]->IsValid())
      continue;
    
    val[0] = 1;
    for(int n=0;n<14;n++)
      crate_dc[s][r]->Write32(dcrb_addr[n]+0x0300, val);
  }
  
  // Read scaler values
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  {
    if(!crate_dc[s][r]->IsValid())
      continue;
    
    for(int n=0;n<14;n++)
    {
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x0304, &dc_ref[s][r][n]);
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x1100, &dc_scalers[s][r][n][0], 16, CRATE_MSG_FLAGS_ADRINC);
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x1300, &dc_scalers[s][r][n][16], 16, CRATE_MSG_FLAGS_ADRINC);
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x1500, &dc_scalers[s][r][n][32], 16, CRATE_MSG_FLAGS_ADRINC);
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x1700, &dc_scalers[s][r][n][48], 16, CRATE_MSG_FLAGS_ADRINC);
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x1900, &dc_scalers[s][r][n][64], 16, CRATE_MSG_FLAGS_ADRINC);
      crate_dc[s][r]->Read32(dcrb_addr[n]+0x1B00, &dc_scalers[s][r][n][80], 16, CRATE_MSG_FLAGS_ADRINC);
    }
  }

  // Reset & enable scalers
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  {
    if(!crate_dc[s][r]->IsValid())
      continue;
    
    val[0] = 0;
    for(int n=0;n<14;n++)
      crate_dc[s][r]->Write32(dcrb_addr[n]+0x0300, val);
  }
  return 0;
}

void dc_scalers_app::normalize_scalers()
{
  float ref, scaled;

  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  for(int n=0;n<14;n++)
  {
    if(!crate_dc[s][r]->IsValid())
      continue;

    if(!dc_ref[s][r][n])
    {
      printf("Error in %s: [%d][%d][%d]=%d not valid\n", __func__, s,r,n,dc_ref[s][r][n]);
      ref = 1;
    }
    else
      ref = 50000000.0f / (float)dc_ref[s][r][n];
    
    for(int ch=0;ch<96;ch++)
    {
      scaled = (float)dc_scalers[s][r][n][ch] * ref;
      dc_scalers[s][r][n][ch] = (unsigned int)scaled;
    }
  }
}

void dc_scalers_app::sum_scalers()
{
  memset(dc_tot, 0, sizeof(dc_tot));
  
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  for(int n=0;n<14;n++)
  for(int ch=0;ch<96;ch++)
    dc_tot[s][r][n/7]+= dc_scalers[s][r][n][ch];
}

void dc_scalers_app::button_init()
{
  unsigned int val[1];
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  for(int n=0;n<14;n++)
  {
    if(!crate_dc[s][r]->IsValid())
      continue;
   
    // Clock reset release
    val[0] = 0;
    crate_dc[s][r]->Write32(dcrb_addr[n]+0x100, val);
    
    // Soft reset release
    val[0] = 0;
    crate_dc[s][r]->Write32(dcrb_addr[n]+0x20, val);
  }
  
  SetThreshold(pSliderThreshold->GetPosition());
}

void dc_scalers_app::SetThreshold(unsigned int thr)
{
  unsigned int val[1];
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  for(int n=0;n<14;n++)
  {
    if(!crate_dc[s][r]->IsValid())
      continue;
   
    val[0] = (int)(((float)thr) * -8.06f + 2048.0f);
    crate_dc[s][r]->Write32(dcrb_addr[n]+0x24, val);
  }
}

void dc_scalers_app::draw_scalers()
{
  static Bool_t called = kFALSE;
  static TPaveText tt[6][3][2];
  
  if(!called)
  {
    called = kTRUE;
    
    for(int s=0;s<6;s++)
    for(int r=0;r<3;r++)
    for(int sl=0;sl<2;sl++)
    {
      tt[s][r][sl].SetTextSize(0.0225);
      tt[s][r][sl].SetBorderSize(0);
      tt[s][r][sl].SetFillColor(kWhite);
      tt[s][r][sl].SetTextColor(kRed);
      tt[s][r][sl].SetX1NDC(0.0);
      tt[s][r][sl].SetX2NDC(0.0);
      tt[s][r][sl].SetY1NDC(0.120+0.136*(2*r+sl));
      tt[s][r][sl].SetY2NDC(0.120+0.136*(2*r+sl));
    }
  }
  
  for(int i=0;i<6;i++)
  {
    pH[i]->Reset("");
    pH[i]->SetMaximum(1000000.0);
    pH[i]->SetMinimum(0.0);
  }

  for(int s=0;s<6;s++)
  {
    pCanvas->GetCanvas()->cd(s+1);
    
    for(int r=0;r<3;r++)
    for(int sl=0;sl<2;sl++)
    {
      tt[s][r][sl].Clear();
      tt[s][r][sl].AddText(Form("%.0fMHz", dc_tot[s][r][sl]/1e6));
      tt[s][r][sl].Draw();
    }
  }
  
  for(int s=0;s<6;s++)
  for(int r=0;r<3;r++)
  for(int n=0;n<14;n++)
  for(int ch=0;ch<96;ch++)
  {
    Double_t x = 16.0*(n%7)+(int)(ch/6);
    Double_t y = ((double)(ch % 3)) * 1.732 + 6*(2*r+(int)(n/7));
    if((ch%6)<3)
    {
      x-= 0.5;
      y+= 0.866;
    }
    pH[s]->Fill(x, y, dc_scalers[s][r][n][ch]);
  }
  
  for(int i=0;i<6;i++)
    pCanvas->GetCanvas()->cd(i+1)->Modified();
  
  pCanvas->GetCanvas()->Update();
}

void dc_scalers_app::refresh_scalers()
{
    if(read_scalers() < 0) DoExit();

    normalize_scalers();
    sum_scalers();
    draw_scalers();

    pTimerUpdate->Start(SCALER_UPDATE_PERIOD, kTRUE);
}

void dc_scalers_app::DoExit()
{
    gApplication->Terminate();
}

dc_scalers_app::~dc_scalers_app()
{
    Cleanup();
}

void dc_scalers_app::button_Save()
{
    TTimeStamp tt;
    TString tstub=tt.AsString("lc");
    tstub.ReplaceAll(" ","_");

    gPad->SaveAs(Form("%s/screenshots/DCSCALERS_%s.png",
                gSystem->Getenv("HOME"),tstub.Data()));
    std::cerr<<"AL:SFHDLA"<<std::endl;
    return;
}

dc_scalers_app::dc_scalers_app(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h) 
{
  printf("dc_scalers_app started...\n");

  SetCleanup(kDeepCleanup);

//  Connect("CloseWindow()", "dc_scalers_app", this, "DoExit()");
  DontCallClose();

  TGCompositeFrame *pTF;
  TGTextButton *pB;

  AddFrame(pTF = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
  pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Save"), BTN_SAVE), new TGLayoutHints(kLHintsLeft | kLHintsCenterX));
  pB->Associate(this);
//  pB->Connect("Clicked()", "dc_scalers_app", this, "button_Save()");
  pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Init"), BTN_INIT), new TGLayoutHints(kLHintsLeft | kLHintsCenterX));
  pB->Associate(this);
//  pB->Connect("Clicked()", "dc_scalers_app", this, "button_init()");
  pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Exit"), BTN_EXIT), new TGLayoutHints(kLHintsLeft | kLHintsCenterX));
  pB->Associate(this);
//  pB->Connect("Clicked()", "dc_scalers_app", this, "DoExit()");
  pTF->AddFrame(pLabelThreshold = new TGLabel(pTF, new TGString(Form("DACThreshold (?):"))), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
    pTF->AddFrame(pSliderThreshold = new TGHSlider(pTF, 100, kSlider1 | kScaleBoth, SDR_THRESHOLD), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
      pSliderThreshold->SetRange(0, THRESHOLD_MAX);
      pSliderThreshold->SetPosition(0);
      pSliderThreshold->Associate(this);      
  
  AddFrame(pTF = new TGVerticalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
  pTF->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pTF, w, h), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
  
  gPad->SetLogz(1);
  gPad->SetLeftMargin(0.0);
  gPad->SetRightMargin(0.1);
  gStyle->SetOptTitle(0);

  
  pCanvas->GetCanvas()->SetBorderMode(0);
  pCanvas->GetCanvas()->Divide(3,2,0.01,0.01);
  
  TText tt;
  for(int i=0;i<6;i++)
  {
    pH[i] = new TH2Poly();
    Honeycomb(pH[i], -0.5, 30-0.5773502692, 0.5773502692);
    Honeycomb(pH[i], -0.5, 24-0.5773502692, 0.5773502692);
    Honeycomb(pH[i], -0.5, 18-0.5773502692, 0.5773502692);
    Honeycomb(pH[i], -0.5, 12-0.5773502692, 0.5773502692);
    Honeycomb(pH[i], -0.5, 6-0.5773502692, 0.5773502692);
    Honeycomb(pH[i], -0.5, -0.5773502692, 0.5773502692);
    
    pCanvas->GetCanvas()->cd(i+1);
    pCanvas->GetCanvas()->cd(i+1)->SetLogz(1);
    pH[i]->SetStats(0);
    pH[i]->GetXaxis()->SetNdivisions(112, kTRUE);
    pH[i]->GetYaxis()->SetLabelSize(0);
    pH[i]->GetYaxis()->SetLabelOffset(999);
    pH[i]->GetZaxis()->SetLabelSize(0.03);
    pH[i]->SetBarOffset(0.10);
    pH[i]->SetBarWidth(0.10);
    pH[i]->SetTitle(Form("DC%d", i+1));
    pH[i]->Draw("COLZ L");
    
    tt.SetTextAngle(0);
    tt.SetTextSize(0.05);
    tt.DrawTextNDC(0.4,0.92,Form("Sector %d",i+1));
    
    tt.SetTextSize(0.03);
    tt.DrawTextNDC(0.0,0.150,"SL1");
    tt.DrawTextNDC(0.0,0.286,"SL2");
    tt.DrawTextNDC(0.0,0.422,"SL3");
    tt.DrawTextNDC(0.0,0.558,"SL4");
    tt.DrawTextNDC(0.0,0.694,"SL5");
    tt.DrawTextNDC(0.0,0.830,"SL6");
  }
   
  if(connect_to_server() < 0) DoExit();

  SetWindowName("DC SCALERS");
  MapSubwindows();
  Resize();
  MapWindow();

  pTimerUpdate = new TTimer(this, SCALER_UPDATE_PERIOD, kTRUE);
  pTimerUpdate->Start(SCALER_UPDATE_PERIOD, kTRUE);
}

void dc_scalers_app::Honeycomb(TH2Poly *pH, Double_t xstart, Double_t ystart, Double_t a)
{
  Int_t k = 112;
  Int_t s = 6;
  // Bins the histogram using a honeycomb structure
  // Add the bins
  Double_t x[6], y[6];
  Double_t xloop, yloop, xtemp;
  xloop = xstart; yloop = ystart + a/2.0;
  for(int sCounter = 0; sCounter < s; sCounter++)
  {
    xtemp = xloop; // Resets the temp variable

    for (int kCounter = 0; kCounter <  k; kCounter++)
    {

      // Go around the hexagon
      x[0] = xtemp;
      y[0] = yloop;
      x[1] = x[0];
      y[1] = y[0] + a;
      x[2] = x[1] + a*TMath::Sqrt(3)/2.0;
      y[2] = y[1] + a/2.0;
      x[3] = x[2] + a*TMath::Sqrt(3)/2.0;
      y[3] = y[1];
      x[4] = x[3];
      y[4] = y[0];
      x[5] = x[2];
      y[5] = y[4] - a/2.0;

      pH->AddBin(6, x, y);

      // Go right
      xtemp += a*TMath::Sqrt(3);
    }

    // Increment the starting position
    if(sCounter%2 == 1)
      xloop += a*TMath::Sqrt(3)/2.0;
    else
      xloop -= a*TMath::Sqrt(3)/2.0;
    
    yloop += 1.5*a;
  }
}

int main(int argc, char* argv[])
{
  int cargc = 1;
  TApplication App("DC Scaler GUI", &cargc, argv);

  if(gROOT->IsBatch())
  {
    fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
    return 1;
  }

  dc_scalers_app *pdc_scalers_app = new dc_scalers_app(gClient->GetRoot(), 800, 600);
  App.Run();

  delete pdc_scalers_app;
  return 0;
}
