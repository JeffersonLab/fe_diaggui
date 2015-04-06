#ifndef GTP_HPSStatus_H
#define GTP_HPSStatus_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "gtp.h"

#include "RegEditor.h"


class GTP_HPSStatus	: public TGCompositeFrame
{
public:
	GTP_HPSStatus(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pFrameButtons->AddFrame(pButtonUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Display"), BTN_UPDATE), new TGLayoutHints(kLHintsCenterX));
				pButtonUpdate->Associate(this);
			pFrameButtons->AddFrame(pButtonReset = new TGTextButton(pFrameButtons, new TGHotString("Reset"), BTN_RESET), new TGLayoutHints(kLHintsCenterX));
				pButtonReset->Associate(this);
			pFrameButtons->AddFrame(pButtonSWSync = new TGTextButton(pFrameButtons, new TGHotString("Sync"), BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX));
				pButtonSWSync->Associate(this);
			
		AddFrame(pFrameText = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameText->AddFrame(pTextViewFPGA = new TGTextView(pFrameText), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		pTimerUpdate = new TTimer(this, 1000, kTRUE);
//		pTimerUpdate->Start(500, kTRUE);

		UpdateTextView();
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
			UpdateTextView();
			pTimerUpdate->Start(500, kTRUE);
		}
		return kTRUE;
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case BTN_UPDATE:
						UpdateTextView();
						break;

					case BTN_RESET:
						break;

					case BTN_SW_SYNC:
						break;

					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
			}
			break;
		}
		return kTRUE;
	}

	void Reset()
	{
	}

	void UpdateTextView()
	{
		int i;
		TGText *pT = new TGText(Form("%-35s = 0x%08lX", "BaseAddr", (long)pRegs));
		pT->AddText(new TGText(""));

		pT->AddText(new TGText(Form("VXS Status")));
		pT->AddText(new TGText(Form("%-11s %-9s %-12s %-11s", "Port", "ChannelUp", "Latency(ns)", "Errors")));

		const char *port_names[] = {
				"Slot10-PP1", "Slot13-PP2", "Slot9-PP3", "Slot14-PP4", "Slot8-PP5", "Slot15-PP6", "Slot7-PP7", "Slot16-PP8",
				"Slot6-PP9", "Slot17-PP10", "Slot5-PP11", "Slot18-PP12", "Slot4-PP13", "Slot19-PP14", "Slot3-PP15", "Slot20-PP16"
			};

		int slot_to_payload[] = {
				0,0,15,13,11,9,7,5,3,1,0,0,2,4,6,8,10,12,14,16
			};

		for(i = 0; i < (int)(sizeof(slot_to_payload)/sizeof(slot_to_payload[0])); i++)
		{
			int payload = slot_to_payload[i];
			if(payload)
			{
				int status = pM->ReadReg32(&pRegs->Ser[payload-1].Status);
				int errors = pM->ReadReg32(&pRegs->Ser[payload-1].ErrTile0);
				int status2 = pM->ReadReg32(&pRegs->Ser[payload-1].ErrTile1);
				pT->AddText(new TGText(Form("%-11s %-9d %-12d %-5d %-5d", port_names[payload-1], (status & 0x1000)>>12, (status2 & 0xFFFF)*4, errors & 0xFFFF, errors>>16)));
			}
		}

		pTextViewFPGA->SetText(pT);
		pTextViewFPGA->Update();
	}

private:
	
	enum Buttons
	{
		BTN_RESET,
		BTN_SW_SYNC,
		BTN_UPDATE,
	};

	ModuleFrame			*pM;
	Gtp_regs				*pRegs;
	
	TTimer				*pTimerUpdate;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameText;

	TGTextView			*pTextViewFPGA;

	TGTextButton		*pButtonUpdate;
	TGTextButton		*pButtonReset;
	TGTextButton		*pButtonSWSync;
	TGTextButton		*pButtonCustomConfig;
	TGTextButton		*pButtonSmartReset;
};

#endif
