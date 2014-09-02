#ifndef GTP_SCOPE_H
#define GTP_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"
#include "gtp.h"

/*
ScopeTraceDesc pGtpScopeTraces[] = {
		// name, height, mode, bitCount, bitOffsetData, {mode.mode, mode.addr, mode.bitOffset}, {val.val, val.addr, val.bitOffset}
		{"I(BCALEnergy)",	128,		TRACE_MODE_ANALOG,	23,	0,	{0, 0x0440, 0},	{0, 0x0460, 0}},
		{"I(BCALHits)",	128,		TRACE_MODE_ANALOG,	4,		0,	{0, 0x0444, 0},	{0, 0x0464, 0}},
		{"I(FCALEnergy)",	128,		TRACE_MODE_ANALOG,	23,	0,	{0, 0x0448, 0},	{0, 0x0468, 0}},
		{"TAGM",				4*32+3,	TRACE_MODE_DIGITAL,	32,	0,	{0, 0x0480, 0},	{0, 0x04A0, 0}},
		{"TAGH",				4*32+3,	TRACE_MODE_DIGITAL,	32,	0,	{0, 0x0484, 0},	{0, 0x04A4, 0}},
		{"PS",				4*16+3,	TRACE_MODE_DIGITAL,	16,	0,	{0, 0x0488, 0},	{0, 0x04A8, 0}},
		{"ST",				4*30+3,	TRACE_MODE_DIGITAL,	30,	0,	{0, 0x048C, 0},	{0, 0x04AC, 0}},
		{"TOFV",				4*16+3,	TRACE_MODE_DIGITAL,	16,	0,	{0, 0x0490, 0},	{0, 0x04B0, 0}},
		{"TOFH",				4*16+3,	TRACE_MODE_DIGITAL,	16,	0,	{0, 0x0490, 16},	{0, 0x04B0, 16}},
		{"RDY",				27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0494, 0},	{0, 0x04B4, 0}},
		{"TRIGOUT0",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 0},	{0, 0x04B8, 0}},
		{"TRIGOUT1",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 1},	{0, 0x04B8, 1}},
		{"TRIGOUT2",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 2},	{0, 0x04B8, 2}},
		{"TRIGOUT3",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 3},	{0, 0x04B8, 3}},
		{"TRIGOUT4",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 4},	{0, 0x04B8, 4}},
		{"TRIGOUT5",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 5},	{0, 0x04B8, 5}},
		{"TRIGOUT6",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 6},	{0, 0x04B8, 6}},
		{"TRIGOUT7",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 7},	{0, 0x04B8, 7}},
		{"TRIGOUT8",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 8},	{0, 0x04B8, 8}},
		{"TRIGOUT9",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 9},	{0, 0x04B8, 9}},
		{"TRIGOUT10",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 10},	{0, 0x04B8, 10}},
		{"TRIGOUT11",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 11},	{0, 0x04B8, 11}},
		{"TRIGOUT12",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 12},	{0, 0x04B8, 12}},
		{"TRIGOUT13",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 13},	{0, 0x04B8, 13}},
		{"TRIGOUT14",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 14},	{0, 0x04B8, 14}},
		{"TRIGOUT15",		27,		TRACE_MODE_DIGITAL,	1,		0,	{0, 0x0498, 15},	{0, 0x04B8, 15}},
	};

int pGtpScopeDataRegs[] = {0x0420, 0x0424, 0x0428, 0x042C, 0x0430, 0x0434, 0x0438};

ScopeDesc GtpScopeDesc = {
		512,
		{0x0404, 0},
		{0x0400, 0},
		{sizeof(pGtpScopeDataRegs)/sizeof(pGtpScopeDataRegs[0]),	pGtpScopeDataRegs},
		{sizeof(pGtpScopeTraces)/sizeof(pGtpScopeTraces[0]),pGtpScopeTraces}
	};
*/

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
		pScope->AddTrace("BCalEnergy",		128,	TRACE_MODE_ANALOG,	23,	0,		0x0440+offset, 0,	0x0460+offset, 0);
		pScope->AddTrace("BCalHitModules",	128,	TRACE_MODE_ANALOG,	4,	23,		0x0444+offset, 0,	0x0464+offset, 0);
		pScope->AddTrace("FCalEnergy",		128,	TRACE_MODE_ANALOG,	23,	27,		0x0448+offset, 0,	0x0468+offset, 0);
		pScope->AddTrace("TagM",			4*32+8,	TRACE_MODE_DIGITAL,	32,	50,		0x0480+offset, 0,	0x04A0+offset, 0);
		pScope->AddTrace("TagH",			4*32+8,	TRACE_MODE_DIGITAL,	32,	82,		0x0484+offset, 0,	0x04A4+offset, 0);
		pScope->AddTrace("PS",				4*16+8,	TRACE_MODE_DIGITAL,	16,	114,	0x0488+offset, 0,	0x04A8+offset, 0);
		pScope->AddTrace("ST",				4*30+8,	TRACE_MODE_DIGITAL,	30,	130,	0x048C+offset, 0,	0x04AC+offset, 0);
		pScope->AddTrace("TOF",				4*32+8,	TRACE_MODE_DIGITAL,	32,	160,	0x0490+offset, 0,	0x04B0+offset, 0);
		pScope->AddTrace("Ready",			27,		TRACE_MODE_DIGITAL,	1,	192,	0x0494+offset, 0,	0x04B4+offset, 0);
		pScope->AddTrace("Trigbit0",		27,		TRACE_MODE_DIGITAL,	1,	193,	0x0498+offset, 0,	0x04B8+offset, 0);
		pScope->AddTrace("Trigbit1",		27,		TRACE_MODE_DIGITAL,	1,	194,	0x0498+offset, 1,	0x04B8+offset, 1);
		pScope->AddTrace("Trigbit2",		27,		TRACE_MODE_DIGITAL,	1,	195,	0x0498+offset, 2,	0x04B8+offset, 2);
		pScope->AddTrace("Trigbit3",		27,		TRACE_MODE_DIGITAL,	1,	196,	0x0498+offset, 3,	0x04B8+offset, 3);
		pScope->AddTrace("Trigbit4",		27,		TRACE_MODE_DIGITAL,	1,	197,	0x0498+offset, 4,	0x04B8+offset, 4);
		pScope->AddTrace("Trigbit5",		27,		TRACE_MODE_DIGITAL,	1,	198,	0x0498+offset, 5,	0x04B8+offset, 5);
		pScope->AddTrace("Trigbit6",		27,		TRACE_MODE_DIGITAL,	1,	199,	0x0498+offset, 6,	0x04B8+offset, 6);
		pScope->AddTrace("Trigbit7",		27,		TRACE_MODE_DIGITAL,	1,	200,	0x0498+offset, 7,	0x04B8+offset, 7);
		pScope->AddTrace("Trigbit8",		27,		TRACE_MODE_DIGITAL,	1,	201,	0x0498+offset, 8,	0x04B8+offset, 8);
		pScope->AddTrace("Trigbit9",		27,		TRACE_MODE_DIGITAL,	1,	202,	0x0498+offset, 9,	0x04B8+offset, 9);
		pScope->AddTrace("Trigbit10",		27,		TRACE_MODE_DIGITAL,	1,	203,	0x0498+offset, 10,	0x04B8+offset, 10);
		pScope->AddTrace("Trigbit11",		27,		TRACE_MODE_DIGITAL,	1,	204,	0x0498+offset, 11,	0x04B8+offset, 11);
		pScope->AddTrace("Trigbit12",		27,		TRACE_MODE_DIGITAL,	1,	205,	0x0498+offset, 12,	0x04B8+offset, 12);
		pScope->AddTrace("Trigbit13",		27,		TRACE_MODE_DIGITAL,	1,	206,	0x0498+offset, 13,	0x04B8+offset, 13);
		pScope->AddTrace("Trigbit14",		27,		TRACE_MODE_DIGITAL,	1,	207,	0x0498+offset, 14,	0x04B8+offset, 14);
		pScope->AddTrace("Trigbit15",		27,		TRACE_MODE_DIGITAL,	1,	208,	0x0498+offset, 15,	0x04B8+offset, 15);
	}
};

#endif
