#ifndef SSP_ConfigUtils_H
#define SSP_ConfigUtils_H

#include "RootHeader.h"
#include "ssp.h"

#define RAD_MODE_TOT			4000
#define RAD_MODE_UPD			4001
#define RAD_MODE_NONUPD			4002
#define RAD_MODE_DISABLED		4003

#define EDT_THRESHOLD			100
#define EDT_PULSEWIDTH			101
#define EDT_PERIOD				102
#define EDT_DUTYCYCLE			103
#define EDT_PHASE				104
#define EDT_LATENCY				105

class DiscriminatorConfig : public TGGroupFrame
{
public:
	DiscriminatorConfig(const TGWindow *p, VMERemote *pClient, SSP_regs *pSSP_regs, const char *name, int index) : TGGroupFrame(p, name, kVerticalFrame)
	{
		iIndex = index;

		pVMEClient = pClient;
		pSSPregs = pSSP_regs;

		AddFrame(pFrameRadio = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));
			pFrameRadio->AddFrame(pRadioModeTot = new TGRadioButton(pFrameRadio, "&TOT", RAD_MODE_TOT), new TGLayoutHints(kLHintsExpandX | kLHintsTop, 0, 0, 0, 0));
			pFrameRadio->AddFrame(pRadioModeUpd = new TGRadioButton(pFrameRadio, "&UP", RAD_MODE_UPD), new TGLayoutHints(kLHintsExpandX | kLHintsTop, 0, 0, 0, 0));
			pFrameRadio->AddFrame(pRadioModeNonUpd = new TGRadioButton(pFrameRadio, "&NUP", RAD_MODE_NONUPD), new TGLayoutHints(kLHintsExpandX | kLHintsTop, 0, 0, 0, 0));
			pFrameRadio->AddFrame(pRadioModeDisabled = new TGRadioButton(pFrameRadio, "&DIS", RAD_MODE_DISABLED), new TGLayoutHints(kLHintsExpandX | kLHintsTop, 0, 0, 0, 0));

		AddFrame(pFrameThreshold = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));
			pFrameThreshold->AddFrame(pLabelThreshold = new TGLabel(pFrameThreshold, new TGString("Threshold: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			pFrameThreshold->AddFrame(pNumberThreshold = new TGNumberEntry(pFrameThreshold, 0, 6, EDT_THRESHOLD, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 0x7FFFFFFF), new TGLayoutHints(kLHintsRight));
				pNumberThreshold->SetWidth(100);

		AddFrame(pFramePulseWidth = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));
			pFramePulseWidth->AddFrame(pLabelPulseWidth = new TGLabel(pFramePulseWidth, new TGString("PulseWidth(ns): ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			pFramePulseWidth->AddFrame(pNumberPulseWidth = new TGNumberEntry(pFramePulseWidth, 0, 6, EDT_PULSEWIDTH, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 0x7FFFFFFF), new TGLayoutHints(kLHintsRight));
				pNumberPulseWidth->SetWidth(100);

		ReadSettings();

		pRadioModeTot->Associate(this);
		pRadioModeUpd->Associate(this);
		pRadioModeNonUpd->Associate(this);
		pNumberPulseWidth->Associate(this);
		pNumberThreshold->Associate(this);
	}

	void ReadSettings()
	{
		unsigned int val;

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Threshold, &val);
		pNumberThreshold->SetIntNumber(val);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->Discriminators[iIndex].PulseWidth, &val);
		pNumberPulseWidth->SetIntNumber(val);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Mode, &val);
		val &= DISC_MODE_MASK;
		switch(val)
		{
			case DISC_MODE_DISABLE:
				pRadioModeTot->SetState(kButtonUp);
				pRadioModeUpd->SetState(kButtonUp);
				pRadioModeNonUpd->SetState(kButtonUp);
				pRadioModeDisabled->SetState(kButtonDown);
				break;
			case DISC_MODE_NONUPDATING:
				pRadioModeTot->SetState(kButtonUp);
				pRadioModeUpd->SetState(kButtonUp);
				pRadioModeNonUpd->SetState(kButtonDown);
				pRadioModeDisabled->SetState(kButtonUp);
				break;
			case DISC_MODE_UPDATING:
				pRadioModeTot->SetState(kButtonUp);
				pRadioModeUpd->SetState(kButtonDown);
				pRadioModeNonUpd->SetState(kButtonUp);
				pRadioModeDisabled->SetState(kButtonUp);
				break;
			case DISC_MODE_TOT:
				pRadioModeTot->SetState(kButtonDown);
				pRadioModeUpd->SetState(kButtonUp);
				pRadioModeNonUpd->SetState(kButtonUp);
				pRadioModeDisabled->SetState(kButtonUp);
				break;
		}

	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
				case kCM_RADIOBUTTON:
					switch(parm1)
					{
						case RAD_MODE_TOT:
							pRadioModeTot->SetState(kButtonDown);
							pRadioModeUpd->SetState(kButtonUp);
							pRadioModeNonUpd->SetState(kButtonUp);
							pRadioModeDisabled->SetState(kButtonUp);
							pVMEClient->WriteVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Mode, DISC_MODE_TOT);
							break;
						case RAD_MODE_UPD:
							pRadioModeTot->SetState(kButtonUp);
							pRadioModeUpd->SetState(kButtonDown);
							pRadioModeNonUpd->SetState(kButtonUp);
							pRadioModeDisabled->SetState(kButtonUp);
							pVMEClient->WriteVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Mode, DISC_MODE_UPDATING);
							break;
						case RAD_MODE_NONUPD:
							pRadioModeTot->SetState(kButtonUp);
							pRadioModeUpd->SetState(kButtonUp);
							pRadioModeNonUpd->SetState(kButtonDown);
							pRadioModeDisabled->SetState(kButtonUp);
							pVMEClient->WriteVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Mode, DISC_MODE_NONUPDATING);
							break;
						case RAD_MODE_DISABLED:
							pRadioModeTot->SetState(kButtonUp);
							pRadioModeUpd->SetState(kButtonUp);
							pRadioModeNonUpd->SetState(kButtonUp);
							pRadioModeDisabled->SetState(kButtonDown);
							pVMEClient->WriteVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Mode, DISC_MODE_DISABLE);
							break;
					}
					break;

			}
		case kC_TEXTENTRY:
			switch(GET_SUBMSG(msg))
			{
				case kTE_TEXTCHANGED:
					switch(parm1)
					{
						case EDT_THRESHOLD:
							pVMEClient->WriteVME32((unsigned int)&pSSPregs->Discriminators[iIndex].Threshold, pNumberThreshold->GetIntNumber());
							break;
						case EDT_PULSEWIDTH:
							pVMEClient->WriteVME32((unsigned int)&pSSPregs->Discriminators[iIndex].PulseWidth, pNumberPulseWidth->GetIntNumber());
							break;
					}
					break;
			}
			break;
		}
		return kTRUE;
	}

	int iIndex;

	VMERemote			*pVMEClient;
	SSP_regs			*pSSPregs;

	TGHorizontalFrame	*pFrameRadio;
	TGHorizontalFrame	*pFrameThreshold;
	TGHorizontalFrame	*pFramePulseWidth;

	TGRadioButton		*pRadioModeTot;
	TGRadioButton		*pRadioModeUpd;
	TGRadioButton		*pRadioModeNonUpd;
	TGRadioButton		*pRadioModeDisabled;

	TGLabel				*pLabelThreshold;
	TGLabel				*pLabelPulseWidth;

	TGNumberEntry		*pNumberThreshold;
	TGNumberEntry		*pNumberPulseWidth;
};

class PulserConfig : public TGGroupFrame
{
public:
	PulserConfig(const TGWindow *p, VMERemote *pClient, SSP_regs *pSSP_regs, const char *name, int index) : TGGroupFrame(p, name, kVerticalFrame)
	{
		iIndex = index;

		pVMEClient = pClient;
		pSSPregs = pSSP_regs;

		AddFrame(pFramePeriod = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));
			pFramePeriod->AddFrame(pLabelPeriod = new TGLabel(pFramePeriod, new TGString("Period: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			pFramePeriod->AddFrame(pNumberPeriod = new TGNumberEntry(pFramePeriod, 0, 6, EDT_PERIOD, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 0x7FFFFFFF), new TGLayoutHints(kLHintsRight));
				pNumberPeriod->SetWidth(100);

		AddFrame(pFrameDuty = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));
			pFrameDuty->AddFrame(pLabelDuty = new TGLabel(pFrameDuty, new TGString("Duty Cycle: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			pFrameDuty->AddFrame(pNumberDuty = new TGNumberEntry(pFrameDuty, 0, 6, EDT_DUTYCYCLE, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 0x7FFFFFFF), new TGLayoutHints(kLHintsRight));
				pNumberDuty->SetWidth(100);

		AddFrame(pFramePhase = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));
			pFramePhase->AddFrame(pLabelPhase = new TGLabel(pFramePhase, new TGString("Phase: ")), new TGLayoutHints(kLHintsLeft, 0, 0, 2, 0));
			pFramePhase->AddFrame(pNumberPhase = new TGNumberEntry(pFramePhase, 0, 6, EDT_PHASE, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 0x7FFFFFFF), new TGLayoutHints(kLHintsRight));
				pNumberPhase->SetWidth(100);

		pNumberPeriod->Associate(this);
		pNumberDuty->Associate(this);
		pNumberPhase->Associate(this);

		ReadSettings();
	}

	void ReadSettings()
	{
		unsigned int val;

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->Pulse_IO[iIndex].PeriodCycles, &val);
		pNumberPeriod->SetIntNumber(val);

		pVMEClient->ReadVME32((unsigned int)&pSSPregs->Pulse_IO[iIndex].HighCycles, &val);
		pNumberDuty->SetIntNumber(val);

		pNumberPhase->SetIntNumber(0);
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		switch(GET_MSG(msg))
		{
		case kC_TEXTENTRY:
			switch(GET_SUBMSG(msg))
			{
			case kTE_TEXTCHANGED:
				switch(parm1)
				{
					case EDT_PERIOD:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Pulse_IO[iIndex].PeriodCycles, pNumberPeriod->GetIntNumber());
						break;
					case EDT_DUTYCYCLE:
						pVMEClient->WriteVME32((unsigned int)&pSSPregs->Pulse_IO[iIndex].HighCycles, pNumberDuty->GetIntNumber());
						break;
					case EDT_PHASE:
						//pVMEClient->WriteVME32((unsigned int)&pSSPregs->Pulse_IO[iIndex].PeriodCycles, pFramePeriod->GetIntNumber());
						break;
				}
			}
			break;
		}
		return kTRUE;
	}

	int iIndex;

	VMERemote			*pVMEClient;
	SSP_regs			*pSSPregs;

	TGHorizontalFrame	*pFramePeriod;
	TGHorizontalFrame	*pFrameDuty;
	TGHorizontalFrame	*pFramePhase;

	TGLabel				*pLabelPeriod;
	TGLabel				*pLabelDuty;
	TGLabel				*pLabelPhase;

	TGNumberEntry		*pNumberPeriod;
	TGNumberEntry		*pNumberDuty;
	TGNumberEntry		*pNumberPhase;
};

#endif
