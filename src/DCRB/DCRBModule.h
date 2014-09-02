#ifndef DCRBModule_H
#define DCRBModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRB_Status.h"
#include "DCRB_Scalers.h"
#include "DCRB_TDCPlots.h"
#include "DCRB_Testing.h"
#include "DCRB_NoisePlots.h"
#include "DCRB_GTP.h"

class DCRBModule	: public ModuleFrame
{
public:
	DCRBModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGTab *pTabs;

#pragma warning("need to get this done through SetParameter")
		A32BaseAddr = 0x08000000;

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("NoisePlots");	tFrame->AddFrame(new DCRB_NoisePlots(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("TDCPlots");		tFrame->AddFrame(new DCRB_TDCPlots(tFrame, this, A32BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("GTP");			tFrame->AddFrame(new DCRB_GTP(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Scalers");		tFrame->AddFrame(new DCRB_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Status");		tFrame->AddFrame(new DCRB_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Testing");		tFrame->AddFrame(new DCRB_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		
		strSlotIdentifier.Form("%d", ReadReg32((volatile unsigned int *)(BaseAddr+0x0050)) & 0x1F);
	}

	const char *GetModuleName() { return "DCRB"; }
	const char *GetModuleFullName() { return "Drift Chamber Readout Board"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pTabs;

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		int val = 0;
		int count = sscanf(pParam2, "%u", &val);

		if(!stricmp(pParam1, "A32BaseAddr") && count) A32BaseAddr = val;
		else if(!stricmp(pParam1, "DacThreshold") && count)
			WriteReg32((volatile unsigned int *)(BaseAddr+0x0038), ((unsigned int)val * 24489360)>>18);
		else if(!stricmp(pParam1, "Reset") && count)
		{
			unsigned int r;
			WriteReg32((volatile unsigned int *)(BaseAddr+0x0068), 0);	// Reset
			r = ReadReg32((volatile unsigned int *)(BaseAddr+0x0030));
			WriteReg32((volatile unsigned int *)(BaseAddr+0x0030), r | 0x2);
			WriteReg32((volatile unsigned int *)(BaseAddr+0x0030), r & ~0x2);
			WriteReg32((volatile unsigned int *)(BaseAddr+0x0030), r | 0x3);
			WriteReg32((volatile unsigned int *)(BaseAddr+0x0030), r & ~0x2);
		}
		else
			return kFALSE;

		return kTRUE;
	}

	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
			{"FirmwareRev",		REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
			{"BoardID",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
			{"TestPulseConfig",	REGMEM_DESC_FLAGS_HEX,		{0x0034, 0, 12, 32}},
			{"DAC",					REGMEM_DESC_FLAGS_UINT,		{0x0038, 0, 32, 32}},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}
private:
	unsigned int	A32BaseAddr;
};

#endif
