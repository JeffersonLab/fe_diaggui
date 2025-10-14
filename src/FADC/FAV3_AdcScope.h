#ifndef FAV3_ADCSCOPE_H
#define FAV3_ADCSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class FAV3_AdcScope	: public TGCompositeFrame
{
public:
	FAV3_AdcScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		pScope->SetRegWidth(16);

		//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x01AA+offset, 0, 0x01AC+offset, 0, 0x0210+offset, 13);
			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("Ch0",		128,		TRACE_MODE_ANALOG,	13,	  0,		0x01AE + offset, 0,	0x01CE + offset, 0);
		pScope->AddTrace("Ch1",		128,		TRACE_MODE_ANALOG,	13,	 13,		0x01B0 + offset, 0,	0x01D0 + offset, 0);
		pScope->AddTrace("Ch2",		128,		TRACE_MODE_ANALOG,	13,	 26,		0x01B2 + offset, 0,	0x01D2 + offset, 0);
		pScope->AddTrace("Ch3",		128,		TRACE_MODE_ANALOG,	13,	 39,		0x01B4 + offset, 0,	0x01D4 + offset, 0);
		pScope->AddTrace("Ch4",		128,		TRACE_MODE_ANALOG,	13,	 52,		0x01B6 + offset, 0,	0x01D6 + offset, 0);
		pScope->AddTrace("Ch5",		128,		TRACE_MODE_ANALOG,	13,	 65,		0x01B8 + offset, 0,	0x01D8 + offset, 0);
		pScope->AddTrace("Ch6",		128,		TRACE_MODE_ANALOG,	13,	 78,		0x01BA + offset, 0,	0x01DA + offset, 0);
		pScope->AddTrace("Ch7",		128,		TRACE_MODE_ANALOG,	13,	 91,		0x01BC + offset, 0,	0x01DC + offset, 0);
		pScope->AddTrace("Ch8",		128,		TRACE_MODE_ANALOG,	13,	104,		0x01BE + offset, 0,	0x01DE + offset, 0);
		pScope->AddTrace("Ch9",		128,		TRACE_MODE_ANALOG,	13,	117,		0x01C0 + offset, 0,	0x01E0 + offset, 0);
		pScope->AddTrace("Ch10",	128,		TRACE_MODE_ANALOG,	13,	130,		0x01C2 + offset, 0,	0x01E2 + offset, 0);
		pScope->AddTrace("Ch11",	128,		TRACE_MODE_ANALOG,	13,	143,		0x01C4 + offset, 0,	0x01E4 + offset, 0);
		pScope->AddTrace("Ch12",	128,		TRACE_MODE_ANALOG,	13,	156,		0x01C6 + offset, 0,	0x01E6 + offset, 0);
		pScope->AddTrace("Ch13",	128,		TRACE_MODE_ANALOG,	13,	169,		0x01C8 + offset, 0,	0x01E8 + offset, 0);
		pScope->AddTrace("Ch14",	128,		TRACE_MODE_ANALOG,	13,	182,		0x01CA + offset, 0,	0x01EA + offset, 0);
		pScope->AddTrace("Ch15",	128,		TRACE_MODE_ANALOG,	13,	195,		0x01CC + offset, 0,	0x01EC + offset, 0);
	}
};

#endif
