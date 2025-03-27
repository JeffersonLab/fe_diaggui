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
    pScope->Init(512, 0xB424+offset, 0, 0xB420+offset, 0, 0xB490+offset,12);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("SLOT3",        4*16+8, TRACE_MODE_DIGITAL,  16,   0,    0xB430+offset, 0,   0xB460+offset,  0);
    pScope->AddTrace("SLOT4",        4*16+8, TRACE_MODE_DIGITAL,  16,  16,    0xB430+offset,16,   0xB460+offset, 16);
    pScope->AddTrace("SLOT5",        4*16+8, TRACE_MODE_DIGITAL,  16,  32,    0xB434+offset, 0,   0xB464+offset,  0);
    pScope->AddTrace("SLOT6",        4*16+8, TRACE_MODE_DIGITAL,  16,  48,    0xB434+offset,16,   0xB464+offset, 16);
    pScope->AddTrace("SLOT7",        4*16+8, TRACE_MODE_DIGITAL,  16,  64,    0xB438+offset, 0,   0xB468+offset,  0);
    pScope->AddTrace("SLOT8",        4*16+8, TRACE_MODE_DIGITAL,  16,  80,    0xB438+offset,16,   0xB468+offset, 16);
    pScope->AddTrace("SLOT9",        4*16+8, TRACE_MODE_DIGITAL,  16,  96,    0xB43C+offset, 0,   0xB46C+offset,  0);
    pScope->AddTrace("SLOT10",       4*16+8, TRACE_MODE_DIGITAL,  16, 112,    0xB43C+offset,16,   0xB46C+offset, 16);
    pScope->AddTrace("SLOT13",       4*16+8, TRACE_MODE_DIGITAL,  16, 128,    0xB440+offset, 0,   0xB470+offset,  0);
    pScope->AddTrace("SLOT14",       4*16+8, TRACE_MODE_DIGITAL,  16, 144,    0xB440+offset,16,   0xB470+offset, 16);
    pScope->AddTrace("SLOT15",       4*16+8, TRACE_MODE_DIGITAL,  16, 160,    0xB444+offset, 0,   0xB474+offset,  0);
    pScope->AddTrace("SLOT16",       4*16+8, TRACE_MODE_DIGITAL,  16, 176,    0xB444+offset,16,   0xB474+offset, 16);
    pScope->AddTrace("SLOT17",       4*16+8, TRACE_MODE_DIGITAL,  16, 192,    0xB448+offset, 0,   0xB478+offset,  0);
    pScope->AddTrace("SLOT18",       4*16+8, TRACE_MODE_DIGITAL,  16, 208,    0xB448+offset,16,   0xB478+offset, 16);
    pScope->AddTrace("SLOT19",       4*16+8, TRACE_MODE_DIGITAL,  16, 224,    0xB44C+offset, 0,   0xB47C+offset,  0);
    pScope->AddTrace("SLOT20",       4*16+8, TRACE_MODE_DIGITAL,  16, 240,    0xB44C+offset,16,   0xB47C+offset, 16);
    pScope->AddTrace("TRIGGER",      4* 1+8, TRACE_MODE_DIGITAL,   1, 256,    0xB450+offset, 0,   0xB480+offset,  0);
    pScope->AddTrace("VALID",        4* 1+8, TRACE_MODE_DIGITAL,   1, 257,    0xB450+offset, 1,   0xB480+offset,  1);
    
/* SBS ECAL Cosmic single module scope
    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0xB414+offset, 0, 0xB410+offset, 0, 0xB500+offset,12);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("SMO_0",        4* 2+8, TRACE_MODE_DIGITAL,   2,   0,    0xB418+offset, 0,   0xB41C+offset,  0);
    pScope->AddTrace("SMO_1",        4* 2+8, TRACE_MODE_DIGITAL,   2,   2,    0xB418+offset, 2,   0xB41C+offset,  2);
    pScope->AddTrace("SMO_2",        4* 2+8, TRACE_MODE_DIGITAL,   2,   4,    0xB418+offset, 4,   0xB41C+offset,  4);
    pScope->AddTrace("TRIG",             27, TRACE_MODE_DIGITAL,   1,   6,    0xB418+offset, 6,   0xB41C+offset,  6);
    pScope->AddTrace("VALID",            27, TRACE_MODE_DIGITAL,   1,   7,    0xB418+offset, 7,   0xB41C+offset,  7);

    pScope->AddTrace("FADC_SL8_CH0",    128,  TRACE_MODE_ANALOG,  13,   8,    0xB424+offset, 0,   0xB494+offset,  0);
    pScope->AddTrace("FADC_SL8_CH1",    128,  TRACE_MODE_ANALOG,  13,  21,    0xB428+offset, 0,   0xB498+offset,  0);
    pScope->AddTrace("FADC_SL8_CH2",    128,  TRACE_MODE_ANALOG,  13,  34,    0xB42C+offset, 0,   0xB49C+offset,  0);
    pScope->AddTrace("FADC_SL8_CH3",    128,  TRACE_MODE_ANALOG,  13,  47,    0xB430+offset, 0,   0xB4A0+offset,  0);
    pScope->AddTrace("FADC_SL8_CH4",    128,  TRACE_MODE_ANALOG,  13,  60,    0xB434+offset, 0,   0xB4A4+offset,  0);
    pScope->AddTrace("FADC_SL8_CH5",    128,  TRACE_MODE_ANALOG,  13,  73,    0xB438+offset, 0,   0xB4A8+offset,  0);
    pScope->AddTrace("FADC_SL8_CH6",    128,  TRACE_MODE_ANALOG,  13,  86,    0xB43C+offset, 0,   0xB4AC+offset,  0);
    pScope->AddTrace("FADC_SL8_CH7",    128,  TRACE_MODE_ANALOG,  13,  99,    0xB440+offset, 0,   0xB4B0+offset,  0);
    pScope->AddTrace("FADC_SL8_CH8",    128,  TRACE_MODE_ANALOG,  13, 112,    0xB444+offset, 0,   0xB4B4+offset,  0);
    pScope->AddTrace("FADC_SL8_CH9",    128,  TRACE_MODE_ANALOG,  13, 125,    0xB448+offset, 0,   0xB4B8+offset,  0);
    pScope->AddTrace("FADC_SL8_CH10",   128,  TRACE_MODE_ANALOG,  13, 138,    0xB44C+offset, 0,   0xB4BC+offset,  0);
    pScope->AddTrace("FADC_SL8_CH11",   128,  TRACE_MODE_ANALOG,  13, 151,    0xB450+offset, 0,   0xB4C0+offset,  0);
    pScope->AddTrace("FADC_SL8_CH12",   128,  TRACE_MODE_ANALOG,  13, 164,    0xB454+offset, 0,   0xB4C4+offset,  0);
    pScope->AddTrace("FADC_SL8_CH13",   128,  TRACE_MODE_ANALOG,  13, 177,    0xB458+offset, 0,   0xB4C8+offset,  0);
    pScope->AddTrace("FADC_SL8_CH14",   128,  TRACE_MODE_ANALOG,  13, 190,    0xB45C+offset, 0,   0xB4CC+offset,  0);
    pScope->AddTrace("FADC_SL8_CH15",   128,  TRACE_MODE_ANALOG,  13, 203,    0xB460+offset, 0,   0xB4D0+offset,  0);
                                                                        
    pScope->AddTrace("FADC_SL9_CH0",    128,  TRACE_MODE_ANALOG,  13, 216,    0xB464+offset, 0,   0xB4D4+offset,  0);
    pScope->AddTrace("FADC_SL9_CH1",    128,  TRACE_MODE_ANALOG,  13, 229,    0xB468+offset, 0,   0xB4D8+offset,  0);
    pScope->AddTrace("FADC_SL9_CH2",    128,  TRACE_MODE_ANALOG,  13, 242,    0xB46C+offset, 0,   0xB4DC+offset,  0);
    pScope->AddTrace("FADC_SL9_CH3",    128,  TRACE_MODE_ANALOG,  13, 255,    0xB470+offset, 0,   0xB4E0+offset,  0);
    pScope->AddTrace("FADC_SL9_CH4",    128,  TRACE_MODE_ANALOG,  13, 268,    0xB474+offset, 0,   0xB4E4+offset,  0);
    pScope->AddTrace("FADC_SL9_CH5",    128,  TRACE_MODE_ANALOG,  13, 281,    0xB478+offset, 0,   0xB4E8+offset,  0);
    pScope->AddTrace("FADC_SL9_CH6",    128,  TRACE_MODE_ANALOG,  13, 294,    0xB47C+offset, 0,   0xB4EC+offset,  0);
    pScope->AddTrace("FADC_SL9_CH7",    128,  TRACE_MODE_ANALOG,  13, 307,    0xB480+offset, 0,   0xB4F0+offset,  0);
    pScope->AddTrace("FADC_SL9_CH8",    128,  TRACE_MODE_ANALOG,  13, 320,    0xB484+offset, 0,   0xB4F4+offset,  0);
    pScope->AddTrace("FADC_SL9_CH9",    128,  TRACE_MODE_ANALOG,  13, 333,    0xB488+offset, 0,   0xB4F8+offset,  0);
    pScope->AddTrace("FADC_SL9_CH10",   128,  TRACE_MODE_ANALOG,  13, 346,    0xB48C+offset, 0,   0xB4FC+offset,  0);
*/
  }
};

#endif
