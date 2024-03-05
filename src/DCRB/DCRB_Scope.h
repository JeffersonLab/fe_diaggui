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
		pScope->Init(512, 0x1014+offset, 0, 0x1010+offset, 0, 0x1020+offset, 1);
			//		void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
		pScope->AddTrace("STATUS",		128,		TRACE_MODE_ANALOG,	32,	  0,		0x1018 + offset, 0,	0x101C + offset, 0);
	}
};

#endif


