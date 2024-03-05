#ifndef VTP_ROCModule_H
#define VTP_ROCModule_H

#include "RootHeader.h"
#include "VTP_ROC_Scope.h"
#include "VTP_Status.h"
#include "ModuleFrame.h"

class VTP_ROCModule : public ModuleFrame
{
public:
  VTP_ROCModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

 
    tFrame = pTabs->AddTab("Status");   tFrame->AddFrame(new VTP_Status(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

//    tFrame = pTabs->AddTab("TrgHist");   tFrame->AddFrame(new VTP_HPS_TrgHist(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//    tFrame = pTabs->AddTab("PairTrg");   tFrame->AddFrame(new VTP_HPS_PairTrg(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("Scope");      tFrame->AddFrame(new VTP_ROC_Scope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    strSlotIdentifier.Form("SWA");
  }

  void SetupRegisters()
  {
#define MONTH_MAP {\
      12,\
      {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"},\
      {1,2,3,4,5,6,7,8,9,10,11,12}\
    }

#define YEAR_MAP {\
      64,\
      {"2000","2001","2002","2003","2004","2005","2006","2007",\
       "2008","2009","2010","2011","2012","2013","2014","2015",\
       "2016","2017","2018","2019","2020","2021","2022","2023",\
       "2024","2025","2026","2027","2028","2029","2030","2031",\
       "2032","2033","2034","2035","2036","2037","2038","2039",\
       "2040","2041","2042","2043","2044","2045","2046","2047",\
       "2048","2049","2050","2051","2052","2053","2054","2055",\
       "2056","2057","2058","2059","2060","2061","2062","2063"},\
     {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
      16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,\
      32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,\
      48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63}\
    }

    static RegMemDesc regs[] = {
      {"Clk", 0},
        {"GclkReset",           REGMEM_DESC_FLAGS_UINT,   {0x8100, 0, 1,32}},
        {"GclkLocked",          REGMEM_DESC_FLAGS_UINT,   {0x8104, 0, 1,32}},
        {"VersionMaj",          REGMEM_DESC_FLAGS_UINT,   {0x8108,16,16,32}},
        {"VersionMin",          REGMEM_DESC_FLAGS_UINT,   {0x8108, 0,16,32}},
        {"FirmwareType",        REGMEM_DESC_FLAGS_UINT,   {0x8110, 0,32,32}},
        {"CompileInfo", 0},
          {"Day",               REGMEM_DESC_FLAGS_UINT,   {0x8114,27, 5,32}},
          {"Month",             REGMEM_DESC_FLAGS_STRING, {0x8114,23, 4,32}, MONTH_MAP},
          {"Year",              REGMEM_DESC_FLAGS_STRING, {0x8114,17, 6,32}, YEAR_MAP},
          {"Hour",              REGMEM_DESC_FLAGS_UINT,   {0x8114,12, 5,32}},
          {"Min",               REGMEM_DESC_FLAGS_UINT,   {0x8114, 6, 6,32}},
          {"Sec",               REGMEM_DESC_FLAGS_UINT,   {0x8114, 0, 6,32}},
        {NULL, 0},
      {NULL, 0},

      {"TCPIP0", 0},
        {"Ctrl",                REGMEM_DESC_FLAGS_HEX,    {0x9000, 0,32,32}},
        {"Addr",                REGMEM_DESC_FLAGS_HEX,    {0x9010, 0,32,32}},
        {"MCastAddr",           REGMEM_DESC_FLAGS_HEX,    {0x9014, 0,32,32}},
        {"SubnetMask",          REGMEM_DESC_FLAGS_HEX,    {0x9018, 0,32,32}},
        {"GatewayAddr",         REGMEM_DESC_FLAGS_HEX,    {0x901C, 0,32,32}},
        {"StateRequest",        REGMEM_DESC_FLAGS_HEX,    {0x9020, 0,32,32}},
        {"ConnectionRequest",   REGMEM_DESC_FLAGS_HEX,    {0x9024, 0,32,32}},
        {"TCPKeepAlive",        REGMEM_DESC_FLAGS_HEX,    {0x9028, 0,32,32}},
        {"TCPStateStatus",      REGMEM_DESC_FLAGS_HEX,    {0x902C, 0,32,32}},
        {"TCPStatus",           REGMEM_DESC_FLAGS_HEX,    {0x9030, 0,32,32}},
        {"MAC_ADDR0",           REGMEM_DESC_FLAGS_HEX,    {0x9034, 0,32,32}},
        {"MAC_ADDR1",           REGMEM_DESC_FLAGS_HEX,    {0x9038, 0,32,32}},
        {"MAC_STATUS0",         REGMEM_DESC_FLAGS_HEX,    {0x903C, 0,32,32}},
        {"MAC_STATUS1",         REGMEM_DESC_FLAGS_HEX,    {0x9040, 0,32,32}},
        {"MAC_STATUS2",         REGMEM_DESC_FLAGS_HEX,    {0x9044, 0,32,32}},
        {"MAC_STATUS3",         REGMEM_DESC_FLAGS_HEX,    {0x9048, 0,32,32}},
        {"PCS_STATUS",          REGMEM_DESC_FLAGS_HEX,    {0x9050, 0,32,32}},
        {"PHY_STATUS",          REGMEM_DESC_FLAGS_HEX,    {0x9060, 0,32,32}},
        {"DEST_ADDR",           REGMEM_DESC_FLAGS_HEX,    {0x9084, 0,32,32}},
        {"DEST_PORT",           REGMEM_DESC_FLAGS_HEX,    {0x90A4, 0,32,32}},
      {NULL, 0},
/*
      {"PayloadDecoder", 0},
        {"RXLatency", 0},
          {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x1E34, 16, 12, 32}},
          {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x1C34, 16, 12, 32}},
          {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x1A34, 16, 12, 32}},
          {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x1834, 16, 12, 32}},
          {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x1634, 16, 12, 32}},
          {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x1434, 16, 12, 32}},
          {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x1234, 16, 12, 32}},
          {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x1034, 16, 12, 32}},
          {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x1134, 16, 12, 32}},
          {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x1334, 16, 12, 32}},
          {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x1534, 16, 12, 32}},
          {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x1734, 16, 12, 32}},
          {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x1934, 16, 12, 32}},
          {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x1B34, 16, 12, 32}},
          {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x1D34, 16, 12, 32}},
          {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x1F34, 16, 12, 32}},
        {NULL, 0},

        {"PayloadEnable", 0},
          {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x0300, 14,  1, 32}},
          {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x0300, 12,  1, 32}},
          {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x0300, 10,  1, 32}},
          {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x0300,  8,  1, 32}},
          {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x0300,  6,  1, 32}},
          {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x0300,  4,  1, 32}},
          {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x0300,  2,  1, 32}},
          {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x0300,  0,  1, 32}},
          {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x0300,  1,  1, 32}},
          {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x0300,  3,  1, 32}},
          {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x0300,  5,  1, 32}},
          {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x0300,  7,  1, 32}},
          {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x0300,  9,  1, 32}},
          {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x0300, 11,  1, 32}},
          {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x0300, 13,  1, 32}},
          {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x0300, 15,  1, 32}},        
        {NULL, 0},
      {NULL, 0},
*/

/*      {"v7eventbuilder", 0},
        {"ctrl",              REGMEM_DESC_FLAGS_HEX,  {0x0A00, 0, 32, 32}},
        {"eviocfg0",          REGMEM_DESC_FLAGS_HEX,  {0x0A10, 0, 32, 32}},
        {"eviocfg1",          REGMEM_DESC_FLAGS_HEX,  {0x0A14, 0, 32, 32}},
        {"eviocfg2",          REGMEM_DESC_FLAGS_HEX,  {0x0A18, 0, 32, 32}},
        {"payloadcfg0",       REGMEM_DESC_FLAGS_HEX,  {0x0A20, 0, 32, 32}},
        {"payloadcfg1",       REGMEM_DESC_FLAGS_HEX,  {0x0A24, 0, 32, 32}},
        {"payloadcfg2",       REGMEM_DESC_FLAGS_HEX,  {0x0A28, 0, 32, 32}},
        {"payloadcfg3",       REGMEM_DESC_FLAGS_HEX,  {0x0A2C, 0, 32, 32}},
        {"payloadcfg4",       REGMEM_DESC_FLAGS_HEX,  {0x0A30, 0, 32, 32}},
        {"payloadcfg5",       REGMEM_DESC_FLAGS_HEX,  {0x0A34, 0, 32, 32}},
        {"payloadcfg6",       REGMEM_DESC_FLAGS_HEX,  {0x0A38, 0, 32, 32}},
        {"payloadcfg7",       REGMEM_DESC_FLAGS_HEX,  {0x0A3C, 0, 32, 32}},
        {"payloadcfg8",       REGMEM_DESC_FLAGS_HEX,  {0x0A40, 0, 32, 32}},
        {"payloadcfg9",       REGMEM_DESC_FLAGS_HEX,  {0x0A44, 0, 32, 32}},
        {"payloadcfg10",      REGMEM_DESC_FLAGS_HEX,  {0x0A48, 0, 32, 32}},
        {"payloadcfg11",      REGMEM_DESC_FLAGS_HEX,  {0x0A4C, 0, 32, 32}},
        {"payloadcfg12",      REGMEM_DESC_FLAGS_HEX,  {0x0A50, 0, 32, 32}},
        {"payloadcfg13",      REGMEM_DESC_FLAGS_HEX,  {0x0A54, 0, 32, 32}},
        {"payloadcfg14",      REGMEM_DESC_FLAGS_HEX,  {0x0A58, 0, 32, 32}},
        {"payloadcfg15",      REGMEM_DESC_FLAGS_HEX,  {0x0A5C, 0, 32, 32}},
      {NULL, 0},

      {"mpd_fiber_per_0", 0},
        {"ctrl.enable",       REGMEM_DESC_FLAGS_UINT, {0xA020, 0,  1, 32}},
        {"ctrl.buildall",     REGMEM_DESC_FLAGS_UINT, {0xA020, 1,  1, 32}},
        {"ctrl.builddebug",   REGMEM_DESC_FLAGS_UINT, {0xA020, 2,  1, 32}},
        {"ctrl.enablecm",     REGMEM_DESC_FLAGS_UINT, {0xA020, 3,  1, 32}},
      {NULL, 0},
      {"mpd_fiber_per_7", 0},
        {"ctrl.enable",       REGMEM_DESC_FLAGS_UINT, {0xA1E0, 0,  1, 32}},
        {"ctrl.buildall",     REGMEM_DESC_FLAGS_UINT, {0xA1E0, 1,  1, 32}},
        {"ctrl.builddebug",   REGMEM_DESC_FLAGS_UINT, {0xA1E0, 2,  1, 32}},
        {"ctrl.enablecm",     REGMEM_DESC_FLAGS_UINT, {0xA1E0, 3,  1, 32}},
      {NULL, 0},

      {"Scalers", 0},
        {"Disable",       REGMEM_DESC_FLAGS_UINT, {0x0208,  0,  1, 32}},
        {"BusClk",        REGMEM_DESC_FLAGS_UINT, {0x0270,  0, 32, 32}},
        {"Sync",          REGMEM_DESC_FLAGS_UINT, {0x0274,  0, 32, 32}},
        {"Trig1",         REGMEM_DESC_FLAGS_UINT, {0x0278,  0, 32, 32}},
        {"Trig2",         REGMEM_DESC_FLAGS_UINT, {0x027C,  0, 32, 32}},
        {"FPA0",          REGMEM_DESC_FLAGS_UINT, {0x0280,  0, 32, 32}},
        {"FPA1",          REGMEM_DESC_FLAGS_UINT, {0x0284,  0, 32, 32}},
        {"FPA2",          REGMEM_DESC_FLAGS_UINT, {0x0288,  0, 32, 32}},
        {"FPA3",          REGMEM_DESC_FLAGS_UINT, {0x028C,  0, 32, 32}},
        {"FPA4",          REGMEM_DESC_FLAGS_UINT, {0x0290,  0, 32, 32}},
        {"FPA5",          REGMEM_DESC_FLAGS_UINT, {0x0294,  0, 32, 32}},
        {"FPA6",          REGMEM_DESC_FLAGS_UINT, {0x0298,  0, 32, 32}},
        {"FPA7",          REGMEM_DESC_FLAGS_UINT, {0x029C,  0, 32, 32}},
        {"FPA8",          REGMEM_DESC_FLAGS_UINT, {0x02A0,  0, 32, 32}},
        {"FPA9",          REGMEM_DESC_FLAGS_UINT, {0x02A4,  0, 32, 32}},
        {"FPA10",         REGMEM_DESC_FLAGS_UINT, {0x02A8,  0, 32, 32}},
        {"FPA11",         REGMEM_DESC_FLAGS_UINT, {0x02AC,  0, 32, 32}},
        {"FPA12",         REGMEM_DESC_FLAGS_UINT, {0x02B0,  0, 32, 32}},
        {"FPA13",         REGMEM_DESC_FLAGS_UINT, {0x02B4,  0, 32, 32}},
        {"FPA14",         REGMEM_DESC_FLAGS_UINT, {0x02B8,  0, 32, 32}},
        {"FPA15",         REGMEM_DESC_FLAGS_UINT, {0x02BC,  0, 32, 32}},
      {NULL, 0},
*/
    };

    pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
  }

  const char *GetModuleName() { return "VTP_ROC"; }
  const char *GetModuleFullName() { return "VXS Trigger Processor-ROC"; }
  const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
  TString     strSlotIdentifier;
  TGTab       *pTabs;
};

#endif
