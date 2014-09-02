#ifndef CTP_H
#define CTP_H

/* Structure to handle the similarities between the FPGA registers 
   The VLX110 has extra registers and will be handled separately */
struct CTP_FPGAStruct
{
  /* 0xn00 */ volatile unsigned int status0;   /* Address 0 */
  /* 0xn04 */ volatile unsigned int status1;   /* Address 1 */
  /* 0xn08 */ volatile unsigned int config0;   /* Address 2 */
  /* 0xn0C */ volatile unsigned int config1;   /* Address 3 */
  /* 0xn10 */ volatile unsigned int temp;      /* Address 4 */
  /* 0xn14 */ volatile unsigned int vint;      /* Address 5 */
};

typedef struct
{
  /* 0x0000 */          unsigned int blankCTP0[(0x3C00-0x0000)/4];
  /* 0x3C00 */ struct   CTP_FPGAStruct fpga1;  /* Device 1 */
  /* 0x3C18 */          unsigned int blankCTP1[(0x5C00-0x3C18)/4];
  /* 0x5C00 */ struct   CTP_FPGAStruct fpga2;  /* Device 2 */
  /* 0x5C18 */          unsigned int blankCTP2[(0x7C00-0x5C18)/4];
  /* 0x7C00 */ struct   CTP_FPGAStruct fpga3;  /* Device 3 */
  /* 0x7C18 */          unsigned int RFU[2];             /* Address 6-7 */
  /* 0x7C20 */ volatile unsigned int sum_threshold_lsb;  /* Address 8 */
  /* 0x7C24 */ volatile unsigned int sum_threshold_msb;  /* Address 9 */
  /* 0x7C28 */ volatile unsigned int history_buffer_lsb; /* Address 10 */
  /* 0x7C2C */ volatile unsigned int history_buffer_msb; /* Address 11 */
  /* 0x7C30 */          unsigned int blankCTP3[(0x10000-0x7C30)/4];
} CTP_regs;

/* CTP Register bits and masks */
/* Lane_up mask shifts by 2 bits for each channel (two lanes/channel) */
#define CTP_FPGA_STATUS0_LANE_UP_MASK            0x3

#define CTP_FPGA_STATUS1_FIRMWARE_VERSION_MASK   0xFF00
/* History buffer only for VLX110 */
#define CTP_FPGA_STATUS1_HISTORY_BUFFER_READY    (1<<2)



#endif
