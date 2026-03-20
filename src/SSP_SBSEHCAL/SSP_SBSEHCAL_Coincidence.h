#ifndef SSP_SBSEHCAL_COINCIDENCE_H
#define SSP_SBSEHCAL_COINCIDENCE_H

#include "RootHeader.h"
#include "ModuleFrame.h"

class SSP_SBSEHCAL_Coincidence : public TGCompositeFrame
{
public:
  SSP_SBSEHCAL_Coincidence(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    TGCompositeFrame *pTF1;

    SetLayoutManager(new TGVerticalLayout(this));

    pM = pModule;

    AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
      pTF1->AddFrame(pButtonRead = new TGTextButton(pTF1, new TGHotString("Read"), BTN_READ), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
       pButtonRead->Associate(this);

    AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", this, 1300, 2300), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    gStyle->SetPalette(1, NULL);

    pCanvas->GetCanvas()->cd(1);
    pHistCoincidence = new TH1I("Coincidence", "Coincidence;;Count", 129, -256, 256);
    pHistCoincidence->SetLineColor(kBlack);
    pHistCoincidence->SetFillColor(kBlue);
    pHistCoincidence->SetNdivisions(129);
    pHistCoincidence->SetStats(0);
    pHistCoincidence->Draw("HIST BAR");
  }

  void ReadScalers()
  {
    volatile unsigned int *ctrl = (volatile unsigned int *)((int)pM->BaseAddr+0x7000);
    volatile unsigned int *stat = (volatile unsigned int *)((int)pM->BaseAddr+0x7004);

    pCanvas->GetCanvas()->cd(1);
    pHistCoincidence->Reset();

    for(int i=-64;i<=64;i++)
    {
      pM->WriteReg32(ctrl, 0x80000000 | ((i<<23)&0x7F800000) | (4<<3) | (3<<0));
      unsigned int w = pM->ReadReg32(stat);
      printf("i=%d,w=%d\n", i,w);
      pHistCoincidence->Fill(i*4,w);
    }
    pM->WriteReg32(ctrl, (4<<3) | (3<<0));

    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
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
              case BTN_READ:
		ReadScalers();
                break;
              default:
                printf("button id %d pressed\n", (int)parm1);
                break;
            }
            break;
	}
    }
    return kTRUE;
  }

private:
  enum Buttons
  {
    BTN_READ = 1002
  };

  ModuleFrame *pM;
  TH1I *pHistCoincidence;
  TRootEmbeddedCanvas *pCanvas;
  TGTextButton *pButtonRead;
};

#endif


