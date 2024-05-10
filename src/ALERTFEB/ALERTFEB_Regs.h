#ifndef ALERTFEB_REGS_H
#define ALERTFEB_REGS_H

#pragma pack(push,4)
typedef struct
{
  union
  {
    unsigned int Data[20];

    struct
    {
      // Analog probe
      unsigned int out_inpDAC_probe           : 32;
      unsigned int out_vth_discri             : 32;
      unsigned int out_time                   : 32;
      unsigned int out_time_dummy             : 1;
      unsigned int out_ramp_tdc               : 32;
      // Digital probe
      unsigned int out_discri_charge          : 32;
      unsigned int out_charge                 : 32;
      unsigned int startRampbADC_int          : 1;
      unsigned int holdb                      : 1;
    } Probes;

    struct
    {
      unsigned int mask_discri_charge         : 32;
      unsigned int inputDAC_ch0               : 8;
      unsigned int inputDAC_ch0_en            : 1;
      unsigned int inputDAC_ch1               : 8;
      unsigned int inputDAC_ch1_en            : 1;
      unsigned int inputDAC_ch2               : 8;
      unsigned int inputDAC_ch2_en            : 1;
      unsigned int inputDAC_ch3               : 8;
      unsigned int inputDAC_ch3_en            : 1;
      unsigned int inputDAC_ch4               : 8;
      unsigned int inputDAC_ch4_en            : 1;
      unsigned int inputDAC_ch5               : 8;
      unsigned int inputDAC_ch5_en            : 1;
      unsigned int inputDAC_ch6               : 8;
      unsigned int inputDAC_ch6_en            : 1;
      unsigned int inputDAC_ch7               : 8;
      unsigned int inputDAC_ch7_en            : 1;
      unsigned int inputDAC_ch8               : 8;
      unsigned int inputDAC_ch8_en            : 1;
      unsigned int inputDAC_ch9               : 8;
      unsigned int inputDAC_ch9_en            : 1;
      unsigned int inputDAC_ch10              : 8;
      unsigned int inputDAC_ch10_en           : 1;
      unsigned int inputDAC_ch11              : 8;
      unsigned int inputDAC_ch11_en           : 1;
      unsigned int inputDAC_ch12              : 8;
      unsigned int inputDAC_ch12_en           : 1;
      unsigned int inputDAC_ch13              : 8;
      unsigned int inputDAC_ch13_en           : 1;
      unsigned int inputDAC_ch14              : 8;
      unsigned int inputDAC_ch14_en           : 1;
      unsigned int inputDAC_ch15              : 8;
      unsigned int inputDAC_ch15_en           : 1;
      unsigned int inputDAC_ch16              : 8;
      unsigned int inputDAC_ch16_en           : 1;
      unsigned int inputDAC_ch17              : 8;
      unsigned int inputDAC_ch17_en           : 1;
      unsigned int inputDAC_ch18              : 8;
      unsigned int inputDAC_ch18_en           : 1;
      unsigned int inputDAC_ch19              : 8;
      unsigned int inputDAC_ch19_en           : 1;
      unsigned int inputDAC_ch20              : 8;
      unsigned int inputDAC_ch20_en           : 1;
      unsigned int inputDAC_ch21              : 8;
      unsigned int inputDAC_ch21_en           : 1;
      unsigned int inputDAC_ch22              : 8;
      unsigned int inputDAC_ch22_en           : 1;
      unsigned int inputDAC_ch23              : 8;
      unsigned int inputDAC_ch23_en           : 1;
      unsigned int inputDAC_ch24              : 8;
      unsigned int inputDAC_ch24_en           : 1;
      unsigned int inputDAC_ch25              : 8;
      unsigned int inputDAC_ch25_en           : 1;
      unsigned int inputDAC_ch26              : 8;
      unsigned int inputDAC_ch26_en           : 1;
      unsigned int inputDAC_ch27              : 8;
      unsigned int inputDAC_ch27_en           : 1;
      unsigned int inputDAC_ch28              : 8;
      unsigned int inputDAC_ch28_en           : 1;
      unsigned int inputDAC_ch29              : 8;
      unsigned int inputDAC_ch29_en           : 1;
      unsigned int inputDAC_ch30              : 8;
      unsigned int inputDAC_ch30_en           : 1;
      unsigned int inputDAC_ch31              : 8;
      unsigned int inputDAC_ch31_en           : 1;
      unsigned int inputDACdummy              : 8;
      unsigned int mask_discri_time           : 32;
      unsigned int DAC6b_ch0                  : 6;
      unsigned int DAC6b_ch1                  : 6;
      unsigned int DAC6b_ch2                  : 6;
      unsigned int DAC6b_ch3                  : 6;
      unsigned int DAC6b_ch4                  : 6;
      unsigned int DAC6b_ch5                  : 6;
      unsigned int DAC6b_ch6                  : 6;
      unsigned int DAC6b_ch7                  : 6;
      unsigned int DAC6b_ch8                  : 6;
      unsigned int DAC6b_ch9                  : 6;
      unsigned int DAC6b_ch10                 : 6;
      unsigned int DAC6b_ch11                 : 6;
      unsigned int DAC6b_ch12                 : 6;
      unsigned int DAC6b_ch13                 : 6;
      unsigned int DAC6b_ch14                 : 6;
      unsigned int DAC6b_ch15                 : 6;
      unsigned int DAC6b_ch16                 : 6;
      unsigned int DAC6b_ch17                 : 6;
      unsigned int DAC6b_ch18                 : 6;
      unsigned int DAC6b_ch19                 : 6;
      unsigned int DAC6b_ch20                 : 6;
      unsigned int DAC6b_ch21                 : 6;
      unsigned int DAC6b_ch22                 : 6;
      unsigned int DAC6b_ch23                 : 6;
      unsigned int DAC6b_ch24                 : 6;
      unsigned int DAC6b_ch25                 : 6;
      unsigned int DAC6b_ch26                 : 6;
      unsigned int DAC6b_ch27                 : 6;
      unsigned int DAC6b_ch28                 : 6;
      unsigned int DAC6b_ch29                 : 6;
      unsigned int DAC6b_ch30                 : 6;
      unsigned int DAC6b_ch31                 : 6;
      unsigned int EN_10b_DAC                 : 1;
      unsigned int PP_10b_DAC                 : 1;
      unsigned int vth_discri_charge          : 10; // note: bit reversal required
      unsigned int vth_time                   : 10; // note: bit reversal required
      unsigned int EN_ADC                     : 1;
      unsigned int PP_ADC                     : 1;
      unsigned int sel_startb_ramp_ADC_ext    : 1;
      unsigned int usebcompensation           : 1;
      unsigned int ENbiasDAC_delay            : 1;
      unsigned int PPbiasDAC_delay            : 1;
      unsigned int ENbiasramp_delay           : 1;
      unsigned int PPbiasramp_delay           : 1;
      unsigned int DACdelay                   : 8;
      unsigned int EN_discri_delay            : 1;
      unsigned int PP_discri_delay            : 1;
      unsigned int EN_temp_sensor             : 1;
      unsigned int PP_temp_sensor             : 1;
      unsigned int EN_bias_pa                 : 1;
      unsigned int PP_bias_pa                 : 1;
      unsigned int EN_bias_discri             : 1;
      unsigned int PP_bias_discri             : 1;
      unsigned int cmd_polarity               : 1;
      unsigned int LatchDiscri                : 1;
      unsigned int EN_bias_6b_DAC             : 1;
      unsigned int PP_bias_6b_DAC             : 1;
      unsigned int EN_bias_tdc                : 1;
      unsigned int PP_bias_tdc                : 1;
      unsigned int ON_input_DAC               : 1;
      unsigned int EN_bias_charge             : 1;
      unsigned int PP_bias_charge             : 1;
      unsigned int Cf                         : 4;  // note: bit reversal required
      unsigned int EN_bias_sca                : 1;
      unsigned int PP_bias_sca                : 1;
      unsigned int EN_bias_discri_charge      : 1;
      unsigned int PP_bias_discri_charge      : 1;
      unsigned int EN_bias_discri_ADC_time    : 1;
      unsigned int PP_bias_discri_ADC_time    : 1;
      unsigned int EN_bias_discri_ADC_charge  : 1;
      unsigned int PP_bias_discri_ADC_charge  : 1;
      unsigned int DIS_razchn_int             : 1;
      unsigned int DIS_razchn_ext             : 1;
      unsigned int SEL_80M                    : 1;
      unsigned int EN_80M                     : 1;
      unsigned int EN_slow_lvds_rec           : 1;
      unsigned int PP_slow_lvds_rec           : 1;
      unsigned int EN_fast_lvds_rec           : 1;
      unsigned int PP_fast_lvds_rec           : 1;
      unsigned int EN_transmitter             : 1;
      unsigned int PP_transmitter             : 1;
      unsigned int ON_1mA                     : 1;
      unsigned int ON_2mA                     : 1;
      unsigned int NC                         : 1;
      unsigned int ON_ota_mux                 : 1;
      unsigned int ON_ota_probe               : 1;
      unsigned int DIS_trig_mux               : 1;
      unsigned int EN_NOR32_time              : 1;
      unsigned int EN_NOR32_charge            : 1;
      unsigned int DIS_triggers               : 1;
      unsigned int EN_dout_oc                 : 1;
      unsigned int EN_transmit                : 1;
    } SlowControl;
  };
} PETIROC_Regs;
#pragma pack(pop)

typedef struct
{
/* 0x0000-0x0003 */ unsigned int    Ctrl;
/* 0x0004-0x0007 */ unsigned int    Reserved0[(0x0008-0x0004)/4];
/* 0x0008-0x000B */ unsigned int    SpiCtrl;
/* 0x000C-0x000F */ unsigned int    SpiStatus;
/* 0x0010-0x0013 */ unsigned int    BoardId;
/* 0x0014-0x00FF */ unsigned int    Reserved1[(0x0100-0x0014)/4];
} CLK_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int    Ctrl;
/* 0x0004-0x0007 */ unsigned int    Status;
/* 0x0008-0x000F */ unsigned int    Reserved0[(0x0010-0x0008)/4];
/* 0x0010-0x005F */ unsigned int    SerData0[20];
/* 0x0060-0x00AF */ unsigned int    SerData1[20];
/* 0x00B0-0x00FF */ unsigned int    Reserved1[(0x0100-0x00B0)/4];
} PETIROC_CFG_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int    Ctrl;
/* 0x0004-0x00FF */ unsigned int    Reserved0[(0x0100-0x0004)/4];
} PETIROC_ADC_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int Ctrl;
/* 0x0004-0x007F */ unsigned int Reserved0[(0x0080-0x0004)/4];
/* 0x0080-0x0083 */ unsigned int Period;
/* 0x0084-0x0087 */ unsigned int LowCycles;
/* 0x0088-0x008B */ unsigned int NCycles;
/* 0x008C-0x008F */ unsigned int Start;
/* 0x0090-0x0093 */ unsigned int Status;
/* 0x0094-0x0097 */ unsigned int Delay;
/* 0x0098-0x00FF */ unsigned int Reserved1[(0x0100-0x0098)/4];
} Pulser_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int Ctrl;
/* 0x0004-0x0007 */ unsigned int NumEntriesMin;
/* 0x0008-0x000F */ unsigned int TOF_TdcEn[2];
/* 0x0010-0x0013 */ unsigned int CAL_TdcEn;
/* 0x0014-0x0017 */ unsigned int CAL_Ctrl;
/* 0x0018-0x001B */ unsigned int CAL_Status;
/* 0x001C-0x001F */ unsigned int Reserved0[(0x0020-0x001C)/4];
/* 0x0020-0x00EF */ unsigned int Scalers[52];
/* 0x00F0-0x00FF */ unsigned int Reserved1[(0x0100-0x00F0)/4];
} TDC_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int    TrigSrc;
/* 0x0004-0x0007 */ unsigned int    SyncSrc;
/* 0x0008-0x000B */ unsigned int    BusySrc;
/* 0x000C-0x000F */ unsigned int    LedGSrc;
/* 0x0010-0x0013 */ unsigned int    LedYSrc;
/* 0x0014-0x007F */ unsigned int    Reserved0[(0x0080-0x0014)/4];
/* 0x0080-0x0083 */ unsigned int    PulserPeriod;
/* 0x0084-0x0087 */ unsigned int    PulserLowCycles;
/* 0x0088-0x008B */ unsigned int    PulserNCycles;
/* 0x008C-0x008F */ unsigned int    PulserStart;
/* 0x0090-0x0093 */ unsigned int    PulserStatus;
/* 0x0094-0x009F */ unsigned int    Reserved1[(0x00A0-0x0094)/4];
/* 0x00A0-0x00A3 */ unsigned int    ScalerLatch;
/* 0x00A4-0x00A7 */ unsigned int    ScalerSysClk;
/* 0x00A8-0x00AB */ unsigned int    ScalerGClk;
/* 0x00AC-0x00AF */ unsigned int    ScalerSync;
/* 0x00B0-0x00B3 */ unsigned int    ScalerTrig;
/* 0x00B4-0x00B7 */ unsigned int    ScalerBusy;
/* 0x00B8-0x00BB */ unsigned int    ScalerNor32Charge0;
/* 0x00BC-0x00BF */ unsigned int    ScalerNor32Charge1;
/* 0x00C0-0x00C3 */ unsigned int    ScalerNor32Time0;
/* 0x00C4-0x00C7 */ unsigned int    ScalerNor32Time1;
/* 0x00C8-0x00FF */ unsigned int    Reserved2[(0x0100-0x00C8)/4];
} ALERT_SD_regs;

typedef struct
{
/* 0x0000-0x0003 */ unsigned int    Blocksize;
/* 0x0004-0x0007 */ unsigned int    TrigFifoBusyThr;
/* 0x0008-0x000B */ unsigned int    Lookback;
/* 0x000C-0x000F */ unsigned int    WindowWidth;
/* 0x0010-0x0013 */ unsigned int    DeviceId;
/* 0x0014-0x0017 */ unsigned int    TrigDelay;
/* 0x0018-0x00FF */ unsigned int    Reserved0[(0x0100-0x0018)/4];
} ALERT_EB_regs;

typedef struct
{
/* 0x0000-0x00FF */ CLK_regs          Clk;
/* 0x0100-0x01FF */ ALERT_SD_regs     Sd;
/* 0x0200-0x02FF */ ALERT_EB_regs     Eb;
/* 0x0300-0x04FF */ unsigned int      Reserved0[(0x0500-0x0300)/4];
/* 0x0500-0x05FF */ PETIROC_CFG_regs  PetirocCfg;
/* 0x0600-0x07FF */ PETIROC_ADC_regs  PetirocAdc[2];
/* 0x0800-0x08FF */ Pulser_regs       Pulser;
/* 0x0900-0x0FFF */ unsigned int      Reserved1[(0x1000-0x0900)/4];
/* 0x1000-0x10FF */ TDC_regs          Tdc;
} ALERTFEB_Regs;

#define FLASH_CMD_WRPAGE      0x12
#define FLASH_CMD_RD          0x13
#define FLASH_CMD_GETSTATUS   0x05
#define FLASH_CMD_WREN        0x06
#define FLASH_CMD_GETID       0x9F
#define FLASH_CMD_ERASE64K    0xDC
#define FLASH_CMD_4BYTE_EN    0xB7
#define FLASH_CMD_4BYTE_DIS   0xE9

#define FLASH_BYTE_LENGTH     32*1024*1024
#define FLASH_MFG_MICRON      0x20
#define FLASH_DEVID_N25Q256A  0xBB19

#define SPI_MFG_WINBOND       0xEF
#define SPI_DEVID_W25Q256JVIQ 0x4019

#define SPI_MFG_ATMEL         0x12
#define SPI_DEVID_AT45DB642D  0x3456

// Generic TDC event hit struct
typedef struct
{
  float t;
  float width;
} tdc_hit_t;

#endif
