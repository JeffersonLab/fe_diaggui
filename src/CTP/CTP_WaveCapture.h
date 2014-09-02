#ifndef CTP_WaveCapture_H
#define CTP_WaveCapture_H

#include "RootHeader.h"

#define CTP_WAVE_NUM_POINTS		512


/* class GraphThresholdFrame	: public TGCompositeFrame */
/* { */
/*  public: */
/*   GraphThresholdFrame(const TGWindow *p, const char *pName, int index) : TGCompositeFrame(p, 400, 400) */
/*     { */
/*       SetLayoutManager(new TGVerticalLayout(this)); */

/*       pCanvas = new TRootEmbeddedCanvas(pName, this, 100, 100); */
/*       AddFrame(pCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY)); */

/*       pFrameButtons = new TGHorizontalFrame(this); */
/*       pLabelThreshold = new TGLabel(pFrameButtons, new TGString("Trig Threshold >= ")); */
/*       pNumberThreshold = new TGNumberEntry(pFrameButtons, 0, 6, -1, TGNumberFormat::kNESInteger); */
/*       pNumberThreshold->SetWidth(80); */
/*       pButtonCloneGraph = new TGTextButton(pFrameButtons, new TGHotString("Copy"), BTN_GRAPH_CLONE); */

/*       pFrameButtons->AddFrame(pLabelThreshold, new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0)); */
/*       pFrameButtons->AddFrame(pNumberThreshold, new TGLayoutHints(kLHintsLeft)); */
/*       pFrameButtons->AddFrame(pButtonCloneGraph, new TGLayoutHints(kLHintsLeft)); */

/*       pButtonCloneGraph->Associate(this); */
/*       AddFrame(pFrameButtons, new TGLayoutHints(kLHintsExpandX)); */

/*       pCanvas->GetCanvas()->SetBorderMode(0); */

/*       pGraph =  new TGraph(CTP_WAVE_NUM_POINTS); */
/*       pGraph->SetTitle(pName); */
/*       pGraph->SetMarkerStyle(20); */
/*       pGraph->SetLineColor(4); */
/*       pGraph->GetXaxis()->SetRangeUser(0, CTP_WAVE_NUM_POINTS-1); */
/*       pGraph->GetYaxis()->SetRangeUser(0, 1.0); */

/*       for(int i = 0; i < CTP_WAVE_NUM_POINTS; i++) */
/* 	pGraph->SetPoint(i, i*4.0, 0); */

/*       DrawGraph(); */
/*     } */

/*     virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t) */
/*     { */
/*       switch(GET_MSG(msg)) */
/* 	{ */
/* 	case kC_COMMAND: */
/* 	  switch(GET_SUBMSG(msg)) */
/* 	    { */
/* 	    case kCM_BUTTON: */
/* 	      switch(parm1) */
/* 		{ */
/* 		case BTN_GRAPH_CLONE: */
/* 		  pCanvas->GetCanvas()->DrawClone(); */
/* 		  break; */
/* 		default: */
/* 		  printf("button id %d pressed\n", (int)parm1); */
/* 		  break; */
/* 		} */
/* 	    } */
/* 	  break; */
/* 	default: */
/* 	  break; */
/* 	} */
/*       return kTRUE; */
/*     } */

/*     void DrawGraph() */
/*     { */
/*       pCanvas->GetCanvas()->SetLeftMargin(0.20); */
/*       pGraph->GetXaxis()->SetTitle("Time(ns)"); */
/*       pGraph->GetXaxis()->SetRangeUser(0.0, (CTP_WAVE_NUM_POINTS-1.0)*4.0); */
/*       pGraph->GetYaxis()->SetTitle("FADC Sum(DAC code)"); */
/*       pGraph->GetYaxis()->SetTitleOffset(1.75); */
/*       pGraph->GetYaxis()->CenterTitle(); */

/*       pCanvas->GetCanvas()->cd(); */
/*       pCanvas->GetCanvas()->Clear(); */
/*       pGraph->Draw("alp"); */
/*       pCanvas->GetCanvas()->Modified(); */
/*       pCanvas->GetCanvas()->Update(); */
/*     } */

/*     TGHorizontalFrame	*pFrameButtons; */

/*     TRootEmbeddedCanvas	*pCanvas; */
/*     TGraph		*pGraph; */
/*     TGNumberEntry	*pNumberThreshold; */
/*     TGLabel		*pLabelThreshold; */
/*     TGTextButton	*pButtonCloneGraph; */
/* }; */

class CTP_WaveCapture	: public TGCompositeFrame
{
 public:
  CTP_WaveCapture(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr) 
    : TGCompositeFrame(p, 400, 400)
    {
      SetLayoutManager(new TGVerticalLayout(this));

      pVMEClient = pClient;
      pCTPregs = (CTP_regs *)baseAddr;

      AddFrame(pFrameButtons = new TGHorizontalFrame(this), 
	       new TGLayoutHints(kLHintsExpandX | kLHintsTop));
      pFrameButtons->AddFrame(pButtonAutoTrigger = 
			      new TGTextButton(pFrameButtons, 
					       new TGHotString("Update Mode: Manual"), 
					       BTN_WAVE_AUTOTRIG), 
			      new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
      pButtonAutoTrigger->SetWidth(80);
      pButtonAutoTrigger->SetEnabled(kTRUE);
      pButtonAutoTrigger->AllowStayDown(kTRUE);
      pFrameButtons->AddFrame(pButtonStartTrigger = 
			      new TGTextButton(pFrameButtons, 
					       new TGHotString("Start Trigger"), 
					       BTN_WAVE_STARTTRIG), 
			      new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
      pFrameButtons->AddFrame(pButtonStopTrigger = 
			      new TGTextButton(pFrameButtons, 
					       new TGHotString("Stop Trigger"), 
					       BTN_WAVE_STOPTRIG), 
			      new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
      pButtonStopTrigger->SetEnabled(kFALSE);
      pFrameButtons->AddFrame(pButtonForceTrigger = 
			      new TGTextButton(pFrameButtons, 
					       new TGHotString("Force Trigger"), 
					       BTN_WAVE_FORCETRIG), 
			      new TGLayoutHints(kLHintsCenterY | kLHintsLeft));		

      AddFrame(pFrameGraphs = 
	       new TGHorizontalFrame(this), 
	       new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameGraphs->AddFrame(pGraphs = 
			     new GraphThresholdFrame(pFrameGraphs, 
						     "Channel 0 Capture", 0), 
			     new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		
      pTimerUpdate = new TTimer(this, 100, kTRUE);

      pButtonAutoTrigger->Associate(this);
      pButtonStartTrigger->Associate(this);
      pButtonStopTrigger->Associate(this);
      pButtonForceTrigger->Associate(this);

      DrawGraph();
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
		case BTN_WAVE_AUTOTRIG:
		  if(pButtonAutoTrigger->IsDown())
		    pButtonAutoTrigger->SetText(new TGHotString("Update Mode: Auto"));
		  else
		    pButtonAutoTrigger->SetText(new TGHotString("Update Mode: Manual"));
		  break;
		case BTN_WAVE_STARTTRIG:
		  pButtonStartTrigger->SetEnabled(kFALSE);
		  pButtonStopTrigger->SetEnabled(kTRUE);
		  SetCTPWaveTrigger();
		  pTimerUpdate->Start(100, kTRUE);
		  break;
		case BTN_WAVE_STOPTRIG:
		  pButtonStartTrigger->SetEnabled(kTRUE);
		  pButtonStopTrigger->SetEnabled(kFALSE);
		  pTimerUpdate->TurnOff();
		  break;
		case BTN_WAVE_FORCETRIG:
		  pButtonForceTrigger->SetEnabled(kFALSE);
		  SetCTPWaveTrigger(kTRUE);
		  UpdateCTPWaveCaptures();
		  break;
		default:
		  printf("button id %d pressed\n", (int)parm1);
		  break;
		}
	    }
	  break;
	default:
	  break;
	}
      return kTRUE;
    }

    virtual Bool_t HandleTimer(TTimer *t)
    {
      if(pTimerUpdate->HasTimedOut())
	{
	  unsigned int historyReady;
	  /* Check for Ready bit */
	  pVMEClient->ReadVME32((unsigned int)&pCTPregs->fpga3.status1, &historyReady);

	  if(historyReady & (1<<2))
	    {
	      UpdateCTPWaveCaptures();
	      if(pButtonAutoTrigger->IsDown())
		{
		  SetCTPWaveTrigger();
		  pTimerUpdate->Start(100, kTRUE);
		}
	      else
		{
		  pButtonStartTrigger->SetEnabled(kTRUE);
		  pButtonStopTrigger->SetEnabled(kFALSE);
		}
	    }
	  else
	    pTimerUpdate->Start(100, kTRUE);
	}
      return kTRUE;
    }

    void SetCTPWaveTrigger(Bool_t force = kFALSE)
    {
      /* Write new threshold */
      if(force)
	{
	  pVMEClient->WriteVME32((unsigned int)&pCTPregs->sum_threshold_lsb, 0);
	  pVMEClient->WriteVME32((unsigned int)&pCTPregs->sum_threshold_msb, 0);
	}
      else
	{
	  Int_t threshold = pGraphs->pNumberThreshold->GetIntNumber();
	  pVMEClient->WriteVME32((unsigned int)&pCTPregs->sum_threshold_lsb, 
				 threshold&0xFFFF);
	  pVMEClient->WriteVME32((unsigned int)&pCTPregs->sum_threshold_msb, 
				 (threshold&0xFFFF)>>16);
	}

      /* Arm history buffer */
      pVMEClient->WriteVME32((unsigned int)&pCTPregs->fpga3.config1, 0x1);
      pVMEClient->WriteVME32((unsigned int)&pCTPregs->fpga3.config1, 0x0);
    }

    void UpdateCTPWaveCaptures()
    {
      unsigned int waveCaptures[CTP_WAVE_NUM_POINTS];

      UInt_t data_lsb=0, data_msb;
      for(int i=0; i< CTP_WAVE_NUM_POINTS; i++)
	{
	  pVMEClient->ReadVME32((unsigned int)pCTPregs->history_buffer_lsb,
				&data_lsb);
	  pVMEClient->ReadVME32((unsigned int)pCTPregs->history_buffer_msb,
				&data_msb);
	  waveCaptures[i] = (data_lsb & 0xffff) | ( (data_msb & 0xffff)<<16);
	}

      unsigned int min = waveCaptures[0], max = waveCaptures[0];
      for(int i = 0; i < CTP_WAVE_NUM_POINTS; i++)
	{
	  if(waveCaptures[i] < min)
	    min = waveCaptures[i];
	  if(waveCaptures[i] > max)
	    max = waveCaptures[i];
	  pGraphs->pGraph->SetPoint(i, i*4.0, (double)waveCaptures[i]);

	}
      pGraphs->pGraph->GetYaxis()->SetRangeUser((double)min, (double)max);

      DrawGraph();
      pButtonForceTrigger->SetEnabled(kTRUE);
    }

    void DrawGraph()
    {
	pGraphs->DrawGraph();
    }

 private:

	enum Buttons
	{
		BTN_WAVE_AUTOTRIG,
		BTN_WAVE_STARTTRIG,
		BTN_WAVE_STOPTRIG,
		BTN_WAVE_FORCETRIG,
		BTN_GRAPH_CLONE
	};

	 VMERemote			*pVMEClient;
    CTP_regs			*pCTPregs;

    TTimer			*pTimerUpdate;

    GraphThresholdFrame	*pGraphs;

    // Top Frame Objects: pFrameButtons
    TGTextButton		*pButtonAutoTrigger;
    TGTextButton		*pButtonStartTrigger;
    TGTextButton		*pButtonStopTrigger;
    TGTextButton		*pButtonForceTrigger;

    TGHorizontalFrame	*pFrameButtons;
    TGHorizontalFrame	*pFrameGraphs;
};

#endif
