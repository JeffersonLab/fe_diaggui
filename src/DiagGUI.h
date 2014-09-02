#ifndef DiagGUI_H
#define DiagGUI_H

#include "RootHeader.h"
#include "ModuleFrame.h"

#define HOST_COUNT_MAX		20
#define MODULE_COUNT_MAX	100

#define EVENT_BUFFER_COUNT	25

#define MODULEID_SSP    0x00838380
#define MODULEID_SD     0x00008386
#define MODULEID_CTP    0x00678480
#define MODULEID_FADC   0x46414443
#define MODULEID_TID    0x00544944
#define MODULEID_FASDC  0x46415344

class DiagGUI : public TGMainFrame
{
private:
	void HandleDisconnect();
	void DiagLoadConfigFile(const char *configFile);
	void ProcessParam(char *paramA, char *paramB, char *paramC, int count);
	void PrintScreen();
	void ChangeFrame(int index);
	void ProcessEventData(int host, int evtNum, int evtLen, unsigned int *pData);
	Bool_t GetInt(char *str, int *pInt);

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);
	virtual void CloseWindow();

	CrateMsgClient	*pCrateMsgClient[HOST_COUNT_MAX];
	ModuleFrame		*pModuleFrames[MODULE_COUNT_MAX];
	TGTextButton	*pModuleButton[MODULE_COUNT_MAX];
	Bool_t			bEventCaptured[HOST_COUNT_MAX];

	int				iHostCount;
	int				iModuleCount;
	int				iEventBufferCount;

	TTimer				*pTimerCapture;

	TGShutter			*pShutter;

	TGTextButton		*pCaptureEvent;
	TGTextButton		*pStopCaptureEvent;
	TGTextButton		*pNextEvent;
	TGTextButton		*pPrevEvent;

	TGTextButton          *pPrintScreen;

	TGVerticalFrame		*pFrameLeft;
	TGVerticalFrame		*pFrameRight;
	TGHorizontalFrame	*pFrameButtons;
	TGHorizontalFrame	*pFrameModule;

public:
	DiagGUI(const TGWindow *p, unsigned int w, unsigned int h, const char *host);
};

#endif
