#ifndef fadc_H
#define fadc_H

/* Define CTRL1 Bits */
#define FA_REF_CLK_INTERNAL        0x0
#define FA_REF_CLK_FP              0x1
#define FA_REF_CLK_P0              0x2
#define FA_REF_CLK_MASK            0x3
#define FA_ENABLE_INTERNAL_CLK     0x8

typedef struct
{
/* 0x0000 */ volatile unsigned int version;
/* 0x0004 */ volatile unsigned int csr;
/* 0x0008 */ volatile unsigned int ctrl1;
/* 0x000C */ volatile unsigned int ctrl2;
/* 0x0010 */ volatile unsigned int blk_level;
/* 0x0014 */ volatile unsigned int intr;
/* 0x0018 */ volatile unsigned int adr32;
/* 0x001C */ volatile unsigned int adr_mb;
/* 0x0020 */ volatile unsigned int s_adr;
/* 0x0024 */ volatile unsigned int delay;
/* 0x0028 */ volatile unsigned int itrig_cfg;
/* 0x002C */ volatile unsigned int reset;
/* 0x0030 */ volatile unsigned int trig_scal;
/* 0x0034 */ volatile unsigned int ev_count;
/* 0x0038 */ volatile unsigned int blk_count;
/* 0x003C */ volatile unsigned int blk_fifo_count;
/* 0x0040 */ volatile unsigned int blk_wrdcnt_fifo;
/* 0x0044 */ volatile unsigned int internal_trig_scal;
/* 0x0048 */ volatile unsigned int ram_word_count;
/* 0x004C */ volatile unsigned int dataflow_status;
/* 0x0050 */ volatile unsigned int dac[8];
/* 0x0070 */ volatile unsigned int status[4];
/* 0x0080 */ volatile unsigned int aux[2];
/* 0x0088 */ volatile unsigned int trig21_delay;
/* 0x008C */ volatile unsigned int mem_adr;
/* 0x0090 */ volatile unsigned int mem1_data;
/* 0x0094 */ volatile unsigned int mem2_data;
/* 0x0098 */ volatile unsigned int prom_reg1;
/* 0x009C */ volatile unsigned int prom_reg2;
/* 0x00A0 */ volatile unsigned int berr_module_scal;
/* 0x00A4 */ volatile unsigned int berr_crate_scal;
/* 0x00A8 */ volatile unsigned int proc_words_scal;
/* 0x00AC */ volatile unsigned int aux_scal2;
/* 0x00B0 */ volatile unsigned int header_scal;
/* 0x00B4 */ volatile unsigned int trig2_scal;
/* 0x00B8 */ volatile unsigned int trailer_scal;
/* 0x00BC */ volatile unsigned int syncreset_scal;
/* 0x00C0 */ volatile unsigned int busy_level;
/* 0x00C4 */ volatile unsigned int gen_evt_header;
/* 0x00C8 */ volatile unsigned int gen_evt_data;
/* 0x00CC */ volatile unsigned int gen_evt_trailer;
/* 0x00D0 */ volatile unsigned int mgt_status;
/* 0x00D4 */ volatile unsigned int mgt_ctrl;
/* 0x00D8 */ volatile unsigned int reserved_ctrl[2];
/* 0x00E0 */ volatile unsigned int scaler_ctrl;
/* 0x00E4 */ volatile unsigned int serial_number[3];
/* 0x00F0 */ volatile unsigned int scaler_interval;
/* 0x00F4 */ volatile unsigned int spare_ctrl[(0x100-0xF4)>>2];

/* 0x0100 */ volatile unsigned int adc_status[3];
/* 0x010C */ volatile unsigned int adc_config[4];
/* 0x011C */ volatile unsigned int adc_ptw;
/* 0x0120 */ volatile unsigned int adc_pl;
/* 0x0124 */ volatile unsigned int adc_nsb;
/* 0x0128 */ volatile unsigned int adc_nsa;
/* 0x012C */ volatile unsigned int adc_thres[8];
/* 0x014C */ volatile unsigned int ptw_last_adr;
/* 0x0150 */ volatile unsigned int ptw_max_buf;
/* 0x0154 */ volatile unsigned int adc_test_data;
/* 0x0158 */ volatile unsigned int adc_pedestal[16];
/* 0x0198 */ volatile unsigned int adc_gain[16];
/* 0x01D8 */ volatile unsigned int spare_adc[(0x200-0x1D8)>>2];

/* 0x0200 */ volatile unsigned int hitsum_status;
/* 0x0204 */ volatile unsigned int hitsum_cfg;
/* 0x0208 */ volatile unsigned int hitsum_hit_width;
/* 0x020C */ volatile unsigned int hitsum_trig_delay;
/* 0x0210 */ volatile unsigned int hitsum_trig_width;
/* 0x0214 */ volatile unsigned int hitsum_window_bits;
/* 0x0218 */ volatile unsigned int hitsum_window_width;
/* 0x021C */ volatile unsigned int hitsum_coin_bits;
/* 0x0220 */ volatile unsigned int hitsum_pattern;
/* 0x0224 */ volatile unsigned int hitsum_fifo;
/* 0x0228 */ volatile unsigned int hitsum_sum_thresh;
/* 0x022C */ volatile unsigned int spare_hitsum[(0x300-0x22C)>>2];

/* 0x0300 */ volatile unsigned int scaler[16];
/* 0x0340 */ volatile unsigned int time_count;
/* 0x0344 */ volatile unsigned int spare_scaler[(0x400-0x344)>>2];

/* 0x0400 */ volatile unsigned int testBit;
/* 0x0404 */ volatile unsigned int clock250count;
/* 0x0408 */ volatile unsigned int syncp0count;
/* 0x040C */ volatile unsigned int trig1p0count;
/* 0x0410 */ volatile unsigned int trig2p0count;
/* 0x0414 */ volatile unsigned int spare_count[(0x500-0x414)>>2];

/* 0x0500 */ volatile unsigned int gtx_ctrl;
/* 0x0504 */ volatile unsigned int gtx_ctrl_tile;
/* 0x0508 */ volatile unsigned int gtx_status;
/* 0x050C */ volatile unsigned int gtx_drp_ctrl;
/* 0x0510 */ volatile unsigned int gtx_drp_status;
/* 0x0514 */ volatile unsigned int gtx_softerr;
/* 0x0518 */ volatile unsigned int gtx_la_ctrl;
/* 0x051C */ volatile unsigned int gtx_la_status;
/* 0x0520 */ volatile unsigned int gtx_la_data[2];
/* 0x0528 */ volatile unsigned int gtx_la_mode;
/* 0x052C */ volatile unsigned int gtx_la_thr;
/* 0x0530 */ volatile unsigned int gtx_la_en[2];
/* 0x0538 */ volatile unsigned int gtx_la_val[2];
/* 0x0540 */ volatile unsigned int spare_gtx[(0x580-0x540)>>2];
/* 0x0580 */ volatile unsigned int hist_ctrl;
/* 0x0584 */ volatile unsigned int hist_time;
/* 0x0588 */ volatile unsigned int hist_data[16];
} fadc_struct;

#endif
