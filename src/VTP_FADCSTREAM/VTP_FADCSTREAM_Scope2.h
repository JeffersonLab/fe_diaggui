#ifndef VTP_FADCSTREAM_SCOPE2_H
#define VTP_FADCSTREAM_SCOPE2_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_FADCSTREAM_Scope2 : public TGCompositeFrame
{
public:
  VTP_FADCSTREAM_Scope2(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x886C+offset, 0, 0x8868+offset, 0, 0x8878+offset,1);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("DDR3_RD_EN",             27, TRACE_MODE_DIGITAL,  1,   0,    0x8870+offset, 0,   0x8874+offset, 0);
    pScope->AddTrace("DDR3_RD_RDY",            27, TRACE_MODE_DIGITAL,  1,   1,    0x8870+offset, 1,   0x8874+offset, 1);
    pScope->AddTrace("DDR3_RD_DATA_RD",        27, TRACE_MODE_DIGITAL,  1,   2,    0x8870+offset, 2,   0x8874+offset, 2);
    pScope->AddTrace("DDR3_RD_DATA_EMPTY",     27, TRACE_MODE_DIGITAL,  1,   3,    0x8870+offset, 3,   0x8874+offset, 3);
    pScope->AddTrace("EB_DATA_VALID",          27, TRACE_MODE_DIGITAL,  4,   4,    0x8870+offset, 4,   0x8874+offset, 4);
    pScope->AddTrace("EB_DATA_WR",             27, TRACE_MODE_DIGITAL,  1,   8,    0x8870+offset, 8,   0x8874+offset, 8);
    pScope->AddTrace("EB_DATA_FULL",           27, TRACE_MODE_DIGITAL,  1,   9,    0x8870+offset, 9,   0x8874+offset, 9);
  }
};

#endif

