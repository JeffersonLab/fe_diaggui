#ifndef VTP_Module_H
#define VTP_Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "VTP_TrgHist.h"

class VTP_Module	: public ModuleFrame
{
public:
	VTP_Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Config");		tFrame->AddFrame(pSSPConfig = new SSP_Config(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Histograms");	tFrame->AddFrame(pSSPHistograms = new SSP_Histograms(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		tFrame = pTabs->AddTab("TrgHist");		tFrame->AddFrame(new VTP_TrgHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));


		strSlotIdentifier.Form("SWA");
	}

	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
			{"ECTrig0", 0},
				{"Hit_dt",					REGMEM_DESC_FLAGS_UINT,		{0x14100, 16, 4, 32}},
				{"Hit_emin",			   REGMEM_DESC_FLAGS_UINT,		{0x14100, 0, 13, 32}},
				{"Dalitz_min",				REGMEM_DESC_FLAGS_UINT,		{0x14104, 0, 10, 32}},
            {"Dalitz_max",          REGMEM_DESC_FLAGS_UINT,    {0x14104, 10, 10, 32}},
			{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "VTP"; }
	const char *GetModuleFullName() { return "VXS Trigger Processor"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pTabs;
};

#endif
