#ifndef VTP_SOLIDECAL_SCOPE_H
#define VTP_SOLIDECAL_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_SOLIDECAL_Scope : public TGCompositeFrame
{
public:
  VTP_SOLIDECAL_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0xB014+offset, 0, 0xB010+offset, 0, 0xB060+offset,7);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("FADCReady",           27, TRACE_MODE_DIGITAL,  1, 210,    0xB058+offset, 2,   0xB05C+offset, 2);
    pScope->AddTrace("FADC3_CH0",          128, TRACE_MODE_ANALOG,  13,   0,    0xB018+offset,13,   0xB018+offset, 0);
    pScope->AddTrace("FADC3_CH1",          128, TRACE_MODE_ANALOG,  13,  13,    0xB01C+offset,13,   0xB01C+offset, 0);
    pScope->AddTrace("FADC3_CH2",          128, TRACE_MODE_ANALOG,  13,  26,    0xB020+offset,13,   0xB020+offset, 0);
    pScope->AddTrace("FADC3_CH3",          128, TRACE_MODE_ANALOG,  13,  39,    0xB024+offset,13,   0xB024+offset, 0);
    pScope->AddTrace("FADC3_CH4",          128, TRACE_MODE_ANALOG,  13,  52,    0xB028+offset,13,   0xB028+offset, 0);
    pScope->AddTrace("FADC3_CH5",          128, TRACE_MODE_ANALOG,  13,  65,    0xB02C+offset,13,   0xB02C+offset, 0);
    pScope->AddTrace("FADC3_CH6",          128, TRACE_MODE_ANALOG,  13,  78,    0xB030+offset,13,   0xB030+offset, 0);
    pScope->AddTrace("FADC3_CH7",          128, TRACE_MODE_ANALOG,  13,  91,    0xB034+offset,13,   0xB034+offset, 0);
    pScope->AddTrace("FADC3_CH8",          128, TRACE_MODE_ANALOG,  13, 104,    0xB038+offset,13,   0xB038+offset, 0);
    pScope->AddTrace("FADC3_CH9",          128, TRACE_MODE_ANALOG,  13, 117,    0xB03C+offset,13,   0xB03C+offset, 0);
    pScope->AddTrace("FADC3_CH10",         128, TRACE_MODE_ANALOG,  13, 130,    0xB040+offset,13,   0xB040+offset, 0);
    pScope->AddTrace("FADC3_CH11",         128, TRACE_MODE_ANALOG,  13, 143,    0xB044+offset,13,   0xB044+offset, 0);
    pScope->AddTrace("FADC3_CH12",         128, TRACE_MODE_ANALOG,  13, 156,    0xB048+offset,13,   0xB048+offset, 0);
    pScope->AddTrace("FADC3_CH13",         128, TRACE_MODE_ANALOG,  13, 169,    0xB04C+offset,13,   0xB04C+offset, 0);
    pScope->AddTrace("FADC3_CH14",         128, TRACE_MODE_ANALOG,  13, 182,    0xB050+offset,13,   0xB050+offset, 0);
    pScope->AddTrace("FADC3_CH15",         128, TRACE_MODE_ANALOG,  13, 195,    0xB054+offset,13,   0xB054+offset, 0);

    pScope->AddTrace("TrigbitReady",       27, TRACE_MODE_DIGITAL,   1, 209,    0xB058+offset, 1,   0xB05C+offset, 1);
    pScope->AddTrace("Trigbit0",           27, TRACE_MODE_DIGITAL,   1, 208,    0xB058+offset, 0,   0xB05C+offset, 0);
  }
};

#endif
