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
		pScope->AddTrace("Energy",				4*13+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	13,	0,		0x2490+offset, 0,		0x24B0+offset, 0, 36);
		pScope->AddTrace("X",					4*6+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	6,		13,	0x2490+offset, 13,	0x24B0+offset, 13, 36);
		pScope->AddTrace("Y",					4*3+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	3,		19,	0x2490+offset, 19,	0x24B0+offset, 19, 36);
		pScope->AddTrace("Time",				4*10+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	10,	22,	0x2490+offset, 22,	0x24B0+offset, 22, 36);
		pScope->AddTrace("NHits",				4*4+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	4,		32,	0x2494+offset, 0,		0x24B4+offset, 0, 36);
		pScope->AddTrace("ClusterValid",		27,			TRACE_MODE_DIGITAL,							1,		36,	0x2494+offset, 4,		0x24B4+offset, 4);
		pScope->AddTrace("ScintTime",			4*10+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	10,	37,	0x2494+offset, 5,		0x24B4+offset, 5, 50);
 		pScope->AddTrace("ScintData",			4*3+8,		TRACE_MODE_DIGITAL | TRACE_MODE_MASK0,	3,		47,	0x2494+offset, 15,	0x24B4+offset, 15, 50);
 		pScope->AddTrace("ScintValid",		27,			TRACE_MODE_DIGITAL						,	1,		50,	0x2494+offset, 18,	0x24B4+offset, 18, 50);

//		pScope->AddTrace("TxDataL",			4*32+8,		TRACE_MODE_DIGITAL,	32,	0,		0x2490+offset, 0,	0x24B0+offset, 0);
//		pScope->AddTrace("TxDataH",			4*32+8,		TRACE_MODE_DIGITAL,	32,	32,	0x2494+offset, 0,	0x24B4+offset, 0);
		pScope->AddTrace("TxDataRdyN",		27,			TRACE_MODE_DIGITAL,	1,		64,	0x2498+offset, 0,	0x24B8+offset, 0);
		pScope->AddTrace("TRxFrameIndex",	4*2+8,		TRACE_MODE_DIGITAL,	2,		65,	0x2498+offset, 1,	0x24B8+offset, 1);
	}
private:
};

#endif
