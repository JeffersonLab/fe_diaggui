#ifndef ALERTFEB_SCALERS_H
#define ALERTFEB_SCALERS_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_Regs.h"

#define ALERTFEB_SCALER_POLL_RATE 1000

class ALERTFEB_SCALERS  : public TGCompositeFrame
{
public:
  ALERTFEB_SCALERS(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    pM = pModule;
    pRegs = (ALERTFEB_Regs *)pM->BaseAddr;

    TGCompositeFrame *pTF1;
    TGTextButton *pB;

    AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
      pTF1->AddFrame(pB = new TGTextButton(pTF1, "Read", BTN_ALERTFEB_READ), new TGLayoutHints(kLHintsCenterX));
        pB->SetWidth(200);
        pB->Associate(this);
      pTF1->AddFrame(pButtonContinuous = new TGTextButton(pTF1, "Continuous", BTN_ALERTFEB_CONTINUOUS), new TGLayoutHints(kLHintsCenterX));
        pButtonContinuous->SetWidth(200);
        pButtonContinuous->AllowStayDown(kTRUE);
        pButtonContinuous->Associate(this);

		AddFrame(pCanvasHisto = new TRootEmbeddedCanvas("TDC Scalers", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasHisto->GetCanvas()->SetBorderMode(0);
      pTH_Scalers = new TH1I("TDC Scalers", "TDC Scalers;Channel;Count", 52, 0.0, 52.0);
      pTH_Scalers->SetStats(kFALSE);
      pTH_Scalers->SetLineColor(kBlack);
      pTH_Scalers->SetFillColor(kBlue);

		DrawPlots();
		UpdatePlots();

    pTimerUpdate = new TTimer(this, ALERTFEB_SCALER_POLL_RATE, kTRUE);
  }

	void DrawPlots()
	{
    pCanvasHisto->GetCanvas()->cd();
    pCanvasHisto->GetCanvas()->Clear();
    pTH_Scalers->Draw("bar0");
	}

	void UpdatePlots()
	{
		pCanvasHisto->GetCanvas()->Modified();
		pCanvasHisto->GetCanvas()->Update();
	}

  void ReadScalers()
  {
    unsigned int val;

    pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x1);
    pTH_Scalers->Reset();
    for(int ch=0; ch<52; ch++)
    {
      val = pM->ReadReg32(&pRegs->Tdc.Scalers[ch]);
      pTH_Scalers->SetBinContent(ch+1, val);
    }
    pM->WriteReg32(&pRegs->Sd.ScalerLatch, 0x0);
    DrawPlots();
    UpdatePlots();
  }

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
      ReadScalers();
      if(pButtonContinuous->IsDown())
				pTimerUpdate->Start(ALERTFEB_TDC_POLL_RATE, kTRUE);
      else
				pTimerUpdate->Stop();
		}
		return kTRUE;
	}

  virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
  {
    switch(GET_MSG(msg))
    {
    case kC_USER:
      switch(GET_SUBMSG(msg))
      {
      }
      break;

    case kC_COMMAND:
      switch(GET_SUBMSG(msg))
      {
        case kCM_BUTTON:
          switch(parm1)
          {
            case BTN_ALERTFEB_READ:
              ReadScalers();
              if(pButtonContinuous->IsDown())
			          pTimerUpdate->Start(ALERTFEB_SCALER_POLL_RATE, kTRUE);
              else
				        pTimerUpdate->Stop();
              break;

            default:
              printf("button id %d pressed\n", (int)parm1);
              break;
          }
          break;
      }
      break;
    }
    return kTRUE;
  }
private:
  enum GUI_IDs
  {
    BTN_ALERTFEB_READ,
    BTN_ALERTFEB_CONTINUOUS
  };

  ALERTFEB_Regs       *pRegs;

  TGTextButton        *pButtonContinuous;

  ModuleFrame         *pM;

  TTimer              *pTimerUpdate;

  TRootEmbeddedCanvas *pCanvasHisto;

  TH1I                *pTH_Scalers;
};

#endif
