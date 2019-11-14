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
		SetupRegisters();
		
		TGTab *pTabs;

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

		tFrame = pTabs->AddTab("Status");	tFrame->AddFrame(new VSCM_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));//tFrame->AddFrame(pVSCM_Status = new VSCM_Status(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Scalers");	tFrame->AddFrame(new VSCM_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB1 U1");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB1 U2");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB1 U3");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB1 U4");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB2 U1");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB2 U2");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB2 U3");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("HFCB2 U4");	tFrame->AddFrame(new VSCM_FssrScalers(tFrame, this, 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Testing");	tFrame->AddFrame(new VSCM_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		strSlotIdentifier.Form("%d", ReadReg32((volatile unsigned int *)(BaseAddr+0x0050)) & 0x1F);
	}

	const char *GetModuleName() { return "VSCM"; }
	const char *GetModuleFullName() { return "VXS Silicon Control Module"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	
	void SetupRegisters()
	{
#define VSCM_SDIOMUX_NAME_MAP		{\
											22,\
											{"0","1","PULSER","FPIN0","FPIN1","FPIN2","FPIN3","SYNC","TRIG1","TRIG2",\
											 "SWAGPIO0","SWAGPIO1","SWBGPIO0","SWBGPIO1","BUSY","GOTHIT",\
											 "DACTRIG","DACTRIGDLY","DACBCOCLK","TOKENOUT","TOKENIN","GOTHITTRIG"},\
											{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}\
										}

		static RegMemDesc regs[] = {
			{"Config", 0},
				{"Spi", 0},
					{"WrData",		REGMEM_DESC_FLAGS_HEX,		{0x0014, 0, 8, 32}},
					{"RdData",		REGMEM_DESC_FLAGS_HEX,		{0x0014, 0, 8, 32}},
					{"NCSSet",		REGMEM_DESC_FLAGS_UINT,		{0x0014, 8, 1, 32}},
					{"NCSClear",	REGMEM_DESC_FLAGS_UINT,		{0x0014, 9, 1, 32}},
					{"Start",		REGMEM_DESC_FLAGS_UINT,		{0x0014, 10, 1, 32}},
					{"Done",			REGMEM_DESC_FLAGS_UINT,		{0x0014, 11, 1, 32}},
				{NULL, 0},
				{"BoardId",			REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
				{"FirmwareRev",	REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
				{"SoftReset",		REGMEM_DESC_FLAGS_UINT,		{0x0068, 0, 1, 32}},
			{NULL, 0},
			{"Clk", 0},
				{"ClkPllReset",	REGMEM_DESC_FLAGS_UINT,		{0x0030, 1, 1, 32}},
				{"ClkSel",			REGMEM_DESC_FLAGS_STRING,	{0x0030, 0, 1, 32}, {2,{"LCLK","SWCLK"}, {0,1}}},
				{"ClkPllLocked",	REGMEM_DESC_FLAGS_UINT,		{0x0030, 2, 1, 32}},
			{NULL, 0},
			{"Sd", 0},
				{"GotHitOrMask",	REGMEM_DESC_FLAGS_HEX,		{0x00AC, 0, 8, 32}},
				{"GotHitOrWidth",	REGMEM_DESC_FLAGS_UINT,		{0x00AC, 8, 8, 32}},
				{"Delays", 0},
					{"FPOUT0",		REGMEM_DESC_FLAGS_UINT,		{0x0138, 16, 13, 32}},
					{"FPOUT1",		REGMEM_DESC_FLAGS_UINT,		{0x013C, 16, 13, 32}},
					{"FPOUT2",		REGMEM_DESC_FLAGS_UINT,		{0x0140, 16, 13, 32}},
					{"FPOUT3",		REGMEM_DESC_FLAGS_UINT,		{0x0144, 16, 13, 32}},
				{NULL, 0},
				{"I/O Muxing", 0},
					{"FPOUT0",		REGMEM_DESC_FLAGS_STRING,	{0x0138, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"FPOUT1",		REGMEM_DESC_FLAGS_STRING,	{0x013C, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"FPOUT2",		REGMEM_DESC_FLAGS_STRING,	{0x0140, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"FPOUT3",		REGMEM_DESC_FLAGS_STRING,	{0x0144, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwAGpio0",	REGMEM_DESC_FLAGS_STRING,	{0x0108, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwAGpio0Dir",REGMEM_DESC_FLAGS_STRING,	{0x0108, 8, 1, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwAGpio1",	REGMEM_DESC_FLAGS_STRING,	{0x0108, 16, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwAGpio1Dir",REGMEM_DESC_FLAGS_STRING,	{0x0108, 24, 1, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwBGpio0",	REGMEM_DESC_FLAGS_STRING,	{0x010C, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwBGpio0Dir",REGMEM_DESC_FLAGS_STRING,	{0x010C, 8, 1, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwBGpio1",	REGMEM_DESC_FLAGS_STRING,	{0x010C, 16, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SwBGpio1Dir",REGMEM_DESC_FLAGS_STRING,	{0x010C, 24, 1, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"Sync",			REGMEM_DESC_FLAGS_STRING,	{0x0104, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"Trig",			REGMEM_DESC_FLAGS_STRING,	{0x0100, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"DACTrig",		REGMEM_DESC_FLAGS_STRING,	{0x014C, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"TokenIn",		REGMEM_DESC_FLAGS_STRING,	{0x0018, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"TokenOut",	REGMEM_DESC_FLAGS_STRING,	{0x001C, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"SdLink",		REGMEM_DESC_FLAGS_STRING,	{0x0020, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
					{"TrigOut",		REGMEM_DESC_FLAGS_STRING,	{0x0024, 0, 5, 32},	VSCM_SDIOMUX_NAME_MAP},
				{NULL, 0},
				{"Pulser", 0},
					{"Period",		REGMEM_DESC_FLAGS_UINT,		{0x0120, 0, 32, 32}},
					{"LowCycles",	REGMEM_DESC_FLAGS_UINT,		{0x0124, 0, 32, 32}},
					{"NPulses",		REGMEM_DESC_FLAGS_UINT,		{0x0150, 0, 32, 32}},
					{"Start",		REGMEM_DESC_FLAGS_UINT,		{0x0154, 0, 0, 32}},
					{"Done",			REGMEM_DESC_FLAGS_UINT,		{0x0158, 0, 1, 32}},
				{NULL, 0},
				{"Scalers", 0},
					{"Latch",		REGMEM_DESC_FLAGS_UINT,		{0x0078, 31, 1, 32}},
					{"FSSREnable",	REGMEM_DESC_FLAGS_HEX,		{0x0078, 0, 8, 32}},
					{"FPOUT0",		REGMEM_DESC_FLAGS_UINT,		{0x0FC8, 0, 32, 32}},
					{"FPOUT1",		REGMEM_DESC_FLAGS_UINT,		{0x0FCC, 0, 32, 32}},
					{"FPOUT2",		REGMEM_DESC_FLAGS_UINT,		{0x0FD0, 0, 32, 32}},
					{"FPOUT3",		REGMEM_DESC_FLAGS_UINT,		{0x0FD4, 0, 32, 32}},
					{"FPIN0",		REGMEM_DESC_FLAGS_UINT,		{0x0FD8, 0, 32, 32}},
					{"FPIN1",		REGMEM_DESC_FLAGS_UINT,		{0x0FDC, 0, 32, 32}},
					{"FPIN2",		REGMEM_DESC_FLAGS_UINT,		{0x0FE0, 0, 32, 32}},
					{"FPIN3",		REGMEM_DESC_FLAGS_UINT,		{0x0FE4, 0, 32, 32}},
					{"Busy",			REGMEM_DESC_FLAGS_UINT,		{0x0FE8, 0, 32, 32}},
					{"BusyCycles",	REGMEM_DESC_FLAGS_UINT,		{0x0FEC, 0, 32, 32}},
					{"SysClk50",	REGMEM_DESC_FLAGS_UINT,		{0x0FF0, 0, 32, 32}},
					{"Sync",			REGMEM_DESC_FLAGS_UINT,		{0x0FF4, 0, 32, 32}},
					{"Trig1",		REGMEM_DESC_FLAGS_UINT,		{0x0FF8, 0, 32, 32}},
					{"Trig2",		REGMEM_DESC_FLAGS_UINT,		{0x0FFC, 0, 32, 32}},
					{"FSSR_H1U1", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1000, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1004, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1008, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x100C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1010, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1014, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1018, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x101C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1020, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1028, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1038, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H1U2", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1100, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1104, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1108, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x110C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1110, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1114, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1118, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x111C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1120, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1128, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1138, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H1U3", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1200, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1204, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1208, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x120C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1210, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1214, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1218, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x121C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1220, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1228, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1238, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H1U4", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1300, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1304, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1308, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x130C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1310, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1314, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1318, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x131C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1320, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1328, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1338, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H2U1", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1400, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1404, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1408, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x140C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1410, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1414, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1418, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x141C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1420, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1428, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1438, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H2U2", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1500, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1504, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1508, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x150C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1510, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1514, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1518, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x151C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1520, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1528, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1538, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H2U3", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1600, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1604, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1608, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x160C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1610, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1614, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1618, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x161C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1620, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1628, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1638, 0, 32, 32}},
					{NULL, 0},
					{"FSSR_H2U4", 0},
						{"LastStat",REGMEM_DESC_FLAGS_HEX,		{0x1700, 0, 32, 32}},
						{"NStat",	REGMEM_DESC_FLAGS_UINT,		{0x1704, 0, 32, 32}},
						{"NEvent",	REGMEM_DESC_FLAGS_UINT,		{0x1708, 0, 32, 32}},
						{"NWord",	REGMEM_DESC_FLAGS_UINT,		{0x170C, 0, 32, 32}},
						{"NIdle",	REGMEM_DESC_FLAGS_UINT,		{0x1710, 0, 32, 32}},
						{"NAqBCO",	REGMEM_DESC_FLAGS_UINT,		{0x1714, 0, 32, 32}},
						{"NMarkErr",REGMEM_DESC_FLAGS_UINT,		{0x1718, 0, 32, 32}},
						{"NEncErr",	REGMEM_DESC_FLAGS_UINT,		{0x171C, 0, 32, 32}},
						{"NIDErr",	REGMEM_DESC_FLAGS_UINT,		{0x1720, 0, 32, 32}},
						{"NGotHit",	REGMEM_DESC_FLAGS_UINT,		{0x1728, 0, 32, 32}},
						{"NCoreTalk",REGMEM_DESC_FLAGS_UINT,	{0x1738, 0, 32, 32}},
					{NULL, 0},
				{NULL, 0},
			{NULL, 0},
		};
		
		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}
};

#endif
