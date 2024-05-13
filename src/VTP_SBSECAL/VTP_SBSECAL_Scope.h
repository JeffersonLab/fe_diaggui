#ifndef VTP_SBSECAL_SCOPE_H
#define VTP_SBSECAL_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_SBSECAL_Scope : public TGCompositeFrame
{
public:
  VTP_SBSECAL_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0xB414+offset, 0, 0xB410+offset, 0, 0xB500+offset,12);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("SMO_0",        4* 2+8, TRACE_MODE_DIGITAL,   2,   0,    0xB418+offset, 0,   0xB41C+offset,  0);
    pScope->AddTrace("SMO_1",        4* 2+8, TRACE_MODE_DIGITAL,   2,   2,    0xB418+offset, 2,   0xB41C+offset,  2);
    pScope->AddTrace("SMO_2",        4* 2+8, TRACE_MODE_DIGITAL,   2,   4,    0xB418+offset, 4,   0xB41C+offset,  4);
    pScope->AddTrace("TRIG",             27, TRACE_MODE_DIGITAL,   1,   6,    0xB418+offset, 6,   0xB41C+offset,  6);
    pScope->AddTrace("VALID",            27, TRACE_MODE_DIGITAL,   1,   7,    0xB418+offset, 7,   0xB41C+offset,  7);

    pScope->AddTrace("FADC_SL8_CH0",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB424+offset, 0,   0xB494+offset,  8);
    pScope->AddTrace("FADC_SL8_CH1",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB428+offset, 0,   0xB498+offset, 21);
    pScope->AddTrace("FADC_SL8_CH2",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB42C+offset, 0,   0xB49C+offset, 34);
    pScope->AddTrace("FADC_SL8_CH3",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB430+offset, 0,   0xB4A0+offset, 47);
    pScope->AddTrace("FADC_SL8_CH4",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB434+offset, 0,   0xB4A4+offset, 60);
    pScope->AddTrace("FADC_SL8_CH5",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB438+offset, 0,   0xB4A8+offset, 73);
    pScope->AddTrace("FADC_SL8_CH6",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB43C+offset, 0,   0xB4AC+offset, 86);
    pScope->AddTrace("FADC_SL8_CH7",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB440+offset, 0,   0xB4B0+offset, 99);
    pScope->AddTrace("FADC_SL8_CH8",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB444+offset, 0,   0xB4B4+offset,112);
    pScope->AddTrace("FADC_SL8_CH9",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB448+offset, 0,   0xB4B8+offset,125);
    pScope->AddTrace("FADC_SL8_CH10",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB44C+offset, 0,   0xB4BC+offset,138);
    pScope->AddTrace("FADC_SL8_CH11",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB450+offset, 0,   0xB4C0+offset,151);
    pScope->AddTrace("FADC_SL8_CH12",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB454+offset, 0,   0xB4C4+offset,164);
    pScope->AddTrace("FADC_SL8_CH13",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB458+offset, 0,   0xB4C8+offset,177);
    pScope->AddTrace("FADC_SL8_CH14",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB45C+offset, 0,   0xB4CC+offset,190);
    pScope->AddTrace("FADC_SL8_CH15",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB460+offset, 0,   0xB4D0+offset,203);
    
    pScope->AddTrace("FADC_SL9_CH0",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB464+offset, 0,   0xB4D4+offset,216);
    pScope->AddTrace("FADC_SL9_CH1",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB468+offset, 0,   0xB4D8+offset,229);
    pScope->AddTrace("FADC_SL9_CH2",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB46C+offset, 0,   0xB4DC+offset,242);
    pScope->AddTrace("FADC_SL9_CH3",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB470+offset, 0,   0xB4E0+offset,255);
    pScope->AddTrace("FADC_SL9_CH4",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB474+offset, 0,   0xB4E4+offset,268);
    pScope->AddTrace("FADC_SL9_CH5",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB478+offset, 0,   0xB4E8+offset,281);
    pScope->AddTrace("FADC_SL9_CH6",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB47C+offset, 0,   0xB4EC+offset,294);
    pScope->AddTrace("FADC_SL9_CH7",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB480+offset, 0,   0xB4F0+offset,307);
    pScope->AddTrace("FADC_SL9_CH8",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB484+offset, 0,   0xB4F4+offset,320);
    pScope->AddTrace("FADC_SL9_CH9",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB488+offset, 0,   0xB4F8+offset,333);
    pScope->AddTrace("FADC_SL9_CH10",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB48C+offset, 0,   0xB4FC+offset,346);
  }
};

#endif
