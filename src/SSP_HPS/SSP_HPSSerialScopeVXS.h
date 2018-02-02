#ifndef SSP_HPSSERIALSCOPEVXS_H
#define SSP_HPSSERIALSCOPEVXS_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class SSP_HPSSerialScopeVXS	: public TGCompositeFrame
{
public:
	SSP_HPSSerialScopeVXS(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = 0x1900+pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		{
			//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
      //pScope->Init(512, 0x44+offset, 0, 0x30+offset, 0, 0x40+offset, 3);
      pScope->Init(512, 0x34+offset, 0, 0x30+offset, 0, 0x40+offset, 3);
     
      pScope->AddTrace("RxData",      128,  TRACE_MODE_ANALOG,  32, 0,  0x60+offset, 0, 0x80+offset, 0);
      pScope->AddTrace("RxData",      4*32+8, TRACE_MODE_DIGITAL, 32, 0,  0xA0+offset, 0, 0xC0+offset, 0);
      pScope->AddTrace("RxDataRdyN",    27,   TRACE_MODE_DIGITAL, 1,  32, 0xA4+offset, 0, 0xC4+offset, 0);
      pScope->AddTrace("RxFrameIndex",  4*2+8,  TRACE_MODE_DIGITAL, 2,  33, 0xA4+offset, 1, 0xC4+offset, 1);

		}
	}
};

#endif


