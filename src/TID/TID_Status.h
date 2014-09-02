#ifndef TID_Status_H
#define TID_Status_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "tid.h"

class TID_Status	: public TGCompositeFrame
{
 public:
  TID_Status(const TGWindow *p, ModuleFrame *pModule) 
    : TGCompositeFrame(p, 400, 400)
    {
      SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (TID_regs *)pM->BaseAddr;

      AddFrame(pFrameButtons = 
	       new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
      pFrameButtons->AddFrame(pButtonUpdate = 
			      new TGTextButton(pFrameButtons, 
					       new TGHotString("Update Display"), BTN_UPDATE), 
			      new TGLayoutHints(kLHintsCenterX));

      pFrameButtons->AddFrame(pButtonSWSync = 
			      new TGTextButton(pFrameButtons, new TGHotString("Sync"), 
					       BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX));

      AddFrame(pFrameText = 
	       new TGHorizontalFrame(this), 
	       new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

      pFrameText->AddFrame(pFrameLeft = 
			   new TGVerticalFrame(pFrameText), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameLeft->AddFrame(pTextViewRegs = 
			   new TGTextView(pFrameLeft), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

      pFrameText->AddFrame(pFrameRight = 
			   new TGVerticalFrame(pFrameText), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameRight->AddFrame(pTextViewStatus = 
			   new TGTextView(pFrameRight), 
			   new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      


      pButtonUpdate->Associate(this);
      pButtonSWSync->Associate(this);

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
		case BTN_SW_SYNC:
		  {
		    pM->WriteReg32(&pRegs->vmeSyncLoad, TID_SYNC_RESET);
		    break;
		  }
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

      pTextViewRegs->Clear();
      pTextViewRegs->AddLineFast("------ TID Registers ------");

      sprintf(buf, "%-20.20s = 0x%08lX","VME BaseAddress", (long)pRegs); pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, dataSetup);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, enableBits);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, intSetup);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigDelay);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, adr32);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, daqStatus);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, fiberLatencyMeasurement);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, fiberSyncAlignment);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, liveTimer);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyTimer);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, monitor);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, oport);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, GTPStatusA);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, GTPStatusB);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, triggerDataBufferLength);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, TSInputCounter);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, blockStatus[0]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, blockStatus[1]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, blockStatus[2]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, blockStatus[3]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, blockStatus[4]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, boardID);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigger_holdoff_read);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, reset);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, triggerCmdCode);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, softTrig);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, randomTrig);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, softTrig2);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigger_holdoff);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 0]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 1]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 2]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 3]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 4]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 5]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 6]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 7]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 8]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[ 9]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[10]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[11]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[12]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[13]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[14]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigTable[15]);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, vmeSyncLoad);  pTextViewRegs->AddLineFast(buf);
      SPFREG(buf, &pRegs, vmeSyncDelay);  pTextViewRegs->AddLineFast(buf);

      pTextViewRegs->Update();

      pTextViewStatus->Clear();

      UInt_t dataSetup, enableBits, intSetup,
	adr32, daqStatus, liveTimer, busyTimer, monitor;
      UInt_t oport, tsCounter;
      UInt_t blockStatus[5], iblock, nblocksReady, nblocksNeedAck;
      UInt_t ifiber, fibermask;
      UInt_t iinp, inpmask;
      int tidMaster=1;

      dataSetup    = pM->ReadReg32(&pRegs->dataSetup);
      enableBits   = pM->ReadReg32(&pRegs->enableBits);
      intSetup     = pM->ReadReg32(&pRegs->intSetup);

      adr32        = pM->ReadReg32(&pRegs->adr32);
      daqStatus    = pM->ReadReg32(&pRegs->daqStatus);
      liveTimer    = pM->ReadReg32(&pRegs->liveTimer);
      busyTimer    = pM->ReadReg32(&pRegs->busyTimer);
      monitor      = pM->ReadReg32(&pRegs->monitor);

      oport        = pM->ReadReg32(&pRegs->oport);
      tsCounter    = pM->ReadReg32(&pRegs->TSInputCounter);

      for(iblock=0;iblock<5;iblock++)
	blockStatus[iblock] = pM->ReadReg32(&pRegs->blockStatus[iblock]);

      sprintf(buf,"STATUS for TID at VME base address 0x%08lX",(long)pRegs);
      pTextViewStatus->AddLineFast(buf);
      sprintf(buf,"---------------------------------------------------");
      pTextViewStatus->AddLineFast(buf);

      sprintf(buf," A32 Data buffer");
      if(adr32&TID_ADR32_ENABLE)
	{
	  sprintf(buf,"%s ENABLED at",buf);
	  sprintf(buf,"%s VME base address 0x%08X",
		  buf,adr32&TID_ADR32_A32_BASE_MASK);
	}
      else
	sprintf(buf,"%s DISABLED",buf);
      pTextViewStatus->AddLineFast(buf);
      fibermask = enableBits & TID_ENABLEBITS_HFBR_MASK;
      if(fibermask)
	{
	  sprintf(buf," HFBR enabled (0x%x)= ",fibermask);
	  for(ifiber=0; ifiber<8; ifiber++)
	    {
	      if( fibermask & (1<<ifiber) ) 
		sprintf(buf,"%s %d",buf,ifiber+1);
	    }
	}
      else
	sprintf(buf," All HFBR Disabled");
      pTextViewStatus->AddLineFast(buf);
      
      sprintf(buf," Trigger input source =");
      pTextViewStatus->AddLineFast(buf);
      if(dataSetup & TID_DATASETUP_TRIGSRC_P0)
	{
	  sprintf(buf,"   P0 Input"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_HFBR1)
	{
	  sprintf(buf,"   HFBR #1 Input"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_LOOPBACK)
	{
	  sprintf(buf,"   TI Master Loopback"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_FPTRG)
	{
	  sprintf(buf,"   Front Panel TRG"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_VME)
	{
	  sprintf(buf,"   VME Command"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_TSINPUTS)
	{
	  sprintf(buf,"   Front Panel TS Inputs"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_TSrev2)
	{
	  sprintf(buf,"   Trigger Supervisor (rev2)"); pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_TRIGSRC_RND)
	{
	  sprintf(buf,"   Internal Pulser"); pTextViewStatus->AddLineFast(buf);
	}

      inpmask = (intSetup & TID_INTSETUP_GTPINPUT_MASK)>>16;
      if(inpmask)
	{
	  sprintf(buf," Front Panel TS Inputs Enabled: ");
	  for(iinp=0; iinp<6; iinp++)
	    {
	      if( inpmask & (1<<iinp)) 
		sprintf(buf,"%s %d",buf,iinp+1);
	    }
	}
      else
	{
	  sprintf(buf," All Front Panel TS Inputs Disabled");
	}
      pTextViewStatus->AddLineFast(buf);

      sprintf(buf," Clock source = ");
      pTextViewStatus->AddLineFast(buf);
      switch(intSetup & TID_INTSETUP_CLK_SOURCE_MASK)
	{
	case TID_INTSETUP_CLK_ONBOARD:
	  sprintf(buf,"   Onboard");
	  tidMaster=1;
	  break;
	case TID_INTSETUP_CLK_HFBR1:
	  sprintf(buf,"   HFBR #1 Input");
	  tidMaster=0;
	  break;
	case TID_INTSETUP_CLK_HFBR5:
	  sprintf(buf,"   HFBR #5 Input");
	  tidMaster=0;
	  break;
	case TID_INTSETUP_CLK_FP:
	  sprintf(buf,"   Front Panel Input");
	  tidMaster=1;
	  break;
	default:
	  sprintf(buf,"   INVALID!");
	}
      pTextViewStatus->AddLineFast(buf);

      sprintf(buf," Sync source = ");
      pTextViewStatus->AddLineFast(buf);
      if(dataSetup & TID_DATASETUP_SYNCSRC_P0)
	{
	  sprintf(buf,"   P0 Input");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_SYNCSRC_HFBR1)
	{
	  sprintf(buf,"   HFBR #1 Input");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_SYNCSRC_HFBR5)
	{
	  sprintf(buf,"   HFBR #5 Input");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_SYNCSRC_FP)
	{
	  sprintf(buf,"   Front Panel Input");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(dataSetup & TID_DATASETUP_SYNCSRC_LOOPBACK)
	{
	  sprintf(buf,"   TI Master Loopback");
	  pTextViewStatus->AddLineFast(buf);
	}

      sprintf(buf," BUSY source = ");
      pTextViewStatus->AddLineFast(buf);
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_SWA)
	{
	  sprintf(buf,"   Switch Slot A");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_SWB)
	{
	  sprintf(buf,"   Switch Slot B");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_VMEP2)
	{
	  sprintf(buf,"   P2 Input");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_TDC)
	{
	  sprintf(buf,"   Front Panel F1TDC Connection");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_ADC)
	{
	  sprintf(buf,"   Front Panel FADC250 Connection");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_FP)
	{
	  sprintf(buf,"   Front Panel");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_LOOPBACK)
	{
	  sprintf(buf,"   Loopback");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR1)
	{
	  sprintf(buf,"   HFBR #1");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR2)
	{
	  sprintf(buf,"   HFBR #2");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR3)
	{
	  sprintf(buf,"   HFBR #3");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR4)
	{
	  sprintf(buf,"   HFBR #4");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR5)
	{
	  sprintf(buf,"   HFBR #5");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR6)
	{
	  sprintf(buf,"   HFBR #6");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR7)
	{
	  sprintf(buf,"   HFBR #7");
	  pTextViewStatus->AddLineFast(buf);
	}
      if(enableBits & TID_ENABLEBITS_BUSY_ENABLE_HFBR8)
	{
	  sprintf(buf,"   HFBR #8");
	  pTextViewStatus->AddLineFast(buf);
	}

      sprintf(buf," Event Format = %d",(dataSetup&TID_DATASETUP_EVENTFORMAT_MASK)>>30);
	  pTextViewStatus->AddLineFast(buf);

      if(enableBits&TID_ENABLEBITS_IRQ_ENABLE)
	sprintf(buf," Interrupts ENABLED");
      else
	sprintf(buf," Interrupts DISABLED");
      pTextViewStatus->AddLineFast(buf);

      sprintf(buf,"   Level = %d   Vector = 0x%02x",
	     (intSetup&TID_INTSETUP_LEVEL_MASK)>>8, (intSetup&TID_INTSETUP_VEC_MASK));
      pTextViewStatus->AddLineFast(buf);
  
      if(adr32&TID_ADR32_ENABLE_BERR)
	{
	  sprintf(buf," Bus Errors Enabled");
	  pTextViewStatus->AddLineFast(buf);
	}

      sprintf(buf," Blocks ready for readout: %d",(daqStatus&TID_DAQSTATUS_BLOCKS_AVAILABLE_MASK)>>24);
      pTextViewStatus->AddLineFast(buf);

      if(tidMaster)
	{
	  /* TI slave block status */
	  fibermask = (enableBits);
	  for(ifiber=0; ifiber<8; ifiber++)
	    {
	      if( fibermask & (1<<ifiber) )
		{
		  if( (ifiber % 2) == 0)
		    {
		      nblocksReady   = blockStatus[ifiber/2] & TID_BLOCKSTATUS_NBLOCKS_READY0;
		      nblocksNeedAck = (blockStatus[ifiber/2] & TID_BLOCKSTATUS_NBLOCKS_NEEDACK0)>>8;
		    }
		  else
		    {
		      nblocksReady   = (blockStatus[(ifiber-1)/2] & TID_BLOCKSTATUS_NBLOCKS_READY1)>>16;
		      nblocksNeedAck = (blockStatus[(ifiber-1)/2] & TID_BLOCKSTATUS_NBLOCKS_NEEDACK1)>>24;
		    }
		  sprintf(buf,"  Fiber %d  :  Blocks ready / need acknowledge: %d / %d",
			 ifiber+1,nblocksReady, nblocksNeedAck);
		  pTextViewStatus->AddLineFast(buf);
		}
	    }

	  /* TI master block status */
	  nblocksReady   = (blockStatus[4] & TID_BLOCKSTATUS_NBLOCKS_READY1)>>16;
	  nblocksNeedAck = (blockStatus[4] & TID_BLOCKSTATUS_NBLOCKS_NEEDACK1)>>24;
	  sprintf(buf,"  Loopback :  Blocks ready / need acknowledge: %d / %d",
		 nblocksReady, nblocksNeedAck);
	  pTextViewStatus->AddLineFast(buf);

	  sprintf(buf," TI Master input counter %d",tsCounter);
	  pTextViewStatus->AddLineFast(buf);
	}

      pTextViewStatus->Update();
    }

 private:

	enum Buttons
	{
		BTN_RESET,
		BTN_SW_SYNC,
		BTN_UPDATE
	};
	 
	 ModuleFrame			*pM;
	TID_regs			*pRegs;

    TGHorizontalFrame   	*pFrameButtons;
    TGHorizontalFrame	        *pFrameText;

    TGVerticalFrame		*pFrameLeft;
    TGVerticalFrame		*pFrameRight;

    TGTextView			*pTextViewRegs;
    TGTextView			*pTextViewStatus;

    TGTextButton		*pButtonUpdate;
    TGTextButton		*pButtonSWSync;
};

#endif
