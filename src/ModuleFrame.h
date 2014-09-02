#ifndef ModuleFrame_H
#define ModuleFrame_H

#include <vector>
#include <list>
#include "RootHeader.h"
#include "CrateMsgClient.h"
#include "RegEditor.h"

#ifndef WIN32
	#define stricmp strcasecmp
#endif

using namespace std;

#define MSG_TAB_ACTIVATE		40020

#define SPFREG(BUF,PTR,REG)				\
  {							\
    sprintf(BUF,"%-35.35s = 0x%08X",#REG,pM->ReadReg32(PTR->REG));	\
  }

#define SPFREG_HEX(PTR,REG)	pT->AddText(new TGText(Form("%-35.35s = 0x%08X",#REG,pM->ReadReg32(PTR->REG))))
#define SPFREG_N_HEX(PTR,REG,n)	pT->AddText(new TGText(Form("%-35.35s = 0x%08X",Form("%s[%d]",#REG,n),pM->ReadReg32(PTR->REG[n]))))
#define SPFBASE_N_REG_HEX(PTR,BASE,n,REG)	pT->AddText(new TGText(Form("%-35.35s = 0x%08X",Form("%s[%d].%s",#BASE,n,#REG),pM->ReadReg32(PTR->BASE[n].REG))))
#define SPFBASE_N_REG_N_HEX(PTR,BASE,m,REG,n)	pT->AddText(new TGText(Form("%-35.35s = 0x%08X",Form("%s[%d].%s[%d]",#BASE,m,#REG,n),pM->ReadReg32(PTR->BASE[m].REG[n]))))

typedef struct
{
	unsigned int Len;
	unsigned int *pEventData;
} EventData;

class ModuleFrame : public TGCompositeFrame
{
private:
public:
	ModuleFrame(const TGWindow *p, CrateMsgClient *pClient, unsigned int baseAddr)	: TGCompositeFrame(p, 10, 10), pCrateMsgClient(pClient), BaseAddr(baseAddr)
	{
		SetLayoutManager(new TGHorizontalLayout(this));

		AddFrame(pRegEditor = new RegEditor(this, pClient, baseAddr), new TGLayoutHints(kLHintsExpandY));

		CurrentDisplayEvent = -1;
		LastDrawnDisplayEvent = -1;
		Active = kFALSE;
		SlotId = 0;
		EventBufferMax = 25;
	}

	void Delay(unsigned int ms)
	{
		pCrateMsgClient->Delay(ms);
	}

	const char *GetName()
	{
		return pCrateMsgClient->GetName();
	}

	Bool_t BlkReadReg32(volatile unsigned int *p, unsigned int *val, int cnt = 1, int flags = 0)
	{
		unsigned long addr = (unsigned long)p;
		return pCrateMsgClient->Read32((unsigned int)addr, val, cnt, flags);
	}

	unsigned int ReadReg32(volatile unsigned int *p)
	{
		unsigned int val = 0xFFFFFFFF;
		unsigned long addr = (unsigned long)p;
		pCrateMsgClient->Read32((unsigned int)addr, &val);
		return val;
	}

	void WriteReg32(volatile unsigned int *p, unsigned int val)
	{
		unsigned long addr = (unsigned long)p;
		pCrateMsgClient->Write32((unsigned int)addr, &val);
	}

	void RMWReg32(volatile unsigned int *p, unsigned int val, unsigned int mask)
	{
		WriteReg32(p, (ReadReg32(p) & ~mask) | (val & mask));
	}

	unsigned short ReadReg16(volatile unsigned int *p)
	{
		unsigned short val = 0xFFFF;
		unsigned long addr = (unsigned long)p;
		pCrateMsgClient->Read16((unsigned int)addr, &val);
		return val;
	}

	void WriteReg16(volatile unsigned int *p, unsigned short val)
	{
		unsigned long addr = (unsigned long)p;
		pCrateMsgClient->Write16((unsigned int)addr, &val);
	}

	void SetActive(Bool_t active)
	{
		Active = active;
	}

	void SetNextDisplayEvent()
	{
		if(CurrentDisplayEvent + 1 < (int)EventDataFIFO.size())
		{
			CurrentDisplayEvent++;
			DrawNewEvent();
		}
	}

	void SetPrevDisplayEvent()
	{
		if(CurrentDisplayEvent > 0)
		{
			CurrentDisplayEvent--;
			DrawNewEvent();
		}
	}

	EventData GetCurrentEvent()
	{
		EventData evt;
		evt.Len = 0;
		evt.pEventData = NULL;

		if(EventDataFIFO.size() <= 0)
			return evt;

		list<EventData>::iterator p = EventDataFIFO.begin();
		for(int i = 0; i < CurrentDisplayEvent; i++)
		{
			if(p == EventDataFIFO.end())
				break;
			p++;
		}
		return *p;
	}

	virtual const char *GetSlotIdentifier() { return "default"; }
	virtual void DrawNewEvent() {};
	virtual Bool_t SetParameter(char *pParam1, char *pParam2) { return kFALSE; }
	virtual const char *GetModuleName() { return "default"; }
	virtual const char *GetModuleFullName() { return "default"; }
	virtual Bool_t ProcessEventData(unsigned int *pBlockEventData, int len) { delete pBlockEventData; return kTRUE; }
	virtual void SetDisplayEvent(int index) { CurrentDisplayEvent = index; }
	virtual void ClearEvents(Bool_t bClearAll = kFALSE)
	{
		CurrentDisplayEvent = -1;
		list<EventData>::iterator p = EventDataFIFO.begin();
		while(p != EventDataFIFO.end())
		{
			delete [] (*p).pEventData;
			p++;
		}
		EventDataFIFO.clear();
	}

	RegEditor 			*pRegEditor;
	TGTextView 			*fTextViewStatus;
	CrateMsgClient		*pCrateMsgClient;
	unsigned int		SlotId;
	unsigned int		BaseAddr;

	list<EventData>	EventDataFIFO;
	int					CurrentDisplayEvent;
	int					LastDrawnDisplayEvent;
	int					EventBufferMax;

	Bool_t				Active;
};


#endif
