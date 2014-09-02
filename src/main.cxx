#ifdef WIN32
	#include <w32pragma.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TServerSocket.h>
#include <TSystem.h>
#include "DiagGUI.h"

int main(int argc, char* argv[])
{
	int cargc = 1;
	TApplication App("Diagnostic GUI", &cargc, argv);

	if(gROOT->IsBatch())
	{
		fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
		return 1;
	}

	if(argc != 2)
	{
		fprintf(stderr, "Error - usage: DiagGUI <ROCConfig.txt>\n");
		return 2;
	}

	DiagGUI *pDiagGUI = new DiagGUI(gClient->GetRoot(), 800, 600, argv[1]);
	App.Run();

	delete pDiagGUI;
	return 0;
}
