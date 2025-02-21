#ifndef V1495LADModule_H
#define V1495LADModule_H

#include "RootHeader.h"
#include "V1495LAD_Scope.h"
#include "ModuleFrame.h"

class V1495LADModule : public ModuleFrame
{
public:
  V1495LADModule(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
  {
    SetupRegisters();

    TGCompositeFrame *tFrame;
    AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));

    tFrame = pTabs->AddTab("Scope");      tFrame->AddFrame(new V1495LAD_Scope(tFrame, this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    strSlotIdentifier.Form("VME");
  }

  void SetupRegisters()
  {
    static RegMemDesc regs[] = {
      {"Info", 0},
        {"FirmwareType",        REGMEM_DESC_FLAGS_HEX,    {0x1000, 0,32,32}},
        {"VersionMaj",          REGMEM_DESC_FLAGS_UINT,   {0x1004,16,16,32}},
        {"VersionMin",          REGMEM_DESC_FLAGS_UINT,   {0x1004, 0,16,32}},
        {"BoardID",             REGMEM_DESC_FLAGS_HEX,    {0x1008, 0,32,32}},
        {"RrAddr0",             REGMEM_DESC_FLAGS_HEX,    {0x1140, 0, 9,32}},
        {"WrAddr0",             REGMEM_DESC_FLAGS_HEX,    {0x1140,16, 9,32}},
        {"RrAddr1",             REGMEM_DESC_FLAGS_HEX,    {0x1144, 0, 9,32}},
        {"WrAddr1",             REGMEM_DESC_FLAGS_HEX,    {0x1144,16, 9,32}},
        {"RrAddr2",             REGMEM_DESC_FLAGS_HEX,    {0x1148, 0, 9,32}},
        {"WrAddr2",             REGMEM_DESC_FLAGS_HEX,    {0x1148,16, 9,32}},
        {"RrAddr3",             REGMEM_DESC_FLAGS_HEX,    {0x114C, 0, 9,32}},
        {"WrAddr3",             REGMEM_DESC_FLAGS_HEX,    {0x114C,16, 9,32}},
      {NULL, 0},

      {"TriggerBits", 0},
        {"TS1-Mult",            REGMEM_DESC_FLAGS_UINT,   {0x1010, 0, 6,32}},
        {"TS2-Mult",            REGMEM_DESC_FLAGS_UINT,   {0x1014, 0, 6,32}},
        {"TS3-Mult",            REGMEM_DESC_FLAGS_UINT,   {0x1018, 0, 6,32}},
        {"TS4-Mult",            REGMEM_DESC_FLAGS_UINT,   {0x101C, 0, 6,32}},
        {"TS5-Mult",            REGMEM_DESC_FLAGS_UINT,   {0x1020, 0, 6,32}},
        {"TS6-Mult",            REGMEM_DESC_FLAGS_UINT,   {0x1024, 0, 6,32}},
      {NULL, 0},
      
      {"TriggerCfg", 0},
        {"DisableMask0",        REGMEM_DESC_FLAGS_HEX,    {0x1050, 0,16, 32}},
        {"DisableMask1",        REGMEM_DESC_FLAGS_HEX,    {0x1054, 0,16, 32}},
        {"DisableMask2",        REGMEM_DESC_FLAGS_HEX,    {0x1058, 0,16, 32}},
        {"DisableMask3",        REGMEM_DESC_FLAGS_HEX,    {0x105C, 0,16, 32}},
        {"DisableMask4",        REGMEM_DESC_FLAGS_HEX,    {0x1060, 0,16, 32}},
        {"DisableMask5",        REGMEM_DESC_FLAGS_HEX,    {0x1064, 0,16, 32}},
        {"DisableMask6",        REGMEM_DESC_FLAGS_HEX,    {0x1068, 0,16, 32}},
      {NULL, 0},
    };

    pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
  }

  const char *GetModuleName() { return "V1495LAD"; }
  const char *GetModuleFullName() { return "V1495 LAD Multiplicity Trigger"; }
  const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
  TString     strSlotIdentifier;
  TGTab       *pTabs;
};

#endif
