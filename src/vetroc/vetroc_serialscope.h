#ifndef VETROC_SERIALSCOPE_H
#define VETROC_SERIALSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class vetroc_serialscope	: public TGCompositeFrame
{
public:
	vetroc_serialscope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x0434+offset, 0, 0x0430+offset, 0, 0x0440+offset, 2);

		//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("TxData",			128,		TRACE_MODE_ANALOG,	32,	0,		0x0460+offset, 0,	0x0480+offset, 0);
		pScope->AddTrace("TxData",			4*32+8,	TRACE_MODE_DIGITAL,	32,	0,		0x04A0+offset, 0,	0x04C0+offset, 0);
		pScope->AddTrace("TxDataRdyN",	27,		TRACE_MODE_DIGITAL,	1,		32,	0x04A4+offset, 0,	0x04C4+offset, 0);
		pScope->AddTrace("TxFrameIndex",	4*3+8,	TRACE_MODE_ANALOG,	3,		33,	0x04A4+offset, 1,	0x04C4+offset, 1);
	}
};

#endif


