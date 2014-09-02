#ifndef SSP_Histograms_H
#define SSP_Histograms_H

#include <math.h>
#include "ssp.h"

#define HIST_BIN_CNT		1024
#define HIST_BIN_LIN_MAX	2147483647

#define BTN_LOGMODE			1000
#define BTN_AUTOUPDATE		1001
#define BTN_MANUALUPDATE	1002
#define BTN_HIST_CLONE		100

#define SDR_UPDATETIME		1100

#define EDT_OFFSET				1500

#define CMB_BINWIDTH			2000

#define CMB_ID_BINWIDTH_1		0
#define CMB_ID_BINWIDTH_2		1
#define CMB_ID_BINWIDTH_4		2
#define CMB_ID_BINWIDTH_8		3
#define CMB_ID_BINWIDTH_16		4
#define CMB_ID_BINWIDTH_32		5
#define CMB_ID_BINWIDTH_64		6
#define CMB_ID_BINWIDTH_128		7
#define CMB_ID_BINWIDTH_256		8
#define CMB_ID_BINWIDTH_512		9
#define CMB_ID_BINWIDTH_1024	10
#define CMB_ID_BINWIDTH_2048	11
#define CMB_ID_BINWIDTH_4096	12
#define CMB_ID_BINWIDTH_8192	13
#define CMB_ID_BINWIDTH_16384	14
#define CMB_ID_BINWIDTH_32768	15
#define CMB_ID_BINWIDTH_65536	16
#define CMB_ID_BINWIDTH_131072	17
#define CMB_ID_BINWIDTH_262144	18
#define CMB_ID_BINWIDTH_524288	19
#define CMB_ID_BINWIDTH_1048576	20
#define CMB_ID_BINWIDTH_2097152	21

#define UDPATETIME_MAX	60

class HistoFrame	: public TGCompositeFrame
{
public:
	HistoFrame(const TGWindow *p, VMERemote *pClient, SSP_regs *pSSP_regs, const char *name, int index) : TGCompositeFrame(p, 150, 150)
	{
		static unsigned int histIndex = 0;

		SetLayoutManager(new TGVerticalLayout(this));

		pVMEClient = pClient;
		pSSPregs = pSSP_regs;
		Index = index;

		AddFrame(pCanvas = new TRootEmbeddedCanvas(name, this, 100, 100), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pFrameButtons->AddFrame(pLabelOffset = new TGLabel(pFrameButtons, new TGString("Offset: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			pFrameButtons->AddFrame(pNumberOffset = new TGNumberEntry(pFrameButtons, 0, 6, EDT_OFFSET, TGNumberFormat::kNESInteger), new TGLayoutHints(kLHintsLeft));
				pNumberOffset->SetWidth(80);

			pFrameButtons->AddFrame(pComboBinWidth = new TGComboBox(pFrameButtons, CMB_BINWIDTH), new TGLayoutHints(kLHintsLeft));
				pComboBinWidth->Resize(120, 20);
				pComboBinWidth->AddEntry("BinSize 1", CMB_ID_BINWIDTH_1);
				pComboBinWidth->AddEntry("BinSize 2", CMB_ID_BINWIDTH_2);
				pComboBinWidth->AddEntry("BinSize 4", CMB_ID_BINWIDTH_4);
				pComboBinWidth->AddEntry("BinSize 8", CMB_ID_BINWIDTH_8);
				pComboBinWidth->AddEntry("BinSize 16", CMB_ID_BINWIDTH_16);
				pComboBinWidth->AddEntry("BinSize 32", CMB_ID_BINWIDTH_32);
				pComboBinWidth->AddEntry("BinSize 64", CMB_ID_BINWIDTH_64);
				pComboBinWidth->AddEntry("BinSize 128", CMB_ID_BINWIDTH_128);
				pComboBinWidth->AddEntry("BinSize 256", CMB_ID_BINWIDTH_256);
				pComboBinWidth->AddEntry("BinSize 512", CMB_ID_BINWIDTH_512);
				if(index == 8)
				{
					pComboBinWidth->AddEntry("BinSize 1024", CMB_ID_BINWIDTH_1024);
					pComboBinWidth->AddEntry("BinSize 2048", CMB_ID_BINWIDTH_2048);
					pComboBinWidth->AddEntry("BinSize 4096", CMB_ID_BINWIDTH_4096);
					pComboBinWidth->AddEntry("BinSize 8192", CMB_ID_BINWIDTH_8192);
					pComboBinWidth->AddEntry("BinSize 16384", CMB_ID_BINWIDTH_16384);
					pComboBinWidth->AddEntry("BinSize 32768", CMB_ID_BINWIDTH_32768);
					pComboBinWidth->AddEntry("BinSize 65536", CMB_ID_BINWIDTH_65536);
					pComboBinWidth->AddEntry("BinSize 131072", CMB_ID_BINWIDTH_131072);
					pComboBinWidth->AddEntry("BinSize 262144", CMB_ID_BINWIDTH_262144);
					pComboBinWidth->AddEntry("BinSize 524288", CMB_ID_BINWIDTH_524288);
					pComboBinWidth->AddEntry("BinSize 1048576", CMB_ID_BINWIDTH_1048576);
					pComboBinWidth->AddEntry("BinSize 2097152", CMB_ID_BINWIDTH_2097152);
				}

			pFrameButtons->AddFrame(pButtonCloneGraph = new TGTextButton(pFrameButtons, new TGHotString("Copy"), BTN_HIST_CLONE), new TGLayoutHints(kLHintsRight));
			pFrameButtons->AddFrame(pButtonLogEnabled = new TGTextButton(pFrameButtons, new TGHotString("Linear"), BTN_LOGMODE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonLogEnabled->AllowStayDown(kTRUE);
				pButtonLogEnabled->SetWidth(50);

			pNumberOffset->Associate(this);
			pComboBinWidth->Associate(this);
			pButtonCloneGraph->Associate(this);
			pButtonLogEnabled->Associate(this);
		

		pCanvas->GetCanvas()->SetBorderMode(0);

		pHistTitle = new TGString;
		pHistTitle->Form("%s(%u)", name, histIndex++);

		pGraphHisto = NULL;
		SetHistBins();
		pGraphHisto = new TH1I(pHistTitle->Data(), name, HIST_BIN_CNT, fHistBins);

		pCanvas->GetCanvas()->SetBorderMode(0);
		pGraphHisto->SetFillColor(4);
//		pGraphHisto->GetXaxis()->CenterLabels();
		pCanvas->GetCanvas()->cd();
		pGraphHisto->Draw("bar0");

		ReadSettings();
	}

	~HistoFrame()
	{
		delete pHistTitle;
	}

	void SetHistBins()
	{
		for(int i = 0; i < HIST_BIN_CNT+1; i++)
		{
			if(pButtonLogEnabled->IsDown())
			{
				double expo = (i>>5) + (i&0x1f)/32.0;
				if(Index < 8)
					fHistBins[i] = pow(2.0, expo);
				else
					fHistBins[i] = pow(2.0, expo);
			}
			else
				fHistBins[i] = pNumberOffset->GetIntNumber() + i*pow(2.0, pComboBinWidth->GetSelected());
		}
		if(pGraphHisto)
			pGraphHisto->SetBins(HIST_BIN_CNT, fHistBins);
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		unsigned int val;

		switch(GET_MSG(msg))
		{
			case kC_COMMAND:
				switch(GET_SUBMSG(msg))
				{
					case kCM_COMBOBOX:
						switch(parm1)
						{
							case CMB_BINWIDTH:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HistShift[Index], pComboBinWidth->GetSelected());
								SetHistBins();
								break;
						}
						break;
					case kCM_BUTTON:
						switch(parm1)
						{
							case BTN_HIST_CLONE:
								pCanvas->GetCanvas()->DrawClone();
								break;
							case BTN_LOGMODE:
								if(pButtonLogEnabled->IsDown())
								{
									pButtonLogEnabled->SetText(new TGHotString("Log"));
									pVMEClient->ReadVME32((unsigned int)&pSSPregs->HistLogEnable, &val);
									pVMEClient->WriteVME32((unsigned int)&pSSPregs->HistLogEnable, val | (1<<Index));
								}
								else
								{
									pButtonLogEnabled->SetText(new TGHotString("Linear"));
									pVMEClient->ReadVME32((unsigned int)&pSSPregs->HistLogEnable, &val);
									pVMEClient->WriteVME32((unsigned int)&pSSPregs->HistLogEnable, val & ~(1<<Index));
								}
								SetHistBins();
								break;
						}
						break;
				}
				break;
			case kC_TEXTENTRY:
				switch(GET_SUBMSG(msg))
				{
					case kTE_TEXTCHANGED:
						switch(parm1)
						{
							case EDT_OFFSET:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HistOffset[Index], pNumberOffset->GetIntNumber());
								SetHistBins();
								break;
						}
						break;
				}
				break;
		}
		return kTRUE;
	}

	void ReadSettings()
	{
		unsigned int val;

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->HistShift[Index], &val);
		pComboBinWidth->Select(val, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->HistOffset[Index], &val);
		pNumberOffset->SetIntNumber(val);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->HistLogEnable, &val);
		if(val & (1<<Index))
		{
			pButtonLogEnabled->SetDown(kTRUE, kTRUE);
			pButtonLogEnabled->SetText(new TGHotString("Log"));
		}
		else
		{
			pButtonLogEnabled->SetDown(kFALSE, kTRUE);
			pButtonLogEnabled->SetText(new TGHotString("Linear"));
		}
		SetHistBins();
	}


	VMERemote			*pVMEClient;
	SSP_regs			*pSSPregs;
	int					Index;

	TGHorizontalFrame	*pFrameButtons;

	TGComboBox			*pComboBinWidth;

	TRootEmbeddedCanvas	*pCanvas;
	TH1I				*pGraphHisto;
	TGNumberEntry		*pNumberOffset;
	TGLabel				*pLabelOffset;

	TGTextButton		*pButtonCloneGraph;
	TGTextButton		*pButtonLogEnabled;

	TGString			*pHistTitle;

	double fHistBins[HIST_BIN_CNT+1];
};

class SSP_Histograms	: public TGCompositeFrame
{
public:
	SSP_Histograms(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		pVMEClient = pClient;
		pSSPregs = (SSP_regs *)baseAddr;

		AddFrame(pFrameButtons = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
			pFrameButtons->AddFrame(pButtonAutoUpdate = new TGTextButton(pFrameButtons, new TGHotString("Update Mode: Manual"), BTN_AUTOUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
				pButtonAutoUpdate->SetWidth(80);
				pButtonAutoUpdate->SetEnabled(kTRUE);
				pButtonAutoUpdate->AllowStayDown(kTRUE);
			pFrameButtons->AddFrame(pButtonManualUpdate = new TGTextButton(pFrameButtons, new TGHotString("Manual Update"), BTN_MANUALUPDATE), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
			pFrameButtons->AddFrame(pSliderUpdateTime = new TGHSlider(pFrameButtons, 100, kSlider1 | kScaleBoth, SDR_UPDATETIME), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
				pSliderUpdateTime->SetRange(0, UDPATETIME_MAX);
//				pSliderUpdateTime->SetEnabled(kFALSE);
				pSliderUpdateTime->SetPosition(5);

			pButtonAutoUpdate->Associate(this);
			pButtonManualUpdate->Associate(this);
			pSliderUpdateTime->Associate(this);

		AddFrame(pFrameGraphs[0] = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[0]->AddFrame(pHistoFrames[0] = new HistoFrame(pFrameGraphs[0], pVMEClient, pSSPregs, "SSP Ch0", 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[0]->AddFrame(pHistoFrames[1] = new HistoFrame(pFrameGraphs[0], pVMEClient, pSSPregs, "SSP Ch1", 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[0]->AddFrame(pHistoFrames[2] = new HistoFrame(pFrameGraphs[0], pVMEClient, pSSPregs, "SSP Ch2", 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		
		AddFrame(pFrameGraphs[1] = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[1]->AddFrame(pHistoFrames[3] = new HistoFrame(pFrameGraphs[1], pVMEClient, pSSPregs, "SSP Ch3", 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[1]->AddFrame(pHistoFrames[4] = new HistoFrame(pFrameGraphs[1], pVMEClient, pSSPregs, "SSP Ch4", 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[1]->AddFrame(pHistoFrames[5] = new HistoFrame(pFrameGraphs[1], pVMEClient, pSSPregs, "SSP Ch5", 5), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		

		AddFrame(pFrameGraphs[2] = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[2]->AddFrame(pHistoFrames[6] = new HistoFrame(pFrameGraphs[2], pVMEClient, pSSPregs, "SSP Ch6", 6), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[2]->AddFrame(pHistoFrames[7] = new HistoFrame(pFrameGraphs[2], pVMEClient, pSSPregs, "SSP Ch7", 7), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pFrameGraphs[2]->AddFrame(pHistoFrames[8] = new HistoFrame(pFrameGraphs[2], pVMEClient, pSSPregs, "SSP Ch8", 8), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

		pTimerUpdate = new TTimer(this, 1000*pSliderUpdateTime->GetPosition(), kTRUE);
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
					case BTN_AUTOUPDATE:
						if(pButtonAutoUpdate->IsDown())
						{
							pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Auto"));
//							pSliderUpdateTime->SetEnabled(kTRUE);
							pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
						}
						else
						{
							pButtonAutoUpdate->SetText(new TGHotString("Update Mode: Manual"));
//							pSliderUpdateTime->SetEnabled(kFALSE);
							pTimerUpdate->TurnOff();
						}
						break;
					case BTN_MANUALUPDATE:
						UpdateHistograms();
						break;
					default:
						printf("button id %d pressed\n", (int)parm1);
						break;
				}
				break;
			case kC_HSLIDER:
				switch(parm1)
				{
					case SDR_UPDATETIME:
						pTimerUpdate->TurnOff();
						pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
						break;
					default:
						printf("slider id %d pressed\n", (int)parm1);
						break;
				}
				break;
			}
			break;
		}
		return kTRUE;
	}

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
		{
			UpdateHistograms();
			if(pButtonAutoUpdate->IsDown())
				pTimerUpdate->Start(1000*pSliderUpdateTime->GetPosition(), kTRUE);
		}
		return kTRUE;
	}

	void UpdateHistograms()
	{
		unsigned int binWeight[HIST_BIN_CNT];

		for(int i = 0; i < 9; i++)
			pHistoFrames[i]->pGraphHisto->Reset();
		

		pVMEClient->WriteVME32((unsigned int)&pSSPregs->HistEnable, 0);
		for(int i = 0; i < 9; i++)
		{
			pVMEClient->BlkReadVME32((unsigned int)&pSSPregs->HistData[i], binWeight, HIST_BIN_CNT, 1);

			for(int j = 0; j < HIST_BIN_CNT; j++)
			{
				if(binWeight[j] > 2000000000)
					pHistoFrames[i]->pGraphHisto->Fill(pHistoFrames[i]->fHistBins[j], 2000000000);
				else
					pHistoFrames[i]->pGraphHisto->Fill(pHistoFrames[i]->fHistBins[j], binWeight[j]);
			}
		}
		pVMEClient->WriteVME32((unsigned int)&pSSPregs->HistEnable, 0x1FF);

		for(int i = 0; i < 9; i++)
		{
//			pCanvasHists[i]->GetCanvas()->cd();
//			pGraphHistos[i]->Draw("bar0");
			pHistoFrames[i]->pCanvas->GetCanvas()->Modified();
			pHistoFrames[i]->pCanvas->GetCanvas()->Update();
		}
	}

private:
	VMERemote			*pVMEClient;
	SSP_regs			*pSSPregs;

	TTimer				*pTimerUpdate;

	// Top Frame Objects: pFrameButtons
	TGSlider			*pSliderUpdateTime;
	TGTextButton		*pButtonAutoUpdate;
	TGTextButton		*pButtonManualUpdate;

	// Bottom Frame Objects: pFrameGraphs
	HistoFrame			*pHistoFrames[9];

	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameGraphs[3];
};

#endif
