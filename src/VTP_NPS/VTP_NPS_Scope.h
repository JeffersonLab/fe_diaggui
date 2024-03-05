#ifndef VTP_NPS_SCOPE_H
#define VTP_NPS_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_NPS_Scope : public TGCompositeFrame
{
public:
  VTP_NPS_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x0314+offset, 0, 0x0310+offset, 0, 0x0320+offset,11);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("HIT_VALID",          27, TRACE_MODE_DIGITAL,   1, 320,    0x0378+offset, 0,   0x03A8+offset, 0);

    pScope->AddTrace("VXS_DATA0",      4*16+8, TRACE_MODE_DIGITAL,  16,   0,    0x0350+offset, 0,   0x0380+offset, 0);
    pScope->AddTrace("VXS_DATA1",      4*16+8, TRACE_MODE_DIGITAL,  16,  16,    0x0350+offset,16,   0x0380+offset,16);
    pScope->AddTrace("VXS_DATA2",      4*16+8, TRACE_MODE_DIGITAL,  16,  32,    0x0354+offset, 0,   0x0384+offset, 0);
    pScope->AddTrace("VXS_DATA3",      4*16+8, TRACE_MODE_DIGITAL,  16,  48,    0x0354+offset,16,   0x0384+offset,16);
    pScope->AddTrace("VXS_DATA4",      4*16+8, TRACE_MODE_DIGITAL,  16,  64,    0x0358+offset, 0,   0x0388+offset, 0);
    pScope->AddTrace("VXS_DATA5",      4*16+8, TRACE_MODE_DIGITAL,  16,  80,    0x0358+offset,16,   0x0388+offset,16);
    pScope->AddTrace("VXS_DATA6",      4*16+8, TRACE_MODE_DIGITAL,  16,  96,    0x035C+offset, 0,   0x038C+offset, 0);
    pScope->AddTrace("VXS_DATA7",      4*16+8, TRACE_MODE_DIGITAL,  16, 112,    0x035C+offset,16,   0x038C+offset,16);
    pScope->AddTrace("VXS_DATA8",      4*16+8, TRACE_MODE_DIGITAL,  16, 128,    0x0360+offset, 0,   0x0390+offset, 0);
    pScope->AddTrace("VXS_DATA9",      4*16+8, TRACE_MODE_DIGITAL,  16, 144,    0x0360+offset,16,   0x0390+offset,16);
    pScope->AddTrace("VXS_DATA10",     4*16+8, TRACE_MODE_DIGITAL,  16, 160,    0x0364+offset, 0,   0x0394+offset, 0);
    pScope->AddTrace("VXS_DATA11",     4*16+8, TRACE_MODE_DIGITAL,  16, 176,    0x0364+offset,16,   0x0394+offset,16);
    pScope->AddTrace("VXS_DATA12",     4*16+8, TRACE_MODE_DIGITAL,  16, 192,    0x0368+offset, 0,   0x0398+offset, 0);
    pScope->AddTrace("VXS_DATA13",     4*16+8, TRACE_MODE_DIGITAL,  16, 208,    0x0368+offset,16,   0x0398+offset,16);
    pScope->AddTrace("VXS_DATA14",     4*16+8, TRACE_MODE_DIGITAL,  16, 224,    0x036C+offset, 0,   0x039C+offset, 0);
    pScope->AddTrace("VXS_DATA15",     4*16+8, TRACE_MODE_DIGITAL,  16, 240,    0x036C+offset,16,   0x039C+offset,16);

    pScope->AddTrace("FIBER_DATA0",    4*32+8, TRACE_MODE_DIGITAL,  32, 256,    0x0370+offset, 0,   0x03A0+offset, 0);
    pScope->AddTrace("FIBER_DATA1",    4*32+8, TRACE_MODE_DIGITAL,  32, 280,    0x0374+offset, 0,   0x03A4+offset, 0);
  }
};

#endif
