#include <stdio.h>
#include <stdlib.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TPaveText.h>
#include <TH2Poly.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRootEmbeddedCanvas.h>
#include <TApplication.h>
#include <TGFileDialog.h>
#include <TGButton.h>
#include <TImage.h>
#include <THashList.h>
#include <TTimeStamp.h>

#include <iostream>

#include "CrateMsgClient.h"

//#define SCALER_UPDATE_PERIOD	1000	/* in milliseconds */
//#define SCALER_UPDATE_PERIOD	200	/* in milliseconds */
#define SCALER_UPDATE_PERIOD	50	/* in milliseconds */

typedef struct
{
	int slot;
	int channel;
	int x;
	int y;
} FT_map_entry;

FT_map_entry adcft1_map[] = {
		{	15	,	8	,	-11,	1	},
		{	15	,	9	,	-7	,	-1	},
		{	15	,	7	,	-6	,	10	},
		{	15	,	10	,	-3	,	-7	},
		{	15	,	6	,	-3	,	6	},
		{	15	,	11	,	-1	,	-5	},
		{	3	,	5	,	1	,	-11	},
		{	3	,	6	,	1	,	-10	},
		{	3	,	4	,	1	,	-9	},
		{	3	,	3	,	1	,	-8	},
		{	3	,	2	,	1	,	-7	},
		{	3	,	1	,	1	,	-6	},
		{	3	,	0	,	1	,	-5	},
		{	15	,	5	,	1	,	5	},
		{	14	,	15	,	1	,	6	},
		{	14	,	14	,	1	,	7	},
		{	14	,	13	,	1	,	8	},
		{	14	,	12	,	1	,	9	},
		{	14	,	10	,	1	,	10	},
		{	14	,	11	,	1	,	11	},
		{	3	,	13	,	2	,	-10	},
		{	3	,	12	,	2	,	-11	},
		{	3	,	11	,	2	,	-9	},
		{	3	,	10	,	2	,	-8	},
		{	3	,	9	,	2	,	-7	},
		{	3	,	8	,	2	,	-6	},
		{	3	,	7	,	2	,	-5	},
		{	14	,	9	,	2	,	5	},
		{	14	,	8	,	2	,	6	},
		{	14	,	7	,	2	,	7	},
		{	14	,	6	,	2	,	8	},
		{	14	,	5	,	2	,	9	},
		{	14	,	3	,	2	,	10	},
		{	14	,	4	,	2	,	11	},
		{	4	,	2	,	3	,	-11	},
		{	4	,	3	,	3	,	-10	},
		{	4	,	4	,	3	,	-9	},
		{	4	,	1	,	3	,	-8	},
		{	4	,	0	,	3	,	-7	},
		{	15	,	0	,	3	,	-6	},
		{	3	,	15	,	3	,	-5	},
		{	3	,	14	,	3	,	-4	},
		{	14	,	2	,	3	,	4	},
		{	14	,	1	,	3	,	5	},
		{	14	,	0	,	3	,	6	},
		{	15	,	4	,	3	,	7	},
		{	13	,	15	,	3	,	8	},
		{	13	,	12	,	3	,	9	},
		{	13	,	13	,	3	,	10	},
		{	13	,	14	,	3	,	11	},
		{	4	,	10	,	4	,	-10	},
		{	4	,	11	,	4	,	-9	},
		{	4	,	12	,	4	,	-8	},
		{	4	,	9	,	4	,	-7	},
		{	4	,	8	,	4	,	-6	},
		{	4	,	7	,	4	,	-5	},
		{	4	,	6	,	4	,	-4	},
		{	4	,	5	,	4	,	-3	},
		{	13	,	11	,	4	,	3	},
		{	13	,	10	,	4	,	4	},
		{	13	,	9	,	4	,	5	},
		{	13	,	8	,	4	,	6	},
		{	13	,	7	,	4	,	7	},
		{	13	,	4	,	4	,	8	},
		{	13	,	5	,	4	,	9	},
		{	13	,	6	,	4	,	10	},
		{	5	,	6	,	5	,	-10	},
		{	5	,	5	,	5	,	-9	},
		{	5	,	4	,	5	,	-8	},
		{	5	,	3	,	5	,	-7	},
		{	5	,	2	,	5	,	-6	},
		{	5	,	1	,	5	,	-5	},
		{	5	,	0	,	5	,	-4	},
		{	4	,	15	,	5	,	-3	},
		{	4	,	14	,	5	,	-2	},
		{	4	,	13	,	5	,	-1	},
		{	13	,	3	,	5	,	1	},
		{	13	,	2	,	5	,	2	},
		{	13	,	1	,	5	,	3	},
		{	13	,	0	,	5	,	4	},
		{	10	,	15	,	5	,	5	},
		{	10	,	14	,	5	,	6	},
		{	10	,	13	,	5	,	7	},
		{	10	,	12	,	5	,	8	},
		{	10	,	11	,	5	,	9	},
		{	10	,	10	,	5	,	10	},
		{	15	,	1	,	6	,	-10	},
		{	5	,	15	,	6	,	-9	},
		{	5	,	14	,	6	,	-8	},
		{	5	,	13	,	6	,	-7	},
		{	5	,	12	,	6	,	-6	},
		{	5	,	11	,	6	,	-5	},
		{	5	,	10	,	6	,	-4	},
		{	5	,	9	,	6	,	-3	},
		{	5	,	8	,	6	,	-2	},
		{	5	,	7	,	6	,	-1	},
		{	10	,	9	,	6	,	1	},
		{	10	,	8	,	6	,	2	},
		{	10	,	7	,	6	,	3	},
		{	10	,	6	,	6	,	4	},
		{	10	,	5	,	6	,	5	},
		{	10	,	4	,	6	,	6	},
		{	10	,	3	,	6	,	7	},
		{	10	,	2	,	6	,	8	},
		{	10	,	1	,	6	,	9	},
		{	10	,	0	,	6	,	10	},
		{	15	,	3	,	7	,	1	},
		{	9	,	15	,	7	,	2	},
		{	9	,	14	,	7	,	3	},
		{	9	,	13	,	7	,	4	},
		{	9	,	12	,	7	,	5	},
		{	9	,	8	,	7	,	6	},
		{	9	,	9	,	7	,	7	},
		{	9	,	10	,	7	,	8	},
		{	9	,	11	,	7	,	9	},
		{	6	,	5	,	7	,	-9	},
		{	6	,	6	,	7	,	-8	},
		{	6	,	7	,	7	,	-7	},
		{	6	,	8	,	7	,	-6	},
		{	6	,	4	,	7	,	-5	},
		{	6	,	3	,	7	,	-4	},
		{	6	,	2	,	7	,	-3	},
		{	6	,	1	,	7	,	-2	},
		{	6	,	0	,	7	,	-1	},
		{	9	,	7	,	8	,	1	},
		{	9	,	6	,	8	,	2	},
		{	9	,	5	,	8	,	3	},
		{	9	,	4	,	8	,	4	},
		{	9	,	3	,	8	,	5	},
		{	9	,	0	,	8	,	6	},
		{	9	,	1	,	8	,	7	},
		{	9	,	2	,	8	,	8	},
		{	6	,	14	,	8	,	-8	},
		{	6	,	15	,	8	,	-7	},
		{	7	,	0	,	8	,	-6	},
		{	6	,	13	,	8	,	-5	},
		{	6	,	12	,	8	,	-4	},
		{	6	,	11	,	8	,	-3	},
		{	6	,	10	,	8	,	-2	},
		{	6	,	9	,	8	,	-1	},
		{	7	,	6	,	9	,	-7	},
		{	7	,	7	,	9	,	-6	},
		{	7	,	5	,	9	,	-5	},
		{	7	,	4	,	9	,	-4	},
		{	7	,	3	,	9	,	-3	},
		{	7	,	2	,	9	,	-2	},
		{	7	,	1	,	9	,	-1	},
		{	8	,	15	,	9	,	1	},
		{	8	,	14	,	9	,	2	},
		{	8	,	13	,	9	,	3	},
		{	8	,	12	,	9	,	4	},
		{	8	,	11	,	9	,	5	},
		{	8	,	9	,	9	,	6	},
		{	8	,	10	,	9	,	7	},
		{	8	,	8	,	10	,	1	},
		{	8	,	7	,	10	,	2	},
		{	8	,	6	,	10	,	3	},
		{	8	,	5	,	10	,	4	},
		{	8	,	4	,	10	,	5	},
		{	8	,	3	,	10	,	6	},
		{	7	,	13	,	10	,	-6	},
		{	7	,	12	,	10	,	-5	},
		{	7	,	11	,	10	,	-4	},
		{	7	,	10	,	10	,	-3	},
		{	7	,	9	,	10	,	-2	},
		{	7	,	8	,	10	,	-1	},
		{	8	,	0	,	11	,	1	},
		{	8	,	1	,	11	,	2	},
		{	8	,	2	,	11	,	3	},
		{	7	,	14	,	11	,	-3	},
		{	7	,	15	,	11	,	-2	},
		{	15	,	2	,	11	,	-1	}
	};

FT_map_entry adcft2_map[] = {
		{	7	,	15	,	-11	,	2	},
		{	7	,	14	,	-11	,	3	},
		{	8	,	2	,	-11	,	-3	},
		{	8	,	1	,	-11	,	-2	},
		{	8	,	0	,	-11	,	-1	},
		{	7	,	8	,	-10	,	1	},
		{	7	,	9	,	-10	,	2	},
		{	7	,	10	,	-10	,	3	},
		{	7	,	11	,	-10	,	4	},
		{	7	,	12	,	-10	,	5	},
		{	7	,	13	,	-10	,	6	},
		{	8	,	3	,	-10	,	-6	},
		{	8	,	4	,	-10	,	-5	},
		{	8	,	5	,	-10	,	-4	},
		{	8	,	6	,	-10	,	-3	},
		{	8	,	7	,	-10	,	-2	},
		{	8	,	8	,	-10	,	-1	},
		{	8	,	10	,	-9	,	-7	},
		{	8	,	9	,	-9	,	-6	},
		{	8	,	11	,	-9	,	-5	},
		{	8	,	12	,	-9	,	-4	},
		{	8	,	13	,	-9	,	-3	},
		{	8	,	14	,	-9	,	-2	},
		{	8	,	15	,	-9	,	-1	},
		{	7	,	1	,	-9	,	1	},
		{	7	,	2	,	-9	,	2	},
		{	7	,	3	,	-9	,	3	},
		{	7	,	4	,	-9	,	4	},
		{	7	,	5	,	-9	,	5	},
		{	7	,	7	,	-9	,	6	},
		{	7	,	6	,	-9	,	7	},
		{	9	,	2	,	-8	,	-8	},
		{	9	,	1	,	-8	,	-7	},
		{	9	,	0	,	-8	,	-6	},
		{	9	,	3	,	-8	,	-5	},
		{	9	,	4	,	-8	,	-4	},
		{	9	,	5	,	-8	,	-3	},
		{	9	,	6	,	-8	,	-2	},
		{	9	,	7	,	-8	,	-1	},
		{	6	,	9	,	-8	,	1	},
		{	6	,	10	,	-8	,	2	},
		{	6	,	11	,	-8	,	3	},
		{	6	,	12	,	-8	,	4	},
		{	6	,	13	,	-8	,	5	},
		{	7	,	0	,	-8	,	6	},
		{	6	,	15	,	-8	,	7	},
		{	6	,	14	,	-8	,	8	},
		{	6	,	0	,	-7	,	1	},
		{	6	,	1	,	-7	,	2	},
		{	6	,	2	,	-7	,	3	},
		{	6	,	3	,	-7	,	4	},
		{	6	,	4	,	-7	,	5	},
		{	6	,	8	,	-7	,	6	},
		{	6	,	7	,	-7	,	7	},
		{	6	,	6	,	-7	,	8	},
		{	6	,	5	,	-7	,	9	},
		{	9	,	11	,	-7	,	-9	},
		{	9	,	10	,	-7	,	-8	},
		{	9	,	9	,	-7	,	-7	},
		{	9	,	8	,	-7	,	-6	},
		{	9	,	12	,	-7	,	-5	},
		{	9	,	13	,	-7	,	-4	},
		{	9	,	14	,	-7	,	-3	},
		{	9	,	15	,	-7	,	-2	},
		{	5	,	7	,	-6	,	1	},
		{	5	,	8	,	-6	,	2	},
		{	5	,	9	,	-6	,	3	},
		{	5	,	10	,	-6	,	4	},
		{	5	,	11	,	-6	,	5	},
		{	5	,	12	,	-6	,	6	},
		{	5	,	13	,	-6	,	7	},
		{	5	,	14	,	-6	,	8	},
		{	5	,	15	,	-6	,	9	},
		{	10	,	0	,	-6	,	-10	},
		{	10	,	1	,	-6	,	-9	},
		{	10	,	2	,	-6	,	-8	},
		{	10	,	3	,	-6	,	-7	},
		{	10	,	4	,	-6	,	-6	},
		{	10	,	5	,	-6	,	-5	},
		{	10	,	6	,	-6	,	-4	},
		{	10	,	7	,	-6	,	-3	},
		{	10	,	8	,	-6	,	-2	},
		{	10	,	9	,	-6	,	-1	},
		{	10	,	10	,	-5	,	-10	},
		{	10	,	11	,	-5	,	-9	},
		{	10	,	12	,	-5	,	-8	},
		{	10	,	13	,	-5	,	-7	},
		{	10	,	14	,	-5	,	-6	},
		{	10	,	15	,	-5	,	-5	},
		{	13	,	0	,	-5	,	-4	},
		{	13	,	1	,	-5	,	-3	},
		{	13	,	2	,	-5	,	-2	},
		{	13	,	3	,	-5	,	-1	},
		{	4	,	13	,	-5	,	1	},
		{	4	,	14	,	-5	,	2	},
		{	4	,	15	,	-5	,	3	},
		{	5	,	0	,	-5	,	4	},
		{	5	,	1	,	-5	,	5	},
		{	5	,	2	,	-5	,	6	},
		{	5	,	3	,	-5	,	7	},
		{	5	,	4	,	-5	,	8	},
		{	5	,	5	,	-5	,	9	},
		{	5	,	6	,	-5	,	10	},
		{	13	,	6	,	-4	,	-10	},
		{	13	,	5	,	-4	,	-9	},
		{	13	,	4	,	-4	,	-8	},
		{	13	,	7	,	-4	,	-7	},
		{	13	,	8	,	-4	,	-6	},
		{	13	,	9	,	-4	,	-5	},
		{	13	,	10	,	-4	,	-4	},
		{	13	,	11	,	-4	,	-3	},
		{	4	,	5	,	-4	,	3	},
		{	4	,	6	,	-4	,	4	},
		{	4	,	7	,	-4	,	5	},
		{	4	,	8	,	-4	,	6	},
		{	4	,	9	,	-4	,	7	},
		{	4	,	12	,	-4	,	8	},
		{	4	,	11	,	-4	,	9	},
		{	4	,	10	,	-4	,	10	},
		{	13	,	14	,	-3	,	-11	},
		{	13	,	13	,	-3	,	-10	},
		{	13	,	12	,	-3	,	-9	},
		{	13	,	15	,	-3	,	-8	},
		{	14	,	0	,	-3	,	-6	},
		{	14	,	1	,	-3	,	-5	},
		{	14	,	2	,	-3	,	-4	},
		{	3	,	14	,	-3	,	4	},
		{	3	,	15	,	-3	,	5	},
		{	4	,	0	,	-3	,	7	},
		{	4	,	1	,	-3	,	8	},
		{	4	,	4	,	-3	,	9	},
		{	4	,	3	,	-3	,	10	},
		{	4	,	2	,	-3	,	11	},
		{	14	,	4	,	-2	,	-11	},
		{	14	,	3	,	-2	,	-10	},
		{	14	,	5	,	-2	,	-9	},
		{	14	,	6	,	-2	,	-8	},
		{	14	,	7	,	-2	,	-7	},
		{	14	,	8	,	-2	,	-6	},
		{	14	,	9	,	-2	,	-5	},
		{	3	,	7	,	-2	,	5	},
		{	3	,	8	,	-2	,	6	},
		{	3	,	9	,	-2	,	7	},
		{	3	,	10	,	-2	,	8	},
		{	3	,	11	,	-2	,	9	},
		{	3	,	12	,	-2	,	11	},
		{	3	,	13	,	-2	,	10	},
		{	14	,	11	,	-1	,	-11	},
		{	14	,	10	,	-1	,	-10	},
		{	14	,	12	,	-1	,	-9	},
		{	14	,	13	,	-1	,	-8	},
		{	14	,	14	,	-1	,	-7	},
		{	14	,	15	,	-1	,	-6	},
		{	3	,	0	,	-1	,	5	},
		{	3	,	1	,	-1	,	6	},
		{	3	,	2	,	-1	,	7	},
		{	3	,	3	,	-1	,	8	},
		{	3	,	4	,	-1	,	9	},
		{	3	,	6	,	-1	,	10	},
		{	3	,	5	,	-1	,	11	}	
	};

class ft_scalers_fadc_app : public TGMainFrame
{
    private:
        int connect_to_server();
        int read_scalers();
        Bool_t  get_ch(int x, int y, int *crate, int *slot, int *ch);
        int get_crate_map();
        int crate_map[2][22];

        unsigned int fadc_crate_slot_scalers[2][22][16];
        unsigned int fadc_crate_slot_ref[2][22];

        void draw_scalers();
        void normalize_scalers();

        CrateMsgClient *crates[2];
        TCanvas *pTC;
        TH2I *pH;
        TRootEmbeddedCanvas *pCanvas;
    public:
        ft_scalers_fadc_app(const TGWindow *p, UInt_t w, UInt_t h);
        ~ft_scalers_fadc_app();

        void DoExit();
        void button_Save();
        void button_LogEnable();
        void refresh_scalers();

        ClassDef(ft_scalers_fadc_app, 0)
};

int ft_scalers_fadc_app::connect_to_server()
{
    for(int i = 0; i < 2; i++)
    {
        char buf[100];
        sprintf(buf, "adcft%d", i+1);
        crates[i] = new CrateMsgClient(buf, 6102);
        if(!crates[i]->IsValid())
            return -1;
    }
    return 0;
}

int ft_scalers_fadc_app::read_scalers()
{
    unsigned int *buf;
    int len;

    for(int crate = 0; crate < 2; crate++)
    {
        for(int slot = 0; slot <= 20; slot++)
        {
            if(crate_map[crate][slot] == SCALER_TYPE_FADC250)
            {
                if(!crates[crate]->ScalerReadBoard(slot, &buf, &len)) return -3;
                if(len == 17)
                {
                    for(int ch = 0; ch < 16; ch++)
                        fadc_crate_slot_scalers[crate][slot][ch] = buf[ch];
                    fadc_crate_slot_ref[crate][slot] = buf[16];
                }
                delete [] buf;
            }
        }
    }
    return 0;
}

void ft_scalers_fadc_app::normalize_scalers()
{
    float ref, scaled;

    for(int crate = 0; crate < 2; crate++)
    {
        for(int slot = 0; slot <= 20; slot++)
        {
            if(crate_map[crate][slot] == SCALER_TYPE_FADC250)
            {
                if(fadc_crate_slot_ref[crate][slot] <= 0)
                {
                    printf("Error in normalize_scalers(): fadc_crate_slot_ref[%d][%d]=%d not valid\n", crate, slot, fadc_crate_slot_ref[crate][slot]);
                    ref = 1;
                }
                else
                    ref = 488281.25f / (float)fadc_crate_slot_ref[crate][slot];

                for(int ch = 0; ch < 16; ch++)
                {
                    scaled = (float)fadc_crate_slot_scalers[crate][slot][ch] * ref;
                    fadc_crate_slot_scalers[crate][slot][ch] = (int)scaled;
                }
            }
        }
    }
}

Bool_t ft_scalers_fadc_app::get_ch(int x, int y, int *crate, int *slot, int *ch)
{
	for(int i = 0; i < sizeof(adcft1_map)/sizeof(adcft1_map[0]); i++)
	{
		if( (x == adcft1_map[i].x) && (y == adcft1_map[i].y) )
		{
			*crate = 0;
			*slot = adcft1_map[i].slot;
			*ch = adcft1_map[i].channel;
			return kTRUE;
		}
	}
	for(int i = 0; i < sizeof(adcft2_map)/sizeof(adcft2_map[0]); i++)
	{
		if( (x == adcft2_map[i].x) && (y == adcft2_map[i].y) )
		{
			*crate = 1;
			*slot = adcft2_map[i].slot;
			*ch = adcft2_map[i].channel;
			return kTRUE;
		}
	}
	return kFALSE;
}

void ft_scalers_fadc_app::draw_scalers()
{
    static bool called=0;

    static TPaveText tt1(0.1,0.97,0.3,1.00,"NDC");
    static TPaveText tt2(0.1,0.94,0.3,0.97,"NDC");
    static TPaveText ttM(0.1,0.91,0.3,0.94,"NDC");
    static TBox bb;
    static TLine ll;

    if (!called)
    {
        called=1;
        bb.SetFillStyle(1001);
        bb.SetFillColor(kWhite);
        bb.SetLineWidth(1);
        bb.SetLineColor(kBlack);
        tt1.SetBorderSize(0);
        tt2.SetBorderSize(0);
        tt1.SetFillColor(kWhite);
        tt2.SetFillColor(kWhite);
        ttM.SetBorderSize(0);
        ttM.SetFillColor(kWhite);
        ttM.SetTextColor(kRed);
    }

    unsigned int max=0;
	 unsigned int total=0;
    pH->SetMinimum(0);
    pH->Reset();
    for(int x = -11; x <= 11; x++)
    {
        for(int y = -11; y <= 11; y++)
        {
			   int ch, slot, crate;
            
            if(get_ch(x, y, &crate, &slot, &ch))
            {
					 unsigned int scaler = fadc_crate_slot_scalers[crate][slot][ch];
					 total+= scaler;
                pH->Fill(x>0?x-1:x, y>0?y-1:y, (float)scaler);
                if(scaler > max) max = scaler;
            }
        }
    }

    tt1.Clear();
    tt2.Clear();
    ttM.Clear();
    tt1.AddText(Form("Total:  %.1E Hz",(float)total));
    tt2.AddText(Form("Total:  %.2f MHz",(float)total/1e6));
    ttM.AddText(Form("MAX SINGLE CRYSTAL = %.2f Hz",(float)max));
    tt1.Draw();
    tt2.Draw();
    ttM.Draw();
    pCanvas->GetCanvas()->Modified();
    pCanvas->GetCanvas()->Update();
}

int ft_scalers_fadc_app::get_crate_map()
{
    unsigned int *map;
    int len;

    for(int crate = 0; crate < 2; crate++)
    {
        if(!crates[crate]->GetCrateMap(&map, &len)) return -4;
        if(len > 22) return -5;

        for(int slot = 0; slot < len; slot++)
        {
            crate_map[crate][slot] = map[slot];
            printf("crate %d, slot %d, type %d\n", crate, slot, map[slot]);
        }
        delete [] map;
    }
    return 0;
}

void ft_scalers_fadc_app::refresh_scalers()
{
    if(read_scalers() < 0) DoExit();

    normalize_scalers();
    draw_scalers();

    TTimer::SingleShot(SCALER_UPDATE_PERIOD, "ft_scalers_fadc_app", this, "refresh_scalers()");
}

void ft_scalers_fadc_app::DoExit()
{
    gApplication->Terminate();
}

ft_scalers_fadc_app::~ft_scalers_fadc_app()
{
    Cleanup();
}

void ft_scalers_fadc_app::button_LogEnable()
{
    pCanvas->GetCanvas()->SetLogz(!pCanvas->GetCanvas()->GetLogz());
}

void ft_scalers_fadc_app::button_Save()
{
    TClass* clGMainFrame = TClass::GetClass("TGMainFrame");
    TGWindow* win = 0;

    TTimeStamp tt;
    TString tstub=tt.AsString("lc");
    tstub.ReplaceAll(" ","_");

    gPad->SaveAs(Form("%s/screenshots/FTSCALERS_%s.png",
                gSystem->Getenv("HOME"),tstub.Data()));
    std::cerr<<"AL:SFHDLA"<<std::endl;
    return;

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

    if(fi.fFilename != NULL) 
    {
        printf("saving to file: %s\n", fi.fFilename);
        TIter iWin(gClient->GetListOfWindows());
        while ((win = (TGWindow*)iWin()))
        {
            if(win->InheritsFrom(clGMainFrame))
            {
                TImage *img = TImage::Create();
                img->FromWindow(win->GetId());
                TString dog=gSystem->BaseName(fi.fFilename);
                dog.ReplaceAll(".","__"+tstub+".");
                dog=Form("%s/screenshots/FTScalers_FADC_%s",
                        gSystem->Getenv("HOME"),dog.Data());
                std::cout<<"Saving as:   "<<dog<<std::endl;
                img->WriteImage(dog);
                img->WriteImage(fi.fFilename);
                break;
            }
        }
    }
}

ft_scalers_fadc_app::ft_scalers_fadc_app(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h) 
{
    printf("ft_scalers_fadc_app started...\n");

    SetCleanup(kDeepCleanup);

    Connect("CloseWindow()", "ft_scalers_fadc_app", this, "DoExit()");
    DontCallClose();

    TGCompositeFrame *pTF;
    TGTextButton *pB;

    AddFrame(pTF= new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
    pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("LogToggle")), new TGLayoutHints(kLHintsLeft | kLHintsCenterX));
    pB->Connect("Clicked()", "ft_scalers_fadc_app", this, "button_LogEnable()");
    pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Save")), new TGLayoutHints(kLHintsLeft | kLHintsCenterX));
    pB->Connect("Clicked()", "ft_scalers_fadc_app", this, "button_Save()");
    pTF->AddFrame(pB = new TGTextButton(pTF, new TGHotString("Exit")), new TGLayoutHints(kLHintsLeft | kLHintsCenterX));
    pB->Connect("Clicked()", "ft_scalers_fadc_app", this, "DoExit()");
    AddFrame(pTF = new TGVerticalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
    pTF->AddFrame(pCanvas = new TRootEmbeddedCanvas("c1", pTF, w, h), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    pCanvas->GetCanvas()->SetBorderMode(0);
    pCanvas->GetCanvas()->cd();

    pH = new TH2I("FT FADC Scalers", ";X;Y", 22, -11.0, 11.0, 22, -11.0, 11.0);
    pH->SetStats(0);
    pH->GetXaxis()->CenterLabels();
    pH->GetXaxis()->SetNdivisions(22, kFALSE);
    pH->GetXaxis()->SetTickLength(0);
    pH->GetYaxis()->CenterLabels();
    pH->GetYaxis()->SetNdivisions(22, kFALSE);
    pH->GetYaxis()->SetTickLength(0);
    pH->GetYaxis()->SetTitleOffset(0.5);
    pH->Draw("COLZTEXT");
    TText tt;
    tt.DrawTextNDC(0.4,0.92,"FT FADC SCALERS");
    tt.SetTextAngle(90);
    tt.DrawText(25.5,0,"kHz");
    tt.SetTextAngle(0);
   
    gPad->SetLogz(1);
    gPad->SetGrid(1,1);
    gPad->SetLeftMargin(0.05);
    gStyle->SetGridStyle(1);
    gStyle->SetGridColor(kGray);

    int i = -11;
    for(int n = 1; n <= 22; n++)
    {
        pH->GetXaxis()->SetBinLabel(n,Form("%d", i));
		  pH->GetYaxis()->SetBinLabel(n,Form("%d", i));
        i++;
        if(i == 0) i++;
    }

    memset(fadc_crate_slot_scalers, 0, sizeof(fadc_crate_slot_scalers));
    memset(fadc_crate_slot_ref, 0xFF, sizeof(fadc_crate_slot_ref));

    if(connect_to_server() < 0) DoExit();
    if(get_crate_map() < 0) DoExit();

    SetWindowName("FT FADC SCALERS");
    MapSubwindows();
    Resize();
    MapWindow();

    TTimer::SingleShot(SCALER_UPDATE_PERIOD, "ft_scalers_fadc_app", this, "refresh_scalers()");
}

void ft_scalers_fadc_app_run()
{
    new ft_scalers_fadc_app(gClient->GetRoot(), 800, 800);
}
