#ifndef DCRBScalersModule_H
#define DCRBScalersModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRBScalers_Plot.h"

class DCRBScalersModule	: public ModuleFrame
{
public:
	DCRBScalersModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		TGTab *pTabs;

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Plot");	tFrame->AddFrame(pDCRBScalers_Plot = new DCRBScalers_Plot(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
	}

	const char *GetModuleName() { return "DCRBScalers"; }
	const char *GetModuleFullName() { return "Drift Chamber Scalers"; }
	const char *GetSlotIdentifier() { return "MULTI"; }

private:
	DCRBScalers_Plot	*pDCRBScalers_Plot;
	TGTab					*pTabs;

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		return pDCRBScalers_Plot->SetParameter(pParam1, pParam2);
	}
};

#endif
