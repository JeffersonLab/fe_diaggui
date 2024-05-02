#ifndef ALERTFEB_Module_H
#define ALERTFEB_Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_TDC.h"
#include "ALERTFEB_EB.h"
#include "ALERTFEB_EB_QCAL.h"
#include "ALERTFEB_Scalers.h"
#include "ALERTFEB_Cfg.h"

class ALERTFEB_Module : public ModuleFrame
{
public:
  ALERTFEB_Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("Scalers");		tFrame->AddFrame(new ALERTFEB_SCALERS(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("TDC");		    tFrame->AddFrame(new ALERTFEB_TDC    (tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("EB");		      tFrame->AddFrame(new ALERTFEB_EB     (tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("EB_QCAL");		tFrame->AddFrame(new ALERTFEB_EB_QCAL(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("Config");     tFrame->AddFrame(new ALERTFEB_Cfg    (tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
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
      {"ClkRst", 0},
        {"SoftReset",       REGMEM_DESC_FLAGS_UINT,   {0x0000, 0, 1, 32}},
        {"ClkSel",          REGMEM_DESC_FLAGS_UINT,   {0x0000, 1, 1, 32}},
        {"Rst",             REGMEM_DESC_FLAGS_UINT,   {0x0000, 2, 1, 32}},
        {"BoardID",         REGMEM_DESC_FLAGS_HEX,    {0x0010, 0,32, 32}},
        {"VersionMaj",          REGMEM_DESC_FLAGS_UINT,   {0x0018,16,16,32}},
        {"VersionMin",          REGMEM_DESC_FLAGS_UINT,   {0x0018, 0,16,32}},
        {"CompileInfo", 0},
          {"Day",               REGMEM_DESC_FLAGS_UINT,   {0x001C,27, 5,32}},
          {"Month",             REGMEM_DESC_FLAGS_STRING, {0x001C,23, 4,32}, MONTH_MAP},
          {"Year",              REGMEM_DESC_FLAGS_STRING, {0x001C,17, 6,32}, YEAR_MAP},
          {"Hour",              REGMEM_DESC_FLAGS_UINT,   {0x001C,12, 5,32}},
          {"Min",               REGMEM_DESC_FLAGS_UINT,   {0x001C, 6, 6,32}},
          {"Sec",               REGMEM_DESC_FLAGS_UINT,   {0x001C, 0, 6,32}},
        {NULL, 0},
      {NULL, 0},
      {"Sd", 0},
        {"Mux", 0},
          {"Trig",          REGMEM_DESC_FLAGS_UINT,   {0x0100, 0, 4, 32}},
          {"Sync",          REGMEM_DESC_FLAGS_UINT,   {0x0104, 0, 4, 32}},
          {"Busy",          REGMEM_DESC_FLAGS_UINT,   {0x0108, 0, 4, 32}},
          {"LED_G",         REGMEM_DESC_FLAGS_UINT,   {0x010C, 0, 4, 32}},
          {"LED_Y",         REGMEM_DESC_FLAGS_UINT,   {0x0110, 0, 4, 32}},
        {NULL, 0},
        {"Pulser", 0},
          {"Period",        REGMEM_DESC_FLAGS_UINT,   {0x0180, 0,32, 32}},
          {"LowCycles",     REGMEM_DESC_FLAGS_UINT,   {0x0184, 0,32, 32}},
          {"NCycles",       REGMEM_DESC_FLAGS_UINT,   {0x0188, 0,32, 32}},
          {"Start",         REGMEM_DESC_FLAGS_UINT,   {0x018C, 0, 1, 32}},
          {"Status",        REGMEM_DESC_FLAGS_UINT,   {0x0190, 0, 1, 32}},
        {NULL, 0},
        {"Scalers", 0},
          {"Latch",         REGMEM_DESC_FLAGS_UINT,   {0x01A0, 0, 1, 32}},
          {"Sysclk",        REGMEM_DESC_FLAGS_UINT,   {0x01A4, 0,32, 32}},
          {"Gclk",          REGMEM_DESC_FLAGS_UINT,   {0x01A8, 0,32, 32}},
          {"Sync",          REGMEM_DESC_FLAGS_UINT,   {0x01AC, 0,32, 32}},
          {"Trig",          REGMEM_DESC_FLAGS_UINT,   {0x01B0, 0,32, 32}},
          {"Busy",          REGMEM_DESC_FLAGS_UINT,   {0x01B4, 0,32, 32}},
          {"Nor32_Charge0", REGMEM_DESC_FLAGS_UINT,   {0x01B8, 0,32, 32}},
          {"Nor32_Charge1", REGMEM_DESC_FLAGS_UINT,   {0x01BC, 0,32, 32}},
          {"Nor32_Time0",   REGMEM_DESC_FLAGS_UINT,   {0x01C0, 0,32, 32}},
          {"Nor32_Time1",   REGMEM_DESC_FLAGS_UINT,   {0x01C4, 0,32, 32}},
        {NULL, 0},
      {NULL, 0},
      {"Eb", 0},
        {"Blocksize",       REGMEM_DESC_FLAGS_UINT,   {0x0200, 0, 8, 32}},
        {"TrigFifoBusyThr", REGMEM_DESC_FLAGS_UINT,   {0x0204, 0, 8, 32}},
        {"Lookback",        REGMEM_DESC_FLAGS_UINT,   {0x0208, 0,16, 32}},
        {"WindowWidth",     REGMEM_DESC_FLAGS_UINT,   {0x020C, 0,16, 32}},
      {NULL, 0},
      {"Tdc", 0},
        {"Ctrl",            REGMEM_DESC_FLAGS_HEX,    {0x1000, 0, 3, 32}},
        {"NumEntriesMin",   REGMEM_DESC_FLAGS_UINT,   {0x1004, 0,25, 32}},
        {"TdcEnable0",      REGMEM_DESC_FLAGS_HEX,    {0x1008, 0,32, 32}},
        {"TdcEnable1",      REGMEM_DESC_FLAGS_HEX,    {0x100C, 0,16, 32}},
        {"CalEnable",       REGMEM_DESC_FLAGS_HEX,    {0x1010, 0, 4, 32}},
        {"CalCtrl",         REGMEM_DESC_FLAGS_HEX,    {0x1014, 0,16, 32}},
        {"CalStatus",       REGMEM_DESC_FLAGS_HEX,    {0x1018, 0,16, 32}},
      {NULL, 0},
      {"PetirocCfg", 0},
        {"Ctrl", 0},
          {"PWR_ON_D",      REGMEM_DESC_FLAGS_UINT,   {0x0500, 4, 1, 32}},
          {"PWR_ON_A",      REGMEM_DESC_FLAGS_UINT,   {0x0500, 5, 1, 32}},
          {"PWR_ON_DAC",    REGMEM_DESC_FLAGS_UINT,   {0x0500, 6, 1, 32}},
          {"PWR_ON_ADC",    REGMEM_DESC_FLAGS_UINT,   {0x0500, 7, 1, 32}},
          {"CLK_DISABLE",   REGMEM_DESC_FLAGS_UINT,   {0x0500, 8, 1, 32}},
          {"GAIN_SEL",      REGMEM_DESC_FLAGS_UINT,   {0x0500, 9, 1, 32}},
        {NULL, 0},
      {NULL, 0},
      {"Pulser", 0},
        {"DAC", 0},
          {"ChMask",        REGMEM_DESC_FLAGS_HEX,    {0x0800, 0, 4, 32}},
          {"Enable",        REGMEM_DESC_FLAGS_HEX,    {0x0800, 4, 1, 32}},
          {"LDAC",          REGMEM_DESC_FLAGS_HEX,    {0x0800, 5, 1, 32}},
          {"RstSel",        REGMEM_DESC_FLAGS_HEX,    {0x0800, 6, 1, 32}},
          {"Sync",          REGMEM_DESC_FLAGS_HEX,    {0x0800, 7, 1, 32}},
          {"SDA",           REGMEM_DESC_FLAGS_HEX,    {0x0800, 8, 1, 32}},
          {"SCK",           REGMEM_DESC_FLAGS_HEX,    {0x0800, 9, 1, 32}},
          {"RST",           REGMEM_DESC_FLAGS_HEX,    {0x0800,10, 1, 32}},
        {NULL, 0},
        {"Pulser", 0},
          {"Period",        REGMEM_DESC_FLAGS_UINT,   {0x0880, 0,32, 32}},
          {"LowCycles",     REGMEM_DESC_FLAGS_UINT,   {0x0884, 0,32, 32}},
          {"NCycles",       REGMEM_DESC_FLAGS_UINT,   {0x0888, 0,32, 32}},
          {"Start",         REGMEM_DESC_FLAGS_UINT,   {0x088C, 0, 1, 32}},
          {"Status",        REGMEM_DESC_FLAGS_UINT,   {0x0890, 0, 1, 32}},
          {"Delay",         REGMEM_DESC_FLAGS_UINT,   {0x0894, 0, 8, 32}},
        {NULL, 0},
        {"CalPolarity",   REGMEM_DESC_FLAGS_HEX,    {0x0800,11, 1, 32}},
      {NULL, 0},
    };

    pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
  }

  const char *GetModuleName() { return "ALERTFEB"; }
  const char *GetModuleFullName() { return "ALERTFEB-PETIROC"; }
  const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
  TString     strSlotIdentifier;
  TGTab       *pTabs;
};

#endif
