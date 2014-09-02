#ifndef CTPModule_H
#define CTPModule_H

#include "RootHeader.h"
#include "CTP_Status.h"
//#include "CTP_WaveCapture.h"
#include "ModuleFrame.h"

class CTPModule	: public ModuleFrame
{
 public:
  CTPModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
    {
      SetLayoutManager(new TGVerticalLayout(this));

      TGCompositeFrame *tFrame;
      AddFrame(pCTPTabs = new TGTab(this), 
	       new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

      tFrame = pCTPTabs->AddTab("Status");
		tFrame->AddFrame(new CTP_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//      tFrame->AddFrame(new CTP_WaveCapture(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    }

    const char *GetModuleName() { return "CTP"; }
    const char *GetModuleFullName() { return "Crate Trigger Processor"; }

 private:
    TGTab			*pCTPTabs;
};

#endif
