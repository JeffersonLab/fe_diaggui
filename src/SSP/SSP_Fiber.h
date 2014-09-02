#ifndef SSP_Fiber_H
#define SSP_Fiber_H

#include "RootHeader.h"
#include "ssp.h"

#define GTX_VXS			0
#define GTX_FIB			1

#define SSP_FIBER_DEBUG	0

#define GTX_LANE0		0
#define GTX_LANE1		1
#define GTX_LANE2		2
#define GTX_LANE3		3
#define GTX_TPOL0		0
#define GTX_TPOL1		1
#define GTX_RPOL0		0
#define GTX_RPOL1		1

typedef struct
{
	unsigned int Lane[4];			// Lane 0 - 3
	unsigned int TxPolarity[4];		// 0-normal, 1-inverted
	unsigned int RxPolarity[4];		// 0-normal, 1-inverted
} FiberMapping;

FiberMapping FiberMaps[] = {
		{	// Fiber 0 Mapping
			{GTX_LANE3, GTX_LANE0, GTX_LANE2, GTX_LANE1},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 1 Mapping
			{GTX_LANE3, GTX_LANE0, GTX_LANE2, GTX_LANE1},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 2 Mapping
			{GTX_LANE3, GTX_LANE0, GTX_LANE2, GTX_LANE1},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 3 Mapping
			{GTX_LANE3, GTX_LANE0, GTX_LANE2, GTX_LANE1},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 4 Mapping
			{GTX_LANE0, GTX_LANE3, GTX_LANE1, GTX_LANE2},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 5 Mapping
			{GTX_LANE0, GTX_LANE3, GTX_LANE1, GTX_LANE2},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 6 Mapping
			{GTX_LANE0, GTX_LANE3, GTX_LANE1, GTX_LANE2},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 7 Mapping
			{GTX_LANE2, GTX_LANE1, GTX_LANE3, GTX_LANE0},
			{GTX_TPOL1, GTX_TPOL0, GTX_TPOL1, GTX_TPOL0},
			{GTX_RPOL1, GTX_RPOL0, GTX_RPOL0, GTX_RPOL1}
		},
		{	// Fiber 8 Mapping
			{GTX_LANE0, GTX_LANE1, GTX_LANE2, GTX_LANE3},
			{GTX_TPOL0, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL0, GTX_RPOL0, GTX_RPOL0, GTX_RPOL0}
		},
		{	// Fiber 9 Mapping
			{GTX_LANE0, GTX_LANE1, GTX_LANE2, GTX_LANE3},
			{GTX_TPOL0, GTX_TPOL0, GTX_TPOL0, GTX_TPOL0},
			{GTX_RPOL0, GTX_RPOL0, GTX_RPOL0, GTX_RPOL0}
		}
	};

#define SSP_FIBER_SWEEP_TIMER_CHECK		50

class SSP_Fiber	: public TGCompositeFrame
{
public:
	SSP_Fiber(const TGWindow *p, ModuleFrame *pModule, int mode, int idx) : TGCompositeFrame(p, 400, 400)
	{
		char buf[100];

		pM = pModule;
		pRegs = (SSP_regs *)pM->BaseAddr;
		Idx = idx;
		Mode = mode;

		if(Mode == GTX_VXS)
			GtxCount = 2;
		else
			GtxCount = 4;

		SetLayoutManager(new TGVerticalLayout(this));

		TGCompositeFrame *pF1, *pF2, *pF3, *pF4;
		
		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pF1->AddFrame(pButtonGtxEnable = new TGTextButton(pF1, new TGHotString("GTX Enabled"), BTN_GTXENABLE), new TGLayoutHints(kLHintsCenterX));
				pButtonGtxEnable->AllowStayDown(kTRUE);
				pButtonGtxEnable->SetWidth(150);
				pButtonGtxEnable->Associate(this);

			pF1->AddFrame(pButtonGtxReset = new TGTextButton(pF1, new TGHotString("GTX Reset"), BTN_GTXRESET), new TGLayoutHints(kLHintsCenterX));
				pButtonGtxReset->AllowStayDown(kTRUE);
				pButtonGtxReset->SetWidth(150);
				pButtonGtxReset->Associate(this);

			pF1->AddFrame(pButtonLinkReset = new TGTextButton(pF1, new TGHotString("Link Reset"), BTN_LINKRESET), new TGLayoutHints(kLHintsCenterX));
				pButtonLinkReset->AllowStayDown(kTRUE);
				pButtonLinkReset->SetWidth(150);
				pButtonLinkReset->Associate(this);

			pF1->AddFrame(pButtonSweep = new TGTextButton(pF1, new TGHotString("Sweep Start"), BTN_SWEEP), new TGLayoutHints(kLHintsCenterX));
				pButtonSweep->SetWidth(150);
				pButtonSweep->AllowStayDown(kTRUE);
				pButtonSweep->Associate(this);

			pF1->AddFrame(pButtonStatus = new TGTextButton(pF1, new TGHotString("Status Update"), BTN_STATUS), new TGLayoutHints(kLHintsCenterX));
				pButtonStatus->SetWidth(150);
				pButtonStatus->Associate(this);

			pF1->AddFrame(pButtonSetupDefaults = new TGTextButton(pF1, new TGHotString("Setup Defaults"), BTN_SETUPDEFAULT), new TGLayoutHints(kLHintsCenterX));
				pButtonSetupDefaults->SetWidth(150);
				pButtonSetupDefaults->Associate(this);

		AddFrame(pF1 = new TGVerticalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

			if(Mode == GTX_VXS)
				sprintf(buf, "VXS %d BER", Idx);
			else
				sprintf(buf, "Fiber %d BER", Idx);

			pF1->AddFrame(pCanvasFiberBer = new TRootEmbeddedCanvas(buf, pF1, 100, 200), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pMultiGraphFiberBer = new TMultiGraph;

				if(Mode == GTX_VXS)
					sprintf(buf, "VXS %d BER;Eye Position;BER", Idx);
				else
					sprintf(buf, "Fiber %d BER;Eye Position;BER", Idx);

				pMultiGraphFiberBer->SetTitle(buf);

				for(int i = 0; i < GtxCount; i++)
				{
					pGraphFiberBer[i] = new TGraph(128);

					for(int j = 0; j < 128; j++)
						pGraphFiberBer[i]->SetPoint(j, j, 1.0);

					pGraphFiberBer[i]->SetLineColor(i+1);
					pGraphFiberBer[i]->SetLineWidth(2);
					sprintf(buf, "Lane %d", i);
					pGraphFiberBer[i]->SetTitle(buf);
					pMultiGraphFiberBer->Add(pGraphFiberBer[i]);
				}
				pCanvasFiberBer->GetCanvas()->cd();
				pCanvasFiberBer->GetCanvas()->SetBorderMode(0);
				pCanvasFiberBer->GetCanvas()->SetLogy();
				pMultiGraphFiberBer->Draw("AL");
				pMultiGraphFiberBer->GetXaxis()->SetRangeUser(0.0, 128.0);
				pMultiGraphFiberBer->GetXaxis()->CenterTitle();
				pMultiGraphFiberBer->GetYaxis()->SetRangeUser(1.0E-15, 1.0);
				pMultiGraphFiberBer->GetYaxis()->CenterTitle();
				pCanvasFiberBer->GetCanvas()->BuildLegend(0.7, 0.7, 0.9, 0.9);

		TGCanvas *pC1;
		AddFrame(pC1 = new TGCanvas(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pC1->SetContainer(pF1 = new TGVerticalFrame(pC1->GetViewPort(), 10, 10));
			pC1->SetScrolling(TGCanvas::kCanvasScrollVertical);

			pF1->AddFrame(pF2 = new TGGroupFrame(pF1, "Common Lane Settings", kHorizontalFrame), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(pF3 = new TGVerticalFrame(pF2), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Sweep error limit: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pF4->AddFrame(pNumEntrySweepError = new TGNumberEntry(pF4, 10, 6, NUM_SWEEPERROR, TGNumberFormat::kNESInteger,
							TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMin, 0.0), new TGLayoutHints(kLHintsRight));

					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Sweep time min(sec): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pF4->AddFrame(pNumEntrySweepTimeMin = new TGNumberEntry(pF4, 0.1, 6, NUM_SWEEPTIMEMIN, TGNumberFormat::kNESReal,
							TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMin, 0.1), new TGLayoutHints(kLHintsRight));

					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Sweep time max(sec): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pF4->AddFrame(pNumEntrySweepTimeMax = new TGNumberEntry(pF4, 10, 6, NUM_SWEEPTIMEMAX, TGNumberFormat::kNESReal,
							TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMin, 0.1), new TGLayoutHints(kLHintsRight));

				pF2->AddFrame(pF3 = new TGVerticalFrame(pF2), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Loopback Mode: ")), new TGLayoutHints(kLHintsLeft, 5, 0, 2, 0));
						pF4->AddFrame(pComboLoopback = new TGComboBox(pF4, CMB_LOOPBACK), new TGLayoutHints(kLHintsRight));
							pComboLoopback->Resize(150, 20);
							pComboLoopback->AddEntry("DISABLED", CMB_ID_LOOPBACK_DISABLED);
							pComboLoopback->AddEntry("NEAR-END PCS", CMB_ID_LOOPBACK_NEARPCS);
							pComboLoopback->AddEntry("NEAR-END PMA", CMB_ID_SYNCSRC_NEARPMA);
							pComboLoopback->AddEntry("FAR-END PMA", CMB_ID_SYNCSRC_FARPMA);
							pComboLoopback->AddEntry("FAR-END PCS", CMB_ID_SYNCSRC_FARPCS);
							pComboLoopback->Associate(this);

					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("PRBS Mode: ")), new TGLayoutHints(kLHintsLeft, 5, 0, 2, 0));
						pF4->AddFrame(pComboPrbs = new TGComboBox(pF4, CMB_PRBS), new TGLayoutHints(kLHintsRight));
							pComboPrbs->Resize(150, 20);
							pComboPrbs->AddEntry("DISABLED", CMB_ID_PRBS_DISABLED);
							pComboPrbs->AddEntry("PRBS-7", CMB_ID_PRBS_7);
							pComboPrbs->AddEntry("PRBS-23", CMB_ID_PRBS_23);
							pComboPrbs->AddEntry("PRBS-31", CMB_ID_PRBS_31);
							pComboPrbs->Associate(this);

					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Sweep eye step: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
						pF4->AddFrame(pNumEntrySweepStep = new TGNumberEntry(pF4, 5, 3, NUM_SWEEPSTEP, TGNumberFormat::kNESInteger,
							TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 1, 100), new TGLayoutHints(kLHintsRight));

			for(int i = 0; i < GtxCount; i++)
			{
				sprintf(buf, "Lane %d Settings", i);
				pF1->AddFrame(pF2 = new TGGroupFrame(pF1, buf, kHorizontalFrame), new TGLayoutHints(kLHintsExpandX));
					pF2->AddFrame(pF3 = new TGVerticalFrame(pF2), new TGLayoutHints(kLHintsExpandX));
						pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
							pF4->AddFrame(new TGLabel(pF4, new TGString("Tx PreEmphasis: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pF4->AddFrame(pComboTxPreEmphasis[i] = new TGComboBox(pF4, CMB_TXPREEMPHASIS0+i), new TGLayoutHints(kLHintsRight));
								pComboTxPreEmphasis[i]->Resize(150, 20);
								pComboTxPreEmphasis[i]->AddEntry("0%", CMB_ID_TXPREEMPHASIS_0);
								pComboTxPreEmphasis[i]->AddEntry("8%", CMB_ID_TXPREEMPHASIS_8);
								pComboTxPreEmphasis[i]->AddEntry("17%", CMB_ID_TXPREEMPHASIS_17);
								pComboTxPreEmphasis[i]->AddEntry("25%", CMB_ID_TXPREEMPHASIS_25);
								pComboTxPreEmphasis[i]->AddEntry("33%", CMB_ID_TXPREEMPHASIS_33);
								pComboTxPreEmphasis[i]->AddEntry("42%", CMB_ID_TXPREEMPHASIS_42);
								pComboTxPreEmphasis[i]->AddEntry("50%", CMB_ID_TXPREEMPHASIS_50);
								pComboTxPreEmphasis[i]->AddEntry("58%", CMB_ID_TXPREEMPHASIS_58);
								pComboTxPreEmphasis[i]->Associate(this);

						pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
							pF4->AddFrame(new TGLabel(pF4, new TGString("Tx Swing: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pF4->AddFrame(pComboTxDiffCtrl[i] = new TGComboBox(pF4, CMB_TXSWING0+i), new TGLayoutHints(kLHintsRight));
								pComboTxDiffCtrl[i]->Resize(150, 20);
								pComboTxDiffCtrl[i]->AddEntry("500mV", CMB_ID_TXSWING_500);
								pComboTxDiffCtrl[i]->AddEntry("700mV", CMB_ID_TXSWING_700);
								pComboTxDiffCtrl[i]->AddEntry("800mV", CMB_ID_TXSWING_800);
								pComboTxDiffCtrl[i]->AddEntry("900mV", CMB_ID_TXSWING_900);
								pComboTxDiffCtrl[i]->AddEntry("1000mV", CMB_ID_TXSWING_1000);
								pComboTxDiffCtrl[i]->AddEntry("1100mV", CMB_ID_TXSWING_1100);
								pComboTxDiffCtrl[i]->AddEntry("1200mV", CMB_ID_TXSWING_1200);
								pComboTxDiffCtrl[i]->AddEntry("1300mV", CMB_ID_TXSWING_1300);
								pComboTxDiffCtrl[i]->Associate(this);

						pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
							pF4->AddFrame(new TGLabel(pF4, new TGString("Tx Polarity: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pF4->AddFrame(pComboTxPol[i] = new TGComboBox(pF4, CMB_TXPOL0+i), new TGLayoutHints(kLHintsRight));
								pComboTxPol[i]->Resize(150, 20);
								pComboTxPol[i]->AddEntry("Normal", CMB_ID_TXPOL_NORMAL);
								pComboTxPol[i]->AddEntry("Inverted", CMB_ID_TXPOL_INVERTED);
								pComboTxPol[i]->Associate(this);

						pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
							pF4->AddFrame(new TGLabel(pF4, new TGString("Rx Equalization: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pF4->AddFrame(pComboRxEqual[i] = new TGComboBox(pF4, CMB_RXEQUAL0+i), new TGLayoutHints(kLHintsRight));
								pComboRxEqual[i]->Resize(150, 20);
								pComboRxEqual[i]->AddEntry("Bypass", CMD_ID_RXEQUAL_BYPASS);
								pComboRxEqual[i]->AddEntry("Small", CMD_ID_RXEQUAL_SMALL);
								pComboRxEqual[i]->AddEntry("Medium", CMD_ID_RXEQUAL_MEDIUM);
								pComboRxEqual[i]->AddEntry("Large", CMD_ID_RXEQUAL_LARGE);
								pComboRxEqual[i]->Associate(this);

						pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
							pF4->AddFrame(pLabelRxSample[i] = new TGLabel(pF4, new TGString("Rx Sample Point(127):")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pF4->AddFrame(pSliderFiberRxSample[i] = new TGHSlider(pF4, 150, kSlider1 | kScaleBoth, SDR_RXSAMPLE0+i), new TGLayoutHints(kLHintsRight));
								pSliderFiberRxSample[i]->SetRange(0, 127);
								pSliderFiberRxSample[i]->Associate(this);

					pF2->AddFrame(pTextViewFiber[i] = new TGTextView(pF2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			}

		pTimerUpdate = new TTimer(this, SSP_FIBER_SWEEP_TIMER_CHECK, kTRUE);

		ReadSettings();
		UpdateTextView();
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
			SweepTimeout();

		return kTRUE;
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		TGString t;
		Long_t msg_type = GET_MSG(msg);
		Long_t submsg_type = GET_SUBMSG(msg);

//		printf("msg_type = %d, submsg_type = %d\n", msg_type, submsg_type);

		if( (msg_type == kC_COMMAND) && (submsg_type == kCM_BUTTON) )
		{
			switch(parm1)
			{
				case BTN_GTXENABLE:
					if(pButtonGtxEnable->IsDown())
					{
						SetGtxPower(0);
						pButtonGtxEnable->SetText(new TGHotString("GTX Enabled"));
					}
					else
					{
						SetGtxPower(1);
						pButtonGtxEnable->SetText(new TGHotString("GTX Disabled"));
					}
					break;

				case BTN_GTXRESET:
					if(pButtonGtxReset->IsDown())
						SetGtxReset(1);
					else
						SetGtxReset(0);
					break;

				case BTN_LINKRESET:
					if(pButtonLinkReset->IsDown())
						SetLinkReset(1);
					else
						SetLinkReset(0);
					break;
	
				case BTN_SWEEP:
					if(pButtonSweep->IsDown())
						SweepStart();
					else
						SweepStop();
					break;

				case BTN_STATUS:
					ReadSettings();
					UpdateTextView();
					break;

				case BTN_SETUPDEFAULT:
					SetupDefaults();
					break;
			}
		}
		else if( (msg_type == kC_HSLIDER) && (submsg_type == kSL_POS) )
		{
			int parm_idx = parm1 % 10;
			int parm = parm1 - parm_idx;
			switch(parm)
			{
				case SDR_RXSAMPLE0:
					t.Form("Rx Sample Point(%u):", pSliderFiberRxSample[parm_idx]->GetPosition());
					pLabelRxSample[parm_idx]->SetText(t);
					SetRxSamplePoint(parm_idx, pSliderFiberRxSample[parm_idx]->GetPosition());
					break;
			}
		}
		else if( (msg_type == kC_COMMAND) && (submsg_type == kCM_COMBOBOX) )
		{
			int parm_idx = parm1 % 10;
			int parm = parm1 - parm_idx;
			switch(parm)
			{
				case CMB_LOOPBACK:
					SetLoopback(pComboLoopback->GetSelected());
					break;

				case CMB_PRBS:
					SetRxPrbs(pComboPrbs->GetSelected());
					SetTxPrbs(pComboPrbs->GetSelected());
					break;

				case CMB_TXPREEMPHASIS0:
					SetTxPreEmphasis(parm_idx, pComboTxPreEmphasis[parm_idx]->GetSelected());
					break;

				case CMB_TXSWING0:
					SetTxSwing(parm_idx, pComboTxDiffCtrl[parm_idx]->GetSelected());
					break;

				case CMB_TXPOL0:
					SetTxPolarity(parm_idx, pComboTxPol[parm_idx]->GetSelected());
					break;

				case CMB_RXEQUAL0:
					SetRxEqualization(parm_idx, pComboRxEqual[parm_idx]->GetSelected());
					break;
			}
		}
		return kTRUE;
	}

	void SweepTimeout()
	{
		unsigned int prbsErrors;
		unsigned int errors[4];
		int i;

		if(!pButtonSweep->IsDown())
			return;

		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, sweepCtrl | 0x80000000);
		sweepTicksElapsed+= (unsigned long long)pM->ReadReg32(&pRegs->GtxQsfp[Idx].RefTime);

		prbsErrors = pM->ReadReg32(&pRegs->GtxQsfp[Idx].PrbsErrors0);
		errors[0] = (prbsErrors & 0xFFFF);
		errors[1] = (prbsErrors >> 16);

		if(Mode == GTX_FIB)
		{
			prbsErrors = pM->ReadReg32(&pRegs->GtxQsfp[Idx].PrbsErrors1);
			errors[2] = (prbsErrors & 0xFFFF);
			errors[3] = (prbsErrors >> 16);
		}

		for(i = 0; i < GtxCount; i++)
		{
			sweepErrorsFound[i] += (unsigned long long)errors[i];
			if(errors[i] == 0xFFFF)
				sweepSampleErrorOverflow[i] = 1;
		}

		unsigned long long minErrors = (unsigned long long)pNumEntrySweepError->GetIntNumber();
		unsigned long long minTime = (unsigned long long)(62.5E6 * pNumEntrySweepTimeMin->GetNumber());
		unsigned long long maxTime = (unsigned long long)(62.5E6 * pNumEntrySweepTimeMax->GetNumber());
		
		bool minErrorsMet = true;
		for(i = 0; i < GtxCount; i++)
		{
			if(sweepErrorsFound[i] < minErrors)
				minErrorsMet = false;
		}

		bool UpdateSweep;
		if( ((sweepTicksElapsed > minTime) && minErrorsMet) || (sweepTicksElapsed > maxTime) )
			UpdateSweep = true;
		else
			UpdateSweep = false;

		if(UpdateSweep)
		{
			if(Mode == GTX_VXS)
			{
				printf("Sweep point %d, Error: %llu,%llu\n", sweepSamplePoint,
					sweepErrorsFound[0], sweepErrorsFound[1]);
			}
			else
			{
				printf("Sweep point %d, Error: %llu,%llu,%llu,%llu\n", sweepSamplePoint,
					sweepErrorsFound[0], sweepErrorsFound[1],
					sweepErrorsFound[2], sweepErrorsFound[3]);
			}
			
			for(i = 0; i < GtxCount; i++)
			{
				if(sweepErrorsFound[i] == 0)
					sweepErrorsFound[i] = 1;

				double sentBits = (double)sweepTicksElapsed * 6.25E9 / 62.5E6;
				double errorRate = (double)sweepErrorsFound[i] / sentBits;

				if(sweepSampleErrorOverflow[i])
				{
					errorRate = 0.5;
					sweepSampleErrorOverflow[i] = 0;
				}

				pGraphFiberBer[i]->SetPoint(pGraphFiberBer[i]->GetN(), sweepSamplePoint, errorRate);
				pGraphFiberBer[i]->GetXaxis()->SetRangeUser(0.0, 128.0);

				sweepErrorsFound[i] = 0;
			}
			pCanvasFiberBer->GetCanvas()->cd();
			pCanvasFiberBer->GetCanvas()->Clear();
			pMultiGraphFiberBer->GetXaxis()->SetRangeUser(0.0, 128.0);
			pMultiGraphFiberBer->Draw("AL");
			pCanvasFiberBer->GetCanvas()->BuildLegend(0.7, 0.7, 0.9, 0.9);
			pCanvasFiberBer->GetCanvas()->Update();
			pCanvasFiberBer->GetCanvas()->Modified();

			sweepSamplePoint+= pNumEntrySweepStep->GetIntNumber();

			if(sweepSamplePoint < 128)
			{
				sweepTicksElapsed = 0;
				for(i = 0; i < GtxCount; i++)
					SetRxSamplePoint(i, sweepSamplePoint);

				pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, sweepCtrl | 0x80000000);
				pTimerUpdate->Start(SSP_FIBER_SWEEP_TIMER_CHECK, kTRUE);
			}
			else
			{
				printf("Ending sweep...\n");
				SweepStop();
			}
		}
		else
			pTimerUpdate->Start(SSP_FIBER_SWEEP_TIMER_CHECK, kTRUE);
	}

	void SweepStart()
	{
		pButtonSweep->SetText(new TGHotString("Sweep Stop"));
		pNumEntrySweepError->SetState(kFALSE);
		pNumEntrySweepTimeMin->SetState(kFALSE);
		pNumEntrySweepTimeMax->SetState(kFALSE);
		pNumEntrySweepStep->SetState(kFALSE);

		sweepTicksElapsed = 0;
		sweepSamplePoint = 0;
		sweepCtrl = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);

		for(int i = 0; i < GtxCount; i++)
		{
			pGraphFiberBer[i]->Set(0);
			sweepErrorsFound[i] = 0;
			sweepSamplePointInitial[i] = GetRxSamplePoint(i);
			sweepSampleErrorOverflow[i] = 0;
			SetRxSamplePoint(i, sweepSamplePoint);
		}

		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, sweepCtrl | 0x80000000);

		pTimerUpdate->Start(SSP_FIBER_SWEEP_TIMER_CHECK, kTRUE);
	}

	void SweepStop()
	{
		for(int i = 0; i < GtxCount; i++)
			SetRxSamplePoint(i, sweepSamplePointInitial[i]);

		pButtonSweep->SetText(new TGHotString("Sweep Start"));
		pButtonSweep->SetDown(kFALSE);
		pNumEntrySweepError->SetState(kTRUE);
		pNumEntrySweepTimeMin->SetState(kTRUE);
		pNumEntrySweepTimeMax->SetState(kTRUE);
		pNumEntrySweepStep->SetState(kTRUE);
	}

	void ReadSettings()
	{
		unsigned int Ctrl = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		unsigned int Status = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status);
		unsigned int TxRxSettings0 = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
		unsigned int TxRxSettings1 = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);

		if(Ctrl & 0x1)
		{
			pButtonGtxEnable->SetText(new TGHotString("GTX Disabled"));
			pButtonGtxEnable->SetDown(kFALSE);
		}
		else
		{
			pButtonGtxEnable->SetText(new TGHotString("GTX Enabled"));
			pButtonGtxEnable->SetDown(kTRUE);
		}

		if(GetRxPrbs() != GetTxPrbs())
			printf("SSPModule.SSP_Fiber(%d) WARNING: GetTxPrbs() != GetRxPrbs()\n", Idx);

		pComboPrbs->Select(GetRxPrbs(), kFALSE);

		pComboLoopback->Select(GetLoopback(), kFALSE);

		for(int i = 0; i < GtxCount; i++)
		{
			pComboTxPreEmphasis[i]->Select(GetTxPreEmphasis(i), kFALSE);
			pComboTxDiffCtrl[i]->Select(GetTxSwing(i), kFALSE);
			pComboTxPol[i]->Select(GetTxPolarity(i), kFALSE);
			pComboRxEqual[i]->Select(GetRxEqualization(i), kFALSE);

			unsigned int val = GetRxSamplePoint(i);
			pSliderFiberRxSample[i]->SetPosition(val);
			TGString t;
			t.Form("Rx Sample Point(%u):", val);
			pLabelRxSample[i]->SetText(t);
		}
	}

	void UpdateTextView()
	{
		char buf[100];
		unsigned int reg;

		// Latch Scalers
		reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, reg | 0x80000000);

		for(int i = 0; i < GtxCount; i++)
		{
			pTextViewFiber[i]->Clear();

			reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
			sprintf(buf, "GTX Ctrl            = 0x%08X", reg);			pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "   POWER_DOWN       = %d", GetGtxPower());	pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "   GT_RESET         = %d", GetGtxReset());	pTextViewFiber[i]->AddLineFast(buf);
			switch(GetLoopback())
			{
				case 0:		pTextViewFiber[i]->AddLineFast("   LOOPBACK         = DISABLED"); break;
				case 1:		pTextViewFiber[i]->AddLineFast("   LOOPBACK         = NEARPCS"); break;
				case 2:		pTextViewFiber[i]->AddLineFast("   LOOPBACK         = NEARPMA"); break;
				case 4:		pTextViewFiber[i]->AddLineFast("   LOOPBACK         = FARPMA"); break;
				case 6:		pTextViewFiber[i]->AddLineFast("   LOOPBACK         = FARPCS"); break;
				default:	pTextViewFiber[i]->AddLineFast("   LOOPBACK         = *** UNKNOWN ***"); break;
			}
			switch(GetRxPrbs())
			{
				case 0:		pTextViewFiber[i]->AddLineFast("   RXPRBS           = DISABLED"); break;
				case 1:		pTextViewFiber[i]->AddLineFast("   RXPRBS           = PRBS7"); break;
				case 2:		pTextViewFiber[i]->AddLineFast("   RXPRBS           = PRBS23"); break;
				case 3:		pTextViewFiber[i]->AddLineFast("   RXPRBS           = PRBS31"); break;
			}
			switch(GetTxPrbs())
			{
				case 0:		pTextViewFiber[i]->AddLineFast("   TXPRBS           = DISABLED"); break;
				case 1:		pTextViewFiber[i]->AddLineFast("   TXPRBS           = PRBS7"); break;
				case 2:		pTextViewFiber[i]->AddLineFast("   TXPRBS           = PRBS23"); break;
				case 3:		pTextViewFiber[i]->AddLineFast("   TXPRBS           = PRBS31"); break;
			}
			sprintf(buf, "   LINK_RESET       = %d", GetLinkReset());		pTextViewFiber[i]->AddLineFast(buf);
			pTextViewFiber[i]->AddLineFast("");

			sprintf(buf, "SOFT_ERROR          = %u", GetSoftErrors(i));	pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "PRBS_ERROR          = %u", GetPrbsErrors(i));	pTextViewFiber[i]->AddLineFast(buf);
			pTextViewFiber[i]->AddLineFast("");

			reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status);
			sprintf(buf, "GTX Status          = 0x%08X", reg);				pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "   HARD_ERROR       = %d", GetHardError(i));	pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "   LANEUP           = %d", GetLaneUp(i));		pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "   CHANNELUP        = %d", (reg>>12) & 0x1);		pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "   TX_LOCK          = %d", (reg>>13) & 0x1);		pTextViewFiber[i]->AddLineFast(buf);
			pTextViewFiber[i]->AddLineFast("");

			reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
			sprintf(buf, "GTX TxRxSettings0   = 0x%08X", reg);	pTextViewFiber[i]->AddLineFast(buf);
			reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
			sprintf(buf, "GTX TxRxSettings1   = 0x%08X", reg);	pTextViewFiber[i]->AddLineFast(buf);

			switch(GetRxEqualization(i))
			{
				case 0:		sprintf(buf, "   RXEQMIX          = LARGE");		pTextViewFiber[i]->AddLineFast(buf); break;
				case 1:		sprintf(buf, "   RXEQMIX          = SMALL");		pTextViewFiber[i]->AddLineFast(buf); break;
				case 2:		sprintf(buf, "   RXEQMIX          = MEDIUM");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 3:		sprintf(buf, "   RXEQMIX          = BYPASS");	pTextViewFiber[i]->AddLineFast(buf); break;
			}
			switch(GetTxPreEmphasis(i))
			{
				case 0:		sprintf(buf, "   TXPRE            = 0%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 1:		sprintf(buf, "   TXPRE            = 8%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 2:		sprintf(buf, "   TXPRE            = 17%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 3:		sprintf(buf, "   TXPRE            = 25%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 4:		sprintf(buf, "   TXPRE            = 33%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 5:		sprintf(buf, "   TXPRE            = 42%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 6:		sprintf(buf, "   TXPRE            = 50%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 7:		sprintf(buf, "   TXPRE            = 58%%");	pTextViewFiber[i]->AddLineFast(buf); break;
				default:	sprintf(buf, "   TXPRE            = *** UNKNOWN ***");	pTextViewFiber[i]->AddLineFast(buf); break;
			}
			switch((reg>>6) & 0x7)
			{
				case 0:		sprintf(buf, "   TXBUFDIFFCTRL    = 600mV");		pTextViewFiber[i]->AddLineFast(buf); break;
				case 1:		sprintf(buf, "   TXBUFDIFFCTRL    = 700mV");		pTextViewFiber[i]->AddLineFast(buf); break;
				case 2:		sprintf(buf, "   TXBUFDIFFCTRL    = 800mV");		pTextViewFiber[i]->AddLineFast(buf); break;
				case 3:		sprintf(buf, "   TXBUFDIFFCTRL    = 900mV");		pTextViewFiber[i]->AddLineFast(buf); break;
				case 4:		sprintf(buf, "   TXBUFDIFFCTRL    = 1000mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 5:		sprintf(buf, "   TXBUFDIFFCTRL    = 1100mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 6:		sprintf(buf, "   TXBUFDIFFCTRL    = 1200mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 7:		sprintf(buf, "   TXBUFDIFFCTRL    = 1300mV");	pTextViewFiber[i]->AddLineFast(buf); break;
			}
			switch(GetTxSwing(i))
			{
				case 0:		sprintf(buf, "   TXDIFFCTRL       = 500mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 1:		sprintf(buf, "   TXDIFFCTRL       = 700mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 2:		sprintf(buf, "   TXDIFFCTRL       = 800mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 3:		sprintf(buf, "   TXDIFFCTRL       = 900mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 4:		sprintf(buf, "   TXDIFFCTRL       = 1000mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 5:		sprintf(buf, "   TXDIFFCTRL       = 1100mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 6:		sprintf(buf, "   TXDIFFCTRL       = 1200mV");	pTextViewFiber[i]->AddLineFast(buf); break;
				case 7:		sprintf(buf, "   TXDIFFCTRL       = 1300mV");	pTextViewFiber[i]->AddLineFast(buf); break;
			}
			sprintf(buf, "TXPOL               = %d", GetTxPolarity(i)); pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "RXPOL               = %d", GetRxPolarity(i)); pTextViewFiber[i]->AddLineFast(buf);
			sprintf(buf, "RXSAMPLE            = %d", GetRxSamplePoint(i)); pTextViewFiber[i]->AddLineFast(buf);

			pTextViewFiber[i]->Update();
		}
	}

	void SetupDefaults()
	{
		SetGtxPower(0);
		SetGtxReset(1);
		SetLinkReset(1);
		SetLoopback(CMB_ID_LOOPBACK_DISABLED);
		SetRxPrbs(CMB_ID_PRBS_DISABLED);
		SetTxPrbs(CMB_ID_PRBS_DISABLED);

		for(int i = 0; i < GtxCount; i++)
		{
			SetTxPreEmphasis(i, CMB_ID_TXPREEMPHASIS_0);
			SetTxSwing(i, CMB_ID_TXSWING_800);
			SetTxPolarity(i, FiberMaps[Idx].TxPolarity[i]);
			SetRxEqualization(i, CMD_ID_RXEQUAL_MEDIUM);
			SetRxSamplePoint(i, 53);	// 6.25Gbps sample point
		}
		SetGtxReset(0);
		SetLinkReset(0);

		ReadSettings();
		UpdateTextView();
	}

	int GetGtxPower()
	{
		unsigned int val = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		if(val & 0x1)
			return 1;

		return 0;
	}

	void SetGtxPower(int dis)
	{
		unsigned int val = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		if(dis)
			val = val | 0x00000001;
		else
			val = val & 0xFFFFFFFE;

		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, val);
	}

	int GetGtxReset()
	{
		unsigned int val = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		if(val & 0x2)
			return 1;

		return 0;
	}

	void SetGtxReset(int en)
	{
		unsigned int val = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		if(en)
			pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, val | 0x2);
		else
			pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, val & ~0x2);
	}

	int GetLinkReset()
	{
		unsigned int val = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		if(val & 0x200)
			return 1;

		return 0;
	}

	void SetLinkReset(int en)
	{
		unsigned int val = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);
		if(en)
			pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, val | 0x200);
		else
			pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, val & ~0x200);
	}

	int GetLoopback()
	{
		return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl)>>2) & 0x3;
	}

	void SetLoopback(int val)
	{
		unsigned int reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);

#if SSP_FIBER_DEBUG
		printf("SetLoopback(%d)\n", val);
#endif

		reg = (reg & 0xFFFFFFF3) | (val << 2);
		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, reg);
	}

	int GetRxPrbs()
	{
		return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl)>>5) & 0x3;
	}

	void SetRxPrbs(int val)
	{
		unsigned int reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);

#if SSP_FIBER_DEBUG
		printf("SetRxPrbs(%d)\n", val);
#endif

		reg = (reg & 0xFFFFFF9F) | (val << 5);
		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, reg);
	}

	int GetTxPrbs()
	{
		return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl)>>7) & 0x3;
	}

	void SetTxPrbs(int val)
	{
		unsigned int reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].Ctrl);

#if SSP_FIBER_DEBUG
		printf("SetTxPrbs(%d)\n", val);
#endif

		reg = (reg & 0xFFFFFE7F) | (val << 7);
		pM->WriteReg32(&pRegs->GtxQsfp[Idx].Ctrl, reg);
	}

	int GetHardError(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>0) & 0x1;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>1) & 0x1;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>2) & 0x1;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>3) & 0x1;
		}
		return -1;
	}

	unsigned int GetSoftErrors(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].SoftErrors0)>>0) & 0xFFFF;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].SoftErrors0)>>16) & 0xFFFF;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].SoftErrors1)>>0) & 0xFFFF;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].SoftErrors1)>>16) & 0xFFFF;
		}
		return -1;
	}

	unsigned int GetPrbsErrors(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].PrbsErrors0)>>0) & 0xFFFF;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].PrbsErrors0)>>16) & 0xFFFF;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].PrbsErrors1)>>0) & 0xFFFF;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].PrbsErrors1)>>16) & 0xFFFF;
		}
		return -1;
	}

	int GetLaneUp(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>4) & 0x1;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>5) & 0x1;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>6) & 0x1;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>7) & 0x1;
		}
		return -1;
	}
	
	int GetTxPreEmphasis(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>2) & 0xF;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>18) & 0xF;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>2) & 0xF;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>18) & 0xF;
		}
		return -1;
	}

	void SetTxPreEmphasis(int lane, int val)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];
		unsigned int reg;

#if SSP_FIBER_DEBUG
		printf("SetTxPreEmphasis(%d, %d) mapped %d\n", lane, val, mapped_lane);
#endif

		switch(mapped_lane)
		{
			case GTX_LANE0:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFFFFFFC3) | (val << 2);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE1:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFFC3FFFF) | (val << 18);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE2:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFFFFFFC3) | (val << 2);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
			case GTX_LANE3:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFFC3FFFF) | (val << 18);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
		}
	}

	int GetTxSwing(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>9) & 0x7;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>25) & 0x7;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>9) & 0x7;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>25) & 0x7;
		}
		return -1;
	}

	void SetTxSwing(int lane, int val)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];
		unsigned int reg;

#if SSP_FIBER_DEBUG
		printf("SetTxSwing(%d, %d) mapped %d\n", lane, val, mapped_lane);
#endif

		switch(mapped_lane)
		{
			case GTX_LANE0:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFFFFF1FF) | (val << 9);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE1:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFF1FFFFF) | (val << 25);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE2:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFFFFF1FF) | (val << 9);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
			case GTX_LANE3:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFF1FFFFF) | (val << 25);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
		}
	}

	int GetTxPolarity(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>12) & 0x1;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>28) & 0x1;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>12) & 0x1;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>28) & 0x1;
		}
		return -1;
	}

	void SetTxPolarity(int lane, int val)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];
		unsigned int reg;

#if SSP_FIBER_DEBUG
		printf("SetTxPolarity(%d, %d) mapped %d\n", lane, val, mapped_lane);
#endif

		switch(mapped_lane)
		{
			case GTX_LANE0:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFFFFEFFF) | (val << 12);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE1:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xEFFFFFFF) | (val << 28);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE2:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFFFFEFFF) | (val << 12);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
			case GTX_LANE3:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xEFFFFFFF) | (val << 28);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
		}
	}

	int GetRxPolarity(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>8) & 0x1;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>9) & 0x1;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>10) & 0x1;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].Status)>>11) & 0x1;
		}
		return -1;
	}
	
	int GetRxEqualization(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];

		switch(mapped_lane)
		{
			case GTX_LANE0:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>0) & 0x3;
			case GTX_LANE1:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0)>>16) & 0x3;
			case GTX_LANE2:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>0) & 0x3;
			case GTX_LANE3:
				return (pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1)>>16) & 0x3;
		}
		return -1;
	}

	void SetRxEqualization(int lane, int val)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];
		unsigned int reg;

#if SSP_FIBER_DEBUG
		printf("SetRxEqualization(%d, %d) mapped %d\n", lane, val, mapped_lane);
#endif

		switch(mapped_lane)
		{
			case GTX_LANE0:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFFFFFFFC) | (val << 0);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE1:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0);
				reg = (reg & 0xFFFCFFFF) | (val << 16);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings0, reg);
				break;
			case GTX_LANE2:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFFFFFFFC) | (val << 0);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
			case GTX_LANE3:
				reg = pM->ReadReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1);
				reg = (reg & 0xFFFCFFFF) | (val << 16);
				pM->WriteReg32(&pRegs->GtxQsfp[Idx].TxRxSettings1, reg);
				break;
		}
	}

	unsigned int GetRxSamplePoint(int lane)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];
		unsigned int tile = (mapped_lane < 2) ? 0 : 1;
		unsigned int result;

		if(mapped_lane & 0x1)
			result = ReverseBits(DrpReadReg(tile, 0x0B));
		else
			result = DrpReadReg(tile, 0x44);

		return (result >> 4) & 0xFF;
	}

	void SetRxSamplePoint(int lane, unsigned int val)
	{
		int mapped_lane = FiberMaps[Idx].Lane[lane];
		unsigned int tile = (mapped_lane < 2) ? 0 : 1;
		unsigned int result;

#if SSP_FIBER_DEBUG
		printf("SetRxSamplePoint(%d, %d) mapped %d\n", lane, val, mapped_lane);
#endif

		if(mapped_lane & 0x1)
			result = ReverseBits(DrpReadReg(tile, 0x0B));
		else
			result = DrpReadReg(tile, 0x44);

		result = result & 0xF00F;
		result = result | ((val & 0xFF)<<4);

		if(mapped_lane & 0x1)
			DrpWriteReg(tile, 0x0B, ReverseBits(result));
		else
			DrpWriteReg(tile, 0x44, result);
	}

	unsigned short ReverseBits(unsigned short val)
	{
		unsigned short result = 0;
		unsigned short mask_rd = 0x0001;
		unsigned short mask_wr = 0x8000;

		for(int i = 0; i < 16; i++)
		{
			if(val & mask_rd)
				result |= mask_wr;
			mask_rd <<= 1;
			mask_wr >>= 1;
		}
		return result;
	}

	unsigned int DrpReadReg(unsigned int tile, unsigned int addr)
	{
		unsigned int result;

		pM->WriteReg32(&pRegs->GtxQsfp[Idx].DrpCtrl, (1<<(24+tile)) | ((addr&0x7f)<<16));
		result = pM->ReadReg32(&pRegs->GtxQsfp[Idx].DrpStatus);

//		printf("DrpReadReg(tile=%d,addr=0x%02X) = 0x%04X\n", tile, addr, result);

		if(!(result & 0x10000))
			printf("Error: SSPModule->SSP_Fiber(%d)->DrpReadReg(%d,%d) failed\n", Idx, tile, addr);

		return result & 0xFFFF;
	}

	void DrpWriteReg(unsigned int tile, unsigned int addr, unsigned int val)
	{
//		printf("DrpWriteReg(tile=%d,addr=0x%02X) = 0x%04X\n", tile, addr, val);
		pM->WriteReg32(&pRegs->GtxQsfp[Idx].DrpCtrl, (1<<(24+tile)) | (1<<23) | ((addr&0x7f)<<16) | (val & 0xFFFF));
	}

private:

	enum Sliders
	{
		SDR_RXSAMPLE0,
		SDR_RXSAMPLE1,
		SDR_RXSAMPLE2,
		SDR_RXSAMPLE3
	};

	enum NumEntries
	{
		NUM_SWEEPERROR,
		NUM_SWEEPTIMEMIN,
		NUM_SWEEPTIMEMAX,
		NUM_SWEEPSTEP
	};

	enum Buttons
	{
		BTN_GTXENABLE,
		BTN_GTXRESET,
		BTN_LINKRESET,
		BTN_SWEEP,
		BTN_STATUS,
		BTN_SETUPDEFAULT
	};

	enum ComboLoopback
	{
		CMB_LOOPBACK = 200,
		CMB_ID_LOOPBACK_DISABLED = 0,
		CMB_ID_LOOPBACK_NEARPCS = 1,
		CMB_ID_SYNCSRC_NEARPMA = 2,
		CMB_ID_SYNCSRC_FARPMA = 4,
		CMB_ID_SYNCSRC_FARPCS = 6
	};

	enum ComboPrbs
	{
		CMB_PRBS = 210,
		CMB_ID_PRBS_DISABLED = 0,
		CMB_ID_PRBS_7 = 1,
		CMB_ID_PRBS_23 = 2,
		CMB_ID_PRBS_31 = 3,
	};

	enum ComboTxPreemphasis
	{
		CMB_TXPREEMPHASIS0 = 220,
		CMB_TXPREEMPHASIS1 = 221,
		CMB_TXPREEMPHASIS2 = 222,
		CMB_TXPREEMPHASIS3 = 223,
		CMB_ID_TXPREEMPHASIS_0 = 0,
		CMB_ID_TXPREEMPHASIS_8 = 1,
		CMB_ID_TXPREEMPHASIS_17 = 2,
		CMB_ID_TXPREEMPHASIS_25 = 3,
		CMB_ID_TXPREEMPHASIS_33 = 4,
		CMB_ID_TXPREEMPHASIS_42 = 5,
		CMB_ID_TXPREEMPHASIS_50 = 6,
		CMB_ID_TXPREEMPHASIS_58 = 7
	};

	enum ComboTxSwing
	{
		CMB_TXSWING0 = 230,
		CMB_TXSWING1 = 231,
		CMB_TXSWING2 = 232,
		CMB_TXSWING3 = 233,
		CMB_ID_TXSWING_500 = 0,
		CMB_ID_TXSWING_700 = 1,
		CMB_ID_TXSWING_800 = 2,
		CMB_ID_TXSWING_900 = 3,
		CMB_ID_TXSWING_1000 = 4,
		CMB_ID_TXSWING_1100 = 5,
		CMB_ID_TXSWING_1200 = 6,
		CMB_ID_TXSWING_1300 = 7
	};

	enum ComboTxPolarity
	{
		CMB_TXPOL0 = 240,
		CMB_TXPOL1 = 241,
		CMB_TXPOL2 = 242,
		CMB_TXPOL3 = 243,
		CMB_ID_TXPOL_NORMAL = 0,
		CMB_ID_TXPOL_INVERTED = 1
	};

	enum ComboRxEqualization
	{
		CMB_RXEQUAL0 = 260,
		CMB_RXEQUAL1 = 261,
		CMB_RXEQUAL2 = 262,
		CMB_RXEQUAL3 = 263,
		CMD_ID_RXEQUAL_LARGE = 0,
		CMD_ID_RXEQUAL_SMALL = 1,
		CMD_ID_RXEQUAL_MEDIUM = 2,
		CMD_ID_RXEQUAL_BYPASS = 3
	};

	ModuleFrame			*pM;
	SSP_regs				*pRegs;

	int					Idx;
	int					Mode;
	int					GtxCount;

	unsigned long long	sweepTicksElapsed;
	unsigned long long	sweepErrorsFound[4];
	unsigned int		sweepSamplePoint;
	unsigned int		sweepSamplePointInitial[4];
	unsigned int		sweepSampleErrorOverflow[4];
	unsigned int		sweepCtrl;

	TTimer				*pTimerUpdate;

	TGTextButton		*pButtonGtxEnable;
	TGTextButton		*pButtonGtxReset;
	TGTextButton		*pButtonLinkReset;
	TGTextButton		*pButtonSweep;
	TGTextButton		*pButtonStatus;
	TGTextButton		*pButtonSetupDefaults;

	TGComboBox			*pComboLoopback;
	TGComboBox			*pComboPrbs;
	TGComboBox			*pComboTxPreEmphasis[4];
	TGComboBox			*pComboTxDiffCtrl[4];
	TGComboBox			*pComboRxEqual[4];
	TGComboBox			*pComboTxPol[4];
	TGComboBox			*pComboRxPol[4];

	TRootEmbeddedCanvas	*pCanvasFiberBer;
	
	TMultiGraph			*pMultiGraphFiberBer;
	TGraph				*pGraphFiberBer[4];

	TGSlider			*pSliderFiberRxSample[4];

	TGLabel				*pLabelRxSample[4];

	TGNumberEntry		*pNumEntrySweepError;
	TGNumberEntry		*pNumEntrySweepTimeMin;
	TGNumberEntry		*pNumEntrySweepTimeMax;
	TGNumberEntry		*pNumEntrySweepStep;

	TGTextView			*pTextViewFiber[4];
};

#endif
