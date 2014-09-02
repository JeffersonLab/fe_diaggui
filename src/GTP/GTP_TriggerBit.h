#ifndef GTP_TRIGGERBIT_H
#define GTP_TRIGGERBIT_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "gtp.h"

class GTP_TriggerBit	: public TGCompositeFrame
{
public:
	GTP_TriggerBit(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		int i;
		
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;
		
		TGCompositeFrame *pF1, *pF2, *pF3, *pF4;

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pF1->AddFrame(pButtonUpdateScalers = new TGTextButton(pF1, new TGHotString("Update Scalers"), BTN_UPDATE_SCALERS));
				pButtonUpdateScalers->Associate(this);

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pF1->AddFrame(pF2 = new TGVerticalFrame(pF1), new TGLayoutHints(kLHintsExpandY));
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "Status", kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pLabelWidthActual = new TGLabel(pF3, new TGString("Actual Width: 9999ns")), new TGLayoutHints(kLHintsLeft));
					pF3->AddFrame(pLabelLatencyActual = new TGLabel(pF3, new TGString("Actual Latency: 9999ns")), new TGLayoutHints(kLHintsLeft));
					pF3->AddFrame(pLabelLatencyStatus = new TGLabel(pF3, new TGString("Latency Status: Error")), new TGLayoutHints(kLHintsLeft));
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "TrigOut Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Trigout:")), new TGLayoutHints(kLHintsLeft));
						pF4->AddFrame(pComboTrignum = new TGComboBox(pF4, CMB_TRIGOUTNUM), new TGLayoutHints(kLHintsRight));
							for(i = 0; i < 32; i++)
								pComboTrignum->AddEntry(Form("Trigout%d", i), i);
							pComboTrignum->Select(0, kFALSE);
							pComboTrignum->SetWidth(75);
							pComboTrignum->SetHeight(20);
							pComboTrignum->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Width:")), new TGLayoutHints(kLHintsLeft));
						pF4->AddFrame(pNumberTrigoutWidth = new TGNumberEntry(pF4, 0, 8, NUM_WIDTH, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
							pNumberTrigoutWidth->SetWidth(75);
							pNumberTrigoutWidth->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("Latency:")), new TGLayoutHints(kLHintsLeft));
						pF4->AddFrame(pNumberTrigoutLatency = new TGNumberEntry(pF4, 0, 8, NUM_LATENCY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 4095), new TGLayoutHints(kLHintsRight));
							pNumberTrigoutLatency->SetWidth(75);
							pNumberTrigoutLatency->Associate(this);
			pF1->AddFrame(pF2 = new TGVerticalFrame(pF1), new TGLayoutHints(kLHintsExpandY));
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "BFCAL Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("BCALHit_thr:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberBCALHit_thr = new TGNumberEntry(pF4, 0, 8, NUM_BCALHIT_THR, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 15), new TGLayoutHints(kLHintsRight));
							pNumberBCALHit_thr->SetWidth(75);
							pNumberBCALHit_thr->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("BCAL_escale:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberBCAL_escale = new TGNumberEntry(pF4, 0, 8, NUM_BCAL_ESCALE, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
							pNumberBCAL_escale->SetWidth(75);
							pNumberBCAL_escale->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("FCAL_escale:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberFCAL_escale = new TGNumberEntry(pF4, 0, 8, NUM_FCAL_ESCALE, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
							pNumberFCAL_escale->SetWidth(75);
							pNumberFCAL_escale->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("BFCAL_thr:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberBFCAL_thr = new TGNumberEntry(pF4, 0, 8, NUM_BFCAL_THR, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMin, 0), new TGLayoutHints(kLHintsRight));
							pNumberBFCAL_thr->SetWidth(75);
							pNumberBFCAL_thr->Associate(this);
					pF3->AddFrame(pCheckBFCAL_en = new TGCheckButton(pF3, new TGHotString("BFCAL_en"), CHK_BFCAL_EN), new TGLayoutHints(kLHintsLeft));
						pCheckBFCAL_en->Associate(this);
					pF3->AddFrame(pCheckBCALHits_en = new TGCheckButton(pF3, new TGHotString("BFCALHits_en"), CHK_BCALHITS_EN), new TGLayoutHints(kLHintsLeft));
						pCheckBCALHits_en->Associate(this);
			pF1->AddFrame(pF2 = new TGVerticalFrame(pF1), new TGLayoutHints(kLHintsExpandY));
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "TAG Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("TAGM_enmsk:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberTAGM_enmsk = new TGNumberEntry(pF4, 0, 8, NUM_TAGM_ENMSK, TGNumberFormat::kNESHex), new TGLayoutHints(kLHintsRight));
							pNumberTAGM_enmsk->SetWidth(75);
							pNumberTAGM_enmsk->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("TAGH_enmsk:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberTAGH_enmsk = new TGNumberEntry(pF4, 0, 8, NUM_TAGH_ENMSK, TGNumberFormat::kNESHex), new TGLayoutHints(kLHintsRight));
							pNumberTAGH_enmsk->SetWidth(75);
							pNumberTAGH_enmsk->Associate(this);
					pF3->AddFrame(pCheckTAGH_en = new TGCheckButton(pF3, new TGHotString("TAGH_en"), CHK_TAGH_EN), new TGLayoutHints(kLHintsLeft));
						pCheckTAGH_en->Associate(this);
					pF3->AddFrame(pCheckTAGM_en = new TGCheckButton(pF3, new TGHotString("TAGM_en"), CHK_TAGM_EN), new TGLayoutHints(kLHintsLeft));
						pCheckTAGM_en->Associate(this);							
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "PS Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("PS_enmsk:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberPS_enmsk = new TGNumberEntry(pF4, 0, 4, NUM_PS_ENMSK, TGNumberFormat::kNESHex), new TGLayoutHints(kLHintsRight));
							pNumberPS_enmsk->SetWidth(75);
							pNumberPS_enmsk->Associate(this);
					pF3->AddFrame(pCheckPS_en = new TGCheckButton(pF3, new TGHotString("PS_en"), CHK_PS_EN), new TGLayoutHints(kLHintsLeft));
						pCheckPS_en->Associate(this);
			pF1->AddFrame(pF2 = new TGVerticalFrame(pF1), new TGLayoutHints(kLHintsExpandY));
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "ST Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("ST_enmsk:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberST_enmsk = new TGNumberEntry(pF4, 0, 8, NUM_ST_ENMSK, TGNumberFormat::kNESHex), new TGLayoutHints(kLHintsRight));
							pNumberST_enmsk->SetWidth(75);
							pNumberST_enmsk->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("STHit_thr:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberSTHit_thr = new TGNumberEntry(pF4, 0, 8, NUM_STHIT_THR, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 31), new TGLayoutHints(kLHintsRight));
							pNumberSTHit_thr->SetWidth(75);
							pNumberSTHit_thr->Associate(this);
					pF3->AddFrame(pCheckST_en = new TGCheckButton(pF3, new TGHotString("ST_en"), CHK_ST_EN), new TGLayoutHints(kLHintsLeft));
						pCheckST_en->Associate(this);
				pF2->AddFrame(pF3 = new TGGroupFrame(pF2, "TOF Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("TOF_enmsk:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberTOF_enmsk = new TGNumberEntry(pF4, 0, 4, NUM_TOF_ENMSK, TGNumberFormat::kNESHex), new TGLayoutHints(kLHintsRight));
							pNumberTOF_enmsk->SetWidth(75);
							pNumberTOF_enmsk->Associate(this);
					pF3->AddFrame(pF4 = new TGHorizontalFrame(pF3), new TGLayoutHints(kLHintsExpandX));
						pF4->AddFrame(new TGLabel(pF4, new TGString("TOFHit_thr:")), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
						pF4->AddFrame(pNumberTOFHit_thr = new TGNumberEntry(pF4, 0, 8, NUM_TOFHIT_THR, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 31), new TGLayoutHints(kLHintsRight));
							pNumberTOFHit_thr->SetWidth(75);
							pNumberTOFHit_thr->Associate(this);
					pF3->AddFrame(pCheckTOF_en = new TGCheckButton(pF3, new TGHotString("TOF_en"), CHK_TOF_EN), new TGLayoutHints(kLHintsLeft));
						pCheckTOF_en->Associate(this);

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pF1->AddFrame(pF2 = new TGGroupFrame(pF1, "Enabled Trigger Terms", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pF2->AddFrame(pTextViewTrigTermsEnabled = new TGTextView(pF2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pTextViewTrigTermsEnabled->SetHeight(100);
			pF1->AddFrame(pF2 = new TGGroupFrame(pF1, "Disabled Trigger Terms", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pF2->AddFrame(pTextViewTrigTermsDisabled = new TGTextView(pF2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					pTextViewTrigTermsDisabled->SetHeight(100);
						
		AddFrame(pCanvasTrigRates = new TRootEmbeddedCanvas("c1", this, 600, 400), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasTrigRates->GetCanvas()->SetBorderMode(0);
			TVirtualPad *pPad = pCanvasTrigRates->GetCanvas()->cd();
				pH_Rate = new TH1D("trigrate", ";;Rate(Hz)", 3, 0, 3);
/*
				pH_Rate->Fill("BCALHITS", 1);
				pH_Rate->Fill("BFCAL", 1);
				pH_Rate->Fill("TAGM", 1);
				pH_Rate->Fill("TAGH", 1);
				pH_Rate->Fill("PS", 1);
				pH_Rate->Fill("ST", 1);
				pH_Rate->Fill("TOF", 1);
				pH_Rate->Fill("TRIGOUT", 1);
				pH_Rate->LabelsDeflate();
*/
				pH_Rate->SetFillColor(49);
				pH_Rate->SetStats(0);
				pH_Rate->GetXaxis()->SetLabelSize(0.05);
				pH_Rate->GetYaxis()->SetLabelSize(0.05);
				pH_Rate->Draw("bar2");
				pPad->SetLogy(1);

		UpdateScalers();
	}
	
	void UpdateScalers()
	{
		TVirtualPad *pPad;
		unsigned int *pScalers;
		int len;

		if(!pM->pCrateMsgClient->ReadScalers(&pScalers, &len))
			return;

		GtpScalers *pGtpScalers = (GtpScalers *)pScalers;

		// BCAL Energy
		pPad = pCanvasTrigRates->GetCanvas()->cd(1);
		pH_Rate->Reset();
		pH_Rate->Fill("BCALHITS", pGtpScalers->Trig_BCal[TrigoutNum]);
		pH_Rate->Fill("BFCAL", pGtpScalers->Trig_BFCal[TrigoutNum]);
		pH_Rate->Fill("TAGM", pGtpScalers->Trig_TAGM[TrigoutNum]);
		pH_Rate->Fill("TAGH", pGtpScalers->Trig_TAGH[TrigoutNum]);
		pH_Rate->Fill("PS", pGtpScalers->Trig_PS[TrigoutNum]);
		pH_Rate->Fill("ST", pGtpScalers->Trig_ST[TrigoutNum]);
		pH_Rate->Fill("TOF", pGtpScalers->Trig_TOF[TrigoutNum]);
		pH_Rate->Fill("TRIGOUT", pGtpScalers->Trig[TrigoutNum]);
		pH_Rate->LabelsDeflate();

		pPad->Modified();
		pPad->Update();

		delete pScalers;
	}
	
	void UpdateControls()
	{

		UpdateTriggerTerms();
	}

	void UpdateTriggerTerms()
	{
		TGText *enabledText = new TGText;
		TGText *disabledText = new TGText;
		TString textLine;

		textLine.Form("BCALHits >= %ld", pNumberBCALHit_thr->GetIntNumber());
		if(pCheckBCALHits_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("BCALEnergy * %ld + FCALEnergy * %ld >= %ld",
				pNumberBCAL_escale->GetIntNumber(),
				pNumberFCAL_escale->GetIntNumber(),
				pNumberBFCAL_thr->GetIntNumber());
		if(pCheckBFCAL_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("TAGM & 0x%08lX", pNumberTAGM_enmsk->GetIntNumber());
		if(pCheckTAGM_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("TAGH & 0x%08lX", pNumberTAGH_enmsk->GetIntNumber());
		if(pCheckTAGH_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("PS & 0x%04lX", pNumberPS_enmsk->GetIntNumber());
		if(pCheckPS_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("bitcount(ST & 0x%08lX) >= %lu",
				pNumberST_enmsk->GetIntNumber(),
				pNumberSTHit_thr->GetIntNumber());
		if(pCheckST_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("(TOFH & 0x%04lX) && (TOFV & 0x%04lX)",
				pNumberTOF_enmsk->GetIntNumber() & 0xFFFF,
				(pNumberTOF_enmsk->GetIntNumber()>>16) & 0xFFFF);
		if(pCheckTOF_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		textLine.Form("bitcount(TOF & 0x%08lX) >= %lu",
				pNumberTOF_enmsk->GetIntNumber(),
				pNumberTOFHit_thr->GetIntNumber());
		if(pCheckTOF_en->IsDown())
			enabledText->InsLine(0, textLine);
		else
			disabledText->InsLine(0, textLine);

		pTextViewTrigTermsEnabled->SetText(enabledText);
		pTextViewTrigTermsEnabled->Update();

		pTextViewTrigTermsDisabled->SetText(disabledText);
		pTextViewTrigTermsDisabled->Update();
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		int v;

		if((GET_MSG(msg) == kC_TEXTENTRY) && (GET_SUBMSG(msg) == kTE_TEXTCHANGED))
		{
			switch(parm1)
			{
				case NUM_WIDTH:
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TrigOutCtrl) & 0xFF00FFFF;
					v |= pNumberTrigoutWidth->GetIntNumber()<<16;
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].TrigOutCtrl, v);
					v = (pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TrigOutCtrl)>>16) & 0xFF;
					pNumberTrigoutWidth->SetIntNumber(v);
					pLabelWidthActual->SetText(Form("Actual Width: %dns", v*4));
					break;
				case NUM_LATENCY:
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TrigOutCtrl) & 0xFFFFF000;
					v |= pNumberTrigoutLatency->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].TrigOutCtrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TrigOutCtrl) & 0xFFF;
					pNumberTrigoutLatency->SetIntNumber(v);
					pLabelLatencyActual->SetText(Form("Actual Latency: %dns", v*4));
					break;
				case NUM_BCALHIT_THR:
					v = pNumberBCALHit_thr->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].BCalCtrl1, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].BCalCtrl1);
					pNumberBCALHit_thr->SetIntNumber(v);
					break;
				case NUM_BCAL_ESCALE:
					v = pNumberBCAL_escale->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].BCalCtrl0, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].BCalCtrl0);
					pNumberBCAL_escale->SetIntNumber(v);
					break;
				case NUM_FCAL_ESCALE:
					v = pNumberFCAL_escale->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].FCalCtrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].FCalCtrl);
					pNumberFCAL_escale->SetIntNumber(v);
					break;
				case NUM_BFCAL_THR:
					v = pNumberBFCAL_thr->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].BFCalCtrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].BFCalCtrl);
					pNumberBFCAL_thr->SetIntNumber(v);
					break;
				case NUM_TAGM_ENMSK:
					v = pNumberTAGM_enmsk->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].TagMCtrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TagMCtrl);
					pNumberTAGM_enmsk->SetIntNumber(v);
					break;
				case NUM_TAGH_ENMSK:
					v = pNumberTAGH_enmsk->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].TagHCtrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TagHCtrl);
					pNumberTAGH_enmsk->SetIntNumber(v);
					break;
				case NUM_PS_ENMSK:
					v = pNumberPS_enmsk->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].PSCtrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].PSCtrl);
					pNumberPS_enmsk->SetIntNumber(v);
					break;
				case NUM_ST_ENMSK:
					v = pNumberST_enmsk->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].STCtrl0, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].STCtrl0);
					pNumberST_enmsk->SetIntNumber(v);
					break;
				case NUM_STHIT_THR:
					v = pNumberSTHit_thr->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].STCtrl1, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].STCtrl1);
					pNumberSTHit_thr->SetIntNumber(v);
					break;
				case NUM_TOF_ENMSK:
					v = pNumberTOF_enmsk->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].TOFCtrl0, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TOFCtrl0);
					pNumberTOF_enmsk->SetIntNumber(v);
					break;
				case NUM_TOFHIT_THR:
					v = pNumberTOFHit_thr->GetIntNumber();
					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].TOFCtrl1, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].TOFCtrl1);
					pNumberTOFHit_thr->SetIntNumber(v);
					break;
				default:
					printf("textentry id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_COMBOBOX))
		{
			switch(parm1)
			{
				case CMB_TRIGOUTNUM:
					TrigoutNum = pComboTrignum->GetSelected();
					// force update of all controls...
					break;

				default:
					printf("combo id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_CHECKBUTTON))
		{
			switch(parm1)
			{
				case CHK_BFCAL_EN:
				case CHK_BCALHITS_EN:
				case CHK_TAGH_EN:
				case CHK_TAGM_EN:
				case CHK_PS_EN:
				case CHK_ST_EN:
				case CHK_TOF_EN:
					v = 0;
					if(pCheckBCALHits_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_BCAL_HITMODULES_EN;
					if(pCheckBFCAL_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_BFCAL_EN;
					if(pCheckTAGH_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_TAGH_PATTERN_EN;
					if(pCheckTAGM_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_TAGM_PATTERN_EN;
					if(pCheckPS_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_PS_COIN_EN;
					if(pCheckST_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_ST_NHITS_EN;
					if(pCheckTOF_en->IsDown())
						v |= GTP_TRIGBIT_CTRL_TOF_NHITS_EN;

					pM->WriteReg32(&pRegs->Trigbits[TrigoutNum].Ctrl, v);
					v = pM->ReadReg32(&pRegs->Trigbits[TrigoutNum].Ctrl);

					if(v & GTP_TRIGBIT_CTRL_BCAL_HITMODULES_EN)
						pCheckBCALHits_en->SetDown(kTRUE, kFALSE);
					else
						pCheckBCALHits_en->SetDown(kFALSE, kFALSE);

					if(v & GTP_TRIGBIT_CTRL_BFCAL_EN)
						pCheckBFCAL_en->SetDown(kTRUE, kFALSE);
					else
						pCheckBFCAL_en->SetDown(kFALSE, kFALSE);

					if(v & GTP_TRIGBIT_CTRL_TAGH_PATTERN_EN)
						pCheckTAGH_en->SetDown(kTRUE, kFALSE);
					else
						pCheckTAGH_en->SetDown(kFALSE, kFALSE);

					if(v & GTP_TRIGBIT_CTRL_TAGM_PATTERN_EN)
						pCheckTAGM_en->SetDown(kTRUE, kFALSE);
					else
						pCheckTAGM_en->SetDown(kFALSE, kFALSE);

					if(v & GTP_TRIGBIT_CTRL_PS_COIN_EN)
						pCheckPS_en->SetDown(kTRUE, kFALSE);
					else
						pCheckTAGM_en->SetDown(kFALSE, kFALSE);

					if(v & GTP_TRIGBIT_CTRL_ST_NHITS_EN)
						pCheckST_en->SetDown(kTRUE, kFALSE);
					else
						pCheckST_en->SetDown(kFALSE, kFALSE);

					if(v & GTP_TRIGBIT_CTRL_TOF_NHITS_EN)
						pCheckTOF_en->SetDown(kTRUE, kFALSE);
					else
						pCheckTOF_en->SetDown(kFALSE, kFALSE);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			switch(parm1)
			{
				case BTN_UPDATE_SCALERS:
					UpdateScalers();
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
			}
		}
		UpdateTriggerTerms();

		return kTRUE;
	}

private:
	enum
	{
		BTN_UPDATE_SCALERS,
		NUM_WIDTH,
		NUM_LATENCY,
		NUM_BCALHIT_THR,
		NUM_BCAL_ESCALE,
		NUM_FCAL_ESCALE,
		NUM_BFCAL_THR,
		NUM_TAGM_ENMSK,
		NUM_TAGH_ENMSK,
		NUM_PS_ENMSK,
		NUM_ST_ENMSK,
		NUM_STHIT_THR,
		NUM_TOF_ENMSK,
		NUM_TOFHIT_THR,
		CHK_BFCAL_EN,
		CHK_BCALHITS_EN,
		CHK_TAGH_EN,
		CHK_TAGM_EN,
		CHK_PS_EN,
		CHK_ST_EN,
		CHK_TOF_EN,
		CMB_TRIGOUTNUM
	};

	int						TrigoutNum;

	ModuleFrame				*pM;
	Gtp_regs					*pRegs;

	TGNumberEntry			*pNumberBCALHit_thr;
	TGNumberEntry			*pNumberBCAL_escale;
	TGNumberEntry			*pNumberFCAL_escale;
	TGNumberEntry			*pNumberBFCAL_thr;
	TGNumberEntry			*pNumberTAGM_enmsk;
	TGNumberEntry			*pNumberTAGH_enmsk;
	TGNumberEntry			*pNumberPS_enmsk;
	TGNumberEntry			*pNumberST_enmsk;
	TGNumberEntry			*pNumberSTHit_thr;
	TGNumberEntry			*pNumberTOF_enmsk;
	TGNumberEntry			*pNumberTOFHit_thr;
	TGNumberEntry			*pNumberTrigoutWidth;
	TGNumberEntry			*pNumberTrigoutLatency;

	TGCheckButton			*pCheckBCALHits_en;
	TGCheckButton			*pCheckBFCAL_en;
	TGCheckButton			*pCheckTAGH_en;
	TGCheckButton			*pCheckTAGM_en;
	TGCheckButton			*pCheckPS_en;
	TGCheckButton			*pCheckST_en;
	TGCheckButton			*pCheckTOF_en;

	TH1D						*pH_Rate;
	TH1D						*pH_Hits;
	
	TGTextView				*pTextViewTrigTermsEnabled;
	TGTextView				*pTextViewTrigTermsDisabled;
	
	TGLabel					*pLabelWidthActual;
	TGLabel					*pLabelLatencyActual;
	TGLabel					*pLabelLatencyStatus;
	
	TGComboBox				*pComboTrignum; 
	
	TRootEmbeddedCanvas	*pCanvasTrigEqu;
	TRootEmbeddedCanvas	*pCanvasTrigRates;
	
	TGTextButton			*pButtonUpdateScalers;
};

#endif
