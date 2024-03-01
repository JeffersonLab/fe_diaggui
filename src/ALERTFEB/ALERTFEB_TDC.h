#ifndef ALERTFEB_TDC_H
#define ALERTFEB_TDC_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_Regs.h"

#define ALERTFEB_TDC_POLL_RATE        20

class ALERTFEB_TDC  : public TGCompositeFrame
{
public:
  ALERTFEB_TDC(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
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
      pTF1->AddFrame(pButtonContinuous = new TGTextButton(pTF1, "Cotinuous", BTN_ALERTFEB_CONTINUOUS), new TGLayoutHints(kLHintsCenterX));
        pButtonContinuous->SetWidth(200);
        pButtonContinuous->AllowStayDown(kTRUE);
        pButtonContinuous->Associate(this);
      pTF1->AddFrame(pB = new TGTextButton(pTF1, "Init", BTN_ALERTFEB_INIT), new TGLayoutHints(kLHintsCenterX));
        pB->SetWidth(200);
        pB->Associate(this);
      pTF1->AddFrame(pButtonEnCalPulser = new TGTextButton(pTF1, "EnCalPulser", BTN_ALERTFEB_ENCALPULSER), new TGLayoutHints(kLHintsCenterX));
        pButtonEnCalPulser->SetWidth(200);
        pButtonEnCalPulser->AllowStayDown(kTRUE);
        pButtonEnCalPulser->Associate(this);

			pTF1->AddFrame(pComboDisplayedChannels = new TGComboBox(pTF1, COM_TDCDISPLAYCHANNELS));
				for(int i = 0; i < 13; i++)
					pComboDisplayedChannels->AddEntry(Form("INL Channels %d-%d", i*4,i*4+3), 0+i);
				for(int i = 0; i < 13; i++)
					pComboDisplayedChannels->AddEntry(Form("Transfer Channels %d-%d", i*4,i*4+3), 13+i);
				for(int i = 0; i < 13; i++)
					pComboDisplayedChannels->AddEntry(Form("Width Channels %d-%d", i*4,i*4+3), 26+i);
				pComboDisplayedChannels->Select(0);
				pComboDisplayedChannels->SetWidth(150);
				pComboDisplayedChannels->SetHeight(20);
				pComboDisplayedChannels->Associate(this);


		AddFrame(pCanvasHisto = new TRootEmbeddedCanvas("TDC Plots", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasHisto->GetCanvas()->SetBorderMode(0);
			pCanvasHisto->GetCanvas()->Divide(2, 2);
      for(int i=0;i<52;i++)
      {
        pTH_DNL[i] = new TH1I(Form("Ch%d DNL", i), Form("Ch%d DNL;TDC Bin;Bin Width(ps)", i), 128, 0.0, 128.0);
        pTH_DNL[i]->SetStats(kFALSE);
        pTH_DNL[i]->SetLineColor(kBlack);
        pTH_DNL[i]->SetFillColor(kBlue);

        pTH_Transfer[i] = new TH1I(Form("Ch%d TDC Transfer Function", i),Form("Ch%d TDC Transfer Function;bin;time(ps)", i), 128, 0.0, 128.0);
        pTH_Transfer[i]->SetStats(kFALSE);
        pTH_Transfer[i]->SetLineColor(kBlack);

        pTH_BinWidths[i] = new TH1I(Form("Ch%d Bin Width", i), Form("Ch%d TDC Bin Width;TDC Bin Width(ps);Count", i), 128, 0.0, 128.0);
        pTH_BinWidths[i]->SetStats(kFALSE);
        pTH_BinWidths[i]->SetLineColor(kBlack);
        pTH_BinWidths[i]->SetFillColor(kBlue);
     }

		DrawPlots();
		UpdatePlots();

    pTimerUpdate = new TTimer(this, ALERTFEB_TDC_POLL_RATE, kTRUE);
  }

	void DrawPlots()
	{
		int offset = pComboDisplayedChannels->GetSelected();
		for(int i = 0; i < 4; i++)
		{
			pCanvasHisto->GetCanvas()->cd(i+1);
			pCanvasHisto->GetCanvas()->GetPad(i+1)->Clear();
      if(offset<13)      pTH_DNL[(offset-0)*4+i]->Draw("bar0");
      else if(offset<26) pTH_Transfer[(offset-13)*4+i]->Draw("p");
      else               pTH_BinWidths[(offset-26)*4+i]->Draw("bar");
		}
	}

	void UpdatePlots()
	{
		pCanvasHisto->GetCanvas()->Modified();
		pCanvasHisto->GetCanvas()->Update();
	}

  void ReadTdcTables()
  {
    unsigned int val, bins[52][128], bins_raw[52][128];
    unsigned int bin_totals[52];

    for(int ch=0; ch<52; ch++)
    {
      bin_totals[ch] = 0;
      for(int bin=0; bin<128; bin++)
      {
        unsigned int addr = ch*128+bin;
        pM->WriteReg32(&pRegs->Tdc.CAL_Ctrl, addr | 0x80000000);
        val = pM->ReadReg32(&pRegs->Tdc.CAL_Status);
        bins[ch][bin] = val & 0x7F;
        bins_raw[ch][bin] = (val>>7);
        bin_totals[ch]+= (val>>7);
      }

      pTH_DNL[ch]->Reset();;
      pTH_Transfer[ch]->Reset();
      pTH_BinWidths[ch]->Reset();
      
      double bin_width;
      for(int bin=0; bin<128; bin++)
      {
        bin_width = 2000.0 * (double)bins_raw[ch][bin] / (double)bin_totals[ch];
        pTH_DNL[ch]->SetBinContent(bin+1, bin_width);
        pTH_Transfer[ch]->SetBinContent(bin+1, 15625 * bins[ch][bin] / 1000);
        pTH_BinWidths[ch]->Fill(bin_width);
      }
    } 
    DrawPlots();
    UpdatePlots();
  }

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
      ReadTdcTables();
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
            case BTN_ALERTFEB_INIT:
              pM->WriteReg32(&pRegs->Tdc.NumEntriesMin, 100000);
              pM->WriteReg32(&pRegs->Tdc.Ctrl, 0x6);
              break;

            case BTN_ALERTFEB_READ:
              ReadTdcTables();
              if(pButtonContinuous->IsDown())
			          pTimerUpdate->Start(ALERTFEB_TDC_POLL_RATE, kTRUE);
              else
				        pTimerUpdate->Stop();
              break;

            case BTN_ALERTFEB_ENCALPULSER:
            {
              int val = pM->ReadReg32(&pRegs->Tdc.Ctrl);
              if(pButtonEnCalPulser->IsDown()) val|= 0x00000004;
              else                             val&= 0xFFFFFFFB;
              pM->WriteReg32(&pRegs->Tdc.Ctrl, val);
              break;
            }

            default:
              printf("button id %d pressed\n", (int)parm1);
              break;
          }
          break;
        case kCM_COMBOBOX:
          switch(parm1)
          {
            case COM_TDCDISPLAYCHANNELS:
              DrawPlots();
              UpdatePlots();
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
    BTN_ALERTFEB_READ=0,
    BTN_ALERTFEB_ENCALPULSER=1,
    BTN_ALERTFEB_INIT=2,
    BTN_ALERTFEB_CONTINUOUS=3,

    COM_TDCDISPLAYCHANNELS=0
  };
  
  ALERTFEB_Regs       *pRegs;

  TGTextButton        *pButtonEnCalPulser;
  TGTextButton        *pButtonContinuous;

  TGComboBox          *pComboDisplayedChannels;

  ModuleFrame         *pM;

  TTimer              *pTimerUpdate;

  TRootEmbeddedCanvas *pCanvasHisto;

  TH1I                *pTH_Transfer[52];
  TH1I                *pTH_DNL[52];
  TH1I                *pTH_BinWidths[52];
};

#endif
