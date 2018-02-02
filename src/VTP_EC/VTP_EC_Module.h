#ifndef VTP_Module_H
#define VTP_Module_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "VTP_EC_TrgHist.h"

class VTP_EC_Module	: public ModuleFrame
{
public:
	VTP_EC_Module(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr) : ModuleFrame(p, pClient, baseAddr)
	{
		SetupRegisters();

		TGCompositeFrame *tFrame;
		AddFrame(pTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Config");		tFrame->AddFrame(pSSPConfig = new SSP_Config(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pTabs->AddTab("Histograms");	tFrame->AddFrame(pSSPHistograms = new SSP_Histograms(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		tFrame = pTabs->AddTab("ECInner");		tFrame->AddFrame(new VTP_EC_TrgHist(tFrame, this, 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    tFrame = pTabs->AddTab("ECOuter");    tFrame->AddFrame(new VTP_EC_TrgHist(tFrame, this, 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));


		strSlotIdentifier.Form("SWA");
	}

	void SetupRegisters()
	{
		static RegMemDesc regs[] = {
			{"ECInnerTrig", 0},
				{"Hit_dt",				REGMEM_DESC_FLAGS_UINT, {0x14100, 16,  4, 32}},
				{"Hit_emin",			REGMEM_DESC_FLAGS_UINT, {0x14100,  0, 13, 32}},
				{"Dalitz_min",		REGMEM_DESC_FLAGS_UINT, {0x14104,  0, 10, 32}},
        {"Dalitz_max",    REGMEM_DESC_FLAGS_UINT, {0x14104, 16, 10, 32}},
      {NULL, 0},
      {"ECOuterTrig", 0},
        {"Hit_dt",        REGMEM_DESC_FLAGS_UINT, {0x14200, 16,  4, 32}},
        {"Hit_emin",      REGMEM_DESC_FLAGS_UINT, {0x14200,  0, 13, 32}},
        {"Dalitz_min",    REGMEM_DESC_FLAGS_UINT, {0x14204,  0, 10, 32}},
        {"Dalitz_max",    REGMEM_DESC_FLAGS_UINT, {0x14204, 16, 10, 32}},
      {NULL, 0},
      {"FadcSum", 0},
        {"SumEn0",        REGMEM_DESC_FLAGS_HEX,  {0x14300,  0, 32, 32}},
        {"SumEn1",        REGMEM_DESC_FLAGS_HEX,  {0x14304,  0, 32, 32}},
        {"SumEn2",        REGMEM_DESC_FLAGS_HEX,  {0x14308,  0, 32, 32}},
        {"SumEn3",        REGMEM_DESC_FLAGS_HEX,  {0x1430C,  0, 32, 32}},
        {"SumEn4",        REGMEM_DESC_FLAGS_HEX,  {0x14310,  0, 32, 32}},
        {"SumEn5",        REGMEM_DESC_FLAGS_HEX,  {0x14314,  0, 32, 32}},
        {"SumEn6",        REGMEM_DESC_FLAGS_HEX,  {0x14318,  0, 32, 32}},
        {"SumEn7",        REGMEM_DESC_FLAGS_HEX,  {0x1431C,  0, 32, 32}},
			{NULL, 0},
      {"FadcDecoder", 0},
        {"PP15Latency",   REGMEM_DESC_FLAGS_UINT, {0x10358,  0, 12, 32}},
        {"PP13Latency",   REGMEM_DESC_FLAGS_UINT, {0x10350,  0, 12, 32}},
        {"PP11Latency",   REGMEM_DESC_FLAGS_UINT, {0x10348,  0, 12, 32}},
        {"PP9Latency",    REGMEM_DESC_FLAGS_UINT, {0x10340,  0, 12, 32}},
        {"PP7Latency",    REGMEM_DESC_FLAGS_UINT, {0x10338,  0, 12, 32}},
        {"PP5Latency",    REGMEM_DESC_FLAGS_UINT, {0x10330,  0, 12, 32}},
        {"PP3Latency",    REGMEM_DESC_FLAGS_UINT, {0x10328,  0, 12, 32}},
        {"PP1Latency",    REGMEM_DESC_FLAGS_UINT, {0x10320,  0, 12, 32}},
        {"PP2Latency",    REGMEM_DESC_FLAGS_UINT, {0x10324,  0, 12, 32}},
        {"PP4Latency",    REGMEM_DESC_FLAGS_UINT, {0x1032C,  0, 12, 32}},
        {"PP6Latency",    REGMEM_DESC_FLAGS_UINT, {0x10334,  0, 12, 32}},
        {"PP8Latency",    REGMEM_DESC_FLAGS_UINT, {0x1033C,  0, 12, 32}},
        {"PP10Latency",   REGMEM_DESC_FLAGS_UINT, {0x10344,  0, 12, 32}},
        {"PP12Latency",   REGMEM_DESC_FLAGS_UINT, {0x1034C,  0, 12, 32}},
        {"PP14Latency",   REGMEM_DESC_FLAGS_UINT, {0x10354,  0, 12, 32}},
        {"PP16Latency",   REGMEM_DESC_FLAGS_UINT, {0x1035C,  0, 12, 32}},
        {"PP15En",        REGMEM_DESC_FLAGS_UINT, {0x10300, 14,  1, 32}},
        {"PP13En",        REGMEM_DESC_FLAGS_UINT, {0x10300, 12,  1, 32}},
        {"PP11En",        REGMEM_DESC_FLAGS_UINT, {0x10300, 10,  1, 32}},
        {"PP9En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  8,  1, 32}},
        {"PP7En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  6,  1, 32}},
        {"PP5En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  4,  1, 32}},
        {"PP3En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  2,  1, 32}},
        {"PP1En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  0,  1, 32}},
        {"PP2En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  1,  1, 32}},
        {"PP4En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  3,  1, 32}},
        {"PP6En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  5,  1, 32}},
        {"PP8En",         REGMEM_DESC_FLAGS_UINT, {0x10300,  7,  1, 32}},
        {"PP10En",        REGMEM_DESC_FLAGS_UINT, {0x10300,  9,  1, 32}},
        {"PP12En",        REGMEM_DESC_FLAGS_UINT, {0x10300, 11,  1, 32}},
        {"PP14En",        REGMEM_DESC_FLAGS_UINT, {0x10300, 13,  1, 32}},
        {"PP16En",        REGMEM_DESC_FLAGS_UINT, {0x10300, 15,  1, 32}},        
      {NULL, 0}
		};

		pRegEditor->AddSet(regs, sizeof(regs)/sizeof(regs[0]));
	}

	const char *GetModuleName() { return "VTP"; }
	const char *GetModuleFullName() { return "VXS Trigger Processor"; }
	const char *GetSlotIdentifier() { return strSlotIdentifier.Data(); }

private:
	TString			strSlotIdentifier;
	TGTab				*pTabs;
};

#endif
