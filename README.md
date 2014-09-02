fe_diaggui
==========

Fast Electronics Diagnostic GUI for various boards we have created.

The GUI communicates with the module using a proprietary protocol over TCP Sockets. A compatible server must be run where the module is present. Currently servers have been implemented for X86 based Intel VME controllers and for the GTP NIOS II processor.

The following modules/firmwares are supported:
CTP (Crate Trigger Processor)
DCRB (Drift Chamber Readout Board - HallB)
DCRBScalers (DCRB crate scaler plot)
DSC (Discriminator)
FADC (FlashADC 250MHz)
GTP (Global Trigger Processor - HallD)
GTP_HPS (GTP HPS - HallB)
SD (Signal Distribution)
SSP (Sub System Processor - HallD)
SSP_HPS (SSP HPS - HallB)
TID (Trigger Interface/Distribution)
V1495Pulser (V1495 Pulser - HallD)
VSCM (VXS Silicon Control Module - HallB)