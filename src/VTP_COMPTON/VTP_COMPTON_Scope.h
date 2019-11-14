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
    pScope->Init(512, 0x9024+offset, 0, 0x9020+offset, 0, 0x9090+offset,15);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("FADC3_0",            128, TRACE_MODE_ANALOG,  13,   0,    0x9028+offset,13,   0x9028+offset, 0);
    pScope->AddTrace("FADC3_1",            128, TRACE_MODE_ANALOG,  13,  13,    0x9028+offset,29,   0x9028+offset,16);
    pScope->AddTrace("FADC3_2",            128, TRACE_MODE_ANALOG,  13,  26,    0x902C+offset,13,   0x902C+offset, 0);
    pScope->AddTrace("FADC3_3",            128, TRACE_MODE_ANALOG,  13,  39,    0x902C+offset,29,   0x902C+offset,16);
    pScope->AddTrace("FADC3_4",            128, TRACE_MODE_ANALOG,  13,  52,    0x9030+offset,13,   0x9030+offset, 0);
    pScope->AddTrace("FADC3_5",            128, TRACE_MODE_ANALOG,  13,  65,    0x9030+offset,29,   0x9030+offset,16);
    pScope->AddTrace("FADC3_6",            128, TRACE_MODE_ANALOG,  13,  78,    0x9034+offset,13,   0x9034+offset, 0);
    pScope->AddTrace("FADC3_7",            128, TRACE_MODE_ANALOG,  13,  91,    0x9034+offset,29,   0x9034+offset,16);
    pScope->AddTrace("FADC3_8",            128, TRACE_MODE_ANALOG,  13, 104,    0x9038+offset,13,   0x9038+offset, 0);
    pScope->AddTrace("FADC3_9",            128, TRACE_MODE_ANALOG,  13, 117,    0x9038+offset,29,   0x9038+offset,16);
    pScope->AddTrace("FADC3_10",           128, TRACE_MODE_ANALOG,  13, 130,    0x903C+offset,13,   0x903C+offset, 0);
    pScope->AddTrace("FADC3_11",           128, TRACE_MODE_ANALOG,  13, 143,    0x903C+offset,29,   0x903C+offset,16);
    pScope->AddTrace("FADC3_12",           128, TRACE_MODE_ANALOG,  13, 156,    0x9040+offset,13,   0x9040+offset, 0);
    pScope->AddTrace("FADC3_13",           128, TRACE_MODE_ANALOG,  13, 169,    0x9040+offset,29,   0x9040+offset,16);
    pScope->AddTrace("FADC3_14",           128, TRACE_MODE_ANALOG,  13, 182,    0x9044+offset,13,   0x9044+offset, 0);
    pScope->AddTrace("FADC3_15",           128, TRACE_MODE_ANALOG,  13, 195,    0x9044+offset,29,   0x9044+offset,16);

    pScope->AddTrace("VETROC13_A",         132, TRACE_MODE_DIGITAL, 32, 208,    0x9048+offset, 0,   0x906C+offset, 0);
    pScope->AddTrace("VETROC13_B",         132, TRACE_MODE_DIGITAL, 32, 240,    0x904C+offset, 0,   0x9070+offset, 0);
    pScope->AddTrace("VETROC13_C",         132, TRACE_MODE_DIGITAL, 32, 272,    0x9050+offset, 0,   0x9074+offset, 0);
    pScope->AddTrace("VETROC13_D",         132, TRACE_MODE_DIGITAL, 32, 304,    0x9054+offset, 0,   0x9078+offset, 0);

    pScope->AddTrace("VETROC14_A",         132, TRACE_MODE_DIGITAL, 32, 336,    0x9058+offset, 0,   0x907C+offset, 0);
    pScope->AddTrace("VETROC14_B",         132, TRACE_MODE_DIGITAL, 32, 368,    0x905C+offset, 0,   0x9080+offset, 0);
    pScope->AddTrace("VETROC14_C",         132, TRACE_MODE_DIGITAL, 32, 400,    0x9060+offset, 0,   0x9084+offset, 0);
    pScope->AddTrace("VETROC14_D",         132, TRACE_MODE_DIGITAL, 32, 432,    0x9064+offset, 0,   0x9088+offset, 0);

    pScope->AddTrace("Ready",               27, TRACE_MODE_DIGITAL,  1, 471,    0x9068+offset, 5,   0x908C+offset, 5);

    pScope->AddTrace("Trigbit0",            27, TRACE_MODE_DIGITAL,  1, 464,    0x9068+offset, 0,   0x908C+offset, 0);
    pScope->AddTrace("Trigbit1",            27, TRACE_MODE_DIGITAL,  1, 465,    0x9068+offset, 1,   0x908C+offset, 1);
    pScope->AddTrace("Trigbit2",            27, TRACE_MODE_DIGITAL,  1, 466,    0x9068+offset, 2,   0x908C+offset, 2);
    pScope->AddTrace("Trigbit3",            27, TRACE_MODE_DIGITAL,  1, 467,    0x9068+offset, 3,   0x908C+offset, 3);
    pScope->AddTrace("Trigbit4",            27, TRACE_MODE_DIGITAL,  1, 468,    0x9068+offset, 4,   0x908C+offset, 4);
  }
};

#endif
