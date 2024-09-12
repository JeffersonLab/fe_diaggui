#ifndef ALERTFEB_EB_H
#define ALERTFEB_EB_H

#include <stdlib.h>
#include <list>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_Regs.h"

#define ALERTFEB_EB_POLL_RATE    20

#define MAX_PLOT_NUM             50

using namespace std;

static bool alert_eb_compare_tdc_hit(const tdc_hit_t &a, const tdc_hit_t &b)
{
  return (a.t < b.t);
}

class ALERTFEB_EB  : public TGCompositeFrame
{
public:
  ALERTFEB_EB(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    pM = pModule;
    pRegs = (ALERTFEB_Regs *)pM->BaseAddr;

    pSockEb = NULL;

    TGCompositeFrame *pTF1, *pTF2;
    TGTextButton *pB;

    AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
      pTF1->AddFrame(pBConnect = new TGTextButton(pTF1, "Connect", BTN_ALERTFEB_CONNECT), new TGLayoutHints(kLHintsCenterX));
        pBConnect->SetWidth(300);
        pBConnect->Associate(this);
      pTF1->AddFrame(pB = new TGTextButton(pTF1, "Reload", BTN_ALERTFEB_RELOAD), new TGLayoutHints(kLHintsCenterX));
        pB->SetWidth(300);
        pB->Associate(this);
      pTF1->AddFrame(pB = new TGTextButton(pTF1, "Start", BTN_ALERTFEB_START), new TGLayoutHints(kLHintsCenterX));
        pB->SetWidth(300);
        pB->Associate(this);
      pTF1->AddFrame(pB = new TGTextButton(pTF1, "ClearHist", BTN_CLEAR_HIST), new TGLayoutHints(kLHintsCenterX));
        pB->SetWidth(300);
        pB->Associate(this);

      pTF1->AddFrame(pTF2 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
        pTF2->AddFrame(pLabelThreshold = new TGLabel(pTF2, new TGString(Form("DACThreshold (%d):", 425))), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
        pTF2->AddFrame(pSliderThreshold = new TGHSlider(pTF2, 100, kSlider1 | kScaleBoth, SDR_THRESHOLD), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
          pSliderThreshold->SetRange(0, 1023);
  //				pSliderUpdateTime->SetEnabled(kFALSE);
          pSliderThreshold->SetPosition(325);
          pSliderThreshold->Associate(this);

      pTF1->AddFrame(pComboDisplayedChannels = new TGComboBox(pTF1, COM_TDCDISPLAYCHANNELS));
				for(int i = 0; i < 13; i++)
					pComboDisplayedChannels->AddEntry(Form("TDC LE %d-%d", i*4,i*4+3), 0+i);
				for(int i = 0; i < 13; i++)
					pComboDisplayedChannels->AddEntry(Form("TDC Width %d-%d", i*4,i*4+3), 13+i);
				for(int i = 0; i < 13; i++)
					pComboDisplayedChannels->AddEntry(Form("TDC Ref %d-%d", i*4,i*4+3), 26+i);
				pComboDisplayedChannels->Select(0);
				pComboDisplayedChannels->SetWidth(150);
				pComboDisplayedChannels->SetHeight(20);
				pComboDisplayedChannels->Associate(this);

    AddFrame(pCanvasHisto = new TRootEmbeddedCanvas("TDC Plots", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasHisto->GetCanvas()->SetBorderMode(0);
      pCanvasHisto->GetCanvas()->Divide(2, 2);

      for(int i=0;i<52;i++)
      {
        pTH_TDC_LE[i] = new TH1I(Form("LE:Ch%d", i), Form("LE:Ch%d;time(ns)", i), 1000, 0.0, 2000.0);
        pTH_TDC_LE[i]->SetLineColor(kBlack);
        pTH_TDC_LE[i]->SetFillColor(kBlue);

        pTH_TDC_Width[i] = new TH1I(Form("Width:Ch%d", i), Form("Width:Ch%d;time(ns)", i), 1000, 0.0, 4096.0);
        pTH_TDC_Width[i]->SetLineColor(kBlack);
        pTH_TDC_Width[i]->SetFillColor(kBlue);

        pTH_TDC_Ref[i] = new TH1I(Form("Ref:Ref-Ch%d", i), Form("Ref:Ref-Ch%d;time(ps)", i), 256, -2000.0, 2000.0);
        pTH_TDC_Ref[i]->SetLineColor(kBlack);
        pTH_TDC_Ref[i]->SetFillColor(kBlue);
     }

    DrawPlots();
		UpdatePlots();

    pTimerUpdate = new TTimer(this, ALERTFEB_EB_POLL_RATE, kTRUE);
  }

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
    {
      if(pSockEb)
      {
        ReadEb();
        pTimerUpdate->Start(ALERTFEB_EB_POLL_RATE, kTRUE);
      }
    }
    return kTRUE;
	}

	void DrawPlots()
	{
    int offset = pComboDisplayedChannels->GetSelected();
		for(int i = 0; i < 4; i++)
		{
			pCanvasHisto->GetCanvas()->cd(i+1);
			pCanvasHisto->GetCanvas()->GetPad(i+1)->Clear();
      if(offset<13)      pTH_TDC_LE   [(offset- 0)*4+i]->Draw("bar0");
      else if(offset<26) pTH_TDC_Width[(offset-13)*4+i]->Draw("bar0");
      else if(offset<39) pTH_TDC_Ref  [(offset-26)*4+i]->Draw("bar0");
		}
  }

	void UpdatePlots()
	{
		pCanvasHisto->GetCanvas()->Modified();
		pCanvasHisto->GetCanvas()->Update();
	}

	void ProcessEvent()
  {
    float ref = 1.0E9;

    for(int i=0;i<52;i++)
    {
      for(list<tdc_hit_t>::iterator it = tdcTimes[i].begin(); it != tdcTimes[i].end(); it++)
      {
        // pick earlier hit time as reference
        ref = (it->t < ref) ? it->t : ref;
        pTH_TDC_Width[i]->Fill(it->width);
        pTH_TDC_LE[i]->Fill(it->t);
      }
    }

    if(ref>0)
    {
      for(int i=0;i<52;i++)
      for(list<tdc_hit_t>::iterator it = tdcTimes[i].begin(); it != tdcTimes[i].end(); it++)
          pTH_TDC_Ref[i]->Fill(1000.0*(ref-it->t));
    }

    for(int i=0;i<52;i++)
      tdcTimes[i].clear();
  }

	void ReadEb()
  {
    unsigned int buf[1000];
    int len = pSockEb->RecvRaw(buf, sizeof(buf), kDontBlock);
    if(len<=0) return;

    printf("%s: len=%d\n", __func__, len);
    for(int i=0;i<len/4;i++)
      printf("%08X ", buf[i]);
    printf("\n");

    static int tag = 0, idx = 0, ch = 0;
    static tdc_hit_t hit;
    for(int i=0;i<len/4;i++)
    {
      int val = buf[i];
      if(val & 0x80000000)
      {
        tag = (val>>27) & 0xF;
        idx = 0;
      }
      else
        idx++;

      switch(tag)
      {
        case 0:
        {
          printf("BLOCK HEADER\n");
          break;
        }

        case 1:
        {
          printf("BLOCK TRAILER\n");
          ProcessEvent();
          break;
        }

        case 2:
        {
          printf("EVENT HEADER: event#=%d\n", (val>>0) & 0xFFFFF);
          break;
        }

        case 3:
        {
          if(idx==0) printf("TIMESTAMP: timestamp=%06X", (val>>0) & 0xFFFFFF);
          if(idx==1) printf(",%06X\n", (val>>0) & 0xFFFFFF);
          break;
        }

        case 5:
        {
          if(idx == 0)
          {
            ch = (val>>21)&0x3f;
            hit.t = ((val>>0)&0x7ffff)*15.625/1000.0;
          }
          else if(idx == 1)
          {
            hit.width = ((val>>0)&0x3ffff)*15.625/1000.0;
            printf("TDC HIT: Ch=%2d, Time=%f, Width=%f\n", ch, hit.t, hit.width);

            if(ch<52)
              tdcTimes[ch].push_back(hit);
          }
          break;
        }
      }
    }
  }

	void ConnectEb()
  {
    if(!pSockEb)
    {
      petiroc_clk_sel(0);

      petiroc_cfg_pwr(1,1,1,1,0,1);

      petiroc_pulser(0x0, 0xFFFFFFFF, 3.0E0, 0.5, 1000, 100);
//      petiroc_pulser(1<<(TEST_CH-48), 1, 1.0E3, 0.5, 0, 180);

      petiroc_cfg_rst();

      petiroc_slow_control();
      petiroc_slow_control();

      petiroc_trig(0);
      petiroc_eb_setup(1,1300, 500, 1200);

      petiroc_soft_reset(1);
      petiroc_soft_reset(0);

      petiroc_adc_init(1);

      // non-latching mode
      petiroc_val_evt(1,0,0);
      petiroc_raz_chn(1);

      petiroc_tdc_calibrate(1, 1);
      gSystem->Sleep(1000);
      petiroc_tdc_calibrate(0, 1);

      petiroc_sync();
      //petiroc_trig(0);

      pBConnect->SetTitle("Disconnect");
      pSockEb = new TSocket("192.168.0.10", 6103);
      pSockEb->SetOption(kNoDelay, 1);
      pSockEb->SetOption(kNoBlock, 1);
      pTimerUpdate->Start(ALERTFEB_EB_POLL_RATE, kTRUE);
    }
    else
    {
      pTimerUpdate->Stop();
      pBConnect->SetTitle("Connect");
      pSockEb->Close();
      pSockEb = NULL;
    }
  }

  virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t)
  {
    switch(GET_MSG(msg))
    {
    case kC_USER:
      switch(GET_SUBMSG(msg))
      {
      }
      break;

    case kC_COMMAND:
      switch(GET_SUBMSG(msg))
      {
        case kCM_BUTTON:
          switch(parm1)
          {
            case BTN_ALERTFEB_CONNECT:
              ConnectEb();
              break;

            case BTN_ALERTFEB_RELOAD:
              petiroc_slow_control();
              petiroc_slow_control();
              break;

            case BTN_ALERTFEB_START:
            {
              petiroc_trig(11);
              break;
            }

            case BTN_CLEAR_HIST:
            {
              for(int i=0;i<52;i++)
              {
                pTH_TDC_LE   [i]->Reset();
                pTH_TDC_Width[i]->Reset();
                pTH_TDC_Ref  [i]->Reset();
              }
              break;
            }

            default:
              printf("button id %d pressed\n", (int)parm1);
              break;
          }
          break;

        case kCM_COMBOBOX:
          switch(parm1)
          {
            case COM_TDCDISPLAYCHANNELS:
              DrawPlots();
              UpdatePlots();
              break;
            default:
              printf("combo id %d pressed\n", (int)parm1);
              break;
          }
          break;
      }
      break;

    case kC_HSLIDER:
      switch(parm1)
      {
        case SDR_THRESHOLD:
        {
          TGString *pStr = new TGString;
          pStr->Form("DACThreshold (%dmV):", pSliderThreshold->GetPosition());
          pLabelThreshold->SetText(pStr);
          break;
        }
        default:
          printf("slider id %d pressed\n", (int)parm1);
          break;
      }
      break;
    }
    return kTRUE;
  }

  void petiroc_tdc_calibrate(int en_cal, int en_cor)
  {
    int val = 0;

    pM->WriteReg32(&pRegs->Tdc.NumEntriesMin, 100000);
    if(en_cal) val|= 0x6;
    if(en_cor) val|= 0x1;
    pM->WriteReg32(&pRegs->Tdc.Ctrl, val);
  }

  void petiroc_sync()
  {
    pM->WriteReg32(&pRegs->Sd.SyncSrc, 1);
    pM->WriteReg32(&pRegs->Sd.SyncSrc, 0);
  }

  void petiroc_trig(int src)
  {
    pM->WriteReg32(&pRegs->Sd.TrigSrc, src);
  }

  void petiroc_eb_setup(int blocksize, int lookback, int width, int delay)
  {
    pM->WriteReg32(&pRegs->Eb.Blocksize, blocksize);
    pM->WriteReg32(&pRegs->Eb.Lookback, lookback);
    pM->WriteReg32(&pRegs->Eb.WindowWidth, width);
    pM->WriteReg32(&pRegs->Eb.TrigDelay, delay);
  }

  void petiroc_soft_reset(int val)
  {
    int v = pM->ReadReg32(&pRegs->Clk.Ctrl);
    if(val) v |= 0x01;            /* assert soft reset */
    else    v &= 0xFFFFFFFE;     /* deassert soft reset */
    pM->WriteReg32(&pRegs->Clk.Ctrl, v);
  }

  void petiroc_clk_sel(int sel)
  {
    int v = pM->ReadReg32(&pRegs->Clk.Ctrl) & 0xFFFFFFF9;
    if(sel) v |= 0x2;
    pM->WriteReg32(&pRegs->Clk.Ctrl, v | 0x4);
    pM->WriteReg32(&pRegs->Clk.Ctrl, v);
  }

  void petiroc_cfg_pwr(int en_d, int en_a, int en_adc, int en_dac, int gain, int clk_en)
  {
    unsigned int val;

    val = pM->ReadReg32(&pRegs->PetirocCfg.Ctrl);
    val &= 0xFFFFFF0F;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
    gSystem->Sleep(100);
    if(en_d)    val |= 0x10;
    if(en_a)    val |= 0x20;
    if(en_dac)  val |= 0x40;
    if(en_adc)  val |= 0x80;
    if(!clk_en) val |= 0x100;
    if(gain)    val |= 0x200;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
    gSystem->Sleep(100);
  }

  void petiroc_pulser(int mask, int ncycles, float freq, float duty, int amp, int delay)
  {
    unsigned int period, lowcycles, ctrl = mask & 0xF;
    unsigned int dac_word, i, j;

    period = 33.333E6 / freq;
    lowcycles = period * duty;

    pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x480); // syncn rstn
    pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x080); // syncn
    pM->WriteReg32(&pRegs->Pulser.Delay, delay);

    for(i=0; i<4; i++)
    {
      dac_word = amp | (i<<17) | (1<<20);

      pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x480); // syncn rstn
      pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x400); //       rstn
      for(j=0; j<24; j++)
      {
        if(dac_word & 0x800000)
        {
          pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x700);
          pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x500);
        }
        else
        {
          pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x600);
          pM->WriteReg32(&pRegs->Pulser.Ctrl, ctrl | 0x400);
        }
        dac_word = dac_word<<1;
      }
pM->ReadReg32(&pRegs->Pulser.Ctrl);
    }
gSystem->Sleep(0.1);
    pM->WriteReg32(&pRegs->Pulser.Period, 33.333E6 / freq);
    pM->WriteReg32(&pRegs->Pulser.LowCycles, duty * 33.333E6 / freq);
    pM->WriteReg32(&pRegs->Pulser.NCycles, ncycles);
    pM->WriteReg32(&pRegs->Pulser.Start, 0);
    //pM->WriteReg32(&pRegs->Pulser.Status, );
  }

  void petiroc_start_conv(int sel)
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      rval = (rval & 0xFFFFF9FF) | (sel<<9);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval);
    }
  }

  void petiroc_cfg_rst()
  {
    int val;

    /* set rst_sc low */
    val = pM->ReadReg32(&pRegs->PetirocCfg.Ctrl);
    val &= 0xFFFFFFFE;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
    usleep(100);

    /* set rst_sc high */
    val |= 0x00000001;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
    usleep(100);
  }

  void petiroc_clken(int en)
  {
    for(int chip=0; chip<2; chip++)
    {
      int val = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);

      if(en)
        val |= 0x0000C000;
      else
        val &= 0xFFFF3FFF;

      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, val);
    }
  }

  void petiroc_slow_control()
  {
    PETIROC_Regs regs[2], result[2];

    petiroc_clken(1);

    for(int i=0;i<2;i++)
      petiroc_init_regs(i, regs);

    petiroc_cfg_select(1);

    petiroc_shift_regs(regs, result);

    petiroc_cfg_load();
  }

  void petiroc_cfg_load()
  {
    int val;

    val = pM->ReadReg32(&pRegs->PetirocCfg.Ctrl);

    /* set load high */
    val |= 0x00000008;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
    gSystem->Sleep(100);

    /* set load low */
    val &= 0xFFFFFFF7;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
    gSystem->Sleep(100);
  }

  void petiroc_shift_regs(PETIROC_Regs *regs, PETIROC_Regs *result)
  {
    int chip,i, val;

    for(chip=0;chip<2;chip++)
    {
      regs[chip].SlowControl.vth_discri_charge = bit_flip(regs[chip].SlowControl.vth_discri_charge,10);
      regs[chip].SlowControl.vth_time = bit_flip(regs[chip].SlowControl.vth_time,10);
      regs[chip].SlowControl.Cf = bit_flip(regs[chip].SlowControl.Cf,4);
    }

    /* write settings to FPGA shift register */
    for(i = 0; i < 20; i++)
    {
  printf("W i=%2d: %08X %08X\n", i, regs[0].Data[i], regs[1].Data[i]);
      pM->WriteReg32(&pRegs->PetirocCfg.SerData0[i], regs[0].Data[i]);
      pM->WriteReg32(&pRegs->PetirocCfg.SerData1[i], regs[1].Data[i]);
pM->ReadReg32(&pRegs->PetirocCfg.SerData1[i]);
    }

    /* do shift register transfer */
    val = pM->ReadReg32(&pRegs->PetirocCfg.Ctrl);
    val |= 0x00000002;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);

    /* check for shift register transfer completion */
    for(i = 10; i > 0; i--)
    {
      val = pM->ReadReg32(&pRegs->PetirocCfg.Status);
      if(!(val & 0x00000001))
        break;

      if(!i)
        printf("Error in %s: timeout on serial transfer...\n", __FUNCTION__);

      gSystem->Sleep(100);
    }

    /* read back settings from FPGA shift register */
    for(i = 0; i < 20; i++)
    {
      result[0].Data[i] = pM->ReadReg32(&pRegs->PetirocCfg.SerData0[i]);
      result[1].Data[i] = pM->ReadReg32(&pRegs->PetirocCfg.SerData1[i]);
  printf("R i=%2d: %08X %08X\n", i, regs[0].Data[i], regs[1].Data[i]);
    }

    for(chip=0;chip<2;chip++)
    {
      result[chip].SlowControl.vth_discri_charge = bit_flip(result[chip].SlowControl.vth_discri_charge,10);
      result[chip].SlowControl.vth_time = bit_flip(result[chip].SlowControl.vth_time,10);
      result[chip].SlowControl.Cf = bit_flip(result[chip].SlowControl.Cf,4);
    }
  }

  void petiroc_cfg_select(int sel)
  {
    int val;

    val = pM->ReadReg32(&pRegs->PetirocCfg.Ctrl);

    if(sel)
      val |= 0x00000004;
    else
      val &= 0xFFFFFFFB;
    pM->WriteReg32(&pRegs->PetirocCfg.Ctrl, val);
  }

  void petiroc_adc_init(int opt)
  {
    if(opt==0)
    {
      petiroc_startb_adc(1);
      petiroc_raz_chn(0);
      petiroc_val_evt(0, 0, 0);
      petiroc_enable(0);
      petiroc_hold_ext(0);

  //    petiroc_soft_reset(1);
  //    petiroc_soft_reset(0);
      petiroc_raz_chn(1);
  //    petiroc_raz_chn(0);
  //petiroc_raz_chn(2);
    }
    else
    {
      petiroc_enable(1);
      usleep(1000);
      petiroc_val_evt(2, 0, 10);
      petiroc_start_conv(2);
    }
  }

  void petiroc_startb_adc(int val)
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      rval = (rval & 0xFFFFFFFD) | (val<<1);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval);
    }
  }

  void petiroc_trig_ext()
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval | 0x8);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval);
    }
  }

  void petiroc_hold_ext(int val)
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      if(val)
        pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval | 0x4);
      else
        pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval & 0xFFFFFFFB);
    }
  }

  void petiroc_enable(int enable)
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      rval = (rval & 0xFFFFFFFE) | (enable<<0);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval);
    }
  }

  void petiroc_val_evt(int sel, int en_dly, int dis_dly)
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      rval = (rval & 0x0000FFCF) | (sel<<4) | (en_dly<<24) | (dis_dly<<16);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval);
    }
  }

  void petiroc_raz_chn(int sel)
  {
    for(int chip=0; chip<2; chip++)
    {
      unsigned int rval = pM->ReadReg32(&pRegs->PetirocAdc[chip].Ctrl);
      rval = (rval & 0xFFFFFF3F) | (sel<<6);
      pM->WriteReg32(&pRegs->PetirocAdc[chip].Ctrl, rval);
    }
  }

  unsigned int bit_flip(unsigned int val, unsigned int len)
  {
    unsigned int result = 0;
    for(int i=0;i<len;i++)
    {
      if(val & (1<<i))
      result |= 1<<(len-1-i);
    }
    return result;
  }

  void petiroc_init_regs(int chip, PETIROC_Regs *regs)
  {
    static int dac = 0;
    int i, lp_en = 0;

    unsigned int PETIROC_CH_MASK[2] = {0x00000000, 0x00000000};
//    unsigned int PETIROC_THR[2] = {325, 325};
    unsigned int PETIROC_THR[2] = {425, 425};
    unsigned int PETIROC_THR_Q[2] = {600, 600};
    unsigned int PETIROC_HOLD_DELAY = 100;

    memset(&regs[chip], 0, sizeof(PETIROC_Regs));

  //  regs[chip].SlowControl.mask_discri_charge = 0;
  //  regs[chip].SlowControl.mask_discri_charge = 0xFFFFFFFF;
    regs[chip].SlowControl.mask_discri_charge = PETIROC_CH_MASK[chip];

    regs[chip].SlowControl.inputDAC_ch0     = dac;
    regs[chip].SlowControl.inputDAC_ch0_en  = 1;
    regs[chip].SlowControl.inputDAC_ch1     = dac;
    regs[chip].SlowControl.inputDAC_ch1_en  = 1;
    regs[chip].SlowControl.inputDAC_ch2     = dac;
    regs[chip].SlowControl.inputDAC_ch2_en  = 1;
    regs[chip].SlowControl.inputDAC_ch3     = dac;
    regs[chip].SlowControl.inputDAC_ch3_en  = 1;
    regs[chip].SlowControl.inputDAC_ch4     = dac;
    regs[chip].SlowControl.inputDAC_ch4_en  = 1;
    regs[chip].SlowControl.inputDAC_ch5     = dac;
    regs[chip].SlowControl.inputDAC_ch5_en  = 1;
    regs[chip].SlowControl.inputDAC_ch6     = dac;
    regs[chip].SlowControl.inputDAC_ch6_en  = 1;
    regs[chip].SlowControl.inputDAC_ch7     = dac;
    regs[chip].SlowControl.inputDAC_ch7_en  = 1;
    regs[chip].SlowControl.inputDAC_ch8     = dac;
    regs[chip].SlowControl.inputDAC_ch8_en  = 1;
    regs[chip].SlowControl.inputDAC_ch9     = dac;
    regs[chip].SlowControl.inputDAC_ch9_en  = 1;
    regs[chip].SlowControl.inputDAC_ch10    = dac;
    regs[chip].SlowControl.inputDAC_ch10_en = 1;
    regs[chip].SlowControl.inputDAC_ch11    = dac;
    regs[chip].SlowControl.inputDAC_ch11_en = 1;
    regs[chip].SlowControl.inputDAC_ch12    = dac;
    regs[chip].SlowControl.inputDAC_ch12_en = 1;
    regs[chip].SlowControl.inputDAC_ch13    = dac;
    regs[chip].SlowControl.inputDAC_ch13_en = 1;
    regs[chip].SlowControl.inputDAC_ch14    = dac;
    regs[chip].SlowControl.inputDAC_ch14_en = 1;
    regs[chip].SlowControl.inputDAC_ch15    = dac;
    regs[chip].SlowControl.inputDAC_ch15_en = 1;
    regs[chip].SlowControl.inputDAC_ch16    = dac;
    regs[chip].SlowControl.inputDAC_ch16_en = 1;
    regs[chip].SlowControl.inputDAC_ch17    = dac;
    regs[chip].SlowControl.inputDAC_ch17_en = 1;
    regs[chip].SlowControl.inputDAC_ch18    = dac;
    regs[chip].SlowControl.inputDAC_ch18_en = 1;
    regs[chip].SlowControl.inputDAC_ch19    = dac;
    regs[chip].SlowControl.inputDAC_ch19_en = 1;
    regs[chip].SlowControl.inputDAC_ch20    = dac;
    regs[chip].SlowControl.inputDAC_ch20_en = 1;
    regs[chip].SlowControl.inputDAC_ch21    = dac;
    regs[chip].SlowControl.inputDAC_ch21_en = 1;
    regs[chip].SlowControl.inputDAC_ch22    = dac;
    regs[chip].SlowControl.inputDAC_ch22_en = 1;
    regs[chip].SlowControl.inputDAC_ch23    = dac;
    regs[chip].SlowControl.inputDAC_ch23_en = 1;
    regs[chip].SlowControl.inputDAC_ch24    = dac;
    regs[chip].SlowControl.inputDAC_ch24_en = 1;
    regs[chip].SlowControl.inputDAC_ch25    = dac;
    regs[chip].SlowControl.inputDAC_ch25_en = 1;
    regs[chip].SlowControl.inputDAC_ch26    = dac;
    regs[chip].SlowControl.inputDAC_ch26_en = 1;
    regs[chip].SlowControl.inputDAC_ch27    = dac;
    regs[chip].SlowControl.inputDAC_ch27_en = 1;
    regs[chip].SlowControl.inputDAC_ch28    = dac;
    regs[chip].SlowControl.inputDAC_ch28_en = 1;
    regs[chip].SlowControl.inputDAC_ch29    = dac;
    regs[chip].SlowControl.inputDAC_ch29_en = 1;
    regs[chip].SlowControl.inputDAC_ch30    = dac;
    regs[chip].SlowControl.inputDAC_ch30_en = 1;
    regs[chip].SlowControl.inputDAC_ch31    = dac;
    regs[chip].SlowControl.inputDAC_ch31_en = 1;

    regs[chip].SlowControl.inputDACdummy = 0;
    regs[chip].SlowControl.mask_discri_time = PETIROC_CH_MASK[chip];

    regs[chip].SlowControl.DAC6b_ch0   = 0;
    regs[chip].SlowControl.DAC6b_ch1   = 0;
    regs[chip].SlowControl.DAC6b_ch2   = 0;
    regs[chip].SlowControl.DAC6b_ch3   = 0;
    regs[chip].SlowControl.DAC6b_ch4   = 0;
    regs[chip].SlowControl.DAC6b_ch5   = 0;
    regs[chip].SlowControl.DAC6b_ch6   = 0;
    regs[chip].SlowControl.DAC6b_ch7   = 0;
    regs[chip].SlowControl.DAC6b_ch8   = 0;
    regs[chip].SlowControl.DAC6b_ch9   = 0;
    regs[chip].SlowControl.DAC6b_ch10  = 0;
    regs[chip].SlowControl.DAC6b_ch11  = 0;
    regs[chip].SlowControl.DAC6b_ch12  = 0;
    regs[chip].SlowControl.DAC6b_ch13  = 0;
    regs[chip].SlowControl.DAC6b_ch14  = 0;
    regs[chip].SlowControl.DAC6b_ch15  = 0;
    regs[chip].SlowControl.DAC6b_ch16  = 0;
    regs[chip].SlowControl.DAC6b_ch17  = 0;
    regs[chip].SlowControl.DAC6b_ch18  = 0;
    regs[chip].SlowControl.DAC6b_ch19  = 0;
    regs[chip].SlowControl.DAC6b_ch20  = 0;
    regs[chip].SlowControl.DAC6b_ch21  = 0;
    regs[chip].SlowControl.DAC6b_ch22  = 0;
    regs[chip].SlowControl.DAC6b_ch23  = 0;
    regs[chip].SlowControl.DAC6b_ch24  = 0;
    regs[chip].SlowControl.DAC6b_ch25  = 0;
    regs[chip].SlowControl.DAC6b_ch26  = 0;
    regs[chip].SlowControl.DAC6b_ch27  = 0;
    regs[chip].SlowControl.DAC6b_ch28  = 0;
    regs[chip].SlowControl.DAC6b_ch29  = 0;
    regs[chip].SlowControl.DAC6b_ch30  = 0;
    regs[chip].SlowControl.DAC6b_ch31  = 0;

    regs[chip].SlowControl.EN_10b_DAC = 1;
    regs[chip].SlowControl.PP_10b_DAC = 0;
    regs[chip].SlowControl.vth_discri_charge = PETIROC_THR_Q[chip];
    regs[chip].SlowControl.vth_time = pSliderThreshold->GetPosition();//PETIROC_THR[chip];

    regs[chip].SlowControl.EN_ADC = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_ADC = 0;
    regs[chip].SlowControl.sel_startb_ramp_ADC_ext = 0;
    regs[chip].SlowControl.usebcompensation = 0;
    regs[chip].SlowControl.ENbiasDAC_delay = lp_en ? 0 : 1;
    regs[chip].SlowControl.PPbiasDAC_delay = 0;
    regs[chip].SlowControl.ENbiasramp_delay = lp_en ? 0 : 1;
    regs[chip].SlowControl.PPbiasramp_delay = 0;
    regs[chip].SlowControl.DACdelay = PETIROC_HOLD_DELAY;
    regs[chip].SlowControl.EN_discri_delay = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_discri_delay = 0;
    regs[chip].SlowControl.EN_temp_sensor = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_temp_sensor = 0;
    regs[chip].SlowControl.EN_bias_pa = 1;
    regs[chip].SlowControl.PP_bias_pa = 0;
    regs[chip].SlowControl.EN_bias_discri = 1;
    regs[chip].SlowControl.PP_bias_discri = 0;
  //  regs[chip].SlowControl.cmd_polarity = 1;
    regs[chip].SlowControl.cmd_polarity = 0;
    regs[chip].SlowControl.LatchDiscri = 0;
  //  regs[chip].SlowControl.LatchDiscri = 1;;
    regs[chip].SlowControl.EN_bias_6b_DAC = 1;
    regs[chip].SlowControl.PP_bias_6b_DAC = 0;
    regs[chip].SlowControl.EN_bias_tdc = 1;
    regs[chip].SlowControl.PP_bias_tdc = 0;
    regs[chip].SlowControl.ON_input_DAC = 1;
    regs[chip].SlowControl.EN_bias_charge = 1;//lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_bias_charge = 0;
    regs[chip].SlowControl.Cf = 0;
  //  regs[chip].SlowControl.Cf = 0xf;
    regs[chip].SlowControl.EN_bias_sca = 1;
    regs[chip].SlowControl.PP_bias_sca = 0;
    regs[chip].SlowControl.EN_bias_discri_charge = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_bias_discri_charge = 0;
    regs[chip].SlowControl.EN_bias_discri_ADC_time = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_bias_discri_ADC_time = 0;
    regs[chip].SlowControl.EN_bias_discri_ADC_charge = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_bias_discri_ADC_charge = 0;
    regs[chip].SlowControl.DIS_razchn_int = 0;
    regs[chip].SlowControl.DIS_razchn_ext = 0;
    regs[chip].SlowControl.SEL_80M = lp_en ? 0 : 1;
    regs[chip].SlowControl.EN_80M = lp_en ? 0 : 1;
    regs[chip].SlowControl.EN_slow_lvds_rec = 1;//lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_slow_lvds_rec = 0;
    regs[chip].SlowControl.EN_fast_lvds_rec = 1;//lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_fast_lvds_rec = 0;
    regs[chip].SlowControl.EN_transmitter = lp_en ? 0 : 1;
    regs[chip].SlowControl.PP_transmitter = 0;
    regs[chip].SlowControl.ON_1mA = 1;
    regs[chip].SlowControl.ON_2mA = 1;
    regs[chip].SlowControl.NC = 0;
    regs[chip].SlowControl.ON_ota_mux = lp_en ? 0 : 1;
    regs[chip].SlowControl.ON_ota_probe = lp_en ? 0 : 1;
    regs[chip].SlowControl.DIS_trig_mux = 0;
    regs[chip].SlowControl.EN_NOR32_time = lp_en ? 0 : 1;
    regs[chip].SlowControl.EN_NOR32_charge = lp_en ? 0 : 1;
    regs[chip].SlowControl.DIS_triggers = 0;
    regs[chip].SlowControl.EN_dout_oc = lp_en ? 0 : 1;
    regs[chip].SlowControl.EN_transmit = lp_en ? 0 : 1;
  }

private:
  enum GUI_IDs
  {
    BTN_ALERTFEB_CONNECT,
    BTN_ALERTFEB_RELOAD,
    BTN_ALERTFEB_START,
    BTN_CLEAR_HIST,
    SDR_THRESHOLD,
    COM_TDCDISPLAYCHANNELS
  };
  
  ALERTFEB_Regs       *pRegs;

  ModuleFrame         *pM;

  TTimer              *pTimerUpdate;

  TGTextButton        *pBConnect;

  TSocket             *pSockEb;

  TGComboBox          *pComboDisplayedChannels;

  TRootEmbeddedCanvas *pCanvasHisto;

  TH1I                *pTH_TDC_LE[52];
  TH1I                *pTH_TDC_Width[52];
  TH1I                *pTH_TDC_Ref[52];

  TGLabel					    *pLabelThreshold;

	TGSlider					  *pSliderThreshold;

  list<tdc_hit_t>     tdcTimes[52];
};

#endif
