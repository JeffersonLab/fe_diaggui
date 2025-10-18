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

      pScope->AddTrace("ECAL-Cosmic",        27, TRACE_MODE_DIGITAL,  1,   0, 0x10+offset, 0, 0x60+offset, 0);
      pScope->AddTrace("ECAL-Scint",         27, TRACE_MODE_DIGITAL,  1,   1, 0x10+offset, 1, 0x60+offset, 1);
      pScope->AddTrace("ECALxHCAL",          27, TRACE_MODE_DIGITAL,  1,   2, 0x10+offset, 2, 0x60+offset, 2);
      pScope->AddTrace("ECAL-Cluster",       27, TRACE_MODE_DIGITAL,  1,   3, 0x10+offset, 3, 0x60+offset, 3);
      pScope->AddTrace("HCAL-Cluster",       27, TRACE_MODE_DIGITAL,  1,   4, 0x10+offset, 4, 0x60+offset, 4);
    }
  }
};

#endif


