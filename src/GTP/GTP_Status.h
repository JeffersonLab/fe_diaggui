#ifndef GTP_Status_H
#define GTP_Status_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "gtp.h"

#include "RegEditor.h"


class GTP_Status	: public TGCompositeFrame
{
public:
	GTP_Status(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
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
						Reset();
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
		pM->WriteReg32(&pRegs->Clk.Ctrl, GTP_CLK_CTRL_RESET | GTP_CLK_CTRL_P0);
		pM->Delay(10);
		pM->WriteReg32(&pRegs->Clk.Ctrl, GTP_CLK_CTRL_P0);
		pM->Delay(10);
		for(int i = 0; i < 8; i++)
		{
			pM->WriteReg32(&pRegs->Ser[2*i].Ctrl, 0x400);
			pM->WriteReg32(&pRegs->Ser[2*i].Ctrl, 0x800);
		}
	}

	void UpdateTextView()
	{
		int i, j;
		TGText *pT = new TGText(Form("%-35s = 0x%08lX", "BaseAddr", (long)pRegs));
		pT->AddText(new TGText(""));

		SPFREG_HEX(&pRegs, Clk.Ctrl);
		SPFREG_HEX(&pRegs, Clk.Status);
		pT->AddText(new TGText(""));

		SPFREG_HEX(&pRegs, Sd.ScalerLatch);
		for(i = 0; i < 15; i++)
			SPFREG_N_HEX(&pRegs, Sd.Scalers, i);
		pT->AddText(new TGText(""));

		SPFREG_HEX(&pRegs, Trg.Ctrl);
		pT->AddText(new TGText(""));

		SPFREG_HEX(&pRegs, BCal.Delay);
		SPFREG_HEX(&pRegs, FCal.Delay);
		SPFREG_HEX(&pRegs, TagM.Delay);
		SPFREG_HEX(&pRegs, TagH.Delay);
		SPFREG_HEX(&pRegs, PS.Delay);
		SPFREG_HEX(&pRegs, ST.Delay);
		SPFREG_HEX(&pRegs, TOF.Delay);
		pT->AddText(new TGText(""));

		SPFREG_HEX(&pRegs, BCal.Width);
		SPFREG_HEX(&pRegs, FCal.Width);
		SPFREG_HEX(&pRegs, TagM.Width);
		SPFREG_HEX(&pRegs, TagH.Width);
		SPFREG_HEX(&pRegs, PS.Width);
		SPFREG_HEX(&pRegs, ST.Width);
		SPFREG_HEX(&pRegs, TOF.Width);
		pT->AddText(new TGText(""));

		for(i = 0; i < 32; i++)
		{
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, Ctrl);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, TrigOutCtrl);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, TrigOutStatus);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, BCalCtrl0);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, BCalCtrl1);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, FCalCtrl);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, BFCalCtrl);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, PSCtrl);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, STCtrl0);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, STCtrl1);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, TOFCtrl0);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, TOFCtrl1);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, TagMCtrl);
			SPFBASE_N_REG_HEX(&pRegs, Trigbits, i, TagHCtrl);
			for(j = 0; j < 8; j++)
				SPFBASE_N_REG_N_HEX(&pRegs, Trigbits, i, Scalers, j);
			pT->AddText(new TGText(""));
		}

		SPFREG_HEX(&pRegs, GxbCfgOdd.Status);
		SPFREG_HEX(&pRegs, GxbCfgOdd.Ctrl);
		SPFREG_HEX(&pRegs, GxbCfgOdd.Ctrl2);
		SPFREG_HEX(&pRegs, GxbCfgOdd.TxRxIn);
		SPFREG_HEX(&pRegs, GxbCfgOdd.TxRxOut);
		pT->AddText(new TGText(""));

		SPFREG_HEX(&pRegs, GxbCfgEven.Status);
		SPFREG_HEX(&pRegs, GxbCfgEven.Ctrl);
		SPFREG_HEX(&pRegs, GxbCfgEven.Ctrl2);
		SPFREG_HEX(&pRegs, GxbCfgEven.TxRxIn);
		SPFREG_HEX(&pRegs, GxbCfgEven.TxRxOut);
		pT->AddText(new TGText(""));

		for(i = 0; i < 16; i++)
		{
			SPFBASE_N_REG_HEX(&pRegs, Ser, i, Ctrl);
			SPFBASE_N_REG_HEX(&pRegs, Ser, i, Status);
			SPFBASE_N_REG_HEX(&pRegs, Ser, i, ErrTile0);
			pT->AddText(new TGText(""));
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
