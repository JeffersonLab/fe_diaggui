#ifndef SSP_SBSEHCAL_COSMICSCOPE_H
#define SSP_SBSEHCAL_COSMICSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class SSP_SBSEHCAL_CosmicScope : public TGCompositeFrame
{
public:
  SSP_SBSEHCAL_CosmicScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = 0x6600+pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    {
      //void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
      pScope->Init(512, 0x04+offset, 0, 0x00+offset, 0, 0xB0+offset, 17);

      pScope->AddTrace("ECalCosmic",      4*7+8, TRACE_MODE_DIGITAL,  7,   0, 0x10+offset, 1, 0x60+offset, 1);
      pScope->AddTrace("AUX",             4*8+8, TRACE_MODE_DIGITAL,  8,   7, 0x10+offset, 0, 0x60+offset, 0);
      pScope->AddTrace("ECal1-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31,  15, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal1-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31,  46, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal2-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31,  77, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal2-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31, 108, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal3-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31, 139, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal3-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31, 170, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal4-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31, 201, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal4-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31, 232, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal5-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31, 263, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal5-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31, 294, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal6-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31, 325, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal6-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31, 356, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal7-BinsL",    32*8+8, TRACE_MODE_DIGITAL, 31, 387, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("ECal7-BinsH",    32*8+8, TRACE_MODE_DIGITAL, 31, 418, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("HCal-BinsL",     32*8+8, TRACE_MODE_DIGITAL, 31, 449, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("HCal-BinsH",     32*8+8, TRACE_MODE_DIGITAL, 31, 480, 0x20+offset, 0, 0x70+offset, 0);
      pScope->AddTrace("BinsValid",          27, TRACE_MODE_DIGITAL,  1, 511, 0x4C+offset,31, 0xBC+offset,31);
      pScope->AddTrace("Trigger0",           27, TRACE_MODE_DIGITAL,  1, 512, 0x50+offset, 0, 0xA0+offset, 0);
      pScope->AddTrace("Trigger1",           27, TRACE_MODE_DIGITAL,  1, 513, 0x50+offset, 1, 0xA0+offset, 1);
      pScope->AddTrace("Trigger2",           27, TRACE_MODE_DIGITAL,  1, 514, 0x50+offset, 2, 0xA0+offset, 2);
      pScope->AddTrace("Trigger3",           27, TRACE_MODE_DIGITAL,  1, 515, 0x50+offset, 3, 0xA0+offset, 3);
      pScope->AddTrace("Trigger4",           27, TRACE_MODE_DIGITAL,  1, 516, 0x50+offset, 4, 0xA0+offset, 4);
    }
  }
};

#endif


