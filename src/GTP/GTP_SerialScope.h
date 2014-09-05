#ifndef GTP_SERIALSCOPE_H
#define GTP_SERIALSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class GTP_SerialScope	: public TGCompositeFrame
{
public:
	GTP_SerialScope(const TGWindow *p, ModuleFrame *pModule, int idx) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = idx*0x200+pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		// void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x1024+offset, 0, 0x1020+offset, 0, 0x1030+offset, 2);

		// void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("RxData",			128,		TRACE_MODE_ANALOG,	16,	0,	0x1050+offset, 0,	0x1070+offset, 0);
		pScope->AddTrace("RxData",			4*32+8,	TRACE_MODE_DIGITAL,	32,	0,	0x1090+offset, 0,	0x10B0+offset, 0);
		pScope->AddTrace("RxDataRdyN",	27,		TRACE_MODE_DIGITAL,	1,	32,	0x1094+offset, 0,	0x10B4+offset, 0);
		pScope->AddTrace("RxDataErr",		27,		TRACE_MODE_DIGITAL,	1,	33,	0x1094+offset, 1,	0x10B4+offset, 1);
		pScope->AddTrace("RxFrameIndex",	4*2+8,	TRACE_MODE_DIGITAL,	2,	34,	0x1094+offset, 2,	0x10B4+offset, 2);
		pScope->AddTrace("Sync",			27,		TRACE_MODE_DIGITAL,	1,	36,	0x1094+offset, 4,	0x10B4+offset, 4);
	}
private:
};

#endif
