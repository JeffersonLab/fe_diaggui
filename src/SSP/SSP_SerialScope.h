#ifndef SSP_SERIALSCOPE_H
#define SSP_SERIALSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class SSP_SerialScope	: public TGCompositeFrame
{
public:
	SSP_SerialScope(const TGWindow *p, ModuleFrame *pModule, int idx) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = idx*0x100+pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		if(idx < 8)
		{
			//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
			pScope->Init(512, 0x1044+offset, 0, 0x1040+offset, 0, 0x1050+offset, 3);

			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
			pScope->AddTrace("RxDataL",			128,		TRACE_MODE_ANALOG,	20,	0,		0x1070+offset, 0,	0x1090+offset, 0);
			pScope->AddTrace("RxDataH",			128,		TRACE_MODE_ANALOG,	20,	32,	0x1070+offset, 0,	0x1090+offset, 0);
			pScope->AddTrace("RxDataL",			4*32+8,	TRACE_MODE_DIGITAL,	32,	0,		0x10B0+offset, 0,	0x10D0+offset, 0);
			pScope->AddTrace("RxDataH",			4*32+8,	TRACE_MODE_DIGITAL,	32,	32,	0x10B0+offset, 0,	0x10D0+offset, 0);
			pScope->AddTrace("RxDataRdyN",		27,		TRACE_MODE_DIGITAL,	1,		64,	0x10B4+offset, 0,	0x10D4+offset, 0);
			pScope->AddTrace("RxFrameIndex",		4*2+8,	TRACE_MODE_DIGITAL,	2,		65,	0x10B4+offset, 1,	0x10D4+offset, 1);
			pScope->AddTrace("RxDataErr",			27,		TRACE_MODE_DIGITAL,	1,		67,	0x10B4+offset, 3,	0x10D4+offset, 3);
			pScope->AddTrace("Sync",				27,		TRACE_MODE_DIGITAL,	1,		68,	0x10B4+offset, 4,	0x10D4+offset, 4);
		}
		else if(idx == 9)
		{
			//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
			pScope->Init(512, 0x1044+offset, 0, 0x1030+offset, 0, 0x1040+offset, 3);

			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
			pScope->AddTrace("RxData",			128,	TRACE_MODE_ANALOG,	32,	0,	0x1060+offset, 0,	0x1080+offset, 0);
			pScope->AddTrace("RxData",			4*32+8,	TRACE_MODE_DIGITAL,	32,	0,	0x10A0+offset, 0,	0x10C0+offset, 0);
			pScope->AddTrace("RxDataRdyN",		27,		TRACE_MODE_DIGITAL,	1,	32,	0x10A4+offset, 0,	0x10C4+offset, 0);
			pScope->AddTrace("RxFrameIndex",	4*2+8,	TRACE_MODE_DIGITAL,	2,	33,	0x10A4+offset, 1,	0x10C4+offset, 1);
		}
	}
};

#endif

