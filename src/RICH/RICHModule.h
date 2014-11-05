#ifndef RICHModule_H
#define RICHModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"

class RICHModule	: public ModuleFrame
{
public:
	RICHModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
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
			{"ClkRst", 0},
				{"SoftReset",				REGMEM_DESC_FLAGS_UINT,		{0x0000, 0, 1, 32}},
				{"Dummy",					REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
			{NULL, 0},
			{"MAROC", 0},
				{"Serial", 0},
					{"ResetN",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 0, 1, 32}},
					{"Start",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 1, 1, 32}},
					{"Busy",					REGMEM_DESC_FLAGS_UINT,		{0x0104, 0, 1, 32}},
				{NULL, 0},
				{"Global", 0},
					{"cmd_fsu",				REGMEM_DESC_FLAGS_UINT,		{0x0110, 0, 1, 32}},
					{"cmd_ss",				REGMEM_DESC_FLAGS_UINT,		{0x0110, 1, 1, 32}},
					{"cmd_fsb",				REGMEM_DESC_FLAGS_UINT,		{0x0110, 2, 1, 32}},
					{"swb_buf_250f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 3, 1, 32}},
					{"swb_buf_500f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 4, 1, 32}},
					{"swb_buf_1p",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 5, 1, 32}},
					{"swb_buf_2p",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 6, 1, 32}},
					{"ON/OFF_ss",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 7, 1, 32}},
					{"sw_ss_300f",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 8, 1, 32}},
					{"sw_ss_600f",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 9, 1, 32}},
					{"sw_ss_1200f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 10, 1, 32}},
					{"EN_ADC",				REGMEM_DESC_FLAGS_UINT,		{0x0110, 11, 1, 32}},
					{"H1H2_choice",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 12, 1, 32}},
					{"sw_fsu_20f",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 13, 1, 32}},
					{"sw_fsu_40f",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 14, 1, 32}},
					{"sw_fsu_25k",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 15, 1, 32}},
					{"sw_fsu_50k",			REGMEM_DESC_FLAGS_UINT,		{0x0110, 16, 1, 32}},
					{"sw_fsu_100k",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 17, 1, 32}},
					{"sw_fsb1_50k",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 18, 1, 32}},
					{"sw_fsb1_100k",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 19, 1, 32}},
					{"sw_fsb1_100f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 20, 1, 32}},
					{"sw_fsb1_50f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 21, 1, 32}},
					{"cmd_fsb_fsu",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 22, 1, 32}},
					{"valid_dc_fs",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 23, 1, 32}},
					{"sw_fsb2_50k",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 24, 1, 32}},
					{"sw_fsb2_100k",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 25, 1, 32}},
					{"sw_fsb2_100f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 26, 1, 32}},
					{"sw_fsb2_50f",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 27, 1, 32}},
					{"valid_dc_fsb2",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 28, 1, 32}},
					{"ENb_tristate",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 29, 1, 32}},
					{"polar_discri",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 30, 1, 32}},
					{"inv_discriADC",		REGMEM_DESC_FLAGS_UINT,		{0x0110, 31, 1, 32}},
					{"d1_d2",				REGMEM_DESC_FLAGS_UINT,		{0x0114, 0, 1, 32}},
					{"cmd_CK_mux",			REGMEM_DESC_FLAGS_UINT,		{0x0114, 1, 1, 32}},
				{NULL, 0},
				{"Channels", 0},
					{"Ch0", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0120, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0120, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0120, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0120, 11, 1, 32}},
					{NULL, 0},
					{"Ch1", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0120, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0120, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0120, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0120, 26, 1, 32}},
					{NULL, 0},
					{"Ch2", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0124, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0124, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0124, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0124, 11, 1, 32}},
					{NULL, 0},
					{"Ch3", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0124, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0124, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0124, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0124, 26, 1, 32}},
					{NULL, 0},
					{"Ch4", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0128, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0128, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0128, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0128, 11, 1, 32}},
					{NULL, 0},
					{"Ch5", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0128, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0128, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0128, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0128, 26, 1, 32}},
					{NULL, 0},
					{"Ch6", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x012C, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x012C, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x012C, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x012C, 11, 1, 32}},
					{NULL, 0},
					{"Ch7", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x012C, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x012C, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x012C, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x012C, 26, 1, 32}},
					{NULL, 0},
					{"Ch8", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0130, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0130, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0130, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0130, 11, 1, 32}},
					{NULL, 0},
					{"Ch9", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0130, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0130, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0130, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0130, 26, 1, 32}},
					{NULL, 0},
					{"Ch10", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0134, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0134, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0134, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0134, 11, 1, 32}},
					{NULL, 0},
					{"Ch11", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0134, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0134, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0134, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0134, 26, 1, 32}},
					{NULL, 0},
					{"Ch12", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0138, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0138, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0138, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0138, 11, 1, 32}},
					{NULL, 0},
					{"Ch13", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x0138, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x0138, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x0138, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x0138, 26, 1, 32}},
					{NULL, 0},
					{"Ch14", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x013C, 0, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x013C, 9, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x013C, 10, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x013C, 11, 1, 32}},
					{NULL, 0},
					{"Ch15", 0},
						{"gain",					REGMEM_DESC_FLAGS_UINT,		{0x013C, 16, 8, 32}},
						{"ctest",				REGMEM_DESC_FLAGS_UINT,		{0x013C, 24, 1, 32}},
						{"mask_or1",			REGMEM_DESC_FLAGS_UINT,		{0x013C, 25, 1, 32}},
						{"mask_or2",			REGMEM_DESC_FLAGS_UINT,		{0x013C, 26, 1, 32}},
					{NULL, 0},
				{NULL, 0},
			{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "RICH"; }
	const char *GetModuleFullName() { return "RICH FPGA"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pTabs;
};

#endif
