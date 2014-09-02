#ifndef GTP_Trigger_H
#define GTP_Trigger_H

#include <stdlib.h>
#include "RootHeader.h"
#include "gtp.h"
#include "VMERemote.h"

#define BTN_RESET		100
#define BTN_SW_SYNC		101
#define BTN_UPDATE		102
#define BTN_TRIG_SETUP	103

#define CMB_TRIG_S_BASE	200
#define CMB_ID_TRIG_S0	200
#define CMB_ID_TRIG_S1	201
#define CMB_ID_TRIG_S2	202
#define CMB_ID_TRIG_S3	203
#define CMB_ID_TRIG_S4	204
#define CMB_ID_TRIG_S5	205
#define CMB_ID_TRIG_S6	206
#define CMB_ID_TRIG_S7	207

#define CMB_ID_TRIG_D0	300
#define CMB_ID_TRIG_D1	301
#define CMB_ID_TRIG_D2	302
#define CMB_ID_TRIG_D3	303
#define CMB_ID_TRIG_D4	304
#define CMB_ID_TRIG_D5	305
#define CMB_ID_TRIG_D6	306
#define CMB_ID_TRIG_D7	307
#define CMB_ID_TRIG_D8	308
#define CMB_ID_TRIG_D9	309
#define CMB_ID_TRIG_D10	310
#define CMB_ID_TRIG_D11	311
#define CMB_ID_TRIG_D12	312
#define CMB_ID_TRIG_D13	313
#define CMB_ID_TRIG_D14	314
#define CMB_ID_TRIG_D15	315

#define CHK_TEST		400

#define CMB_ID_THRESH_D0	500
#define CMB_ID_THRESH_D1	501
#define CMB_ID_THRESH_D2	502
#define CMB_ID_THRESH_D3	503
#define CMB_ID_THRESH_D4	504
#define CMB_ID_THRESH_D5	505
#define CMB_ID_THRESH_D6	506
#define CMB_ID_THRESH_D7	507
#define CMB_ID_THRESH_D8	508
#define CMB_ID_THRESH_D9	509
#define CMB_ID_THRESH_D10	510
#define CMB_ID_THRESH_D11	511
#define CMB_ID_THRESH_D12	512
#define CMB_ID_THRESH_D13	513
#define CMB_ID_THRESH_D14	514
#define CMB_ID_THRESH_D15	515

class GTP_Trigger	: public TGCompositeFrame
{
 public:
  GTP_Trigger(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr) 
    : TGCompositeFrame(p, 400, 400)
    {
      SetLayoutManager(new TGVerticalLayout(this));

      pVMEClient = pClient;
      pGTPregs = (GTP_regs *)baseAddr;
	  TGCompositeFrame *pGroup1;
	  TGCompositeFrame *pHF1;
	  TGCanvas *pCanvas;


	  // Top Buttons
      AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
		pFrameButtons->AddFrame(pButtonUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Display"), BTN_UPDATE), new TGLayoutHints(kLHintsCenterX));
//		pFrameButtons->AddFrame(pButtonReset = new TGTextButton(pFrameButtons, new TGHotString("Reset"), BTN_RESET), new TGLayoutHints(kLHintsCenterX));
		pFrameButtons->AddFrame(pButtonTrigSetup = new TGTextButton(pFrameButtons, new TGHotString("Trigger Config"), BTN_TRIG_SETUP), new TGLayoutHints(kLHintsCenterX));
		pFrameButtons->AddFrame(pTestEnable = new TGCheckButton(pFrameButtons, new TGHotString("Test Enable"), CHK_TEST), new TGLayoutHints(kLHintsCenterX));

	AddFrame(pFrameMain = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		// Equation Delays Left
		pFrameMain->AddFrame(pCanvas = new TGCanvas(pFrameMain), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvas->SetContainer(pFrameLeft = new TGVerticalFrame(pCanvas->GetViewPort(), 10, 10));
			char combine[32], trig_num[4];
			for(int i=0; i<16; i++)
			{
				strcpy(combine,"Equation "); itoa(i+1,trig_num,10); strcat(combine,trig_num);
				pFrameLeft->AddFrame(pGroup1 = new TGGroupFrame(pFrameLeft, combine, kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
					pGroup1->AddFrame(pHF1 = new TGHorizontalFrame(pGroup1), new TGLayoutHints(kLHintsExpandX));
						pHF1->AddFrame(new TGLabel(pHF1, new TGString("Delay (4ns): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pHF1->AddFrame(pDelay[i] = new TGHSlider(pHF1, 150, kSlider1 | kScaleDownRight, CMB_ID_TRIG_D0 + i), new TGLayoutHints(kLHintsRight));
							pDelay[i]->SetRange(0,255);
					pGroup1->AddFrame(pHF1 = new TGHorizontalFrame(pGroup1), new TGLayoutHints(kLHintsExpandX));
						pHF1->AddFrame(new TGLabel(pHF1, new TGString("Threshold: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pHF1->AddFrame(pTrigThres[i] = new TGHSlider(pHF1, 150, kSlider1 | kScaleDownRight, CMB_ID_THRESH_D0 + i), new TGLayoutHints(kLHintsRight));
							pTrigThres[i]->SetRange(0,65535);
			}

		// Trigger Outputs Right
		pFrameMain->AddFrame(pCanvas = new TGCanvas(pFrameMain), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvas->SetContainer(pFrameRight = new TGVerticalFrame(pCanvas->GetViewPort(), 10, 10));
			for(int i=0; i<32; i++)
			{
				strcpy(combine,"Trigger Output "); itoa(i+1,trig_num,10); strcat(combine,trig_num);
				pFrameRight->AddFrame(pGroup1 = new TGGroupFrame(pFrameRight, combine , kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
					pGroup1->AddFrame(pHF1 = new TGHorizontalFrame(pGroup1), new TGLayoutHints(kLHintsExpandX));
						pHF1->AddFrame(new TGLabel(pHF1, new TGString("Source: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pHF1->AddFrame(pTrig[i] = new TGComboBox(pHF1, CMB_TRIG_S_BASE + i), new TGLayoutHints(kLHintsRight));
							pTrig[i]->Resize(150,24);
							pTrig[i]->AddEntry("Disable",CFG_TRIG_SOURCE_DIS);
							pTrig[i]->AddEntry("Clock",CFG_TRIG_SOURCE_CLK);
							pTrig[i]->AddEntry("Fiber Trigger Out",CFG_TRIG_SOURCE_FIB);
							pTrig[i]->AddEntry("Equation A",CFG_TRIG_SOURCE_EQA);
							pTrig[i]->AddEntry("Equation B",CFG_TRIG_SOURCE_EQB);
							pTrig[i]->AddEntry("Equation C",CFG_TRIG_SOURCE_EQC);
							pTrig[i]->AddEntry("Equation D",CFG_TRIG_SOURCE_EQD);
							pTrig[i]->AddEntry("Equation E",CFG_TRIG_SOURCE_EQE);
							pTrig[i]->AddEntry("Equation F",CFG_TRIG_SOURCE_EQF);
							pTrig[i]->AddEntry("Equation G",CFG_TRIG_SOURCE_EQG);
							pTrig[i]->AddEntry("Equation H",CFG_TRIG_SOURCE_EQH);
							pTrig[i]->AddEntry("Equation I",CFG_TRIG_SOURCE_EQI);
							pTrig[i]->AddEntry("Equation J",CFG_TRIG_SOURCE_EQJ);
							pTrig[i]->AddEntry("Equation K",CFG_TRIG_SOURCE_EQK);
							pTrig[i]->AddEntry("Equation L",CFG_TRIG_SOURCE_EQL);
							pTrig[i]->AddEntry("Equation M",CFG_TRIG_SOURCE_EQM);
							pTrig[i]->AddEntry("Equation N",CFG_TRIG_SOURCE_EQN);
							pTrig[i]->AddEntry("Equation O",CFG_TRIG_SOURCE_EQO);
							pTrig[i]->AddEntry("Equation P",CFG_TRIG_SOURCE_EQP);
							pTrig[i]->AddEntry("Trig 1 In", CFG_TRIG_SOURCE_TR1);
			}


//		pButtonUpdate->Associate(this);

		ReadSettings();

		pButtonUpdate->Associate(this);
		pButtonTrigSetup->Associate(this);
		pTestEnable->Associate(this);

		for(int i=0; i<32; i++)
			pTrig[i]->Associate(this);

		for(int i=0; i<16; i++)
		{
			pDelay[i]->Associate(this);
			pTrigThres[i]->Associate(this);
		}


    }


	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		unsigned int val, temp, ls_16=0, ms_16=0;

		printf("command %d, %d, %d\n",GET_MSG(msg), GET_SUBMSG(msg), parm1);

		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_CHECKBUTTON:
				switch(parm1)
				{
				case CHK_TEST:
					if (pTestEnable->IsDown())
						pVMEClient->WriteVME32((unsigned int)&pGTPregs->test_trig_en, 0x0001);
					else
						pVMEClient->WriteVME32((unsigned int)&pGTPregs->test_trig_en, 0x0000);
					break;
				default:
					break;
				}
			case kCM_COMBOBOX:
				switch(parm1)
				{
				case CHK_TEST:
					break;
				default:
					// trigger sources 0-31
					val = parm1 - CMB_TRIG_S_BASE;
					pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_source[val], pTrig[val]->GetSelected());
					break;
				}
			case kCM_BUTTON:
				switch(parm1)
				{
				case BTN_UPDATE:
					ReadSettings();
					break;
				case BTN_TRIG_SETUP:
					pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig1_csr, CFG_TRIG_SWB);
					pVMEClient->WriteVME32((unsigned int)&pGTPregs->clk250_stat,CFG_CLK_SWB);
					for(int i=0; i<32; i++)
						pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_source[i], CFG_TRIG_SOURCE_EQG);

					pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_source[0], CFG_TRIG_SOURCE_CLK);
					pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_source[16], CFG_TRIG_SOURCE_CLK);

					// vme slot 16
					pVMEClient->WriteVME32((unsigned int)&pGTPregs->enable_payload0, 0x0800);

					pVMEClient->WriteVME32((unsigned int)&pGTPregs->test_trig_en, 0x0000);

					pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[13], 0x2100);
					pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[12], 0x0);

					ReadSettings();
					break;
				}
			}
			break;
		case kC_HSLIDER:
			switch(parm1)
			{
			case CMB_ID_TRIG_D0:
				printf("slider id %d\n", (int)parm1);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[0], pDelay[0]->GetPosition());
				break;
			case CMB_ID_TRIG_D1:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[1], pDelay[1]->GetPosition());
				break;
			case CMB_ID_TRIG_D2:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[2], pDelay[2]->GetPosition());
				break;
			case CMB_ID_TRIG_D3:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[3], pDelay[3]->GetPosition());
				break;
			case CMB_ID_TRIG_D4:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[4], pDelay[4]->GetPosition());
				break;
			case CMB_ID_TRIG_D5:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[5], pDelay[5]->GetPosition());
				break;
			case CMB_ID_TRIG_D6:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[6], pDelay[6]->GetPosition());
				break;
			case CMB_ID_TRIG_D7:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[7], pDelay[7]->GetPosition());
				break;
			case CMB_ID_TRIG_D8:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[8], pDelay[8]->GetPosition());
				break;
			case CMB_ID_TRIG_D9:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[9], pDelay[9]->GetPosition());
				break;
			case CMB_ID_TRIG_D10:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[10], pDelay[10]->GetPosition());
				break;
			case CMB_ID_TRIG_D11:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[11], pDelay[11]->GetPosition());
				break;
			case CMB_ID_TRIG_D12:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[12], pDelay[12]->GetPosition());
				break;
			case CMB_ID_TRIG_D13:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[13], pDelay[13]->GetPosition());
				break;
			case CMB_ID_TRIG_D14:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[14], pDelay[14]->GetPosition());
				break;
			case CMB_ID_TRIG_D15:
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_delay[15], pDelay[15]->GetPosition());
				break;

			case CMB_ID_THRESH_D0:
				temp = pTrigThres[0]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[1], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[0], ls_16);
				break;
			case CMB_ID_THRESH_D1:
				temp = pTrigThres[1]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[3], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[2], ls_16);
				break;
			case CMB_ID_THRESH_D2:
				temp = pTrigThres[2]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[5], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[4], ls_16);
				break;
			case CMB_ID_THRESH_D3:
				temp = pTrigThres[3]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[7], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[6], ls_16);
				break;
			case CMB_ID_THRESH_D4:
				temp = pTrigThres[4]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[9], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[8], ls_16);
				break;
			case CMB_ID_THRESH_D5:
				temp = pTrigThres[5]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[11], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[10], ls_16);
				break;
			case CMB_ID_THRESH_D6:
				temp = pTrigThres[6]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[13], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[12], ls_16);
				break;
			case CMB_ID_THRESH_D7:
				temp = pTrigThres[7]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[15], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[14], ls_16);
				break;
			case CMB_ID_THRESH_D8:
				temp = pTrigThres[8]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[17], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[16], ls_16);
				break;
			case CMB_ID_THRESH_D9:
				temp = pTrigThres[9]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[19], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[18], ls_16);
				break;
			case CMB_ID_THRESH_D10:
				temp = pTrigThres[10]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[21], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[20], ls_16);
				break;
			case CMB_ID_THRESH_D11:
				temp = pTrigThres[11]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[23], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[22], ls_16);
				break;
			case CMB_ID_THRESH_D12:
				temp = pTrigThres[12]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[25], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[24], ls_16);
				break;
			case CMB_ID_THRESH_D13:
				temp = pTrigThres[13]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[27], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[26], ls_16);
				break;
			case CMB_ID_THRESH_D14:
				temp = pTrigThres[14]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[29], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[28], ls_16);
				break;
			case CMB_ID_THRESH_D15:
				temp = pTrigThres[15]->GetPosition();

				for(int i=0; i<8; i++)
				{
					ms_16 += (unsigned int)pow(2.0,2*i+1) *((temp >> 8+i) % 2);
					ms_16 += (unsigned int)pow(2.0,2*i)   *((temp >> 8+i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i+1) *((temp >>   i) % 2);
					ls_16 += (unsigned int)pow(2.0,2*i)   *((temp >>   i) % 2);
				}
				
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[31], ms_16);
				pVMEClient->WriteVME32((unsigned int)&pGTPregs->trig_thresh[30], ls_16);
				break;
			}
		}
	return kTRUE;
	}


	void ReadSettings()
	{
		unsigned int val;

		for(int i = 0; i < 32; i++)
		{
			pVMEClient->ReadVME32((unsigned int)&pGTPregs->trig_source[i], &val);
			pTrig[i]->Select(val,kFALSE);
		}

		for(int i = 0; i < 16; i++)
		{
			pVMEClient->ReadVME32((unsigned int)&pGTPregs->trig_delay[i], &val);
			pDelay[i]->SetPosition(val);

			pVMEClient->ReadVME32((unsigned int)&pGTPregs->trig_thresh[i], &val);
			pTrigThres[i]->SetPosition(val);
		}

		pVMEClient->ReadVME32((unsigned int)&pGTPregs->test_trig_en, &val);
		if(val & FIBER_MODULE_ENABLE)
			pTestEnable->SetOn(kTRUE);
		else
			pTestEnable->SetOn(kFALSE);
	}


 private:
	VMERemote			*pVMEClient;
	GTP_regs			*pGTPregs;

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameMain;

	TGVerticalFrame		*pFrameLeft;
	TGVerticalFrame		*pFrameRight;

	TGComboBox			*pTrig[32];
	TGHSlider			*pTrigThres[16];
	TGHSlider			*pDelay[16];

	TGTextButton		*pButtonUpdate;
	TGTextButton		*pButtonReset;
	TGTextButton		*pButtonTrigSetup;

	TGCheckButton		*pTestEnable;
/*     TGTextButton		*pButtonSWSync; */
};

#endif
