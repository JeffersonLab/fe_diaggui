#ifndef SSP_HPSModule_H
#define SSP_HPSModule_H

#include "RootHeader.h"
//#include "SSP_Histograms.h"
//#include "SSP_SumHist.h"
//#include "SSP_WaveCapture.h"
//#include "SSP_Config.h"
//#include "SSP_Status.h"
//#include "SSP_Scalers.h"
//#include "SSP_Fiber.h"
//#include "SSP_Testing.h"
#include "SSP_HPS_TrgHist.h"
#include "SSP_HPSSerialScope.h"
#include "ModuleFrame.h"

class SSP_HPSModule	: public ModuleFrame
{
public:
	SSP_HPSModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pSSPTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Config");		tFrame->AddFrame(pSSPConfig = new SSP_Config(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Histograms");	tFrame->AddFrame(pSSPHistograms = new SSP_Histograms(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		tFrame = pSSPTabs->AddTab("TrgHist");		tFrame->AddFrame(new SSP_HPS_TrgHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

//		tFrame = pSSPTabs->AddTab("SumHist");		tFrame->AddFrame(new SSP_SumHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Status");		tFrame->AddFrame(new SSP_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("Fiber 0");		tFrame->AddFrame(new SSP_HPSSerialScope(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("Fiber 1");		tFrame->AddFrame(new SSP_HPSSerialScope(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 2");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 3");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 4");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 5");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 6");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 7");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("SWA VXS 1");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 9), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("WaveCapture");	tFrame->AddFrame(new SSP_WaveCapture(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Scalers");		tFrame->AddFrame(new SSP_Scalers(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("SWA VXS 0");	tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_VXS, 8), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("SWA VXS 1");	tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_VXS, 9), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 0");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 1");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 2");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 3");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 4");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 5");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 6");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 7");		tFrame->AddFrame(new SSP_Fiber(tFrame, this, GTX_FIB, 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Testing");		tFrame->AddFrame(new SSP_Testing(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		strSlotIdentifier.Form("%d", (BaseAddr>>19) & 0x1F);
	}

	void SetupRegisters()
	{
#define SSP_SDIOMUX_NAME_MAP		{\
											28,\
											{"0","1","SYNC","TRIG1","TRIG2","FPIN0","FPIN1","FPIN2","FPIN3","FPIN4","P2IN0","P2IN1","P2IN2","P2IN3","P2IN4","P2IN5","P2IN6","P2IN7","PULSER","BUSY","TRIGBIT0","TRIGBIT1","TRIGBIT2","TRIGBIT3","TRIGBIT4","TRIGBIT5","TRIGBIT6","TRIGBIT7"},\
											{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27}\
										}

		static RegMemDesc regs[] = {
			{"Config", 0},
				{"Spi", 0},
					{"WrData",				REGMEM_DESC_FLAGS_HEX,		{0x0008, 0, 8, 32}},
					{"RdData",				REGMEM_DESC_FLAGS_HEX,		{0x000C, 0, 8, 32}},
					{"NCSSet",				REGMEM_DESC_FLAGS_UINT,		{0x0008, 8, 1, 32}},
					{"NCSClear",			REGMEM_DESC_FLAGS_UINT,		{0x0008, 9, 1, 32}},
					{"Start",				REGMEM_DESC_FLAGS_UINT,		{0x0008, 10, 1, 32}},
					{"Done",					REGMEM_DESC_FLAGS_UINT,		{0x000C, 11, 1, 32}},
				{NULL, 0},
				{"BoardId",					REGMEM_DESC_FLAGS_HEX,		{0x0000, 0, 32, 32}},
				{"FirmwareRev",			REGMEM_DESC_FLAGS_HEX,		{0x0004, 0, 32, 32}},
				{"SoftReset",				REGMEM_DESC_FLAGS_UINT,		{0x0020, 0, 1, 32}},
			{NULL, 0},
			{"Clk", 0},
				{"Drp", 0},
					{"Addr",				REGMEM_DESC_FLAGS_HEX,		{0x0100, 16, 5, 32}},
					{"WrEn",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 21, 1, 32}},
					{"Den",				REGMEM_DESC_FLAGS_UINT,		{0x0100, 22, 1, 32}},
					{"WrData",			REGMEM_DESC_FLAGS_HEX,		{0x0100, 0, 16, 32}},
					{"RdData",			REGMEM_DESC_FLAGS_HEX,		{0x0104, 0, 16, 32}},
					{"RdDataValid",	REGMEM_DESC_FLAGS_UINT,		{0x0104, 16, 1, 32}},
				{NULL, 0},
				{"ClkSerdes",			REGMEM_DESC_FLAGS_STRING,	{0x0100, 24, 2, 32}, {4,{"DISABLED","VXS","P2","LOCAL"},{0,1,2,3}}},
				{"ClkLogic",			REGMEM_DESC_FLAGS_STRING,	{0x0100, 26, 2, 32}, {4,{"DISABLED","VXS","P2","LOCAL"},{0,1,2,3}}},
				{"ClkPllReset",		REGMEM_DESC_FLAGS_UINT,		{0x0100, 31, 1, 32}},
				{"ClkPllLocked",		REGMEM_DESC_FLAGS_UINT,		{0x0104, 17, 1, 32}},
			{NULL, 0},
			{"Sd", 0},
				{"I/O Muxing", 0},
					{"FpOut0",					REGMEM_DESC_FLAGS_STRING,	{0x0200, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut1",					REGMEM_DESC_FLAGS_STRING,	{0x0204, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut2",					REGMEM_DESC_FLAGS_STRING,	{0x0208, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut3",					REGMEM_DESC_FLAGS_STRING,	{0x020C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"FpOut4",					REGMEM_DESC_FLAGS_STRING,	{0x0210, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Gpio0",					REGMEM_DESC_FLAGS_STRING,	{0x0214, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Gpio1",					REGMEM_DESC_FLAGS_STRING,	{0x0218, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out0",					REGMEM_DESC_FLAGS_STRING,	{0x021C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out1",					REGMEM_DESC_FLAGS_STRING,	{0x0220, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out2",					REGMEM_DESC_FLAGS_STRING,	{0x0224, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out3",					REGMEM_DESC_FLAGS_STRING,	{0x0228, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out4",					REGMEM_DESC_FLAGS_STRING,	{0x022C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out5",					REGMEM_DESC_FLAGS_STRING,	{0x0230, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out6",					REGMEM_DESC_FLAGS_STRING,	{0x0234, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"P2Out7",					REGMEM_DESC_FLAGS_STRING,	{0x0238, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Trig",						REGMEM_DESC_FLAGS_STRING,	{0x023C, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
					{"Sync",						REGMEM_DESC_FLAGS_STRING,	{0x0240, 0, 5, 32},	SSP_SDIOMUX_NAME_MAP},
				{NULL, 0},
				{"Pulser", 0},
					{"Period",					REGMEM_DESC_FLAGS_UINT,		{0x0280, 0, 32, 32}},
					{"LowCycles",				REGMEM_DESC_FLAGS_UINT,		{0x0284, 0, 32, 32}},
					{"NPulses",					REGMEM_DESC_FLAGS_UINT,		{0x0288, 0, 32, 32}},
					{"Start",					REGMEM_DESC_FLAGS_UINT,		{0x028C, 0, 0, 32}},
					{"Done",						REGMEM_DESC_FLAGS_UINT,		{0x0290, 0, 1, 32}},
				{NULL, 0},
				{"Scalers", 0},
					{"Disable",					REGMEM_DESC_FLAGS_UINT,		{0x0300, 0, 1, 32}},
					{"SysClk50",				REGMEM_DESC_FLAGS_UINT,		{0x0304, 0, 32, 32}},
					{"GClk250",					REGMEM_DESC_FLAGS_UINT,		{0x0308, 0, 32, 32}},
					{"Sync",						REGMEM_DESC_FLAGS_UINT,		{0x030C, 0, 32, 32}},
					{"Trig1",					REGMEM_DESC_FLAGS_UINT,		{0x0310, 0, 32, 32}},
					{"Trig2",					REGMEM_DESC_FLAGS_UINT,		{0x0314, 0, 32, 32}},
					{"Gpio0",					REGMEM_DESC_FLAGS_UINT,		{0x0318, 0, 32, 32}},
					{"Gpio1",					REGMEM_DESC_FLAGS_UINT,		{0x031C, 0, 32, 32}},
					{"FpIn0",					REGMEM_DESC_FLAGS_UINT,		{0x0320, 0, 32, 32}},
					{"FpIn1",					REGMEM_DESC_FLAGS_UINT,		{0x0324, 0, 32, 32}},
					{"FpIn2",					REGMEM_DESC_FLAGS_UINT,		{0x0328, 0, 32, 32}},
					{"FpIn3",					REGMEM_DESC_FLAGS_UINT,		{0x032C, 0, 32, 32}},
					{"FpIn4",					REGMEM_DESC_FLAGS_UINT,		{0x0330, 0, 32, 32}},
					{"FpOut0",					REGMEM_DESC_FLAGS_UINT,		{0x0334, 0, 32, 32}},
					{"FpOut1",					REGMEM_DESC_FLAGS_UINT,		{0x0338, 0, 32, 32}},
					{"FpOut2",					REGMEM_DESC_FLAGS_UINT,		{0x033C, 0, 32, 32}},
					{"FpOut3",					REGMEM_DESC_FLAGS_UINT,		{0x0340, 0, 32, 32}},
					{"FpOut4",					REGMEM_DESC_FLAGS_UINT,		{0x0344, 0, 32, 32}},
					{"Busy",						REGMEM_DESC_FLAGS_UINT,		{0x0348, 0, 32, 32}},
					{"BusyCycles",				REGMEM_DESC_FLAGS_UINT,		{0x034C, 0, 32, 32}},
					{"P2In0",					REGMEM_DESC_FLAGS_UINT,		{0x0350, 0, 32, 32}},
					{"P2In1",					REGMEM_DESC_FLAGS_UINT,		{0x0354, 0, 32, 32}},
					{"P2In2",					REGMEM_DESC_FLAGS_UINT,		{0x0358, 0, 32, 32}},
					{"P2In3",					REGMEM_DESC_FLAGS_UINT,		{0x035C, 0, 32, 32}},
					{"P2In4",					REGMEM_DESC_FLAGS_UINT,		{0x0360, 0, 32, 32}},
					{"P2In5",					REGMEM_DESC_FLAGS_UINT,		{0x0364, 0, 32, 32}},
					{"P2In6",					REGMEM_DESC_FLAGS_UINT,		{0x0368, 0, 32, 32}},
					{"P2In7",					REGMEM_DESC_FLAGS_UINT,		{0x036C, 0, 32, 32}},
					{"P2Out0",					REGMEM_DESC_FLAGS_UINT,		{0x0370, 0, 32, 32}},
					{"P2Out1",					REGMEM_DESC_FLAGS_UINT,		{0x0374, 0, 32, 32}},
					{"P2Out2",					REGMEM_DESC_FLAGS_UINT,		{0x0378, 0, 32, 32}},
					{"P2Out3",					REGMEM_DESC_FLAGS_UINT,		{0x037C, 0, 32, 32}},
					{"P2Out4",					REGMEM_DESC_FLAGS_UINT,		{0x0380, 0, 32, 32}},
					{"P2Out5",					REGMEM_DESC_FLAGS_UINT,		{0x0384, 0, 32, 32}},
					{"P2Out6",					REGMEM_DESC_FLAGS_UINT,		{0x0388, 0, 32, 32}},
					{"P2Out7",					REGMEM_DESC_FLAGS_UINT,		{0x038C, 0, 32, 32}},
				{NULL, 0},
			{NULL, 0},
			{"Hps", 0},
				{"TriggerLatency",			REGMEM_DESC_FLAGS_UINT,		{0x2100, 0, 10, 32}},
				{"ScalerTrig0Busy",		REGMEM_DESC_FLAGS_UINT,		{0x2110, 0, 32, 32}},	//trigger(0)
				{"ScalerTrig1Busy",		REGMEM_DESC_FLAGS_UINT,		{0x2114, 0, 32, 32}},	//trigger(1)
				{"ScalerTrig2Busy",		REGMEM_DESC_FLAGS_UINT,		{0x2118, 0, 32, 32}},	//trigger(2)
				{"ScalerTrig3Busy",		REGMEM_DESC_FLAGS_UINT,		{0x211C, 0, 32, 32}},	//trigger(3)
				{"ScalerTrig4Busy",		REGMEM_DESC_FLAGS_UINT,		{0x2120, 0, 32, 32}},	//trigger(4)
				{"ScalerTrig5Busy",		REGMEM_DESC_FLAGS_UINT,		{0x2124, 0, 32, 32}},	//trigger(5)
				{"Singles 0 Trigger", 0},
					{"Emin_en",					REGMEM_DESC_FLAGS_UINT,		{0x0700, 0, 1, 32}},
					{"Emin",						REGMEM_DESC_FLAGS_UINT,		{0x0718, 0, 13, 32}},
					{"Emax_en",					REGMEM_DESC_FLAGS_UINT,		{0x0700, 1, 1, 32}},
					{"Emax",						REGMEM_DESC_FLAGS_UINT,		{0x071C, 0, 13, 32}},
					{"Nmin_en",					REGMEM_DESC_FLAGS_UINT,		{0x0700, 2, 1, 32}},
					{"Nmin",						REGMEM_DESC_FLAGS_UINT,		{0x0720, 0, 4, 32}},

					{"Prescale0_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0730, 0, 16, 32}},
					{"Prescale0_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0730, 16, 6, 32}},
					{"Prescale0_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0730, 24, 6, 32}},

					{"Prescale1_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0734, 0, 16, 32}},
					{"Prescale1_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0734, 16, 6, 32}},
					{"Prescale1_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0734, 24, 6, 32}},

					{"Prescale2_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0738, 0, 16, 32}},
					{"Prescale2_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0738, 16, 6, 32}},
					{"Prescale2_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0738, 24, 6, 32}},

					{"Prescale3_Val",			REGMEM_DESC_FLAGS_UINT,		{0x073C, 0, 16, 32}},
					{"Prescale3_MinX",		REGMEM_DESC_FLAGS_INT,		{0x073C, 16, 6, 32}},
					{"Prescale3_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x073C, 24, 6, 32}},

					{"Prescale4_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0740, 0, 16, 32}},
					{"Prescale4_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0740, 16, 6, 32}},
					{"Prescale4_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0740, 24, 6, 32}},

					{"Prescale5_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0744, 0, 16, 32}},
					{"Prescale5_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0744, 16, 6, 32}},
					{"Prescale5_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0744, 24, 6, 32}},

					{"Prescale6_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0748, 0, 16, 32}},
					{"Prescale6_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0748, 16, 6, 32}},
					{"Prescale6_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0748, 24, 6, 32}},

					{"ScalerSinglePass",		REGMEM_DESC_FLAGS_UINT,		{0x0780, 0, 32, 32}},
					{"ScalerSingleTot",		REGMEM_DESC_FLAGS_UINT,		{0x0784, 0, 32, 32}},
				{NULL, 0},
				{"Singles 1 Trigger", 0},
					{"Emin_en",					REGMEM_DESC_FLAGS_UINT,		{0x0800, 0, 1, 32}},
					{"Emin",						REGMEM_DESC_FLAGS_UINT,		{0x0818, 0, 13, 32}},
					{"Emax_en",					REGMEM_DESC_FLAGS_UINT,		{0x0800, 1, 1, 32}},
					{"Emax",						REGMEM_DESC_FLAGS_UINT,		{0x081C, 0, 13, 32}},
					{"Nmin_en",					REGMEM_DESC_FLAGS_UINT,		{0x0800, 2, 1, 32}},
					{"Nmin",						REGMEM_DESC_FLAGS_UINT,		{0x0820, 0, 4, 32}},


					{"Prescale0_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0830, 0, 16, 32}},
					{"Prescale0_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0830, 16, 6, 32}},
					{"Prescale0_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0830, 24, 6, 32}},

					{"Prescale1_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0834, 0, 16, 32}},
					{"Prescale1_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0834, 16, 6, 32}},
					{"Prescale1_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0834, 24, 6, 32}},

					{"Prescale2_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0838, 0, 16, 32}},
					{"Prescale2_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0838, 16, 6, 32}},
					{"Prescale2_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0838, 24, 6, 32}},

					{"Prescale3_Val",			REGMEM_DESC_FLAGS_UINT,		{0x083C, 0, 16, 32}},
					{"Prescale3_MinX",		REGMEM_DESC_FLAGS_INT,		{0x083C, 16, 6, 32}},
					{"Prescale3_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x083C, 24, 6, 32}},

					{"Prescale4_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0840, 0, 16, 32}},
					{"Prescale4_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0840, 16, 6, 32}},
					{"Prescale4_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0840, 24, 6, 32}},

					{"Prescale5_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0844, 0, 16, 32}},
					{"Prescale5_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0844, 16, 6, 32}},
					{"Prescale5_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0844, 24, 6, 32}},

					{"Prescale6_Val",			REGMEM_DESC_FLAGS_UINT,		{0x0848, 0, 16, 32}},
					{"Prescale6_MinX",		REGMEM_DESC_FLAGS_INT,		{0x0848, 16, 6, 32}},
					{"Prescale6_MaxX",		REGMEM_DESC_FLAGS_INT,		{0x0848, 24, 6, 32}},

					{"ScalerSinglePass",		REGMEM_DESC_FLAGS_UINT,		{0x0880, 0, 32, 32}},
					{"ScalerSingleTot",		REGMEM_DESC_FLAGS_UINT,		{0x0884, 0, 32, 32}},
				{NULL, 0},
				{"Pairs 0 Trigger", 0},
					{"Sum_en",					REGMEM_DESC_FLAGS_UINT,		{0x0900, 0, 1, 32}},
					{"Diff_en",					REGMEM_DESC_FLAGS_UINT,		{0x0900, 1, 1, 32}},
					{"Coplanarity_en",		REGMEM_DESC_FLAGS_UINT,		{0x0900, 2, 1, 32}},
					{"EnergeyDist_en",		REGMEM_DESC_FLAGS_UINT,		{0x0900, 3, 1, 32}},
					{"TimeCoincidence",		REGMEM_DESC_FLAGS_UINT,		{0x090C, 0, 4, 32}},
					{"Summax",					REGMEM_DESC_FLAGS_UINT,		{0x0910, 0, 13, 32}},
					{"Diffmax",					REGMEM_DESC_FLAGS_UINT,		{0x0914, 0, 13, 32}},
					{"Emin",						REGMEM_DESC_FLAGS_UINT,		{0x0918, 0, 13, 32}},
					{"Emax",						REGMEM_DESC_FLAGS_UINT,		{0x091C, 0, 13, 32}},
					{"Nmin",						REGMEM_DESC_FLAGS_UINT,		{0x0920, 0, 4, 32}},
					{"Coplanarity",			REGMEM_DESC_FLAGS_UINT,		{0x0924, 0, 8, 32}},
					{"EnergyDistF",			REGMEM_DESC_FLAGS_UINT,		{0x0928, 0, 13, 32}},
					{"EnergyDistmin",			REGMEM_DESC_FLAGS_UINT,		{0x092C, 0, 13, 32}},
					{"ScalerPairsPass",		REGMEM_DESC_FLAGS_UINT,		{0x0980, 0, 32, 32}},
					{"ScalerSumPass",			REGMEM_DESC_FLAGS_UINT,		{0x0984, 0, 32, 32}},
					{"ScalerDiffPass",		REGMEM_DESC_FLAGS_UINT,		{0x0988, 0, 32, 32}},
					{"ScalerEDPass",			REGMEM_DESC_FLAGS_UINT,		{0x098C, 0, 32, 32}},
					{"ScalerCoplanarPass",	REGMEM_DESC_FLAGS_UINT,		{0x0990, 0, 32, 32}},
					{"ScalerTriggerPass",	REGMEM_DESC_FLAGS_UINT,		{0x0994, 0, 32, 32}},
				{NULL, 0},
				{"Pairs 1 Trigger", 0},
					{"Sum_en",					REGMEM_DESC_FLAGS_UINT,		{0x0A00, 0, 1, 32}},
					{"Diff_en",					REGMEM_DESC_FLAGS_UINT,		{0x0A00, 1, 1, 32}},
					{"Coplanarity_en",		REGMEM_DESC_FLAGS_UINT,		{0x0A00, 2, 1, 32}},
					{"EnergeyDist_en",		REGMEM_DESC_FLAGS_UINT,		{0x0A00, 3, 1, 32}},
					{"TimeCoincidence",		REGMEM_DESC_FLAGS_UINT,		{0x0A0C, 0, 4, 32}},
					{"Summax",					REGMEM_DESC_FLAGS_UINT,		{0x0A10, 0, 13, 32}},
					{"Diffmax",					REGMEM_DESC_FLAGS_UINT,		{0x0A14, 0, 13, 32}},
					{"Emin",						REGMEM_DESC_FLAGS_UINT,		{0x0A18, 0, 13, 32}},
					{"Emax",						REGMEM_DESC_FLAGS_UINT,		{0x0A1C, 0, 13, 32}},
					{"Nmin",						REGMEM_DESC_FLAGS_UINT,		{0x0A20, 0, 4, 32}},
					{"Coplanarity",			REGMEM_DESC_FLAGS_UINT,		{0x0A24, 0, 8, 32}},
					{"EnergyDistF",			REGMEM_DESC_FLAGS_UINT,		{0x0A28, 0, 13, 32}},
					{"EnergyDistmin",			REGMEM_DESC_FLAGS_UINT,		{0x0A2C, 0, 13, 32}},

					{"ScalerPairsPass",		REGMEM_DESC_FLAGS_UINT,		{0x0A80, 0, 32, 32}},
					{"ScalerSumPass",			REGMEM_DESC_FLAGS_UINT,		{0x0A84, 0, 32, 32}},
					{"ScalerDiffPass",		REGMEM_DESC_FLAGS_UINT,		{0x0A88, 0, 32, 32}},
					{"ScalerEDPass",			REGMEM_DESC_FLAGS_UINT,		{0x0A8C, 0, 32, 32}},
					{"ScalerCoplanarPass",	REGMEM_DESC_FLAGS_UINT,		{0x0A90, 0, 32, 32}},
					{"ScalerTriggerPass",	REGMEM_DESC_FLAGS_UINT,		{0x0A94, 0, 32, 32}},
				{NULL, 0},
				{"Cosmic Trigger", 0},
					{"TimeCoincidence",		REGMEM_DESC_FLAGS_UINT,		{0x0B00, 0, 8, 32}},
					{"PatternCoincidence",	REGMEM_DESC_FLAGS_UINT,		{0x0B04, 0, 16, 32}},
					{"ScalerCosmicTop0",		REGMEM_DESC_FLAGS_UINT,		{0x0B10, 0, 32, 32}},
					{"ScalerCosmicTop1",		REGMEM_DESC_FLAGS_UINT,		{0x0B14, 0, 32, 32}},
					{"ScalerCosmicTop2",		REGMEM_DESC_FLAGS_UINT,		{0x0B18, 0, 32, 32}},
					{"ScalerCosmicTopTrig",	REGMEM_DESC_FLAGS_UINT,		{0x0B1C, 0, 32, 32}},
					{"ScalerCosmicBot0",		REGMEM_DESC_FLAGS_UINT,		{0x0B20, 0, 32, 32}},
					{"ScalerCosmicBot1",		REGMEM_DESC_FLAGS_UINT,		{0x0B24, 0, 32, 32}},
					{"ScalerCosmicBot2",		REGMEM_DESC_FLAGS_UINT,		{0x0B28, 0, 32, 32}},
					{"ScalerCosmicBotTrig",	REGMEM_DESC_FLAGS_UINT,		{0x0B2C, 0, 32, 32}},
				{NULL, 0},
			{NULL, 0},
			{"Event Builder", 0},
				{"Lookback",					REGMEM_DESC_FLAGS_UINT,		{0x2000, 0, 10, 32}},
				{"WindowWidth",				REGMEM_DESC_FLAGS_UINT,		{0x2004, 0, 10, 32}},
				{"BlockSize",					REGMEM_DESC_FLAGS_UINT,		{0x2008, 0, 8, 32}},
				{"Adr32Base",					REGMEM_DESC_FLAGS_HEX,		{0x200C, 7, 9, 32}},
				{"Adr32En",						REGMEM_DESC_FLAGS_UINT,		{0x200C, 0, 1, 32}},
				{"Adr32Mmin",					REGMEM_DESC_FLAGS_HEX,		{0x2010, 0, 9, 32}},
				{"Adr32Mmax",					REGMEM_DESC_FLAGS_HEX,		{0x2010, 16, 9, 32}},
				{"Adr32Men",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 25, 1, 32}},
				{"TokenFirst",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 26, 1, 32}},
				{"TokenLast",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 27, 1, 32}},
				{"TokenTake",					REGMEM_DESC_FLAGS_UINT,		{0x2010, 28, 1, 32}},
				{"BerrEn",						REGMEM_DESC_FLAGS_UINT,		{0x2018, 0, 1, 32}},
				{"FifoBlockCnt",				REGMEM_DESC_FLAGS_UINT,		{0x2020, 0, 32, 32}},
				{"FifoWordCnt",				REGMEM_DESC_FLAGS_UINT,		{0x2024, 0, 32, 32}},
				{"FifoEventCnt",				REGMEM_DESC_FLAGS_UINT,		{0x2028, 0, 32, 32}},
			{NULL, 0},
			{"SerDes", 0},
				{"F1", 0},
					{"Drp", 0},
						{"WrEn",					REGMEM_DESC_FLAGS_UINT,		{0x100C, 24, 1, 32}},
						{"DenTile0",			REGMEM_DESC_FLAGS_UINT,		{0x100C, 25, 1, 32}},
						{"DenTile1",			REGMEM_DESC_FLAGS_UINT,		{0x100C, 26, 1, 32}},
						{"Addr",					REGMEM_DESC_FLAGS_HEX,		{0x100C, 16, 7, 32}},
						{"WrData",				REGMEM_DESC_FLAGS_HEX,		{0x100C, 0, 16, 32}},
						{"RdData",				REGMEM_DESC_FLAGS_UINT,		{0x1014, 0, 16, 32}},
						{"RdDataValid",		REGMEM_DESC_FLAGS_UINT,		{0x1014, 16, 1, 32}},
					{NULL, 0},
					{"Settings", 0},
						{"Loopback",			REGMEM_DESC_FLAGS_STRING,	{0x1000, 2, 3, 32},	{5,{"DISABLED","NEARPCS","NEARPMA","FARPMA","FARPCS"},{0,1,2,4,6}}},
						{"RxEnPrbs",			REGMEM_DESC_FLAGS_STRING,	{0x1000, 5, 2, 32},	{4,{"DISABLED","PRBS7","PRBS23","PRBS31"},{0,1,2,3}}},
						{"TxEnPrbs",			REGMEM_DESC_FLAGS_STRING,	{0x1000, 7, 2, 32},	{4,{"DISABLED","PRBS7","PRBS23","PRBS31"},{0,1,2,3}}},
						{"RxEqMix0",			REGMEM_DESC_FLAGS_STRING,	{0x1004, 0, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp0",			REGMEM_DESC_FLAGS_STRING,	{0x1004, 2, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff0",			REGMEM_DESC_FLAGS_UINT,		{0x1004, 6, 3, 32}},
						{"TxDiffCtrl0",		REGMEM_DESC_FLAGS_STRING,	{0x1004, 9, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix1",			REGMEM_DESC_FLAGS_STRING,	{0x1004, 16, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp1",			REGMEM_DESC_FLAGS_STRING,	{0x1004, 18, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff1",			REGMEM_DESC_FLAGS_UINT,		{0x1004, 22, 3, 32}},
						{"TxDiffCtrl1",		REGMEM_DESC_FLAGS_STRING,	{0x1004, 25, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix2",			REGMEM_DESC_FLAGS_STRING,	{0x1008, 0, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp2",			REGMEM_DESC_FLAGS_STRING,	{0x1008, 2, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff2",			REGMEM_DESC_FLAGS_UINT,		{0x1008, 6, 3, 32}},
						{"TxDiffCtrl2",		REGMEM_DESC_FLAGS_STRING,	{0x1008, 9, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix3",			REGMEM_DESC_FLAGS_STRING,	{0x1008, 16, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp3",			REGMEM_DESC_FLAGS_STRING,	{0x1008, 18, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff3",			REGMEM_DESC_FLAGS_UINT,		{0x1008, 22, 3, 32}},
						{"TxDiffCtrl3",		REGMEM_DESC_FLAGS_STRING,	{0x1008, 25, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
					{NULL, 0},
					{"CrateId",				REGMEM_DESC_FLAGS_UINT,		{0x1020, 0, 16, 32}},
					{"PowerDown",			REGMEM_DESC_FLAGS_UINT,		{0x1000, 0, 1, 32}},
					{"GTReset",				REGMEM_DESC_FLAGS_UINT,		{0x1000, 1, 1, 32}},
					{"LinkReset",			REGMEM_DESC_FLAGS_UINT,		{0x1000, 9, 1, 32}},
					{"BitErrCntRst",		REGMEM_DESC_FLAGS_UINT,		{0x1000, 10, 1, 32}},
					{"BitErrCntEn",		REGMEM_DESC_FLAGS_UINT,		{0x1000, 11, 1, 32}},
					{"BitErrCnt0",			REGMEM_DESC_FLAGS_UINT,		{0x1018, 0, 16, 32}},
					{"BitErrCnt1",			REGMEM_DESC_FLAGS_UINT,		{0x1018, 16, 16, 32}},
					{"BitErrCnt2",			REGMEM_DESC_FLAGS_UINT,		{0x101C, 0, 16, 32}},
					{"BitErrCnt3",			REGMEM_DESC_FLAGS_UINT,		{0x101C, 16, 16, 32}},
					{"HardErr0",			REGMEM_DESC_FLAGS_UINT,		{0x1010, 0, 1, 32}},
					{"HardErr1",			REGMEM_DESC_FLAGS_UINT,		{0x1010, 1, 1, 32}},
					{"HardErr2",			REGMEM_DESC_FLAGS_UINT,		{0x1010, 2, 1, 32}},
					{"HardErr3",			REGMEM_DESC_FLAGS_UINT,		{0x1010, 3, 1, 32}},
					{"LaneUp0",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 4, 1, 32}},
					{"LaneUp1",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 5, 1, 32}},
					{"LaneUp2",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 6, 1, 32}},
					{"LaneUp3",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 7, 1, 32}},
					{"RxPolarity0",		REGMEM_DESC_FLAGS_UINT,		{0x1010, 8, 1, 32}},
					{"RxPolarity1",		REGMEM_DESC_FLAGS_UINT,		{0x1010, 9, 1, 32}},
					{"RxPolarity2",		REGMEM_DESC_FLAGS_UINT,		{0x1010, 10, 1, 32}},
					{"RxPolarity3",		REGMEM_DESC_FLAGS_UINT,		{0x1010, 11, 1, 32}},
					{"ChannelUp",			REGMEM_DESC_FLAGS_UINT,		{0x1010, 12, 1, 32}},
					{"TxLock",				REGMEM_DESC_FLAGS_UINT,		{0x1010, 13, 1, 32}},
					{"RxSrcRdyN",			REGMEM_DESC_FLAGS_UINT,		{0x1010, 14, 1, 32}},
				{NULL, 0},
				{"F2", 0},
					{"Drp", 0},
						{"WrEn",					REGMEM_DESC_FLAGS_UINT,		{0x110C, 24, 1, 32}},
						{"DenTile0",			REGMEM_DESC_FLAGS_UINT,		{0x110C, 25, 1, 32}},
						{"DenTile1",			REGMEM_DESC_FLAGS_UINT,		{0x110C, 26, 1, 32}},
						{"Addr",					REGMEM_DESC_FLAGS_HEX,		{0x110C, 16, 7, 32}},
						{"WrData",				REGMEM_DESC_FLAGS_HEX,		{0x110C, 0, 16, 32}},
						{"RdData",				REGMEM_DESC_FLAGS_UINT,		{0x1114, 0, 16, 32}},
						{"RdDataValid",		REGMEM_DESC_FLAGS_UINT,		{0x1114, 16, 1, 32}},
					{NULL, 0},
					{"Settings", 0},
						{"Loopback",			REGMEM_DESC_FLAGS_STRING,	{0x1100, 2, 3, 32},	{5,{"DISABLED","NEARPCS","NEARPMA","FARPMA","FARPCS"},{0,1,2,4,6}}},
						{"RxEnPrbs",			REGMEM_DESC_FLAGS_STRING,	{0x1100, 5, 2, 32},	{4,{"DISABLED","PRBS7","PRBS23","PRBS31"},{0,1,2,3}}},
						{"TxEnPrbs",			REGMEM_DESC_FLAGS_STRING,	{0x1100, 7, 2, 32},	{4,{"DISABLED","PRBS7","PRBS23","PRBS31"},{0,1,2,3}}},
						{"RxEqMix0",			REGMEM_DESC_FLAGS_STRING,	{0x1104, 0, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp0",			REGMEM_DESC_FLAGS_STRING,	{0x1104, 2, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff0",			REGMEM_DESC_FLAGS_UINT,		{0x1104, 6, 3, 32}},
						{"TxDiffCtrl0",		REGMEM_DESC_FLAGS_STRING,	{0x1104, 9, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix1",			REGMEM_DESC_FLAGS_STRING,	{0x1104, 16, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp1",			REGMEM_DESC_FLAGS_STRING,	{0x1104, 18, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff1",			REGMEM_DESC_FLAGS_UINT,		{0x1104, 22, 3, 32}},
						{"TxDiffCtrl1",		REGMEM_DESC_FLAGS_STRING,	{0x1104, 25, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix2",			REGMEM_DESC_FLAGS_STRING,	{0x1108, 0, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp2",			REGMEM_DESC_FLAGS_STRING,	{0x1108, 2, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff2",			REGMEM_DESC_FLAGS_UINT,		{0x1108, 6, 3, 32}},
						{"TxDiffCtrl2",		REGMEM_DESC_FLAGS_STRING,	{0x1108, 9, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
						{"RxEqMix3",			REGMEM_DESC_FLAGS_STRING,	{0x1108, 16, 2, 32},	{4,{"LARGE","SMALL","MEDIUM","BYPASS"},{0,1,2,3}}},
						{"TxPreEmp3",			REGMEM_DESC_FLAGS_STRING,	{0x1108, 18, 4, 32},	{8,{"0%","8%","17%","25%","33%","42%","50%","58%"},{0,1,2,3,4,5,6,7}}},
						{"TxBufDiff3",			REGMEM_DESC_FLAGS_UINT,		{0x1108, 22, 3, 32}},
						{"TxDiffCtrl3",		REGMEM_DESC_FLAGS_STRING,	{0x1108, 25, 3, 32},	{8,{"500mV","700mV","800mV","900mV","1000mV","1100mV","1200mV","1300mV"},{0,1,2,3,4,5,6,7}}},
					{NULL, 0},
					{"PowerDown",			REGMEM_DESC_FLAGS_UINT,		{0x1100, 0, 1, 32}},
					{"GTReset",				REGMEM_DESC_FLAGS_UINT,		{0x1100, 1, 1, 32}},
					{"LinkReset",			REGMEM_DESC_FLAGS_UINT,		{0x1100, 9, 1, 32}},
					{"BitErrCntRst",		REGMEM_DESC_FLAGS_UINT,		{0x1100, 10, 1, 32}},
					{"BitErrCntEn",		REGMEM_DESC_FLAGS_UINT,		{0x1100, 11, 1, 32}},
					{"BitErrCnt0",			REGMEM_DESC_FLAGS_UINT,		{0x1118, 0, 16, 32}},
					{"BitErrCnt1",			REGMEM_DESC_FLAGS_UINT,		{0x1118, 16, 16, 32}},
					{"BitErrCnt2",			REGMEM_DESC_FLAGS_UINT,		{0x111C, 0, 16, 32}},
					{"BitErrCnt3",			REGMEM_DESC_FLAGS_UINT,		{0x111C, 16, 16, 32}},
					{"HardErr0",			REGMEM_DESC_FLAGS_UINT,		{0x1110, 0, 1, 32}},
					{"HardErr1",			REGMEM_DESC_FLAGS_UINT,		{0x1110, 1, 1, 32}},
					{"HardErr2",			REGMEM_DESC_FLAGS_UINT,		{0x1110, 2, 1, 32}},
					{"HardErr3",			REGMEM_DESC_FLAGS_UINT,		{0x1110, 3, 1, 32}},
					{"LaneUp0",				REGMEM_DESC_FLAGS_UINT,		{0x1110, 4, 1, 32}},
					{"LaneUp1",				REGMEM_DESC_FLAGS_UINT,		{0x1110, 5, 1, 32}},
					{"LaneUp2",				REGMEM_DESC_FLAGS_UINT,		{0x1110, 6, 1, 32}},
					{"LaneUp3",				REGMEM_DESC_FLAGS_UINT,		{0x1110, 7, 1, 32}},
					{"RxPolarity0",		REGMEM_DESC_FLAGS_UINT,		{0x1110, 8, 1, 32}},
					{"RxPolarity1",		REGMEM_DESC_FLAGS_UINT,		{0x1110, 9, 1, 32}},
					{"RxPolarity2",		REGMEM_DESC_FLAGS_UINT,		{0x1110, 10, 1, 32}},
					{"RxPolarity3",		REGMEM_DESC_FLAGS_UINT,		{0x1110, 11, 1, 32}},
					{"ChannelUp",			REGMEM_DESC_FLAGS_UINT,		{0x1110, 12, 1, 32}},
					{"TxLock",				REGMEM_DESC_FLAGS_UINT,		{0x1110, 13, 1, 32}},
					{"RxSrcRdyN",			REGMEM_DESC_FLAGS_UINT,		{0x1110, 14, 1, 32}},
				{NULL, 0},
			{NULL, 0},
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "SSP_HPS"; }
	const char *GetModuleFullName() { return "Sub System Processor-HPS"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pSSPTabs;
};

#endif
