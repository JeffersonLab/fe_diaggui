#ifndef VTP_SBSECALModule_H
#define VTP_SBSECALModule_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "VTP_SBSECAL_Scope.h"

class VTP_SBSECALModule : public ModuleFrame
{
public:
  VTP_SBSECALModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

    tFrame = pTabs->AddTab("Scope");      tFrame->AddFrame(new VTP_SBSECAL_Scope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

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
        {"GclkReset",           REGMEM_DESC_FLAGS_UINT,   {0x0100, 0, 1,32}},
        {"GclkLocked",          REGMEM_DESC_FLAGS_UINT,   {0x0104, 0, 1,32}},
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

        {"Ctrl", 0},
          {"Sl3,PP15",        REGMEM_DESC_FLAGS_HEX, {0x1E00,  0, 32, 32}},
          {"Sl4,PP13",        REGMEM_DESC_FLAGS_HEX, {0x1C00,  0, 32, 32}},
          {"Sl5,PP11",        REGMEM_DESC_FLAGS_HEX, {0x1A00,  0, 32, 32}},
          {"Sl6,PP9",         REGMEM_DESC_FLAGS_HEX, {0x1800,  0, 32, 32}},
          {"Sl7,PP7",         REGMEM_DESC_FLAGS_HEX, {0x1600,  0, 32, 32}},
          {"Sl8,PP5",         REGMEM_DESC_FLAGS_HEX, {0x1400,  0, 32, 32}},
          {"Sl9,PP3",         REGMEM_DESC_FLAGS_HEX, {0x1200,  0, 32, 32}},
          {"Sl10,PP1",        REGMEM_DESC_FLAGS_HEX, {0x1000,  0, 32, 32}},
          {"Sl13,PP2",        REGMEM_DESC_FLAGS_HEX, {0x1100,  0, 32, 32}},
          {"Sl14,PP4",        REGMEM_DESC_FLAGS_HEX, {0x1300,  0, 32, 32}},
          {"Sl15,PP6",        REGMEM_DESC_FLAGS_HEX, {0x1500,  0, 32, 32}},
          {"Sl16,PP8",        REGMEM_DESC_FLAGS_HEX, {0x1700,  0, 32, 32}},
          {"Sl17,PP10",       REGMEM_DESC_FLAGS_HEX, {0x1900,  0, 32, 32}},
          {"Sl18,PP12",       REGMEM_DESC_FLAGS_HEX, {0x1B00,  0, 32, 32}},
          {"Sl19,PP14",       REGMEM_DESC_FLAGS_HEX, {0x1D00,  0, 32, 32}},
          {"Sl20,PP16",       REGMEM_DESC_FLAGS_HEX, {0x1F00,  0, 32, 32}},
        {NULL, 0},

        {"Status", 0},
          {"Sl3,PP15",        REGMEM_DESC_FLAGS_HEX, {0x1E04,  0, 32, 32}},
          {"Sl4,PP13",        REGMEM_DESC_FLAGS_HEX, {0x1C04,  0, 32, 32}},
          {"Sl5,PP11",        REGMEM_DESC_FLAGS_HEX, {0x1A04,  0, 32, 32}},
          {"Sl6,PP9",         REGMEM_DESC_FLAGS_HEX, {0x1804,  0, 32, 32}},
          {"Sl7,PP7",         REGMEM_DESC_FLAGS_HEX, {0x1604,  0, 32, 32}},
          {"Sl8,PP5",         REGMEM_DESC_FLAGS_HEX, {0x1404,  0, 32, 32}},
          {"Sl9,PP3",         REGMEM_DESC_FLAGS_HEX, {0x1204,  0, 32, 32}},
          {"Sl10,PP1",        REGMEM_DESC_FLAGS_HEX, {0x1004,  0, 32, 32}},
          {"Sl13,PP2",        REGMEM_DESC_FLAGS_HEX, {0x1104,  0, 32, 32}},
          {"Sl14,PP4",        REGMEM_DESC_FLAGS_HEX, {0x1304,  0, 32, 32}},
          {"Sl15,PP6",        REGMEM_DESC_FLAGS_HEX, {0x1504,  0, 32, 32}},
          {"Sl16,PP8",        REGMEM_DESC_FLAGS_HEX, {0x1704,  0, 32, 32}},
          {"Sl17,PP10",       REGMEM_DESC_FLAGS_HEX, {0x1904,  0, 32, 32}},
          {"Sl18,PP12",       REGMEM_DESC_FLAGS_HEX, {0x1B04,  0, 32, 32}},
          {"Sl19,PP14",       REGMEM_DESC_FLAGS_HEX, {0x1D04,  0, 32, 32}},
          {"Sl20,PP16",       REGMEM_DESC_FLAGS_HEX, {0x1F04,  0, 32, 32}},
        {NULL, 0},

        {"SerdesCounters", 0},
          {"VXS_TRG_RX_CNT", 0},
            {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x1E20,  0, 32, 32}},
            {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x1C20,  0, 32, 32}},
            {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x1A20,  0, 32, 32}},
            {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x1820,  0, 32, 32}},
            {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x1620,  0, 32, 32}},
            {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x1420,  0, 32, 32}},
            {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x1220,  0, 32, 32}},
            {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x1020,  0, 32, 32}},
            {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x1120,  0, 32, 32}},
            {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x1320,  0, 32, 32}},
            {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x1520,  0, 32, 32}},
            {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x1720,  0, 32, 32}},
            {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x1920,  0, 32, 32}},
            {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x1B20,  0, 32, 32}},
            {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x1D20,  0, 32, 32}},
            {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x1F20,  0, 32, 32}},
          {NULL, 0},
          {"VXS_EVT_RX_CNT", 0},
            {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x1E24,  0, 32, 32}},
            {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x1C24,  0, 32, 32}},
            {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x1A24,  0, 32, 32}},
            {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x1824,  0, 32, 32}},
            {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x1624,  0, 32, 32}},
            {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x1424,  0, 32, 32}},
            {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x1224,  0, 32, 32}},
            {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x1024,  0, 32, 32}},
            {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x1124,  0, 32, 32}},
            {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x1324,  0, 32, 32}},
            {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x1524,  0, 32, 32}},
            {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x1724,  0, 32, 32}},
            {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x1924,  0, 32, 32}},
            {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x1B24,  0, 32, 32}},
            {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x1D24,  0, 32, 32}},
            {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x1F24,  0, 32, 32}},
          {NULL, 0},
          {"VXS_STR_RX_CNT", 0},
            {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x1E28,  0, 32, 32}},
            {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x1C28,  0, 32, 32}},
            {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x1A28,  0, 32, 32}},
            {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x1828,  0, 32, 32}},
            {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x1628,  0, 32, 32}},
            {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x1428,  0, 32, 32}},
            {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x1228,  0, 32, 32}},
            {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x1028,  0, 32, 32}},
            {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x1128,  0, 32, 32}},
            {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x1328,  0, 32, 32}},
            {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x1528,  0, 32, 32}},
            {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x1728,  0, 32, 32}},
            {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x1928,  0, 32, 32}},
            {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x1B28,  0, 32, 32}},
            {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x1D28,  0, 32, 32}},
            {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x1F28,  0, 32, 32}},
          {NULL, 0},
          {"VXS_UNK_RX_CNT", 0},
            {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x1E2C,  0, 32, 32}},
            {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x1C2C,  0, 32, 32}},
            {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x1A2C,  0, 32, 32}},
            {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x182C,  0, 32, 32}},
            {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x162C,  0, 32, 32}},
            {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x142C,  0, 32, 32}},
            {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x122C,  0, 32, 32}},
            {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x102C,  0, 32, 32}},
            {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x112C,  0, 32, 32}},
            {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x132C,  0, 32, 32}},
            {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x152C,  0, 32, 32}},
            {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x172C,  0, 32, 32}},
            {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x192C,  0, 32, 32}},
            {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x1B2C,  0, 32, 32}},
            {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x1D2C,  0, 32, 32}},
            {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x1F2C,  0, 32, 32}},
          {NULL, 0},
          {"VXS_IDL_RX_CNT", 0},
            {"Sl3,PP15",        REGMEM_DESC_FLAGS_UINT, {0x1E30,  0, 32, 32}},
            {"Sl4,PP13",        REGMEM_DESC_FLAGS_UINT, {0x1C30,  0, 32, 32}},
            {"Sl5,PP11",        REGMEM_DESC_FLAGS_UINT, {0x1A30,  0, 32, 32}},
            {"Sl6,PP9",         REGMEM_DESC_FLAGS_UINT, {0x1830,  0, 32, 32}},
            {"Sl7,PP7",         REGMEM_DESC_FLAGS_UINT, {0x1630,  0, 32, 32}},
            {"Sl8,PP5",         REGMEM_DESC_FLAGS_UINT, {0x1430,  0, 32, 32}},
            {"Sl9,PP3",         REGMEM_DESC_FLAGS_UINT, {0x1230,  0, 32, 32}},
            {"Sl10,PP1",        REGMEM_DESC_FLAGS_UINT, {0x1030,  0, 32, 32}},
            {"Sl13,PP2",        REGMEM_DESC_FLAGS_UINT, {0x1130,  0, 32, 32}},
            {"Sl14,PP4",        REGMEM_DESC_FLAGS_UINT, {0x1330,  0, 32, 32}},
            {"Sl15,PP6",        REGMEM_DESC_FLAGS_UINT, {0x1530,  0, 32, 32}},
            {"Sl16,PP8",        REGMEM_DESC_FLAGS_UINT, {0x1730,  0, 32, 32}},
            {"Sl17,PP10",       REGMEM_DESC_FLAGS_UINT, {0x1930,  0, 32, 32}},
            {"Sl18,PP12",       REGMEM_DESC_FLAGS_UINT, {0x1B30,  0, 32, 32}},
            {"Sl19,PP14",       REGMEM_DESC_FLAGS_UINT, {0x1D30,  0, 32, 32}},
            {"Sl20,PP16",       REGMEM_DESC_FLAGS_UINT, {0x1F30,  0, 32, 32}},
          {NULL, 0},
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
          {"Fiber0",          REGMEM_DESC_FLAGS_UINT, {0x0300, 16,  1, 32}},        
          {"Fiber1",          REGMEM_DESC_FLAGS_UINT, {0x0300, 17,  1, 32}},        
          {"Fiber2",          REGMEM_DESC_FLAGS_UINT, {0x0300, 18,  1, 32}},     
          {"Fiber3",          REGMEM_DESC_FLAGS_UINT, {0x0300, 19,  1, 32}},
          {"DataRdy",         REGMEM_DESC_FLAGS_HEX,  {0x0304,  0, 20, 32}},
          {"Latency",         REGMEM_DESC_FLAGS_UINT, {0x0304, 23,  9, 32}},
        {NULL, 0},
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

      {"Cosmic", 0},
        {"HIT_DT",              REGMEM_DESC_FLAGS_UINT, {0xB400, 0, 3, 32}},
        {"SMO_DT",              REGMEM_DESC_FLAGS_UINT, {0xB400, 4, 3, 32}},
        {"NSMO_THRESHOLD",      REGMEM_DESC_FLAGS_UINT, {0xB400, 8, 2, 32}},
        {"MLTP_THRESHOLD_1",    REGMEM_DESC_FLAGS_UINT, {0xB400,12, 4, 32}},
        {"MLTP_THRESHOLD_2",    REGMEM_DESC_FLAGS_UINT, {0xB400,16, 4, 32}},
        {"MLTP_THRESHOLD_3",    REGMEM_DESC_FLAGS_UINT, {0xB400,20, 4, 32}},
      {NULL, 0},

      {"TriggerBits", 0},
        {"Latency",             REGMEM_DESC_FLAGS_UINT,   {0x5000, 0,11,32}},
        {"Width",               REGMEM_DESC_FLAGS_UINT,   {0x5004, 0, 8,32}},
        {"Prescalers", 0},
          {"TrgBit0",           REGMEM_DESC_FLAGS_UINT,   {0x5010, 0,16,32}},
          {"TrgBit1",           REGMEM_DESC_FLAGS_UINT,   {0x5014, 0,16,32}},
          {"TrgBit2",           REGMEM_DESC_FLAGS_UINT,   {0x5018, 0,16,32}},
          {"TrgBit3",           REGMEM_DESC_FLAGS_UINT,   {0x501C, 0,16,32}},
          {"TrgBit4",           REGMEM_DESC_FLAGS_UINT,   {0x5020, 0,16,32}},
          {"TrgBit5",           REGMEM_DESC_FLAGS_UINT,   {0x5024, 0,16,32}},
          {"TrgBit6",           REGMEM_DESC_FLAGS_UINT,   {0x5028, 0,16,32}},
          {"TrgBit7",           REGMEM_DESC_FLAGS_UINT,   {0x502C, 0,16,32}},
          {"TrgBit8",           REGMEM_DESC_FLAGS_UINT,   {0x5030, 0,16,32}},
          {"TrgBit9",           REGMEM_DESC_FLAGS_UINT,   {0x5034, 0,16,32}},
          {"TrgBit10",          REGMEM_DESC_FLAGS_UINT,   {0x5038, 0,16,32}},
          {"TrgBit11",          REGMEM_DESC_FLAGS_UINT,   {0x503C, 0,16,32}},
          {"TrgBit12",          REGMEM_DESC_FLAGS_UINT,   {0x5040, 0,16,32}},
          {"TrgBit13",          REGMEM_DESC_FLAGS_UINT,   {0x5044, 0,16,32}},
          {"TrgBit14",          REGMEM_DESC_FLAGS_UINT,   {0x5048, 0,16,32}},
          {"TrgBit15",          REGMEM_DESC_FLAGS_UINT,   {0x504C, 0,16,32}},
          {"TrgBit16",          REGMEM_DESC_FLAGS_UINT,   {0x5050, 0,16,32}},
          {"TrgBit17",          REGMEM_DESC_FLAGS_UINT,   {0x5054, 0,16,32}},
          {"TrgBit18",          REGMEM_DESC_FLAGS_UINT,   {0x5058, 0,16,32}},
          {"TrgBit19",          REGMEM_DESC_FLAGS_UINT,   {0x505C, 0,16,32}},
          {"TrgBit20",          REGMEM_DESC_FLAGS_UINT,   {0x5060, 0,16,32}},
          {"TrgBit21",          REGMEM_DESC_FLAGS_UINT,   {0x5064, 0,16,32}},
          {"TrgBit22",          REGMEM_DESC_FLAGS_UINT,   {0x5068, 0,16,32}},
          {"TrgBit23",          REGMEM_DESC_FLAGS_UINT,   {0x506C, 0,16,32}},
          {"TrgBit24",          REGMEM_DESC_FLAGS_UINT,   {0x5070, 0,16,32}},
          {"TrgBit25",          REGMEM_DESC_FLAGS_UINT,   {0x5074, 0,16,32}},
          {"TrgBit26",          REGMEM_DESC_FLAGS_UINT,   {0x5078, 0,16,32}},
          {"TrgBit27",          REGMEM_DESC_FLAGS_UINT,   {0x507C, 0,16,32}},
          {"TrgBit28",          REGMEM_DESC_FLAGS_UINT,   {0x5080, 0,16,32}},
          {"TrgBit29",          REGMEM_DESC_FLAGS_UINT,   {0x5084, 0,16,32}},
          {"TrgBit30",          REGMEM_DESC_FLAGS_UINT,   {0x5088, 0,16,32}},
          {"TrgBit31",          REGMEM_DESC_FLAGS_UINT,   {0x508C, 0,16,32}},
        {NULL, 0},
      {NULL, 0},
    };

    pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
  }

  const char *GetModuleName() { return "VTP_SBSECAL"; }
  const char *GetModuleFullName() { return "VXS Trigger Processor-SBSECAL"; }
  const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
  TString     strSlotIdentifier;
  TGTab       *pTabs;
};

#endif
