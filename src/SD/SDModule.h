#ifndef SDModule_H
#define SDModule_H

#include "RootHeader.h"
#include "SD_Status.h"
#include "ModuleFrame.h"

class SDModule	: public ModuleFrame
{
 public:
  SDModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
    {
      SetLayoutManager(new TGVerticalLayout(this));

      TGCompositeFrame *tFrame;
      AddFrame(pSDTabs = new TGTab(this), 
	       new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

      tFrame = pSDTabs->AddTab("Status");
      tFrame->AddFrame(new SD_Status(tFrame, this), 
		       new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    }

    const char *GetModuleName() { return "SD"; }
    const char *GetModuleFullName() { return "Signal Distribution Module"; }

 private:
    TGTab			*pSDTabs;
};

#endif
