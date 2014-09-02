#ifndef CTP_Status_H
#define CTP_Status_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ctp.h"

class CTP_Status	: public TGCompositeFrame
{
public:
	
	CTP_Status(const TGWindow *p, ModuleFrame *pModule)
//CTP_Status(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr) 
    : TGCompositeFrame(p, 400, 400)
    {
      SetLayoutManager(new TGVerticalLayout(this));
		
		pM = pModule;
		pRegs = (CTP_regs *)pM->BaseAddr;

      AddFrame(pFrameButtons = 
	       new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
      pFrameButtons->AddFrame(pButtonUpdate = 
			      new TGTextButton(pFrameButtons, 
					       new TGHotString("Update Display"), BTN_UPDATE), 
			      new TGLayoutHints(kLHintsCenterX));

/*       pFrameButtons->AddFrame(pButtonReset =  */
/* 			      new TGTextButton(pFrameButtons, new TGHotString("Reset"),  */
/* 					       BTN_RESET), new TGLayoutHints(kLHintsCenterX)); */
/*       pFrameButtons->AddFrame(pButtonSWSync =  */
/* 			      new TGTextButton(pFrameButtons, new TGHotString("Sync"),  */
/* 					       BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX)); */

      AddFrame(pFrameText = 
	       new TGHorizontalFrame(this), 
	       new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameText->AddFrame(pFrameLeft = 
			   new TGVerticalFrame(pFrameText), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameLeft->AddFrame(pTextViewFPGA1 = 
			   new TGTextView(pFrameLeft), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameLeft->AddFrame(pTextViewFPGA2 = 
			   new TGTextView(pFrameLeft), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

      pFrameText->AddFrame(pFrameRight =
			   new TGVerticalFrame(pFrameText),
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameRight->AddFrame(pTextViewFPGA3 =
			    new TGTextView(pFrameRight),
			    new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
/*       pFrameRight->AddFrame(pTextViewFiberFPGA2 =  */
/* 			    new TGTextView(pFrameRight),  */
/* 			    new TGLayoutHints(kLHintsExpandX | kLHintsExpandY)); */

      pButtonUpdate->Associate(this);
/*       pButtonReset->Associate(this); */
/*       pButtonSWSync->Associate(this); */

      UpdateTextView();
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
		case BTN_UPDATE:
		  UpdateTextView();
		  break;
/* 		case BTN_RESET: */
/* 		  { */
/* 		    unsigned int r = ReadReg32(&pSSPregs->Config); */
/* 		    pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r | CFG_RESET); */
/* 		    pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r); */
/* 		    break; */
/* 		  } */
/* 		case BTN_SW_SYNC: */
/* 		  { */
/* 		    unsigned int r = ReadReg32(&pSSPregs->Config); */
/* 		    pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r | CFG_SYNC_SW); */
/* 		    pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r); */
/* 		    break; */
/* 		  } */
		default:
		  printf("button id %d pressed\n", (int)parm1);
		  break;
		}
	    }
	  break;
		}
      return kTRUE;
    }

	void UpdateTextView()
	{
		char buf[100];
		unsigned int reg, mask;

		pTextViewFPGA1->Clear();
		pTextViewFPGA1->AddLineFast("------ CTP FPGA1 Status ------");

		sprintf(buf, "%-20.20s = 0x%08lX", "VME BaseAddress",(long)pRegs); pTextViewFPGA1->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga1.status0); pTextViewFPGA1->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga1.status0)>>12;
		mask = reg>>0 & 1;  sprintf(buf,"  PP7  Channel Up       = %d",mask); pTextViewFPGA1->AddLineFast(buf);
		mask = reg>>1 & 1;  sprintf(buf,"  PP9  Channel Up       = %d",mask); pTextViewFPGA1->AddLineFast(buf);
		mask = reg>>2 & 1;  sprintf(buf,"  PP11 Channel Up       = %d",mask); pTextViewFPGA1->AddLineFast(buf);
		mask = reg>>3 & 1;  sprintf(buf,"  PP13 Channel Up       = %d",mask); pTextViewFPGA1->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga2.status1);
		mask = reg>>0 & 1;  sprintf(buf,"  PP15 Channel Up       = %d",mask); pTextViewFPGA1->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga1.status1); pTextViewFPGA1->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga1.config0); pTextViewFPGA1->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga1.config1); pTextViewFPGA1->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga1.temp); pTextViewFPGA1->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga1.vint); pTextViewFPGA1->AddLineFast(buf);

		pTextViewFPGA1->Update();

		pTextViewFPGA2->Clear();
		pTextViewFPGA2->AddLineFast("------ CTP FPGA2 Status ------");

		SPFREG(buf,&pRegs,fpga2.status0); pTextViewFPGA2->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga2.status0)>>12;
		mask = reg>>0 & 1;  sprintf(buf,"  PP8  Channel Up       = %d",mask); pTextViewFPGA2->AddLineFast(buf);
		mask = reg>>1 & 1;  sprintf(buf,"  PP10 Channel Up       = %d",mask); pTextViewFPGA2->AddLineFast(buf);
		mask = reg>>2 & 1;  sprintf(buf,"  PP12 Channel Up       = %d",mask); pTextViewFPGA2->AddLineFast(buf);
		mask = reg>>3 & 1;  sprintf(buf,"  PP14 Channel Up       = %d",mask); pTextViewFPGA2->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga2.status1);
		mask = reg>>0 & 1;  sprintf(buf,"  PP16 Channel Up       = %d",mask); pTextViewFPGA2->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga2.status1); pTextViewFPGA2->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga2.config0); pTextViewFPGA2->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga2.config1); pTextViewFPGA2->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga2.temp); pTextViewFPGA2->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga2.vint); pTextViewFPGA2->AddLineFast(buf);

		pTextViewFPGA2->Update();

		pTextViewFPGA3->Clear();
		pTextViewFPGA3->AddLineFast("------ CTP FPGA3 Status ------");

		SPFREG(buf,&pRegs,fpga3.status0); pTextViewFPGA3->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga3.status0)>>12;
		mask = reg>>1 & 1; sprintf(buf,"  PP1  Channel Up       = %d",mask); pTextViewFPGA3->AddLineFast(buf);
		mask = reg>>3 & 1; sprintf(buf,"  PP2  Channel Up       = %d",mask); pTextViewFPGA3->AddLineFast(buf);
		mask = reg>>0 & 1; sprintf(buf,"  PP3  Channel Up       = %d",mask); pTextViewFPGA3->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga3.status1);
		mask = reg>>0 & 1; sprintf(buf,"  PP4  Channel Up       = %d",mask); pTextViewFPGA3->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga3.status0)>>12;
		mask = reg>>2 & 1; sprintf(buf,"  PP5  Channel Up       = %d",mask); pTextViewFPGA3->AddLineFast(buf);
		reg = pM->ReadReg32(&pRegs->fpga3.status1);
		mask = reg>>2 & 1; sprintf(buf,"  PP6  Channel Up       = %d",mask); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga3.status1); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga3.config0); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga3.config1); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga3.temp); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,fpga3.vint); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,sum_threshold_lsb); pTextViewFPGA3->AddLineFast(buf);
		SPFREG(buf,&pRegs,sum_threshold_msb); pTextViewFPGA3->AddLineFast(buf);

		pTextViewFPGA3->Update();
	}

 private:

	enum Buttons
	{
		BTN_RESET,
		BTN_SW_SYNC,
		BTN_UPDATE
	};
	 
	ModuleFrame		*pM;
	CTP_regs			*pRegs;

    TGHorizontalFrame    	*pFrameButtons;
    TGHorizontalFrame   	*pFrameText;

    TGVerticalFrame		*pFrameLeft;
    TGVerticalFrame		*pFrameRight;

    TGTextView			*pTextViewFPGA1;
    TGTextView			*pTextViewFPGA2;
    TGTextView			*pTextViewFPGA3;

    TGTextButton		*pButtonUpdate;
/*     TGTextButton		*pButtonReset; */
/*     TGTextButton		*pButtonSWSync; */
};

#endif
