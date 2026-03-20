#ifndef FADC250_Status_H
#define FADC250_Status_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "fadc.h"

class FADC250_Status  : public TGCompositeFrame
{
 public:
  FADC250_Status(const TGWindow *p, ModuleFrame *pModule) 
    : TGCompositeFrame(p, 400, 400)
    {
      SetLayoutManager(new TGVerticalLayout(this));

      pM = pModule;
      pRegs = (fadc_struct *)pM->BaseAddr;

      TGTextButton *pB;
      AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
        pFrameButtons->AddFrame(pB = new TGTextButton(pFrameButtons, new TGHotString("Update Display"), BTN_UPDATE));
          pB->Associate(this);
        pFrameButtons->AddFrame(pB = new TGTextButton(pFrameButtons, new TGHotString("Init"), BTN_INIT));
          pB->Associate(this);

/*       pFrameButtons->AddFrame(pButtonReset =  */
/*            new TGTextButton(pFrameButtons, new TGHotString("Reset"),  */
/*                 BTN_RESET), new TGLayoutHints(kLHintsCenterX)); */
/*       pFrameButtons->AddFrame(pButtonSWSync =  */
/*            new TGTextButton(pFrameButtons, new TGHotString("Sync"),  */
/*                 BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX)); */

      AddFrame(pFrameText = 
         new TGHorizontalFrame(this), 
         new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameText->AddFrame(pFrameLeft = 
         new TGVerticalFrame(pFrameText), 
         new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameLeft->AddFrame(pTextViewMain = 
         new TGTextView(pFrameLeft), 
         new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      pFrameText->AddFrame(pFrameRight =
         new TGVerticalFrame(pFrameText),
         new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
/*       pFrameRight->AddFrame(pTextViewFiberFPGA1 =  */
/*          new TGTextView(pFrameRight),  */
/*          new TGLayoutHints(kLHintsExpandX | kLHintsExpandY)); */
/*       pFrameRight->AddFrame(pTextViewFiberFPGA2 =  */
/*          new TGTextView(pFrameRight),  */
/*          new TGLayoutHints(kLHintsExpandX | kLHintsExpandY)); */

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
                case BTN_INIT:
                  Init();
                  break;
                default:
                  printf("button id %d pressed\n", (int)parm1);
                  break;
              }
          }
          break;
      }
      return kTRUE;
    }

    void Init()
    {
      pM->WriteReg32(&pRegs->csr,      0x80000000);
      usleep(100000);
      pM->WriteReg32(&pRegs->reset,    0x0000FFFF);
      usleep(100000);
      pM->WriteReg32(&pRegs->ctrl1,    0x00100332);
      usleep(100000);
      pM->WriteReg32(&pRegs->ctrl2,    0x00000007);
//      usleep(100000);
//      pM->WriteReg32(&pRegs->mgt_ctrl, 0x00000001);
//      pM->WriteReg32(&pRegs->mgt_ctrl, 0x00000000);
      usleep(100000);
      pM->WriteReg32(&pRegs->adc_nsb,  2);
      pM->WriteReg32(&pRegs->adc_nsa,  19);
      pM->WriteReg32(&pRegs->csr,      0x40000000);
      usleep(100000);
    }

    void UpdateTextView()
    {
#if 0
      char buf[100];

      pTextViewMain->Clear();
      pTextViewMain->AddLineFast("------ SD Status ------");

      sprintf(buf, "%-20.20s = 0x%08lX","VME BaseAddress", (long)pRegs); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, system); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, status); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, payloadPorts); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, tokenPorts); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutPorts); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigoutPorts); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutStatus); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, trigoutStatus); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 0]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 1]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 2]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 3]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 4]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 5]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 6]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 7]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 8]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[ 9]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[10]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[11]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[12]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[13]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[14]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, busyoutCounter[15]); pTextViewMain->AddLineFast(buf);
      SPFREG(buf, &pRegs, version); pTextViewMain->AddLineFast(buf);

      pTextViewMain->Update();
#endif
    }

 private:

  enum Buttons
  {
    BTN_RESET,
    BTN_SW_SYNC,
    BTN_UPDATE,
    BTN_INIT
  };
   
  ModuleFrame     *pM;
  fadc_struct     *pRegs;

  TGHorizontalFrame *pFrameButtons;
  TGHorizontalFrame *pFrameText;

  TGVerticalFrame *pFrameLeft;
  TGVerticalFrame *pFrameRight;

  TGTextView      *pTextViewMain;
};

#endif
