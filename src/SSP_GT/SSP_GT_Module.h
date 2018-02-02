#ifndef SSP_GT_Module_H
#define SSP_GT_Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "SSP_GTSerialScopeVXS.h"
#include "SSP_GTSerialScopeQSFP.h"

class SSP_GT_Module	: public ModuleFrame
{
public:
	SSP_GT_Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pSSPTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("SWA VXS 1");   tFrame->AddFrame(new SSP_GTSerialScopeVXS(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      
      tFrame = pSSPTabs->AddTab("QSFP 0");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 1");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 2");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 3");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 4");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 5");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 6");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
      tFrame = pSSPTabs->AddTab("QSFP 7");   tFrame->AddFrame(new SSP_GTSerialScopeQSFP(tFrame, this, 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

      
//		tFrame = pSSPTabs->AddTab("Config");		tFrame->AddFrame(pSSPConfig = new SSP_Config(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Histograms");	tFrame->AddFrame(pSSPHistograms = new SSP_Histograms(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

//		tFrame = pSSPTabs->AddTab("SumHist");		tFrame->AddFrame(new SSP_SumHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Status");		tFrame->AddFrame(new SSP_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 0");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Fiber 1");		tFrame->AddFrame(new SSP_SerialScope(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
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
    static RegMemDesc regs[] = {
      {"Config", 0},
        {"Spi", 0},
          {"WrData",            REGMEM_DESC_FLAGS_HEX,    {0x0008, 0, 8, 32}},
          {"RdData",            REGMEM_DESC_FLAGS_HEX,    {0x000C, 0, 8, 32}},
          {"NCSSet",            REGMEM_DESC_FLAGS_UINT,   {0x0008, 8, 1, 32}},
          {"NCSClear",          REGMEM_DESC_FLAGS_UINT,   {0x0008, 9, 1, 32}},
          {"Start",             REGMEM_DESC_FLAGS_UINT,   {0x0008, 10, 1, 32}},
          {"Done",              REGMEM_DESC_FLAGS_UINT,   {0x000C, 11, 1, 32}},
        {NULL, 0},
        {"BoardId",             REGMEM_DESC_FLAGS_HEX,    {0x0000, 0, 32, 32}},
        {"FirmwareRev",         REGMEM_DESC_FLAGS_HEX,    {0x0004, 0, 32, 32}},
      {NULL, 0},
      {"Clk", 0},
        {"Drp", 0},
          {"Addr",              REGMEM_DESC_FLAGS_HEX,    {0x0100, 16, 5, 32}},
          {"WrEn",              REGMEM_DESC_FLAGS_UINT,   {0x0100, 21, 1, 32}},
          {"Den",               REGMEM_DESC_FLAGS_UINT,   {0x0100, 22, 1, 32}},
          {"WrData",            REGMEM_DESC_FLAGS_HEX,    {0x0100, 0, 16, 32}},
          {"RdData",            REGMEM_DESC_FLAGS_HEX,    {0x0104, 0, 16, 32}},
          {"RdDataValid",       REGMEM_DESC_FLAGS_UINT,   {0x0104, 16, 1, 32}},
        {NULL, 0},
        {"ClkSerdes",           REGMEM_DESC_FLAGS_STRING, {0x0100, 24, 2, 32}, {4,{"DISABLED","VXS","P2","LOCAL"},{0,1,2,3}}},
        {"ClkLogic",            REGMEM_DESC_FLAGS_STRING, {0x0100, 26, 2, 32}, {4,{"DISABLED","VXS","P2","LOCAL"},{0,1,2,3}}},
        {"ClkPllReset",         REGMEM_DESC_FLAGS_UINT,   {0x0100, 31, 1, 32}},
        {"ClkPllLocked",        REGMEM_DESC_FLAGS_UINT,   {0x0104, 17, 1, 32}},
      {NULL, 0},
      {"ECal", 0},
        {"ESum", 0},
          {"Delay",             REGMEM_DESC_FLAGS_UINT,   {0x2200, 0, 10, 32}},
          {"IntWidth",          REGMEM_DESC_FLAGS_UINT,   {0x2210, 0, 6, 32}},
        {NULL, 0},
        {"Cluster", 0},
          {"Delay",             REGMEM_DESC_FLAGS_UINT,   {0x2204, 0, 10, 32}},
        {NULL, 0},
      {NULL, 0},
      {"PCal", 0},
        {"ESum", 0},
          {"Delay",             REGMEM_DESC_FLAGS_UINT,   {0x2300, 0, 10, 32}},
          {"IntWidth",          REGMEM_DESC_FLAGS_UINT,   {0x2310, 0, 6, 32}},
        {NULL, 0},
        {"Cluster", 0},
          {"Delay",             REGMEM_DESC_FLAGS_UINT,   {0x2304, 0, 10, 32}},
        {NULL, 0},
      {NULL, 0},      
      {"STrigger0", 0},
        {"En",                  REGMEM_DESC_FLAGS_UINT,   {0x3000,  0,  1, 32}},
        {"Pcal", 0},
          {"ClusterEn",         REGMEM_DESC_FLAGS_UINT,   {0x3000,  1,  1, 32}},
          {"ClusterEmin",       REGMEM_DESC_FLAGS_UINT,   {0x3020,  0, 14, 32}},
          {"ClusterWidth",      REGMEM_DESC_FLAGS_UINT,   {0x3020, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3000,  4,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3014,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3014, 16,  8, 32}},
        {NULL, 0},
        {"Ecal", 0},
          {"OuterClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3000,  2,  1, 32}},
          {"OuterClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x301C,  0, 14, 32}},
          {"OuterClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x301C, 16,  8, 32}},
          {"InnerClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3000,  3,  1, 32}},
          {"InnerClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x3018,  0, 14, 32}},
          {"InnerClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x3018, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3000,  5,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3010,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3010, 16,  8, 32}},
        {NULL, 0},
      {NULL, 0},
      {"STrigger1", 0},
        {"En",                  REGMEM_DESC_FLAGS_UINT,   {0x3100,  0,  1, 32}},
        {"Pcal", 0},
          {"ClusterEn",         REGMEM_DESC_FLAGS_UINT,   {0x3100,  1,  1, 32}},
          {"ClusterEmin",       REGMEM_DESC_FLAGS_UINT,   {0x3120,  0, 14, 32}},
          {"ClusterWidth",      REGMEM_DESC_FLAGS_UINT,   {0x3120, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3100,  4,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3114,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3114, 16,  8, 32}},
        {NULL, 0},
        {"Ecal", 0},
          {"OuterClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3100,  2,  1, 32}},
          {"OuterClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x311C,  0, 14, 32}},
          {"OuterClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x311C, 16,  8, 32}},
          {"InnerClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3100,  3,  1, 32}},
          {"InnerClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x3118,  0, 14, 32}},
          {"InnerClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x3118, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3100,  5,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3110,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3110, 16,  8, 32}},
        {NULL, 0},
      {NULL, 0},
      {"STrigger2", 0},
        {"En",                  REGMEM_DESC_FLAGS_UINT,   {0x3200,  0,  1, 32}},
        {"Pcal", 0},
          {"ClusterEn",         REGMEM_DESC_FLAGS_UINT,   {0x3200,  1,  1, 32}},
          {"ClusterEmin",       REGMEM_DESC_FLAGS_UINT,   {0x3220,  0, 14, 32}},
          {"ClusterWidth",      REGMEM_DESC_FLAGS_UINT,   {0x3220, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3200,  4,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3214,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3214, 16,  8, 32}},
        {NULL, 0},
        {"Ecal", 0},
          {"OuterClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3200,  2,  1, 32}},
          {"OuterClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x321C,  0, 14, 32}},
          {"OuterClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x321C, 16,  8, 32}},
          {"InnerClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3200,  3,  1, 32}},
          {"InnerClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x3218,  0, 14, 32}},
          {"InnerClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x3218, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3200,  5,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3210,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3210, 16,  8, 32}},
        {NULL, 0},
      {NULL, 0},
      {"STrigger3", 0},
        {"En",                  REGMEM_DESC_FLAGS_UINT,   {0x3300,  0,  1, 32}},
        {"Pcal", 0},
          {"ClusterEn",         REGMEM_DESC_FLAGS_UINT,   {0x3300,  1,  1, 32}},
          {"ClusterEmin",       REGMEM_DESC_FLAGS_UINT,   {0x3320,  0, 14, 32}},
          {"ClusterWidth",      REGMEM_DESC_FLAGS_UINT,   {0x3320, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3300,  4,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3314,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3314, 16,  8, 32}},
        {NULL, 0},
        {"Ecal", 0},
          {"OuterClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3300,  2,  1, 32}},
          {"OuterClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x331C,  0, 14, 32}},
          {"OuterClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x331C, 16,  8, 32}},
          {"InnerClusterEn",    REGMEM_DESC_FLAGS_UINT,   {0x3300,  3,  1, 32}},
          {"InnerClusterEmin",  REGMEM_DESC_FLAGS_UINT,   {0x3318,  0, 14, 32}},
          {"InnerClusterWidth", REGMEM_DESC_FLAGS_UINT,   {0x3318, 16,  8, 32}},
          {"SumEn",             REGMEM_DESC_FLAGS_UINT,   {0x3300,  5,  1, 32}},
          {"SumEmin",           REGMEM_DESC_FLAGS_UINT,   {0x3310,  0, 14, 32}},
          {"SumWidth",          REGMEM_DESC_FLAGS_UINT,   {0x3310, 16,  8, 32}},
        {NULL, 0},
      {NULL, 0},
      {"GtpIf", 0},
        {"Latency",             REGMEM_DESC_FLAGS_UINT,   {0x2400, 0, 11, 32}},
      {NULL, 0},
      {"Scalers", 0},
        {"Disable",             REGMEM_DESC_FLAGS_UINT,   {0x0300, 0, 1, 32}},
        {"SysClk50",            REGMEM_DESC_FLAGS_UINT,   {0x0304, 0, 32, 32}},
        {"GClk250",             REGMEM_DESC_FLAGS_UINT,   {0x0308, 0, 32, 32}},
        {"Sync",                REGMEM_DESC_FLAGS_UINT,   {0x030C, 0, 32, 32}},
        {"Trig1",               REGMEM_DESC_FLAGS_UINT,   {0x0310, 0, 32, 32}},
        {"Trig2",               REGMEM_DESC_FLAGS_UINT,   {0x0314, 0, 32, 32}},
        {"ECInnerCluster",      REGMEM_DESC_FLAGS_UINT,   {0x2220, 0, 32, 32}},
        {"ECOuterCluster",      REGMEM_DESC_FLAGS_UINT,   {0x2224, 0, 32, 32}},
        {"PCCluster",           REGMEM_DESC_FLAGS_UINT,   {0x2320, 0, 32, 32}},
        {"STrigger0",           REGMEM_DESC_FLAGS_UINT,   {0x3030, 0, 32, 32}},
        {"STrigger1",           REGMEM_DESC_FLAGS_UINT,   {0x3130, 0, 32, 32}},
        {"STrigger2",           REGMEM_DESC_FLAGS_UINT,   {0x3230, 0, 32, 32}},
        {"STrigger3",           REGMEM_DESC_FLAGS_UINT,   {0x3330, 0, 32, 32}},
      {NULL, 0},
		};

    pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "SSP"; }
	const char *GetModuleFullName() { return "Sub System Processor"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pSSPTabs;
};

#endif
