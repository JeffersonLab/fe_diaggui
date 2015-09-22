#ifndef vectoc_module_H
#define vectoc_module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "vetroc_scalers.h"
#include "vetroc_serialscope.h"

class vetroc_module	: public ModuleFrame
{
public:
	vetroc_module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGTab *pTabs;

#pragma warning("need to get this done through SetParameter")
		A32BaseAddr = 0x08000000;

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("NoisePlots");	tFrame->AddFrame(new DCRB_NoisePlots(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("TDCPlots");		tFrame->AddFrame(new DCRB_TDCPlots(tFrame, this, A32BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("GTP");			tFrame->AddFrame(new DCRB_GTP(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("VXSScope");		tFrame->AddFrame(new vetroc_serialscope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Scalers");		tFrame->AddFrame(new vetroc_scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Status");		tFrame->AddFrame(new DCRB_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Testing");		tFrame->AddFrame(new DCRB_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		
		strSlotIdentifier.Form("%d", (ReadReg32((volatile unsigned int *)(BaseAddr+0x0000))>>24) & 0x1F);
	}

	const char *GetModuleName() { return "VETROC"; }
	const char *GetModuleFullName() { return "VETROC"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pTabs;

	Bool_t SetParameter(char *pParam1, char *pParam2)
	{
		int val = 0;
		int count = sscanf(pParam2, "%u", &val);

		if(!stricmp(pParam1, "A32BaseAddr") && count) A32BaseAddr = val;
			return kFALSE;

		return kTRUE;
	}

	void SetupRegisters()
	{
/*
		static RegMemDesc regs[] = {
			{"FirmwareRev",		REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
			{"BoardID",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
			{"TestPulseConfig",	REGMEM_DESC_FLAGS_HEX,		{0x0034, 0, 12, 32}},
			{"DAC",					REGMEM_DESC_FLAGS_UINT,		{0x0038, 0, 32, 32}},
		};
*/
#define VETROC_SDIOMUX_NAME_MAP	{\
												20,\
												{"0","1","FPIN1","FPIN2","FPIN3","FPIN4","FPIN5","FPIN6","FPIN7","FPIN8","TOKENFI","SYNCFI","TRIG1F","TRIG2F","StatAIn","StatBIn","0","0","PULSER","BUSY"},\
												{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}\
											}

		static RegMemDesc regs[] = {
			{"Config", 0},
				{"Spi", 0},
					{"WrData",		REGMEM_DESC_FLAGS_HEX,		{0x0010, 0, 8, 32}},
					{"RdData",		REGMEM_DESC_FLAGS_HEX,		{0x0014, 0, 8, 32}},
					{"NCSSet",		REGMEM_DESC_FLAGS_UINT,		{0x0010, 8, 1, 32}},
					{"NCSClear",	REGMEM_DESC_FLAGS_UINT,		{0x0010, 9, 1, 32}},
					{"Start",		REGMEM_DESC_FLAGS_UINT,		{0x0010, 10, 1, 32}},
					{"Done",			REGMEM_DESC_FLAGS_UINT,		{0x0014, 11, 1, 32}},
				{NULL, 0},
				{"Clk", 0},
					{"GTPASrc",		REGMEM_DESC_FLAGS_STRING,	{0x0008, 22, 2, 32}, {4,{"TI","NONE","LOCAL","SWB"}, {0,1,2,3}}},
					{"GTPBSrc",		REGMEM_DESC_FLAGS_STRING,	{0x0008, 24, 2, 32}, {4,{"TI","NONE","LOCAL","SWB"}, {0,1,2,3}}},
					{"FPGA",			REGMEM_DESC_FLAGS_STRING,	{0x0008, 26, 2, 32}, {4,{"TI","NONE","LOCAL","SWB"}, {0,1,2,3}}},
					{"TD",			REGMEM_DESC_FLAGS_STRING,	{0x0008, 28, 2, 32}, {4,{"TI","NONE","LOCAL","SWB"}, {0,1,2,3}}},
					{"PLLReset",	REGMEM_DESC_FLAGS_UINT,		{0x0008, 31, 1, 32}},
					{"PLLLocked",	REGMEM_DESC_FLAGS_UINT,		{0x000C, 17, 1, 32}},
				{NULL, 0},
				{"BoardId",			REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
				{"FirmwareRev",	REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
				{"SoftReset",		REGMEM_DESC_FLAGS_UINT,		{0x0018, 0, 1, 32}},
			{NULL, 0},
			{"Sd", 0},
				{"I/O Muxing", 0},
					{"FPOUT1",		REGMEM_DESC_FLAGS_STRING,	{0x0208, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT2",		REGMEM_DESC_FLAGS_STRING,	{0x020C, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT3",		REGMEM_DESC_FLAGS_STRING,	{0x0210, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT4",		REGMEM_DESC_FLAGS_STRING,	{0x0214, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT5",		REGMEM_DESC_FLAGS_STRING,	{0x0218, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT6",		REGMEM_DESC_FLAGS_STRING,	{0x021C, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT7",		REGMEM_DESC_FLAGS_STRING,	{0x0220, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"FPOUT8",		REGMEM_DESC_FLAGS_STRING,	{0x0224, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"TokenOut",	REGMEM_DESC_FLAGS_STRING,	{0x0228, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"TrigOut",		REGMEM_DESC_FLAGS_STRING,	{0x022C, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"SdLink",		REGMEM_DESC_FLAGS_STRING,	{0x0230, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"SwAStatus",	REGMEM_DESC_FLAGS_STRING,	{0x0234, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"BusyOut",		REGMEM_DESC_FLAGS_STRING,	{0x0238, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"Trig",			REGMEM_DESC_FLAGS_STRING,	{0x023C, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
					{"Sync",			REGMEM_DESC_FLAGS_STRING,	{0x0240, 0, 5, 32},	VETROC_SDIOMUX_NAME_MAP},
				{NULL, 0},
				{"Pulser", 0},
					{"Period",		REGMEM_DESC_FLAGS_UINT,		{0x0280, 0, 32, 32}},
					{"LowCycles",	REGMEM_DESC_FLAGS_UINT,		{0x0284, 0, 32, 32}},
					{"NPulses",		REGMEM_DESC_FLAGS_UINT,		{0x0288, 0, 32, 32}},
					{"Start",		REGMEM_DESC_FLAGS_UINT,		{0x028C, 0, 0, 32}},
					{"Done",			REGMEM_DESC_FLAGS_UINT,		{0x0290, 0, 1, 32}},
				{NULL, 0},
				{"Scalers", 0},
					{"Disable",		REGMEM_DESC_FLAGS_UINT,		{0x0300, 0, 1, 32}},
					{"Reset",		REGMEM_DESC_FLAGS_UINT,		{0x0300, 1, 1, 32}},
					{"GClk125",		REGMEM_DESC_FLAGS_UINT,		{0x0308, 0, 32, 32}},
					{"Sync",			REGMEM_DESC_FLAGS_UINT,		{0x030C, 0, 32, 32}},
					{"Trig",			REGMEM_DESC_FLAGS_UINT,		{0x0310, 0, 32, 32}},
					{"BusyCycles",	REGMEM_DESC_FLAGS_UINT,		{0x0314, 0, 32, 32}},
					{"FPIN1",		REGMEM_DESC_FLAGS_UINT,		{0x0318, 0, 32, 32}},
					{"FPIN2",		REGMEM_DESC_FLAGS_UINT,		{0x031C, 0, 32, 32}},
					{"FPIN3",		REGMEM_DESC_FLAGS_UINT,		{0x0320, 0, 32, 32}},
					{"FPIN4",		REGMEM_DESC_FLAGS_UINT,		{0x0324, 0, 32, 32}},
					{"FPIN5",		REGMEM_DESC_FLAGS_UINT,		{0x0328, 0, 32, 32}},
					{"FPIN6",		REGMEM_DESC_FLAGS_UINT,		{0x032C, 0, 32, 32}},
					{"FPIN7",		REGMEM_DESC_FLAGS_UINT,		{0x0330, 0, 32, 32}},
					{"FPIN8",		REGMEM_DESC_FLAGS_UINT,		{0x0334, 0, 32, 32}},
					{"TokenFI",		REGMEM_DESC_FLAGS_UINT,		{0x0338, 0, 32, 32}},
					{"SyncFI",		REGMEM_DESC_FLAGS_UINT,		{0x033C, 0, 32, 32}},
					{"Trig1F",		REGMEM_DESC_FLAGS_UINT,		{0x0340, 0, 32, 32}},
					{"Trig2F",		REGMEM_DESC_FLAGS_UINT,		{0x0344, 0, 32, 32}},
					{"StatAIn",		REGMEM_DESC_FLAGS_UINT,		{0x0348, 0, 32, 32}},
					{"StatBIn",		REGMEM_DESC_FLAGS_UINT,		{0x034C, 0, 32, 32}},
					{"FPOUT1",		REGMEM_DESC_FLAGS_UINT,		{0x0350, 0, 32, 32}},
					{"FPOUT2",		REGMEM_DESC_FLAGS_UINT,		{0x0354, 0, 32, 32}},
					{"FPOUT3",		REGMEM_DESC_FLAGS_UINT,		{0x0358, 0, 32, 32}},
					{"FPOUT4",		REGMEM_DESC_FLAGS_UINT,		{0x035C, 0, 32, 32}},
					{"FPOUT5",		REGMEM_DESC_FLAGS_UINT,		{0x0360, 0, 32, 32}},
					{"FPOUT6",		REGMEM_DESC_FLAGS_UINT,		{0x0364, 0, 32, 32}},
					{"FPOUT7",		REGMEM_DESC_FLAGS_UINT,		{0x0368, 0, 32, 32}},
					{"FPOUT8",		REGMEM_DESC_FLAGS_UINT,		{0x036C, 0, 32, 32}},
					{"TokenFO",		REGMEM_DESC_FLAGS_UINT,		{0x0370, 0, 32, 32}},
					{"TrigFO",		REGMEM_DESC_FLAGS_UINT,		{0x0374, 0, 32, 32}},
					{"SdLinkF",		REGMEM_DESC_FLAGS_UINT,		{0x0378, 0, 32, 32}},
					{"StatAOut",	REGMEM_DESC_FLAGS_UINT,		{0x037C, 0, 32, 32}},
					{"BusyOut",		REGMEM_DESC_FLAGS_UINT,		{0x0380, 0, 32, 32}},
					{"TDC0-15", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1080, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1084, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1088, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x108C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1090, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1094, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1098, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x109C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x10A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x10A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x10A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x10AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x10B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x10B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x10B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x10BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC16-31", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1180, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1184, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1188, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x118C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1190, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1194, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1198, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x119C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x11A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x11A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x11A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x11AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x11B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x11B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x11B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x11BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC32-47", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1280, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1284, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1288, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x128C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1290, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1294, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1298, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x129C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x12A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x12A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x12A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x12AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x12B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x12B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x12B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x12BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC48-63", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1380, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1384, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1388, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x138C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1390, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1394, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1398, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x139C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x13A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x13A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x13A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x13AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x13B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x13B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x13B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x13BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC64-79", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1480, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1484, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1488, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x148C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1490, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1494, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1498, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x149C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x14A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x14A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x14A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x14AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x14B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x14B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x14B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x14BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC80-95", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1580, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1584, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1588, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x158C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1590, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1594, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1598, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x159C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x15A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x15A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x15A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x15AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x15B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x15B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x15B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x15BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC96-111", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1680, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1684, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1688, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x168C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1690, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1694, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1698, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x169C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x16A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x16A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x16A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x16AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x16B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x16B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x16B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x16BC, 0, 32, 32}},
					{NULL, 0},
					{"TDC112-127", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1780, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1784, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1788, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x178C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1790, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1794, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1798, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x179C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x17A0, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x17A4, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x17A8, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x17AC, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x17B0, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x17B4, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x17B8, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x17BC, 0, 32, 32}},
					{NULL, 0},
				{NULL, 0},
			{NULL, 0},
			{"Event Builder", 0},
				{"Lookback",		REGMEM_DESC_FLAGS_UINT,		{0x2000, 0, 10, 32}},
				{"WindowWidth",	REGMEM_DESC_FLAGS_UINT,		{0x2004, 0, 10, 32}},
				{"BlockSize",		REGMEM_DESC_FLAGS_UINT,		{0x2008, 0, 8, 32}},
				{"Adr32Base",		REGMEM_DESC_FLAGS_HEX,		{0x200C, 7, 9, 32}},
				{"Adr32En",			REGMEM_DESC_FLAGS_UINT,		{0x200C, 0, 1, 32}},
				{"Adr32Mmin",		REGMEM_DESC_FLAGS_HEX,		{0x2010, 0, 9, 32}},
				{"Adr32Mmax",		REGMEM_DESC_FLAGS_HEX,		{0x2010, 16, 9, 32}},
				{"Adr32Men",		REGMEM_DESC_FLAGS_UINT,		{0x2010, 25, 1, 32}},
				{"TokenFirst",		REGMEM_DESC_FLAGS_UINT,		{0x2010, 26, 1, 32}},
				{"TokenLast",		REGMEM_DESC_FLAGS_UINT,		{0x2010, 27, 1, 32}},
				{"TokenTake",		REGMEM_DESC_FLAGS_UINT,		{0x2010, 28, 1, 32}},
				{"BerrEn",			REGMEM_DESC_FLAGS_UINT,		{0x2018, 0, 1, 32}},
				{"FifoBlockCnt",	REGMEM_DESC_FLAGS_UINT,		{0x2020, 0, 32, 32}},
				{"FifoWordCnt",	REGMEM_DESC_FLAGS_UINT,		{0x2024, 0, 32, 32}},
				{"FifoEventCnt",	REGMEM_DESC_FLAGS_UINT,		{0x2028, 0, 32, 32}},
				{"TrigCntBusy",	REGMEM_DESC_FLAGS_UINT,		{0x202C, 0, 8, 32}},
				{"SramAddr",		REGMEM_DESC_FLAGS_HEX,		{0x2030, 0, 19, 32}},
				{"SramDinL",		REGMEM_DESC_FLAGS_HEX,		{0x2034, 0, 32, 32}},
				{"SramDinH",		REGMEM_DESC_FLAGS_HEX,		{0x2038, 0, 4, 32}},
				{"SramDoutL",		REGMEM_DESC_FLAGS_HEX,		{0x203C, 0, 32, 32}},
				{"SramDoutH",		REGMEM_DESC_FLAGS_HEX,		{0x2040, 0, 4, 32}},
				{"SramCtrlWr",		REGMEM_DESC_FLAGS_HEX,		{0x2044, 0, 1, 32}},
				{"SramCtrlRd",		REGMEM_DESC_FLAGS_HEX,		{0x2044, 1, 1, 32}},
			{NULL, 0},
			{"TDC0-15", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1000, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1004, 0, 12, 32}},
			{NULL, 0},
			{"TDC16-31", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1100, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1104, 0, 12, 32}},
			{NULL, 0},
			{"TDC32-47", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1200, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1204, 0, 12, 32}},
			{NULL, 0},
			{"TDC48-63", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1300, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1304, 0, 12, 32}},
			{NULL, 0},
			{"TDC64-79", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1400, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1404, 0, 12, 32}},
			{NULL, 0},
			{"TDC80-95", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1500, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1504, 0, 12, 32}},
			{NULL, 0},
			{"TDC96-111", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1600, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1604, 0, 12, 32}},
			{NULL, 0},
			{"TDC112-127", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1700, 0, 16, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1704, 0, 12, 32}},
			{NULL, 0},
			{"Serdes", 0},
				{"Ctrl",				REGMEM_DESC_FLAGS_HEX,		{0x0400, 0, 32, 32}},
				{"Status",			REGMEM_DESC_FLAGS_HEX,		{0x0410, 0, 32, 32}},
			{NULL, 0},
		};
		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}
private:
	unsigned int	A32BaseAddr;
};

#endif
