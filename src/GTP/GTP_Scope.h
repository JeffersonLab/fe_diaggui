#ifndef GTP_SCOPE_H
#define GTP_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"
#include "gtp.h"

class GTP_Scope	: public TGCompositeFrame
{
public:
	GTP_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		// void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x0404+offset, 0, 0x0400+offset, 0, 0x0420+offset, 7);

		// void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("BCalEnergy",		128,		TRACE_MODE_ANALOG,	16,	0,		0x0440+offset, 0,		0x0460+offset, 0);
		pScope->AddTrace("BCalCosmic",		27,		TRACE_MODE_DIGITAL,	1,		16,	0x049C+offset, 0,		0x04BC+offset, 0);
		pScope->AddTrace("BCalCosmicHits",	4*16+8,	TRACE_MODE_DIGITAL,	16,	17,	0x049C+offset, 1,		0x04BC+offset, 1);
		pScope->AddTrace("FCalEnergy",		128,		TRACE_MODE_ANALOG,	16,	33,	0x0444+offset, 0,		0x0464+offset, 0);
		pScope->AddTrace("TagM",				4*32+8,	TRACE_MODE_DIGITAL,	32,	49,	0x0480+offset, 0,		0x04A0+offset, 0);
		pScope->AddTrace("TagH",				4*32+8,	TRACE_MODE_DIGITAL,	32,	81,	0x0484+offset, 0,		0x04A4+offset, 0);
		pScope->AddTrace("PS",					4*16+8,	TRACE_MODE_DIGITAL,	16,	113,	0x0488+offset, 0,		0x04A8+offset, 0);
		pScope->AddTrace("ST",					4*30+8,	TRACE_MODE_DIGITAL,	30,	129,	0x048C+offset, 0,		0x04AC+offset, 0);
		pScope->AddTrace("TOF",					4*32+8,	TRACE_MODE_DIGITAL,	32,	159,	0x0490+offset, 0,		0x04B0+offset, 0);
		pScope->AddTrace("Ready",				27,		TRACE_MODE_DIGITAL,	1,		191,	0x0494+offset, 0,		0x04B4+offset, 0);
		pScope->AddTrace("Trigbit0",			27,		TRACE_MODE_DIGITAL,	1,		192,	0x0498+offset, 0,		0x04B8+offset, 0);
		pScope->AddTrace("Trigbit1",			27,		TRACE_MODE_DIGITAL,	1,		193,	0x0498+offset, 1,		0x04B8+offset, 1);
		pScope->AddTrace("Trigbit2",			27,		TRACE_MODE_DIGITAL,	1,		194,	0x0498+offset, 2,		0x04B8+offset, 2);
		pScope->AddTrace("Trigbit3",			27,		TRACE_MODE_DIGITAL,	1,		195,	0x0498+offset, 3,		0x04B8+offset, 3);
		pScope->AddTrace("Trigbit4",			27,		TRACE_MODE_DIGITAL,	1,		196,	0x0498+offset, 4,		0x04B8+offset, 4);
		pScope->AddTrace("Trigbit5",			27,		TRACE_MODE_DIGITAL,	1,		197,	0x0498+offset, 5,		0x04B8+offset, 5);
		pScope->AddTrace("Trigbit6",			27,		TRACE_MODE_DIGITAL,	1,		198,	0x0498+offset, 6,		0x04B8+offset, 6);
		pScope->AddTrace("Trigbit7",			27,		TRACE_MODE_DIGITAL,	1,		199,	0x0498+offset, 7,		0x04B8+offset, 7);
		pScope->AddTrace("Trigbit8",			27,		TRACE_MODE_DIGITAL,	1,		200,	0x0498+offset, 8,		0x04B8+offset, 8);
		pScope->AddTrace("Trigbit9",			27,		TRACE_MODE_DIGITAL,	1,		201,	0x0498+offset, 9,		0x04B8+offset, 9);
		pScope->AddTrace("Trigbit10",			27,		TRACE_MODE_DIGITAL,	1,		202,	0x0498+offset, 10,	0x04B8+offset, 10);
		pScope->AddTrace("Trigbit11",			27,		TRACE_MODE_DIGITAL,	1,		203,	0x0498+offset, 11,	0x04B8+offset, 11);
		pScope->AddTrace("Trigbit12",			27,		TRACE_MODE_DIGITAL,	1,		204,	0x0498+offset, 12,	0x04B8+offset, 12);
		pScope->AddTrace("Trigbit13",			27,		TRACE_MODE_DIGITAL,	1,		205,	0x0498+offset, 13,	0x04B8+offset, 13);
		pScope->AddTrace("Trigbit14",			27,		TRACE_MODE_DIGITAL,	1,		206,	0x0498+offset, 14,	0x04B8+offset, 14);
		pScope->AddTrace("Trigbit15",			27,		TRACE_MODE_DIGITAL,	1,		207,	0x0498+offset, 15,	0x04B8+offset, 15);
	}
};

#endif
