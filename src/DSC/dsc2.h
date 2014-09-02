#ifndef DiscriminatorBoardRegs_H
#define DiscriminatorBoardRegs_H

#define SPIFLASH_ID_NUMONYX		0x20
#define SPIFLASH_ID_ATMEL		0x1F

#define CAL_ADDR_NUMONYX		0x1FE000
#define CAL_ADDR_ATMEL			0x3FC000

#define DSC_BOARD_ID       0x44534332
#define DSC_MAX_BOARDS             20
/* Reference channel clock frequency - 128 MHz */
#define DSC_REFERENCE_RATE  125000000.0

/* Some definitions for "type" argument in routines */
#define TDCTRG      0  /* Both TDC and TRG */
#define TDC         1
#define TRG         2
#define TRGOUTPUT   3
#define SCALER      1
#define VMESCALER   0
#define GATEDSCALER 1

typedef struct dsc_struct
{
  /* 0x0000-0x003F */ volatile unsigned int threshold[16];
  /* 0x0040-0x007F */ volatile unsigned int trigOut[16];
  /* 0x0080-0x0083 */ volatile unsigned int pulsewidth;
  /* 0x0084-0x0087 */ volatile unsigned int reserved0[(0x0088-0x0084)/4];
  /* 0x0088-0x008B */ volatile unsigned int chEnable;
  /* 0x008C-0x008F */ volatile unsigned int orMask;
  /* 0x0090-0x0093 */ volatile unsigned int delay;
  /* 0x0094-0x0097 */ volatile unsigned int testCtrl;
  /* 0x0098-0x009B */ volatile unsigned int ScalerLatchGrp2;
  /* 0x009C-0x009F */ volatile unsigned int ScalerLatchGrp1;
  /* 0x00A0-0x00A3 */ volatile unsigned int trigOutSrc;
  /* 0x00A4-0x00A7 */ volatile unsigned int Adr32;
  /* 0x00A8-0x00AB */ volatile unsigned int Interrupt;
  /* 0x00AC-0x00AF */ volatile unsigned int InterruptAck;
  /* 0x00B0-0x00B3 */ volatile unsigned int Geo;
  /* 0x00B4-0x00B7 */ volatile unsigned int IO;
  /* 0x00B8-0x00BB */ volatile unsigned int ScalerGateGrp2;
  /* 0x00BC-0x00BF */ volatile unsigned int ScalerGateGrp1;
  /* 0x00C0-0x00C3 */ volatile unsigned int PulserPeriod;
  /* 0x00C4-0x00C7 */ volatile unsigned int PulserLow;
  /* 0x00C8-0x00CB */ volatile unsigned int PulserNPulses;
  /* 0x00CC-0x00CF */ volatile unsigned int PulserStart;
  /* 0x00D0-0x00D3 */ volatile unsigned int PulserStatus;
  /* 0x00D4-0x00F7 */ volatile unsigned int reserved1[(0x00F8-0x00D4)/4];
  /* 0x00F8-0x00FF */ volatile unsigned int reserved2[(0x0100-0x00F8)/4];
  /* 0x0100-0x013F */ volatile unsigned int TrgScalerGrp1[16];
  /* 0x0140-0x017F */ volatile unsigned int TdcScalerGrp1[16];
  /* 0x0180-0x01BF */ volatile unsigned int TrgScalerGrp2[16];
  /* 0x01C0-0x01FF */ volatile unsigned int TdcScalerGrp2[16];
  /* 0x0200-0x0203 */ volatile unsigned int refScalerGrp2;
  /* 0x0204-0x0207 */ volatile unsigned int refScalerGrp1;
  /* 0x0208-0x03FF */ volatile unsigned int reserved3[(0x400-0x208)/4];
  /* 0x0400-0x0403 */ volatile unsigned int firmwareRev;
  /* 0x0404-0x0407 */ volatile unsigned int boardID;
  /* 0x0408-0x040B */ volatile unsigned int SerialNum;
  /* 0x040C-0x040F */ volatile unsigned int SerialMfg;
  /* 0x0410-0x04FF */ volatile unsigned int reserved4[(0x0500-0x410)/4];
  /* 0x0500-0x0503 */ volatile unsigned int readoutClear;
  /* 0x0504-0x0507 */ volatile unsigned int readoutStart;
  /* 0x0508-0x050B */ volatile unsigned int readoutCfg;
  /* 0x050C-0x7FFF */ volatile unsigned int reserved5[(0x8000-0x50C)/4];
  /* 0x8000-0x8003 */ volatile unsigned int calCmd;
  /* 0x8004-0x8203 */ volatile unsigned int calBuf[(0x8204-0x8004)/4];
  /* 0x8204-0x8FFF */ volatile unsigned int reserved6[(0x9000-0x8204)/4];
  /* 0x9000-0x9003 */ volatile unsigned int calExe;
} DSC2_regs;

/* threshold register Masks */
#define DSC_THRESHOLD_TRG_MASK          0x03ff0000
#define DSC_THRESHOLD_TDC_MASK          0x000003ff

/* pulsewidth register Masks */
#define DSC_PULSEWIDTH_TRG_OUTPUT_MASK  0xf0000000
#define DSC_PULSEWIDTH_TRG_MASK         0x003f0000
#define DSC_PULSEWIDTH_TDC_MASK         0x0000003f

/* chEnable register Masks */
#define DSC_CHENABLE_TRG_MASK           0xffff0000
#define DSC_CHENABLE_TDC_MASK           0x0000ffff

/* orMask register Masks */
#define DSC_ORMASK_TRG_MASK             0xffff0000
#define DSC_ORMASK_TDC_MASK             0x0000ffff

/* delay register Masks */
#define DSC_DELAY_TRG_MASK              0x007f0000
#define DSC_DELAY_SCALER_MASK           0x0000007f

/* firmwareRev register Masks */
#define DSC_FIRMWAREREV_MASK            0xffff
#define DSC_FIRMWAREREV_MAJOR_MASK      0xff00
#define DSC_FIRMWAREREV_MINOR_MASK      0x00ff

/* Scaler readout definitions 
   These are bound to change in future firmware/driver revisions */
#define DSC_SCT_HEADER					0xdca00000 /* + (0-7) Readout flag in LSBs + (8-12) Module id */
#define DSC_READOUT_TRG                 (1<<0)
#define DSC_READOUT_TDC                 (1<<1)
#define DSC_READOUT_TRGVME              (1<<2)
#define DSC_READOUT_TDCVME              (1<<3)
#define DSC_READOUT_REF                 (1<<4)
#define DSC_READOUT_REFVME              (1<<5)
#define DSC_LATCH_VME_BEFORE_READOUT    (1<<6)
#define DSC_LATCH_GATED_BEFORE_READOUT  (1<<7)

#endif
