#ifndef FADCScalers_HPSModule_H
#define FADCScalers_HPSModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "FADCScalers_HPSPlot.h"

class FADCScalers_HPSModule	: public ModuleFrame
{
public:
	FADCScalers_HPSModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		TGTab *pTabs;

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Plot");	tFrame->AddFrame(pFADCScalers_HPSPlot = new FADCScalers_HPSPlot(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
	}

	const char *GetModuleName() { return "FADCScalers_HPS"; }
	const char *GetModuleFullName() { return "FADC HPS Scalers"; }
	const char *GetSlotIdentifier() { return "MULTI"; }

private:
	FADCScalers_HPSPlot	*pFADCScalers_HPSPlot;
	TGTab						*pTabs;

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		return pFADCScalers_HPSPlot->SetParameter(pParam1, pParam2);
	}
};

#endif
