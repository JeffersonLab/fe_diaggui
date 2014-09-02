#ifndef DCRB_H
#define DCRB_H

#define TRIGSRC_SWSYNC		0x800
#define TRIGSRC_SWTRIG		0x008

typedef struct
{
/* 0x0000-0x0003 */ volatile unsigned int FirmwareRev;
/* 0x0004-0x0007 */ volatile unsigned int BoardID;
/* 0x0008-0x000B */ volatile unsigned int GrpBusyFifo;
/* 0x000C-0x000F */ volatile unsigned int GrpBusyTrig;
/* 0x0010-0x0013 */ volatile unsigned int GrpErrorFifo;
/* 0x0014-0x0017 */ volatile unsigned int SpiFlash;
/* 0x0018-0x001B */ volatile unsigned int ICap;
/* 0x001C-0x001F */ volatile unsigned int Adr32M;
/* 0x0020-0x0023 */ volatile unsigned int LookBack;
/* 0x0024-0x0027 */ volatile unsigned int WindowWidth;
/* 0x0028-0x002B */ volatile unsigned int BlockConfig;
/* 0x002C-0x002F */ volatile unsigned int TDCConfig;
/* 0x0030-0x0033 */ volatile unsigned int ClockConfig;
/* 0x0034-0x0037 */ volatile unsigned int TestPulseConfig;
/* 0x0038-0x003B */ volatile unsigned int DACConfig;
/* 0x003C-0x003F */ volatile unsigned int TriggerBusyThreshold;
/* 0x0040-0x0043 */ volatile unsigned int TriggerSource;
/* 0x0044-0x0047 */ volatile unsigned int ADR32;
/* 0x0048-0x004B */ volatile unsigned int Interrupt;
/* 0x004C-0x004F */ volatile unsigned int InterruptAck;
/* 0x0050-0x0053 */ volatile unsigned int Geo;
/* 0x0054-0x0057 */ volatile unsigned int FifoWordCnt;
/* 0x0058-0x005B */ volatile unsigned int FifoEventCnt;
/* 0x005C-0x005F */ volatile unsigned int ReadoutConfig;
/* 0x0060-0x0063 */ volatile unsigned int SRAMDebugAddr;
/* 0x0064-0x0067 */ volatile unsigned int SRAMDebugData;
/* 0x0068-0x006B */ volatile unsigned int Reset;
/* 0x006C-0x0077 */ volatile unsigned int ChDisable[3];
/* 0x0078-0x007B */ volatile unsigned int ScalerLatch;
/* 0x007C-0x007F */ volatile unsigned int Reserved1[(0x0080-0x007C)/4];
/* 0x0080-0x0083 */ volatile unsigned int FifoBlockCnt;
/* 0x0084-0x0087 */ volatile unsigned int InterruptWordCnt;
/* 0x0088-0x008B */ volatile unsigned int InterruptEventCnt;
/* 0x008C-0x008F */ volatile unsigned int InterruptBlockCnt;
/* 0x0090-0x0093 */ volatile unsigned int BusyWordCnt;
/* 0x0094-0x0097 */ volatile unsigned int BusyEventCnt;
/* 0x0098-0x009B */ volatile unsigned int BusyBlockCnt;
/* 0x009C-0x009F */ volatile unsigned int TriggerCtrl;
/* 0x00A0-0x00A3 */ volatile unsigned int GtpCtrl;
/* 0x00A4-0x00A7 */ volatile unsigned int GtpCtrlTile0;
/* 0x00A8-0x00AB */ volatile unsigned int GtpDrpCtrl;
/* 0x00AC-0x00AF */ volatile unsigned int GtpStatus;
/* 0x00B0-0x00B3 */ volatile unsigned int SoftErrCnt;
/* 0x00B4-0x00B7 */ volatile unsigned int PrbsErrCnt;
/* 0x00B8-0x0107 */ volatile unsigned int Reserved3[(0x0108-0x00B8)/4];
/* 0x0108-0x010B */ volatile unsigned int SwAGpio;
/* 0x010C-0x010F */ volatile unsigned int SwBGpio;
/* 0x0110-0x0113 */ volatile unsigned int TokenInCfg;
/* 0x0114-0x0117 */ volatile unsigned int TokenOutCfg;
/* 0x0118-0x011B */ volatile unsigned int SdLinkCfg;
/* 0x011C-0x011F */ volatile unsigned int TrigOutCfg;
/* 0x0120-0x0123 */ volatile unsigned int PulserPeriod;
/* 0x0124-0x0127 */ volatile unsigned int PulserLow;
/* 0x0128-0x012B */ volatile unsigned int PulserNPulses;
/* 0x012C-0x012F */ volatile unsigned int PulserStart;
/* 0x0130-0x0133 */ volatile unsigned int PulserStatus;
/* 0x0134-0x0FE7 */ volatile unsigned int Reserved4[(0x0FE8-0x0134)/4];
/* 0x0FE8-0x0FEB */ volatile unsigned int BusyScaler;
/* 0x0FEC-0x0FEF */ volatile unsigned int BusyCyclesScaler;
/* 0x0FF0-0x0FF3 */ volatile unsigned int VmeClkScaler;
/* 0x0FF4-0x0FF7 */ volatile unsigned int SyncScaler;
/* 0x0FF8-0x0FFB */ volatile unsigned int Trig1Scaler;
/* 0x0FFC-0x0FFF */ volatile unsigned int Trig2Scaler;
/* 0x1000-0x117F */ volatile unsigned int Scalers[96];
} DCRB_regs;


#endif
