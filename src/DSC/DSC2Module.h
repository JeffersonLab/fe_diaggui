#ifndef DSC2Module_H
#define DSC2Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DSC2_Scalers.h"
#include "DSC2_Status.h"
#include "DSC2_Config.h"
#include "DSC2_Testing.h"

class DSC2Module	: public ModuleFrame
{
public:
	DSC2Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();
		//SetLayoutManager(new TGVerticalLayout(this));
		//SetLayoutManager(new TGHorizontalLayout(this));

		TGCompositeFrame *tFrame;
		AddFrame(pDSC2Tabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
		tFrame = pDSC2Tabs->AddTab("Config");		tFrame->AddFrame(new DSC2_Config(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pDSC2Tabs->AddTab("Status");		tFrame->AddFrame(new DSC2_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pDSC2Tabs->AddTab("Scalers");		tFrame->AddFrame(new DSC2_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pDSC2Tabs->AddTab("Testing");		tFrame->AddFrame(new DSC2_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
	}

	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
				{"Test Config", 0},
					{"Pulse",				REGMEM_DESC_FLAGS_UINT,		{0x0094, 31, 1, 32}},
					{"EnIn1",				REGMEM_DESC_FLAGS_UINT,		{0x0094, 0, 1, 32}},
					{"EnIn2",				REGMEM_DESC_FLAGS_UINT,		{0x0094, 1, 1, 32}},
				{NULL, 0},
				{"Pulser", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x00C0, 0, 32, 32}},
					{"LowCycles",				REGMEM_DESC_FLAGS_UINT,		{0x00C4, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x00C8, 0, 32, 32}},
					{"Start",					REGMEM_DESC_FLAGS_UINT,		{0x00CC, 0, 0, 32}},
					{"Done",						REGMEM_DESC_FLAGS_UINT,		{0x00D0, 0, 1, 32}},
				{NULL, 0},
				{"TDC Config", 0},
					{"Thresholds", 0},
						{"Ch1",				REGMEM_DESC_FLAGS_UINT,		{0x0000, 0, 12, 32}},
						{"Ch2",				REGMEM_DESC_FLAGS_UINT,		{0x0004, 0, 12, 32}},
						{"Ch3",				REGMEM_DESC_FLAGS_UINT,		{0x0008, 0, 12, 32}},
						{"Ch4",				REGMEM_DESC_FLAGS_UINT,		{0x000C, 0, 12, 32}},
						{"Ch5",				REGMEM_DESC_FLAGS_UINT,		{0x0010, 0, 12, 32}},
						{"Ch6",				REGMEM_DESC_FLAGS_UINT,		{0x0014, 0, 12, 32}},
						{"Ch7",				REGMEM_DESC_FLAGS_UINT,		{0x0018, 0, 12, 32}},
						{"Ch8",				REGMEM_DESC_FLAGS_UINT,		{0x001C, 0, 12, 32}},
						{"Ch9",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 0, 12, 32}},
						{"Ch10",				REGMEM_DESC_FLAGS_UINT,		{0x0024, 0, 12, 32}},
						{"Ch11",				REGMEM_DESC_FLAGS_UINT,		{0x0028, 0, 12, 32}},
						{"Ch12",				REGMEM_DESC_FLAGS_UINT,		{0x002C, 0, 12, 32}},
						{"Ch13",				REGMEM_DESC_FLAGS_UINT,		{0x0030, 0, 12, 32}},
						{"Ch14",				REGMEM_DESC_FLAGS_UINT,		{0x0034, 0, 12, 32}},
						{"Ch15",				REGMEM_DESC_FLAGS_UINT,		{0x0038, 0, 12, 32}},
						{"Ch16",				REGMEM_DESC_FLAGS_UINT,		{0x003C, 0, 12, 32}},
					{NULL, 0},
					{"Enable",				REGMEM_DESC_FLAGS_HEX,		{0x0088, 0, 16, 32}},
					{"OR Mask",				REGMEM_DESC_FLAGS_HEX,		{0x008C, 0, 16, 32}},
					{"Analog Pulser Width",	REGMEM_DESC_FLAGS_UINT,		{0x0080, 0, 6, 32}},
				{NULL, 0},
				{"TRG Config", 0},
					{"Thresholds", 0},
						{"Ch1",				REGMEM_DESC_FLAGS_UINT,		{0x0000, 16, 12, 32}},
						{"Ch2",				REGMEM_DESC_FLAGS_UINT,		{0x0004, 16, 12, 32}},
						{"Ch3",				REGMEM_DESC_FLAGS_UINT,		{0x0008, 16, 12, 32}},
						{"Ch4",				REGMEM_DESC_FLAGS_UINT,		{0x000C, 16, 12, 32}},
						{"Ch5",				REGMEM_DESC_FLAGS_UINT,		{0x0010, 16, 12, 32}},
						{"Ch6",				REGMEM_DESC_FLAGS_UINT,		{0x0014, 16, 12, 32}},
						{"Ch7",				REGMEM_DESC_FLAGS_UINT,		{0x0018, 16, 12, 32}},
						{"Ch8",				REGMEM_DESC_FLAGS_UINT,		{0x001C, 16, 12, 32}},
						{"Ch9",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 16, 12, 32}},
						{"Ch10",				REGMEM_DESC_FLAGS_UINT,		{0x0024, 16, 12, 32}},
						{"Ch11",				REGMEM_DESC_FLAGS_UINT,		{0x0028, 16, 12, 32}},
						{"Ch12",				REGMEM_DESC_FLAGS_UINT,		{0x002C, 16, 12, 32}},
						{"Ch13",				REGMEM_DESC_FLAGS_UINT,		{0x0030, 16, 12, 32}},
						{"Ch14",				REGMEM_DESC_FLAGS_UINT,		{0x0034, 16, 12, 32}},
						{"Ch15",				REGMEM_DESC_FLAGS_UINT,		{0x0038, 16, 12, 32}},
						{"Ch16",				REGMEM_DESC_FLAGS_UINT,		{0x003C, 16, 12, 32}},
					{NULL, 0},
					{"Digital Pulser Width", 0},
						{"Ch1",				REGMEM_DESC_FLAGS_UINT,		{0x0040, 8, 8, 32}},
						{"Ch2",				REGMEM_DESC_FLAGS_UINT,		{0x0044, 8, 8, 32}},
						{"Ch3",				REGMEM_DESC_FLAGS_UINT,		{0x0048, 8, 8, 32}},
						{"Ch4",				REGMEM_DESC_FLAGS_UINT,		{0x004C, 8, 8, 32}},
						{"Ch5",				REGMEM_DESC_FLAGS_UINT,		{0x0050, 8, 8, 32}},
						{"Ch6",				REGMEM_DESC_FLAGS_UINT,		{0x0054, 8, 8, 32}},
						{"Ch7",				REGMEM_DESC_FLAGS_UINT,		{0x0058, 8, 8, 32}},
						{"Ch8",				REGMEM_DESC_FLAGS_UINT,		{0x005C, 8, 8, 32}},
						{"Ch9",				REGMEM_DESC_FLAGS_UINT,		{0x0060, 8, 8, 32}},
						{"Ch10",				REGMEM_DESC_FLAGS_UINT,		{0x0064, 8, 8, 32}},
						{"Ch11",				REGMEM_DESC_FLAGS_UINT,		{0x0068, 8, 8, 32}},
						{"Ch12",				REGMEM_DESC_FLAGS_UINT,		{0x006C, 8, 8, 32}},
						{"Ch13",				REGMEM_DESC_FLAGS_UINT,		{0x0070, 8, 8, 32}},
						{"Ch14",				REGMEM_DESC_FLAGS_UINT,		{0x0074, 8, 8, 32}},
						{"Ch15",				REGMEM_DESC_FLAGS_UINT,		{0x0078, 8, 8, 32}},
						{"Ch16",				REGMEM_DESC_FLAGS_UINT,		{0x007C, 8, 8, 32}},
					{NULL, 0},
					{"Delay", 0},
						{"Ch1",				REGMEM_DESC_FLAGS_UINT,		{0x0040, 0, 8, 32}},
						{"Ch2",				REGMEM_DESC_FLAGS_UINT,		{0x0044, 0, 8, 32}},
						{"Ch3",				REGMEM_DESC_FLAGS_UINT,		{0x0048, 0, 8, 32}},
						{"Ch4",				REGMEM_DESC_FLAGS_UINT,		{0x004C, 0, 8, 32}},
						{"Ch5",				REGMEM_DESC_FLAGS_UINT,		{0x0050, 0, 8, 32}},
						{"Ch6",				REGMEM_DESC_FLAGS_UINT,		{0x0054, 0, 8, 32}},
						{"Ch7",				REGMEM_DESC_FLAGS_UINT,		{0x0058, 0, 8, 32}},
						{"Ch8",				REGMEM_DESC_FLAGS_UINT,		{0x005C, 0, 8, 32}},
						{"Ch9",				REGMEM_DESC_FLAGS_UINT,		{0x0060, 0, 8, 32}},
						{"Ch10",				REGMEM_DESC_FLAGS_UINT,		{0x0064, 0, 8, 32}},
						{"Ch11",				REGMEM_DESC_FLAGS_UINT,		{0x0068, 0, 8, 32}},
						{"Ch12",				REGMEM_DESC_FLAGS_UINT,		{0x006C, 0, 8, 32}},
						{"Ch13",				REGMEM_DESC_FLAGS_UINT,		{0x0070, 0, 8, 32}},
						{"Ch14",				REGMEM_DESC_FLAGS_UINT,		{0x0074, 0, 8, 32}},
						{"Ch15",				REGMEM_DESC_FLAGS_UINT,		{0x0078, 0, 8, 32}},
						{"Ch16",				REGMEM_DESC_FLAGS_UINT,		{0x007C, 0, 8, 32}},
					{NULL, 0},
					{"Enable",				REGMEM_DESC_FLAGS_HEX,		{0x0088, 16, 16, 32}},
					{"OR Mask",				REGMEM_DESC_FLAGS_HEX,		{0x008C, 16, 16, 32}},
					{"Src Select Mask",	REGMEM_DESC_FLAGS_HEX,		{0x00A0, 0, 16, 32}},
					{"Src Bypass Mask",	REGMEM_DESC_FLAGS_HEX,		{0x00A0, 16, 16, 32}},
					{"Analog Pulser Width",	REGMEM_DESC_FLAGS_UINT,		{0x0080, 16, 6, 32}},
				{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "DSC2"; }
	const char *GetModuleFullName() { return "Dual Threshold Scaler"; }

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		//int val = 0;
		//int count = sscanf(pParam2, "%u", &val);

//		if(!stricmp(pParam1, "A32BaseAddr") && count) A32BaseAddr = val;
//		else
			return kFALSE;

		return kTRUE;
	}

private:
	TGTab			*pDSC2Tabs;
};

#endif
