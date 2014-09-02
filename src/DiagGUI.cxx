#include <stdio.h>
#include "TClass.h"
#include "THashList.h"
#include "TImage.h"
#include "DiagGUI.h"
#include "CTPModule.h"
#include "DCRBModule.h"
#include "DCRBScalersModule.h"
#include "DSC2Module.h"
#include "FADC250Module.h"
#include "SDModule.h"
#include "SSPModule.h"
#include "SSP_HPSModule.h"
#include "TIDModule.h"
#include "VSCMModule.h"
#include "GTPModule.h"
#include "GTP_HPSModule.h"
#include "V1495PulserModule.h"

#define TIMER_CAPTURE_POLLRATE	100

#define BTN_CAPTUREEVENT		100
#define BTN_NEXTEVENT			101
#define BTN_PREVIOUSEVENT		102
#define BTN_STOPCAPTURE			103
#define BTN_PRINTSCREEN			104

#define SHUTTER_MSG_ITEM		0x5000
#define SHUTTER_MSG_BUTTON		0x6000

#ifndef WIN32
	#define stricmp strcasecmp
#endif

DiagGUI::DiagGUI(const TGWindow *p, unsigned int w, unsigned int h, const char *configFile) 
  : TGMainFrame(p, w, h)
{
	SetCleanup(kDeepCleanup);
	SetLayoutManager(new TGHorizontalLayout(this));

	gStyle->SetPalette(1, NULL);
	gStyle->SetCanvasPreferGL(true);

	iEventBufferCount = EVENT_BUFFER_COUNT;

	iModuleCount = 0;
	for(int i = 0; i < MODULE_COUNT_MAX; i++)
		pModuleFrames[i] = NULL;

	iHostCount = 0;
	for(int i = 0; i < HOST_COUNT_MAX; i++)
		pCrateMsgClient[i] = NULL;

  AddFrame(pFrameRight = 
	   new TGVerticalFrame(this), 
	   new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY | kLHintsRight));
  pFrameRight->AddFrame(pFrameButtons = 
			new TGHorizontalFrame(pFrameRight), 
			new TGLayoutHints(kLHintsTop | kLHintsExpandX));
  pFrameButtons->AddFrame(pCaptureEvent = 
			  new TGTextButton(pFrameButtons, 
					   new TGHotString("Capture Event"), 
					   BTN_CAPTUREEVENT), 
			  new TGLayoutHints(kLHintsCenterX));
  pFrameButtons->AddFrame(pStopCaptureEvent = 
			  new TGTextButton(pFrameButtons, 
					   new TGHotString("Stop Capture"), 
					   BTN_STOPCAPTURE), 
			  new TGLayoutHints(kLHintsCenterX));
				pStopCaptureEvent->SetEnabled(kFALSE);
  pFrameButtons->AddFrame(pNextEvent = 
			  new TGTextButton(pFrameButtons, 
					   new TGHotString("Next Event"), 
					   BTN_NEXTEVENT), 
			  new TGLayoutHints(kLHintsCenterX));
  pFrameButtons->AddFrame(pPrevEvent = 
			  new TGTextButton(pFrameButtons, 
					   new TGHotString("Previous Event"), 
					   BTN_PREVIOUSEVENT), 
			  new TGLayoutHints(kLHintsCenterX));

  pFrameButtons->AddFrame(pPrintScreen = 
			  new TGTextButton(pFrameButtons, 
					   new TGHotString("Print Screen"), 
					   BTN_PRINTSCREEN), 
			  new TGLayoutHints(kLHintsCenterX));

  pFrameRight->AddFrame(pFrameModule = 
			new TGHorizontalFrame(pFrameRight), 
			new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY));
			//pFrameModule->SetEditDisabled(kEditDisable | kEditDisableLayout);

  AddFrame(pFrameLeft = 
	   new TGVerticalFrame(this, 150, 20, kFixedWidth), 
	   new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandY));
		pShutter = new TGShutter(pFrameLeft, kSunkenFrame);
		DiagLoadConfigFile(configFile);
		pFrameLeft->AddFrame(pShutter, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
		pFrameLeft->Resize(150,300);

	pCaptureEvent->Associate(this);
	pStopCaptureEvent->Associate(this);
	pNextEvent->Associate(this);
	pPrevEvent->Associate(this);
	pPrintScreen->Associate(this);

	pTimerCapture = new TTimer(this, TIMER_CAPTURE_POLLRATE, kTRUE);

	SetWindowName("DIAG GUI");

	MapSubwindows();
	Resize();
	ChangeFrame(0);
	Resize(w, h);
	MapWindow();

}

void
DiagGUI::PrintScreen()
{

  TClass* clGMainFrame = TClass::GetClass("TGMainFrame");
  TGWindow* win = 0;

  static TString dir("printouts");
  TGFileInfo fi;
  const char *myfiletypes[] = 
    { 
      "All files","*",
      "PNG files","*.png",
      "GIF files","*.gif",
      "JPG files","*.jpg",
      0,
      0 
    };
  fi.fFileTypes = myfiletypes;
  fi.fIniDir    = StrDup(dir.Data());

  new TGFileDialog(gClient->GetRoot(), 0, kFDSave, &fi);
  if(fi.fFilename!=NULL) 
    {
      TIter iWin(gClient->GetListOfWindows());
      while ((win = (TGWindow*)iWin())) {
	if(win->InheritsFrom(clGMainFrame))
	  {
	    TImage *img = TImage::Create();
	    img->FromWindow(win->GetId());
	    img->WriteImage(fi.fFilename);
	    break;
	  }
      }

    }
}

void 
DiagGUI::ChangeFrame(int index)
{
	static int prev_index=-1;

	if(prev_index==-1)
	{
		for(int i=0; i < iModuleCount; i++)
		{
			pModuleButton[i]->SetTextJustify(kTextLeft);
			pModuleFrames[i]->SetActive(kFALSE);
			pFrameModule->HideFrame(pModuleFrames[i]);
		}
	}
	else
	{
		pModuleButton[prev_index]->SetTextJustify(kTextLeft);
		pModuleFrames[prev_index]->SetActive(kFALSE);
		pFrameModule->HideFrame(pModuleFrames[prev_index]);
	}

	pModuleButton[index]->SetTextJustify(kTextCenterX);
	pModuleFrames[index]->SetActive(kTRUE);
	pFrameModule->ShowFrame(pModuleFrames[index]);

	prev_index=index;
}

void DiagGUI::DiagLoadConfigFile(const char *configFile)
{
	FILE *f = fopen(configFile, "rt");
	if(!f)
	{
		printf("Error: DiagLoadConfigFile() failed to open %s\n", configFile);
		gApplication->Terminate();
		return;
	}

	char paramA[100], paramB[100], paramC[100], buf[200];
	int line = 0;
	while(!feof(f))
	{
		if(fgets(buf, sizeof(buf), f))
		{
			int len = strlen(buf);
			line++;
			for(int i = 0; i < len; i++)
			{
				if(isalpha(buf[i]))
					buf[i] = toupper(buf[i]);
				else if( (buf[i] == '#') || (buf[i] == '\r') || (buf[i] == '\n') )
				{
					buf[i] = 0;
					break;
				}
			}
			paramA[0] = 0;
			paramB[0] = 0;
			paramC[0] = 0;
			int count = sscanf(buf, "%100s%100s%100s", paramA, paramB, paramC);
			if(count && (count != EOF))
				ProcessParam(paramA, paramB, paramC, count);
			else if(count && (count != EOF))
				printf("Error processing line %d: %s\n", line, buf);
		}
	}
	fclose(f);
}

Bool_t DiagGUI::GetInt(char *str, int *pInt)
{
	int result = sscanf(str, "0X%X", pInt);
	if( (result == EOF) || !result)
	{
		result = sscanf(str, "%u", pInt);
		if(!result)
			return kFALSE;
	}
	return kTRUE;
}

void DiagGUI::ProcessParam(char *paramA, char *paramB, char *paramC, int count)
{
	static TGShutterItem *item;
	static TGCompositeFrame *container;
//   static TGTextButton *button;
	static CrateMsgClient *pCrateMsgClientLast = NULL;
	static ModuleFrame *pModuleFrameLast = NULL;
	unsigned int addr = 0;

	if(!stricmp("HOSTNAME", paramA))
	{
		if(iHostCount < HOST_COUNT_MAX)
		{
			item = new TGShutterItem(pShutter, new TGHotString(paramB), SHUTTER_MSG_ITEM + iHostCount);
			container = (TGCompositeFrame *)item->GetContainer();

			int port = CRATEMSG_LISTEN_PORT;
			if(count == 3)
				GetInt(paramC, &port);

			pCrateMsgClient[iHostCount] = new CrateMsgClient(paramB, port);
			
			if(!pCrateMsgClient[iHostCount]->IsValid())
			{
//	      printf("%s: INVALID!\n",__FUNCTION__);
//	      delete pVMERemote[iHostCount];
//		  getch();
//	      gApplication->Terminate();
			}
			pCrateMsgClientLast = pCrateMsgClient[iHostCount];
			iHostCount++;
		}
		else
		{
			printf("Error: Maximum host count exceeded.\n");
			return;
		}
	}
	else if(!stricmp("EVENT_BUFFER_COUNT", paramA))
	{
		if(!GetInt(paramB, &iEventBufferCount))
		{
			printf("Error: [EVENT_BUFFER_COUNT] Invalid parameter %s\n", paramB);
			return;
		}
		else if( (iEventBufferCount < 1) || (iEventBufferCount > 1000) )
		{
			printf("Error: [EVENT_BUFFER_COUNT] Invalid parameter val specified %d\n", iEventBufferCount);
			iEventBufferCount = EVENT_BUFFER_COUNT;
			return;
		}
	}
	else if(!stricmp("MODULE", paramA))
	{
		if(!pCrateMsgClientLast)
		{
			printf("Error: No host defined for module: %s.\n", paramA);
			return;
		}
		if(iModuleCount < MODULE_COUNT_MAX)
		{
			if((count >= 3) && !GetInt(paramC, (int *)&addr))
			{
				printf("Error: expected base address for module %s, read %s.\n", paramB, paramC);
				return;
			}

			if(!stricmp("MOD_TYPE_SSP", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new SSPModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_SSP_HPS", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new SSP_HPSModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_TID", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new TIDModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_FADC250", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new FADC250Module(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_DCRB", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new DCRBModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_DCRBSCALERS", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new DCRBScalersModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_DSC2", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new DSC2Module(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_VSCM", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new VSCMModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_SD", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new SDModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_CTP", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new CTPModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_GTP", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new GTPModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_GTP_HPS", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new GTP_HPSModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else if(!stricmp("MOD_TYPE_V1495_PULSER", paramB))
				pFrameModule->AddFrame(pModuleFrames[iModuleCount] = new V1495PulserModule(pFrameModule, pCrateMsgClientLast, addr), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			else
			{
				printf("Error: Unknown module type: %s\n", paramB);
				return;
			}
			TString str;
			str.Form("%s: %s", pModuleFrames[iModuleCount]->GetSlotIdentifier(), pModuleFrames[iModuleCount]->GetModuleName());

			pModuleButton[iModuleCount] = new TGTextButton(container, str, SHUTTER_MSG_BUTTON + iModuleCount);
			container->AddFrame(pModuleButton[iModuleCount], new TGLayoutHints(kLHintsTop | kLHintsCenterX | kLHintsExpandX, 20, 20, 5, 0));
			pModuleButton[iModuleCount]->SetToolTipText(pModuleFrames[iModuleCount]->GetModuleFullName());
			pModuleButton[iModuleCount]->Associate(this);				

			pModuleButton[iModuleCount]->SetTextJustify(kTextLeft);
			pModuleFrames[iModuleCount]->SetActive(kFALSE);
			pFrameModule->HideFrame(pModuleFrames[iModuleCount]);

			pModuleFrameLast = pModuleFrames[iModuleCount];
			iModuleCount++;
		}
		else
			printf("Error: Maximum module count exceeded.\n");
	}
	else if(!stricmp("ENDHOST", paramA))
		pShutter->AddItem(item);
	else if(!stricmp("AUTO_CONFIG_MODULES", paramA))
	{
		printf("Error: AUTO_CONFIG_MODULES not supported.\n");
	}
	else
	{
		if(pModuleFrameLast && pModuleFrameLast->SetParameter(paramA, paramB))
		{
		}
		else
			printf("Unknown parameter: %s\n", paramA);
	}
}

Bool_t DiagGUI::ProcessMessage(Long_t msg, Long_t parm1, Long_t)
{
	switch(GET_MSG(msg))
	{
		case kC_COMMAND:
			switch(GET_SUBMSG(msg))
			{
				case kCM_BUTTON:
					if( (parm1 >= SHUTTER_MSG_BUTTON) && (parm1 < SHUTTER_MSG_BUTTON + MODULE_COUNT_MAX) )
						ChangeFrame(parm1 - SHUTTER_MSG_BUTTON);
					else
					{
						switch(parm1)
						{
							case BTN_PRINTSCREEN:
							{
								PrintScreen();
// 		    TImage *img = TImage::Create();
// 		    img->FromWindow(this);
// 		    img->WriteImage("out.png");
								break;
							}
							default:
								printf("button id %d pressed\n", (int)parm1);
								break;
						}
					}
					break;
			}
			break;
	}
	return kTRUE;
}

void DiagGUI::HandleDisconnect()
{
	for(int i = 0; i < iHostCount; i++)
	{
		if(pCrateMsgClient[i] && pCrateMsgClient[i]->IsValid())
		{
			pCrateMsgClient[i]->Close();
			printf("Disconnected from host: %s\n", pCrateMsgClient[i]->GetUrl());
		}
	}
}

void DiagGUI::CloseWindow()
{
	HandleDisconnect();
	gApplication->Terminate();
}
