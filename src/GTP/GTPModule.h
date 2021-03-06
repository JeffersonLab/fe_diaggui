#ifndef GTPModule_H
#define GTPModule_H

#include "RootHeader.h"
#include "GTP_Status.h"
#include "GTP_WaveCapture.h"
#include "GTP_DCTrigger.h"
#include "GTP_SSHitPattern.h"
#include "GTP_SSFCal.h"
#include "GTP_SSBCal.h"
#include "GTP_SS_Scalers.h"
#include "GTP_TriggerBit.h"
#include "GTP_Serial.h"
#include "GTP_SerialScope.h"
#include "GTP_Scope.h"
#include "ModuleFrame.h"
#include "gtp.h"

class GTPModule	: public ModuleFrame
{
public:
	GTPModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pGTPTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

		tFrame = pGTPTabs->AddTab("PP1 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP3 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP5 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP7 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP9 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP11 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP13 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PP15 Scope");	tFrame->AddFrame(new GTP_SerialScope(tFrame, this, 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pGTPTabs->AddTab("Serial-PP15");	tFrame->AddFrame(new GTP_Serial(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pGTPTabs->AddTab("Status");		tFrame->AddFrame(new GTP_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pGTPTabs->AddTab("WaveCapture");	tFrame->AddFrame(new GTP_WaveCapture(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pGTPTabs->AddTab("DCTrigger");	tFrame->AddFrame(new GTP_DCTrigger(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("FCAL");			tFrame->AddFrame(new GTP_SSFCal(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("BCAL");			tFrame->AddFrame(new GTP_SSBCal(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("TOF");			tFrame->AddFrame(new GTP_SSHitPattern(tFrame, this, GTP_HITPATTER_TYPE_TOF), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("PS");				tFrame->AddFrame(new GTP_SSHitPattern(tFrame, this, GTP_HITPATTER_TYPE_PS), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("ST");				tFrame->AddFrame(new GTP_SSHitPattern(tFrame, this, GTP_HITPATTER_TYPE_ST), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("TAGH");			tFrame->AddFrame(new GTP_SSHitPattern(tFrame, this, GTP_HITPATTER_TYPE_TAGH), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("TAGM");			tFrame->AddFrame(new GTP_SSHitPattern(tFrame, this, GTP_HITPATTER_TYPE_TAGM), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pGTPTabs->AddTab("Scalers");		tFrame->AddFrame(new GTP_SS_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pGTPTabs->AddTab("TriggerBits");	tFrame->AddFrame(new GTP_TriggerBit(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pGTPTabs->AddTab("Scope");			tFrame->AddFrame(new GTP_Scope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		
		// serializer status page (ch up/down, lane up/down, latency, rxrdy, rxerror, crc status,...?)
		// delay curve sweeps
		strSlotIdentifier.Form("SWA");
	}

	void SetupRegisters()
	{
#define GTP_SDIOMUX_NAME_MAP		{\
											43,\
											{"0","1","SYNC","TRIG1","TRIG2","FPIN0","FPIN1","FPIN2","FPIN3","PULSER","BUSY","TRIGBIT0","TRIGBIT1","TRIGBIT2","TRIGBIT3","TRIGBIT4","TRIGBIT5","TRIGBIT6","TRIGBIT7","TRIGBIT8","TRIGBIT9","TRIGBIT10","TRIGBIT11","TRIGBIT12","TRIGBIT13","TRIGBIT14","TRIGBIT15","TRIGBIT16","TRIGBIT17","TRIGBIT18","TRIGBIT19","TRIGBIT20","TRIGBIT21","TRIGBIT22","TRIGBIT23","TRIGBIT24","TRIGBIT25","TRIGBIT26","TRIGBIT27","TRIGBIT28","TRIGBIT29","TRIGBIT30","TRIGBIT31"},\
											{0,1,2,3,4,5,6,7,8,9,10,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63}\
										}

		static RegMemDesc regs[] = {
			{"Clk", 0},
				{"GClkSource",					REGMEM_DESC_FLAGS_STRING,	{0x0100, 0, 2, 32},	{2,{"VXS","LOCAL"},{1,2}}},
				{"GClkPllReset",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 31, 1, 32}},
				{"GClkPllLocked",				REGMEM_DESC_FLAGS_UINT,		{0x0104, 0, 1, 32}},
				{"ATXClkLPllLocked",			REGMEM_DESC_FLAGS_UINT,		{0x0104, 1, 1, 32}},
				{"ATXClkRPllLocked",			REGMEM_DESC_FLAGS_UINT,		{0x0104, 2, 1, 32}},
			{NULL, 0},
			{"Sd", 0},
				{"Scalers", 0},
					{"Disable",					REGMEM_DESC_FLAGS_UINT,		{0x0200, 0, 1, 32}},
					{"SysClk50",				REGMEM_DESC_FLAGS_UINT,		{0x0204, 0, 32, 32}},
					{"GClk250",					REGMEM_DESC_FLAGS_UINT,		{0x0208, 0, 32, 32}},
					{"Sync",					REGMEM_DESC_FLAGS_UINT,		{0x020C, 0, 32, 32}},
					{"Trig1",					REGMEM_DESC_FLAGS_UINT,		{0x0210, 0, 32, 32}},
					{"Trig2",					REGMEM_DESC_FLAGS_UINT,		{0x0214, 0, 32, 32}},
					{"Busy",					REGMEM_DESC_FLAGS_UINT,		{0x0218, 0, 32, 32}},
					{"BusyCycles",				REGMEM_DESC_FLAGS_UINT,		{0x021C, 0, 32, 32}},
					{"FpIn0",					REGMEM_DESC_FLAGS_UINT,		{0x0220, 0, 32, 32}},
					{"FpIn1",					REGMEM_DESC_FLAGS_UINT,		{0x0224, 0, 32, 32}},
					{"FpIn2",					REGMEM_DESC_FLAGS_UINT,		{0x0228, 0, 32, 32}},
					{"FpIn3",					REGMEM_DESC_FLAGS_UINT,		{0x022C, 0, 32, 32}},
					{"FpOut0",					REGMEM_DESC_FLAGS_UINT,		{0x0230, 0, 32, 32}},
					{"FpOut1",					REGMEM_DESC_FLAGS_UINT,		{0x0234, 0, 32, 32}},
					{"FpOut2",					REGMEM_DESC_FLAGS_UINT,		{0x0238, 0, 32, 32}},
					{"FpOut3",					REGMEM_DESC_FLAGS_UINT,		{0x023C, 0, 32, 32}},
				{NULL, 0},
				{"Pulser", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x0300, 0, 32, 32}},
					{"LowCycles",				REGMEM_DESC_FLAGS_UINT,		{0x0304, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x0308, 0, 32, 32}},
					{"Done",					REGMEM_DESC_FLAGS_UINT,		{0x030C, 0, 32, 32}},
					{"Start",					REGMEM_DESC_FLAGS_UINT,		{0x0310, 0, 0, 32}},
				{NULL, 0},
				{"I/O Muxing", 0},
					{"Trig",					REGMEM_DESC_FLAGS_STRING,	{0x0320, 0, 6, 32},	GTP_SDIOMUX_NAME_MAP},
					{"Sync",					REGMEM_DESC_FLAGS_STRING,	{0x0324, 0, 6, 32},	GTP_SDIOMUX_NAME_MAP},
					{"FpOut0",					REGMEM_DESC_FLAGS_STRING,	{0x0328, 0, 6, 32},	GTP_SDIOMUX_NAME_MAP},
					{"FpOut1",					REGMEM_DESC_FLAGS_STRING,	{0x032C, 0, 6, 32},	GTP_SDIOMUX_NAME_MAP},
					{"FpOut2",					REGMEM_DESC_FLAGS_STRING,	{0x0330, 0, 6, 32},	GTP_SDIOMUX_NAME_MAP},
					{"FpOut3",					REGMEM_DESC_FLAGS_STRING,	{0x0334, 0, 6, 32},	GTP_SDIOMUX_NAME_MAP},
				{NULL, 0},
			{NULL, 0},
			{"GxbCfgOdd", 0},
				{"AnalogControls", 0},
					{"LogicalAddr",				REGMEM_DESC_FLAGS_UINT,		{0x0504, 0, 7, 32}},
					{"RxEqCtrlWr",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 0, 4, 32}},
					{"RxEqDCGainWr",			REGMEM_DESC_FLAGS_UINT,		{0x050C, 4, 3, 32}},
					{"TxPreEmp0Wr",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 7, 5, 32}},
					{"TxPreEmp1Wr",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 12, 5, 32}},
					{"TxPreEmp2Wr",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 17, 5, 32}},
					{"TxVODCtrlWr",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 22, 3, 32}},
					{"RxEqCtrlRd",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 0, 4, 32}},
					{"RxEqDCGainRd",			REGMEM_DESC_FLAGS_UINT,		{0x050C, 4, 3, 32}},
					{"TxPreEmp0Rd",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 7, 5, 32}},
					{"TxPreEmp1Rd",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 12, 5, 32}},
					{"TxPreEmp2Rd",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 17, 5, 32}},
					{"TxVODCtrlRd",				REGMEM_DESC_FLAGS_UINT,		{0x050C, 22, 3, 32}},
				{NULL, 0},
				{"DigitalControls", 0},
					{"ModeSelect",				REGMEM_DESC_FLAGS_UINT,		{0x0504, 7, 4, 32}},
					{"CtrlRead",				REGMEM_DESC_FLAGS_UINT,		{0x0504, 13, 1, 32}},
					{"CtrlWrite",				REGMEM_DESC_FLAGS_UINT,		{0x0504, 15, 1, 32}},
					{"CtrlAddress",				REGMEM_DESC_FLAGS_UINT,		{0x0508, 0, 16, 32}},
					{"CtrlReadData",			REGMEM_DESC_FLAGS_UINT,		{0x0500, 0, 16, 32}},
					{"CtrlWriteData",			REGMEM_DESC_FLAGS_UINT,		{0x0508, 16, 16, 32}},
				{NULL, 0},
				{"Busy",						REGMEM_DESC_FLAGS_UINT,		{0x0500, 16, 1, 32}},
				{"DataValid",					REGMEM_DESC_FLAGS_UINT,		{0x0500, 17, 1, 32}},
				{"Error",						REGMEM_DESC_FLAGS_UINT,		{0x0500, 18, 1, 32}},
				{"Read",						REGMEM_DESC_FLAGS_UINT,		{0x0504, 11, 1, 32}},
				{"WriteAll",					REGMEM_DESC_FLAGS_UINT,		{0x0504, 12, 1, 32}},
				{"PowerDown",					REGMEM_DESC_FLAGS_UINT,		{0x0504, 15, 1, 32}},
			{NULL, 0},
			{"SerDes", 0},
				{"PP1(Slot10)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1000, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1000, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1000, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1018, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1018, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1010, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1010, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1010, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x101C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x101C, 16, 2, 32}},
				{NULL, 0},
				{"PP3(Slot9)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1200, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1200, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1200, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1218, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1218, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1210, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1210, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1210, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1210, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1210, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1210, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1210, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x121C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x121C, 16, 2, 32}},
				{NULL, 0},
				{"PP5(Slot8)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1400, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1400, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1400, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1418, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1418, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1410, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1410, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1410, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1410, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1410, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1410, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1410, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x141C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x141C, 16, 2, 32}},
				{NULL, 0},
				{"PP7(Slot7)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1600, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1600, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1600, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1618, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1618, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1610, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1610, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1610, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1610, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1610, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1610, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1610, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x161C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x161C, 16, 2, 32}},
				{NULL, 0},
				{"PP9(Slot6)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1800, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1800, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1800, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1818, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1818, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1810, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1810, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1810, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1810, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1810, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1810, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1810, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x181C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x181C, 16, 2, 32}},
				{NULL, 0},
				{"PP11(Slot5)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1A00, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1A00, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1A00, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1A18, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1A18, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1A10, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1A10, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1A10, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1A10, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1A10, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1A10, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1A10, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x1A1C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x1A1C, 16, 2, 32}},
				{NULL, 0},
				{"PP13(Slot4)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1C00, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1C00, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1C00, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1C18, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1C18, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1C10, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1C10, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1C10, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1C10, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1C10, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1C10, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1C10, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x1C1C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x1C1C, 16, 2, 32}},
				{NULL, 0},
				{"PP15(Slot3)", 0},
					{"PowerDown",				REGMEM_DESC_FLAGS_UINT,		{0x1E00, 0, 1, 32}},
					{"BitErrCntRst",			REGMEM_DESC_FLAGS_UINT,		{0x1E00, 10, 1, 32}},
					{"BitErrCntEn",				REGMEM_DESC_FLAGS_UINT,		{0x1E00, 11, 1, 32}},
					{"BitErrCnt0",				REGMEM_DESC_FLAGS_UINT,		{0x1E18, 0, 16, 32}},
					{"BitErrCnt1",				REGMEM_DESC_FLAGS_UINT,		{0x1E18, 16, 16, 32}},
					{"HardErr0",				REGMEM_DESC_FLAGS_UINT,		{0x1E10, 0, 1, 32}},
					{"HardErr1",				REGMEM_DESC_FLAGS_UINT,		{0x1E10, 1, 1, 32}},
					{"LaneUp0",					REGMEM_DESC_FLAGS_UINT,		{0x1E10, 4, 1, 32}},
					{"LaneUp1",					REGMEM_DESC_FLAGS_UINT,		{0x1E10, 5, 1, 32}},
					{"ChannelUp",				REGMEM_DESC_FLAGS_UINT,		{0x1E10, 12, 1, 32}},
					{"TxLock",					REGMEM_DESC_FLAGS_UINT,		{0x1E10, 13, 1, 32}},
					{"RxSrcRdyN",				REGMEM_DESC_FLAGS_UINT,		{0x1E10, 14, 1, 32}},
					{"Latency",					REGMEM_DESC_FLAGS_UINT,		{0x1E1C, 0, 16, 32}},
					{"CrcPass",					REGMEM_DESC_FLAGS_UINT,		{0x1E1C, 16, 2, 32}},
				{NULL, 0},
			{NULL, 0},
			{"Subsystems", 0},
				{"BCal", 0},
					{"BCALEnergyEn",			REGMEM_DESC_FLAGS_UINT,		{0x2000, 0, 1, 32}},
					{"BCALCosmicEn",			REGMEM_DESC_FLAGS_UINT,		{0x2000, 1, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3000, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3004, 0, 8, 32}},
				{NULL, 0},
				{"FCal", 0},
					{"FCALEnergyEn",			REGMEM_DESC_FLAGS_UINT,		{0x2000, 2, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3100, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3104, 0, 8, 32}},
				{NULL, 0},
				{"TagM", 0},
					{"TAGMHitPatternEn",		REGMEM_DESC_FLAGS_UINT,		{0x2000, 3, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3200, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3204, 0, 8, 32}},
					{"EdgeDetEn",					REGMEM_DESC_FLAGS_UINT,		{0x3208, 0, 1, 32}},
				{NULL, 0},
				{"TagH", 0},
					{"TAGHHitPatternEn",		REGMEM_DESC_FLAGS_UINT,		{0x2000, 4, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3300, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3304, 0, 8, 32}},
					{"EdgeDetEn",					REGMEM_DESC_FLAGS_UINT,		{0x3308, 0, 1, 32}},
				{NULL, 0},
				{"PS", 0},
					{"PSHitPatternEn",		REGMEM_DESC_FLAGS_UINT,		{0x2000, 5, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3400, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3404, 0, 8, 32}},
          {"EdgeDetEn",                                   REGMEM_DESC_FLAGS_UINT,         {0x3408, 0, 1, 32}},
				{NULL, 0},
				{"ST", 0},
					{"STHitPatternEn",		REGMEM_DESC_FLAGS_UINT,		{0x2000, 6, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3500, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3504, 0, 8, 32}},
          {"EdgeDetEn",                                   REGMEM_DESC_FLAGS_UINT,         {0x3508, 0, 1, 32}},
				{NULL, 0},
				{"TOF", 0},
					{"TOFHitPatternEn",		REGMEM_DESC_FLAGS_UINT,		{0x2000, 7, 1, 32}},
					{"Delay",					REGMEM_DESC_FLAGS_UINT,		{0x3600, 0, 8, 32}},
					{"Width",					REGMEM_DESC_FLAGS_UINT,		{0x3604, 0, 8, 32}},
          {"EdgeDetEn",                                   REGMEM_DESC_FLAGS_UINT,         {0x3608, 0, 1, 32}},
				{NULL, 0},
			{NULL, 0},
			{"TriggerBits", 0},
				{"Trigout0", 0},
					{"BCal/FCal", 0},
						{"BCalEnergyScale",		REGMEM_DESC_FLAGS_UINT,		{0x4010, 0, 8, 32}},
						{"FCalEnergyScale",		REGMEM_DESC_FLAGS_UINT,		{0x4020, 0, 8, 32}},
						{"BFCalEnergyThr",		REGMEM_DESC_FLAGS_UINT,		{0x4030, 0, 32, 32}},
						{"BCalCosmicEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 1, 1, 32}},
						{"BFCalEnergyEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 2, 1, 32}},
					{NULL, 0},

					{"BCal", 0},
						{"EnergyMin",		REGMEM_DESC_FLAGS_UINT,		{0x4014, 0, 16, 32}},
						{"EnergyMax",		REGMEM_DESC_FLAGS_UINT,		{0x4014, 16, 16, 32}},
						{"EnergyCutEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 8, 1, 32}},
					{NULL, 0},

					{"FCal", 0},
						{"EnergyMin",		REGMEM_DESC_FLAGS_UINT,		{0x4024, 0, 16, 32}},
						{"EnergyMax",		REGMEM_DESC_FLAGS_UINT,		{0x4024, 16, 16, 32}},
						{"EnergyCutEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 9, 1, 32}},
					{NULL, 0},

					{"TagM", 0},
						{"TagMPatternEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 3, 1, 32}},
						{"TagMHitPatternMask",	REGMEM_DESC_FLAGS_HEX,		{0x4070, 0, 32, 32}},
					{NULL, 0},
					{"TagH", 0},
						{"TagHPatternEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 4, 1, 32}},
						{"TagHHitPatternMask",	REGMEM_DESC_FLAGS_HEX,		{0x4074, 0, 32, 32}},
					{NULL, 0},
					{"PS", 0},
						{"PSCoincidenceEn",		REGMEM_DESC_FLAGS_UINT,		{0x4000, 5, 1, 32}},
						{"PSHitPatternMask",		REGMEM_DESC_FLAGS_HEX,		{0x4040, 0, 16, 32}},
					{NULL, 0},
					{"ST", 0},
						{"STHitCountEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 6, 1, 32}},
						{"STHitPatternMask",		REGMEM_DESC_FLAGS_HEX,		{0x4050, 0, 32, 32}},
						{"STHitCountThr",			REGMEM_DESC_FLAGS_UINT,		{0x4054, 0, 6, 32}},
					{NULL, 0},
					{"TOF", 0},
						{"TOFHitCountEn",			REGMEM_DESC_FLAGS_UINT,		{0x4000, 7, 1, 32}},
						{"TOFHitPatternMask",	REGMEM_DESC_FLAGS_HEX,		{0x4060, 0, 32, 32}},
						{"TOFHitCountThr",		REGMEM_DESC_FLAGS_UINT,		{0x4064, 0, 6, 32}},
					{NULL, 0},
					{"TrigbitEn",					REGMEM_DESC_FLAGS_UINT,		{0x4000, 0, 1, 32}},
					{"TrigoutWidth",				REGMEM_DESC_FLAGS_UINT,		{0x4004, 16, 12, 32}},
					{"TrigoutLatency",			REGMEM_DESC_FLAGS_UINT,		{0x4004, 0, 12, 32}},
					{"LatencyError",				REGMEM_DESC_FLAGS_UINT,		{0x4008, 0, 1, 32}},
				{NULL, 0},
			{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "GTP"; }
	const char *GetModuleFullName() { return "Global Trigger Processor"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pGTPTabs;
};

#endif
