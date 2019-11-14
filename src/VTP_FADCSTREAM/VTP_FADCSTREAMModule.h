#ifndef VTP_FADCSTREAMModule_H
#define VTP_FADCSTREAMModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"

class VTP_FADCSTREAMModule : public ModuleFrame
{
public:
  VTP_HPSModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

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
      {"Z7", 0"},
        {"Clk", 0},
          {"GclkReset",           REGMEM_DESC_FLAGS_UINT,   {0x0100, 0, 1,32}},
          {"Clk40GbeReset",       REGMEM_DESC_FLAGS_UINT,   {0x0100, 1, 1,32}},
          {"IDelayReset",         REGMEM_DESC_FLAGS_UINT,   {0x0100, 2, 1,32}},
          {"GclkLocked",          REGMEM_DESC_FLAGS_UINT,   {0x0104, 0, 1,32}},
          {"PllLocked",           REGMEM_DESC_FLAGS_UINT,   {0x0104, 1, 1,32}},
          {"IDelayReady",         REGMEM_DESC_FLAGS_UINT,   {0x0104, 2, 1,32}},
          {"VersionMaj",          REGMEM_DESC_FLAGS_UINT,   {0x0108,16,16,32}},
          {"VersionMin",          REGMEM_DESC_FLAGS_UINT,   {0x0108, 0,16,32}},
          {"FirmwareType",        REGMEM_DESC_FLAGS_UINT,   {0x0110, 0,32,32}},
          {"CompileInfo", 0},
            {"Day",               REGMEM_DESC_FLAGS_UINT,   {0x0114,27, 5,32}},
            {"Month",             REGMEM_DESC_FLAGS_STRING, {0x0114,23, 4,32}, MONTH_MAP},
            {"Year",              REGMEM_DESC_FLAGS_STRING, {0x0114,17, 6,32}, YEAR_MAP},
            {"Hour",              REGMEM_DESC_FLAGS_UINT,   {0x0114,12, 5,32}},
            {"Min",               REGMEM_DESC_FLAGS_UINT,   {0x0114, 6, 6,32}},
            {"Sec",               REGMEM_DESC_FLAGS_UINT,   {0x0114, 0, 6,32}},
          {NULL, 0},
        {NULL, 0},

        {"TcpClient0", 0},
          {"Reset",               REGMEM_DESC_FLAGS_UINT,   {0x1000, 0, 1,32}},
          {"PhyCfgChg",           REGMEM_DESC_FLAGS_UINT,   {0x1000, 1, 1,32}},
          {"PhyReset",            REGMEM_DESC_FLAGS_UINT,   {0x1000, 2, 1,32}},
          {"PhyTestMode",         REGMEM_DESC_FLAGS_UINT,   {0x1000, 3, 2,32}},
          {"PhyPowerDown",        REGMEM_DESC_FLAGS_UINT,   {0x1000, 5, 1,32}},
          {"PMAPMDType",          REGMEM_DESC_FLAGS_UINT,   {0x1000, 6, 3,32}},
          {"SignalDet",           REGMEM_DESC_FLAGS_UINT,   {0x1000, 9, 1,32}},
          {"TxFault",             REGMEM_DESC_FLAGS_UINT,   {0x1000,10, 1,32}},
          {"Ip4Addr", 0},
            {"Byte0",             REGMEM_DESC_FLAGS_UINT,   {0x1010, 0, 8,32}},
            {"Byte1",             REGMEM_DESC_FLAGS_UINT,   {0x1010, 8, 8,32}},
            {"Byte2",             REGMEM_DESC_FLAGS_UINT,   {0x1010,16, 8,32}},
            {"Byte3",             REGMEM_DESC_FLAGS_UINT,   {0x1010,24, 8,32}},
          {NULL, 0},
          {"Ip4MAddr", 0},
            {"Byte0",             REGMEM_DESC_FLAGS_UINT,   {0x1014, 0, 8,32}},
            {"Byte1",             REGMEM_DESC_FLAGS_UINT,   {0x1014, 8, 8,32}},
            {"Byte2",             REGMEM_DESC_FLAGS_UINT,   {0x1014,16, 8,32}},
            {"Byte3",             REGMEM_DESC_FLAGS_UINT,   {0x1014,24, 8,32}},
          {NULL, 0},
          {"Ip4Mask", 0},
            {"Byte0",             REGMEM_DESC_FLAGS_UINT,   {0x1018, 0, 8,32}},
            {"Byte1",             REGMEM_DESC_FLAGS_UINT,   {0x1018, 8, 8,32}},
            {"Byte2",             REGMEM_DESC_FLAGS_UINT,   {0x1018,16, 8,32}},
            {"Byte3",             REGMEM_DESC_FLAGS_UINT,   {0x1018,24, 8,32}},
          {NULL, 0},
          {"Ip4Gateway", 0},
            {"Byte0",             REGMEM_DESC_FLAGS_UINT,   {0x101C, 0, 8,32}},
            {"Byte1",             REGMEM_DESC_FLAGS_UINT,   {0x101C, 8, 8,32}},
            {"Byte2",             REGMEM_DESC_FLAGS_UINT,   {0x101C,16, 8,32}},
            {"Byte3",             REGMEM_DESC_FLAGS_UINT,   {0x101C,24, 8,32}},
          {NULL, 0},
          {"TcpStateReq",         REGMEM_DESC_FLAGS_HEX,    {0x1020, 0, 8,32}},
          {"ConnReset",           REGMEM_DESC_FLAGS_HEX,    {0x1024, 0, 8,32}},
          {"TcpKeepAlive",        REGMEM_DESC_FLAGS_HEX,    {0x1028, 0, 8,32}},
          {"TcpStateStatus",      REGMEM_DESC_FLAGS_HEX,    {0x102C, 0,32,32}},
          {"TcpStatus",           REGMEM_DESC_FLAGS_HEX,    {0x1030, 0, 8,32}},
        {NULL, 0},

        {"TcpTextTx0", 0},
          {"GclkReset",           REGMEM_DESC_FLAGS_UINT,   {0x1800, 0, 1,32}},
        {NULL, 0},

        {"EBIORX0", 0},
          {"GclkReset",           REGMEM_DESC_FLAGS_UINT,   {0x2000, 0, 1,32}},
        {NULL, 0},
      {NULL, 0},

      {"V7", 0"},
        {"Clk", 0},
          {"GclkReset",           REGMEM_DESC_FLAGS_UINT,   {0x10100, 0, 1,32}},
          {"GclkLocked",          REGMEM_DESC_FLAGS_UINT,   {0x10104, 0, 1,32}},
          {"VersionMaj",          REGMEM_DESC_FLAGS_UINT,   {0x10108,16,16,32}},
          {"VersionMin",          REGMEM_DESC_FLAGS_UINT,   {0x10108, 0,16,32}},
          {"FirmwareType",        REGMEM_DESC_FLAGS_UINT,   {0x10110, 0,32,32}},
          {"CompileInfo", 0},
            {"Day",               REGMEM_DESC_FLAGS_UINT,   {0x10114,27, 5,32}},
            {"Month",             REGMEM_DESC_FLAGS_STRING, {0x10114,23, 4,32}, MONTH_MAP},
            {"Year",              REGMEM_DESC_FLAGS_STRING, {0x10114,17, 6,32}, YEAR_MAP},
            {"Hour",              REGMEM_DESC_FLAGS_UINT,   {0x10114,12, 5,32}},
            {"Min",               REGMEM_DESC_FLAGS_UINT,   {0x10114, 6, 6,32}},
            {"Sec",               REGMEM_DESC_FLAGS_UINT,   {0x10114, 0, 6,32}},
          {NULL, 0},
        {NULL, 0},
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
