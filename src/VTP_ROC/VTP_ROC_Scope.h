#ifndef VTP_ROC_SCOPE_H
#define VTP_ROC_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_ROC_Scope : public TGCompositeFrame
{
public:
  VTP_ROC_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x83E4+offset, 0, 0x83E0+offset, 0, 0x83F0+offset,1);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("TI_DATA_STATE",       27, TRACE_MODE_DIGITAL,  4,  0,     0x83E8+offset, 0,   0x83EC+offset, 0);
    pScope->AddTrace("EVIO_HEADER_STATE",   27, TRACE_MODE_DIGITAL,  4,  4,     0x83E8+offset, 4,   0x83EC+offset, 4);
    pScope->AddTrace("ROC_HEADER_STATE",    27, TRACE_MODE_DIGITAL,  4,  8,     0x83E8+offset, 8,   0x83EC+offset, 8);
    pScope->AddTrace("CODA_ROC_STATE",      27, TRACE_MODE_DIGITAL,  4, 12,     0x83E8+offset,12,   0x83EC+offset,12);
    pScope->AddTrace("TCP_TX_CTS",          27, TRACE_MODE_DIGITAL,  1, 16,     0x83E8+offset,16,   0x83EC+offset,16);
    pScope->AddTrace("TCP_TX_DATA_VALID",   27, TRACE_MODE_DIGITAL,  1, 17,     0x83E8+offset,17,   0x83EC+offset,17);
    pScope->AddTrace("TI_EVT_RD",           27, TRACE_MODE_DIGITAL,  1, 18,     0x83E8+offset,18,   0x83EC+offset,18);
    pScope->AddTrace("TI_EVT_EMPTY",        27, TRACE_MODE_DIGITAL,  1, 19,     0x83E8+offset,19,   0x83EC+offset,19);
    pScope->AddTrace("TI_EVT_LEN_RD",       27, TRACE_MODE_DIGITAL,  1, 20,     0x83E8+offset,20,   0x83EC+offset,20);
    pScope->AddTrace("TI_EVT_LEN_EMPTY",    27, TRACE_MODE_DIGITAL,  1, 21,     0x83E8+offset,21,   0x83EC+offset,21);
    pScope->AddTrace("TI_ACK",              27, TRACE_MODE_DIGITAL,  1, 22,     0x83E8+offset,22,   0x83EC+offset,22);
    pScope->AddTrace("V7_EVT_EMPTY",        27, TRACE_MODE_DIGITAL,  1, 23,     0x83E8+offset,23,   0x83EC+offset,23);
    pScope->AddTrace("V7_EVT_RD",           27, TRACE_MODE_DIGITAL,  1, 24,     0x83E8+offset,24,   0x83EC+offset,24);
    pScope->AddTrace("V7_EVT_LEN_EMPTY",    27, TRACE_MODE_DIGITAL,  1, 25,     0x83E8+offset,25,   0x83EC+offset,25);
    pScope->AddTrace("V7_EVT_LEN_RD",       27, TRACE_MODE_DIGITAL,  1, 26,     0x83E8+offset,26,   0x83EC+offset,26);
  }
};

#endif
