#ifndef V1495PulserModule_H
#define V1495PulserModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"

class V1495PulserModule	: public ModuleFrame
{
public:
	V1495PulserModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

//		tFrame = pTabs->AddTab("Testing");		tFrame->AddFrame(new SSP_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		strSlotIdentifier.Form("%d", (BaseAddr>>19) & 0x1F);
	}

	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
			{"Status", 0},
				{"PulserId",				REGMEM_DESC_FLAGS_HEX,		{0x1000, 0, 32, 32}},
				{"FirmwareRev",			REGMEM_DESC_FLAGS_HEX,		{0x1004, 0, 32, 32}},
				{"Daughterboard",			REGMEM_DESC_FLAGS_HEX,		{0x1008, 0, 32, 32}},
				{"Jumpers",					REGMEM_DESC_FLAGS_HEX,		{0x100C, 0, 32, 32}},
			{NULL, 0},
			{"Pulsers", 0},
				{"Global", 0},
					{"StartStop",				REGMEM_DESC_FLAGS_UINT,		{0x1030, 0, 1, 32}},
					{"StatusL",					REGMEM_DESC_FLAGS_HEX,		{0x1014, 0, 32, 32}},
					{"StatusH",					REGMEM_DESC_FLAGS_HEX,		{0x1010, 0, 32, 32}},
					{"StartMaskL",				REGMEM_DESC_FLAGS_HEX,		{0x101C, 0, 32, 32}},
					{"StartMaskH",				REGMEM_DESC_FLAGS_HEX,		{0x1018, 0, 32, 32}},
					{"StopMaskL",				REGMEM_DESC_FLAGS_HEX,		{0x1024, 0, 32, 32}},
					{"StopMaskH",				REGMEM_DESC_FLAGS_HEX,		{0x1020, 0, 32, 32}},
					{"GinMaskL",				REGMEM_DESC_FLAGS_HEX,		{0x102C, 0, 32, 32}},
					{"GinMaskH",				REGMEM_DESC_FLAGS_HEX,		{0x1028, 0, 32, 32}},
					{"MasterOrDelay",			REGMEM_DESC_FLAGS_UINT,		{0x1100, 0, 32, 32}},
					{"MasterOrWidth",			REGMEM_DESC_FLAGS_UINT,		{0x1104, 0, 32, 32}},
				{NULL, 0},
				{"Pulser0", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x2000, 0, 27, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x2004, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x2008, 0, 32, 32}},
				{NULL, 0},
				{"Pulser1", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 0, 27, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x2014, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x2018, 0, 32, 32}},
				{NULL, 0},
				{"Pulser2", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x2020, 0, 27, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x2024, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x2028, 0, 32, 32}},
				{NULL, 0},
				{"Pulser3", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x2030, 0, 27, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x2034, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x2038, 0, 32, 32}},
				{NULL, 0},
			{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "V1495Pulser"; }
	const char *GetModuleFullName() { return "V1495 Pulser"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pTabs;
};

#endif
