#ifndef ALERTFEB_EB_QCAL_H
#define ALERTFEB_EB_QCAL_H

#include <stdlib.h>
#include <list>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_Regs.h"

using namespace std;

#define ALERTFEB_QCAL_THR_START  400
#define ALERTFEB_QCAL_THR_STEP   100
#define ALERTFEB_QCAL_THR_NUM    1

#define ALERTFEB_QCAL_DAC_START  0
#define ALERTFEB_QCAL_DAC_STEP   500
#define ALERTFEB_QCAL_DAC_NUM    130

#define ALERTFEB_QCAL_EB_POLL_RATE    20

static bool alert_eb_qcal_compare_tdc_hit(const tdc_hit_t &a, const tdc_hit_t &b)
{
  return (a.t < b.t);
}

class ALERTFEB_EB_QCAL  : public TGCompositeFrame
{
public:
  ALERTFEB_EB_QCAL(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
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

      pTF1->AddFrame(pTF2 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX | kLHintsTop));
        pTF2->AddFrame(pLabelThreshold = new TGLabel(pTF2, new TGString(Form("DACThreshold (%d):", 325))), new TGLayoutHints(kLHintsCenterY | kLHintsLeft));
        pTF2->AddFrame(pSliderThreshold = new TGHSlider(pTF2, 100, kSlider1 | kScaleBoth, SDR_THRESHOLD), new TGLayoutHints(kLHintsExpandX | kLHintsCenterY | kLHintsLeft));
          pSliderThreshold->SetRange(0, 1023);
  //				pSliderUpdateTime->SetEnabled(kFALSE);
          pSliderThreshold->SetPosition(325);
          pSliderThreshold->Associate(this);

    AddFrame(pCanvasHisto = new TRootEmbeddedCanvas("TDC Plots", this), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
			pCanvasHisto->GetCanvas()->SetBorderMode(0);
      pCanvasHisto->GetCanvas()->Divide(2, 4);
      for(int i=0;i<4;i++)
      for(int j=0;j<ALERTFEB_QCAL_THR_NUM;j++)
      {
        pTH_TDC_Charge_Width[i][j] = new TH2I(Form("Ch%d_QvsW",48+i), Form("Ch%d;Charge(pC);Width(ns)",48+i), 1000, 0.0, (i<2) ? 250.0 : 25.0, 1000, 0.0, (i<2) ? 1600.0 : 100.0);
        pTH_TDC_Charge_Width[i][j]->SetMarkerColor(1+j);
        pTH_TDC_Charge_Width[i][j]->SetStats(kFALSE);

        pTH_TDC_Charge_LE[i][j] = new TH2I(Form("Ch%d_QvsLE",48+i), Form("Ch%d;Charge(pC);LeadingEdge(ns)",48+i), 1000, 0.0, (i<2) ? 250.0 : 25.0, 1000, 100.0, 200.0);
        pTH_TDC_Charge_LE[i][j]->SetMarkerColor(1+j);
        pTH_TDC_Charge_LE[i][j]->SetStats(kFALSE);
      }

    DrawPlots();
		UpdatePlots();

    pTimerUpdate = new TTimer(this, ALERTFEB_QCAL_EB_POLL_RATE, kTRUE);
  }

	virtual Bool_t HandleTimer(TTimer *t)
	{
		if(pTimerUpdate->HasTimedOut())
    {
      if(pSockEb)
      {
        ReadEb();
        pTimerUpdate->Start(ALERTFEB_QCAL_EB_POLL_RATE, kTRUE);
      }
    }
    return kTRUE;
	}

	void DrawPlots()
	{
		for(int i = 0; i < 4; i++)
		{
			pCanvasHisto->GetCanvas()->cd(i+1);
			pCanvasHisto->GetCanvas()->GetPad(i+1)->Clear();
      for(int j=0;j<ALERTFEB_QCAL_THR_NUM;j++)
        pTH_TDC_Charge_Width[i][j]->Draw(j ? "same" : "");

			pCanvasHisto->GetCanvas()->cd(i+5);
			pCanvasHisto->GetCanvas()->GetPad(i+5)->Clear();
      for(int j=0;j<ALERTFEB_QCAL_THR_NUM;j++)
        pTH_TDC_Charge_LE[i][j]->Draw(j ? "same" : "");
		}
  }

	void UpdatePlots()
	{
		pCanvasHisto->GetCanvas()->Modified();
		pCanvasHisto->GetCanvas()->Update();
	}

	void ProcessEvent()
  {
    if(Channel>=52 || Channel<0) return;

    for(int i=0;i<52;i++)
      tdcTimes[i].sort(alert_eb_qcal_compare_tdc_hit);
    // process hits
    printf("Sorted time hits:\n");
    for(list<tdc_hit_t>::iterator it = tdcTimes[Channel].begin(); it != tdcTimes[Channel].end(); it++)
      printf("ch%d: hit.t=%f, hit.width=%f\n", Channel, it->t, it->width);

    tdc_hit_t max_width = {-1.0, -1.0};
    printf("Sorted time hits with width:\n");
    for(list<tdc_hit_t>::iterator it = tdcTimes[Channel].begin(); it != tdcTimes[Channel].end(); it++)
    {
      if(it->width > max_width.width)
        max_width = *it;
    }

    if(max_width.width > 0.0)
    {
      pTH_TDC_Charge_Width[Channel-48][ThresholdIndex]->Fill(Charge_pC[Channel-48], max_width.width);
      pTH_TDC_Charge_LE[Channel-48][ThresholdIndex]->Fill(Charge_pC[Channel-48], max_width.t);
    }

    for(int i=0;i<52;i++)
      tdcTimes[i].clear();

    if(++DACIndex>=ALERTFEB_QCAL_DAC_NUM)
    {
      DACIndex = 0;

      if(++ThresholdIndex>=ALERTFEB_QCAL_THR_NUM)
      {
        DrawPlots();
        UpdatePlots();

        Threshold = ALERTFEB_QCAL_THR_START;
        ThresholdIndex = 0;

//        if(Channel<52)
//          Channel++;
      }
      else
        Threshold+= ALERTFEB_QCAL_THR_STEP;

//      petiroc_slow_control();
//      petiroc_slow_control();
    }

    int DAC = DACIndex*ALERTFEB_QCAL_DAC_STEP;

//    if(Channel<52)
    {
      Charge_pC[0] = Charge_pC[1] = 250.0 * DAC / 65536.0;
      Charge_pC[2] = Charge_pC[3] = 25.0 * DAC / 65536.0;
      printf("DAC=%d Charge_pC=%f,%f,%f,%f\n", DAC, Charge_pC[0], Charge_pC[1], Charge_pC[2], Charge_pC[3]);
      petiroc_pulser(1<<(Channel-48), 1, 1.0E3, 0.5, DAC, 180);
    }
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

    static int tag = 0, idx = 0, event = 0, ch;
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
          event = 0;
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
          if(event++)
            ProcessEvent();
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
            hit.width = ((val>>0)&0xffff)*15.625/1000.0;
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

      int gain = 0;
      petiroc_cfg_pwr(1,1,1,1,gain,1);

//      petiroc_pulser(0xF, 0xFFFFFFFF, 3.0E0, 0.5, 1000, 100);
      petiroc_pulser(0, 1, 1.0E3, 0.5, 0, 180);

      petiroc_cfg_rst();

      petiroc_slow_control();
      petiroc_slow_control();

      petiroc_trig(0);
      petiroc_eb_setup(1, 200, 200);

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
      pTimerUpdate->Start(ALERTFEB_QCAL_EB_POLL_RATE, kTRUE);
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
              petiroc_trig(12);
              Channel = 48;
              DACIndex = 0;
              int DAC = DACIndex*ALERTFEB_QCAL_DAC_STEP;
              Threshold = ALERTFEB_QCAL_THR_START;
              ThresholdIndex = 0;
              petiroc_slow_control();
              petiroc_slow_control();
              Charge_pC[0] = Charge_pC[1] = 250.0 * DAC / 65536.0;
              Charge_pC[2] = Charge_pC[3] = 25.0 * DAC / 65536.0;
              petiroc_pulser(1<<(Channel-48), 1, 1.0E3, 0.5, DAC, 180);

              // Good
              //petiroc_probe(1,0,0,0); // time amp, ch0
              //petiroc_probe(1,1,0,0); // vth discri, ch0
              //petiroc_probe(1,2,0,0); // time amp, ch1
              //petiroc_probe(1,3,0,0); // vth discri, ch1
              //petiroc_probe(1,4,0,4); // time amp, ch2
              //petiroc_probe(1,5,0,0); // vth discri, ch2
              petiroc_probe(1,12,0,4); // time amp, ch6
              //petiroc_probe(1,13,0,0); // vth discri, ch6

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

  void petiroc_eb_setup(int blocksize, int lookback, int width)
  {
    pM->WriteReg32(&pRegs->Eb.Blocksize, blocksize);
    pM->WriteReg32(&pRegs->Eb.Lookback, lookback);
    pM->WriteReg32(&pRegs->Eb.WindowWidth, width);
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

  void petiroc_probe(int ana, int ana_bit, int dig, int dig_bit)
  {
    PETIROC_Regs regs[2], result[2];

    memset(&regs, 0, sizeof(regs));

    for(int i=0; i<2; i++)
    {
      if(ana == 0) regs[i].Probes.out_inpDAC_probe  = (1<<ana_bit);
      if(ana == 1) regs[i].Probes.out_vth_discri    = (1<<ana_bit);
      if(ana == 2) regs[i].Probes.out_time          = (1<<ana_bit);
      if(ana == 3) regs[i].Probes.out_time_dummy    = (1<<ana_bit);
      if(ana == 4) regs[i].Probes.out_ramp_tdc      = (1<<ana_bit);

      if(dig == 0) regs[i].Probes.out_discri_charge = (1<<dig_bit);
      if(dig == 1) regs[i].Probes.out_charge        = (1<<dig_bit);
      if(dig == 2) regs[i].Probes.startRampbADC_int = (1<<dig_bit);
      if(dig == 3) regs[i].Probes.holdb             = (1<<dig_bit);
    }

    petiroc_cfg_select(0);

    petiroc_shift_regs(regs, result);
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
    regs[chip].SlowControl.vth_time = Threshold;//pSliderThreshold->GetPosition();//PETIROC_THR[chip];

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

  TH2I                *pTH_TDC_Charge_Width[4][ALERTFEB_QCAL_THR_NUM];
  TH2I                *pTH_TDC_Charge_LE[4][ALERTFEB_QCAL_THR_NUM];

  TGLabel					    *pLabelThreshold;

	TGSlider					  *pSliderThreshold;

  list<tdc_hit_t>     tdcTimes[52];

  float               Charge_pC[4];
  int                 DACIndex;
  int                 Threshold;
  int                 ThresholdIndex;
  int                 Channel;
};

#endif
