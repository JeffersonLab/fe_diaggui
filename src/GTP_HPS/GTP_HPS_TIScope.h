#ifndef GTP_HPS_TISCOPE_H
#define GTP_HPS_TISCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class GTP_HPS_TIScope	: public TGCompositeFrame
{
public:
	GTP_HPS_TIScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = 0x2500+pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		// void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x0084+offset, 0, 0x0080+offset, 0, 0x0090+offset, 1);

		// void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("TxCmd",			4*2+8,	TRACE_MODE_DIGITAL,	2,	0,		0x00A0+offset, 0,		0x00B0+offset, 0);
		pScope->AddTrace("TxData",			4*32+8,	TRACE_MODE_DIGITAL,	8,	2,		0x00A0+offset, 2,		0x00B0+offset, 2);
		pScope->AddTrace("RxCmd",			4*2+8,	TRACE_MODE_DIGITAL,	2,	10,	0x00A0+offset, 10,	0x00B0+offset, 10);
		pScope->AddTrace("RxData",			4*32+8,	TRACE_MODE_DIGITAL,	8,	12,	0x00A0+offset, 12,	0x00B0+offset, 12);
		pScope->AddTrace("SyncEvt",		27,		TRACE_MODE_DIGITAL,	1,	20,	0x00A0+offset, 20,	0x00B0+offset, 20);
		pScope->AddTrace("SyncEvtReset",	27,		TRACE_MODE_DIGITAL,	1,	21,	0x00A0+offset, 21,	0x00B0+offset, 21);
		pScope->AddTrace("BlockAck",		27,		TRACE_MODE_DIGITAL,	1,	22,	0x00A0+offset, 22,	0x00B0+offset, 22);
		pScope->AddTrace("BlockSizeReq",	27,		TRACE_MODE_DIGITAL,	1,	23,	0x00A0+offset, 23,	0x00B0+offset, 23);
	}
private:
};

#endif
