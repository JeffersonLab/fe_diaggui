#ifndef FADC250Module_H
#define FADC250Module_H

#include "RootHeader.h"
//#include "FADC250_Status.h"
//#include "FADC250_EventHist.h"
#include "ModuleFrame.h"
//#include "FADC250_GTX.h"
#include "FADC250_TrgHist.h"
#include "FADC250_SerialScope.h"
#include "FADC250_AdcScope.h"

class FADC250Module	: public ModuleFrame
{
public:
	FADC250Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

		TGCompositeFrame *tFrame;
//		FADC250_Status *pStatus;

//		tFrame = pTabs->AddTab("Status");		tFrame->AddFrame(pStatus = new FADC250_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("GTX");			tFrame->AddFrame(new FADC250_GTX(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("TrgHist");		tFrame->AddFrame(new FADC250_TrgHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("VXS Scope");	tFrame->AddFrame(new FADC250_SerialScope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		for(int i = 0; i < 16; i++)
		{
			tFrame = pTabs->AddTab(Form("Ch%d", i));	tFrame->AddFrame(new FADC250_AdcScope(tFrame, this, i), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		}


		//		tFrame = pTabs->AddTab("EventHist");	tFrame->AddFrame(new FADC250_EventHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		strSlotIdentifier.Form("%d", ReadReg32((volatile unsigned int *)(BaseAddr+0x14))>>16);
	}


	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
				{"AdcParameters", 0},
					{"AdcThreshold", 0},
						{"tet0",				REGMEM_DESC_FLAGS_UINT,		{0x012C, 16, 12, 32}},
						{"tet1",				REGMEM_DESC_FLAGS_UINT,		{0x012C, 0, 12, 32}},
						{"tet2",				REGMEM_DESC_FLAGS_UINT,		{0x0130, 16, 12, 32}},
						{"tet3",				REGMEM_DESC_FLAGS_UINT,		{0x0130, 0, 12, 32}},
						{"tet4",				REGMEM_DESC_FLAGS_UINT,		{0x0134, 16, 12, 32}},
						{"tet5",				REGMEM_DESC_FLAGS_UINT,		{0x0134, 0, 12, 32}},
						{"tet6",				REGMEM_DESC_FLAGS_UINT,		{0x0138, 16, 12, 32}},
						{"tet7",				REGMEM_DESC_FLAGS_UINT,		{0x0138, 0, 12, 32}},
						{"tet8",				REGMEM_DESC_FLAGS_UINT,		{0x013C, 16, 12, 32}},
						{"tet9",				REGMEM_DESC_FLAGS_UINT,		{0x013C, 0, 12, 32}},
						{"tet10",			REGMEM_DESC_FLAGS_UINT,		{0x0140, 16, 12, 32}},
						{"tet11",			REGMEM_DESC_FLAGS_UINT,		{0x0140, 0, 12, 32}},
						{"tet12",			REGMEM_DESC_FLAGS_UINT,		{0x0144, 16, 12, 32}},
						{"tet13",			REGMEM_DESC_FLAGS_UINT,		{0x0144, 0, 12, 32}},
						{"tet14",			REGMEM_DESC_FLAGS_UINT,		{0x0148, 16, 12, 32}},
						{"tet15",			REGMEM_DESC_FLAGS_UINT,		{0x0148, 0, 12, 32}},
					{NULL, 0},
					{"AdcPedestal", 0},
						{"ped0",					REGMEM_DESC_FLAGS_UINT,		{0x0158, 0, 16, 32}},
						{"ped1",					REGMEM_DESC_FLAGS_UINT,		{0x015C, 0, 16, 32}},
						{"ped2",					REGMEM_DESC_FLAGS_UINT,		{0x0160, 0, 16, 32}},
						{"ped3",					REGMEM_DESC_FLAGS_UINT,		{0x0164, 0, 16, 32}},
						{"ped4",					REGMEM_DESC_FLAGS_UINT,		{0x0168, 0, 16, 32}},
						{"ped5",					REGMEM_DESC_FLAGS_UINT,		{0x016C, 0, 16, 32}},
						{"ped6",					REGMEM_DESC_FLAGS_UINT,		{0x0170, 0, 16, 32}},
						{"ped7",					REGMEM_DESC_FLAGS_UINT,		{0x0174, 0, 16, 32}},
						{"ped8",					REGMEM_DESC_FLAGS_UINT,		{0x0178, 0, 16, 32}},
						{"ped9",					REGMEM_DESC_FLAGS_UINT,		{0x017C, 0, 16, 32}},
						{"ped10",				REGMEM_DESC_FLAGS_UINT,		{0x0180, 0, 16, 32}},
						{"ped11",				REGMEM_DESC_FLAGS_UINT,		{0x0184, 0, 16, 32}},
						{"ped12",				REGMEM_DESC_FLAGS_UINT,		{0x0188, 0, 16, 32}},
						{"ped13",				REGMEM_DESC_FLAGS_UINT,		{0x018C, 0, 16, 32}},
						{"ped14",				REGMEM_DESC_FLAGS_UINT,		{0x0190, 0, 16, 32}},
						{"ped15",				REGMEM_DESC_FLAGS_UINT,		{0x0194, 0, 16, 32}},
					{NULL, 0},
					{"AdcGain", 0},
						{"gain0",				REGMEM_DESC_FLAGS_UINT,		{0x0198, 0, 16, 32}},
						{"gain1",				REGMEM_DESC_FLAGS_UINT,		{0x019C, 0, 16, 32}},
						{"gain2",				REGMEM_DESC_FLAGS_UINT,		{0x01A0, 0, 16, 32}},
						{"gain3",				REGMEM_DESC_FLAGS_UINT,		{0x01A4, 0, 16, 32}},
						{"gain4",				REGMEM_DESC_FLAGS_UINT,		{0x01A8, 0, 16, 32}},
						{"gain5",				REGMEM_DESC_FLAGS_UINT,		{0x01AC, 0, 16, 32}},
						{"gain6",				REGMEM_DESC_FLAGS_UINT,		{0x01B0, 0, 16, 32}},
						{"gain7",				REGMEM_DESC_FLAGS_UINT,		{0x01B4, 0, 16, 32}},
						{"gain8",				REGMEM_DESC_FLAGS_UINT,		{0x01B8, 0, 16, 32}},
						{"gain9",				REGMEM_DESC_FLAGS_UINT,		{0x01BC, 0, 16, 32}},
						{"gain10",				REGMEM_DESC_FLAGS_UINT,		{0x01C0, 0, 16, 32}},
						{"gain11",				REGMEM_DESC_FLAGS_UINT,		{0x01C4, 0, 16, 32}},
						{"gain12",				REGMEM_DESC_FLAGS_UINT,		{0x01C8, 0, 16, 32}},
						{"gain13",				REGMEM_DESC_FLAGS_UINT,		{0x01CC, 0, 16, 32}},
						{"gain14",				REGMEM_DESC_FLAGS_UINT,		{0x01D0, 0, 16, 32}},
						{"gain15",				REGMEM_DESC_FLAGS_UINT,		{0x01D4, 0, 16, 32}},
					{NULL, 0},
					{"Dac", 0},
						{"dac0",					REGMEM_DESC_FLAGS_UINT,		{0x0050, 16, 16, 32}},
						{"dac1",					REGMEM_DESC_FLAGS_UINT,		{0x0050, 0, 16, 32}},
						{"dac2",					REGMEM_DESC_FLAGS_UINT,		{0x0054, 16, 16, 32}},
						{"dac3",					REGMEM_DESC_FLAGS_UINT,		{0x0054, 0, 16, 32}},
						{"dac4",					REGMEM_DESC_FLAGS_UINT,		{0x0058, 16, 16, 32}},
						{"dac5",					REGMEM_DESC_FLAGS_UINT,		{0x0058, 0, 16, 32}},
						{"dac6",					REGMEM_DESC_FLAGS_UINT,		{0x005C, 16, 16, 32}},
						{"dac7",					REGMEM_DESC_FLAGS_UINT,		{0x005C, 0, 16, 32}},
						{"dac8",					REGMEM_DESC_FLAGS_UINT,		{0x0060, 16, 16, 32}},
						{"dac9",					REGMEM_DESC_FLAGS_UINT,		{0x0060, 0, 16, 32}},
						{"dac10",				REGMEM_DESC_FLAGS_UINT,		{0x0064, 16, 16, 32}},
						{"dac11",				REGMEM_DESC_FLAGS_UINT,		{0x0064, 0, 16, 32}},
						{"dac12",				REGMEM_DESC_FLAGS_UINT,		{0x0068, 16, 16, 32}},
						{"dac13",				REGMEM_DESC_FLAGS_UINT,		{0x0068, 0, 16, 32}},
						{"dac14",				REGMEM_DESC_FLAGS_UINT,		{0x006C, 16, 16, 32}},
						{"dac15",				REGMEM_DESC_FLAGS_UINT,		{0x006C, 0, 16, 32}},
					{NULL, 0},
					{"ptw",						REGMEM_DESC_FLAGS_UINT,		{0x011C, 0, 9, 32}},
					{"pl",						REGMEM_DESC_FLAGS_UINT,		{0x0120, 0, 10, 32}},
					{"nsb",						REGMEM_DESC_FLAGS_UINT,		{0x0124, 0, 9, 32}},
					{"nsa",						REGMEM_DESC_FLAGS_UINT,		{0x0128, 0, 9, 32}},
				{NULL, 0},
				{"Scalers", 0},
					{"enable",					REGMEM_DESC_FLAGS_UINT,		{0x00E0, 0, 1, 32}},
					{"latch",					REGMEM_DESC_FLAGS_UINT,		{0x00E0, 1, 1, 32}},
					{"reset",					REGMEM_DESC_FLAGS_UINT,		{0x00E0, 2, 1, 32}},
					{"trig_scal",				REGMEM_DESC_FLAGS_UINT,		{0x0030, 0, 32, 32}},
					{"ev_count",				REGMEM_DESC_FLAGS_UINT,		{0x0034, 0, 32, 32}},
					{"blk_count",				REGMEM_DESC_FLAGS_UINT,		{0x0038, 0, 32, 32}},
					{"blk_fifo_count",		REGMEM_DESC_FLAGS_UINT,		{0x003C, 0, 32, 32}},
					{"blk_wrdcnt_fifo",		REGMEM_DESC_FLAGS_UINT,		{0x0040, 0, 32, 32}},
					{"internal_trig_scal",	REGMEM_DESC_FLAGS_UINT,		{0x0044, 0, 32, 32}},
					{"ram_word_count",		REGMEM_DESC_FLAGS_UINT,		{0x0048, 0, 32, 32}},
					{"berr_module_scal",		REGMEM_DESC_FLAGS_UINT,		{0x00A0, 0, 32, 32}},
					{"berr_crate_scal",		REGMEM_DESC_FLAGS_UINT,		{0x00A4, 0, 32, 32}},
					{"proc_words_scal",		REGMEM_DESC_FLAGS_UINT,		{0x00A8, 0, 32, 32}},
					{"aux_scal2",				REGMEM_DESC_FLAGS_UINT,		{0x00AC, 0, 32, 32}},
					{"header_scal",			REGMEM_DESC_FLAGS_UINT,		{0x00B0, 0, 32, 32}},
					{"trig2_scal",				REGMEM_DESC_FLAGS_UINT,		{0x00B4, 0, 32, 32}},
					{"trailer_scal",			REGMEM_DESC_FLAGS_UINT,		{0x00B8, 0, 32, 32}},
					{"syncreset_scal",		REGMEM_DESC_FLAGS_UINT,		{0x00BC, 0, 32, 32}},
					{"scaler_ctrl",			REGMEM_DESC_FLAGS_UINT,		{0x00E0, 0, 32, 32}},
					{"scaler_interval",		REGMEM_DESC_FLAGS_UINT,		{0x00F0, 0, 32, 32}},
					{"time_count",				REGMEM_DESC_FLAGS_UINT,		{0x0340, 0, 32, 32}},
					{"clock250count",			REGMEM_DESC_FLAGS_UINT,		{0x0404, 0, 32, 32}},
					{"syncp0count",			REGMEM_DESC_FLAGS_UINT,		{0x0408, 0, 32, 32}},
					{"trig1p0count",			REGMEM_DESC_FLAGS_UINT,		{0x040C, 0, 32, 32}},
					{"trig2p0count",			REGMEM_DESC_FLAGS_UINT,		{0x0410, 0, 32, 32}},
					{"scaler0",					REGMEM_DESC_FLAGS_UINT,		{0x0300, 0, 32, 32}},
					{"scaler1",					REGMEM_DESC_FLAGS_UINT,		{0x0304, 0, 32, 32}},
					{"scaler2",					REGMEM_DESC_FLAGS_UINT,		{0x0308, 0, 32, 32}},
					{"scaler3",					REGMEM_DESC_FLAGS_UINT,		{0x030C, 0, 32, 32}},
					{"scaler4",					REGMEM_DESC_FLAGS_UINT,		{0x0310, 0, 32, 32}},
					{"scaler5",					REGMEM_DESC_FLAGS_UINT,		{0x0314, 0, 32, 32}},
					{"scaler6",					REGMEM_DESC_FLAGS_UINT,		{0x0318, 0, 32, 32}},
					{"scaler7",					REGMEM_DESC_FLAGS_UINT,		{0x031C, 0, 32, 32}},
					{"scaler8",					REGMEM_DESC_FLAGS_UINT,		{0x0320, 0, 32, 32}},
					{"scaler9",					REGMEM_DESC_FLAGS_UINT,		{0x0324, 0, 32, 32}},
					{"scaler10",				REGMEM_DESC_FLAGS_UINT,		{0x0328, 0, 32, 32}},
					{"scaler11",				REGMEM_DESC_FLAGS_UINT,		{0x032C, 0, 32, 32}},
					{"scaler12",				REGMEM_DESC_FLAGS_UINT,		{0x0330, 0, 32, 32}},
					{"scaler13",				REGMEM_DESC_FLAGS_UINT,		{0x0334, 0, 32, 32}},
					{"scaler14",				REGMEM_DESC_FLAGS_UINT,		{0x0338, 0, 32, 32}},
					{"scaler15",				REGMEM_DESC_FLAGS_UINT,		{0x033C, 0, 32, 32}},
				{NULL, 0},
				{"CTP(SWA:lanes2-3)", 0},
					{"Drp", 0},
						{"WrEn",					REGMEM_DESC_FLAGS_UINT,		{0x050C, 24, 1, 32}},
						{"DenTile0",			REGMEM_DESC_FLAGS_UINT,		{0x050C, 25, 1, 32}},
						{"Addr",					REGMEM_DESC_FLAGS_HEX,		{0x050C, 16, 7, 32}},
						{"WrData",				REGMEM_DESC_FLAGS_HEX,		{0x050C, 0, 16, 32}},
						{"RdData",				REGMEM_DESC_FLAGS_UINT,		{0x0510, 0, 16, 32}},
						{"RdDataValid",		REGMEM_DESC_FLAGS_UINT,		{0x0510, 16, 1, 32}},
					{NULL, 0},
					{"Settings", 0},
						{"Loopback",			REGMEM_DESC_FLAGS_STRING,	{0x0500, 2, 3, 32},	{5,{"DISABLED","NEARPCS","NEARPMA","FARPMA","FARPCS"},{0,1,2,4,6}}},
						{"RxEnPrbs",			REGMEM_DESC_FLAGS_STRING,	{0x0500, 5, 2, 32},	{4,{"DISABLED","PRBS7","PRBS23","PRBS31"},{0,1,2,3}}},
						{"TxEnPrbs",			REGMEM_DESC_FLAGS_STRING,	{0x0500, 7, 2, 32},	{4,{"DISABLED","PRBS7","PRBS23","PRBS31"},{0,1,2,3}}},
						{"RxEqMix0",			REGMEM_DESC_FLAGS_STRING,	{0x0504, 0, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp0",			REGMEM_DESC_FLAGS_STRING,	{0x0504, 2, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff0",			REGMEM_DESC_FLAGS_UINT,		{0x0504, 6, 3, 32}},
						{"TxDiffCtrl0",		REGMEM_DESC_FLAGS_STRING,	{0x0504, 9, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix1",			REGMEM_DESC_FLAGS_STRING,	{0x0504, 16, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp1",			REGMEM_DESC_FLAGS_STRING,	{0x0504, 18, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff1",			REGMEM_DESC_FLAGS_UINT,		{0x0504, 22, 3, 32}},
						{"TxDiffCtrl1",		REGMEM_DESC_FLAGS_STRING,	{0x0504, 25, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
					{NULL, 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x0500, 0, 1, 32}},
					{"GTReset",					REGMEM_DESC_FLAGS_UINT,		{0x0500, 1, 1, 32}},
					{"LinkReset",				REGMEM_DESC_FLAGS_UINT,		{0x0500, 9, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x0500, 10, 1, 32}},
					{"BitErrCntEn",			REGMEM_DESC_FLAGS_UINT,		{0x0500, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x0514, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x0514, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x0508, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x0508, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x0508, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x0508, 5, 1, 32}},
					{"RxPolarity0",			REGMEM_DESC_FLAGS_UINT,		{0x0508, 8, 1, 32}},
					{"RxPolarity1",			REGMEM_DESC_FLAGS_UINT,		{0x0508, 9, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x0508, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x0508, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x0508, 14, 1, 32}},
				{NULL, 0},
				{"CSR", 0},
					{"ClearModule",			REGMEM_DESC_FLAGS_HEX,		{0x0004, 21, 1, 32}},
					{"SyncReset",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 28, 1, 32}},
					{"Trigger1",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 29, 1, 32}},
					{"SoftReset",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 30, 1, 32}},
					{"HardReset",				REGMEM_DESC_FLAGS_HEX,		{0x0004, 31, 1, 32}},
				{NULL, 0},
				{"CTRL1", 0},
					{"ClkSource",				REGMEM_DESC_FLAGS_STRING,	{0x0008, 0, 2, 32}, {4,{"INT","FP","P0","P0"},{0,1,2,3}}},
					{"IntClkEnable",			REGMEM_DESC_FLAGS_HEX,		{0x0008, 3, 1, 32}},
					{"TrigSource",				REGMEM_DESC_FLAGS_STRING,	{0x0008, 4, 3, 32}, {7,{"FP-ASYNC","FP-SYNC","P0-ASYNC","P0-SYNC","SW-T2+dT1","SW-T1","INT"},{0,1,2,3,5,6,7}}},
					{"TrigSoftEnable",		REGMEM_DESC_FLAGS_HEX,		{0x0008, 7, 1, 32}},
					{"SyncSource",				REGMEM_DESC_FLAGS_STRING,	{0x0008, 8, 3, 32}, {5,{"FP-ASYNC","FP-SYNC","P0-ASYNC","P0-SYNC","SW"},{0,1,2,3,6}}},
					{"SyncSoftEnable",		REGMEM_DESC_FLAGS_HEX,		{0x0008, 11, 1, 32}},
				{NULL, 0},
				{"CTRL2", 0},
					{"Go",						REGMEM_DESC_FLAGS_HEX,		{0x000C, 0, 1, 32}},
					{"TrigEnable",				REGMEM_DESC_FLAGS_HEX,		{0x000C, 1, 1, 32}},
					{"SyncEnable",				REGMEM_DESC_FLAGS_HEX,		{0x000C, 2, 1, 32}},
				{NULL, 0},
				{"Reset", 0},
					{"HardResetCtrl",			REGMEM_DESC_FLAGS_HEX,		{0x0002C, 0, 1, 32}},
					{"HardResetAdc",			REGMEM_DESC_FLAGS_HEX,		{0x0002C, 1, 1, 32}},
					{"SoftResetCtrl",			REGMEM_DESC_FLAGS_HEX,		{0x0002C, 4, 1, 32}},
					{"SoftResetAdc",			REGMEM_DESC_FLAGS_HEX,		{0x0002C, 5, 1, 32}},
					{"ResetAdcFifo",			REGMEM_DESC_FLAGS_HEX,		{0x0002C, 8, 1, 32}},
					{"ResetHitsumFifo",		REGMEM_DESC_FLAGS_HEX,		{0x0002C, 10, 1, 32}},
					{"ResetDac",				REGMEM_DESC_FLAGS_HEX,		{0x0002C, 11, 1, 32}},
					{"ResetRam",				REGMEM_DESC_FLAGS_HEX,		{0x0002C, 12, 1, 32}},
				{NULL, 0},
				{"Misc", 0},
					{"version",					REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
					{"csr",						REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
					{"ctrl1",					REGMEM_DESC_FLAGS_HEX,		{0x0008, 0, 32, 32}},
					{"ctrl2",					REGMEM_DESC_FLAGS_HEX,		{0x000C, 0, 32, 32}},
					{"blk_level",				REGMEM_DESC_FLAGS_UINT,		{0x0010, 0, 32, 32}},
					{"itrig_cfg",				REGMEM_DESC_FLAGS_HEX,		{0x0028, 0, 32, 32}},
					{"reset",					REGMEM_DESC_FLAGS_HEX,		{0x002C, 0, 32, 32}},
					{"dataflow_status",		REGMEM_DESC_FLAGS_HEX,		{0x004C, 0, 32, 32}},
					{"status0",					REGMEM_DESC_FLAGS_HEX,		{0x0070, 0, 32, 32}},
					{"status1",					REGMEM_DESC_FLAGS_HEX,		{0x0074, 0, 32, 32}},
					{"status2",					REGMEM_DESC_FLAGS_HEX,		{0x0078, 0, 32, 32}},
					{"status3",					REGMEM_DESC_FLAGS_HEX,		{0x007C, 0, 32, 32}},
					{"busy_level",				REGMEM_DESC_FLAGS_UINT,		{0x00C0, 0, 32, 32}},
					{"serial0",					REGMEM_DESC_FLAGS_HEX,		{0x00E4, 0, 32, 32}},
					{"serial1",					REGMEM_DESC_FLAGS_HEX,		{0x00E8, 0, 32, 32}},
					{"serial2",					REGMEM_DESC_FLAGS_HEX,		{0x00EC, 0, 32, 32}},
					{"adc_status0",			REGMEM_DESC_FLAGS_HEX,		{0x0100, 0, 32, 32}},
					{"adc_status1",			REGMEM_DESC_FLAGS_HEX,		{0x0104, 0, 32, 32}},
					{"adc_status2",			REGMEM_DESC_FLAGS_HEX,		{0x0108, 0, 32, 32}},
					{"adc_config0",			REGMEM_DESC_FLAGS_HEX,		{0x010C, 0, 32, 32}},
					{"adc_config1",			REGMEM_DESC_FLAGS_HEX,		{0x0110, 0, 32, 32}},
					{"adc_config2",			REGMEM_DESC_FLAGS_HEX,		{0x0114, 0, 32, 32}},
					{"adc_config3",			REGMEM_DESC_FLAGS_HEX,		{0x0118, 0, 32, 32}},
					{"ptw_last_adr",			REGMEM_DESC_FLAGS_UINT,		{0x014C, 0, 32, 32}},
					{"ptw_max_buf",			REGMEM_DESC_FLAGS_UINT,		{0x0150, 0, 32, 32}},
					{"adc_test_data",			REGMEM_DESC_FLAGS_HEX,		{0x0154, 0, 32, 32}},
					{"gtx_ctrl",				REGMEM_DESC_FLAGS_HEX,		{0x0500, 0, 32, 32}},
					{"gtx_ctrl_tile",			REGMEM_DESC_FLAGS_HEX,		{0x0504, 0, 32, 32}},
					{"gtx_status",				REGMEM_DESC_FLAGS_HEX,		{0x0508, 0, 32, 32}},
					{"gtx_err",					REGMEM_DESC_FLAGS_HEX,		{0x0514, 0, 32, 32}},
					{"gtx_drp_ctrl",			REGMEM_DESC_FLAGS_HEX,		{0x050C, 0, 32, 32}},
					{"gtx_drp_status",		REGMEM_DESC_FLAGS_HEX,		{0x0510, 0, 32, 32}},
				{NULL, 0}
		};
		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "FADC250"; }
	const char *GetModuleFullName() { return "Flash ADC 250Msps"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString				strSlotIdentifier;
	TGTab				*pTabs;
};

#endif
