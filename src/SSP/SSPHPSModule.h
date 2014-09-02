#ifndef SSPHPSModule_H
#define SSPHPSModule_H

#include "RootHeader.h"
#include "VMERemote.h"
//#include "SSP_Histograms.h"
//#include "SSP_WaveCapture.h"
#include "SSP_Config.h"
#include "SSPHPS_EnergyHist.h"
#include "SSPHPS_PositionHist.h"
#include "SSPHPS_LatencyHist.h"
#include "SSP_Status.h"
#include "SSP_Scalers.h"
#include "ModuleFrame.h"

class SSPHPSModule	: public ModuleFrame
{
public:
	SSPHPSModule(const TGWindow *p, VMERemote *pRemoteClient, unsigned int baseAddr) : ModuleFrame(p, pRemoteClient, baseAddr)
	{
		SetLayoutManager(new TGVerticalLayout(this));

		TGCompositeFrame *tFrame;
		AddFrame(pSSPTabs = new TGTab(this), new TGLayoutHints(kLHintsBottom | kLHintsRight | kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("Config");			tFrame->AddFrame(pSSPConfig = new SSP_Config(tFrame, pVMEClient, BaseAddr, SSP_MODE_HPS), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("Scalers");			tFrame->AddFrame(pSSPScalers = new SSP_Scalers(tFrame, pVMEClient, BaseAddr, SSP_MODE_HPS), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("ClusterEnergy");		tFrame->AddFrame(pSSPHPS_EnergyHist = new SSPHPS_EnergyHist(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("ClusterPosition");	tFrame->AddFrame(pSSPHPS_PositionHist = new SSPHPS_PositionHist(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("ClusterLatency");	tFrame->AddFrame(pSSPHPS_LatencyHist = new SSPHPS_LatencyHist(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		tFrame = pSSPTabs->AddTab("Status");			tFrame->AddFrame(pSSPStatus = new SSP_Status(tFrame, pVMEClient, BaseAddr, SSP_MODE_HPS), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("Histograms");	tFrame->AddFrame(pSSPHistograms = new SSP_Histograms(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
//		tFrame = pSSPTabs->AddTab("WaveCapture");	tFrame->AddFrame(pSSPWaveCapture = new SSP_WaveCapture(tFrame, pVMEClient, BaseAddr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
	}

	const char *GetModuleName() { return "SSPHPS"; }
	const char *GetModuleFullName() { return "Sub System Processor(HPS Config)"; }

private:
	//SSP_Histograms		*pSSPHistograms;
	//SSP_WaveCapture		*pSSPWaveCapture;
	SSP_Config				*pSSPConfig;
	SSP_Status				*pSSPStatus;
	SSP_Scalers				*pSSPScalers;
	SSPHPS_EnergyHist		*pSSPHPS_EnergyHist;
	SSPHPS_PositionHist		*pSSPHPS_PositionHist;
	SSPHPS_LatencyHist		*pSSPHPS_LatencyHist;

	TGTab					*pSSPTabs;
};

#endif
