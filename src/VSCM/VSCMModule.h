#ifndef VSCMModule_H
#define VSCMModule_H

#include "RootHeader.h"
#include "VSCM_Status.h"
#include "VSCM_Scalers.h"
#include "VSCM_FssrScalers.h"
#include "VSCM_Testing.h"
#include "ModuleFrame.h"

class VSCMModule	: public ModuleFrame
{
public:
	VSCMModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		AddFrame(pVSCMTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

		TGCompositeFrame *tFrame;
		VSCM_Status *pVSCM_Status;

		tFrame = pVSCMTabs->AddTab("Testing");		tFrame->AddFrame(new VSCM_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("Status");		tFrame->AddFrame(pVSCM_Status = new VSCM_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));//tFrame->AddFrame(pVSCM_Status = new VSCM_Status(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("Scalers");		tFrame->AddFrame(new VSCM_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB1 U1");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB1 U2");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB1 U3");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB1 U4");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB2 U1");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB2 U2");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB2 U3");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pVSCMTabs->AddTab("HFCB2 U4");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		strSlotIdentifier.Form("%d", pVSCM_Status->GetSlot());
	}

	const char *GetModuleName() { return "VSCM"; }
	const char *GetModuleFullName() { return "VXS Silicon Control Module"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pVSCMTabs;
};

#endif
