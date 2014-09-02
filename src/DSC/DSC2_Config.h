#ifndef DSC2_Config_H
#define DSC2_Config_H

#define N_CHANNELS		16

#define DAC_MIN_THRESHOLD		0
#define DAC_MAX_THRESHOLD		1023

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "dsc2.h"

class DSC2_Config	: public TGCompositeFrame
{
public:
	DSC2_Config(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		TGCompositeFrame *tF1, *tF2, *tF3;

		SetLayoutManager(new TGVerticalLayout(this));
		pM = pModule;
		pRegs = (DSC2_regs *)pM->BaseAddr;
		
		AddFrame(tF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF1->AddFrame(pButtonLoadSettings = new TGTextButton(tF1, new TGHotString("LoadSettings"), BTN_LOAD_SETTINGS), new TGLayoutHints(kLHintsCenterX));
				pButtonLoadSettings->Associate(this);
			tF1->AddFrame(pButtonSaveSettings = new TGTextButton(tF1, new TGHotString("SaveSettings"), BTN_SAVE_SETTINGS), new TGLayoutHints(kLHintsCenterX));
				pButtonSaveSettings->Associate(this);
			tF1->AddFrame(pButtonForceRead = new TGTextButton(tF1, new TGHotString("ForceRegisterRead"), BTN_FORCE_READ), new TGLayoutHints(kLHintsCenterX));
				pButtonForceRead->Associate(this);
			tF1->AddFrame(pButtonSWTestPulse = new TGTextButton(tF1, new TGHotString("SWTestPulse"), BTN_TEST_PULSE), new TGLayoutHints(kLHintsCenterX));
				pButtonSWTestPulse->AllowStayDown(kTRUE);
				pButtonSWTestPulse->Associate(this);

		AddFrame(tF3 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			tF3->AddFrame(tF1 = new TGGroupFrame(tF3, "Discriminator Channels", kHorizontalFrame));
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
					tF2->AddFrame(new TGLabel(tF2, new TGString("Channel")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
					for(int i = 0; i < 16; i++)
					{
						char buf[20];
						sprintf(buf, "    %d", i+1);
						tF2->AddFrame(new TGLabel(tF2, new TGString(buf)), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 3, 3));
					}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TDC Thr")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pNumEntryTDCThr[i] = new TGNumberEntry(tF2, 0, 4, NUM_TDCTHR0+i, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, DAC_MIN_THRESHOLD, DAC_MAX_THRESHOLD), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
								pNumEntryTDCThr[i]->SetWidth(60);
								pNumEntryTDCThr[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TDCEn")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pCheckTDCEn[i] = new TGCheckButton(tF2, new TGHotString(""), CHK_TDCEN), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 2, 3));
								pCheckTDCEn[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TDCOREn")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pCheckTDCOREn[i] = new TGCheckButton(tF2, new TGHotString(""), CHK_TDCOREN), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 2, 3));
								pCheckTDCOREn[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TRG Thr")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pNumEntryTRGThr[i] = new TGNumberEntry(tF2, 0, 4, NUM_TRGTHR0+i, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, DAC_MIN_THRESHOLD, DAC_MAX_THRESHOLD), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
								pNumEntryTRGThr[i]->SetWidth(60);
								pNumEntryTRGThr[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TRGEn")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pCheckTRGEn[i] = new TGCheckButton(tF2, new TGHotString(""), CHK_TRGEN), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 2, 3));
								pCheckTRGEn[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TRGOREn")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pCheckTRGOREn[i] = new TGCheckButton(tF2, new TGHotString(""), CHK_TRGOREN), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 2, 3));
								pCheckTRGOREn[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TRGDly")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pNumEntryTRGDly[i] = new TGNumberEntry(tF2, 0, 4, NUM_TRGDELAY0+i, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
								pNumEntryTRGDly[i]->SetWidth(60);
								pNumEntryTRGDly[i]->Associate(this);
						}
				tF1->AddFrame(tF2 = new TGVerticalFrame(tF1), new TGLayoutHints(kLHintsNormal, 2, 2));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TRGWidth")), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
						for(int i = 0; i < 16; i++)
						{
							tF2->AddFrame(pNumEntryTRGWidth[i] = new TGNumberEntry(tF2, 0, 4, NUM_TRGWIDTH0+i, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 255), new TGLayoutHints(kLHintsCenterX | kLHintsCenterY));
								pNumEntryTRGWidth[i]->SetWidth(60);
								pNumEntryTRGWidth[i]->Associate(this);
						}
			tF3->AddFrame(tF1 = new TGVerticalFrame(tF3), new TGLayoutHints(kLHintsExpandX, 10, 5, 10, 5));
				tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
					tF2->AddFrame(new TGLabel(tF2, new TGString("Scaler Delay Grp1(4ns ticks):")));
					tF2->AddFrame(pNumEntryScalerDelayGrp1 = new TGNumberEntry(tF2, 0, 4, NUM_SCALERDELAY_GRP1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 127), new TGLayoutHints(kLHintsRight | kLHintsCenterY));
						pNumEntryScalerDelayGrp1->Associate(this);
				tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
					tF2->AddFrame(new TGLabel(tF2, new TGString("Scaler Delay Grp2(4ns ticks):")));
					tF2->AddFrame(pNumEntryScalerDelayGrp2 = new TGNumberEntry(tF2, 0, 4, NUM_SCALERDELAY_GRP2, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 127), new TGLayoutHints(kLHintsRight | kLHintsCenterY));
						pNumEntryScalerDelayGrp2->Associate(this);
				tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TDC Pulser Width(1ns ticks):")));
					tF2->AddFrame(pNumEntryTDCPulserWidth = new TGNumberEntry(tF2, 0, 4, NUM_TDCPULSERWIDTH, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 63), new TGLayoutHints(kLHintsRight | kLHintsCenterY));
						pNumEntryTDCPulserWidth->Associate(this);
				tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
					tF2->AddFrame(new TGLabel(tF2, new TGString("TRG Pulser Width(1ns ticks):")));
					tF2->AddFrame(pNumEntryTRGPulserWidth = new TGNumberEntry(tF2, 0, 4, NUM_TRGPULSERWIDTH, TGNumberFormat::kNESInteger, TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 63), new TGLayoutHints(kLHintsRight | kLHintsCenterY));
						pNumEntryTRGPulserWidth->Associate(this);
				tF1->AddFrame(tF2 = new TGHorizontalFrame(tF1), new TGLayoutHints(kLHintsExpandX));
					tF2->AddFrame(new TGLabel(tF2, new TGString("Test Input Pulse Enable:")));
					tF2->AddFrame(pCheckTestEn = new TGCheckButton(tF2, new TGHotString(""), CHK_TESTEN), new TGLayoutHints(kLHintsRight | kLHintsCenterY, 0, 0, 2, 3));
						pCheckTestEn->Associate(this);

		ForceRegisterRead();
	}

private:

	void LoadRegisterSettings()
	{
		TGFileInfo FileInfo;
		const char *filetypes[] = { "Config Files",    "*.dat",
		                            "All files",     "*",

									0,               0 };

		FileInfo.fFileTypes = filetypes;
		FileInfo.fIniDir = StrDup(".");

		new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &FileInfo);
		if(FileInfo.fFilename)
		{
			FILE *f = fopen(FileInfo.fFilename, "rt");
			if(f)
			{
				while(!feof(f))
				{
					char buf[200], token[50], val[50];
					unsigned int value;
					fgets(buf, sizeof(buf), f);
					if(sscanf(buf, "%49s%49s", token, val) == 2)
					{
						if(token[0] == '#')
							continue;

						if(!stricmp("0x", val))
							value = strtol(val, NULL, 16);
						else
							value = strtol(val, NULL, 10);

						if(!stricmp("CH1_TDC_THR", token))					pM->RMWReg32(&pRegs->threshold[0], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH2_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[1], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH3_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[2], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH4_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[3], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH5_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[4], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH6_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[5], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH7_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[6], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH8_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[7], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH9_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[8], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH10_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[9], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH11_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[10], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH12_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[11], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH13_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[12], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH14_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[13], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH15_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[14], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH16_TDC_THR", token))			pM->RMWReg32(&pRegs->threshold[15], value, DSC_THRESHOLD_TDC_MASK);
						else if(!stricmp("CH1_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[0], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH2_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[1], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH3_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[2], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH4_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[3], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH5_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[4], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH6_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[5], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH7_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[6], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH8_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[7], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH9_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[8], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH10_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[9], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH11_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[10], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH12_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[11], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH13_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[12], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH14_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[13], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH15_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[14], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("CH16_TRG_THR", token))			pM->RMWReg32(&pRegs->threshold[15], value<<16, DSC_THRESHOLD_TRG_MASK);
						else if(!stricmp("TDC_PULSEWIDTH", token))		pM->RMWReg32(&pRegs->pulsewidth, value, DSC_PULSEWIDTH_TDC_MASK);
						else if(!stricmp("TRG_PULSEWIDTH", token))		pM->RMWReg32(&pRegs->pulsewidth, value<<16, DSC_PULSEWIDTH_TRG_MASK);
						else if(!stricmp("TRGOUT_PULSEWIDTH", token))	pM->RMWReg32(&pRegs->pulsewidth, value<<28, DSC_PULSEWIDTH_TRG_OUTPUT_MASK);
						else if(!stricmp("TDC_ENABLEMASK", token))		pM->RMWReg32(&pRegs->chEnable, value, DSC_CHENABLE_TDC_MASK);
						else if(!stricmp("TRG_ENABLEMASK", token))		pM->RMWReg32(&pRegs->chEnable, value<<16, DSC_CHENABLE_TRG_MASK);
						else if(!stricmp("TDC_ENABLEORMASK", token))		pM->RMWReg32(&pRegs->orMask, value, DSC_ORMASK_TDC_MASK);
						else if(!stricmp("TRG_ENABLEORMASK", token))		pM->RMWReg32(&pRegs->orMask, value<<16, DSC_ORMASK_TRG_MASK);
						else if(!stricmp("SCALER_DELAY", token))			pM->RMWReg32(&pRegs->delay, value, DSC_DELAY_SCALER_MASK);
						else if(!stricmp("TRIGOUT_DELAY", token))			pM->RMWReg32(&pRegs->delay, value<<16, DSC_DELAY_TRG_MASK);
						else if(!stricmp("TEST_INPUT", token))				pM->RMWReg32(&pRegs->delay, value, 0x1);
						else printf("Unknown Key/Value pair: %s %d\n", token, value);
					}
				}
				fclose(f);
				ForceRegisterRead();
			}
			else
				printf("Error opening file: %s\n", FileInfo.fFilename);
		}
	}

	void SaveRegisterSettings()
	{
		int i;
		TGFileInfo FileInfo;
		const char *filetypes[] = { "Config Files",    "*.dat",
		                            "All files",     "*",
									0,               0 };

		FileInfo.fFileTypes = filetypes;
		FileInfo.fIniDir = StrDup(".");

		new TGFileDialog(gClient->GetRoot(), this, kFDSave, &FileInfo);
		if(FileInfo.fFilename)
		{
			FILE *f = fopen(FileInfo.fFilename, "wt");
			if(f)
			{
				fprintf(f, "# JLab Dual Threshold Discriminator Register Settings\n");
				fprintf(f, "# Last Updated: %s at %s\n", __DATE__, __TIME__);

				fprintf(f, "\n# TDC Output Thresholds (in -mV units)\n");
				for(i = 0; i < 16; i++)
					fprintf(f, "CH%d_TDC_THR		%d\n", i+1, (pM->ReadReg32(&pRegs->threshold[i]) & DSC_THRESHOLD_TDC_MASK));

				fprintf(f, "\n# Trigger Output Thresholds (in -mV units)\n");
				for(i = 0; i < 16; i++)
					fprintf(f, "CH%d_TRG_THR		%d\n", i+1, ((pM->ReadReg32(&pRegs->threshold[i]) & DSC_THRESHOLD_TRG_MASK)>>16));

				fprintf(f, "\n# TDC Output Pulse Width\n");
				fprintf(f, "TDC_PULSEWIDTH		%d\n", pM->ReadReg32(&pRegs->pulsewidth) & DSC_PULSEWIDTH_TDC_MASK);
				fprintf(f, "\n# Trigger Output Pulse Width\n");
				fprintf(f, "TRG_PULSEWIDTH		%d\n", (pM->ReadReg32(&pRegs->pulsewidth) & DSC_PULSEWIDTH_TRG_MASK)>>16);
				fprintf(f, "TRGOUT_PULSEWIDTH	%d\n", (pM->ReadReg32(&pRegs->pulsewidth) & DSC_PULSEWIDTH_TRG_OUTPUT_MASK)>>28);
				fprintf(f, "\n# Discriminator Channel Enable Mask. Enables/Disables both Trigger and TDC outputs\n");
				fprintf(f, "TDC_ENABLEMASK		0x%04X\n", pM->ReadReg32(&pRegs->chEnable) & DSC_CHENABLE_TDC_MASK);
				fprintf(f, "\n# Discriminator Channel Enable Mask. Enables/Disables Trigger output.\n");
				fprintf(f, "TRG_ENABLEMASK		0x%04X\n", (pM->ReadReg32(&pRegs->chEnable) & DSC_CHENABLE_TRG_MASK)>>16);
				fprintf(f, "\n# TDC Channel OR Enable Mask\n");
				fprintf(f, "TDC_ENABLEORMASK	0x%04X\n", pM->ReadReg32(&pRegs->orMask) & DSC_ORMASK_TDC_MASK);
				fprintf(f, "\n# Trigger Channel OR Enable Mask\n");
				fprintf(f, "TRG_ENABLEORMASK	0x%04X\n", (pM->ReadReg32(&pRegs->orMask) & DSC_ORMASK_TRG_MASK)>>16);
				fprintf(f, "\n# Trigger/TDC Input Delay used with External gate for scalers\n");
				fprintf(f, "SCALER_DELAY		%d\n", pM->ReadReg32(&pRegs->delay) & DSC_DELAY_SCALER_MASK);
				fprintf(f, "\n# Trigger output delay (in 4ns ticks)\n");
				fprintf(f, "TRIGOUT_DELAY		%d\n", (pM->ReadReg32(&pRegs->delay) & DSC_DELAY_TRG_MASK)>>16);
				fprintf(f, "\n# Test input enabled\n");
				fprintf(f, "TEST_INPUT			%d\n", pM->ReadReg32(&pRegs->testCtrl) & 0x1);

				fclose(f);
			}
		}
	}

	void SWTestPulse()
	{
		while(pButtonSWTestPulse->IsDown())
		{
			gSystem->ProcessEvents();
			gSystem->Sleep(1);
			// sw test pulse
			pM->WriteReg32(&pRegs->testCtrl, pM->ReadReg32(&pRegs->testCtrl) | 0x80000000);
		}
	}

	void ForceRegisterRead()
	{
		unsigned int val;
		int i;

		for(i = 0; i < 16; i++)
		{
			val = pM->ReadReg32(&pRegs->threshold[i]);
			pNumEntryTDCThr[i]->SetIntNumber(val&DSC_THRESHOLD_TDC_MASK);
			pNumEntryTRGThr[i]->SetIntNumber((val&DSC_THRESHOLD_TRG_MASK)>>16);

			val = pM->ReadReg32(&pRegs->trigOut[i]);
			pNumEntryTRGDly[i]->SetIntNumber((val & 0xFF)>>0);
			pNumEntryTRGWidth[i]->SetIntNumber((val & 0xFF00)>>8);
		}

		val = pM->ReadReg32(&pRegs->chEnable);
		for(i = 0; i < 16; i++)
		{
			if(val & (1<<i))
				pCheckTDCEn[i]->SetDown(kTRUE);
			else
				pCheckTDCEn[i]->SetDown(kFALSE);

			if(val & (1<<(i+16)))
				pCheckTRGEn[i]->SetDown(kTRUE);
			else
				pCheckTRGEn[i]->SetDown(kFALSE);
		}

		val = pM->ReadReg32(&pRegs->orMask);
		for(i = 0; i < 16; i++)
		{
			if(val & (1<<i))
				pCheckTDCOREn[i]->SetDown(kTRUE);
			else
				pCheckTDCOREn[i]->SetDown(kFALSE);

			if(val & (1<<(i+16)))
				pCheckTRGOREn[i]->SetDown(kTRUE);
			else
				pCheckTRGOREn[i]->SetDown(kFALSE);
		}

		val = pM->ReadReg32(&pRegs->testCtrl);
		if(val & 0x1)
			pCheckTestEn->SetDown(kTRUE);
		else
			pCheckTestEn->SetDown(kFALSE);

		val = pM->ReadReg32(&pRegs->delay);
		pNumEntryScalerDelayGrp1->SetIntNumber(val & DSC_DELAY_SCALER_MASK);
		pNumEntryScalerDelayGrp2->SetIntNumber((val & DSC_DELAY_TRG_MASK)>>16);

		val = pM->ReadReg32(&pRegs->pulsewidth);
		pNumEntryTDCPulserWidth->SetIntNumber((val & DSC_PULSEWIDTH_TDC_MASK)>>0);
		pNumEntryTRGPulserWidth->SetIntNumber((val & DSC_PULSEWIDTH_TRG_MASK)>>16);
	}

	Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
	{
		unsigned int val, ch;

		switch(GET_MSG(msg))
		{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
			case kCM_BUTTON:
				switch(parm1)
				{
				case BTN_LOAD_SETTINGS:
					LoadRegisterSettings();
					break;
				case BTN_SAVE_SETTINGS:
					SaveRegisterSettings();
					break;
				case BTN_FORCE_READ:
					ForceRegisterRead();
					break;
				case BTN_TEST_PULSE:
					SWTestPulse();
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
				}
				break;
			case kCM_CHECKBUTTON:
				switch(parm1)
				{
				case CHK_TDCEN:
				case CHK_TRGEN:
					val = 0;
					for(int i = 0; i < 16; i++)
					{
						if(pCheckTDCEn[i]->IsDown())
							val |= (1<<i);
						if(pCheckTRGEn[i]->IsDown())
							val |= (1<<(i+16));
					}
					pM->WriteReg32(&pRegs->chEnable, val);
					break;
				case CHK_TDCOREN:
				case CHK_TRGOREN:
					val = 0;
					for(int i = 0; i < 16; i++)
					{
						if(pCheckTDCOREn[i]->IsDown())
							val |= (1<<i);
						if(pCheckTRGOREn[i]->IsDown())
							val |= (1<<(i+16));
					}
					pM->WriteReg32(&pRegs->orMask, val);
					break;
				case CHK_TESTEN:
					if(pCheckTestEn->IsDown())
						pM->WriteReg32(&pRegs->testCtrl, 1);
					else
						pM->WriteReg32(&pRegs->testCtrl, 0);
					break;
				default:
					printf("check button id %d pressed\n", (int)parm1);
				}
				break;
			}
			break;
		case kC_TEXTENTRY:
			switch(GET_SUBMSG(msg))
			{
			case kTE_ENTER:
			case kTE_TAB:
			case kTE_TEXTCHANGED:
				if( (parm1 >= NUM_TDCTHR0) && (parm1 <= NUM_TRGTHR0+15) )
				{
					if(parm1 >= NUM_TRGTHR0)
						ch = parm1 - NUM_TRGTHR0;
					else
						ch = parm1 - NUM_TDCTHR0;
					pM->WriteReg32(&pRegs->threshold[ch], pNumEntryTDCThr[ch]->GetIntNumber() | (pNumEntryTRGThr[ch]->GetIntNumber()<<16));
				}
				else if( (parm1 >= NUM_TRGDELAY0) && (parm1 <= NUM_TRGDELAY0+15) )
				{
					ch = parm1 - NUM_TRGDELAY0;

					val = pM->ReadReg32(&pRegs->trigOut[ch]) & 0xFFFFFF00;
					val |= pNumEntryTRGDly[ch]->GetIntNumber();
					pM->WriteReg32(&pRegs->trigOut[ch], val);
				}
				else if( (parm1 >= NUM_TRGWIDTH0) && (parm1 <= NUM_TRGWIDTH0+15) )
				{
					ch = parm1 - NUM_TRGWIDTH0;

					val = pM->ReadReg32(&pRegs->trigOut[ch]) & 0xFFFF00FF;
					val |= pNumEntryTRGWidth[ch]->GetIntNumber() << 8;
					pM->WriteReg32(&pRegs->trigOut[ch], val);
				}
				else
				{
					switch(parm1)
					{
					case NUM_SCALERDELAY_GRP1:
					case NUM_SCALERDELAY_GRP2:
						pM->WriteReg32(&pRegs->delay, pNumEntryScalerDelayGrp1->GetIntNumber() | (pNumEntryScalerDelayGrp2->GetIntNumber()<<16));
						break;
					case NUM_TRGPULSERWIDTH:
					case NUM_TDCPULSERWIDTH:
						pM->WriteReg32(&pRegs->pulsewidth, pNumEntryTDCPulserWidth->GetIntNumber() | (pNumEntryTRGPulserWidth->GetIntNumber()<<16));
						break;
					default:
						printf("text entry id %d pressed\n", (int)parm1);
					}
				}
				break;
			}
			break;
		}
		return kTRUE;
	}

	enum Buttons
	{
		NUM_TDCTHR0				= 400,
		NUM_TRGTHR0				= 416,
		NUM_TRGDELAY0			= 432,
		NUM_TRGWIDTH0			= 448,
		NUM_SCALERDELAY_GRP1	= 464,
		NUM_SCALERDELAY_GRP2 = 465,
		NUM_TDCPULSERWIDTH	= 466,
		NUM_TRGPULSERWIDTH	= 467,
		CHK_TDCEN				= 500,
		CHK_TRGEN				= 501,
		CHK_TDCOREN				= 502,
		CHK_TRGOREN				= 503,
		CHK_TESTEN				= 504,
		BTN_LOAD_SETTINGS		= 300,
		BTN_SAVE_SETTINGS		= 301,
		BTN_FORCE_READ			= 302,
		BTN_TEST_PULSE			= 303
	};

	ModuleFrame				*pM;
	DSC2_regs				*pRegs;

	TGNumberEntry			*pNumEntryTDCThr[16];
	TGNumberEntry			*pNumEntryTRGThr[16];
	TGNumberEntry			*pNumEntryTRGDly[16];
	TGNumberEntry			*pNumEntryTRGWidth[16];
	TGNumberEntry			*pNumEntryScalerDelayGrp1;
	TGNumberEntry			*pNumEntryScalerDelayGrp2;
	TGNumberEntry			*pNumEntryTDCPulserWidth;
	TGNumberEntry			*pNumEntryTRGPulserWidth;

	TGCheckButton			*pCheckTDCEn[16];
	TGCheckButton			*pCheckTDCOREn[16];
	TGCheckButton			*pCheckTRGEn[16];
	TGCheckButton			*pCheckTRGOREn[16];
	TGCheckButton			*pCheckTestEn;

	TGTextButton			*pButtonLoadSettings;
	TGTextButton			*pButtonSaveSettings;
	TGTextButton			*pButtonForceRead;
	TGTextButton			*pButtonSWTestPulse;
};

#endif
