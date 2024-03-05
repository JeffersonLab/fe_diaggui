#ifndef VTP_FADCSTREAM_SCOPE_H
#define VTP_FADCSTREAM_SCOPE_H

#include "RootHeader.h"
#include "ModuleFrame.h"
#include "Scope.h"

class VTP_FADCSTREAM_Scope : public TGCompositeFrame
{
public:
  VTP_FADCSTREAM_Scope(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    Scope *pScope;
    int offset = pModule->BaseAddr;

    AddFrame(pScope = new Scope(this, pModule), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

    // void Init(int sampleLen, int rdyAddr, int rdyBit, int ctrlAddr, int ctrlBit, int dataAddr, int dataNum)
    pScope->Init(512, 0x9058+offset, 0, 0x9054+offset, 0, 0x90E0+offset,8);

    // void AddTrace(const char *name, int height, int mode, int bitCount, int bitOffsetData, int cfgAddr, int cfgBitOffset, int valAddr, int valBitOffset)
    pScope->AddTrace("IP_PAYLOAD_DATA0",   4*32+8, TRACE_MODE_DIGITAL, 32,   0,    0x9060+offset, 0,   0x90C0+offset, 0);
    pScope->AddTrace("IP_PAYLOAD_DATA1",   4*32+8, TRACE_MODE_DIGITAL, 32,  32,    0x9064+offset, 0,   0x90C4+offset, 0);
    pScope->AddTrace("MAC_RX_DATA_H",      4*32+8, TRACE_MODE_DIGITAL, 32,  64,    0x9068+offset, 0,   0x90C8+offset, 0);
    pScope->AddTrace("MAC_RX_DATA_L",      4*32+8, TRACE_MODE_DIGITAL, 32,  96,    0x906C+offset, 0,   0x90CC+offset, 0);
    pScope->AddTrace("RX_TCP_ACK_NO",      4*32+8, TRACE_MODE_DIGITAL, 32, 128,    0x9070+offset, 0,   0x90D0+offset, 0);
    pScope->AddTrace("RX_VALID_ACK_TMOUT", 4*24+8, TRACE_MODE_DIGITAL, 24, 160,    0x9074+offset, 0,   0x90D4+offset, 0);
    pScope->AddTrace("RX_TCP_FLAGS",       4* 8+8, TRACE_MODE_DIGITAL,  8, 184,    0x9074+offset,24,   0x90D4+offset,24);
    pScope->AddTrace("MAC_RX_DATA_VALID",  4* 8+8, TRACE_MODE_DIGITAL,  8, 192,    0x9078+offset, 0,   0x90D8+offset, 0);
    pScope->AddTrace("TCP_STATE",          4* 4+8, TRACE_MODE_DIGITAL,  4, 200,    0x9078+offset, 8,   0x90D8+offset, 8);
    pScope->AddTrace("IP_PAYLOAD_WORD_CNT",4*11+8, TRACE_MODE_DIGITAL, 11, 204,    0x9078+offset,12,   0x90D8+offset,12);
    pScope->AddTrace("RX_TCP_DATA_OFFSET", 4* 4+8, TRACE_MODE_DIGITAL,  4, 215,    0x9078+offset,23,   0x90D8+offset,23);
    pScope->AddTrace("MAC_N_RX_BAD_CRCS",      27, TRACE_MODE_DIGITAL,  1, 223,    0x9078+offset,31,   0x90D8+offset,31);
    pScope->AddTrace("MAC_RX_SOF",             27, TRACE_MODE_DIGITAL,  1, 224,    0x907C+offset, 0,   0x90DC+offset, 0);
    pScope->AddTrace("MAC_RX_EOF",             27, TRACE_MODE_DIGITAL,  1, 225,    0x907C+offset, 1,   0x90DC+offset, 1);
    pScope->AddTrace("MAC_RX_FRAME_VALID",     27, TRACE_MODE_DIGITAL,  1, 226,    0x907C+offset, 2,   0x90DC+offset, 2);

    pScope->AddTrace("RT_REQ_RTS",             27, TRACE_MODE_DIGITAL,  1, 227,    0x907C+offset, 3,   0x90DC+offset, 3);
    pScope->AddTrace("RT_REQ_CTS",             27, TRACE_MODE_DIGITAL,  1, 228,    0x907C+offset, 4,   0x90DC+offset, 4);
    pScope->AddTrace("RT_NAK",                 27, TRACE_MODE_DIGITAL,  1, 229,    0x907C+offset, 5,   0x90DC+offset, 5);
    pScope->AddTrace("RTS",                    27, TRACE_MODE_DIGITAL,  1, 230,    0x907C+offset, 6,   0x90DC+offset, 6);
    pScope->AddTrace("RETRANSMIT_FLAG",        27, TRACE_MODE_DIGITAL,  1, 231,    0x907C+offset, 7,   0x90DC+offset, 7);
    pScope->AddTrace("TX_PKT_SEQ_STRT",        27, TRACE_MODE_DIGITAL,  1, 232,    0x907C+offset, 8,   0x90DC+offset, 8);
    pScope->AddTrace("NXT_TX_TCP_FRM_Q",       27, TRACE_MODE_DIGITAL,  1, 233,    0x907C+offset, 9,   0x90DC+offset, 9);
    pScope->AddTrace("NXT_TX_TCP_STRM_SEL",    27, TRACE_MODE_DIGITAL,  1, 234,    0x907C+offset,10,   0x90DC+offset,10);
    pScope->AddTrace("TX_TCP_STRM_SEL",        27, TRACE_MODE_DIGITAL,  1, 235,    0x907C+offset,11,   0x90DC+offset,11);
    pScope->AddTrace("EVENTS1",                27, TRACE_MODE_DIGITAL,  1, 236,    0x907C+offset,12,   0x90DC+offset,12);
    pScope->AddTrace("EVENTS2",                27, TRACE_MODE_DIGITAL,  1, 237,    0x907C+offset,13,   0x90DC+offset,13);
    pScope->AddTrace("EVENTS3",                27, TRACE_MODE_DIGITAL,  1, 238,    0x907C+offset,14,   0x90DC+offset,14);
    pScope->AddTrace("EVENTS4",                27, TRACE_MODE_DIGITAL,  1, 239,    0x907C+offset,15,   0x90DC+offset,15);
    pScope->AddTrace("EVENTS4A",               27, TRACE_MODE_DIGITAL,  1, 240,    0x907C+offset,16,   0x90DC+offset,16);
    pScope->AddTrace("EVENTS4B",               27, TRACE_MODE_DIGITAL,  1, 241,    0x907C+offset,17,   0x90DC+offset,17);
    pScope->AddTrace("EVENTS4C",               27, TRACE_MODE_DIGITAL,  1, 242,    0x907C+offset,18,   0x90DC+offset,18);
    pScope->AddTrace("EVENTS5",                27, TRACE_MODE_DIGITAL,  1, 243,    0x907C+offset,19,   0x90DC+offset,19);
    pScope->AddTrace("EVENTS7",                27, TRACE_MODE_DIGITAL,  1, 244,    0x907C+offset,20,   0x90DC+offset,20);
    pScope->AddTrace("EVENTS8",                27, TRACE_MODE_DIGITAL,  1, 245,    0x907C+offset,21,   0x90DC+offset,21);
    pScope->AddTrace("EVENTS9",                27, TRACE_MODE_DIGITAL,  1, 246,    0x907C+offset,22,   0x90DC+offset,22);
    pScope->AddTrace("EVENTS10",               27, TRACE_MODE_DIGITAL,  1, 247,    0x907C+offset,23,   0x90DC+offset,23);
    pScope->AddTrace("EVENTS11",               27, TRACE_MODE_DIGITAL,  1, 248,    0x907C+offset,24,   0x90DC+offset,24);
    pScope->AddTrace("EVENTS12",               27, TRACE_MODE_DIGITAL,  1, 249,    0x907C+offset,25,   0x90DC+offset,25);
    pScope->AddTrace("EVENTS13",               27, TRACE_MODE_DIGITAL,  1, 250,    0x907C+offset,26,   0x90DC+offset,26);
    pScope->AddTrace("IP_PAYLOAD_EOF_D",       27, TRACE_MODE_DIGITAL,  1, 251,    0x907C+offset,27,   0x90DC+offset,27);
    pScope->AddTrace("RX_TCP_STREAM_SEL_D",    27, TRACE_MODE_DIGITAL,  1, 252,    0x907C+offset,28,   0x90DC+offset,28);
    pScope->AddTrace("VALID_RX_TCP_ALL",       27, TRACE_MODE_DIGITAL,  1, 253,    0x907C+offset,29,   0x90DC+offset,29);
    pScope->AddTrace("ORIGINATOR_ID",          27, TRACE_MODE_DIGITAL,  1, 254,    0x907C+offset,30,   0x90DC+offset,30);
    pScope->AddTrace("IP_PAYLOAD_WORD_VALID",  27, TRACE_MODE_DIGITAL,  1, 255,    0x907C+offset,31,   0x90DC+offset,31);
  }
};

#endif

