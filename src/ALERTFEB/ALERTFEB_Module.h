#ifndef ALERTFEB_Module_H
#define ALERTFEB_Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_TDC.h"

class ALERTFEB_Module : public ModuleFrame
{
public:
  ALERTFEB_Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
		tFrame = pTabs->AddTab("TDC");		tFrame->AddFrame(new ALERTFEB_TDC(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
  
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
/*
      {"MAROC", 0},
        {"Serial", 0},
          {"ResetN",        REGMEM_DESC_FLAGS_UINT,   {0x0100, 0, 1, 32}},
          {"Start",       REGMEM_DESC_FLAGS_UINT,   {0x0100, 1, 1, 32}},
          {"Busy",          REGMEM_DESC_FLAGS_UINT,   {0x0104, 0, 1, 32}},
        {NULL, 0},
        {"Global", 0},
          {"cmd_fsu",       REGMEM_DESC_FLAGS_UINT,   {0x0110, 0, 1, 32}},
          {"cmd_ss",        REGMEM_DESC_FLAGS_UINT,   {0x0110, 1, 1, 32}},
          {"cmd_fsb",       REGMEM_DESC_FLAGS_UINT,   {0x0110, 2, 1, 32}},
          {"swb_buf_250f",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 3, 1, 32}},
          {"swb_buf_500f",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 4, 1, 32}},
          {"swb_buf_1p",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 5, 1, 32}},
          {"swb_buf_2p",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 6, 1, 32}},
          {"ON/OFF_ss",     REGMEM_DESC_FLAGS_UINT,   {0x0110, 7, 1, 32}},
          {"sw_ss_300f",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 8, 1, 32}},
          {"sw_ss_600f",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 9, 1, 32}},
          {"sw_ss_1200f",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 10, 1, 32}},
          {"EN_ADC",        REGMEM_DESC_FLAGS_UINT,   {0x0110, 11, 1, 32}},
          {"H1H2_choice",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 12, 1, 32}},
          {"sw_fsu_20f",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 13, 1, 32}},
          {"sw_fsu_40f",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 14, 1, 32}},
          {"sw_fsu_25k",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 15, 1, 32}},
          {"sw_fsu_50k",      REGMEM_DESC_FLAGS_UINT,   {0x0110, 16, 1, 32}},
          {"sw_fsu_100k",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 17, 1, 32}},
          {"sw_fsb1_50k",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 18, 1, 32}},
          {"sw_fsb1_100k",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 19, 1, 32}},
          {"sw_fsb1_100f",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 20, 1, 32}},
          {"sw_fsb1_50f",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 21, 1, 32}},
          {"cmd_fsb_fsu",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 22, 1, 32}},
          {"valid_dc_fs",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 23, 1, 32}},
          {"sw_fsb2_50k",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 24, 1, 32}},
          {"sw_fsb2_100k",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 25, 1, 32}},
          {"sw_fsb2_100f",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 26, 1, 32}},
          {"sw_fsb2_50f",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 27, 1, 32}},
          {"valid_dc_fsb2",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 28, 1, 32}},
          {"ENb_tristate",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 29, 1, 32}},
          {"polar_discri",    REGMEM_DESC_FLAGS_UINT,   {0x0110, 30, 1, 32}},
          {"inv_discriADC",   REGMEM_DESC_FLAGS_UINT,   {0x0110, 31, 1, 32}},
          {"d1_d2",       REGMEM_DESC_FLAGS_UINT,   {0x0114, 0, 1, 32}},
          {"cmd_CK_mux",      REGMEM_DESC_FLAGS_UINT,   {0x0114, 1, 1, 32}},
        {NULL, 0},
      {NULL, 0},
*/
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
