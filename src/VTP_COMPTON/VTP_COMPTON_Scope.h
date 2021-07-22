#ifndef VTP_COMPTON_SCOPE_H
#define VTP_COMPTON_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_COMPTON_Scope : public TGCompositeFrame
{
public:
  VTP_COMPTON_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x9024+offset, 0, 0x9020+offset, 0, 0x90B4+offset,17);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("FADC3_CH0",          128, TRACE_MODE_ANALOG,  13,   0,    0x9028+offset,13,   0x9028+offset, 0);
    pScope->AddTrace("MPS", 27, TRACE_MODE_DIGITAL, 1, 531, 0x906C+offset, 6, 0x90B0+offset, 6);
    pScope->AddTrace("Helicity", 27, TRACE_MODE_DIGITAL, 1, 532, 0x906C+offset, 7, 0x90B0+offset, 7);

    pScope->AddTrace("VETROC13_A",          68, TRACE_MODE_DIGITAL, 32,  13,    0x902C+offset, 0,   0x9070+offset, 0);
    pScope->AddTrace("VETROC13_B",          68, TRACE_MODE_DIGITAL, 32,  45,    0x9030+offset, 0,   0x9074+offset, 0);
    pScope->AddTrace("VETROC13_C",          68, TRACE_MODE_DIGITAL, 32,  77,    0x9034+offset, 0,   0x9078+offset, 0);
    pScope->AddTrace("VETROC13_D",          68, TRACE_MODE_DIGITAL, 32, 109,    0x9038+offset, 0,   0x907C+offset, 0);

    pScope->AddTrace("VETROC14_A",          68, TRACE_MODE_DIGITAL, 32, 141,    0x903C+offset, 0,   0x9080+offset, 0);
    pScope->AddTrace("VETROC14_B",          68, TRACE_MODE_DIGITAL, 32, 173,    0x9040+offset, 0,   0x9084+offset, 0);
    pScope->AddTrace("VETROC14_C",          68, TRACE_MODE_DIGITAL, 32, 205,    0x9044+offset, 0,   0x9088+offset, 0);
    pScope->AddTrace("VETROC14_D",          68, TRACE_MODE_DIGITAL, 32, 237,    0x9048+offset, 0,   0x908C+offset, 0);

    pScope->AddTrace("VETROC15_A",          68, TRACE_MODE_DIGITAL, 32, 269,    0x904C+offset, 0,   0x9090+offset, 0);
    pScope->AddTrace("VETROC15_B",          68, TRACE_MODE_DIGITAL, 32, 301,    0x9050+offset, 0,   0x9094+offset, 0);
    pScope->AddTrace("VETROC15_C",          68, TRACE_MODE_DIGITAL, 32, 333,    0x9054+offset, 0,   0x9098+offset, 0);
    pScope->AddTrace("VETROC15_D",          68, TRACE_MODE_DIGITAL, 32, 365,    0x9058+offset, 0,   0x909C+offset, 0);

    pScope->AddTrace("VETROC16_A",          68, TRACE_MODE_DIGITAL, 32, 397,    0x905C+offset, 0,   0x90A0+offset, 0);
    pScope->AddTrace("VETROC16_B",          68, TRACE_MODE_DIGITAL, 32, 429,    0x9060+offset, 0,   0x90A4+offset, 0);
    pScope->AddTrace("VETROC16_C",          68, TRACE_MODE_DIGITAL, 32, 461,    0x9064+offset, 0,   0x90A8+offset, 0);
    pScope->AddTrace("VETROC16_D",          68, TRACE_MODE_DIGITAL, 32, 493,    0x9068+offset, 0,   0x90AC+offset, 0);

    pScope->AddTrace("Ready",               27, TRACE_MODE_DIGITAL,  1, 530,    0x906C+offset, 5,   0x90B0+offset, 5);

    pScope->AddTrace("Trigbit0",            27, TRACE_MODE_DIGITAL,  1, 525,    0x906C+offset, 0,   0x90B0+offset, 0);
    pScope->AddTrace("Trigbit1",            27, TRACE_MODE_DIGITAL,  1, 526,    0x906C+offset, 1,   0x90B0+offset, 1);
    pScope->AddTrace("Trigbit2",            27, TRACE_MODE_DIGITAL,  1, 527,    0x906C+offset, 2,   0x90B0+offset, 2);
    pScope->AddTrace("Trigbit3",            27, TRACE_MODE_DIGITAL,  1, 528,    0x906C+offset, 3,   0x90B0+offset, 3);
    pScope->AddTrace("Trigbit4",            27, TRACE_MODE_DIGITAL,  1, 529,    0x906C+offset, 4,   0x90B0+offset, 4);
  }
};

#endif
