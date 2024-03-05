#ifndef VTP_FADCCOIN_SCOPE_H
#define VTP_FADCCOIN_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_FADCCOIN_Scope : public TGCompositeFrame
{
public:
  VTP_FADCCOIN_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x9184+offset, 0, 0x9180+offset, 0, 0x91C0+offset,4);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("FADCSUM_GRP0",       128, TRACE_MODE_ANALOG,  29,   0,    0x9188+offset,29,   0x9188+offset, 0);
    pScope->AddTrace("FADCSUM_GRP1",       128, TRACE_MODE_ANALOG,  29,  29,    0x918C+offset,29,   0x918C+offset, 0);
    pScope->AddTrace("FADCSUM_GRP2",       128, TRACE_MODE_ANALOG,  29,  58,    0x9190+offset,29,   0x9190+offset, 0);
    pScope->AddTrace("Ready",               27, TRACE_MODE_DIGITAL,  1,  87,    0x91A0+offset, 0,   0x91B0+offset, 0);
    pScope->AddTrace("Trigbit0",            27, TRACE_MODE_DIGITAL,  1,  88,    0x91A0+offset, 1,   0x91B0+offset, 1);
  }
};

#endif
