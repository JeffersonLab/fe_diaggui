#ifndef DCRB_SCOPE_H
#define DCRB_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class DCRB_Scope	: public TGCompositeFrame
{
public:
	DCRB_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//    pScope->SetRegWidth(16);

		//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x0704+offset, 0, 0x0700+offset, 0, 0x0740+offset, 24);
			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("Ch0",		4*8+8,		TRACE_MODE_DIGITAL,	8,	  0,		0x0708 + offset, 0,	0x0714 + offset, 0);
		pScope->AddTrace("Ch1",		4*8+8,		TRACE_MODE_DIGITAL,	8,	  8,		0x0708 + offset, 1,	0x0714 + offset, 1);
		pScope->AddTrace("Ch2",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 16,		0x0708 + offset, 2,	0x0714 + offset, 2);
		pScope->AddTrace("Ch3",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 24,		0x0708 + offset, 3,	0x0714 + offset, 3);
		pScope->AddTrace("Ch4",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 32,		0x0708 + offset, 4,	0x0714 + offset, 4);
		pScope->AddTrace("Ch5",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 40,		0x0708 + offset, 5,	0x0714 + offset, 5);
		pScope->AddTrace("Ch6",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 48,		0x0708 + offset, 6,	0x0714 + offset, 6);
		pScope->AddTrace("Ch7",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 56,		0x0708 + offset, 7,	0x0714 + offset, 7);
  	pScope->AddTrace("Ch8",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 64,		0x0708 + offset, 8,	0x0714 + offset, 8);
		pScope->AddTrace("Ch9",		4*8+8,		TRACE_MODE_DIGITAL,	8,	 72,		0x0708 + offset, 9,	0x0714 + offset, 9);
		pScope->AddTrace("Ch10",	4*8+8,		TRACE_MODE_DIGITAL,	8,	 80,		0x0708 + offset,10,	0x0714 + offset,10);
		pScope->AddTrace("Ch11",	4*8+8,		TRACE_MODE_DIGITAL,	8,	 88,		0x0708 + offset,11,	0x0714 + offset,11);
		pScope->AddTrace("Ch12",	4*8+8,		TRACE_MODE_DIGITAL,	8,	 96,		0x0708 + offset,12,	0x0714 + offset,12);
		pScope->AddTrace("Ch13",	4*8+8,		TRACE_MODE_DIGITAL,	8,	104,		0x0708 + offset,13,	0x0714 + offset,13);
		pScope->AddTrace("Ch14",	4*8+8,		TRACE_MODE_DIGITAL,	8,	112,		0x0708 + offset,14,	0x0714 + offset,14);
		pScope->AddTrace("Ch15",	4*8+8,		TRACE_MODE_DIGITAL,	8,	120,		0x0708 + offset,15,	0x0714 + offset,15);
		pScope->AddTrace("Ch16",	4*8+8,		TRACE_MODE_DIGITAL,	8,	128,		0x0708 + offset,16,	0x0714 + offset,16);
		pScope->AddTrace("Ch17",	4*8+8,		TRACE_MODE_DIGITAL,	8,	136,		0x0708 + offset,17,	0x0714 + offset,17);
		pScope->AddTrace("Ch18",	4*8+8,		TRACE_MODE_DIGITAL,	8,	144,		0x0708 + offset,18,	0x0714 + offset,18);
		pScope->AddTrace("Ch19",	4*8+8,		TRACE_MODE_DIGITAL,	8,	152,		0x0708 + offset,19,	0x0714 + offset,19);
		pScope->AddTrace("Ch20",	4*8+8,		TRACE_MODE_DIGITAL,	8,	160,		0x0708 + offset,20,	0x0714 + offset,20);
		pScope->AddTrace("Ch21",	4*8+8,		TRACE_MODE_DIGITAL,	8,	168,		0x0708 + offset,21,	0x0714 + offset,21);
		pScope->AddTrace("Ch22",	4*8+8,		TRACE_MODE_DIGITAL,	8,	176,		0x0708 + offset,22,	0x0714 + offset,22);
		pScope->AddTrace("Ch23",	4*8+8,		TRACE_MODE_DIGITAL,	8,	184,		0x0708 + offset,23,	0x0714 + offset,23);
  	pScope->AddTrace("Ch24",	4*8+8,		TRACE_MODE_DIGITAL,	8,	192,		0x0708 + offset,24,	0x0714 + offset,24);
		pScope->AddTrace("Ch25",	4*8+8,		TRACE_MODE_DIGITAL,	8,	200,		0x0708 + offset,25,	0x0714 + offset,25);
		pScope->AddTrace("Ch26",	4*8+8,		TRACE_MODE_DIGITAL,	8,	208,		0x0708 + offset,26,	0x0714 + offset,26);
		pScope->AddTrace("Ch27",	4*8+8,		TRACE_MODE_DIGITAL,	8,	216,		0x0708 + offset,27,	0x0714 + offset,27);
		pScope->AddTrace("Ch28",	4*8+8,		TRACE_MODE_DIGITAL,	8,	224,		0x0708 + offset,28,	0x0714 + offset,28);
		pScope->AddTrace("Ch29",	4*8+8,		TRACE_MODE_DIGITAL,	8,	232,		0x0708 + offset,29,	0x0714 + offset,29);
		pScope->AddTrace("Ch30",	4*8+8,		TRACE_MODE_DIGITAL,	8,	240,		0x0708 + offset,30,	0x0714 + offset,30);
		pScope->AddTrace("Ch31",	4*8+8,		TRACE_MODE_DIGITAL,	8,	248,		0x0708 + offset,31,	0x0714 + offset,31);
		pScope->AddTrace("Ch32",	4*8+8,		TRACE_MODE_DIGITAL,	8,	256,		0x070C + offset, 0,	0x0718 + offset, 0);
		pScope->AddTrace("Ch33",	4*8+8,		TRACE_MODE_DIGITAL,	8,	264,		0x070C + offset, 1,	0x0718 + offset, 1);
		pScope->AddTrace("Ch34",	4*8+8,		TRACE_MODE_DIGITAL,	8,	272,		0x070C + offset, 2,	0x0718 + offset, 2);
		pScope->AddTrace("Ch35",	4*8+8,		TRACE_MODE_DIGITAL,	8,	280,		0x070C + offset, 3,	0x0718 + offset, 3);
		pScope->AddTrace("Ch36",	4*8+8,		TRACE_MODE_DIGITAL,	8,	288,		0x070C + offset, 4,	0x0718 + offset, 4);
		pScope->AddTrace("Ch37",	4*8+8,		TRACE_MODE_DIGITAL,	8,	296,		0x070C + offset, 5,	0x0718 + offset, 5);
		pScope->AddTrace("Ch38",	4*8+8,		TRACE_MODE_DIGITAL,	8,	304,		0x070C + offset, 6,	0x0718 + offset, 6);
		pScope->AddTrace("Ch39",	4*8+8,		TRACE_MODE_DIGITAL,	8,	312,		0x070C + offset, 7,	0x0718 + offset, 7);
  	pScope->AddTrace("Ch40",	4*8+8,		TRACE_MODE_DIGITAL,	8,	320,		0x070C + offset, 8,	0x0718 + offset, 8);
		pScope->AddTrace("Ch41",	4*8+8,		TRACE_MODE_DIGITAL,	8,	328,		0x070C + offset, 9,	0x0718 + offset, 9);
		pScope->AddTrace("Ch42",	4*8+8,		TRACE_MODE_DIGITAL,	8,	336,		0x070C + offset,10,	0x0718 + offset,10);
		pScope->AddTrace("Ch43",	4*8+8,		TRACE_MODE_DIGITAL,	8,	344,		0x070C + offset,11,	0x0718 + offset,11);
		pScope->AddTrace("Ch44",	4*8+8,		TRACE_MODE_DIGITAL,	8,	352,		0x070C + offset,12,	0x0718 + offset,12);
		pScope->AddTrace("Ch45",	4*8+8,		TRACE_MODE_DIGITAL,	8,	360,		0x070C + offset,13,	0x0718 + offset,13);
		pScope->AddTrace("Ch46",	4*8+8,		TRACE_MODE_DIGITAL,	8,	368,		0x070C + offset,14,	0x0718 + offset,14);
		pScope->AddTrace("Ch47",	4*8+8,		TRACE_MODE_DIGITAL,	8,	376,		0x070C + offset,15,	0x0718 + offset,15);
		pScope->AddTrace("Ch48",	4*8+8,		TRACE_MODE_DIGITAL,	8,	384,		0x070C + offset,16,	0x0718 + offset,16);
		pScope->AddTrace("Ch49",	4*8+8,		TRACE_MODE_DIGITAL,	8,	392,		0x070C + offset,17,	0x0718 + offset,17);
		pScope->AddTrace("Ch50",	4*8+8,		TRACE_MODE_DIGITAL,	8,	400,		0x070C + offset,18,	0x0718 + offset,18);
		pScope->AddTrace("Ch51",	4*8+8,		TRACE_MODE_DIGITAL,	8,	408,		0x070C + offset,19,	0x0718 + offset,19);
		pScope->AddTrace("Ch52",	4*8+8,		TRACE_MODE_DIGITAL,	8,	416,		0x070C + offset,20,	0x0718 + offset,20);
		pScope->AddTrace("Ch53",	4*8+8,		TRACE_MODE_DIGITAL,	8,	424,		0x070C + offset,21,	0x0718 + offset,21);
		pScope->AddTrace("Ch54",	4*8+8,		TRACE_MODE_DIGITAL,	8,	432,		0x070C + offset,22,	0x0718 + offset,22);
		pScope->AddTrace("Ch55",	4*8+8,		TRACE_MODE_DIGITAL,	8,	440,		0x070C + offset,23,	0x0718 + offset,23);
  	pScope->AddTrace("Ch56",	4*8+8,		TRACE_MODE_DIGITAL,	8,	448,		0x070C + offset,24,	0x0718 + offset,24);
		pScope->AddTrace("Ch57",	4*8+8,		TRACE_MODE_DIGITAL,	8,	456,		0x070C + offset,25,	0x0718 + offset,25);
		pScope->AddTrace("Ch58",	4*8+8,		TRACE_MODE_DIGITAL,	8,	464,		0x070C + offset,26,	0x0718 + offset,26);
		pScope->AddTrace("Ch59",	4*8+8,		TRACE_MODE_DIGITAL,	8,	472,		0x070C + offset,27,	0x0718 + offset,27);
		pScope->AddTrace("Ch60",	4*8+8,		TRACE_MODE_DIGITAL,	8,	480,		0x070C + offset,28,	0x0718 + offset,28);
		pScope->AddTrace("Ch61",	4*8+8,		TRACE_MODE_DIGITAL,	8,	488,		0x070C + offset,29,	0x0718 + offset,29);
		pScope->AddTrace("Ch62",	4*8+8,		TRACE_MODE_DIGITAL,	8,	496,		0x070C + offset,30,	0x0718 + offset,30);
		pScope->AddTrace("Ch63",	4*8+8,		TRACE_MODE_DIGITAL,	8,	504,		0x070C + offset,31,	0x0718 + offset,31);
	}
};

#endif


