#ifndef VTP_SBSECAL_FIBERSCOPE_H
#define VTP_SBSECAL_FIBERSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_SBSECAL_FiberScope : public TGCompositeFrame
{
public:
  VTP_SBSECAL_FiberScope(const TGWindow *p, ModuleFrame *pModule, int ifiber) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr + ifiber*0x0100;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    
    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x1044+offset, 0, 0x1040+offset, 0, 0x1070+offset,5);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("RX_TDATA_H",   4*32+8, TRACE_MODE_DIGITAL,  32,  32,    0x104C+offset, 0,   0x1060+offset,  0);
    pScope->AddTrace("RX_TDATA_L",   4*32+8, TRACE_MODE_DIGITAL,  32,   0,    0x1048+offset, 0,   0x105C+offset,  0);
    pScope->AddTrace("RX_TKEEP",     4* 8+8, TRACE_MODE_DIGITAL,   8, 138,    0x1058+offset, 8,   0x106C+offset,  8);
    pScope->AddTrace("RX_TVALID",        16, TRACE_MODE_DIGITAL,   1, 144,    0x1058+offset,16,   0x106C+offset, 16);
    pScope->AddTrace("RX_TLAST",         16, TRACE_MODE_DIGITAL,   1, 145,    0x1058+offset,17,   0x106C+offset, 17);
    pScope->AddTrace("RX_DATA_H",    4*32+8, TRACE_MODE_DIGITAL,  32,  96,    0x1054+offset, 0,   0x1068+offset,  0);
    pScope->AddTrace("RX_TATA_L",    4*32+8, TRACE_MODE_DIGITAL,  32,  64,    0x1050+offset, 0,   0x1064+offset,  0);
    pScope->AddTrace("RX_IS_K",      4* 8+8, TRACE_MODE_DIGITAL,   8, 128,    0x1058+offset, 0,   0x106C+offset,  0);
    pScope->AddTrace("CHANNEL_UP",       16, TRACE_MODE_DIGITAL,   1, 146,    0x1058+offset,18,   0x106C+offset, 18);
  }
};

#endif
