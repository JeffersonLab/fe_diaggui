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
    pScope->AddTrace("SMO_0",        4* 2+8, TRACE_MODE_DIGITAL,   2,   0,    0xB418+offset, 0,   0xB41C+offset, 0);
    pScope->AddTrace("SMO_1",        4* 2+8, TRACE_MODE_DIGITAL,   2,   2,    0xB418+offset, 2,   0xB41C+offset, 2);
    pScope->AddTrace("SMO_2",        4* 2+8, TRACE_MODE_DIGITAL,   2,   4,    0xB418+offset, 4,   0xB41C+offset, 4);
    pScope->AddTrace("TRIG",             27, TRACE_MODE_DIGITAL,   1,   5,    0xB418+offset, 5,   0xB41C+offset, 5);
    pScope->AddTrace("VALID",            27, TRACE_MODE_DIGITAL,   1,   6,    0xB418+offset, 6,   0xB41C+offset, 6);

    pScope->AddTrace("FADC_SL3_CH0",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB424+offset, 0,   0xB494+offset, 0);
    pScope->AddTrace("FADC_SL3_CH1",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB428+offset, 0,   0xB498+offset, 0);
    pScope->AddTrace("FADC_SL3_CH2",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB42C+offset, 0,   0xB49C+offset, 0);
    pScope->AddTrace("FADC_SL3_CH3",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB430+offset, 0,   0xB4A0+offset, 0);
    pScope->AddTrace("FADC_SL3_CH4",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB434+offset, 0,   0xB4A4+offset, 0);
    pScope->AddTrace("FADC_SL3_CH5",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB438+offset, 0,   0xB4A8+offset, 0);
    pScope->AddTrace("FADC_SL3_CH6",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB43C+offset, 0,   0xB4AC+offset, 0);
    pScope->AddTrace("FADC_SL3_CH7",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB440+offset, 0,   0xB4B0+offset, 0);
    pScope->AddTrace("FADC_SL3_CH8",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB444+offset, 0,   0xB4B4+offset, 0);
    pScope->AddTrace("FADC_SL3_CH9",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB448+offset, 0,   0xB4B8+offset, 0);
    pScope->AddTrace("FADC_SL3_CH10",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB44C+offset, 0,   0xB4BC+offset, 0);
    pScope->AddTrace("FADC_SL3_CH11",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB450+offset, 0,   0xB4C0+offset, 0);
    pScope->AddTrace("FADC_SL3_CH12",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB454+offset, 0,   0xB4C4+offset, 0);
    pScope->AddTrace("FADC_SL3_CH13",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB458+offset, 0,   0xB4C8+offset, 0);
    pScope->AddTrace("FADC_SL3_CH14",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB45C+offset, 0,   0xB4CC+offset, 0);
    pScope->AddTrace("FADC_SL3_CH15",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB460+offset, 0,   0xB4D0+offset, 0);
    
    pScope->AddTrace("FADC_SL4_CH0",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB464+offset, 0,   0xB4D4+offset, 0);
    pScope->AddTrace("FADC_SL4_CH1",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB468+offset, 0,   0xB4D8+offset, 0);
    pScope->AddTrace("FADC_SL4_CH2",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB46C+offset, 0,   0xB4DC+offset, 0);
    pScope->AddTrace("FADC_SL4_CH3",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB470+offset, 0,   0xB4E0+offset, 0);
    pScope->AddTrace("FADC_SL4_CH4",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB474+offset, 0,   0xB4E4+offset, 0);
    pScope->AddTrace("FADC_SL4_CH5",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB478+offset, 0,   0xB4E8+offset, 0);
    pScope->AddTrace("FADC_SLOT4_CH6",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB47C+offset, 0,   0xB4EC+offset, 0);
    pScope->AddTrace("FADC_SLOT4_CH7",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB480+offset, 0,   0xB5F0+offset, 0);
    pScope->AddTrace("FADC_SLOT4_CH8",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB484+offset, 0,   0xB5F4+offset, 0);
    pScope->AddTrace("FADC_SLOT4_CH9",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB488+offset, 0,   0xB5F8+offset, 0);
    pScope->AddTrace("FADC_SLOT4_CH10",   128,  TRACE_MODE_ANALOG,  13,   8,    0xB48C+offset, 0,   0xB5FC+offset, 0);
  }
};

#endif
