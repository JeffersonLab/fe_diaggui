#ifndef VTP_FADCSTREAMModule_H
#define VTP_FADCSTREAMModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "VTP_FADCSTREAM_Scope.h"
#include "VTP_FADCSTREAM_Scope2.h"

class VTP_FADCSTREAMModule : public ModuleFrame
{
public:
  VTP_FADCSTREAMModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
//    tFrame = pTabs->AddTab("Scope");      tFrame->AddFrame(new VTP_FADCSTREAM_Scope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//    tFrame = pTabs->AddTab("Scope2");     tFrame->AddFrame(new VTP_FADCSTREAM_Scope2(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

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
        {"Statis",              REGMEM_DESC_FLAGS_HEX,    {0x9004, 0,32,32}},
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
        {"UDP_DEST_IP_ADDR",    REGMEM_DESC_FLAGS_HEX,    {0x9064, 0,32,32}},
        {"UDP_PORT",            REGMEM_DESC_FLAGS_HEX,    {0x9068, 0,32,32}},
        {"DEST_ADDR",           REGMEM_DESC_FLAGS_HEX,    {0x9080, 0,32,32}},
        {"DEST_PORT",           REGMEM_DESC_FLAGS_HEX,    {0x90A0, 0,32,32}},
      {NULL, 0},
    };

    pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
  }

  const char *GetModuleName() { return "VTP_FADCSTREAM"; }
  const char *GetModuleFullName() { return "VXS Trigger Processor-FADC Streaming"; }
  const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
  TString     strSlotIdentifier;
  TGTab       *pTabs;
};

#endif
