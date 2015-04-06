#ifndef DCRB_NoisePlots_H
#define DCRB_NoisePlots_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "DCRB.h"

class DCRB_NoisePlots	: public TGCompositeFrame
{
public:
	DCRB_NoisePlots(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (DCRB_regs *)pM->BaseAddr;

		TGCompositeFrame *pTF1;
		TGTextButton *pB;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pTF1->AddFrame(pB = new TGTextButton(pTF1, new TGHotString("Start"), BTN_START), new TGLayoutHints(kLHintsCenterY));
				pB->Associate(this);
			pTF1->AddFrame(pB = new TGTextButton(pTF1, new TGHotString("Stop"), BTN_STOP), new TGLayoutHints(kLHintsCenterY));
				pB->Associate(this);
			pTF1->AddFrame(pB = new TGTextButton(pTF1, new TGHotString("Save"), BTN_SAVE), new TGLayoutHints(kLHintsCenterY));
				pB->Associate(this);

			pTF1->AddFrame(new TGLabel(pTF1, "Min Threshold(mV):"));
			pTF1->AddFrame(pNumEntryMinThreshold = new TGNumberEntry(pTF1, 15, 4, NUM_HISTNUMBINS, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 0.0, 200.0));
				pNumEntryMinThreshold->Associate(this);
			pTF1->AddFrame(new TGLabel(pTF1, "Max Threshold(mV):"));
			pTF1->AddFrame(pNumEntryMaxThreshold = new TGNumberEntry(pTF1, 60, 4, NUM_HISTNUMBINS, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAPositive, TGNumberFormat::kNELLimitMinMax, 0.0, 200.0));
				pNumEntryMaxThreshold->Associate(this);

		TGLayoutHints *hint = 0;
		TGLayoutHints *fHintTL  = new TGLayoutHints(kLHintsTop | kLHintsLeft);

	   TGCanvas *fGCanvas2 = new TGCanvas(this, 300, 300, 0);
	   TGCompositeFrame *fFRE2 = new TGCompositeFrame(fGCanvas2->GetViewPort(),400,300, kVerticalFrame);
	   fGCanvas2->SetContainer(fFRE2);
	   pCanvas = new TRootEmbeddedCanvas("canvasB",fFRE2,450*6,375*16);
	   fFRE2->AddFrame(pCanvas, fHintTL);
	   hint = new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 5);
	   AddFrame(fGCanvas2, hint);

		pCanvas->GetCanvas()->Divide(6, 16, 0.001, 0.001);

		for(int i = 0; i < 96; i++)
		{
			pHistThresholdHits[i] = new TH1D(Form("Ch%d Threshold & Noise", i+1), NULL, 10, 0.0, 10.0);
			pHistThresholdHits[i]->SetStats(kFALSE);
			pHistThresholdHits[i]->SetMarkerColor(4);
			pHistThresholdHits[i]->SetMarkerSize(1);
			pHistThresholdHits[i]->SetMarkerStyle(6);
			pHistThresholdHits[i]->SetLineColor(4);

			pHistThresholdHitsDerivative[i] = new TH1D(Form("Ch%d Threshold & Noise", i+1), NULL, 10, 0.0, 10.0);
			pHistThresholdHitsDerivative[i]->SetFillColor(4);
			pHistThresholdHitsDerivative[i]->SetStats(kTRUE);
			pHistThresholdHitsDerivative[i]->SetMarkerColor(2);
			pHistThresholdHitsDerivative[i]->SetMarkerSize(1);
			pHistThresholdHitsDerivative[i]->SetMarkerStyle(6);
			pHistThresholdHitsDerivative[i]->SetLineColor(2);

			pFuncThresholdHitsFit[i] = new TF1(Form("fa%d", i+1), "[0]*(1+TMath::Erf([1]*([2]-x)))", 10.0, 60.0);
			pFuncThresholdHitsFit[i]->SetLineColor(4);
		}
		
		Reg_DAC = (volatile unsigned int *)((int)pM->BaseAddr + 0x0024);
		Reg_PulserPeriod = (volatile unsigned int *)((int)pM->BaseAddr + 0x0280);
		Reg_PulserLowCycles = (volatile unsigned int *)((int)pM->BaseAddr + 0x0284);
		Reg_PulserNPulses = (volatile unsigned int *)((int)pM->BaseAddr + 0x0288);
		Reg_PulserStart = (volatile unsigned int *)((int)pM->BaseAddr + 0x028C);
		Reg_PulserDone = (volatile unsigned int *)((int)pM->BaseAddr + 0x0290);
		Reg_SD_DCE0 = (volatile unsigned int *)((int)pM->BaseAddr + 0x0200);
		Reg_SD_DCE1 = (volatile unsigned int *)((int)pM->BaseAddr + 0x0204);
		Reg_SD_DCE2 = (volatile unsigned int *)((int)pM->BaseAddr + 0x0208);
		Reg_SD_FCE0 = (volatile unsigned int *)((int)pM->BaseAddr + 0x020C);
		Reg_SD_FCE1 = (volatile unsigned int *)((int)pM->BaseAddr + 0x0210);
		Reg_SD_FCE2 = (volatile unsigned int *)((int)pM->BaseAddr + 0x0214);
		Reg_ScalerLatch = (volatile unsigned int *)((int)pM->BaseAddr + 0x0300);
		Reg_ScalerClk50 = (volatile unsigned int *)((int)pM->BaseAddr + 0x0304);
		
		for(int i = 0; i < 96; i++)
		{
			int offset = 0x1100+4*(i%16)+0x200*(i/16);
			Reg_Scaler[i] = (volatile unsigned int *)((int)pM->BaseAddr + offset);
		}
		
		SetupPulser(0x38, 500.0, 0.0, 20.0, 10, 1.0E-6);
		SetThreshold(-100.0);
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
					case BTN_START:
						Start();
						break;
					case BTN_STOP:
						Stop();
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
				break;
			}
		}
		return kTRUE;
	}
	
	void SetupPulser(int grp_mask, double offset_mv, double low_mv, double high_mv, int width, double period)
	{
		printf("mask=0x%02X,offset=%d,low=%d,high=%d,width=%d,period=%d\n", grp_mask, (int)offset_mv, (int)low_mv, (int)high_mv, width, (int)period);
		WriteDac(1, high_mv/2.0+2048.0);
		WriteDac(2, low_mv/2.0+2048.0);
		WriteDac(3, -offset_mv+2048.0);
		
		int per = (int)(period*125000000.0);
		pM->WriteReg32(Reg_PulserPeriod, per);
		pM->WriteReg32(Reg_PulserLowCycles, per-width);
		pM->WriteReg32(Reg_PulserNPulses, 0xFFFFFFFF);
		
		if(grp_mask & 0x1)	pM->WriteReg32(Reg_SD_DCE0, 18);
		else						pM->WriteReg32(Reg_SD_DCE0, 0);
			
		if(grp_mask & 0x2)	pM->WriteReg32(Reg_SD_DCE1, 18);
		else						pM->WriteReg32(Reg_SD_DCE1, 0);

		if(grp_mask & 0x4)	pM->WriteReg32(Reg_SD_DCE2, 18);
		else						pM->WriteReg32(Reg_SD_DCE2, 0);

		if(grp_mask & 0x8)	pM->WriteReg32(Reg_SD_FCE0, 18);
		else						pM->WriteReg32(Reg_SD_FCE0, 0);

		if(grp_mask & 0x10)	pM->WriteReg32(Reg_SD_FCE1, 18);
		else						pM->WriteReg32(Reg_SD_FCE1, 0);

		if(grp_mask & 0x20)	pM->WriteReg32(Reg_SD_FCE2, 18);
		else						pM->WriteReg32(Reg_SD_FCE2, 0);
	}

	void SetThreshold(double mv)
	{
		mv = (mv * 8.06) + 2048.0;
		int dac;
		
		if(mv < 0.0) dac = 0;
		if(mv > 4095.0) dac = 4095;
		
		WriteDac(0, dac);
	}
	
	void WriteDac(int ch, int val)
	{
		pM->WriteReg32(Reg_DAC, 0xC0000);						// NRST=1,NLD=1,NCS=0,WR=0
		pM->WriteReg32(Reg_DAC, 0xD0000 | val | (ch<<14));	// NRST=1,NLD=1,NCS=0,WR=1
		pM->Delay(1);
		pM->WriteReg32(Reg_DAC, 0x80000);						// NRST=1,NLD=0,NCS=0,WR=0
		pM->WriteReg32(Reg_DAC, 0xC0000);						// NRST=1,NLD=1,NCS=0,WR=0
	}

	void SetLocalTest(Bool_t en)
	{
/*
		unsigned int val = pM->ReadReg32(&pRegs->TestPulseConfig);
		if(en)
			val = 0x3f<<0;
		else
			val &= ~(0x3f<<0);
		pM->WriteReg32(&pRegs->TestPulseConfig, val);
*/
	}

	void Start()
	{
		int i;
		double minThreshold = pNumEntryMinThreshold->GetNumber();
		double maxThreshold = pNumEntryMaxThreshold->GetNumber();
		double CurrentThreshold;
		unsigned int ref, scalers[96];
		double dref;

		if(minThreshold >= maxThreshold)
			return;

		for(i = 0; i < 96; i++)
		{
			pHistThresholdHits[i]->SetBins(4*(1+maxThreshold-minThreshold), minThreshold, maxThreshold);
			pHistThresholdHits[i]->Clear();

			pHistThresholdHitsDerivative[i]->SetBins(4*(1+maxThreshold-minThreshold), minThreshold, maxThreshold);;
			pHistThresholdHitsDerivative[i]->Clear();

			pFuncThresholdHitsFit[i]->SetRange(minThreshold, maxThreshold);

			pCanvas->GetCanvas()->cd(i+i);
			pCanvas->GetCanvas()->GetPad(i+1)->Clear();
		}

		CurrentThreshold = minThreshold;
		SetLocalTest(1);
		for(CurrentThreshold = minThreshold; CurrentThreshold <= maxThreshold; CurrentThreshold+= 1)	//1mV steps
		{
			SetThreshold(CurrentThreshold);
			
			pM->WriteReg32(Reg_ScalerLatch, 1);
			pM->WriteReg32(Reg_ScalerLatch, 0);
			gSystem->Sleep(1000);
			pM->WriteReg32(Reg_ScalerLatch, 1);

			ref = pM->ReadReg32(Reg_ScalerClk50);
			
			pM->BlkReadReg32(Reg_Scaler[0], &scalers[0], 16, CRATE_MSG_FLAGS_ADRINC);
			pM->BlkReadReg32(Reg_Scaler[16], &scalers[16], 16, CRATE_MSG_FLAGS_ADRINC);
			pM->BlkReadReg32(Reg_Scaler[32], &scalers[32], 16, CRATE_MSG_FLAGS_ADRINC);
			pM->BlkReadReg32(Reg_Scaler[48], &scalers[48], 16, CRATE_MSG_FLAGS_ADRINC);
			pM->BlkReadReg32(Reg_Scaler[64], &scalers[64], 16, CRATE_MSG_FLAGS_ADRINC);
			pM->BlkReadReg32(Reg_Scaler[80], &scalers[80], 16, CRATE_MSG_FLAGS_ADRINC);

			if(ref)
				dref = ref;
			else
				dref = 1.0;

			for(int i = 0; i < 96; i++)
				pHistThresholdHits[i]->Fill(CurrentThreshold, (double)scalers[i] * 50.0E6 / dref);

			printf("CurrentThreshold=%lf\n", CurrentThreshold);
		}
		SetLocalTest(0);

		TCanvas *pCstats = new TCanvas("c1", "c1", 800, 600);
		TH1D *pHthreshold = new TH1D("h_threshold", "Pulser Thresholds", 96, 0.0, 96.0);
		TH1D *pHrms = new TH1D("h_rms", "Pulser RMS Noise", 96, 0.0, 96.0);

		pHthreshold->SetFillColor(4);
		pHrms->SetFillColor(2);

		for(i = 0; i < 96; i++)
		{
			pCanvas->GetCanvas()->cd(i+1);

			double max = pHistThresholdHits[i]->GetMaximum() / 2.0;
			double thr = pHistThresholdHits[i]->GetBinCenter(pHistThresholdHits[i]->FindLastBinAbove(max/2.0));

			pFuncThresholdHitsFit[i]->SetParameters(max, 1.0, thr);
			pHistThresholdHits[i]->Fit(pFuncThresholdHitsFit[i], "0");

			for(CurrentThreshold = minThreshold; CurrentThreshold <= maxThreshold; CurrentThreshold+= 0.25)	//250uV steps
				pHistThresholdHitsDerivative[i]->Fill(CurrentThreshold, -1.0*pFuncThresholdHitsFit[i]->Derivative(CurrentThreshold));

			pHistThresholdHitsDerivative[i]->GetYaxis()->SetRangeUser(0.0, pHistThresholdHits[i]->GetMaximum());
			pHistThresholdHitsDerivative[i]->Draw("P");
			pFuncThresholdHitsFit[i]->Draw("SAME");
			pHistThresholdHits[i]->Draw("PSAME");

			pHthreshold->Fill((double)i, pHistThresholdHitsDerivative[i]->GetMean());
			pHrms->Fill((double)i, pHistThresholdHitsDerivative[i]->GetRMS());
		}
		pCstats->Divide(1,2,0.001,0.001);
		pCstats->cd(1);
		pHthreshold->Draw("bar0");
		pCstats->cd(2);
		pHrms->Draw("bar0");
	}

	void Stop()
	{
	}

	void MeasureRates(int thr, int bin)
	{

	}
private:

	enum Buttons
	{
		BTN_START,
		BTN_STOP,
		BTN_SAVE
	};

	ModuleFrame				*pM;
	DCRB_regs				*pRegs;

	TH1D						*pHistThresholdHits[96];
	TH1D						*pHistThresholdHitsDerivative[96];
	TF1						*pFuncThresholdHitsFit[96];

	TRootEmbeddedCanvas	*pCanvas;
	TCanvas					*pC;

	TGNumberEntry			*pNumEntryMinThreshold;
	TGNumberEntry			*pNumEntryMaxThreshold;
	
	volatile unsigned int	*Reg_DAC;
	volatile unsigned int	*Reg_PulserPeriod;
	volatile unsigned int	*Reg_PulserLowCycles;
	volatile unsigned int	*Reg_PulserNPulses;
	volatile unsigned int	*Reg_PulserStart;
	volatile unsigned int	*Reg_PulserDone;
	volatile unsigned int	*Reg_SD_DCE0;
	volatile unsigned int	*Reg_SD_DCE1;
	volatile unsigned int	*Reg_SD_DCE2;
	volatile unsigned int	*Reg_SD_FCE0;
	volatile unsigned int	*Reg_SD_FCE1;
	volatile unsigned int	*Reg_SD_FCE2;
	volatile unsigned int	*Reg_ScalerLatch;
	volatile unsigned int	*Reg_Scaler[96];
	volatile unsigned int	*Reg_ScalerClk50;
};

#endif
