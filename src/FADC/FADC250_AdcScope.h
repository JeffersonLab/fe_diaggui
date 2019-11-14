#ifndef FADC250_ADCSCOPE_H
#define FADC250_ADCSCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class FADC250_AdcScope	: public TGCompositeFrame
{
public:
	FADC250_AdcScope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Scope *pScope;
		int offset = pModule->BaseAddr;

		AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    pScope->SetRegWidth(16);

		//		void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
		pScope->Init(512, 0x0202+offset, 0, 0x0200+offset, 0, 0x02C0+offset, 13);
			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("Ch0",		128,		TRACE_MODE_ANALOG,	13,	  0,		0x0220 + offset, 0,	0x0240 + offset, 0);
		pScope->AddTrace("Ch1",		128,		TRACE_MODE_ANALOG,	13,	 13,		0x0222 + offset, 0,	0x0242 + offset, 0);
		pScope->AddTrace("Ch2",		128,		TRACE_MODE_ANALOG,	13,	 26,		0x0224 + offset, 0,	0x0244 + offset, 0);
		pScope->AddTrace("Ch3",		128,		TRACE_MODE_ANALOG,	13,	 39,		0x0226 + offset, 0,	0x0246 + offset, 0);
		pScope->AddTrace("Ch4",		128,		TRACE_MODE_ANALOG,	13,	 52,		0x0228 + offset, 0,	0x0248 + offset, 0);
		pScope->AddTrace("Ch5",		128,		TRACE_MODE_ANALOG,	13,	 65,		0x022A + offset, 0,	0x024A + offset, 0);
		pScope->AddTrace("Ch6",		128,		TRACE_MODE_ANALOG,	13,	 78,		0x022C + offset, 0,	0x024C + offset, 0);
		pScope->AddTrace("Ch7",		128,		TRACE_MODE_ANALOG,	13,	 91,		0x022E + offset, 0,	0x024E + offset, 0);
		pScope->AddTrace("Ch8",		128,		TRACE_MODE_ANALOG,	13,	104,		0x0230 + offset, 0,	0x0250 + offset, 0);
		pScope->AddTrace("Ch9",		128,		TRACE_MODE_ANALOG,	13,	117,		0x0232 + offset, 0,	0x0252 + offset, 0);
		pScope->AddTrace("Ch10",	128,		TRACE_MODE_ANALOG,	13,	130,		0x0234 + offset, 0,	0x0254 + offset, 0);
		pScope->AddTrace("Ch11",	128,		TRACE_MODE_ANALOG,	13,	143,		0x0236 + offset, 0,	0x0256 + offset, 0);
		pScope->AddTrace("Ch12",	128,		TRACE_MODE_ANALOG,	13,	156,		0x0238 + offset, 0,	0x0258 + offset, 0);
		pScope->AddTrace("Ch13",	128,		TRACE_MODE_ANALOG,	13,	169,		0x023A + offset, 0,	0x025A + offset, 0);
		pScope->AddTrace("Ch14",	128,		TRACE_MODE_ANALOG,	13,	182,		0x023C + offset, 0,	0x025C + offset, 0);
		pScope->AddTrace("Ch15",	128,		TRACE_MODE_ANALOG,	13,	195,		0x023E + offset, 0,	0x025E + offset, 0);
	}
};

#endif


