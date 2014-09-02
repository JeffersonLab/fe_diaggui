#ifndef GTP_SS_SCALERS_H
#define GTP_SS_SCALERS_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "gtp.h"

#define TAG_CELL_POS_X		0.0
#define TAG_CELL_POS_Y		-10.0
#define TAG_CELL_WIDTH		0.5
#define TAG_CELL_HEIGHT		5.0
#define TAG_AXIS_OFFSET		0.2

#define PS_CELL_POS_X		40.0
#define PS_CELL_POS_Y		0.0
#define PS_CELL_WIDTH		5.0
#define PS_CELL_HEIGHT		1
#define PS_RL_OFFSET			1.0
#define PS_AXIS_OFFSET		0.2

#define ST_CELL_POS_X		55.0
#define ST_CELL_POS_Y		0.0
#define ST_CELL_WIDTH		0.75
#define ST_CELL_HEIGHT		4.0
#define ST_RADIUS				4.0

typedef struct
{
	double x[4];
	double y[4];
} DetRect;

DetRect TAG[64];
DetRect PS[16];
DetRect ST[30];
DetRect BCALHits[32];
DetRect BCAL[32];
DetRect TOFH[16];
DetRect TOFV[16];
DetRect FCAL[32];

class GTP_SS_Scalers	: public TGCompositeFrame
{
public:
	void BuildDetRects()
	{
		unsigned int i, j;
		
		memset(PS, 0, sizeof(PS));
		memset(ST, 0, sizeof(ST));
		memset(TAG, 0, sizeof(TAG));
		memset(BCALHits, 0, sizeof(BCALHits));
		memset(BCAL, 0, sizeof(BCAL));
		memset(TOFH, 0, sizeof(TOFH));
		memset(TOFV, 0, sizeof(TOFV));
		memset(FCAL, 0, sizeof(FCAL));

		// TAG
		for(i = 0; i < sizeof(TAG)/sizeof(TAG[0]); i++)
		{
			TAG[i].x[0] = TAG_CELL_POS_X+TAG_CELL_WIDTH*i;
			TAG[i].x[1] = TAG_CELL_POS_X+TAG_CELL_WIDTH*(i+1);
			TAG[i].x[2] = TAG_CELL_POS_X+TAG_CELL_WIDTH*(i+1);
			TAG[i].x[3] = TAG_CELL_POS_X+TAG_CELL_WIDTH*i;
			TAG[i].y[0] = TAG_CELL_POS_Y;
			TAG[i].y[1] = TAG_CELL_POS_Y;
			TAG[i].y[2] = TAG_CELL_POS_Y+TAG_CELL_HEIGHT;
			TAG[i].y[3] = TAG_CELL_POS_Y+TAG_CELL_HEIGHT;
		}
		
		// PS
		for(i = 0; i < sizeof(PS)/sizeof(PS[0]); i++)
		{
			PS[i].x[0] = PS_CELL_POS_X;
			PS[i].x[1] = PS_CELL_POS_X+PS_CELL_WIDTH;
			PS[i].x[2] = PS_CELL_POS_X+PS_CELL_WIDTH;
			PS[i].x[3] = PS_CELL_POS_X;
			
			if(i < 8)
			{
				PS[i].y[0] = PS_CELL_POS_Y+PS_CELL_HEIGHT*(i%8)+PS_RL_OFFSET;
				PS[i].y[1] = PS_CELL_POS_Y+PS_CELL_HEIGHT*(i%8)+PS_RL_OFFSET;
				PS[i].y[2] = PS_CELL_POS_Y+(PS_CELL_HEIGHT*(i%8)+1)+PS_RL_OFFSET;
				PS[i].y[3] = PS_CELL_POS_Y+(PS_CELL_HEIGHT*(i%8)+1)+PS_RL_OFFSET;
			}
			else
			{
				PS[i].y[0] = PS_CELL_POS_Y-PS_CELL_HEIGHT*(i%8)-PS_RL_OFFSET;
				PS[i].y[1] = PS_CELL_POS_Y-PS_CELL_HEIGHT*(i%8)-PS_RL_OFFSET;
				PS[i].y[2] = PS_CELL_POS_Y-(PS_CELL_HEIGHT*(i%8)+1)-PS_RL_OFFSET;
				PS[i].y[3] = PS_CELL_POS_Y-(PS_CELL_HEIGHT*(i%8)+1)-PS_RL_OFFSET;
			}
		}

		// ST
		for(i = 0; i < sizeof(ST)/sizeof(ST[0]); i++)
		{
			double angle = 2.0 * TMath::Pi() * i / (sizeof(ST)/sizeof(ST[0]));
			double x[4], y[4];
			
			x[0] = ST_RADIUS;
			y[0] = ST_CELL_WIDTH/2.0;

			x[1] = ST_RADIUS;
			y[1] = -ST_CELL_WIDTH/2.0;

			x[2] = ST_RADIUS+ST_CELL_HEIGHT;
			y[2] = -ST_CELL_WIDTH/2.0;

			x[3] = ST_RADIUS+ST_CELL_HEIGHT;
			y[3] = ST_CELL_WIDTH/2.0;
			
			for(j = 0; j < 4; j++)
			{
				ST[i].x[j] = ST_CELL_POS_X+x[j]*TMath::Cos(angle)-y[j]*TMath::Sin(angle);
				ST[i].y[j] = ST_CELL_POS_Y+y[j]*TMath::Cos(angle)+x[j]*TMath::Sin(angle);
			}
		}
	}
	
	GTP_SS_Scalers(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
	{
		unsigned int i;
		
		BuildDetRects();
		
		SetLayoutManager(new TGVerticalLayout(this));

		pM = pModule;
		pRegs = (Gtp_regs *)pM->BaseAddr;
		
		TGCompositeFrame *pF1, *pF2;
		AddFrame(pF1 = new TGGroupFrame(this, "Subsystem Trigger Scalers", kVerticalFrame), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pF1->AddFrame(pF2 = new TGHorizontalFrame(pF1), new TGLayoutHints(kLHintsExpandX));
				pF2->AddFrame(pButtonUpdateScalers = new TGTextButton(pF2, new TGHotString("Update Scalers"), BTN_UPDATE_SCALERS));
					pButtonUpdateScalers->Associate(this);
		
			pF1->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pF1, 600, 400), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
				pCanvas->GetCanvas()->SetBorderMode(0);

				TVirtualPad *pPad = pCanvas->GetCanvas()->cd();
					pH_Subsystems = new TH2Poly();
					pH_Subsystems->SetTitle("Hall D Subsystem Trigger Rates");
					pH_Subsystems->SetStats(0);

					for(i = 0; i < sizeof(TAG)/sizeof(TAG[0]); i++)
						pH_Subsystems->AddBin(4, TAG[i].x, TAG[i].y);

					for(i = 0; i < sizeof(PS)/sizeof(PS[0]); i++)
						pH_Subsystems->AddBin(4, PS[i].x, PS[i].y);

					for(i = 0; i < sizeof(ST)/sizeof(ST[0]); i++)
						pH_Subsystems->AddBin(4, ST[i].x, ST[i].y);
//					...create TGaxis for each subdetector identify channel ids

					for(i = 0; i < sizeof(TAG)/sizeof(TAG[0]); i++)
						pH_Subsystems->Fill(
							(TAG[i].x[0]+TAG[i].x[1]+TAG[i].x[2]+TAG[i].x[3])/4,
							(TAG[i].y[0]+TAG[i].y[1]+TAG[i].y[2]+TAG[i].y[3])/4,
							i+1);

					for(i = 0; i < sizeof(PS)/sizeof(PS[0]); i++)
						pH_Subsystems->Fill(
							(PS[i].x[0]+PS[i].x[1]+PS[i].x[2]+PS[i].x[3])/4,
							(PS[i].y[0]+PS[i].y[1]+PS[i].y[2]+PS[i].y[3])/4,
							i+1);

					for(i = 0; i < sizeof(ST)/sizeof(ST[0]); i++)
						pH_Subsystems->Fill(
							(ST[i].x[0]+ST[i].x[1]+ST[i].x[2]+ST[i].x[3])/4,
							(ST[i].y[0]+ST[i].y[1]+ST[i].y[2]+ST[i].y[3])/4,
							i+1);
					
					gStyle->SetPalette(1);
					pH_Subsystems->Draw("ACOLZTEXT");//ACOLZTEXT
					pPad->Modified();
					pPad->Update();

					TGaxis *axis;
					double xmin, xmax, ymin, ymax;
					
					// TAG axis
					xmin = TAG_CELL_POS_X;
					ymin = TAG_CELL_POS_Y-TAG_AXIS_OFFSET;
					xmax = TAG_CELL_POS_X+64.0*TAG_CELL_WIDTH;
					ymax = TAG_CELL_POS_Y-TAG_AXIS_OFFSET;
					axis = new TGaxis(xmin, ymin, xmax, ymax,0,64,510,"+B");
					axis->SetTitle("Tagger");
					axis->CenterTitle();
					axis->Draw();

					// PS left-axis
					xmin = PS_CELL_POS_X-PS_AXIS_OFFSET;
					ymin = PS_CELL_POS_Y+PS_RL_OFFSET;
					xmax = PS_CELL_POS_X-PS_AXIS_OFFSET;
					ymax = PS_CELL_POS_Y+PS_RL_OFFSET+8.0*PS_CELL_HEIGHT;
					axis = new TGaxis(xmin, ymin, xmax, ymax,0,8,510,"-R");
					axis->SetTitle("PS Left");
					axis->SetTitleOffset(0.7);
					axis->CenterTitle();
					axis->Draw();

					// PS right-axis
					xmin = PS_CELL_POS_X-PS_AXIS_OFFSET;
					ymin = PS_CELL_POS_Y-PS_RL_OFFSET-8.0*PS_CELL_HEIGHT;
					xmax = PS_CELL_POS_X-PS_AXIS_OFFSET;
					ymax = PS_CELL_POS_Y-PS_RL_OFFSET;
					axis = new TGaxis(xmin, ymin, xmax, ymax,0,8,510,"-R");
					axis->SetTitle("PS Right");
					axis->SetTitleOffset(0.7);
					axis->CenterTitle();
					axis->Draw();
					
			pF1->AddFrame(pTVScalers = new TGTextView(pF1), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
					
//printf("xmin=%f,xmax=%f,ymin=%f,ymax=%f\n", gPad->GetUxmin(), gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUymax());

/*					
				
					pH_Rate = new TH1D("fcalrate", ";ADC Integral;Rate(Hz)", 32, bins);
pH_Rate->Fill(10);
					pH_Rate->SetFillColor(49);
					pH_Rate->SetStats(0);
					pH_Rate->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_Rate->GetXaxis()->CenterLabels();
					pH_Rate->Draw("bar2");
					pPad->SetLogx(1);
					pPad->SetLogy(1);
					pPad->Modified();
					pPad->Update();

				pPad = pCanvas->GetCanvas()->cd(2);
					pH_Hits = new TH1D("fcalhits", ";ADC Integral;Hits", 32, bins);
pH_Hits->Fill(2); pH_Hits->Fill(2); pH_Hits->Fill(9);
					pH_Hits->SetFillColor(50);
					pH_Hits->SetStats(0);
					pH_Hits->GetXaxis()->SetNdivisions(16, kFALSE);
					pH_Hits->GetXaxis()->CenterLabels();
					pH_Hits->Draw("bar2");
					pPad->SetLogx(1);
					pPad->SetLogy(1);
					pPad->Modified();
					pPad->Update();
					*/
		UpdateScalers();
	}
	
	void UpdateScalers()
	{
	}
	
	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
	{
		if((GET_MSG(msg) == kC_TEXTENTRY) && (GET_SUBMSG(msg) == kTE_TEXTCHANGED))
		{
			switch(parm1)
			{
				default:
					printf("textentry id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_COMBOBOX))
		{
			switch(parm1)
			{
				default:
					printf("combo id %d selected\n", (int)parm1);
					break;
			}
		}
		else if((GET_MSG(msg) == kC_COMMAND) && (GET_SUBMSG(msg) == kCM_BUTTON))
		{
			switch(parm1)
			{
				case BTN_UPDATE_SCALERS:
					UpdateScalers();
					break;
				default:
					printf("button id %d pressed\n", (int)parm1);
					break;
			}
		}
		return kTRUE;
	}

private:
	enum
	{
		BTN_UPDATE_SCALERS
	};

	ModuleFrame				*pM;
	Gtp_regs					*pRegs;
	
	TRootEmbeddedCanvas	*pCanvas;
	
	TH2Poly					*pH_Subsystems;

	TGTextButton			*pButtonUpdateScalers;
	
	TGTextView				*pTVScalers;
};

#endif
