#ifndef REGEDITOR_H
#define REGEDITOR_H

#include "RootHeader.h"

#define REGMEMDESC_MAP_MAXLEN		64

#define REGMEM_DESC_FLAGS_INT		0x00001
#define REGMEM_DESC_FLAGS_UINT	0x00002
#define REGMEM_DESC_FLAGS_HEX		0x00004
#define REGMEM_DESC_FLAGS_STRING	0x00008
#define REGMEM_DESC_FLAGS_LIMITS	0x10000

typedef struct
{
	const char *name;
	int mode;

	struct
	{
		int addr;
		int shift;
		int nbits;
		int access_width;
	} info;

	struct
	{
		int cnt;
		const char *name[REGMEMDESC_MAP_MAXLEN];
		int val[REGMEMDESC_MAP_MAXLEN];
	} map;

	struct
	{
		double min;
		double max;
	} limits;
} RegMemDesc;

class RegEditorDialog	: public TGTransientFrame
{
public:
	RegEditorDialog(const TGWindow *p) : TGTransientFrame(p, NULL, 200, 150, kVerticalFrame | kFixedSize)
	{
		DontCallClose(); // to avoid double deletions.
		SetCleanup(kDeepCleanup);
	}

	Bool_t Run(RegMemDesc *pRegMemDesc)
	{
		quit = kFALSE;

		TGCompositeFrame *pF1;

		AddFrame(pTextViewInfo = new TGTextView(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pTextViewInfo->SetText(new TGText(Form("Name: %s", pRegMemDesc->name)));
			pTextViewInfo->AddLineFast(Form("Addr: 0x%08X", pRegMemDesc->info.addr));
			pTextViewInfo->AddLineFast(Form("NumBits: %d", pRegMemDesc->info.nbits));
			pTextViewInfo->AddLineFast(Form("Shift: %d", pRegMemDesc->info.shift));
			pTextViewInfo->AddLineFast(Form("AccessWidth: %d", pRegMemDesc->info.access_width));
			pTextViewInfo->AddLineFast(Form("Min: %lf", pRegMemDesc->limits.min));
			pTextViewInfo->AddLineFast(Form("Max: %lf", pRegMemDesc->limits.max));
			pTextViewInfo->Update();

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pF1->AddFrame(new TGLabel(pF1, "Write Value: "), new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
			if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_STRING)
			{
				pF1->AddFrame(pComboValue = new TGComboBox(pF1), new TGLayoutHints(kLHintsExpandX));
					for(int i = 0; i < pRegMemDesc->map.cnt; i++)
						pComboValue->AddEntry(pRegMemDesc->map.name[i], pRegMemDesc->map.val[i]);
					pComboValue->Select(pRegMemDesc->map.val[0], kFALSE);
					pComboValue->SetHeight(20);
			}
			else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_INT)
			{
				pF1->AddFrame(pNumEditValue = new TGNumberEntry(pF1, 0, 8, -1,
						TGNumberFormat::kNESInteger,
						TGNumberFormat::kNEAAnyNumber,
						TGNumberFormat::kNELLimitMinMax,
						pRegMemDesc->limits.min, pRegMemDesc->limits.max), new TGLayoutHints(kLHintsExpandX));
			}
			else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_UINT)
			{
				pF1->AddFrame(pNumEditValue = new TGNumberEntry(pF1, 0, 8, -1,
						TGNumberFormat::kNESInteger,
						TGNumberFormat::kNEAAnyNumber,
						TGNumberFormat::kNELLimitMinMax,
						pRegMemDesc->limits.min, pRegMemDesc->limits.max), new TGLayoutHints(kLHintsExpandX));
			}
			else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_HEX)
			{
				pF1->AddFrame(pNumEditValue = new TGNumberEntry(pF1, 0, 8, -1,
						TGNumberFormat::kNESHex,
						TGNumberFormat::kNEAAnyNumber,
						TGNumberFormat::kNELLimitMinMax,
						pRegMemDesc->limits.min, pRegMemDesc->limits.max), new TGLayoutHints(kLHintsExpandX));
			}
		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX,20,20,5,5));
			pF1->AddFrame(pButtonOk = new TGTextButton(pF1, new TGHotString("Ok"), BTN_OK), new TGLayoutHints(kLHintsCenterX));
				pButtonOk->SetWidth(75);
				pButtonOk->Associate(this);
			pF1->AddFrame(pButtonCancel = new TGTextButton(pF1, new TGHotString("Cancel"), BTN_CANCEL), new TGLayoutHints(kLHintsCenterX));
				pButtonCancel->SetWidth(75);
				pButtonCancel->Associate(this);

		MapSubwindows();
		Resize();
		CenterOnParent();
		SetWindowName(Form("Register edit: %s", pRegMemDesc->name));
		MapWindow();

		while(!quit)
			gSystem->ProcessEvents();

		if(writeParam)
		{
			if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_STRING)
				val = pComboValue->GetSelected();
			else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_INT)
				val = (int)pNumEditValue->GetIntNumber();
			else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_UINT)
				val = (int)pNumEditValue->GetIntNumber();
			else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_HEX)
				val = (int)pNumEditValue->GetIntNumber();

			return kTRUE;
		}

		//DeleteWindow();  // deletes fMain

		return kFALSE;
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			switch(parm1)
			{
				case BTN_OK:
					writeParam = kTRUE;
					quit = kTRUE;
					break;
				case BTN_CANCEL:
					writeParam = kFALSE;
					quit = kTRUE;
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
			}
		}
//		else
//			printf("msg=%d, submsg=%d, p1=%ld, p2=%ld\n", GET_MSG(msg), GET_SUBMSG(msg), parm1, parm2);

		return kTRUE;
	}

	int					val;

private:
	enum
	{
		BTN_OK,
		BTN_CANCEL
	};

	Bool_t				quit;
	Bool_t				writeParam;
	TGTextView			*pTextViewInfo;
	TGComboBox			*pComboValue;
	TGNumberEntry		*pNumEditValue;
	TGTextButton		*pToggleValue;
	TGTextButton		*pButtonOk;
	TGTextButton		*pButtonCancel;
};

class RegEditor : public TGVerticalFrame
{
public:
	RegEditor(TGWindow* p, CrateMsgClient *pClient, unsigned int baseAddr, UInt_t w = 250, UInt_t h = 200) : TGVerticalFrame(p, w, h), pCrateMsgClient(pClient), BaseAddr(baseAddr)
	{
		picBinaryData = gClient->GetPicture("pics/binarydata.xpm");

		TGCompositeFrame *pF1;

		AddFrame(pF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
			pF1->AddFrame(pButtonUpdate = new TGTextButton(pF1, "Refresh", BTN_UPDATE), new TGLayoutHints(kLHintsCenterX | kLHintsTop | kLHintsExpandX));
//				pButtonUpdate->ChangeOptions(pButtonUpdate->GetOptions() | kFixedSize);
//				pButtonUpdate->SetWidth(w);
				pButtonUpdate->SetHeight(20);
				pButtonUpdate->Associate(this);
			pF1->AddFrame(pButtonLoad = new TGTextButton(pF1, "LoadFile", BTN_LOAD), new TGLayoutHints(kLHintsCenterX | kLHintsTop | kLHintsExpandX));
//				pButtonLoad->ChangeOptions(pButtonUpdate->GetOptions() | kFixedSize);
//				pButtonLoad->SetWidth(w);
				pButtonLoad->SetHeight(20);
				pButtonLoad->Associate(this);
			pF1->AddFrame(pButtonSave = new TGTextButton(pF1, "SaveFile", BTN_SAVE), new TGLayoutHints(kLHintsCenterX | kLHintsTop | kLHintsExpandX));
//				pButtonSave->ChangeOptions(pButtonUpdate->GetOptions() | kFixedSize);
//				pButtonSave->SetWidth(w);
				pButtonSave->SetHeight(20);
				pButtonSave->Associate(this);

		AddFrame(pCanvas = new TGCanvas(this, w, h), new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsExpandY | kLHintsTop));
			pListTree = new TGListTree(pCanvas->GetViewPort(), kHorizontalFrame);
			pCanvas->SetContainer(pListTree);
			pListTree->SetCanvas(pCanvas);
			pListTree->Associate(this);
	}

	TGListTreeItem *AddFolder(TGListTreeItem *parent, const char *name)
	{
		return pListTree->AddItem(parent, name);
	}

	void Add(TGListTreeItem *pParent, RegMemDesc *pRegMemDesc)
	{
		if(!(pRegMemDesc->mode & REGMEM_DESC_FLAGS_LIMITS))
		{
			pRegMemDesc->limits.min = 0;
			pRegMemDesc->limits.max = pow(2.0, pRegMemDesc->info.nbits) - 1.0;
		}
		pListTree->AddItem(pParent, Form("%-20s unknown", pRegMemDesc->name), pRegMemDesc, picBinaryData, picBinaryData);
	}

	void AddSet(RegMemDesc *pRegMemDesc, int cnt)
	{
		TGListTreeItem *pItem = NULL;

		for(int i = 0; i < cnt; i++)
		{
			if(!pRegMemDesc[i].mode)
			{
				if(pRegMemDesc[i].name)
					pItem = AddFolder(pItem, pRegMemDesc[i].name);
				else if(pItem)
					pItem = pItem->GetParent();
			}
			else
				Add(pItem, &pRegMemDesc[i]);
		}
	}

	char *BuildName(RegMemDesc *pRegMemDesc, int value)
	{
		if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_INT)
			return Form("%-20s %d", pRegMemDesc->name, value);
		else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_UINT)
			return Form("%-20s %u", pRegMemDesc->name, value);
		else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_HEX)
		{
			if(pRegMemDesc->info.nbits > 24)
				return Form("%-20s 0x%08X", pRegMemDesc->name, value);
			else if(pRegMemDesc->info.nbits > 16)
				return Form("%-20s 0x%06X", pRegMemDesc->name, value);
			else if(pRegMemDesc->info.nbits > 8)
				return Form("%-20s 0x%04X", pRegMemDesc->name, value);
			else
				return Form("%-20s 0x%02X", pRegMemDesc->name, value);
		}
		else if(pRegMemDesc->mode & REGMEM_DESC_FLAGS_STRING)
		{
			for(int i = 0; i < pRegMemDesc->map.cnt; i++)
			{
				if(pRegMemDesc->map.val[i] == value)
					return Form("%-20s %s", pRegMemDesc->name, pRegMemDesc->map.name[i]);
			}
			return Form("%-20s unknown(%d)", pRegMemDesc->name, value);
		}
		return Form("%-20s style unknown", pRegMemDesc->name);
	}

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			switch(parm1)
			{
				case BTN_LOAD:
					Load();
					break;
				case BTN_SAVE:
					Save();
					break;
				case BTN_UPDATE:
					Refresh(pListTree->GetFirstItem(), kTRUE);
					pListTree->ClearViewPort();
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_LISTTREE) && (GET_SUBMSG(msg) == kCT_ITEMDBLCLICK))
			Edit(pListTree->GetSelected());

		return kTRUE;
	}

	void Load()
	{

	}

	void Save()
	{
/*
		int i;
		TGFileInfo FileInfo;
		const char *filetypes[] = {
				"Config Files", "*.dat", "All files", "*", 0, 0
			};

		FileInfo.fFileTypes = filetypes;
		FileInfo.fIniDir = StrDup(".");

		new TGFileDialog(gClient->GetRoot(), this, kFDSave, &FileInfo);
		if(!FileInfo.fFilename)
			return;

		FILE *f = fopen(FileInfo.fFilename, "wt");
		if(!f)
			return;

		fprintf(f, )


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
*/
	}

	void Refresh(TGListTreeItem *pItem, Bool_t recursive = kFALSE)
	{
		RegMemDesc *pRegMemDesc = (RegMemDesc *)pItem->GetUserData();

		if(pRegMemDesc)
		{
			int val = Read(pRegMemDesc);
			pItem->SetText(BuildName(pRegMemDesc, val));
		}
		if(recursive)
		{
			if(pItem->GetFirstChild())
				Refresh(pItem->GetFirstChild(), kTRUE);
			else if(pItem->GetNextSibling())
				Refresh(pItem->GetNextSibling(), kTRUE);
			else
			{
				while(pItem->GetParent())
				{
					pItem = pItem->GetParent();
					if(pItem->GetNextSibling())
					{
						Refresh(pItem->GetNextSibling(), kTRUE);
						break;
					}
				}
			}
		}
	}

	int Read(RegMemDesc *pRegMemDesc)
	{
		int result = 0xFFFFFFFF;
		int mask = (1<<pRegMemDesc->info.nbits)-1;

		if(pRegMemDesc->info.nbits == 32)
			mask = 0xFFFFFFFF;

		if(pRegMemDesc->info.access_width == 32)
		{
			unsigned int val;
			pCrateMsgClient->Read32(pRegMemDesc->info.addr+BaseAddr, &val);
			result = (int)val;
		}
		else if(pRegMemDesc->info.access_width == 16)
		{
			unsigned short val;
			pCrateMsgClient->Read16(pRegMemDesc->info.addr+BaseAddr, &val);
			result = (int)val;
		}
		else
			printf("unsupported access width %d\n", pRegMemDesc->info.access_width);

		result >>= pRegMemDesc->info.shift;
		result &= mask;
		return result;
	}

	void Write(RegMemDesc *pRegMemDesc, int val)
	{
		int result = 0;
		int mask = (1<<pRegMemDesc->info.nbits)-1;

		if(pRegMemDesc->info.nbits == 32)
			mask = 0xFFFFFFFF;

		if(pRegMemDesc->info.access_width == 32)
		{
			unsigned int val32;
			pCrateMsgClient->Read32(pRegMemDesc->info.addr+BaseAddr, &val32);
			result = (int)val32;
		}
		else if(pRegMemDesc->info.access_width == 16)
		{
			unsigned short val16;
			pCrateMsgClient->Read16(pRegMemDesc->info.addr+BaseAddr, &val16);
			result = (int)val16;
		}
		else
			printf("unsupported access width %d\n", pRegMemDesc->info.access_width);

		result &= ~(mask<<pRegMemDesc->info.shift);
		result |= (val & mask)<<pRegMemDesc->info.shift;

		if(pRegMemDesc->info.access_width == 32)
		{
			unsigned int val32 = result;
			pCrateMsgClient->Write32(pRegMemDesc->info.addr+BaseAddr, &val32);
		}
		else if(pRegMemDesc->info.access_width == 16)
		{
			unsigned short val16 = result;
			pCrateMsgClient->Write16(pRegMemDesc->info.addr+BaseAddr, &val16);
		}
		else
			printf("unsupported access width %d\n", pRegMemDesc->info.access_width);
	}

	void Edit(TGListTreeItem *pItem)
	{
		RegMemDesc *pRegMemDesc = (RegMemDesc *)pItem->GetUserData();

		if(!pRegMemDesc)
			return;

		RegEditorDialog regEdit(gClient->GetRoot());
		if(regEdit.Run(pRegMemDesc) == kTRUE)
		{
			Write(pRegMemDesc, regEdit.val);
			Refresh(pItem);
			pListTree->ClearViewPort();
		}
	}

	enum
	{
		BTN_UPDATE	= 1,
		BTN_LOAD		= 2,
		BTN_SAVE		= 3
	};

	CrateMsgClient		*pCrateMsgClient;
	TGTextButton		*pButtonLoad;
	TGTextButton		*pButtonSave;
	TGTextButton		*pButtonUpdate;
	TGCanvas 			*pCanvas;
	TGListTree			*pListTree;
	const TGPicture	*picBinaryData;
	unsigned int		BaseAddr;
};

#endif
