#ifndef SSP_GTSERIALSCOPEQSFP_H
#define SSP_GTSERIALSCOPEQSFP_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class SSP_GTSerialScopeQSFP	: public TGCompositeFrame
{
public:
	SSP_GTSerialScopeQSFP(const TGWindow *p, ModuleFrame *pModule, int inst) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = 0x1000+pModule->BaseAddr+inst*256;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		{
			//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
      pScope->Init(512, 0x44+offset, 0, 0x40+offset, 0, 0x60+offset, 3);
     
      pScope->AddTrace("RxDataL",     4*32+8, TRACE_MODE_DIGITAL, 32,   0, 0x48+offset, 0, 0x54+offset, 0);
      pScope->AddTrace("RxDataH",     4*32+8, TRACE_MODE_DIGITAL, 32,  32, 0x4C+offset, 0, 0x58+offset, 0);
      pScope->AddTrace("RxDataRdyN",      27, TRACE_MODE_DIGITAL,  1,  64, 0x50+offset, 0, 0x5C+offset, 0);
      pScope->AddTrace("RxFrameIndex", 4*2+8, TRACE_MODE_DIGITAL,  6,  65, 0x50+offset, 1, 0x5C+offset, 1);
		}
	}
};

#endif


