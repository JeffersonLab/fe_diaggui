#ifndef DCRBModule_H
#define DCRBModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
//#include "DCRB_Status.h"
//#include "DCRB_Scalers.h"
//#include "DCRB_TDCPlots.h"
#include "DCRB_Testing.h"
//#include "DCRB_NoisePlots.h"
//#include "DCRB_GTP.h"

class DCRBModule	: public ModuleFrame
{
public:
	DCRBModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGTab *pTabs;

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("NoisePlots");	tFrame->AddFrame(new DCRB_NoisePlots(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("TDCPlots");		tFrame->AddFrame(new DCRB_TDCPlots(tFrame, this, A32BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("GTP");			tFrame->AddFrame(new DCRB_GTP(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Scalers");		tFrame->AddFrame(new DCRB_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Status");		tFrame->AddFrame(new DCRB_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("Testing");		tFrame->AddFrame(new DCRB_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		
		strSlotIdentifier.Form("%d", (ReadReg32((volatile unsigned int *)(BaseAddr+0x0004))>>24) & 0x1F);
	}

	const char *GetModuleName() { return "DCRB"; }
	const char *GetModuleFullName() { return "Drift Chamber Readout Board"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;

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
/*
		static RegMemDesc regs[] = {
			{"FirmwareRev",		REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
			{"BoardID",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
			{"TestPulseConfig",	REGMEM_DESC_FLAGS_HEX,		{0x0034, 0, 12, 32}},
			{"DAC",					REGMEM_DESC_FLAGS_UINT,		{0x0038, 0, 32, 32}},
		};
*/
#define DCRB_SDIOMUX_NAME_MAP		{\
											7,\
											{"0","1","SYNC","TRIG1","TRIG2","PULSER","BUSY"},\
											{0,1,2,3,4,18,19}\
										}

		static RegMemDesc regs[] = {
			{"Config", 0},
				{"Spi", 0},
					{"WrData",		REGMEM_DESC_FLAGS_HEX,		{0x0008, 0, 8, 32}},
					{"RdData",		REGMEM_DESC_FLAGS_HEX,		{0x000C, 0, 8, 32}},
					{"NCSSet",		REGMEM_DESC_FLAGS_UINT,		{0x0008, 8, 1, 32}},
					{"NCSClear",	REGMEM_DESC_FLAGS_UINT,		{0x0008, 9, 1, 32}},
					{"Start",		REGMEM_DESC_FLAGS_UINT,		{0x0008, 10, 1, 32}},
					{"Done",			REGMEM_DESC_FLAGS_UINT,		{0x000C, 11, 1, 32}},
				{NULL, 0},
				{"DAC", 0},
					{"Threshold",	REGMEM_DESC_FLAGS_UINT,		{0x0024, 0, 12, 32}},
					{"Low",			REGMEM_DESC_FLAGS_UINT,		{0x0028, 0, 12, 32}},
					{"High",			REGMEM_DESC_FLAGS_UINT,		{0x002C, 0, 12, 32}},
					{"Offset",		REGMEM_DESC_FLAGS_UINT,		{0x0030, 0, 12, 32}},
				{NULL, 0},
				{"BoardId",			REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
				{"FirmwareRev",	REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
				{"SoftReset",		REGMEM_DESC_FLAGS_UINT,		{0x0020, 0, 1, 32}},
			{NULL, 0},
			{"Clk", 0},
				{"ClkPllReset",	REGMEM_DESC_FLAGS_UINT,		{0x0100, 31, 1, 32}},
				{"ClkSel",			REGMEM_DESC_FLAGS_STRING,	{0x0100, 30, 1, 32}, {2,{"LCLK","SWCLK"}, {0,1}}},
				{"ClkPllLocked",	REGMEM_DESC_FLAGS_UINT,		{0x0104, 17, 1, 32}},
			{NULL, 0},
			{"Sd", 0},
				{"I/O Muxing", 0},
					{"DCE0",			REGMEM_DESC_FLAGS_STRING,	{0x0200, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"DCE1",			REGMEM_DESC_FLAGS_STRING,	{0x0204, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"DCE2",			REGMEM_DESC_FLAGS_STRING,	{0x0208, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"FCE0",			REGMEM_DESC_FLAGS_STRING,	{0x020C, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"FCE1",			REGMEM_DESC_FLAGS_STRING,	{0x0210, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"FCE2",			REGMEM_DESC_FLAGS_STRING,	{0x0214, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"SwAGpio0",	REGMEM_DESC_FLAGS_STRING,	{0x0218, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"SwBGpio0",	REGMEM_DESC_FLAGS_STRING,	{0x021C, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"TrigOut",		REGMEM_DESC_FLAGS_STRING,	{0x0220, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"SdLink",		REGMEM_DESC_FLAGS_STRING,	{0x0224, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"TokenOut",	REGMEM_DESC_FLAGS_STRING,	{0x0228, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"TokenIn",		REGMEM_DESC_FLAGS_STRING,	{0x022C, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"Trig",			REGMEM_DESC_FLAGS_STRING,	{0x023C, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
					{"Sync",			REGMEM_DESC_FLAGS_STRING,	{0x0240, 0, 5, 32},	DCRB_SDIOMUX_NAME_MAP},
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
					{"SysClk50",	REGMEM_DESC_FLAGS_UINT,		{0x0304, 0, 32, 32}},
					{"GClk125",		REGMEM_DESC_FLAGS_UINT,		{0x0308, 0, 32, 32}},
					{"Sync",			REGMEM_DESC_FLAGS_UINT,		{0x030C, 0, 32, 32}},
					{"Trig1",		REGMEM_DESC_FLAGS_UINT,		{0x0310, 0, 32, 32}},
					{"Trig2",		REGMEM_DESC_FLAGS_UINT,		{0x0314, 0, 32, 32}},
					{"SwAGpio1",	REGMEM_DESC_FLAGS_UINT,		{0x033C, 0, 32, 32}},
					{"SwBGpio1",	REGMEM_DESC_FLAGS_UINT,		{0x0340, 0, 32, 32}},
					{"TokenIn",		REGMEM_DESC_FLAGS_UINT,		{0x0344, 0, 32, 32}},
					{"Busy",			REGMEM_DESC_FLAGS_UINT,		{0x0348, 0, 32, 32}},
					{"BusyCycles",	REGMEM_DESC_FLAGS_UINT,		{0x034C, 0, 32, 32}},				
					{"TDC0-15", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1100, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1104, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1108, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x110C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1110, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1114, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1118, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x111C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x1120, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x1124, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x1128, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x112C, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x1130, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x1134, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x1138, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x113C, 0, 32, 32}},
					{NULL, 0},
					{"TDC16-31", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1300, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1304, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1308, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x130C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1310, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1314, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1318, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x131C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x1320, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x1324, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x1328, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x132C, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x1330, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x1334, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x1338, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x133C, 0, 32, 32}},
					{NULL, 0},
					{"TDC32-47", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1500, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1504, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1508, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x150C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1510, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1514, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1518, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x151C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x1520, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x1524, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x1528, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x152C, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x1530, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x1534, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x1538, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x153C, 0, 32, 32}},
					{NULL, 0},
					{"TDC48-63", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1700, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1704, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1708, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x170C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1710, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1714, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1718, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x171C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x1720, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x1724, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x1728, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x172C, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x1730, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x1734, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x1738, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x173C, 0, 32, 32}},
					{NULL, 0},
					{"TDC64-79", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1900, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1904, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1908, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x190C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1910, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1914, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1918, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x191C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x1920, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x1924, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x1928, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x192C, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x1930, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x1934, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x1938, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x193C, 0, 32, 32}},
					{NULL, 0},
					{"TDC80-95", 0},
						{"TDC0",		REGMEM_DESC_FLAGS_UINT,		{0x1B00, 0, 32, 32}},
						{"TDC1",		REGMEM_DESC_FLAGS_UINT,		{0x1B04, 0, 32, 32}},
						{"TDC2",		REGMEM_DESC_FLAGS_UINT,		{0x1B08, 0, 32, 32}},
						{"TDC3",		REGMEM_DESC_FLAGS_UINT,		{0x1B0C, 0, 32, 32}},
						{"TDC4",		REGMEM_DESC_FLAGS_UINT,		{0x1B10, 0, 32, 32}},
						{"TDC5",		REGMEM_DESC_FLAGS_UINT,		{0x1B14, 0, 32, 32}},
						{"TDC6",		REGMEM_DESC_FLAGS_UINT,		{0x1B18, 0, 32, 32}},
						{"TDC7",		REGMEM_DESC_FLAGS_UINT,		{0x1B1C, 0, 32, 32}},
						{"TDC8",		REGMEM_DESC_FLAGS_UINT,		{0x1B20, 0, 32, 32}},
						{"TDC9",		REGMEM_DESC_FLAGS_UINT,		{0x1B24, 0, 32, 32}},
						{"TDC10",	REGMEM_DESC_FLAGS_UINT,		{0x1B28, 0, 32, 32}},
						{"TDC11",	REGMEM_DESC_FLAGS_UINT,		{0x1B2C, 0, 32, 32}},
						{"TDC12",	REGMEM_DESC_FLAGS_UINT,		{0x1B30, 0, 32, 32}},
						{"TDC13",	REGMEM_DESC_FLAGS_UINT,		{0x1B34, 0, 32, 32}},
						{"TDC14",	REGMEM_DESC_FLAGS_UINT,		{0x1B38, 0, 32, 32}},
						{"TDC15",	REGMEM_DESC_FLAGS_UINT,		{0x1B3C, 0, 32, 32}},
					{NULL, 0},
				{NULL, 0},
			{NULL, 0},
			{"Event Builder", 0},
				{"Lookback",		REGMEM_DESC_FLAGS_UINT,		{0x0400, 0, 10, 32}},
				{"WindowWidth",	REGMEM_DESC_FLAGS_UINT,		{0x0404, 0, 10, 32}},
				{"BlockSize",		REGMEM_DESC_FLAGS_UINT,		{0x0408, 0, 8, 32}},
				{"Adr32Base",		REGMEM_DESC_FLAGS_HEX,		{0x040C, 7, 9, 32}},
				{"Adr32En",			REGMEM_DESC_FLAGS_UINT,		{0x040C, 0, 1, 32}},
				{"Adr32Mmin",		REGMEM_DESC_FLAGS_HEX,		{0x0410, 0, 9, 32}},
				{"Adr32Mmax",		REGMEM_DESC_FLAGS_HEX,		{0x0410, 16, 9, 32}},
				{"Adr32Men",		REGMEM_DESC_FLAGS_UINT,		{0x0410, 25, 1, 32}},
				{"TokenFirst",		REGMEM_DESC_FLAGS_UINT,		{0x0410, 26, 1, 32}},
				{"TokenLast",		REGMEM_DESC_FLAGS_UINT,		{0x0410, 27, 1, 32}},
				{"TokenTake",		REGMEM_DESC_FLAGS_UINT,		{0x0410, 28, 1, 32}},
				{"BerrEn",			REGMEM_DESC_FLAGS_UINT,		{0x0418, 0, 1, 32}},
				{"FifoBlockCnt",	REGMEM_DESC_FLAGS_UINT,		{0x0420, 0, 32, 32}},
				{"FifoWordCnt",	REGMEM_DESC_FLAGS_UINT,		{0x0424, 0, 32, 32}},
				{"FifoEventCnt",	REGMEM_DESC_FLAGS_UINT,		{0x0428, 0, 32, 32}},
				{"TrigCntBusy",	REGMEM_DESC_FLAGS_UINT,		{0x042C, 0, 8, 32}},
				{"SramAddr",		REGMEM_DESC_FLAGS_HEX,		{0x0430, 0, 19, 32}},
				{"SramDinL",		REGMEM_DESC_FLAGS_HEX,		{0x0434, 0, 32, 32}},
				{"SramDinH",		REGMEM_DESC_FLAGS_HEX,		{0x0438, 0, 4, 32}},
				{"SramDoutL",		REGMEM_DESC_FLAGS_HEX,		{0x043C, 0, 32, 32}},
				{"SramDoutH",		REGMEM_DESC_FLAGS_HEX,		{0x0440, 0, 4, 32}},
				{"SramCtrlWr",		REGMEM_DESC_FLAGS_HEX,		{0x0444, 0, 1, 32}},
				{"SramCtrlRd",		REGMEM_DESC_FLAGS_HEX,		{0x0444, 1, 1, 32}},
			{NULL, 0},
			{"TDC0-15", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1000, 0, 16, 32}},
				{"DeadCycles",		REGMEM_DESC_FLAGS_UINT,		{0x1004, 0, 8, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1008, 0, 12, 32}},
			{NULL, 0},
			{"TDC16-31", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1200, 0, 16, 32}},
				{"DeadCycles",		REGMEM_DESC_FLAGS_UINT,		{0x1204, 0, 8, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1208, 0, 12, 32}},
			{NULL, 0},
			{"TDC32-47", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1400, 0, 16, 32}},
				{"DeadCycles",		REGMEM_DESC_FLAGS_UINT,		{0x1404, 0, 8, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1408, 0, 12, 32}},
			{NULL, 0},
			{"TDC48-63", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1600, 0, 16, 32}},
				{"DeadCycles",		REGMEM_DESC_FLAGS_UINT,		{0x1604, 0, 8, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1608, 0, 12, 32}},
			{NULL, 0},
			{"TDC64-79", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1800, 0, 16, 32}},
				{"DeadCycles",		REGMEM_DESC_FLAGS_UINT,		{0x1804, 0, 8, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1808, 0, 12, 32}},
			{NULL, 0},
			{"TDC80-95", 0},
				{"EnableN",			REGMEM_DESC_FLAGS_HEX,		{0x1A00, 0, 16, 32}},
				{"DeadCycles",		REGMEM_DESC_FLAGS_UINT,		{0x1A04, 0, 8, 32}},
				{"TrigWidth",		REGMEM_DESC_FLAGS_UINT,		{0x1A08, 0, 12, 32}},
			{NULL, 0},
		};
		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}
private:
	unsigned int	A32BaseAddr;
};

#endif
