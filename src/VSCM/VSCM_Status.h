#ifndef VSCM_Status_H
#define VSCM_Status_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "vscm.h"

class VSCM_Status	: public TGCompositeFrame
{
public:
	VSCM_Status(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (VSCM_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pTF1->AddFrame(pButtonUpdate = new TGTextButton(pTF1, new TGHotString("Update Display"), BTN_UPDATE), new TGLayoutHints(kLHintsCenterX));
			pTF1->AddFrame(pButtonReset = new TGTextButton(pTF1, new TGHotString("Reset"), BTN_RESET), new TGLayoutHints(kLHintsCenterX));
			pTF1->AddFrame(pButtonSWSync = new TGTextButton(pTF1, new TGHotString("Sync"), BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX));

		AddFrame(pTextViewMainFPGA = new TGTextView(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		pButtonUpdate->Associate(this);
		pButtonReset->Associate(this);
		pButtonSWSync->Associate(this);

		strSerialNumber = GetSerialNumber();
		iDacCal = GetDacCalibration();

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
					case BTN_RESET:
					{
//						unsigned int r = ReadReg32(&pSSPregs->Config);
//						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r | CFG_RESET);
//						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r);
						break;
					}
					case BTN_SW_SYNC:
					{
//						unsigned int r = ReadReg32(&pSSPregs->Config);
//						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r | CFG_SYNC_SW);
//						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r);
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
	
	void SpiFlashSelect(int sel)
	{
		if(sel)
			pM->WriteReg32(&pRegs->SpiFlash, 0x0);
		else
			pM->WriteReg32(&pRegs->SpiFlash, 0x4);
	}

	unsigned char SpiFlashTransferByte(unsigned char data)
	{
		int i;
		unsigned char rsp = 0;
		for(i = 0; i < 8; i++)
		{
			pM->WriteReg32(&pRegs->SpiFlash, ((data>>7)&0x1));
			rsp = (rsp<<1) | (pM->ReadReg32(&pRegs->SpiFlash) & 0x1);
			pM->WriteReg32(&pRegs->SpiFlash, 0x2|((data>>7)&0x1));
			data<<=1;
		}
		return rsp;
	}

	TString GetSerialNumber()
	{
		char buf[100];

		SpiFlashSelect(0);
		SpiFlashSelect(1);

		SpiFlashTransferByte(0x03);	// Read Continuous
		SpiFlashTransferByte(0x7F);
		SpiFlashTransferByte(0xF0);
		SpiFlashTransferByte(0x00);

		memset(buf, 0, sizeof(buf));
		for(unsigned int i = 0; i < sizeof(buf); i++)
		{
			buf[i] = SpiFlashTransferByte(0xFF);
			if(buf[i] == 0x0)
				break;
			if(buf[i] == 0xFF)
			{
				buf[0] = 'e';
				buf[1] = 'r';
				buf[2] = 'r';
				buf[3] = 'o';
				buf[4] = 'r';
				buf[5] = 0x0;
				break;
			}
		}
		SpiFlashSelect(0);

		TString result(buf);
		return result;
	}

	unsigned char GetDacCalibration()
	{
		unsigned char result;

		SpiFlashSelect(0);
		SpiFlashSelect(1);

		SpiFlashTransferByte(0x03);	// Read Continuous
		SpiFlashTransferByte(0x7F);
		SpiFlashTransferByte(0xF0);
		SpiFlashTransferByte(0x80);
		result = SpiFlashTransferByte(0xFF);
		SpiFlashSelect(0);

		// Do this to load calibration value into DAC:
		// pM->WriteReg32(&pRegs->DacCfg, (0<<16) | 0x80000D00 | (result & 0x3F));

		return result;
	}

	int GetSlot()
	{
		return pM->ReadReg32(&pRegs->Geo) & 0x1F;
	}

	void UpdateTextView()
	{
		char buf[100];

		pTextViewMainFPGA->Clear();
		pTextViewMainFPGA->AddLineFast("------ VSCM Main FPGA Status ------");

		sprintf(buf, "Serial Number    = %s", strSerialNumber.Data()); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "DAC Calibration  = %d", iDacCal); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "VME BaseAddress  = 0x%08lX", (long)pRegs); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "Firmware Rev     = 0x%08X", pM->ReadReg32(&pRegs->FirmwareRev)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "BoardId          = 0x%08X", pM->ReadReg32(&pRegs->BoardId)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "SpiFlash         = 0x%08X", pM->ReadReg32(&pRegs->SpiFlash)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "BlockCfg         = 0x%08X", pM->ReadReg32(&pRegs->BlockCfg)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "ClockCfg         = 0x%08X", pM->ReadReg32(&pRegs->ClockCfg)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "TrigBusyThr      = 0x%08X", pM->ReadReg32(&pRegs->TrigBusyThr)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "TrigSrc          = 0x%08X", pM->ReadReg32(&pRegs->TrigSrc)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "AD32             = 0x%08X", pM->ReadReg32(&pRegs->AD32)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "Interrupt        = 0x%08X", pM->ReadReg32(&pRegs->Interrupt)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "InterruptAck     = 0x%08X", pM->ReadReg32(&pRegs->InterruptAck)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "Geo              = 0x%08X", pM->ReadReg32(&pRegs->Geo)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FifoWordCnt      = 0x%08X", pM->ReadReg32(&pRegs->FifoWordCnt)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FifoEventCnt     = 0x%08X", pM->ReadReg32(&pRegs->FifoEventCnt)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "ReadoutCfg       = 0x%08X", pM->ReadReg32(&pRegs->ReadoutCfg)); pTextViewMainFPGA->AddLineFast(buf);
//		sprintf(buf, "SramDbgAdr       = 0x%08X", pM->ReadReg32(&pRegs->SramDbgAdr)); pTextViewMainFPGA->AddLineFast(buf);
//		sprintf(buf, "SramDbgData      = 0x%08X", pM->ReadReg32(&pRegs->SramDbgData)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "Reset            = 0x%08X", pM->ReadReg32(&pRegs->Reset)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrClkCfg       = 0x%08X", pM->ReadReg32(&pRegs->FssrClkCfg)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "ScalerLatch      = 0x%08X", pM->ReadReg32(&pRegs->ScalerLatch)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrSerCfg       = 0x%08X", pM->ReadReg32(&pRegs->FssrSerCfg)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrSerData[0]   = 0x%08X", pM->ReadReg32(&pRegs->FssrSerData[0])); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrSerData[1]   = 0x%08X", pM->ReadReg32(&pRegs->FssrSerData[1])); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrSerData[2]   = 0x%08X", pM->ReadReg32(&pRegs->FssrSerData[2])); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrSerData[3]   = 0x%08X", pM->ReadReg32(&pRegs->FssrSerData[3])); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "DacCfg           = 0x%08X", pM->ReadReg32(&pRegs->DacCfg)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "DacCh0           = 0x%08X", pM->ReadReg32(&pRegs->DacCh0)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "DacCh1           = 0x%08X", pM->ReadReg32(&pRegs->DacCh1)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrSerClk       = 0x%08X", pM->ReadReg32(&pRegs->FssrSerClk)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrAddrH1       = 0x%08X", pM->ReadReg32(&pRegs->FssrAddrH1)); pTextViewMainFPGA->AddLineFast(buf);
		sprintf(buf, "FssrAddrH2       = 0x%08X", pM->ReadReg32(&pRegs->FssrAddrH2)); pTextViewMainFPGA->AddLineFast(buf);

		pTextViewMainFPGA->Update();
	}

private:

	enum Buttons
	{
		BTN_RESET,
		BTN_SW_SYNC,
		BTN_UPDATE
	};
	
	TString				strSerialNumber;

	int					iDacCal;

	ModuleFrame			*pM;
	VSCM_regs			*pRegs;

	TGTextView			*pTextViewMainFPGA;

	TGTextButton		*pButtonUpdate;
	TGTextButton		*pButtonReset;
	TGTextButton		*pButtonSWSync;

	unsigned int		Mode;
};

#endif
