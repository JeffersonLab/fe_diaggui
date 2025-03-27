#ifndef SSP_SBSEHCALModule_H
#define SSP_SBSEHCALModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "SSP_SBSEHCAL_CosmicScope.h"

class SSP_SBSEHCALModule	: public ModuleFrame
{
public:
  SSP_SBSEHCALModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    TGCompositeFrame *tFrame;
    AddFrame(pSSPTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

    SetupRegisters();
    tFrame = pSSPTabs->AddTab("CosmicScope"); tFrame->AddFrame(new SSP_SBSEHCAL_CosmicScope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

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
        {"Sd", 0},
          {"I/O Muxing", 0},
            {"FpOut0",            REGMEM_DESC_FLAGS_STRING, {0x0200, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"FpOut1",            REGMEM_DESC_FLAGS_STRING, {0x0204, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"FpOut2",            REGMEM_DESC_FLAGS_STRING, {0x0208, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"FpOut3",            REGMEM_DESC_FLAGS_STRING, {0x020C, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"FpOut4",            REGMEM_DESC_FLAGS_STRING, {0x0210, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"Gpio0",             REGMEM_DESC_FLAGS_STRING, {0x0214, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"Gpio1",             REGMEM_DESC_FLAGS_STRING, {0x0218, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out0",            REGMEM_DESC_FLAGS_STRING, {0x021C, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out1",            REGMEM_DESC_FLAGS_STRING, {0x0220, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out2",            REGMEM_DESC_FLAGS_STRING, {0x0224, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out3",            REGMEM_DESC_FLAGS_STRING, {0x0228, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out4",            REGMEM_DESC_FLAGS_STRING, {0x022C, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out5",            REGMEM_DESC_FLAGS_STRING, {0x0230, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out6",            REGMEM_DESC_FLAGS_STRING, {0x0234, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"P2Out7",            REGMEM_DESC_FLAGS_STRING, {0x0238, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"Trig",              REGMEM_DESC_FLAGS_STRING, {0x023C, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
            {"Sync",              REGMEM_DESC_FLAGS_STRING, {0x0240, 0, 5, 32}, SSP_SDIOMUX_NAME_MAP},
          {NULL, 0},
          {"Pulser", 0},
            {"Period",            REGMEM_DESC_FLAGS_UINT, {0x0280, 0, 32, 32}},
            {"LowCycles",         REGMEM_DESC_FLAGS_UINT, {0x0284, 0, 32, 32}},
            {"NPulses",           REGMEM_DESC_FLAGS_UINT, {0x0288, 0, 32, 32}},
            {"Start",             REGMEM_DESC_FLAGS_UINT, {0x028C, 0, 0, 32}},
            {"Done",              REGMEM_DESC_FLAGS_UINT, {0x0290, 0, 1, 32}},
          {NULL, 0},
          {"Scalers", 0},
            {"Disable",           REGMEM_DESC_FLAGS_UINT, {0x0300, 0, 1, 32}},
            {"SysClk50",          REGMEM_DESC_FLAGS_UINT, {0x0304, 0, 32, 32}},
            {"GClk250",           REGMEM_DESC_FLAGS_UINT, {0x0308, 0, 32, 32}},
            {"Sync",              REGMEM_DESC_FLAGS_UINT, {0x030C, 0, 32, 32}},
            {"Trig1",             REGMEM_DESC_FLAGS_UINT, {0x0310, 0, 32, 32}},
            {"Trig2",             REGMEM_DESC_FLAGS_UINT, {0x0314, 0, 32, 32}},
            {"Gpio0",             REGMEM_DESC_FLAGS_UINT, {0x0318, 0, 32, 32}},
            {"Gpio1",             REGMEM_DESC_FLAGS_UINT, {0x031C, 0, 32, 32}},
            {"FpIn0",             REGMEM_DESC_FLAGS_UINT, {0x0320, 0, 32, 32}},
            {"FpIn1",             REGMEM_DESC_FLAGS_UINT, {0x0324, 0, 32, 32}},
            {"FpIn2",             REGMEM_DESC_FLAGS_UINT, {0x0328, 0, 32, 32}},
            {"FpIn3",             REGMEM_DESC_FLAGS_UINT, {0x032C, 0, 32, 32}},
            {"FpIn4",             REGMEM_DESC_FLAGS_UINT, {0x0330, 0, 32, 32}},
            {"FpOut0",            REGMEM_DESC_FLAGS_UINT, {0x0334, 0, 32, 32}},
            {"FpOut1",            REGMEM_DESC_FLAGS_UINT, {0x0338, 0, 32, 32}},
            {"FpOut2",            REGMEM_DESC_FLAGS_UINT, {0x033C, 0, 32, 32}},
            {"FpOut3",            REGMEM_DESC_FLAGS_UINT, {0x0340, 0, 32, 32}},
            {"FpOut4",            REGMEM_DESC_FLAGS_UINT, {0x0344, 0, 32, 32}},
            {"Busy",              REGMEM_DESC_FLAGS_UINT, {0x0348, 0, 32, 32}},
            {"BusyCycles",        REGMEM_DESC_FLAGS_UINT, {0x034C, 0, 32, 32}},
            {"P2In0",             REGMEM_DESC_FLAGS_UINT, {0x0350, 0, 32, 32}},
            {"P2In1",             REGMEM_DESC_FLAGS_UINT, {0x0354, 0, 32, 32}},
            {"P2In2",             REGMEM_DESC_FLAGS_UINT, {0x0358, 0, 32, 32}},
            {"P2In3",             REGMEM_DESC_FLAGS_UINT, {0x035C, 0, 32, 32}},
            {"P2In4",             REGMEM_DESC_FLAGS_UINT, {0x0360, 0, 32, 32}},
            {"P2In5",             REGMEM_DESC_FLAGS_UINT, {0x0364, 0, 32, 32}},
            {"P2In6",             REGMEM_DESC_FLAGS_UINT, {0x0368, 0, 32, 32}},
            {"P2In7",             REGMEM_DESC_FLAGS_UINT, {0x036C, 0, 32, 32}},
            {"P2Out0",            REGMEM_DESC_FLAGS_UINT, {0x0370, 0, 32, 32}},
            {"P2Out1",            REGMEM_DESC_FLAGS_UINT, {0x0374, 0, 32, 32}},
            {"P2Out2",            REGMEM_DESC_FLAGS_UINT, {0x0378, 0, 32, 32}},
            {"P2Out3",            REGMEM_DESC_FLAGS_UINT, {0x037C, 0, 32, 32}},
            {"P2Out4",            REGMEM_DESC_FLAGS_UINT, {0x0380, 0, 32, 32}},
            {"P2Out5",            REGMEM_DESC_FLAGS_UINT, {0x0384, 0, 32, 32}},
            {"P2Out6",            REGMEM_DESC_FLAGS_UINT, {0x0388, 0, 32, 32}},
            {"P2Out7",            REGMEM_DESC_FLAGS_UINT, {0x038C, 0, 32, 32}},
          {NULL, 0},
        {NULL, 0},
	{"FiberDecoder", 0},
          {"EnableMask",          REGMEM_DESC_FLAGS_HEX,  {0x6000, 0, 8, 32}},
        {NULL, 0},
	{"CosmicTrgBit", 0},
          {"TrgLatency",          REGMEM_DESC_FLAGS_UINT, {0x6100, 0,11, 32}},
          {"TrgWidth",            REGMEM_DESC_FLAGS_UINT, {0x6100,11, 8, 32}},
          {"Mult",                REGMEM_DESC_FLAGS_UINT, {0x6100,19, 3, 32}},
          {"EnMask",              REGMEM_DESC_FLAGS_UINT, {0x6100,22, 7, 32}},
          {"LatencyStatus",       REGMEM_DESC_FLAGS_UINT, {0x6104, 0,11, 32}},
        {NULL, 0},
	{"AuxTrgBit", 0},
          {"TrgLatency",          REGMEM_DESC_FLAGS_UINT, {0x6500, 0,11, 32}},
          {"TrgWidth",            REGMEM_DESC_FLAGS_UINT, {0x6500,11, 8, 32}},
          {"Mult",                REGMEM_DESC_FLAGS_UINT, {0x6500,19, 3, 32}},
          {"EnMask",              REGMEM_DESC_FLAGS_UINT, {0x6500,22, 7, 32}},
          {"LatencyStatus",       REGMEM_DESC_FLAGS_UINT, {0x6504, 0,11, 32}},
        {NULL, 0},
	{"EHTrgBit", 0},
          {"TrgLatency",          REGMEM_DESC_FLAGS_UINT, {0x6200, 0,11, 32}},
          {"TrgWidth",            REGMEM_DESC_FLAGS_UINT, {0x6200,11, 8, 32}},
          {"LatencyStatus",       REGMEM_DESC_FLAGS_UINT, {0x6204, 0,11, 32}},
          {"Delay",               REGMEM_DESC_FLAGS_UINT, {0x6210, 0, 8, 32}},
        {NULL, 0},
	{"ETrgBit", 0},
          {"TrgLatency",          REGMEM_DESC_FLAGS_UINT, {0x6300, 0,11, 32}},
          {"TrgWidth",            REGMEM_DESC_FLAGS_UINT, {0x6300,11, 8, 32}},
          {"LatencyStatus",       REGMEM_DESC_FLAGS_UINT, {0x6304, 0,11, 32}},
          {"Delay",               REGMEM_DESC_FLAGS_UINT, {0x6310, 0, 8, 32}},
        {NULL, 0},
	{"HTrgBit", 0},
          {"TrgLatency",          REGMEM_DESC_FLAGS_UINT, {0x6400, 0,11, 32}},
          {"TrgWidth",            REGMEM_DESC_FLAGS_UINT, {0x6400,11, 8, 32}},
          {"LatencyStatus",       REGMEM_DESC_FLAGS_UINT, {0x6404, 0,11, 32}},
          {"Delay",               REGMEM_DESC_FLAGS_UINT, {0x6410, 0, 8, 32}},
        {NULL, 0},
        {"SerDes", 0},
          {"F0", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1010, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1010, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1010, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1010, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1010, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1000, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1034,16,12, 32}},
          {NULL, 0},
          {"F1", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1110, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1110, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1110, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1110, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1110, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1100, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1134,16,12, 32}},
          {NULL, 0},
          {"F2", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1210, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1210, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1210, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1210, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1210, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1200, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1234,16,12, 32}},
          {NULL, 0},
          {"F3", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1310, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1310, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1310, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1310, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1310, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1300, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1334,16,12, 32}},
          {NULL, 0},
          {"F4", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1410, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1410, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1410, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1410, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1410, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1400, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1434,16,12, 32}},
          {NULL, 0},
          {"F5", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1510, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1510, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1510, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1510, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1510, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1500, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1534,16,12, 32}},
          {NULL, 0},
          {"F6", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1610, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1610, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1610, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1610, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1610, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1600, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1634,16,12, 32}},
          {NULL, 0},
          {"F7", 0},
            {"ChannelUp",         REGMEM_DESC_FLAGS_UINT, {0x1710, 0, 1, 32}},
            {"LaneUp0",           REGMEM_DESC_FLAGS_UINT, {0x1710, 1, 1, 32}},
            {"LaneUp1",           REGMEM_DESC_FLAGS_UINT, {0x1710, 2, 1, 32}},
            {"LaneUp2",           REGMEM_DESC_FLAGS_UINT, {0x1710, 3, 1, 32}},
            {"LaneUp3",           REGMEM_DESC_FLAGS_UINT, {0x1710, 4, 1, 32}},
            {"PowerDown",         REGMEM_DESC_FLAGS_UINT, {0x1700, 0, 1, 32}},
            {"Latency",           REGMEM_DESC_FLAGS_UINT, {0x1734,16,12, 32}},
          {NULL, 0},
        {NULL, 0},
        {"Scalers", 0},
          {"Disable",             REGMEM_DESC_FLAGS_UINT,   {0x0300, 0, 1, 32}},
          {"SysClk50",            REGMEM_DESC_FLAGS_UINT,   {0x0304, 0, 32, 32}},
          {"GClk250",             REGMEM_DESC_FLAGS_UINT,   {0x0308, 0, 32, 32}},
          {"Sync",                REGMEM_DESC_FLAGS_UINT,   {0x030C, 0, 32, 32}},
          {"Trig1",               REGMEM_DESC_FLAGS_UINT,   {0x0310, 0, 32, 32}},
          {"Trig2",               REGMEM_DESC_FLAGS_UINT,   {0x0314, 0, 32, 32}},
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
