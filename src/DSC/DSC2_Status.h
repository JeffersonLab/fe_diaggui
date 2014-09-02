#ifndef DSC2_Status_H
#define DSC2_Status_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "dsc2.h"

class DSC2_Status	: public TGCompositeFrame
{
public:
	DSC2_Status(const TGWindow *p, ModuleFrame *pMFrame) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pMFrame;
		pRegs = (DSC2_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pFrameButtons->AddFrame(pButtonUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Display"), BTN_UPDATE), new TGLayoutHints(kLHintsCenterX));
				pButtonUpdate->Associate(this);

		AddFrame(pTextViewMain = new TGTextView(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		UpdateTextView();
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
					case BTN_UPDATE:
						UpdateTextView();
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

	char *GetAssyInfo()
	{
		unsigned int result, id;
		static char buf[512];
		unsigned int spiBuf[256];

		memset(buf, 0, sizeof(buf));

		pM->WriteReg32(&pRegs->calBuf[1], 0x9f);
		pM->WriteReg32(&pRegs->calBuf[0], 2);
		pM->WriteReg32(&pRegs->calCmd, 3 | 0x30000);
		pM->WriteReg32(&pRegs->calExe, 0x01);
		pM->Delay(10);

		result = pM->ReadReg32(&pRegs->calCmd);
		id = pM->ReadReg32(&pRegs->calBuf[2]) & 0xFF;

		if(result != 0xFFFFFFFF)
			sprintf(buf, "FlashId=ERROR, no response");
		else
		{
			if(id == SPIFLASH_ID_NUMONYX)	// Numonyx
			{
				pM->WriteReg32(&pRegs->calBuf[4], ((CAL_ADDR_NUMONYX+0x1F00)>>0) & 0xFF);
				pM->WriteReg32(&pRegs->calBuf[3], ((CAL_ADDR_NUMONYX+0x1F00)>>8) & 0xFF);
				pM->WriteReg32(&pRegs->calBuf[2], ((CAL_ADDR_NUMONYX+0x1F00)>>16) & 0xFF);
				pM->WriteReg32(&pRegs->calBuf[1], 0x03);
				pM->WriteReg32(&pRegs->calBuf[0], 260);
				pM->WriteReg32(&pRegs->calCmd, 3 | 0x30000);
				pM->WriteReg32(&pRegs->calExe, 0x01);
				pM->Delay(10);

				pM->BlkReadReg32(&pRegs->calBuf[5], spiBuf, 256, CRATE_MSG_FLAGS_ADRINC);

				for(int i = 0; i < 255; i++)
				{
					if(spiBuf[i] < 0x80)
						buf[i] = spiBuf[i] & 0xFF;
					else
					{
						buf[i] = 0;
						break;
					}
				}
			}
			else if(id == SPIFLASH_ID_ATMEL)	// Atmel
			{
				pM->WriteReg32(&pRegs->calBuf[4], ((CAL_ADDR_ATMEL+0x3C00)>>0) & 0xFF);
				pM->WriteReg32(&pRegs->calBuf[3], ((CAL_ADDR_ATMEL+0x3C00)>>8) & 0xFF);
				pM->WriteReg32(&pRegs->calBuf[2], ((CAL_ADDR_ATMEL+0x3C00)>>16) & 0xFF);
				pM->WriteReg32(&pRegs->calBuf[1], 0x03);
				pM->WriteReg32(&pRegs->calBuf[0], 260);
				pM->WriteReg32(&pRegs->calCmd, 3 | 0x30000);
				pM->WriteReg32(&pRegs->calExe, 0x01);
				pM->Delay(10);

				pM->BlkReadReg32(&pRegs->calBuf[5], spiBuf, 256, CRATE_MSG_FLAGS_ADRINC);

				for(int i = 0; i < 255; i++)
				{
					if(spiBuf[i] < 0x80)
						buf[i] = spiBuf[i] & 0xFF;
					else
					{
						buf[i] = 0;
						break;
					}
				}
			}
			else
				sprintf(buf, "FlashId=ERROR, unknown id 0x%02X", id);
		}
		return buf;
	}

	void UpdateTextView()
	{
		char buf[200];

		pTextViewMain->Clear();
		pTextViewMain->AddLineFast("------ DSC2 Status ------");

		sprintf(buf, "VME BaseAddress      = 0x%08lX", (long)pRegs); pTextViewMain->AddLineFast(buf);
		for(int i = 0; i < 16; i++)
		{ sprintf(buf, "threshold[%2d]        = 0x%08X", i, pM->ReadReg32(&pRegs->threshold[i])); pTextViewMain->AddLineFast(buf); }

		sprintf(buf, "pulsewidth           = 0x%08X", pM->ReadReg32(&pRegs->pulsewidth)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "chEnable             = 0x%08X", pM->ReadReg32(&pRegs->chEnable)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "orMask               = 0x%08X", pM->ReadReg32(&pRegs->orMask)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "delay                = 0x%08X", pM->ReadReg32(&pRegs->delay)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "testCtrl             = 0x%08X", pM->ReadReg32(&pRegs->testCtrl)); pTextViewMain->AddLineFast(buf);

		for(int i = 0; i < 16; i++) { sprintf(buf, "triggerScaler[%2d]    = 0x%08X", i, pM->ReadReg32(&pRegs->TrgScalerGrp1[i])); pTextViewMain->AddLineFast(buf);	}
		for(int i = 0; i < 16; i++) { sprintf(buf, "tdcScaler[%2d]        = 0x%08X", i, pM->ReadReg32(&pRegs->TdcScalerGrp1[i])); pTextViewMain->AddLineFast(buf); }
		for(int i = 0; i < 16; i++) { sprintf(buf, "triggerVmeScaler[%2d] = 0x%08X", i, pM->ReadReg32(&pRegs->TrgScalerGrp2[i])); pTextViewMain->AddLineFast(buf); }
		for(int i = 0; i < 16; i++) { sprintf(buf, "tdcVmeScaler[%2d]     = 0x%08X", i, pM->ReadReg32(&pRegs->TdcScalerGrp2[i])); pTextViewMain->AddLineFast(buf); }

		sprintf(buf, "refVmeScaler         = 0x%08X", pM->ReadReg32(&pRegs->refScalerGrp2)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "refGatedScaler       = 0x%08X", pM->ReadReg32(&pRegs->refScalerGrp1)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "firmwareRev          = 0x%08X", pM->ReadReg32(&pRegs->firmwareRev)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "boardID              = 0x%08X", pM->ReadReg32(&pRegs->boardID)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "serialNum            = %u", pM->ReadReg32(&pRegs->SerialNum)); pTextViewMain->AddLineFast(buf);
		sprintf(buf, "mfgId                = 0x%08X", pM->ReadReg32(&pRegs->SerialMfg)); pTextViewMain->AddLineFast(buf);

		sprintf(buf, "Assembly Information: %s", GetAssyInfo()); pTextViewMain->AddLineFast(buf);
		
		pTextViewMain->Update();
	}

private:
	
	enum Buttons
	{
		BTN_UPDATE
	};
	
	ModuleFrame			*pM;
	DSC2_regs			*pRegs;

	TGHorizontalFrame	*pFrameButtons;

	TGTextView			*pTextViewMain;

	TGTextButton		*pButtonUpdate;
};

#endif
