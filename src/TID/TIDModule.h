#ifndef TIDModule_H
#define TIDModule_H

#include "RootHeader.h"
#include "TID_Status.h"
#include "ModuleFrame.h"

class TIDModule	: public ModuleFrame
{
 public:
  TIDModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
    {
		SetupRegisters();

      TGCompositeFrame *tFrame;
      AddFrame(pTIDTabs = new TGTab(this), 
	       new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

      tFrame = pTIDTabs->AddTab("Status");
      tFrame->AddFrame(new TID_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    }


	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
				{"SD", 0},
					{"TIBoardID",			REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
					{"Version",				REGMEM_DESC_FLAGS_HEX,		{0x43C7C, 0, 32, 32}},
					{"TIBoardID",			REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
				{NULL, 0},
				{"BoardID", 0},
					{"CrateID",				REGMEM_DESC_FLAGS_UINT,		{0x0000, 0, 8, 32}},
					{"A24Addr",				REGMEM_DESC_FLAGS_HEX,		{0x0000, 8, 5, 32}},
					{"PCB",					REGMEM_DESC_FLAGS_STRING,	{0x0000, 16, 8, 32}, {2,{"PRODUCTION", "PROTOTYPE"},{0x01,0x00}}},
					{"TYPE",					REGMEM_DESC_FLAGS_STRING,	{0x0000, 24, 8, 32}, {3,{"TS","TS","TD"},{0x71,0x75,0x7D}}},
				{NULL, 0},
				{"Transceivers", 0},
					{"EnableMask",			REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 8, 32}},
					{"LinkSync'd",			REGMEM_DESC_FLAGS_HEX,		{0x0004, 16, 8, 32}},
					{"TITrgEnabled",		REGMEM_DESC_FLAGS_HEX,		{0x0004, 24, 8, 32}},
				{NULL, 0},
				{"Pulses", 0},
					{"Trig1Delay",			REGMEM_DESC_FLAGS_HEX,		{0x000C, 0, 8, 32}},
					{"Trig1Width",			REGMEM_DESC_FLAGS_HEX,		{0x000C, 9, 8, 32}},
					{"Trig2Delay",			REGMEM_DESC_FLAGS_HEX,		{0x000C, 16, 8, 32}},
					{"Trig2Width",			REGMEM_DESC_FLAGS_HEX,		{0x000C, 24, 8, 32}},
				{NULL, 0},
				{"TrgSrc", 0},
					{"P0",					REGMEM_DESC_FLAGS_UINT,		{0x0020, 0, 1, 32}},
					{"HFBR1",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 1, 1, 32}},
					{"TIMLoopback",		REGMEM_DESC_FLAGS_UINT,		{0x0020, 2, 1, 32}},
					{"FP-TrgIn",			REGMEM_DESC_FLAGS_UINT,		{0x0020, 3, 1, 32}},
					{"VME",					REGMEM_DESC_FLAGS_UINT,		{0x0020, 4, 1, 32}},
					{"FP-TrgCode",			REGMEM_DESC_FLAGS_UINT,		{0x0020, 5, 1, 32}},
					{"TS-TrgIn",			REGMEM_DESC_FLAGS_UINT,		{0x0020, 6, 1, 32}},
					{"Random",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 7, 1, 32}},
					{"HFBR5",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 10, 1, 32}},
					{"TSsub1",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 12, 1, 32}},
					{"TSsub2",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 13, 1, 32}},
					{"TSsub3",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 14, 1, 32}},
					{"TSsub4",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 15, 1, 32}},
				{NULL, 0},
				{"SyncSrc", 0},
					{"P0",					REGMEM_DESC_FLAGS_UINT,		{0x0024, 0, 1, 32}},
					{"HFBR1",				REGMEM_DESC_FLAGS_UINT,		{0x0024, 1, 1, 32}},
					{"HFBR5",				REGMEM_DESC_FLAGS_UINT,		{0x0024, 2, 1, 32}},
					{"FP-TrgInhEn",		REGMEM_DESC_FLAGS_UINT,		{0x0024, 3, 1, 32}},
					{"TIMLoopback",		REGMEM_DESC_FLAGS_UINT,		{0x0024, 4, 1, 32}},
					{"Auto",					REGMEM_DESC_FLAGS_UINT,		{0x0024, 6, 1, 32}},
					{"User",					REGMEM_DESC_FLAGS_UINT,		{0x0024, 7, 1, 32}},
				{NULL, 0},
				{"BusySrc", 0},
					{"SWA",					REGMEM_DESC_FLAGS_UINT,		{0x0028, 0, 1, 32}},
					{"SWB",					REGMEM_DESC_FLAGS_UINT,		{0x0028, 1, 1, 32}},
					{"P2",					REGMEM_DESC_FLAGS_UINT,		{0x0028, 2, 1, 32}},
					{"FP-TDC",				REGMEM_DESC_FLAGS_UINT,		{0x0028, 3, 1, 32}},
					{"FP-ADC",				REGMEM_DESC_FLAGS_UINT,		{0x0028, 4, 1, 32}},
					{"FP",					REGMEM_DESC_FLAGS_UINT,		{0x0028, 5, 1, 32}},
					{"TS",					REGMEM_DESC_FLAGS_UINT,		{0x0028, 7, 1, 32}},
					{"HFBRMask",			REGMEM_DESC_FLAGS_HEX,		{0x0028, 8, 8, 32}},
				{NULL, 0},
				{"ClkSrc",					REGMEM_DESC_FLAGS_STRING,	{0x002C, 0, 2, 32}, {4,{"INT","HFBR5","HFBR1","FP"},{0,1,2,3}}},
				{"TrgPrescale",			REGMEM_DESC_FLAGS_UINT,		{0x0030, 0, 16, 32}},
				{"VMEAcks",					REGMEM_DESC_FLAGS_UINT,		{0x0054, 0, 8, 32}},
				{"TiGtpAcks",				REGMEM_DESC_FLAGS_UINT,		{0x0054, 8, 8, 32}},
				{"TiGtpRxErrors",			REGMEM_DESC_FLAGS_UINT,		{0x0040, 16, 16, 32}},
				{"TiGtpSentBlocks",		REGMEM_DESC_FLAGS_UINT,		{0x0040, 0, 16, 32}},
				{"HFBR1-SyncPhase",		REGMEM_DESC_FLAGS_UINT,		{0x0050, 0, 8, 32}},
				{"HFBR1-SyncDelay",		REGMEM_DESC_FLAGS_UINT,		{0x0050, 8, 8, 32}},
				{"TM-SyncDelay",			REGMEM_DESC_FLAGS_UINT,		{0x0050, 16, 8, 32}},
				{"FP1-Prescale",			REGMEM_DESC_FLAGS_UINT,		{0x0074, 0, 4, 32}},
				{"FP2-Prescale",			REGMEM_DESC_FLAGS_UINT,		{0x0074, 4, 4, 32}},
				{"FP3-Prescale",			REGMEM_DESC_FLAGS_UINT,		{0x0074, 8, 4, 32}},
				{"FP4-Prescale",			REGMEM_DESC_FLAGS_UINT,		{0x0074, 12, 4, 32}},
				{"FP5-Prescale",			REGMEM_DESC_FLAGS_UINT,		{0x0074, 16, 4, 32}},
				{"FP6-Prescale",			REGMEM_DESC_FLAGS_UINT,		{0x0074, 20, 4, 32}},

				{"HFBR1-Lat4ns",			REGMEM_DESC_FLAGS_UINT,		{0x00A0, 23, 9, 32}},
				{"HFBR1-Lat78ps",			REGMEM_DESC_FLAGS_UINT,		{0x00A0, 16, 7, 32}},
				{"HFBR1-LatCarry",		REGMEM_DESC_FLAGS_UINT,		{0x00A0, 0, 16, 32}},

				{"HFBR5-Lat4ns",			REGMEM_DESC_FLAGS_UINT,		{0x00A0, 23, 9, 32}},
				{"HFBR5-Lat78ps",			REGMEM_DESC_FLAGS_UINT,		{0x00A0, 16, 7, 32}},
				{"HFBR5-LatCarry",		REGMEM_DESC_FLAGS_UINT,		{0x00A0, 0, 16, 32}},

				{"TIM-TrgBufWords",		REGMEM_DESC_FLAGS_UINT,		{0x00B0, 16, 10, 32}},
				{"TI-TrgBufWords",		REGMEM_DESC_FLAGS_UINT,		{0x00B8, 0, 10, 32}},

				{"ROCEnableMask",			REGMEM_DESC_FLAGS_UINT,		{0x00EC, 0, 8, 32}},

				// Temporary monitor regiser
				{"TiGtpSOPCount",			REGMEM_DESC_FLAGS_UINT,		{0x0044, 0, 8, 32}},
				{"TiGtpAckCount",			REGMEM_DESC_FLAGS_UINT,		{0x0044, 8, 8, 32}},
				{"TiGtpEOPCount",			REGMEM_DESC_FLAGS_UINT,		{0x0044, 16, 8, 32}},
				{"TiGtpSOPAckEOPCount",	REGMEM_DESC_FLAGS_UINT,		{0x0044, 24, 8, 32}},
		};
		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

    const char *GetModuleName() { return "TID"; }
    const char *GetModuleFullName() { return "Trigger Interface/Distributor"; }

 private:
    TGTab			*pTIDTabs;
};

#endif
