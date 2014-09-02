#ifndef FADC250_SERIALSCOPE_H
#define FADC250_SERIALSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class FADC250_SerialScope	: public TGCompositeFrame
{
public:
	FADC250_SerialScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x051C+offset, 0, 0x0518+offset, 0, 0x0520+offset, 2);

		//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("TxData",			128,		TRACE_MODE_ANALOG,	32,	0,		0x0528+offset, 0,	0x052C+offset, 0);
		pScope->AddTrace("TxData",			4*32+8,	TRACE_MODE_DIGITAL,	32,	0,		0x0530+offset, 0,	0x0538+offset, 0);
		pScope->AddTrace("TxDataRdyN",	27,		TRACE_MODE_DIGITAL,	1,		32,	0x0534+offset, 0,	0x053C+offset, 0);
		pScope->AddTrace("TxFrameIndex",	4*3+8,	TRACE_MODE_ANALOG,	3,		33,	0x0534+offset, 1,	0x053C+offset, 1);
	}
};

#endif


