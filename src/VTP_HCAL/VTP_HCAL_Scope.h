#ifndef VTP_HCAL_SCOPE_H
#define VTP_HCAL_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_HCAL_Scope : public TGCompositeFrame
{
public:
  VTP_HCAL_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x4834+offset, 0, 0x4830+offset, 0, 0x4848+offset,2);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("HCAL_ROW",         8+4*5, TRACE_MODE_DIGITAL,  5,   0,    0x4838+offset, 0,   0x4840+offset, 0);
    pScope->AddTrace("HCAL_COL",         8+4*4, TRACE_MODE_DIGITAL,  4,   5,    0x4838+offset, 5,   0x4840+offset, 5);
    pScope->AddTrace("HCAL_E",          8+4*16, TRACE_MODE_DIGITAL, 16,   9,    0x4838+offset, 9,   0x4840+offset, 9);
    pScope->AddTrace("HCAL_T",          8+4*11, TRACE_MODE_DIGITAL, 11,  25,    0x4838+offset,25,   0x4840+offset,25);
    pScope->AddTrace("HCAL_N",           8+4*4, TRACE_MODE_DIGITAL,  4,  36,    0x483C+offset, 4,   0x4844+offset, 4);
    pScope->AddTrace("HCAL_EN",             27, TRACE_MODE_DIGITAL,  1,  40,    0x483C+offset, 8,   0x4844+offset, 8);
  }
};

#endif
