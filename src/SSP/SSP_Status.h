#ifndef SSP_Status_H
#define SSP_Status_H

#include <stdlib.h>
#include "ModuleFrame.h"
#include "RootHeader.h"
#include "ssp.h"

class SSP_Status	: public TGCompositeFrame
{
public:
	SSP_Status(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (SSP_regs *)pM->BaseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pFrameButtons->AddFrame(pButtonUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Display"), BTN_UPDATE), new TGLayoutHints(kLHintsCenterX));
			pFrameButtons->AddFrame(pButtonReset = new TGTextButton(pFrameButtons, new TGHotString("Reset"), BTN_RESET), new TGLayoutHints(kLHintsCenterX));
			pFrameButtons->AddFrame(pButtonSWSync = new TGTextButton(pFrameButtons, new TGHotString("Sync"), BTN_SW_SYNC), new TGLayoutHints(kLHintsCenterX));
			pFrameButtons->AddFrame(pButtonCustomConfig = new TGTextButton(pFrameButtons, new TGHotString("CustomConfig"), BTN_CUSTOM_CONFIG), new TGLayoutHints(kLHintsCenterX));

		AddFrame(pFrameText = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameText->AddFrame(pTextViewFPGA = new TGTextView(pFrameText), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		pButtonUpdate->Associate(this);
		pButtonReset->Associate(this);
		pButtonSWSync->Associate(this);
		pButtonCustomConfig->Associate(this);

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
						//unsigned int r = ReadReg32(&pSSPregs->Config);
						//pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r | CFG_RESET);
						//pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r);
						break;
					}
					case BTN_SW_SYNC:
					{
						unsigned int result = pM->ReadReg32((volatile unsigned int *)0x100);
						printf("pM->ReadReg32(0x100) = 0x%08X\n", result);

						result = pM->ReadReg32((volatile unsigned int *)0x0);
						printf("pM->ReadReg32(0x0) = 0x%08X\n", result);
						//unsigned int r = ReadReg32(&pSSPregs->Config);
						//pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r | CFG_SYNC_SW);
						//pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, r);
						break;
					}
					case BTN_CUSTOM_CONFIG:
					{
						pM->WriteReg32(&pRegs->Clk.Ctrl, CLK_CTRL_GCLKRST | (SSP_CLKSRC_SWB<<24) | (SSP_CLKSRC_SWB<<26));
						pM->WriteReg32(&pRegs->Clk.Ctrl, (SSP_CLKSRC_SWB<<24) | (SSP_CLKSRC_SWB<<26));

						for(int i = 0; i < 10; i++)
							pM->WriteReg32(&pRegs->Ser[i].Ctrl, SSP_SER_CTRL_ERRCNT_EN);
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

		pTextViewFPGA->Clear();
		
		TString t;
		pTextViewFPGA->AddLineFast(t.Format("%-35s = 0x%08lX", "VMEBaseAddr", (long)pRegs));
		pTextViewFPGA->AddLineFast("");

		SPFREG(buf, &pRegs, Cfg.BoardId);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Cfg.FirmwareRev);	pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Clk.Ctrl);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Clk.Status);	pTextViewFPGA->AddLineFast(buf);
		
		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_LVDSOUT0]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_LVDSOUT1]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_LVDSOUT2]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_LVDSOUT3]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_LVDSOUT4]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_GPIO0]);				pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_GPIO1]);				pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT0]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT1]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT2]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT3]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT4]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT5]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT6]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.SrcSel[SD_SRC_P2_LVDSOUT7]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.PulserPeriod);							pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.PulserLowCycles);						pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.PulserNPulses);							pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.PulserDone);								pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_SYSCLK]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_GCLK]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_SYNC]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_TRIG1]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_TRIG2]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_GPIO0]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_GPIO1]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSIN0]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSIN1]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSIN2]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSIN3]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSIN4]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSOUT0]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSOUT1]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSOUT2]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSOUT3]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_LVDSOUT4]);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_BUSY]);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_BUSYCYCLES]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN0]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN1]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN2]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN3]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN4]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN5]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN6]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSIN7]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT0]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT1]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT2]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT3]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT4]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT5]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT6]);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Sd.Scalers[SD_SCALER_P2_LVDSOUT7]);	pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Trg.Ctrl);				pTextViewFPGA->AddLineFast(buf);
//		SPFREG(buf, &pRegs, Trg.SumHistCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Trg.SumHistThr);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Trg.SumHistWindow);	pTextViewFPGA->AddLineFast(buf);
//		SPFREG(buf, &pRegs, Trg.SumHistGain);		pTextViewFPGA->AddLineFast(buf);
//		SPFREG(buf, &pRegs, Trg.SumHistTime);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER0].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER1].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER2].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER3].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER4].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER5].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER6].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_FIBER7].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].Ctrl);				pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].CtrlTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].CtrlTile1);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].DrpCtrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].Status);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].DrpStatus);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXS0].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->AddLineFast("");
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].Ctrl);			pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].CtrlTile0);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].CtrlTile1);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].DrpCtrl);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].Status);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].DrpStatus);	pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].ErrTile0);		pTextViewFPGA->AddLineFast(buf);
		SPFREG(buf, &pRegs, Ser[SSP_SER_VXSGTP].ErrTile1);		pTextViewFPGA->AddLineFast(buf);

		pTextViewFPGA->Update();
	}

private:

	enum Buttons
	{
		BTN_RESET,
		BTN_SW_SYNC,
		BTN_UPDATE,
		BTN_CUSTOM_CONFIG
	};
	
	ModuleFrame			*pM;
	SSP_regs				*pRegs;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameText;

	TGTextView			*pTextViewFPGA;

	TGTextButton		*pButtonUpdate;
	TGTextButton		*pButtonReset;
	TGTextButton		*pButtonSWSync;
	TGTextButton		*pButtonCustomConfig;
};

#endif
