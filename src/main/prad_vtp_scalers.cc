#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TClass.h>
#include <TGButton.h>
#include <TGFileDialog.h>
#include <TGLabel.h>
#include <TGSlider.h>
#include <TH2.h>
#include <TH2Poly.h>
#include <THashList.h>
#include <TImage.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TRootEmbeddedCanvas.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TTimeStamp.h>
#include "CrateMsgClient.h"
#include "hycal_map.h"
#include "hycal_coord_pkg.h"

#define SCALER_UPDATE_PERIOD	1000	/* in milliseconds */
#define MSG_PORT              6102
#define N_VTPS                7

#define BTN_SAVE              0
#define BTN_INIT              1
#define BTN_EXIT              2

class prad_vtp_scalers_app : public TGMainFrame
{
  private:
    int connect_to_server();
    int read_scalers();

    unsigned int vtp_nhits[N_VTPS][16];
    unsigned int vtp_energy[N_VTPS][1024];
    unsigned int vtp_pos[N_VTPS][256];
    unsigned int vtp_ref[N_VTPS];
    Double_t vtp_pos_tot;

    void draw_scalers();
    void normalize_scalers();
    void sum_scalers();
    void SetThreshold(unsigned int thr);
    Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);
    Bool_t HandleTimer(TTimer *t);

    TTimer *pTimerUpdate;
    CrateMsgClient *crate_pradvtp[N_VTPS];
    TCanvas *pTC;
    TH2Poly *pH_Position;
    TH1F *pH_Nhits;
    TH1F *pH_Energy;
    TRootEmbeddedCanvas *pC;
  public:
    prad_vtp_scalers_app(const TGWindow *p, UInt_t w, UInt_t h);
    ~prad_vtp_scalers_app();

    void button_init();
    void DoExit();
    void button_Save();
    void refresh_scalers();
};

Bool_t prad_vtp_scalers_app::HandleTimer(TTimer *t)
{
  if(pTimerUpdate->HasTimedOut())
  {
    refresh_scalers();
    pTimerUpdate->Start(SCALER_UPDATE_PERIOD, kTRUE);
  }
  return kTRUE;
}
  
Bool_t prad_vtp_scalers_app::ProcessMessage(Long_t msg, Long_t parm1, Long_t)
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
  }    
  return kTRUE;
}

int prad_vtp_scalers_app::connect_to_server()
{
  for(int c=0;c<N_VTPS;c++)
  {
    printf("Connecting to: %s\n", Form("adchycal%dvtp",c+1));
    crate_pradvtp[c] = new CrateMsgClient(Form("adchycal%dvtp",c+1), MSG_PORT, false);
  }
  return 0;
}

int prad_vtp_scalers_app::read_scalers()
{
  unsigned int *buf;
  int len;
  unsigned int val[1];

  memset(vtp_ref, 0, sizeof(vtp_ref));
  memset(vtp_pos, 0, sizeof(vtp_pos));
  memset(vtp_energy, 0, sizeof(vtp_energy));
  memset(vtp_nhits, 0, sizeof(vtp_nhits));
  
  // Disable scalers
  for(int c=0;c<N_VTPS;c++)
  {
    if(!crate_pradvtp[c]->IsValid())
      continue;
    
    val[0] = 0x0;
    crate_pradvtp[c]->Write32(0x1BA10, val);
  }

  // Read scaler values
  for(int c=0;c<N_VTPS;c++)
  {
    if(!crate_pradvtp[c]->IsValid())
      continue;

    // cluster nhits histogram
    crate_pradvtp[c]->Read32(0x1BA2C, &vtp_nhits[c][0], 16, CRATE_MSG_FLAGS_NOADRINC);

    // cluster energy histogram
    crate_pradvtp[c]->Read32(0x1BA28, &vtp_energy[c][0], 1024, CRATE_MSG_FLAGS_NOADRINC);

    // cluster position histogram
    crate_pradvtp[c]->Read32(0x1BA24, &vtp_pos[c][0], 256, CRATE_MSG_FLAGS_NOADRINC);
/*
printf("c=%d: ", c);
for(int i=0;i<256;i++)
  printf("%d ", vtp_pos[c][i]);
printf("\n");
*/
    // reference time scaler
    crate_pradvtp[c]->Read32(0x1BA20, &vtp_ref[c]);
//printf("ref[%d]=%d\n", c, vtp_ref[c]);
  }

  // Reset & enable scalers
  for(int c=0;c<N_VTPS;c++)
  {
    if(!crate_pradvtp[c]->IsValid())
      continue;

    val[0] = 0xF;
    crate_pradvtp[c]->Write32(0x1BA10, val);
  }
  return 0;
}

void prad_vtp_scalers_app::normalize_scalers()
{
  float ref, scaled;

  for(int c=0;c<N_VTPS;c++)
  {
    if(!crate_pradvtp[c]->IsValid())
      continue;

    if(!vtp_ref[c])
    {
      printf("Error in %s: vtp_ref[%d]=%d not valid\n", __func__, c,vtp_ref[c]);
      ref = 1;
    }
    else
      ref = 1000000.0 / (float)vtp_ref[c];

    for(int i=0;i<16;i++)
      vtp_nhits[c][i] = (unsigned int)((float)vtp_nhits[c][i]*ref);

    for(int i=0;i<1024;i++)
      vtp_energy[c][i] = (unsigned int)((float)vtp_energy[c][i]*ref);

    for(int i=0;i<256;i++)
    {
      vtp_pos[c][i] = (unsigned int)((float)vtp_pos[c][i]*ref);
if(vtp_pos[c][i] > 100)
  printf("vtp_pos[%d][%d]>100\n",c,i);
    }
  }
}

void prad_vtp_scalers_app::sum_scalers()
{
  vtp_pos_tot = 0.0;

  for(int c=0;c<N_VTPS;c++)
  for(int i=0;i<256;i++)
    vtp_pos_tot+= (Double_t)vtp_pos[c][i];
}

void prad_vtp_scalers_app::button_init()
{
}

void prad_vtp_scalers_app::draw_scalers()
{
  static Bool_t called = kFALSE;
  static TPaveText tt[6][3][2];
 #if 0 
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
#endif
  pH_Position->Reset("");
  pH_Position->SetMaximum(1000000.0);
  pH_Position->SetMinimum(0.1);
  int y_offset[N_VTPS] = {0,16,28,40,52,64,76};
  for(int c=0;c<N_VTPS;c++)
  for(int i=0;i<256;i++)
  {
    int blockid = -1;
    for(int j=0;j<sizeof(HYCAL_MAP)/sizeof(HYCAL_MAP[0]);j++)
    {
      if( (c==HYCAL_MAP[j].crate) && (i==HYCAL_MAP[j].local_bin) )
      {
        blockid = HYCAL_MAP[j].blockid;
        break;
      }
    }
    if(blockid>0)
    {
      for(int j=0;j<sizeof(HYCAL_COORD)/sizeof(HYCAL_COORD[0]);j++)
      {
        if(blockid==HYCAL_COORD[j].id)
        {
          pH_Position->Fill(HYCAL_COORD[j].x, HYCAL_COORD[j].y, vtp_pos[c][i]);
          break;
        }
      }
    }
  }

  pH_Energy->Reset("");
  for(int c=0;c<N_VTPS;c++)
  for(int i=0;i<1024;i++)
    pH_Energy->Fill(i*16, vtp_energy[c][i]);
   
  pH_Nhits->Reset("");
  for(int c=0;c<N_VTPS;c++)
  for(int i=0;i<16;i++)
    pH_Nhits->Fill(i, vtp_nhits[c][i]);

  pC->GetCanvas()->cd(1)->Modified();
  pC->GetCanvas()->cd(2)->cd(1)->Modified();
  pC->GetCanvas()->cd(2)->cd(2)->Modified();
  
  pC->GetCanvas()->Update();
}

void prad_vtp_scalers_app::refresh_scalers()
{
  if(read_scalers() < 0) DoExit();

  normalize_scalers();
  sum_scalers();
  draw_scalers();

  pTimerUpdate->Start(SCALER_UPDATE_PERIOD, kTRUE);
}

void prad_vtp_scalers_app::DoExit()
{
  gApplication->Terminate();
}

prad_vtp_scalers_app::~prad_vtp_scalers_app()
{
  Cleanup();
}

void prad_vtp_scalers_app::button_Save()
{
  TTimeStamp tt;
  TString tstub=tt.AsString("lc");
  tstub.ReplaceAll(" ","_");
  gPad->SaveAs(Form("%s/screenshots/PRAD_VTP_SCALERS_%s.png", gSystem->Getenv("HOME"), tstub.Data()));
  std::cerr<<"AL:SFHDLA"<<std::endl;
}

TH2Poly *TH2Poly_PRAD()
{
  Double_t x[4], y[4];
  TH2Poly *pH = new TH2Poly();
  for(int i=0;i<sizeof(HYCAL_COORD)/sizeof(HYCAL_COORD[0]);i++)
  {
    x[0] = HYCAL_COORD[i].x - HYCAL_COORD[i].size_x/2.0;
    y[0] = HYCAL_COORD[i].y - HYCAL_COORD[i].size_y/2.0;
    x[1] = HYCAL_COORD[i].x + HYCAL_COORD[i].size_x/2.0;
    y[1] = HYCAL_COORD[i].y - HYCAL_COORD[i].size_y/2.0;
    x[2] = HYCAL_COORD[i].x + HYCAL_COORD[i].size_x/2.0;
    y[2] = HYCAL_COORD[i].y + HYCAL_COORD[i].size_y/2.0;
    x[3] = HYCAL_COORD[i].x - HYCAL_COORD[i].size_x/2.0;
    y[3] = HYCAL_COORD[i].y + HYCAL_COORD[i].size_y/2.0;
    pH->AddBin(4, x, y);
  }
  return pH;
}

prad_vtp_scalers_app::prad_vtp_scalers_app(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h) 
{
  printf("prad_vtp_scalers_app started...\n");

  SetCleanup(kDeepCleanup);

  DontCallClose();

  TGCompositeFrame *pTF;
  TGTextButton *pB;

  AddFrame(pTF = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
    pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Save"), BTN_SAVE), new TGLayoutHints(kLHintsLeft | kLHintsCenterX)); pB->Associate(this);
    pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Init"), BTN_INIT), new TGLayoutHints(kLHintsLeft | kLHintsCenterX)); pB->Associate(this);
    pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Exit"), BTN_EXIT), new TGLayoutHints(kLHintsLeft | kLHintsCenterX)); pB->Associate(this);
  
  AddFrame(pTF = new TGVerticalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    pTF->AddFrame(pC = new TRootEmbeddedCanvas("c1", pTF, w, h), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

  gStyle->SetPalette(1, NULL);
  gStyle->SetPaintTextFormat(".0f");
 /* 
  gPad->SetLogz(1);
  gPad->SetLeftMargin(0.1);
  gPad->SetRightMargin(0.1);
  gStyle->SetOptTitle(0);
*/
  pC->GetCanvas()->SetBorderMode(0);
  pC->GetCanvas()->Divide(1,2,0.01,0.01);
  pC->GetCanvas()->cd(2)->Divide(2,1,0.01,0.01);

  // Cluster Position
  pC->GetCanvas()->cd(1);
  pC->GetCanvas()->cd(1)->SetLogz(1);
  pH_Position = TH2Poly_PRAD();
  pH_Position->SetStats(0);
  pH_Position->GetZaxis()->SetRangeUser(0.1,1.0E7);
  pH_Position->Draw("COLZ L");

/* 
  pH_Position = new TH2F("ClusterPosition","ClusterPosition;X;Y",28,0.0,28.0,69,0.0,69.0);
  pH_Position->SetStats(0);
  pH_Position->GetXaxis()->CenterLabels();
  pH_Position->GetXaxis()->CenterTitle();
  pH_Position->GetXaxis()->SetNdivisions(28, kFALSE);
  pH_Position->GetXaxis()->SetTickLength(1);
  for(int i=0;i<=27;i++) pH_Position->GetXaxis()->SetBinLabel(i+1,Form("%d",27-i));

  pH_Position->GetYaxis()->CenterLabels();
  pH_Position->GetYaxis()->CenterTitle();
  pH_Position->GetYaxis()->SetNdivisions(36, kFALSE);
  pH_Position->GetYaxis()->SetTickLength(1);
//  for(int i=1;i<=36;i++) pH_Position->GetYaxis()->SetBinLabel(i,Form("%d",i-1));
  pH_Position->GetZaxis()->SetLabelSize(0.03);
  pH_Position->SetBarOffset(0.10);
  pH_Position->SetBarWidth(0.10);
  pH_Position->SetTitle("PRAD Calorimeter Clusters");
  pH_Position->Draw("COLZ L");
*/

  // Cluster Energy
  pC->GetCanvas()->cd(2)->cd(1);
  pH_Energy = new TH1F("ClusterEnergy","ClusterEnergy;MeV;Hz",1024,0.0,16384.0);
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

  if(connect_to_server() < 0) DoExit();

  SetWindowName("PRAD VTP SCALERS");
  MapSubwindows();
  Resize();
  MapWindow();

  pTimerUpdate = new TTimer(this, SCALER_UPDATE_PERIOD, kTRUE);
  pTimerUpdate->Start(SCALER_UPDATE_PERIOD, kTRUE);
}

int main(int argc, char* argv[])
{
  int cargc = 1;
  TApplication App("PRAD VTP Scaler GUI", &cargc, argv);

  if(gROOT->IsBatch())
  {
    fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
    return 1;
  }

  prad_vtp_scalers_app *pprad_vtp_scalers_app = new prad_vtp_scalers_app(gClient->GetRoot(), 800, 800);
  App.Run();

  delete pprad_vtp_scalers_app;
  return 0;
}
