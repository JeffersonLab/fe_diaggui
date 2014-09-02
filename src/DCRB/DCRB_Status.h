#ifndef DCRB_Status_H
#define DCRB_Status_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRB.h"

class DCRB_Status	: public TGCompositeFrame
{
public:
	DCRB_Status(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (DCRB_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pFrameButtons->AddFrame(pButtonUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Display"), DCRB_BTN_UPDATE), new TGLayoutHints(kLHintsCenterX));
				pButtonUpdate->Associate(this);
			pFrameButtons->AddFrame(pButtonReset = new TGTextButton(pFrameButtons, new TGHotString("Reset"), DCRB_BTN_RESET), new TGLayoutHints(kLHintsCenterX));
				pButtonReset->Associate(this);
			pFrameButtons->AddFrame(pButtonSWSync = new TGTextButton(pFrameButtons, new TGHotString("Sync"), DCRB_BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX));
				pButtonSWSync->Associate(this);
			pFrameButtons->AddFrame(pButtonSWTrig = new TGTextButton(pFrameButtons, new TGHotString("Trig"), DCRB_BTN_SW_TRIG), new TGLayoutHints(kLHintsCenterX));
				pButtonSWTrig->Associate(this);
			pFrameButtons->AddFrame(pButtonCustomCfg = new TGTextButton(pFrameButtons, new TGHotString("CustomConfig"), DCRB_BTN_CUSTOM_CFG), new TGLayoutHints(kLHintsCenterX));
				pButtonCustomCfg->Associate(this);

		AddFrame(pFrameText = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameText->AddFrame(pFrameLeft = new TGVerticalFrame(pFrameText), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pFrameLeft->AddFrame(pTextViewMain = new TGTextView(pFrameLeft), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));


		UpdateTextView();
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		unsigned int val;

		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
					case DCRB_BTN_UPDATE:
						UpdateTextView();
						break;
					case DCRB_BTN_RESET:
						pM->WriteReg32(&pRegs->Reset, 1);
						pM->WriteReg32(&pRegs->Reset, 0);

						pM->WriteReg32(&pRegs->GtpCtrl, 0x203);
						pM->WriteReg32(&pRegs->GtpCtrl, 0x202);
						pM->WriteReg32(&pRegs->GtpCtrl, 0x200);
						pM->WriteReg32(&pRegs->GtpCtrl, 0x000);
						
						break;
					case DCRB_BTN_SW_SYNC:
					{
						unsigned int r = pM->ReadReg32(&pRegs->TriggerSource);
						pM->WriteReg32(&pRegs->TriggerSource, r | TRIGSRC_SWSYNC);
						break;
					}
					case DCRB_BTN_SW_TRIG:
					{
						unsigned int r = pM->ReadReg32(&pRegs->TriggerSource);
						pM->WriteReg32(&pRegs->TriggerSource, r | TRIGSRC_SWTRIG);
						break;
					}
					case DCRB_BTN_CUSTOM_CFG:
					{
						val = pM->ReadReg32(&pRegs->ClockConfig) & 0xFFFFFFFC;
						pM->WriteReg32(&pRegs->ClockConfig, val | 0x3);
						pM->WriteReg32(&pRegs->ClockConfig, val | 0x1);
						pM->WriteReg32(&pRegs->TestPulseConfig, 0x3f);
						
						pM->WriteReg32(&pRegs->TriggerCtrl, 0xFE);

						pM->WriteReg32(&pRegs->GtpCtrl, 0x203);
						pM->WriteReg32(&pRegs->GtpCtrl, 0x202);
						break;
					}
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
			}
			break;
		}
		return kTRUE;
	}
	
	void UpdateTextView()
	{
		char buf[100];
		int i;

		pTextViewMain->Clear();
		pTextViewMain->AddLineFast("------ DCRB Status ------");

		sprintf(buf, "VME BaseAddress      = 0x%08lX", (long)pRegs); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Firmware Rev         = 0x%08X", pM->ReadReg32(&pRegs->FirmwareRev)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Board ID             = 0x%08X", pM->ReadReg32(&pRegs->BoardID)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GrpBusyFifo          = 0x%08X", pM->ReadReg32(&pRegs->GrpBusyFifo)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GrpBusyTrig          = 0x%08X", pM->ReadReg32(&pRegs->GrpBusyTrig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GrpErrorFifo         = 0x%08X", pM->ReadReg32(&pRegs->GrpErrorFifo)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SpiFlash             = 0x%08X", pM->ReadReg32(&pRegs->SpiFlash)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ICap                 = 0x%08X", pM->ReadReg32(&pRegs->ICap)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Adr32M               = 0x%08X", pM->ReadReg32(&pRegs->Adr32M)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "LookBack             = 0x%08X", pM->ReadReg32(&pRegs->LookBack)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "WindowWidth          = 0x%08X", pM->ReadReg32(&pRegs->WindowWidth)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "BlockConfig          = 0x%08X", pM->ReadReg32(&pRegs->BlockConfig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TDCConfig            = 0x%08X", pM->ReadReg32(&pRegs->TDCConfig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ClockConfig          = 0x%08X", pM->ReadReg32(&pRegs->ClockConfig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TestPulseConfig      = 0x%08X", pM->ReadReg32(&pRegs->TestPulseConfig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "DACConfig            = 0x%08X", pM->ReadReg32(&pRegs->DACConfig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TriggerBusyThreshold = 0x%08X", pM->ReadReg32(&pRegs->TriggerBusyThreshold)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TriggerSource        = 0x%08X", pM->ReadReg32(&pRegs->TriggerSource)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ADR32                = 0x%08X", pM->ReadReg32(&pRegs->ADR32)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Interrupt            = 0x%08X", pM->ReadReg32(&pRegs->Interrupt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "InterruptAck         = 0x%08X", pM->ReadReg32(&pRegs->InterruptAck)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Geo                  = 0x%08X", pM->ReadReg32(&pRegs->Geo)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "FifoWordCnt          = 0x%08X", pM->ReadReg32(&pRegs->FifoWordCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "FifoEventCnt         = 0x%08X", pM->ReadReg32(&pRegs->FifoEventCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ReadoutConfig        = 0x%08X", pM->ReadReg32(&pRegs->ReadoutConfig)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SRAMDebugAddr        = 0x%08X", pM->ReadReg32(&pRegs->SRAMDebugAddr)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SRAMDebugData        = 0x%08X", pM->ReadReg32(&pRegs->SRAMDebugData)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Reset                = 0x%08X", pM->ReadReg32(&pRegs->Reset)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ChDisable[0]         = 0x%08X", pM->ReadReg32(&pRegs->ChDisable[0])); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ChDisable[1]         = 0x%08X", pM->ReadReg32(&pRegs->ChDisable[1])); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "ChDisable[2]         = 0x%08X", pM->ReadReg32(&pRegs->ChDisable[2])); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "FifoBlockCnt         = 0x%08X", pM->ReadReg32(&pRegs->FifoBlockCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "InterruptWordCnt     = 0x%08X", pM->ReadReg32(&pRegs->InterruptWordCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "InterruptEventCnt    = 0x%08X", pM->ReadReg32(&pRegs->InterruptEventCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "InterruptBlockCnt    = 0x%08X", pM->ReadReg32(&pRegs->InterruptBlockCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "BusyWordCnt          = 0x%08X", pM->ReadReg32(&pRegs->BusyWordCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "BusyEventCnt         = 0x%08X", pM->ReadReg32(&pRegs->BusyEventCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "BusyBlockCnt         = 0x%08X", pM->ReadReg32(&pRegs->BusyBlockCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TriggerCtrl          = 0x%08X", pM->ReadReg32(&pRegs->TriggerCtrl)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GtpCtrl              = 0x%08X", pM->ReadReg32(&pRegs->GtpCtrl)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GtpCtrlTile0         = 0x%08X", pM->ReadReg32(&pRegs->GtpCtrlTile0)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GtpDrpCtrl           = 0x%08X", pM->ReadReg32(&pRegs->GtpDrpCtrl)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "GtpStatus            = 0x%08X", pM->ReadReg32(&pRegs->GtpStatus)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SoftErrCnt           = 0x%08X", pM->ReadReg32(&pRegs->SoftErrCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "PrbsErrCnt           = 0x%08X", pM->ReadReg32(&pRegs->PrbsErrCnt)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SwAGpio              = 0x%08X", pM->ReadReg32(&pRegs->SwAGpio)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SwBGpio              = 0x%08X", pM->ReadReg32(&pRegs->SwBGpio)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TokenInCfg           = 0x%08X", pM->ReadReg32(&pRegs->TokenInCfg)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TokenOutCfg          = 0x%08X", pM->ReadReg32(&pRegs->TokenOutCfg)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SdLinkCfg            = 0x%08X", pM->ReadReg32(&pRegs->SdLinkCfg)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "TrigOutCfg           = 0x%08X", pM->ReadReg32(&pRegs->TrigOutCfg)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "PulserPeriod         = 0x%08X", pM->ReadReg32(&pRegs->PulserPeriod)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "PulserLow            = 0x%08X", pM->ReadReg32(&pRegs->PulserLow)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "PulserNPulses        = 0x%08X", pM->ReadReg32(&pRegs->PulserNPulses)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "PulserStart          = 0x%08X", pM->ReadReg32(&pRegs->PulserStart)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "PulserStatus         = 0x%08X", pM->ReadReg32(&pRegs->PulserStatus)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "BusyScaler           = 0x%08X", pM->ReadReg32(&pRegs->BusyScaler)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "BusyCyclesScaler     = 0x%08X", pM->ReadReg32(&pRegs->BusyCyclesScaler)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "VmeClkScaler         = 0x%08X", pM->ReadReg32(&pRegs->VmeClkScaler)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "SyncScaler           = 0x%08X", pM->ReadReg32(&pRegs->SyncScaler)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Trig1Scaler          = 0x%08X", pM->ReadReg32(&pRegs->Trig1Scaler)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "Trig2Scaler          = 0x%08X", pM->ReadReg32(&pRegs->Trig2Scaler)); pTextViewMain->AddLineFast(buf);

		for(i = 0; i < 96; i++)
		{
			sprintf(buf, "Scalers[%2d]          = 0x%08X", i, pM->ReadReg32(&pRegs->Scalers[i]));
			pTextViewMain->AddLineFast(buf);
		}

		pTextViewMain->Update();
	}

private:
	
	enum
	{
		DCRB_BTN_RESET,
		DCRB_BTN_SW_SYNC,
		DCRB_BTN_UPDATE,
		DCRB_BTN_SW_TRIG,
		DCRB_BTN_CUSTOM_CFG
	};

	ModuleFrame			*pM;
	DCRB_regs			*pRegs;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameText;

	TGVerticalFrame		*pFrameLeft;
	TGVerticalFrame		*pFrameRight;

	TGTextView			*pTextViewMain;

	TGTextButton		*pButtonUpdate;
	TGTextButton		*pButtonReset;
	TGTextButton		*pButtonSWSync;
	TGTextButton		*pButtonSWTrig;
	TGTextButton		*pButtonCustomCfg;
};

#endif
