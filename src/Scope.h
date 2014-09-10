#ifndef SCOPE_H
#define SCOPE_H

#include <vector>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "gtp.h"

#define SCOPE_PIXELS_PER_BIT					5

#define SCOPE_NAME_WIDTH						100
#define SCOPE_COLOR_EN							0xB0FFB0
#define SCOPE_COLOR_DIS							0xFFB0B0

#define SCOPE_DESC_MAX_CFG_REGS				16
#define SCOPE_DESC_MAX_DATA_REGS				16
#define SCOPE_DESC_CFG_MODE_COMPARE			0
#define SCOPE_DESC_CFG_MODE_MASK				1

#define TRACE_MODE_ANALOG						0x00000001
#define TRACE_MODE_DIGITAL						0x00000002
#define TRACE_MODE_MASK0						0x80000000	// don't draw non-zero values when mask bit=0
#define TRACE_MODE_MASK1						0x40000000	// don't draw non-zero values when mask bit=1

typedef struct
{
	const char *name;
	int height;
	int mode;
	int bitCount;
	int bitOffsetData;
	int maskOffset;
	struct
	{
		int cfg;
		int addr;
		int bitOffset;
	} cfg;
	struct
	{
		int val;
		int addr;
		int bitOffset;
	} val;
} ScopeTraceDesc;

class ScopeTrace	: public TGFrame
{
public:
	ScopeTrace(const TGWindow *p, int traceHeight, int traceMode, int traceBitCount, int len, Color_t c)	: TGFrame(p, len*SCOPE_PIXELS_PER_BIT, traceHeight, 0, c)
	{
		static TRandom3 r;

		mode = traceMode;
		bitCount = traceBitCount;
		sampleLen = len;
		cursorpos = 0;
		pTraceData = new unsigned int[sampleLen];

		SetDisplayRange(0, GetWidth()-1);

		// Load some random data patterns for UI testing
		if(pTraceData)
		{
			if(mode & TRACE_MODE_ANALOG)
			{
				for(int i = 0; i < sampleLen; i++)
					pTraceData[i] = 100.0*r.Rndm();	// noise

				int n = 10.0*r.Rndm();	// number of pulses to generate
				while(n--)
				{
					double amp = 200.0*r.Rndm();	// pulse height
					int t = sampleLen*r.Rndm();
					for(int i = 0; i < (sampleLen-t); i++)
						pTraceData[t+i] += (double)i*amp*TMath::Exp(-(double)i/20.0);
				}

				for(int i = 0; i < sampleLen; i++)
				{
					unsigned int sum = 0;
					for(int j = 0; j < 20; j++)
					{
						if(i+j < sampleLen)
							sum+= pTraceData[i+j];
					}
					pTraceData[i] = sum;
				}
			}
			else if(mode & TRACE_MODE_DIGITAL)
			{
				for(int i = 0; i < sampleLen; i++)
					pTraceData[i] = 0;

				for(int i = 0; i < bitCount; i++)
				{
					int n = 10.0*r.Rndm();	// number of pulses to generate
					while(n--)
					{
						int t = sampleLen*r.Rndm();
						int w = 20.0*r.Rndm();
						int p = t+w;
						while(w--)
						{
							if(p < sampleLen)
								pTraceData[p] |= (1<<i);
							else
								break;
							p++;
						}
					}
				}
			}
		}
	}
	
	virtual void DoRedraw()
	{
		static TGGC *gc = 0;
		char buf[100];

		TGFrame::DoRedraw();

		if(!pTraceData)
			return;

		if(!gc)
		{
			gc = fClient->GetResourcePool()->GetGCPool()->FindGC(GetShadowGC()());
			gc = new TGGC(*gc);
		}

		if(mode & TRACE_MODE_ANALOG)	// analog mode
		{
			double min=4294967295.0, max=0.0, scale;
			
			for(int i = 0; i < sampleLen; i++)
			{
				if((unsigned int)pTraceData[i] > max)
					max = (unsigned int)pTraceData[i];
				if((unsigned int)pTraceData[i] < min)
					min = (unsigned int)pTraceData[i];
			}
			
			if(max-min != 0)
				scale = (GetHeight()-2)/(max-min);
			else
				scale = 1.0;
			
			for(int i = 0; i < sampleLen; i++)
			{
				int x,y,w;
				double h;
				w = SCOPE_PIXELS_PER_BIT;
				h = ((double)pTraceData[i]-min)*scale+1.0;
				x = i*SCOPE_PIXELS_PER_BIT;
				y = GetHeight()-h;
				gc->SetForeground(0x008000);
				gVirtualX->FillRectangle(fId, gc->GetGC(),x,y,w,(int)h);
				gc->SetForeground(0x00F000);
				gVirtualX->DrawRectangle(fId, gc->GetGC(),x,y,w,(int)h);
			}
			sprintf(buf, "%u", GetCursorValue());
		}
		else if((mode & TRACE_MODE_DIGITAL) && (bitCount > 1))	// digital bus mode
		{
			int scale = GetHeight()/bitCount;
			int x,y,w,h;
			for(int b = 0; b < bitCount; b++)
			{
				for(int i = 0; i < sampleLen; i++)
				{
					w = SCOPE_PIXELS_PER_BIT-1;
					x = i*SCOPE_PIXELS_PER_BIT+1;
					h = scale-1;
					y = GetHeight()-b*scale-scale;
					if(pTraceData[i]&(1<<b))
						gc->SetForeground(0x00F000);
					else
						gc->SetForeground(0xF00000);
					gVirtualX->FillRectangle(fId, gc->GetGC(),x,y,w,h);
				}
// draw separation line every 10 traces
//				gc->SetForeground(0x808080);
//				if((b % 10) == 9)
//					gVirtualX->DrawLine(fId, gc->GetGC(),0,y-1,GetWidth()-1,y-1);
			}
			sprintf(buf, "0x%08X", GetCursorValue());
		}
		else if((mode & TRACE_MODE_DIGITAL) && (bitCount == 1))	// digital trace mode
		{
			int scale = GetHeight()/bitCount;
			int yhi = GetHeight()-scale+2;
			int ylo = GetHeight()-2;
			int x1,y1,x2,y2;
			x2 = 0;
			y2 = ylo;
			gc->SetForeground(0x00F000);
			for(int i = 0; i < sampleLen; i++)
			{
				x1 = x2;
				y1 = y2;
				x2 = x1 + SCOPE_PIXELS_PER_BIT;
				if(pTraceData[i])
					y2 = yhi;
				else
					y2 = ylo;
				
				if(y1 != y2)
					gVirtualX->DrawLine(fId, gc->GetGC(),x1,y1,x1,y2);
				
				gVirtualX->DrawLine(fId, gc->GetGC(),x1,y2,x2,y2);
			}
			sprintf(buf, "%u", GetCursorValue());
		}
		else
			sprintf(buf, "trace mode error");

		// Draw cursor selected value
		gc->SetForeground(0x000000);
		gVirtualX->FillRectangle(fId, gc->GetGC(),x1_disp,3,6*strlen(buf),13);
		gc->SetForeground(0xFFFF00);
		gVirtualX->DrawString(fId, gc->GetGC(),x1_disp,14,(const char *)buf, strlen(buf));

		// T=0
		gc->SetForeground(0x0000FF);
		gVirtualX->DrawLine(fId, gc->GetGC(),GetWidth()/2,0,GetWidth()/2,GetHeight()-1);
		
		// Cursor
		gc->SetForeground(0x0000FF);
		gVirtualX->DrawLine(fId, gc->GetGC(),cursorpos,0,cursorpos,GetHeight()-1);
//...use xor?...
	}
	
	unsigned int GetCursorValue()
	{
		int idx = cursorpos / SCOPE_PIXELS_PER_BIT;

		if(idx >= sampleLen)
			idx = sampleLen-1;

		if(idx < 0)
			return idx = 0;

		return pTraceData[idx];
	}

	void SetCursor(int x)
	{
		cursorpos = x;
		fClient->NeedRedraw(this);
	}

	void SetDisplayRange(int x1, int x2)
	{
		x1_disp = x1;
		x2_disp = x2;
	}

	int				mode;
	int				bitCount;
	int				sampleLen;
	int				cursorpos;
	int				x1_disp, x2_disp;
	unsigned int	*pTraceData;
};

class ScopeCfgTrg	: public TGTransientFrame
{
public:
	ScopeCfgTrg(const TGWindow *p) : TGTransientFrame(p, NULL, 200, 120, kVerticalFrame | kFixedSize)
	{
		DontCallClose(); // to avoid double deletions.
		SetCleanup(kDeepCleanup);
	}
	
	Bool_t Run(ScopeTraceDesc *pDesc)
	{
		quit = kFALSE;
		
		TGCompositeFrame *pF1;
		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX,20,20,5,5));
			if(pDesc->mode & TRACE_MODE_DIGITAL)
			{
				pF1->AddFrame(new TGLabel(pF1, new TGString("EnableMask:")), new TGLayoutHints(kLHintsLeft));
				pF1->AddFrame(pNumEnabled = new TGNumberEntry(pF1, pDesc->cfg.cfg, 8, -1, TGNumberFormat::kNESHex, TGNumberFormat::kNEAAnyNumber), new TGLayoutHints(kLHintsRight));
					pNumEnabled->SetWidth(75);
			}
		
		if(pDesc->mode & TRACE_MODE_ANALOG)
		{
			AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX,20,20,5,5));
				pF1->AddFrame(new TGLabel(pF1, new TGString("Comparison:")), new TGLayoutHints(kLHintsLeft));
				pF1->AddFrame(pComboOperator = new TGComboBox(pF1), new TGLayoutHints(kLHintsRight));
					pComboOperator->AddEntry("any", 0);
					pComboOperator->AddEntry("==", 1);
					pComboOperator->AddEntry("!=", 2);
					pComboOperator->AddEntry("<", 3);
					pComboOperator->AddEntry(">", 4);
					pComboOperator->Select(pDesc->cfg.cfg % 5, kFALSE);
					pComboOperator->SetWidth(75);
					pComboOperator->SetHeight(20);
		}
		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX,20,20,5,5));
			pF1->AddFrame(new TGLabel(pF1, new TGString("Value:")), new TGLayoutHints(kLHintsLeft));
			if(pDesc->mode & TRACE_MODE_ANALOG)
			{
				pF1->AddFrame(pNumValue = new TGNumberEntry(pF1, pDesc->val.val, 8, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber), new TGLayoutHints(kLHintsRight));
				pNumValue->SetLimits(TGNumberFormat::kNELLimitMinMax, 0.0, pow(2.0, pDesc->bitCount) - 1.0);
				pNumValue->SetWidth(75);
			}
			else if(pDesc->mode & TRACE_MODE_DIGITAL)
			{
				pF1->AddFrame(pNumValue = new TGNumberEntry(pF1, pDesc->val.val, 8, -1, TGNumberFormat::kNESHex, TGNumberFormat::kNEAAnyNumber), new TGLayoutHints(kLHintsRight));
				pNumValue->SetLimits(TGNumberFormat::kNELLimitMinMax, 0.0, pow(2.0, pDesc->bitCount) - 1.0);
				pNumValue->SetWidth(75);
			}
		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX,20,20,5,5));
			pF1->AddFrame(pButtonOk = new TGTextButton(pF1, new TGHotString("Ok"), BTN_OK), new TGLayoutHints(kLHintsCenterX));
				pButtonOk->SetWidth(75);
				pButtonOk->Associate(this);
			pF1->AddFrame(pButtonCancel = new TGTextButton(pF1, new TGHotString("Cancel"), BTN_CANCEL), new TGLayoutHints(kLHintsCenterX));
				pButtonCancel->SetWidth(75);
				pButtonCancel->Associate(this);

		MapSubwindows();
		Resize();
		CenterOnParent();
		SetWindowName(Form("Trigger config: %s", pDesc->name));
		MapWindow();
		
		while(!quit)
			gSystem->ProcessEvents();

		if(writeParam)
		{
			if(pDesc->mode & TRACE_MODE_ANALOG)
				pDesc->cfg.cfg = pComboOperator->GetSelected();
			else if(pDesc->mode & TRACE_MODE_DIGITAL)
				pDesc->cfg.cfg = pNumEnabled->GetIntNumber();

			pDesc->val.val = pNumValue->GetIntNumber();
			return kTRUE;
		}
		
		//DeleteWindow();  // deletes fMain
		
		return kFALSE;
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			switch(parm1)
			{
				case BTN_OK:
					writeParam = kTRUE;
					quit = kTRUE;
					break;
				case BTN_CANCEL:
					writeParam = kFALSE;
					quit = kTRUE;
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
			}
		}
		else
			printf("msg=%d, submsg=%d, p1=%ld, p2=%ld\n", GET_MSG(msg), GET_SUBMSG(msg), parm1, parm2);
		
		return kTRUE;
	}

private:
	enum
	{
		BTN_OK,
		BTN_CANCEL
	};
	
	Bool_t				quit;
	Bool_t				writeParam;
	TGCheckButton		*pCheckEnable;
	TGComboBox			*pComboOperator;
	TGNumberEntry		*pNumValue;
	TGNumberEntry		*pNumEnabled;
	TGTextButton		*pButtonOk;
	TGTextButton		*pButtonCancel;
};

typedef struct
{
	int sampleLen;
	struct
	{
		int addr;
		int bitNum;
	} rdyStatusReg;
	struct
	{
		int addr;
		int bitNum;
	} enControlReg;
	struct
	{
		int addr;
		int num;
	} dataRegs;
	vector<ScopeTraceDesc>	traceDesc;
	vector<ScopeTrace *>	traceFrame;
	vector<TGTextButton	*>	traceButton;
} ScopeDesc;

class Scope	: public TGCompositeFrame
{
public:
	Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;

		TGCompositeFrame *pF1;

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pF1->AddFrame(pButtonAuto = new TGTextButton(pF1, new TGHotString("Auto")));
				pButtonAuto->AllowStayDown(kTRUE);
				pButtonAuto->SetEnabled(kTRUE);
			pF1->AddFrame(pButtonRun = new TGTextButton(pF1, new TGHotString("Run"), BTN_RUN));
				pButtonRun->Associate(this);
				pButtonRun->SetEnabled(kTRUE);
			pF1->AddFrame(pButtonStop = new TGTextButton(pF1, new TGHotString("Stop"), BTN_STOP));
				pButtonStop->Associate(this);
				pButtonStop->SetEnabled(kFALSE);
			pF1->AddFrame(pButtonSave = new TGTextButton(pF1, new TGHotString("Save"), BTN_SAVE));
				pButtonSave->Associate(this);

		AddFrame(pFrameTraces = new TGHorizontalFrame(this, SCOPE_NAME_WIDTH, 100), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameTraces->AddFrame(pCNames = new TGCanvas(pFrameTraces, SCOPE_NAME_WIDTH, 100), new TGLayoutHints(kLHintsExpandY));
				pCNames->SetContainer(pFrameTraceNames = new TGVerticalFrame(pCNames->GetViewPort(), SCOPE_NAME_WIDTH, 100));
				pCNames->SetScrolling(TGCanvas::kCanvasNoScroll);

			pFrameTraces->AddFrame(pCTraces = new TGCanvas(pFrameTraces), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCTraces->SetContainer(pFrameTraceScope = new TGVerticalFrame(pCTraces->GetViewPort()));
				pCTraces->GetVScrollbar()->Associate(this);
				pCTraces->GetHScrollbar()->Associate(this);

		AddFrame(pStatusBar = new TGStatusBar(this), new TGLayoutHints(kLHintsExpandX));

		gVirtualX->GrabButton(GetId(), kButton3, kAnyModifier, kPointerMotionMask | kButtonPressMask, kNone, kNone);

		pTimerUpdate = new TTimer(this, 100, kTRUE);

		ScopeConfig.sampleLen = 0;
		ScopeConfig.rdyStatusReg.addr = 0;
		ScopeConfig.rdyStatusReg.bitNum = 0;
		ScopeConfig.enControlReg.addr = 0;
		ScopeConfig.enControlReg.bitNum = 0;
		ScopeConfig.dataRegs.addr = 0;
		ScopeConfig.dataRegs.num = 0;
	}
	
	void UpdateCursor(int pos)
	{
		if(pos >= SCOPE_NAME_WIDTH+3)
		{
			pos-= SCOPE_NAME_WIDTH+3;
			for(unsigned int i = 0; i < ScopeConfig.traceFrame.size(); i++)
				ScopeConfig.traceFrame[i]->SetCursor(pos);

			if(ScopeConfig.traceFrame.size() > 0)
				pStatusBar->SetText(Form("Cursor @ %dns", 4*(pos-(int)ScopeConfig.traceFrame[0]->GetWidth()/2)/SCOPE_PIXELS_PER_BIT));
		}
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
			ScopeTriggerTimeout();

		return kTRUE;
	}
	
	virtual Bool_t HandleButton(Event_t *event)
	{
		TGCompositeFrame::HandleButton(event);

		if(event->fCode == kButton3)
			UpdateCursor(event->fX+pCTraces->GetHScrollbar()->GetPosition());
		return kTRUE;
	}

	virtual Bool_t HandleMotion(Event_t *event)
	{
		TGCompositeFrame::HandleMotion(event);

		UpdateCursor(event->fX+pCTraces->GetHScrollbar()->GetPosition());
		return kTRUE;
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		if((GET_MSG(msg) == kC_TEXTENTRY) && (GET_SUBMSG(msg) == kTE_TEXTCHANGED))
		{
			switch(parm1)
			{
				default:
					printf("textentry id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_COMBOBOX))
		{
			switch(parm1)
			{
				default:
					printf("combo id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			if(parm1 >= BTN_SCOPETRACE)
			{
				int i = parm1-BTN_SCOPETRACE;
				ScopeCfgTrg scopeCfgTrg(gClient->GetRoot());
				if(scopeCfgTrg.Run(&ScopeConfig.traceDesc[i]) == kTRUE)
				{
					if(ScopeConfig.traceDesc[i].cfg.cfg)
					{
						ScopeConfig.traceButton[i]->SetBackgroundColor(SCOPE_COLOR_EN);
						if(ScopeConfig.traceDesc[i].mode == 0)
						{
							const char *op_sym[] = {"any", "==", "!=", "<", "<"};
							ScopeConfig.traceButton[i]->SetToolTipText(Form("%s\n%s %u",
									ScopeConfig.traceDesc[i].name,
									op_sym[ScopeConfig.traceDesc[i].cfg.cfg % 5],
									ScopeConfig.traceDesc[i].val.val));
						}
						else
						{
							ScopeConfig.traceButton[i]->SetToolTipText(
								Form("%s\nM: 0x%08X V: 0x%08X",
									ScopeConfig.traceDesc[i].name,
									ScopeConfig.traceDesc[i].cfg.cfg,
									ScopeConfig.traceDesc[i].val.val));
						}
					}
					else
					{
						ScopeConfig.traceButton[i]->SetBackgroundColor(SCOPE_COLOR_DIS);
						ScopeConfig.traceButton[i]->SetToolTipText("Disabled");
					}
					fClient->NeedRedraw(ScopeConfig.traceButton[i]);
				}
			}
			else
			{
				switch(parm1)
				{
					case BTN_RUN:
						ScopeTriggerRun();
						break;
					case BTN_STOP:
						ScopeTriggerStop();
						break;
					case BTN_SAVE:
						ScopeSave();
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
			}
		}
		else if(GET_MSG(msg) == kC_VSCROLL)
		{
			pCTraces->GetViewPort()->SetVPos((Int_t)-parm1);
			pCNames->GetViewPort()->SetVPos((Int_t)-parm1);
		}
		else if(GET_MSG(msg) == kC_HSCROLL)
		{
			pCTraces->GetViewPort()->SetHPos((Int_t)-parm1);
			for(unsigned int i = 0; i < ScopeConfig.traceFrame.size(); i++)
				ScopeConfig.traceFrame[i]->SetDisplayRange(parm1, parm1);
		}
		else
			printf("msg=%d, submsg=%d, p1=%ld, p2=%ld\n", GET_MSG(msg), GET_SUBMSG(msg), parm1, parm2);
		return kTRUE;
	}

	void ScopeSave()
	{
		FILE *f = fopen("waveform.txt", "awt");

		if(f)
		{
			fprintf(f, "# WAVEFORM START\n");

			fprintf(f, "#t");
			for(unsigned int i = 0; i < ScopeConfig.traceDesc.size(); i++)
				fprintf(f, ",%s", ScopeConfig.traceDesc[i].name);
			fprintf(f, "\n");

			for(int j = 0; j < ScopeConfig.sampleLen; j++)
			{
				fprintf(f, "%d", j);
				for(unsigned int i = 0; i < ScopeConfig.traceDesc.size(); i++)
				{
					fprintf(f, ",%d", ScopeConfig.traceFrame[i]->pTraceData[j]);
				}
				fprintf(f, "\n");
			}
			fprintf(f, "# WAVEFORM END\n");
			fclose(f);
		}
	}

	void ScopeTriggerReadout()
	{
		int i, j;
		int **pBuf = new (nothrow) int *[ScopeConfig.dataRegs.num];
		if(!pBuf)
		{
			printf("Error: ScopeTriggerReadout() memory failed to allocate\n");
			return;
		}
		
		for(i = 0; i < ScopeConfig.dataRegs.num; i++)
		{
			pBuf[i] = new (nothrow) int [ScopeConfig.sampleLen];
			if(!pBuf[i])
			{
				printf("Error: ScopeTriggerReadout() memory failed to allocate\n");
				for(int j = 0; j < i; j++)
					delete[] pBuf[j];
				delete[] pBuf;
				return;
			}
		}

		pM->RMWReg32((volatile unsigned int *)ScopeConfig.enControlReg.addr, 0, 1<<ScopeConfig.enControlReg.bitNum);

		for(i = 0; i < ScopeConfig.dataRegs.num; i++)
			pM->BlkReadReg32((volatile unsigned int *)ScopeConfig.dataRegs.addr+i, (unsigned int *)pBuf[i], ScopeConfig.sampleLen, CRATE_MSG_FLAGS_NOADRINC);

		for(unsigned i = 0; i < ScopeConfig.traceDesc.size(); i++)
		{
			int bufNum = ScopeConfig.traceDesc[i].bitOffsetData / 32;
			int bufShift = ScopeConfig.traceDesc[i].bitOffsetData % 32;
			int bufMask = 0xFFFFFFFF;

			if(ScopeConfig.traceDesc[i].bitCount < 32)
				bufMask = (1<<ScopeConfig.traceDesc[i].bitCount)-1;

//			printf("\n");
			for(j = 0; j < ScopeConfig.sampleLen; j++)
			{
				int maskval;

				if( (ScopeConfig.traceDesc[i].mode & TRACE_MODE_MASK0) || (ScopeConfig.traceDesc[i].mode & TRACE_MODE_MASK1) )
//				{
					maskval = (pBuf[ScopeConfig.traceDesc[i].maskOffset / 32][j]>>(ScopeConfig.traceDesc[i].maskOffset % 32)) & 0x1;
//					printf("%d", maskval);
//				}

				if( (ScopeConfig.traceDesc[i].mode & TRACE_MODE_MASK0) && (maskval == 0) )
						ScopeConfig.traceFrame[i]->pTraceData[j] = 0;
				else if( (ScopeConfig.traceDesc[i].mode & TRACE_MODE_MASK1) && (maskval == 1) )
					ScopeConfig.traceFrame[i]->pTraceData[j] = 0;
				else
				{
					ScopeConfig.traceFrame[i]->pTraceData[j] = (pBuf[bufNum][j]>>bufShift);

					if(bufShift+ScopeConfig.traceDesc[i].bitCount > 32)
						ScopeConfig.traceFrame[i]->pTraceData[j] |= pBuf[bufNum+1][j]<<(32-bufShift);

					ScopeConfig.traceFrame[i]->pTraceData[j] &= bufMask;
				}
			}
//			printf("\n");

			fClient->NeedRedraw(ScopeConfig.traceFrame[i]);
		}

		for(i = 0; i < ScopeConfig.dataRegs.num; i++)
			delete[] pBuf[i];
		delete[] pBuf;
	}

	void ScopeTriggerLoad()
	{
		for(unsigned int i = 0; i < ScopeConfig.traceDesc.size(); i++)
		{
			if(ScopeConfig.traceDesc[i].mode & TRACE_MODE_ANALOG)
			{
				int mask;

				mask = 0x7<<ScopeConfig.traceDesc[i].cfg.bitOffset;
				pM->RMWReg32((volatile unsigned int *)ScopeConfig.traceDesc[i].cfg.addr, ScopeConfig.traceDesc[i].cfg.cfg<<ScopeConfig.traceDesc[i].cfg.bitOffset, mask);

				mask = 0xFFFFFFFF;
				if(ScopeConfig.traceDesc[i].bitCount < 32)
					mask = (1<<ScopeConfig.traceDesc[i].bitCount)-1;
				mask<<= ScopeConfig.traceDesc[i].val.bitOffset;
				pM->RMWReg32((volatile unsigned int *)ScopeConfig.traceDesc[i].val.addr, ScopeConfig.traceDesc[i].val.val<<ScopeConfig.traceDesc[i].val.bitOffset, mask);
			}
			else if(ScopeConfig.traceDesc[i].mode & TRACE_MODE_DIGITAL)
			{
				int reg;
				int mask;

				// Configure trigger mask
				reg = pM->ReadReg32((volatile unsigned int *)ScopeConfig.traceDesc[i].cfg.addr);
				mask = 0xFFFFFFFF;

				if(ScopeConfig.traceDesc[i].bitCount < 32)
					mask = (1<<ScopeConfig.traceDesc[i].bitCount)-1;

				mask<<= ScopeConfig.traceDesc[i].cfg.bitOffset;

				reg &= ~mask;
				reg |= ScopeConfig.traceDesc[i].cfg.cfg<<ScopeConfig.traceDesc[i].cfg.bitOffset;
				pM->WriteReg32((volatile unsigned int *)ScopeConfig.traceDesc[i].cfg.addr, reg);

				// Configure trigger value
				reg = pM->ReadReg32((volatile unsigned int *)ScopeConfig.traceDesc[i].val.addr);
				mask = 0xFFFFFFFF;

				if(ScopeConfig.traceDesc[i].bitCount < 32)
					mask = (1<<ScopeConfig.traceDesc[i].bitCount)-1;

				mask<<= ScopeConfig.traceDesc[i].val.bitOffset;

				reg &= ~mask;
				reg |= ScopeConfig.traceDesc[i].val.val<<ScopeConfig.traceDesc[i].val.bitOffset;
				pM->WriteReg32((volatile unsigned int *)ScopeConfig.traceDesc[i].val.addr, reg);
			}
		}
		pM->RMWReg32((volatile unsigned int *)ScopeConfig.enControlReg.addr,
				(1<<ScopeConfig.enControlReg.bitNum),
				(1<<ScopeConfig.enControlReg.bitNum));
	}

	void ScopeTriggerTimeout()
	{
		unsigned int status = pM->ReadReg32((volatile unsigned int *)ScopeConfig.rdyStatusReg.addr);

		if(status & (1<<ScopeConfig.rdyStatusReg.bitNum))
		{
			ScopeTriggerReadout();

			if(pButtonAuto->IsDown())
				ScopeTriggerRun();
			else
				ScopeTriggerStop();
		}
		else
			pTimerUpdate->Start(100, kTRUE);
	}

	void ScopeTriggerRun()
	{
//		pButtonAuto->SetEnabled(kFALSE);
		pButtonRun->SetEnabled(kFALSE);
		pButtonStop->SetEnabled(kTRUE);

		ScopeTriggerLoad();

		pTimerUpdate->Start(100, kTRUE);
	}

	void ScopeTriggerStop()
	{
		pTimerUpdate->Stop();

//		pButtonAuto->SetEnabled(kTRUE);
		pButtonRun->SetEnabled(kTRUE);
		pButtonStop->SetEnabled(kFALSE);
	}

	void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
	{
		ScopeConfig.sampleLen = sampleLen;
		ScopeConfig.rdyStatusReg.addr = rdyAddr;
		ScopeConfig.rdyStatusReg.bitNum = rdyBit;
		ScopeConfig.enControlReg.addr = ctrlAddr;
		ScopeConfig.enControlReg.bitNum = ctrlBit;
		ScopeConfig.dataRegs.addr = dataAddr;
		ScopeConfig.dataRegs.num = dataNum;
	}

	void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset, int maskBitOffset = 0)
	{
		TGCompositeFrame *pF1;
		TGTextButton *pButton;
		ScopeTraceDesc traceDesc;
		ScopeTrace *pScopeTrace;

		traceDesc.name = name;
		traceDesc.height = height;
		traceDesc.mode = mode;
		traceDesc.bitCount = bitCount;
		traceDesc.bitOffsetData = bitOffsetData;
		traceDesc.maskOffset = maskBitOffset;
		traceDesc.cfg.cfg = 0;
		traceDesc.cfg.addr = cfgAddr;
		traceDesc.cfg.bitOffset = cfgBitOffset;
		traceDesc.val.val = 0;
		traceDesc.val.addr = valAddr;
		traceDesc.val.bitOffset = valBitOffset;
		ScopeConfig.traceDesc.push_back(traceDesc);

		pFrameTraceNames->AddFrame(pF1 = new TGVerticalFrame(pFrameTraceNames));
			pButton = new TGTextButton(pF1, new TGHotString(name), BTN_SCOPETRACE+ScopeConfig.traceButton.size()), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY);
			pF1->ChangeOptions(pF1->GetOptions() | kFixedSize);
			pF1->Resize(SCOPE_NAME_WIDTH, traceDesc.height);
			pF1->AddFrame(pButton, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pButton->SetBackgroundColor(SCOPE_COLOR_DIS);
				pButton->SetToolTipText("Disabled");
				pButton->Associate(this);
		ScopeConfig.traceButton.push_back(pButton);

		pScopeTrace = new ScopeTrace(pFrameTraceScope, height, mode, bitCount, ScopeConfig.sampleLen, TColor::RGB2Pixel(0,0,0));
		pFrameTraceScope->AddFrame(pScopeTrace);
		ScopeConfig.traceFrame.push_back(pScopeTrace);
	}

private:
	enum
	{
		BTN_RUN = 1,
		BTN_STOP = 2,
		BTN_SCOPETRACE	= 100,	// 100-200 reserved for scope trace button ids
		BTN_SAVE = 3
	};

	ModuleFrame			*pM;

	ScopeDesc			ScopeConfig;
	TGCompositeFrame	*pFrameTraces;
	TGCompositeFrame	*pFrameTraceNames;
	TGCompositeFrame	*pFrameTraceScope;
	TGTextButton		*pButtonAuto;
	TGTextButton		*pButtonRun;
	TGTextButton		*pButtonStop;
	TGTextButton		*pButtonSave;
	TGCanvas				*pCTraces;
	TGCanvas				*pCNames;
	TGStatusBar			*pStatusBar;
	TTimer				*pTimerUpdate;
};

#endif
