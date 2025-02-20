#ifndef V1495LAD_SCOPE_H
#define V1495LAD_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class V1495LAD_Scope : public TGCompositeFrame
{
public:
  V1495LAD_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x1104+offset, 0, 0x1100+offset, 0, 0x1130+offset,4);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("DSC_A_15_0",         4*16+8, TRACE_MODE_DIGITAL, 16,  0,     0x1110+offset, 0,   0x1120+offset, 0);
    pScope->AddTrace("DSC_A_31_16",        4*16+8, TRACE_MODE_DIGITAL, 16, 16,     0x1110+offset,16,   0x1120+offset,16);
    pScope->AddTrace("DSC_B_15_0",         4*16+8, TRACE_MODE_DIGITAL, 16, 32,     0x1114+offset, 0,   0x1124+offset, 0);
    pScope->AddTrace("DSC_B_31_16",        4*16+8, TRACE_MODE_DIGITAL, 16, 48,     0x1114+offset,16,   0x1124+offset,16);
    pScope->AddTrace("DSC_D_15_0",         4*16+8, TRACE_MODE_DIGITAL, 16, 64,     0x1118+offset, 0,   0x1128+offset, 0);
    pScope->AddTrace("DSC_D_31_16",        4*16+8, TRACE_MODE_DIGITAL, 16, 80,     0x1118+offset,16,   0x1128+offset,16);
    pScope->AddTrace("DSC_E_15_0",         4*16+8, TRACE_MODE_DIGITAL, 16, 96,     0x111C+offset, 0,   0x112C+offset, 0);
    pScope->AddTrace("COIN_SUM",              128, TRACE_MODE_ANALOG,   6,112,     0x111C+offset,16,   0x112C+offset,16);
    pScope->AddTrace("TS1",                    27, TRACE_MODE_DIGITAL,  1,118,     0x111C+offset,22,   0x112C+offset,22);
    pScope->AddTrace("TS2",                    27, TRACE_MODE_DIGITAL,  1,119,     0x111C+offset,23,   0x112C+offset,23);
    pScope->AddTrace("TS3",                    27, TRACE_MODE_DIGITAL,  1,120,     0x111C+offset,24,   0x112C+offset,24);
    pScope->AddTrace("TS4",                    27, TRACE_MODE_DIGITAL,  1,121,     0x111C+offset,25,   0x112C+offset,25);
    pScope->AddTrace("TS5",                    27, TRACE_MODE_DIGITAL,  1,122,     0x111C+offset,26,   0x112C+offset,26);
    pScope->AddTrace("TS6",                    27, TRACE_MODE_DIGITAL,  1,123,     0x111C+offset,27,   0x112C+offset,27);
  }
};

#endif
