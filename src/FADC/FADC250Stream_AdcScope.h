#ifndef FADC250STREAM_ADCSCOPE_H
#define FADC250STREAM_ADCSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class FADC250Stream_AdcScope  : public TGCompositeFrame
{
public:
  FADC250Stream_AdcScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    //pScope->SetRegWidth(16); // 16bit for FAV2/V3, 32bit for FAV2 Streaming

    //    void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x0904+offset, 0, 0x0900+offset, 0, 0x09A0+offset, 7);
      //    void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("Ch0",   128,    TRACE_MODE_ANALOG,  13,   0,    0x0920 + offset, 0, 0x0960 + offset, 0);
    pScope->AddTrace("Ch1",   128,    TRACE_MODE_ANALOG,  13,  13,    0x0924 + offset, 0, 0x0964 + offset, 0);
    pScope->AddTrace("Ch2",   128,    TRACE_MODE_ANALOG,  13,  26,    0x0928 + offset, 0, 0x0968 + offset, 0);
    pScope->AddTrace("Ch3",   128,    TRACE_MODE_ANALOG,  13,  39,    0x092C + offset, 0, 0x096C + offset, 0);
    pScope->AddTrace("Ch4",   128,    TRACE_MODE_ANALOG,  13,  52,    0x0930 + offset, 0, 0x0970 + offset, 0);
    pScope->AddTrace("Ch5",   128,    TRACE_MODE_ANALOG,  13,  65,    0x0934 + offset, 0, 0x0974 + offset, 0);
    pScope->AddTrace("Ch6",   128,    TRACE_MODE_ANALOG,  13,  78,    0x0938 + offset, 0, 0x0978 + offset, 0);
    pScope->AddTrace("Ch7",   128,    TRACE_MODE_ANALOG,  13,  91,    0x093C + offset, 0, 0x097C + offset, 0);
    pScope->AddTrace("Ch8",   128,    TRACE_MODE_ANALOG,  13, 104,    0x0940 + offset, 0, 0x0980 + offset, 0);
    pScope->AddTrace("Ch9",   128,    TRACE_MODE_ANALOG,  13, 117,    0x0944 + offset, 0, 0x0984 + offset, 0);
    pScope->AddTrace("Ch10",  128,    TRACE_MODE_ANALOG,  13, 130,    0x0948 + offset, 0, 0x0988 + offset, 0);
    pScope->AddTrace("Ch11",  128,    TRACE_MODE_ANALOG,  13, 143,    0x094C + offset, 0, 0x098C + offset, 0);
    pScope->AddTrace("Ch12",  128,    TRACE_MODE_ANALOG,  13, 156,    0x0950 + offset, 0, 0x0990 + offset, 0);
    pScope->AddTrace("Ch13",  128,    TRACE_MODE_ANALOG,  13, 169,    0x0954 + offset, 0, 0x0994 + offset, 0);
    pScope->AddTrace("Ch14",  128,    TRACE_MODE_ANALOG,  13, 182,    0x0958 + offset, 0, 0x0998 + offset, 0);
    pScope->AddTrace("Ch15",  128,    TRACE_MODE_ANALOG,  13, 195,    0x095C + offset, 0, 0x099C + offset, 0);
    
    pScope->AddTrace("NCS",    32,    TRACE_MODE_DIGITAL,  1, 208,    0x0910 + offset, 0, 0x0914 + offset, 0);
    pScope->AddTrace("SCK",    32,    TRACE_MODE_DIGITAL,  1, 209,    0x0910 + offset, 1, 0x0914 + offset, 1);
    pScope->AddTrace("SDO",    32,    TRACE_MODE_DIGITAL,  1, 210,    0x0910 + offset, 2, 0x0914 + offset, 2);
    pScope->AddTrace("SDI",    32,    TRACE_MODE_DIGITAL,  1, 211,    0x0910 + offset, 3, 0x0914 + offset, 3);
  }
};

#endif


