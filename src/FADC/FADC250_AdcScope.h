#ifndef FADC250_ADCSCOPE_H
#define FADC250_ADCSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class FADC250_AdcScope	: public TGCompositeFrame
{
public:
	FADC250_AdcScope(const TGWindow *p, ModuleFrame *pModule, int idx) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		if(idx & 0x1)
		{
			pScope->Init(512, 0x02A0+(idx>>1)*4+offset, 0, 0x0200+(idx>>1)*4+offset, 0, 0x02C0+idx*4+offset, 1);
			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
			pScope->AddTrace("AdcData",		256,		TRACE_MODE_ANALOG,	13,	0,		0x0220+(idx>>1)*4+offset, 0,	0x0240+(idx>>1)*4+offset, 0);
			pScope->AddTrace("AdcData",		4*32+8,	TRACE_MODE_DIGITAL,	13,	0,		0x0260+(idx>>1)*4+offset, 0,	0x0280+(idx>>1)*4+offset, 0);
		}
		else
		{
			pScope->Init(512, 0x02A0+(idx>>1)*4+offset, 16, 0x0200+(idx>>1)*4+offset, 16, 0x02C0+idx*4+offset, 1);
			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
			pScope->AddTrace("AdcData",		256,		TRACE_MODE_ANALOG,	13,	0,		0x0220+(idx>>1)*4+offset, 16,	0x0240+(idx>>1)*4+offset, 16);
			pScope->AddTrace("AdcData",		4*32+8,	TRACE_MODE_DIGITAL,	13,	0,		0x0260+(idx>>1)*4+offset, 16,	0x0280+(idx>>1)*4+offset, 16);
		}

	}
};

#endif


