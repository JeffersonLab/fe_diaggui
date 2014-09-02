#ifndef SSP_Config_H
#define SSP_Config_H

#include "RootHeader.h"
#include "ssp.h"
#include "SSP_ConfigUtils.h"

#define EDT_BOTTOMDELAY			200
#define EDT_CLUSTERCOINCIDENCE	201
#define EDT_PAIRSUMMAX			202
#define EDT_PAIRDIFFMAX			203
#define EDT_EDTHRESHOLD			204
#define EDT_MAXENERGY			205
#define EDT_MINENERGY			206

#define CMB_TRIGGERMODE			400
#define CMB_ID_SEL_PAIREDCLUSTERS		0
#define CMB_ID_SEL_TOPCLUSTERS			1
#define CMB_ID_SEL_BOTCLUSTERS			2
#define CMB_ID_SEL_DISABLEDCLUSTERS		3

#define CMB_SYNCSRC				3000
#define CMB_CLOCKSRC			3001
#define CMB_GPIONIMA			3002
#define CMB_GPIONIMB			3003
#define CMB_GPIOLVDS0			3004
#define CMB_GPIOLVDS1			3005
#define CMB_GPIOLVDS2			3006
#define CMB_GPIOLVDS3			3007

#define CHK_FIBER_EN0			120
#define CHK_FIBER_EN1			121
#define CHK_FIBER_EN2			122
#define CHK_FIBER_EN3			123
#define CHK_FIBER_EN4			124
#define CHK_FIBER_EN5			125
#define CHK_FIBER_EN6			126
#define CHK_FIBER_EN7			127
#define CHK_TRIG_SUM			130
#define CHK_TRIG_DIFF			131
#define CHK_TRIG_ED				132
#define CHK_TRIG_COPLANAR		133

#define CMB_ID_SYNCSRC_NIMA		CFG_SYNC_SRC_NIMA
#define CMB_ID_SYNCSRC_NIMB		CFG_SYNC_SRC_NIMB
#define CMB_ID_SYNCSRC_LVDS0	CFG_SYNC_SRC_LVDS0
#define CMB_ID_SYNCSRC_LVDS1	CFG_SYNC_SRC_LVDS1
#define CMB_ID_SYNCSRC_LVDS2	CFG_SYNC_SRC_LVDS2
#define CMB_ID_SYNCSRC_LVDS3	CFG_SYNC_SRC_LVDS3
#define CMB_ID_SYNCSRC_SWB		CFG_SYNC_SRC_P0
#define CMB_ID_SYNCSRC_DISABLE	CFG_SYNC_SRC_NONE

#define CMB_ID_CLOCKSRC_SWA		CFG_CLOCK_SRC_SWA
#define CMB_ID_CLOCKSRC_SWB		CFG_CLOCK_SRC_SWB
#define CMB_ID_CLOCKSRC_SMA		CFG_CLOCK_SRC_SMA
#define CMB_ID_CLOCKSRC_LOCAL	CFG_CLOCK_SRC_LOCAL

#define CMB_ID_SEL_NIMA			GPIO_MUXSEL_NIMA
#define CMB_ID_SEL_NIMB			GPIO_MUXSEL_NIMB
#define CMB_ID_SEL_LVDS0		GPIO_MUXSEL_LVDS0
#define CMB_ID_SEL_LVDS1		GPIO_MUXSEL_LVDS1
#define CMB_ID_SEL_LVDS2		GPIO_MUXSEL_LVDS2
#define CMB_ID_SEL_LVDS3		GPIO_MUXSEL_LVDS3
#define CMB_ID_SEL_CLK100		GPIO_MUXSEL_CLK100
#define CMB_ID_SEL_CLK200		GPIO_MUXSEL_CLK200
#define CMB_ID_SEL_CLK125		GPIO_MUXSEL_CLK125
#define CMB_ID_SEL_CLK250		GPIO_MUXSEL_CLK250
#define CMB_ID_SEL_PULSER0		GPIO_MUXSEL_PULSER0
#define CMB_ID_SEL_PULSER1		GPIO_MUXSEL_PULSER1
#define CMB_ID_SEL_PULSER2		GPIO_MUXSEL_PULSER2
#define CMB_ID_SEL_PULSER3		GPIO_MUXSEL_PULSER3
#define CMB_ID_SEL_PULSER4		GPIO_MUXSEL_PULSER4
#define CMB_ID_SEL_DISC0		GPIO_MUXSEL_DISC0
#define CMB_ID_SEL_DISC1		GPIO_MUXSEL_DISC1
#define CMB_ID_SEL_DISC2		GPIO_MUXSEL_DISC2
#define CMB_ID_SEL_DISC3		GPIO_MUXSEL_DISC3
#define CMB_ID_SEL_FORCE0		(GPIO_MUXSEL_VMEREG | GPIO_VMEREG_0)
#define CMB_ID_SEL_FORCE1		(GPIO_MUXSEL_VMEREG | GPIO_VMEREG_1)
#define CMB_ID_SEL_INPUT		(GPIO_MUXSEL_VMEREG | GPIO_VMEREG_0)

class SSP_Config	: public TGCompositeFrame
{
public:
	SSP_Config(const TGWindow *p, VMERemote *pClient, unsigned int baseAddr, unsigned int mode = 0) : TGCompositeFrame(p, 400, 400)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		Mode = mode;
		pVMEClient = pClient;
		pSSPregs = (SSP_regs *)baseAddr;

		TGCompositeFrame *pTF1, *pTF2, *pTF3, *pTF4;

		AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTF1->AddFrame(pTF2 = new TGVerticalFrame(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsLeft));
				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelSync = new TGLabel(pTF3, new TGString("Sync Source: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboSync = new TGComboBox(pTF3, CMB_SYNCSRC), new TGLayoutHints(kLHintsRight));
						pComboSync->Resize(150, 20);
						pComboSync->AddEntry("GPIO NIM A", CMB_ID_SYNCSRC_NIMA);
						pComboSync->AddEntry("GPIO NIM B", CMB_ID_SYNCSRC_NIMB);
						pComboSync->AddEntry("GPIO LVDS 0", CMB_ID_SYNCSRC_LVDS0);
						pComboSync->AddEntry("GPIO LVDS 1", CMB_ID_SYNCSRC_LVDS1);
						pComboSync->AddEntry("GPIO LVDS 2", CMB_ID_SYNCSRC_LVDS2);
						pComboSync->AddEntry("GPIO LVDS 3", CMB_ID_SYNCSRC_LVDS3);
						pComboSync->AddEntry("VXS SWITCH B", CMB_ID_SYNCSRC_SWB);
						pComboSync->AddEntry("DISABLED", CMB_ID_SYNCSRC_DISABLE);

				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelClock = new TGLabel(pTF3, new TGString("Clock Source: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboClock = new TGComboBox(pTF3, CMB_CLOCKSRC), new TGLayoutHints(kLHintsRight));
						pComboClock->Resize(150, 20);
						pComboClock->AddEntry("VXS SWITCH A", CMB_ID_CLOCKSRC_SWA);
						pComboClock->AddEntry("VXS SWITCH B", CMB_ID_CLOCKSRC_SWB);
						pComboClock->AddEntry("SMA", CMB_ID_CLOCKSRC_SMA);
						pComboClock->AddEntry("LOCAL OSC", CMB_ID_CLOCKSRC_LOCAL);

				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelNIMA = new TGLabel(pTF3, new TGString("GPIO NIMA: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboNIMA = new TGComboBox(pTF3, CMB_GPIONIMA), new TGLayoutHints(kLHintsRight));
						pComboNIMA->Resize(150, 20);
						pComboNIMA->AddEntry("DISABLED", CMB_ID_SEL_NIMA);
						pComboNIMA->AddEntry("GPIO NIM B", CMB_ID_SEL_NIMB);
						pComboNIMA->AddEntry("GPIO LVDS 0", CMB_ID_SEL_LVDS0);
						pComboNIMA->AddEntry("GPIO LVDS 1", CMB_ID_SEL_LVDS1);
						pComboNIMA->AddEntry("GPIO LVDS 2", CMB_ID_SEL_LVDS2);
						pComboNIMA->AddEntry("GPIO LVDS 3", CMB_ID_SEL_LVDS3);
						pComboNIMA->AddEntry("CLK 100MHZ", CMB_ID_SEL_CLK100);
						pComboNIMA->AddEntry("CLK 200MHZ", CMB_ID_SEL_CLK200);
						pComboNIMA->AddEntry("CLK 125MHZ", CMB_ID_SEL_CLK125);
						pComboNIMA->AddEntry("CLK 250MHZ", CMB_ID_SEL_CLK250);
						pComboNIMA->AddEntry("PULSER 0", CMB_ID_SEL_PULSER0);
						pComboNIMA->AddEntry("PULSER 1", CMB_ID_SEL_PULSER1);
						pComboNIMA->AddEntry("PULSER 2", CMB_ID_SEL_PULSER2);
						pComboNIMA->AddEntry("PULSER 3", CMB_ID_SEL_PULSER3);
						pComboNIMA->AddEntry("PULSER 4", CMB_ID_SEL_PULSER4);
						if(Mode == SSP_MODE_NORMAL)
						{
							pComboNIMA->AddEntry("DISCRIMINATOR 0", CMB_ID_SEL_DISC0);
							pComboNIMA->AddEntry("DISCRIMINATOR 1", CMB_ID_SEL_DISC1);
							pComboNIMA->AddEntry("DISCRIMINATOR 2", CMB_ID_SEL_DISC2);
							pComboNIMA->AddEntry("DISCRIMINATOR 3", CMB_ID_SEL_DISC3);
						}
						else if(Mode == SSP_MODE_HPS)
							pComboNIMA->AddEntry("HPS TRIGGER", CMB_ID_SEL_DISC0);

						pComboNIMA->AddEntry("LOGIC 0", CMB_ID_SEL_FORCE0);
						pComboNIMA->AddEntry("LOGIC 1", CMB_ID_SEL_FORCE1);
						pComboNIMA->AddEntry("INPUT ONLY", CMB_ID_SEL_INPUT);

				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelNIMB = new TGLabel(pTF3, new TGString("GPIO NIMB: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboNIMB = new TGComboBox(pTF3, CMB_GPIONIMB), new TGLayoutHints(kLHintsRight));
						pComboNIMB->Resize(150, 20);
						pComboNIMB->AddEntry("DISABLED", CMB_ID_SEL_NIMB);
						pComboNIMB->AddEntry("GPIO NIM A", CMB_ID_SEL_NIMA);
						pComboNIMB->AddEntry("GPIO LVDS 0", CMB_ID_SEL_LVDS0);
						pComboNIMB->AddEntry("GPIO LVDS 1", CMB_ID_SEL_LVDS1);
						pComboNIMB->AddEntry("GPIO LVDS 2", CMB_ID_SEL_LVDS2);
						pComboNIMB->AddEntry("GPIO LVDS 3", CMB_ID_SEL_LVDS3);
						pComboNIMB->AddEntry("CLK 100MHZ", CMB_ID_SEL_CLK100);
						pComboNIMB->AddEntry("CLK 200MHZ", CMB_ID_SEL_CLK200);
						pComboNIMB->AddEntry("CLK 125MHZ", CMB_ID_SEL_CLK125);
						pComboNIMB->AddEntry("CLK 250MHZ", CMB_ID_SEL_CLK250);
						pComboNIMB->AddEntry("PULSER 0", CMB_ID_SEL_PULSER0);
						pComboNIMB->AddEntry("PULSER 1", CMB_ID_SEL_PULSER1);
						pComboNIMB->AddEntry("PULSER 2", CMB_ID_SEL_PULSER2);
						pComboNIMB->AddEntry("PULSER 3", CMB_ID_SEL_PULSER3);
						pComboNIMB->AddEntry("PULSER 4", CMB_ID_SEL_PULSER4);
						if(Mode == SSP_MODE_NORMAL)
						{
							pComboNIMB->AddEntry("DISCRIMINATOR 0", CMB_ID_SEL_DISC0);
							pComboNIMB->AddEntry("DISCRIMINATOR 1", CMB_ID_SEL_DISC1);
							pComboNIMB->AddEntry("DISCRIMINATOR 2", CMB_ID_SEL_DISC2);
							pComboNIMB->AddEntry("DISCRIMINATOR 3", CMB_ID_SEL_DISC3);
						}
						else if(Mode == SSP_MODE_HPS)
							pComboNIMB->AddEntry("HPS TRIGGER", CMB_ID_SEL_DISC0);

						pComboNIMB->AddEntry("LOGIC 0", CMB_ID_SEL_FORCE0);
						pComboNIMB->AddEntry("LOGIC 1", CMB_ID_SEL_FORCE1);
						pComboNIMB->AddEntry("INPUT ONLY", CMB_ID_SEL_INPUT);

				if(Mode == SSP_MODE_NORMAL)
				{
					pTF2->AddFrame(pDiscConfig0 = new DiscriminatorConfig(pTF2, pVMEClient, pSSPregs, "Discriminator 0", 0), new TGLayoutHints(kLHintsExpandX  | kLHintsExpandY, 2, 2, 2, 2));
					pTF2->AddFrame(pDiscConfig1 = new DiscriminatorConfig(pTF2, pVMEClient, pSSPregs, "Discriminator 1", 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
					pTF2->AddFrame(pDiscConfig2 = new DiscriminatorConfig(pTF2, pVMEClient, pSSPregs, "Discriminator 2", 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
					pTF2->AddFrame(pDiscConfig3 = new DiscriminatorConfig(pTF2, pVMEClient, pSSPregs, "Discriminator 3", 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				}
				else if(Mode == SSP_MODE_HPS)
				{
					pTF2->AddFrame(pTF3 = new TGGroupFrame(pTF2, "HPS Config", kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Bottom Cluster Delay(4ns ticks): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberBottomDelay = new TGNumberEntry(pTF4, 0, 4, EDT_BOTTOMDELAY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 1023), new TGLayoutHints(kLHintsRight));
								pNumberBottomDelay->SetWidth(100);

						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Cluster Coincidence(+/- 4ns ticks): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberClusterCoincidence = new TGNumberEntry(pTF4, 0, 4, EDT_CLUSTERCOINCIDENCE, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 15), new TGLayoutHints(kLHintsRight));
								pNumberClusterCoincidence->SetWidth(100);

						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Pair Sum Max: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberPairSumMax = new TGNumberEntry(pTF4, 0, 4, EDT_PAIRSUMMAX, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
								pNumberPairSumMax->SetWidth(100);

						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Pair Diff Max: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberPairDiffMax = new TGNumberEntry(pTF4, 0, 4, EDT_PAIRDIFFMAX, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
								pNumberPairDiffMax->SetWidth(100);

						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Distance*Energy Threshold: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberEDThreshold = new TGNumberEntry(pTF4, 0, 4, EDT_EDTHRESHOLD, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
								pNumberEDThreshold->SetWidth(100);

						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Cluster Energy Max: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberMaxEnergy = new TGNumberEntry(pTF4, 0, 4, EDT_MAXENERGY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
								pNumberMaxEnergy->SetWidth(100);

						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Cluster Energy Min: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pNumberMinEnergy = new TGNumberEntry(pTF4, 0, 4, EDT_MINENERGY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsRight));
								pNumberMinEnergy->SetWidth(100);

					pTF2->AddFrame(pTF3 = new TGGroupFrame(pTF2, "HPS Trigger Cuts", kVerticalFrame), new TGLayoutHints(kLHintsExpandX));
						pTF3->AddFrame(pCheckTriggerCutSum = new TGCheckButton(pTF3, new TGHotString("Cluster Sum"), CHK_TRIG_SUM), new TGLayoutHints(kLHintsLeft));
						pTF3->AddFrame(pCheckTriggerCutDiff = new TGCheckButton(pTF3, new TGHotString("Cluster Diff"), CHK_TRIG_DIFF), new TGLayoutHints(kLHintsLeft));
						pTF3->AddFrame(pCheckTriggerCutED = new TGCheckButton(pTF3, new TGHotString("Cluster Energy-Distance"), CHK_TRIG_ED), new TGLayoutHints(kLHintsLeft));
						pTF3->AddFrame(pCheckTriggerCutCoplanar = new TGCheckButton(pTF3, new TGHotString("Cluster Coplanar"), CHK_TRIG_COPLANAR), new TGLayoutHints(kLHintsLeft));
						
						pTF3->AddFrame(pTF4 = new TGHorizontalFrame(pTF3), new TGLayoutHints(kLHintsExpandX));
							pTF4->AddFrame(new TGLabel(pTF4, new TGString("Trigger Mode: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
							pTF4->AddFrame(pComboTriggerMode = new TGComboBox(pTF4, CMB_TRIGGERMODE), new TGLayoutHints(kLHintsRight));
								pComboTriggerMode->Resize(150, 20);
								pComboTriggerMode->AddEntry("PAIRED CLUSTERS", CMB_ID_SEL_PAIREDCLUSTERS);
								pComboTriggerMode->AddEntry("TOP CLUSTERS", CMB_ID_SEL_TOPCLUSTERS);
								pComboTriggerMode->AddEntry("BOTTOM CLUSTERS", CMB_ID_SEL_BOTCLUSTERS);
								pComboTriggerMode->AddEntry("DISABLED", CMB_ID_SEL_DISABLEDCLUSTERS);
				}

				pTF2->AddFrame(pTF3 = new TGGroupFrame(pTF2, "Latency", kHorizontalFrame), new TGLayoutHints(kLHintsExpandX));
					pTF3->AddFrame(pLabelLatency = new TGLabel(pTF3, new TGString("Trigger Latency(4ns ticks): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pNumberLatency = new TGNumberEntry(pTF3, 0, 4, EDT_LATENCY, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 1023), new TGLayoutHints(kLHintsRight));
						pNumberLatency->SetWidth(100);

			pTF1->AddFrame(pTF2 = new TGVerticalFrame(pTF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight));
				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelLVDS0 = new TGLabel(pTF3, new TGString("GPIO LVDS0: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboLVDS0 = new TGComboBox(pTF3, CMB_GPIOLVDS0), new TGLayoutHints(kLHintsRight));
						pComboLVDS0->Resize(150, 20);
						pComboLVDS0->AddEntry("GPIO NIM A", CMB_ID_SEL_NIMA);
						pComboLVDS0->AddEntry("GPIO NIM B", CMB_ID_SEL_NIMB);
						pComboLVDS0->AddEntry("GPIO LVDS 1", CMB_ID_SEL_LVDS1);
						pComboLVDS0->AddEntry("GPIO LVDS 2", CMB_ID_SEL_LVDS2);
						pComboLVDS0->AddEntry("GPIO LVDS 3", CMB_ID_SEL_LVDS3);
						pComboLVDS0->AddEntry("CLK 100MHZ", CMB_ID_SEL_CLK100);
						pComboLVDS0->AddEntry("CLK 200MHZ", CMB_ID_SEL_CLK200);
						pComboLVDS0->AddEntry("CLK 125MHZ", CMB_ID_SEL_CLK125);
						pComboLVDS0->AddEntry("CLK 250MHZ", CMB_ID_SEL_CLK250);
						pComboLVDS0->AddEntry("PULSER 0", CMB_ID_SEL_PULSER0);
						pComboLVDS0->AddEntry("PULSER 1", CMB_ID_SEL_PULSER1);
						pComboLVDS0->AddEntry("PULSER 2", CMB_ID_SEL_PULSER2);
						pComboLVDS0->AddEntry("PULSER 3", CMB_ID_SEL_PULSER3);
						pComboLVDS0->AddEntry("PULSER 4", CMB_ID_SEL_PULSER4);
						if(Mode == SSP_MODE_NORMAL)
						{
							pComboLVDS0->AddEntry("DISCRIMINATOR 0", CMB_ID_SEL_DISC0);
							pComboLVDS0->AddEntry("DISCRIMINATOR 1", CMB_ID_SEL_DISC1);
							pComboLVDS0->AddEntry("DISCRIMINATOR 2", CMB_ID_SEL_DISC2);
							pComboLVDS0->AddEntry("DISCRIMINATOR 3", CMB_ID_SEL_DISC3);
						}
						else if(Mode == SSP_MODE_HPS)
							pComboLVDS0->AddEntry("HPS TRIGGER", CMB_ID_SEL_DISC0);

						pComboLVDS0->AddEntry("LOGIC 0", CMB_ID_SEL_FORCE0);
						pComboLVDS0->AddEntry("LOGIC 1", CMB_ID_SEL_FORCE1);

				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelLVDS1 = new TGLabel(pTF3, new TGString("GPIO LVDS1: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboLVDS1 = new TGComboBox(pTF3, CMB_GPIOLVDS1), new TGLayoutHints(kLHintsRight));
						pComboLVDS1->Resize(150, 20);
						pComboLVDS1->AddEntry("GPIO NIM A", CMB_ID_SEL_NIMA);
						pComboLVDS1->AddEntry("GPIO NIM B", CMB_ID_SEL_NIMB);
						pComboLVDS1->AddEntry("GPIO LVDS 0", CMB_ID_SEL_LVDS0);
						pComboLVDS1->AddEntry("GPIO LVDS 1", CMB_ID_SEL_LVDS1);
						pComboLVDS1->AddEntry("GPIO LVDS 2", CMB_ID_SEL_LVDS2);
						pComboLVDS1->AddEntry("GPIO LVDS 3", CMB_ID_SEL_LVDS3);
						pComboLVDS1->AddEntry("CLK 100MHZ", CMB_ID_SEL_CLK100);
						pComboLVDS1->AddEntry("CLK 200MHZ", CMB_ID_SEL_CLK200);
						pComboLVDS1->AddEntry("CLK 125MHZ", CMB_ID_SEL_CLK125);
						pComboLVDS1->AddEntry("CLK 250MHZ", CMB_ID_SEL_CLK250);
						pComboLVDS1->AddEntry("PULSER 0", CMB_ID_SEL_PULSER0);
						pComboLVDS1->AddEntry("PULSER 1", CMB_ID_SEL_PULSER1);
						pComboLVDS1->AddEntry("PULSER 2", CMB_ID_SEL_PULSER2);
						pComboLVDS1->AddEntry("PULSER 3", CMB_ID_SEL_PULSER3);
						pComboLVDS1->AddEntry("PULSER 4", CMB_ID_SEL_PULSER4);
						if(Mode == SSP_MODE_NORMAL)
						{
							pComboLVDS1->AddEntry("DISCRIMINATOR 0", CMB_ID_SEL_DISC0);
							pComboLVDS1->AddEntry("DISCRIMINATOR 1", CMB_ID_SEL_DISC1);
							pComboLVDS1->AddEntry("DISCRIMINATOR 2", CMB_ID_SEL_DISC2);
							pComboLVDS1->AddEntry("DISCRIMINATOR 3", CMB_ID_SEL_DISC3);
						}
						else if(Mode == SSP_MODE_HPS)
							pComboLVDS1->AddEntry("HPS TRIGGER", CMB_ID_SEL_DISC0);

						pComboLVDS1->AddEntry("LOGIC 0", CMB_ID_SEL_FORCE0);
						pComboLVDS1->AddEntry("LOGIC 1", CMB_ID_SEL_FORCE1);

				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelLVDS2 = new TGLabel(pTF3, new TGString("GPIO LVDS2: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboLVDS2 = new TGComboBox(pTF3, CMB_GPIOLVDS2), new TGLayoutHints(kLHintsRight));
						pComboLVDS2->Resize(150, 20);
						pComboLVDS2->AddEntry("GPIO NIM A", CMB_ID_SEL_NIMA);
						pComboLVDS2->AddEntry("GPIO NIM B", CMB_ID_SEL_NIMB);
						pComboLVDS2->AddEntry("GPIO LVDS 0", CMB_ID_SEL_LVDS0);
						pComboLVDS2->AddEntry("GPIO LVDS 1", CMB_ID_SEL_LVDS1);
						pComboLVDS2->AddEntry("GPIO LVDS 2", CMB_ID_SEL_LVDS2);
						pComboLVDS2->AddEntry("GPIO LVDS 3", CMB_ID_SEL_LVDS3);
						pComboLVDS2->AddEntry("CLK 100MHZ", CMB_ID_SEL_CLK100);
						pComboLVDS2->AddEntry("CLK 200MHZ", CMB_ID_SEL_CLK200);
						pComboLVDS2->AddEntry("CLK 125MHZ", CMB_ID_SEL_CLK125);
						pComboLVDS2->AddEntry("CLK 250MHZ", CMB_ID_SEL_CLK250);
						pComboLVDS2->AddEntry("PULSER 0", CMB_ID_SEL_PULSER0);
						pComboLVDS2->AddEntry("PULSER 1", CMB_ID_SEL_PULSER1);
						pComboLVDS2->AddEntry("PULSER 2", CMB_ID_SEL_PULSER2);
						pComboLVDS2->AddEntry("PULSER 3", CMB_ID_SEL_PULSER3);
						pComboLVDS2->AddEntry("PULSER 4", CMB_ID_SEL_PULSER4);
						if(Mode == SSP_MODE_NORMAL)
						{
							pComboLVDS2->AddEntry("DISCRIMINATOR 0", CMB_ID_SEL_DISC0);
							pComboLVDS2->AddEntry("DISCRIMINATOR 1", CMB_ID_SEL_DISC1);
							pComboLVDS2->AddEntry("DISCRIMINATOR 2", CMB_ID_SEL_DISC2);
							pComboLVDS2->AddEntry("DISCRIMINATOR 3", CMB_ID_SEL_DISC3);
						}
						else if(Mode == SSP_MODE_HPS)
							pComboLVDS2->AddEntry("HPS TRIGGER", CMB_ID_SEL_DISC0);

						pComboLVDS2->AddEntry("LOGIC 0", CMB_ID_SEL_FORCE0);
						pComboLVDS2->AddEntry("LOGIC 1", CMB_ID_SEL_FORCE1);

				pTF2->AddFrame(pTF3 = new TGHorizontalFrame(pTF2), new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 2, 2, 2, 2));
					pTF3->AddFrame(pLabelLVDS3 = new TGLabel(pTF3, new TGString("GPIO LVDS3: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
					pTF3->AddFrame(pComboLVDS3 = new TGComboBox(pTF3, CMB_GPIOLVDS3), new TGLayoutHints(kLHintsRight));
						pComboLVDS3->Resize(150, 20);
						pComboLVDS3->AddEntry("GPIO NIM A", CMB_ID_SEL_NIMA);
						pComboLVDS3->AddEntry("GPIO NIM B", CMB_ID_SEL_NIMB);
						pComboLVDS3->AddEntry("GPIO LVDS 0", CMB_ID_SEL_LVDS0);
						pComboLVDS3->AddEntry("GPIO LVDS 1", CMB_ID_SEL_LVDS1);
						pComboLVDS3->AddEntry("GPIO LVDS 2", CMB_ID_SEL_LVDS2);
						pComboLVDS3->AddEntry("GPIO LVDS 3", CMB_ID_SEL_LVDS3);
						pComboLVDS3->AddEntry("CLK 100MHZ", CMB_ID_SEL_CLK100);
						pComboLVDS3->AddEntry("CLK 200MHZ", CMB_ID_SEL_CLK200);
						pComboLVDS3->AddEntry("CLK 125MHZ", CMB_ID_SEL_CLK125);
						pComboLVDS3->AddEntry("CLK 250MHZ", CMB_ID_SEL_CLK250);
						pComboLVDS3->AddEntry("PULSER 0", CMB_ID_SEL_PULSER0);
						pComboLVDS3->AddEntry("PULSER 1", CMB_ID_SEL_PULSER1);
						pComboLVDS3->AddEntry("PULSER 2", CMB_ID_SEL_PULSER2);
						pComboLVDS3->AddEntry("PULSER 3", CMB_ID_SEL_PULSER3);
						pComboLVDS3->AddEntry("PULSER 4", CMB_ID_SEL_PULSER4);
						if(Mode == SSP_MODE_NORMAL)
						{
							pComboLVDS3->AddEntry("DISCRIMINATOR 0", CMB_ID_SEL_DISC0);
							pComboLVDS3->AddEntry("DISCRIMINATOR 1", CMB_ID_SEL_DISC1);
							pComboLVDS3->AddEntry("DISCRIMINATOR 2", CMB_ID_SEL_DISC2);
							pComboLVDS3->AddEntry("DISCRIMINATOR 3", CMB_ID_SEL_DISC3);
						}
						else if(Mode == SSP_MODE_HPS)
							pComboLVDS3->AddEntry("HPS TRIGGER", CMB_ID_SEL_DISC0);

						pComboLVDS3->AddEntry("LOGIC 0", CMB_ID_SEL_FORCE0);
						pComboLVDS3->AddEntry("LOGIC 1", CMB_ID_SEL_FORCE1);

				pTF2->AddFrame(pPulserConfig0 = new PulserConfig(pTF2, pVMEClient, pSSPregs, "Pulser 0", 0), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pTF2->AddFrame(pPulserConfig1 = new PulserConfig(pTF2, pVMEClient, pSSPregs, "Pulser 1", 1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pTF2->AddFrame(pPulserConfig2 = new PulserConfig(pTF2, pVMEClient, pSSPregs, "Pulser 2", 2), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pTF2->AddFrame(pPulserConfig3 = new PulserConfig(pTF2, pVMEClient, pSSPregs, "Pulser 3", 3), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
				pTF2->AddFrame(pPulserConfig4 = new PulserConfig(pTF2, pVMEClient, pSSPregs, "Pulser 4", 4), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

			AddFrame(pTF1 = new TGGroupFrame(this, "Fiber Enable", kHorizontalFrame), new TGLayoutHints(kLHintsExpandX));
				pTF1->AddFrame(pCheckButtonFiberEnable[0] = new TGCheckButton(pTF1, new TGHotString("CH0"), CHK_FIBER_EN0), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[1] = new TGCheckButton(pTF1, new TGHotString("CH1"), CHK_FIBER_EN1), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[2] = new TGCheckButton(pTF1, new TGHotString("CH2"), CHK_FIBER_EN2), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[3] = new TGCheckButton(pTF1, new TGHotString("CH3"), CHK_FIBER_EN3), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[4] = new TGCheckButton(pTF1, new TGHotString("CH4"), CHK_FIBER_EN4), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[5] = new TGCheckButton(pTF1, new TGHotString("CH5"), CHK_FIBER_EN5), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[6] = new TGCheckButton(pTF1, new TGHotString("CH6"), CHK_FIBER_EN6), new TGLayoutHints(kLHintsCenterX));
				pTF1->AddFrame(pCheckButtonFiberEnable[7] = new TGCheckButton(pTF1, new TGHotString("CH7"), CHK_FIBER_EN7), new TGLayoutHints(kLHintsCenterX));

		ReadSettings();

		pComboSync->Associate(this);
		pComboClock->Associate(this);
		pComboNIMA->Associate(this);
		pComboNIMB->Associate(this);
		pComboLVDS0->Associate(this);
		pComboLVDS1->Associate(this);
		pComboLVDS2->Associate(this);
		pComboLVDS3->Associate(this);
		pNumberLatency->Associate(this);
		pComboTriggerMode->Associate(this);
		pNumberBottomDelay->Associate(this);
		pNumberClusterCoincidence->Associate(this);
		pNumberPairSumMax->Associate(this);
		pNumberPairDiffMax->Associate(this);
		pNumberEDThreshold->Associate(this);
		pNumberMaxEnergy->Associate(this);
		pNumberMinEnergy->Associate(this);
		pCheckTriggerCutSum->Associate(this);
		pCheckTriggerCutDiff->Associate(this);
		pCheckTriggerCutED->Associate(this);
		pCheckTriggerCutCoplanar->Associate(this);

		for(int i = 0; i < 8; i++)
			pCheckButtonFiberEnable[i]->Associate(this);
	}

	void ReadSettings()
	{
		unsigned int val;

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->Config, &val);
		pComboSync->Select(val & CFG_SYNC_SRC_MASK, kFALSE);
		pComboClock->Select(val & CFG_CLOCK_SRC_MASK, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->NIM_IO[0], &val);
		if((val & GPIO_MUXSEL_MASK) == GPIO_MUXSEL_VMEREG)
			pComboNIMA->Select(val & (GPIO_MUXSEL_MASK | GPIO_OUTPUT_MASK), kFALSE);
		else
			pComboNIMA->Select(val & GPIO_MUXSEL_MASK, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->NIM_IO[1], &val);
		if((val & GPIO_MUXSEL_MASK) == GPIO_MUXSEL_VMEREG)
			pComboNIMB->Select(val & (GPIO_MUXSEL_MASK | GPIO_OUTPUT_MASK), kFALSE);
		else
			pComboNIMB->Select(val & GPIO_MUXSEL_MASK, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->LVDS_IO[0], &val);
		if((val & GPIO_MUXSEL_MASK) == GPIO_MUXSEL_VMEREG)
			pComboLVDS0->Select(val & (GPIO_MUXSEL_MASK | GPIO_OUTPUT_MASK), kFALSE);
		else
			pComboLVDS0->Select(val & GPIO_MUXSEL_MASK, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->LVDS_IO[1], &val);
		if((val & GPIO_MUXSEL_MASK) == GPIO_MUXSEL_VMEREG)
			pComboLVDS1->Select(val & (GPIO_MUXSEL_MASK | GPIO_OUTPUT_MASK), kFALSE);
		else
			pComboLVDS1->Select(val & GPIO_MUXSEL_MASK, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->LVDS_IO[2], &val);
		if((val & GPIO_MUXSEL_MASK) == GPIO_MUXSEL_VMEREG)
			pComboLVDS2->Select(val & (GPIO_MUXSEL_MASK | GPIO_OUTPUT_MASK), kFALSE);
		else
			pComboLVDS2->Select(val & GPIO_MUXSEL_MASK, kFALSE);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->LVDS_IO[3], &val);
		if((val & GPIO_MUXSEL_MASK) == GPIO_MUXSEL_VMEREG)
			pComboLVDS3->Select(val & (GPIO_MUXSEL_MASK | GPIO_OUTPUT_MASK), kFALSE);
		else
			pComboLVDS3->Select(val & GPIO_MUXSEL_MASK, kFALSE);

		if(Mode == SSP_MODE_NORMAL)
		{
			pVMEClient->ReadVME32((unsigned int)&pSSPregs->FLConfig, &val);
			pNumberLatency->SetIntNumber(val & 0x3FFF);
		}
		else if(Mode == SSP_MODE_HPS)
		{
			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerLatency, &val);
			pNumberLatency->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.Conincidence, &val);
			pNumberClusterCoincidence->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.Delay, &val);
			pNumberBottomDelay->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.EDSlope, &val);
			pNumberEDThreshold->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.EMax, &val);
			pNumberMaxEnergy->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.EMin, &val);
			pNumberMinEnergy->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.PairDiffMax, &val);
			pNumberPairDiffMax->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.PairSumMax, &val);
			pNumberPairSumMax->SetIntNumber(val);

			pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, &val);
			pComboTriggerMode->Select((val>>4) & 0x3, kFALSE);
			if(val & 0x1)	pCheckTriggerCutSum->SetOn(kTRUE);
			else			pCheckTriggerCutSum->SetOn(kFALSE);
			if(val & 0x2)	pCheckTriggerCutDiff->SetOn(kTRUE);
			else			pCheckTriggerCutDiff->SetOn(kFALSE);
			if(val & 0x4)	pCheckTriggerCutED->SetOn(kTRUE);
			else			pCheckTriggerCutED->SetOn(kFALSE);
			if(val & 0x8)	pCheckTriggerCutCoplanar->SetOn(kTRUE);
			else			pCheckTriggerCutCoplanar->SetOn(kFALSE);
		}

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
		unsigned int bit = SSPCFG_CHANNEL_0;
		for(int i = 0; i < 8; i++)
		{
			if(val & bit)
			{
//				EnableFiberPort(i, kTRUE);
				pCheckButtonFiberEnable[i]->SetOn(kTRUE);
			}
			else
			{
//				EnableFiberPort(i, kFALSE);
				pCheckButtonFiberEnable[i]->SetOn(kFALSE);
			}
			bit<<= 1;
		}
	}

	void EnableFiberPort(int port, Bool_t enable)
	{
		if((port >= 0) && (port < 4))
		{
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->LinkA[port].Control, 0x1);
			if(enable)
				pVMEClient->WriteVME32((unsigned int)&pSSPregs->LinkA[port].Control, 0x0);
		}
		else if((port >= 4) && (port < 8))
		{
			pVMEClient->WriteVME32((unsigned int)&pSSPregs->LinkB[port-4].Control, 0x1);
			if(enable)
				pVMEClient->WriteVME32((unsigned int)&pSSPregs->LinkB[port-4].Control, 0x0);
		}
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		unsigned int val;

		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_CHECKBUTTON:
				switch(parm1)
				{
					case CHK_FIBER_EN0:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(0, pCheckButtonFiberEnable[0]->IsDown());
						if(pCheckButtonFiberEnable[0]->IsDown())
							val |= SSPCFG_CHANNEL_0;
						else
							val &= ~SSPCFG_CHANNEL_0;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN1:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(1, pCheckButtonFiberEnable[1]->IsDown());
						if(pCheckButtonFiberEnable[1]->IsDown())
							val |= SSPCFG_CHANNEL_1;
						else
							val &= ~SSPCFG_CHANNEL_1;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN2:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(2, pCheckButtonFiberEnable[2]->IsDown());
						if(pCheckButtonFiberEnable[2]->IsDown())
							val |= SSPCFG_CHANNEL_2;
						else
							val &= ~SSPCFG_CHANNEL_2;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN3:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(3, pCheckButtonFiberEnable[3]->IsDown());
						if(pCheckButtonFiberEnable[3]->IsDown())
							val |= SSPCFG_CHANNEL_3;
						else
							val &= ~SSPCFG_CHANNEL_3;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN4:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(4, pCheckButtonFiberEnable[4]->IsDown());
						if(pCheckButtonFiberEnable[4]->IsDown())
							val |= SSPCFG_CHANNEL_4;
						else
							val &= ~SSPCFG_CHANNEL_4;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN5:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(5, pCheckButtonFiberEnable[5]->IsDown());
						if(pCheckButtonFiberEnable[5]->IsDown())
							val |= SSPCFG_CHANNEL_5;
						else
							val &= ~SSPCFG_CHANNEL_5;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN6:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(6, pCheckButtonFiberEnable[6]->IsDown());
						if(pCheckButtonFiberEnable[6]->IsDown())
							val |= SSPCFG_CHANNEL_6;
						else
							val &= ~SSPCFG_CHANNEL_6;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_FIBER_EN7:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->SSPConfig, &val);
						EnableFiberPort(7, pCheckButtonFiberEnable[7]->IsDown());
						if(pCheckButtonFiberEnable[7]->IsDown())
							val |= SSPCFG_CHANNEL_7;
						else
							val &= ~SSPCFG_CHANNEL_7;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->SSPConfig, val);
						break;
					case CHK_TRIG_SUM:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, &val);
						if(pCheckTriggerCutSum->IsDown())	val |= 0x1;
						else								val &= ~0x1;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, val);
						break;
					case CHK_TRIG_DIFF:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, &val);
						if(pCheckTriggerCutDiff->IsDown())	val |= 0x2;
						else								val &= ~0x2;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, val);
						break;
					case CHK_TRIG_ED:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, &val);
						if(pCheckTriggerCutED->IsDown())	val |= 0x4;
						else								val &= ~0x4;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, val);
						break;
					case CHK_TRIG_COPLANAR:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, &val);
						if(pCheckTriggerCutCoplanar->IsDown())	val |= 0x8;
						else									val &= ~0x8;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, val);
						break;
				}
			case kCM_COMBOBOX:
				switch(parm1)
				{
					case CMB_SYNCSRC:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->Config, &val);
						val &= ~CFG_SYNC_SRC_MASK;
						val |= pComboSync->GetSelected() & CFG_SYNC_SRC_MASK;
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, val);
						break;
					case CMB_CLOCKSRC:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->Config, &val);
						val &= ~CFG_CLOCK_SRC_MASK;
						val |= (pComboClock->GetSelected() & CFG_CLOCK_SRC_MASK);
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, val | CFG_RESET);
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Config, val);
						break;
					case CMB_GPIONIMA:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->NIM_IO[0], pComboNIMA->GetSelected());
						break;
					case CMB_GPIONIMB:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->NIM_IO[1], pComboNIMB->GetSelected());
						break;
					case CMB_GPIOLVDS0:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->LVDS_IO[0], pComboLVDS0->GetSelected());
						break;
					case CMB_GPIOLVDS1:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->LVDS_IO[1], pComboLVDS1->GetSelected());
						break;
					case CMB_GPIOLVDS2:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->LVDS_IO[2], pComboLVDS2->GetSelected());
						break;
					case CMB_GPIOLVDS3:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->LVDS_IO[3], pComboLVDS3->GetSelected());
						break;
					case CMB_TRIGGERMODE:
						pVMEClient->ReadVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, &val);
						val = (val & 0xFFFFFFCF) | ((pComboTriggerMode->GetSelected() & 0x3)<<4);
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TriggerCutEnable, val);
						break;
				}
			}
			break;
			case kC_TEXTENTRY:
				switch(GET_SUBMSG(msg))
				{
					case kTE_TEXTCHANGED:
						switch(parm1)
						{
							case EDT_LATENCY:
								if(Mode == SSP_MODE_NORMAL)
									pVMEClient->WriteVME32((unsigned int)&pSSPregs->FLConfig, pNumberLatency->GetIntNumber());
								else if(Mode == SSP_MODE_HPS)
									pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.TriggerLatency, pNumberLatency->GetIntNumber());
								break;
							case EDT_BOTTOMDELAY:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.Delay, pNumberBottomDelay->GetIntNumber());
								break;
							case EDT_CLUSTERCOINCIDENCE:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.Conincidence, pNumberClusterCoincidence->GetIntNumber());
								break;
							case EDT_PAIRSUMMAX:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.PairSumMax, pNumberPairSumMax->GetIntNumber());
								break;
							case EDT_PAIRDIFFMAX:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.PairDiffMax, pNumberPairDiffMax->GetIntNumber());
								break;
							case EDT_EDTHRESHOLD:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.EDSlope, pNumberEDThreshold->GetIntNumber());
								break;
							case EDT_MAXENERGY:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.EMax, pNumberMaxEnergy->GetIntNumber());
								break;
							case EDT_MINENERGY:
								pVMEClient->WriteVME32((unsigned int)&pSSPregs->HPSRegs.EMin, pNumberMinEnergy->GetIntNumber());
								break;
						}
						break;
				}
				break;
		}
		return kTRUE;
	}

private:
	VMERemote			*pVMEClient;
	SSP_regs			*pSSPregs;
	unsigned int		Mode;

	TGLabel				*pLabelSync;
	TGLabel				*pLabelClock;
	TGLabel				*pLabelNIMA;
	TGLabel				*pLabelNIMB;
	TGLabel				*pLabelLVDS0;
	TGLabel				*pLabelLVDS1;
	TGLabel				*pLabelLVDS2;
	TGLabel				*pLabelLVDS3;
	TGLabel				*pLabelLatency;

	TGComboBox			*pComboSync;
	TGComboBox			*pComboClock;
	TGComboBox			*pComboNIMA;
	TGComboBox			*pComboNIMB;
	TGComboBox			*pComboLVDS0;
	TGComboBox			*pComboLVDS1;
	TGComboBox			*pComboLVDS2;
	TGComboBox			*pComboLVDS3;
	TGComboBox			*pComboTriggerMode;

	TGNumberEntry		*pNumberLatency;
	TGNumberEntry		*pNumberBottomDelay;
	TGNumberEntry		*pNumberClusterCoincidence;
	TGNumberEntry		*pNumberPairSumMax;
	TGNumberEntry		*pNumberPairDiffMax;
	TGNumberEntry		*pNumberEDThreshold;
	TGNumberEntry		*pNumberMaxEnergy;
	TGNumberEntry		*pNumberMinEnergy;

	DiscriminatorConfig	*pDiscConfig0;
	DiscriminatorConfig	*pDiscConfig1;
	DiscriminatorConfig	*pDiscConfig2;
	DiscriminatorConfig	*pDiscConfig3;

	PulserConfig		*pPulserConfig0;
	PulserConfig		*pPulserConfig1;
	PulserConfig		*pPulserConfig2;
	PulserConfig		*pPulserConfig3;
	PulserConfig		*pPulserConfig4;

	TGCheckButton		*pCheckButtonFiberEnable[8];
	TGCheckButton		*pCheckTriggerCutSum;
	TGCheckButton		*pCheckTriggerCutDiff;
	TGCheckButton		*pCheckTriggerCutED;
	TGCheckButton		*pCheckTriggerCutCoplanar;
};

#endif
