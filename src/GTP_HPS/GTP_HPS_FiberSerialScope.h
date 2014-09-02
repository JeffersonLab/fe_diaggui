#ifndef GTP_HPS_FIBERSERIALSCOPE_H
#define GTP_HPS_FIBERSERIALSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class GTP_HPS_FiberSerialScope	: public TGCompositeFrame
{
public:
	GTP_HPS_FiberSerialScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		// void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x2424+offset, 0, 0x2420+offset, 0, 0x2430+offset, 3);

		// void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("Energy",				128,		TRACE_MODE_ANALOG | TRACE_MODE_MASK1,	13,	0,		0x2490+offset, 0,	0x24B0+offset, 0, 64);
		pScope->AddTrace("X",					128,		TRACE_MODE_ANALOG | TRACE_MODE_MASK1,	6,		13,	0x2490+offset, 0,	0x24B0+offset, 0, 64);
		pScope->AddTrace("Y",					128,		TRACE_MODE_ANALOG | TRACE_MODE_MASK1,	3,		19,	0x2490+offset, 0,	0x24B0+offset, 0, 64);
		pScope->AddTrace("Time",				128,		TRACE_MODE_ANALOG | TRACE_MODE_MASK1,	10,	22,	0x2490+offset, 0,	0x24B0+offset, 0, 64);
		pScope->AddTrace("NHits",				128,		TRACE_MODE_ANALOG | TRACE_MODE_MASK1,	4,		32,	0x2490+offset, 0,	0x24B0+offset, 0, 64);

		pScope->AddTrace("TxDataL",			4*32+8,	TRACE_MODE_DIGITAL,	32,	0,		0x2490+offset, 0,	0x24B0+offset, 0);
		pScope->AddTrace("TxDataH",			4*32+8,	TRACE_MODE_DIGITAL,	32,	32,	0x2494+offset, 0,	0x24B4+offset, 0);
		pScope->AddTrace("TxDataRdyN",		27,		TRACE_MODE_DIGITAL,	1,		64,	0x2498+offset, 0,	0x24B8+offset, 0);
		pScope->AddTrace("TRxFrameIndex",	4*2+8,	TRACE_MODE_DIGITAL,	2,		65,	0x2498+offset, 1,	0x24B8+offset, 1);
	}
private:
};

#endif
