#ifndef ALERTFEB_Module_H
#define ALERTFEB_Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_TDC.h"
#include "ALERTFEB_EB.h"

class ALERTFEB_Module : public ModuleFrame
{
public:
  ALERTFEB_Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("TDC");		tFrame->AddFrame(new ALERTFEB_TDC(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("EB");		tFrame->AddFrame(new ALERTFEB_EB(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
  }

  void SetupRegisters()
  {
    static RegMemDesc regs[] = {
      {"ClkRst", 0},
        {"SoftReset",       REGMEM_DESC_FLAGS_UINT,   {0x0000, 0, 1, 32}},
        {"ClkSel",          REGMEM_DESC_FLAGS_UINT,   {0x0000, 1, 1, 32}},
        {"Rst",             REGMEM_DESC_FLAGS_UINT,   {0x0000, 2, 1, 32}},
        {"BoardID",         REGMEM_DESC_FLAGS_HEX,    {0x0010, 0,32, 32}},
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
        {"TrigFifoBusyThr", REGMEM_DESC_FLAGS_UINT,   {0x0204, 1, 8, 32}},
        {"Lookback",        REGMEM_DESC_FLAGS_UINT,   {0x0208, 2,16, 32}},
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
