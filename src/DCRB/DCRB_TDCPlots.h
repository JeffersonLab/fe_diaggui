#ifndef DCRB_TDCPlots_H
#define DCRB_TDCPlots_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRB.h"

#define READOUT_BUFFER_LEN		1024

#define COM_TDCREFERENCE		2000
#define COM_TDCDISPLAYCHANNELS	2001

#define NUM_HISTNUMBINS			3000

#define COM_SEL_TRIG			0
#define COM_SEL_TRIG_SELF		1
#define COM_SEL_TRIG_CH0		2

#define COM_SEL_TDCH			0

#define POLL_RATE				20

class DCRB_TDCPlots	: public TGCompositeFrame
{
public:
	DCRB_TDCPlots(const TGWindow *p, ModuleFrame *pModule, unsigned int a32_baseAddr) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		A32BaseAddr = a32_baseAddr;
		pM = pModule;
		pRegs = (DCRB_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrameButtons->AddFrame(pButtonReadSingle = new TGTextButton(pFrameButtons, new TGHotString("ReadSingle"), BTN_READ_SINGLE), new TGLayoutHints(kLHintsCenterY));
				pButtonReadSingle->Associate(this);
			pFrameButtons->AddFrame(pButtonReadContinuous = new TGTextButton(pFrameButtons, new TGHotString("ReadContinous"), BTN_READ_CONT), new TGLayoutHints(kLHintsCenterY));
				pButtonReadContinuous->Associate(this);
			pFrameButtons->AddFrame(pButtonReadStop = new TGTextButton(pFrameButtons, new TGHotString("ReadStop"), BTN_READ_STOP), new TGLayoutHints(kLHintsCenterY));
				pButtonReadStop->SetEnabled(kFALSE);
				pButtonReadStop->Associate(this);
			pFrameButtons->AddFrame(pButtonClearHist = new TGTextButton(pFrameButtons, new TGHotString("ClearHist"), BTN_CLEAR_HIST), new TGLayoutHints(kLHintsCenterY));
				pButtonClearHist->Associate(this);
			pFrameButtons->AddFrame(pButtonUseSWTrig = new TGTextButton(pFrameButtons, new TGHotString("UseSWTrig"), BTN_USE_SWTRIG), new TGLayoutHints(kLHintsCenterY));
				pButtonUseSWTrig->AllowStayDown(kTRUE);
				pButtonUseSWTrig->Associate(this);
			pFrameButtons->AddFrame(pComboReference = new TGComboBox(pFrameButtons, COM_TDCREFERENCE));
				pComboReference->AddEntry(new TGString("Trigger"), COM_SEL_TRIG);
				pComboReference->AddEntry(new TGString("Self (period)"), COM_SEL_TRIG_SELF);
				for(int i = 0; i < 96; i++)
				{
					char buf[20];
					sprintf(buf, "Channel %d", i);
					pComboReference->AddEntry(buf, COM_SEL_TRIG_CH0+i);
				}
				pComboReference->Select(0);
				pComboReference->SetWidth(150);
				pComboReference->SetHeight(20);
				pComboReference->Associate(this);
			pFrameButtons->AddFrame(pComboDisplayedChannels = new TGComboBox(pFrameButtons, COM_TDCDISPLAYCHANNELS));
				for(int i = 0; i < 16; i++)
				{
					char buf[20];
					sprintf(buf, "Channels %d-%d", i*6,i*6+5);
					pComboDisplayedChannels->AddEntry(buf, COM_SEL_TDCH+i);
				}
				pComboDisplayedChannels->Select(0);
				pComboDisplayedChannels->SetWidth(150);
				pComboDisplayedChannels->SetHeight(20);
				pComboDisplayedChannels->Associate(this);

			pFrameButtons->AddFrame(pLabelHistNumBins = new TGLabel(pFrameButtons, "Histogram Bins(1ns):"));
			pFrameButtons->AddFrame(pNumEntryHistNumBins = new TGNumberEntry(pFrameButtons, 2000, 4, NUM_HISTNUMBINS, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 1.0, 32768.0));
				pNumEntryHistNumBins->Associate(this);

		AddFrame(pCanvasHisto = new TRootEmbeddedCanvas("TDC Channels", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasHisto->GetCanvas()->SetBorderMode(0);
			pCanvasHisto->GetCanvas()->Divide(3, 2);
			for(int i = 0; i < 96; i++)
			{
				char buf[20];
				sprintf(buf, "TDC Channel %d", i);
				pHistTDCChannels[i] = new TH1I(buf, NULL, pNumEntryHistNumBins->GetIntNumber(), 0, pNumEntryHistNumBins->GetIntNumber()-1);
				pHistTDCChannels[i]->SetFillColor(2);
			}

		DrawPlots();
		UpdatePlots();

		pTimerUpdate = new TTimer(this, POLL_RATE, kTRUE);
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_READ_SINGLE:
						pButtonReadSingle->SetEnabled(kFALSE);
						pButtonReadContinuous->SetEnabled(kFALSE);
						pButtonReadStop->SetEnabled(kTRUE);
						pTimerUpdate->Start(POLL_RATE, kTRUE);
						bReadSingle = kTRUE;
						if(pButtonUseSWTrig->IsDown())
							pM->WriteReg32(&pRegs->TriggerSource, 0x08);
						break;
					case BTN_READ_CONT:
						pButtonReadSingle->SetEnabled(kFALSE);
						pButtonReadContinuous->SetEnabled(kFALSE);
						pButtonReadStop->SetEnabled(kTRUE);
						pTimerUpdate->Start(POLL_RATE, kTRUE);
						bReadSingle = kFALSE;
						if(pButtonUseSWTrig->IsDown())
							pM->WriteReg32(&pRegs->TriggerSource, 0x08);
						break;
					case BTN_READ_STOP:
						pButtonReadSingle->SetEnabled(kTRUE);
						pButtonReadContinuous->SetEnabled(kTRUE);
						pButtonReadStop->SetEnabled(kFALSE);
						pTimerUpdate->Stop();
						break;
					case BTN_CLEAR_HIST:
						for(int i = 0; i < 96; i++)
							pHistTDCChannels[i]->Clear();
						pCanvasHisto->GetCanvas()->Modified();
						pCanvasHisto->GetCanvas()->Update();
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
				break;
			case kCM_COMBOBOX:
				switch(parm1)
				{
				case COM_TDCREFERENCE:
					break;
				case COM_TDCDISPLAYCHANNELS:
					DrawPlots();
					UpdatePlots();
					break;
				default:
					printf("combo id %d pressed\n", (int)parm1);
					break;
				}
				break;
			}
			break;
		}
		return kTRUE;
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
			unsigned int evtCount = pM->ReadReg32(&pRegs->FifoEventCnt);
			if((evtCount != 0xFFFFFFFF) && evtCount)
			{
				ReadoutBlock();
				if(bReadSingle == kFALSE)
				{
					if(pButtonUseSWTrig->IsDown())
						pM->WriteReg32(&pRegs->TriggerSource, 0x08);
					pTimerUpdate->Start(POLL_RATE, kTRUE);
				}
				else
				{
					pButtonReadSingle->SetEnabled(kTRUE);
					pButtonReadContinuous->SetEnabled(kTRUE);
					pButtonReadStop->SetEnabled(kFALSE);
					pTimerUpdate->Stop();
				}
			}
			else
				pTimerUpdate->Start(POLL_RATE, kTRUE);
		}
		return kTRUE;
	}

	void DrawPlots()
	{
		int offset = pComboDisplayedChannels->GetSelected();
		for(int i = 0; i < 6; i++)
		{
			pCanvasHisto->GetCanvas()->cd(i+1);
			pCanvasHisto->GetCanvas()->GetPad(i+1)->Clear();
			pHistTDCChannels[offset*6+i]->Draw("bar0");
		}
	}

	void UpdatePlots()
	{
		pCanvasHisto->GetCanvas()->Modified();
		pCanvasHisto->GetCanvas()->Update();
	}

	void ReadoutBlock()
	{
		ReadoutBufferLength = 0;
#if 0
		for(int i = 0; i < READOUT_BUFFER_LEN; i++)
		{
			ReadoutBuffer[i] = ReadReg32((volatile unsigned int *)A32BaseAddr);

//			if((ReadoutBuffer[i] & 0xF8000000) == 0x90000000)	// Event Header - flush data processing process data before
//				ProcessReadoutBlock();

			ReadoutBufferLength++;
			if((ReadoutBuffer[i] & 0xF8000000) == 0x88000000)	// Block Trailer
			{
				ProcessReadoutBlock();
				break;
			}
		}
#else
		//...neeed to fix this!
		//if(!pM->BlkReadReg32(A32BaseAddr, ReadoutBuffer, sizeof(ReadoutBuffer), CRATE_MSG_FLAGS_ADRINC | CRATE_MSG_FLAGS_USEDMA))
			return;

		//ReadoutBufferLength = (sizeof(ReadoutBuffer)-bytes_left)/4;
		ProcessReadoutBlock();
#endif
		DrawPlots();
		UpdatePlots();
	}

	void ProcessReadoutBlock()
	{
		unsigned int i, RefTime[96];

		int mode = pComboReference->GetSelected();

		if(mode == COM_SEL_TRIG)
		{
			for(i = 0; i < 96; i++)
				RefTime[i] = 0;
		}
		else if(mode == COM_SEL_TRIG_SELF)
		{
			for(i = 0; i < 96; i++)
				RefTime[i] = 0xFFFFFFFF;
		}
		else
		{
			unsigned int rtime = 32768;
			int ch = mode - COM_SEL_TRIG_CH0;
			if( (ch < 0) || (ch > 95) )
				ch = 0;

			for(i = 0; i < ReadoutBufferLength; i++)
			{
				if((ReadoutBuffer[i] & 0xF8000000) == 0xC0000000)
				{
					int evt_ch = (ReadoutBuffer[i]>>16) & 0x7F;
					unsigned int evt_time = (ReadoutBuffer[i]>>0) & 0xFFFF;
					if(evt_ch == ch)
					{
						rtime = evt_time;
						break;
					}
				}
			}
			for(i = 0; i < 96; i++)
				RefTime[i] = rtime;
		}
		for(i = 0; i < ReadoutBufferLength; i++)
		{
			if((ReadoutBuffer[i] & 0xF8000000) == 0xC0000000)
			{
				unsigned int ch = (ReadoutBuffer[i]>>16) & 0x7F;
				unsigned int time = (ReadoutBuffer[i]>>0) & 0xFFFF;

				if(ch < 96)
				{
					if(mode == COM_SEL_TRIG_SELF)
					{
						if(RefTime[ch] != 0xFFFFFFFF)
							pHistTDCChannels[ch]->Fill(RefTime[ch] - time);
						RefTime[ch] = time;
					}
					else
						pHistTDCChannels[ch]->Fill(time - RefTime[ch]);
				}
			}
		}
	}

private:

	enum Buttons
	{
		BTN_READ_SINGLE,
		BTN_READ_CONT,
		BTN_READ_STOP,
		BTN_CLEAR_HIST,
		BTN_USE_SWTRIG
	};
	
	unsigned int			A32BaseAddr;
	unsigned int			ReadoutBufferLength;
	unsigned int			ReadoutBuffer[READOUT_BUFFER_LEN];

	Bool_t					bReadSingle;

	ModuleFrame				*pM;
	DCRB_regs				*pRegs;

	TH1I						*pHistTDCChannels[96];

	TTimer					*pTimerUpdate;

	TRootEmbeddedCanvas	*pCanvasHisto;

	TGHorizontalFrame		*pFrameButtons;

	TGTextButton			*pButtonReadSingle;
	TGTextButton			*pButtonReadContinuous;
	TGTextButton			*pButtonReadStop;
	TGTextButton			*pButtonClearHist;
	TGTextButton			*pButtonUseSWTrig;

	TGComboBox				*pComboReference;
	TGComboBox				*pComboDisplayedChannels;

	TGLabel					*pLabelHistNumBins;
	TGNumberEntry			*pNumEntryHistNumBins;
};

#endif
