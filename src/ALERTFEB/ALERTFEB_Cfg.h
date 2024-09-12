#ifndef ALERTFEB_CFG_H
#define ALERTFEB_CFG_H

#include <stdlib.h>
#include "RootHeader.h"
#include "ModuleFrame.h"
#include "ALERTFEB_Regs.h"

class ALERTFEB_Cfg  : public TGCompositeFrame
{
public:
  ALERTFEB_Cfg(const TGWindow *p, ModuleFrame *pModule) : TGCompositeFrame(p, 400, 400)
  {
    SetLayoutManager(new TGVerticalLayout(this));

    pM = pModule;
    pRegs = (ALERTFEB_Regs *)pM->BaseAddr;

    TGCompositeFrame *pTF1;
    TGTextButton *pB;

    AddFrame(pTF1 = new TGHorizontalFrame(this), new TGLayoutHints(kLHintsExpandX));
      pTF1->AddFrame(pB = new TGTextButton(pTF1, "FirmwareUpdate", BTN_ALERTFEB_FIRMWARE_UPDATE), new TGLayoutHints(kLHintsCenterX));
        pB->SetWidth(200);
        pB->Associate(this);
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
            case BTN_ALERTFEB_FIRMWARE_UPDATE:
              UpdateFirmware();
              break;

            default:
              printf("button id %d pressed\n", (int)parm1);
              break;
          }
          break;
      }
      break;
    }
    return kTRUE;
  }

  void UpdateFirmware()
  {
    TClass* clGMainFrame = TClass::GetClass("TGMainFrame");
    TGWindow* win = 0;
    static TString dir(".");
    TGFileInfo fi;
    const char *myfiletypes[] = {"BIN files","*.bin",0};
    fi.fFileTypes = myfiletypes;
    fi.fIniDir    = StrDup(dir.Data());

    new TGFileDialog(gClient->GetRoot(), 0, kFDOpen, &fi);
    if(fi.fFilename!=NULL)
    {
      TIter iWin(gClient->GetListOfWindows());
      while ((win = (TGWindow*)iWin()))
      {
        if(win->InheritsFrom(clGMainFrame))
        {
          flash_FirmwareUpdateVerify(fi.fFilename);
          break;
        }
      }
    }
  }

  void flash_SelectSpi(int sel)
  {
    if(sel)
      pM->WriteReg32(&pRegs->Clk.SpiCtrl, 0x200);
    else
      pM->WriteReg32(&pRegs->Clk.SpiCtrl, 0x100);
  }

  unsigned char flash_TransferSpi(unsigned char data, int do_read)
  {
    static int no_read_cnt = 0;
    int i;
    unsigned int val=0;

    pM->WriteReg32(&pRegs->Clk.SpiCtrl, data | 0x400);

    if(do_read || (no_read_cnt>10))
    {
      for(i = 0; i < 1000; i++)
      {
        val = pM->ReadReg32(&pRegs->Clk.SpiStatus);
        if(val & 0x800)
          break;
      }
      if(i == 1000)
        printf("%s: ERROR: Timeout!!!\n", __func__);

      no_read_cnt = 0;
    }
    else
      no_read_cnt++;

    return val & 0xFF;
  }

  void flash_GetId(unsigned char *rsp)
  {
    flash_SelectSpi(1);
    flash_TransferSpi(FLASH_CMD_GETID,0);
    rsp[0] = flash_TransferSpi(0xFF,1);
    rsp[1] = flash_TransferSpi(0xFF,1);
    rsp[2] = flash_TransferSpi(0xFF,1);
    flash_SelectSpi(0);
  }

  unsigned char flash_GetStatus()
  {
    unsigned char rsp;

    flash_SelectSpi(1);
    flash_TransferSpi(FLASH_CMD_GETSTATUS,0);
    rsp = flash_TransferSpi(0xFF,1);
    flash_SelectSpi(0);

    return rsp;
  }

  int flash_Cmd(unsigned char cmd)
  {
    flash_SelectSpi(1);
    flash_TransferSpi(cmd,0);
    flash_SelectSpi(0);

    return kTRUE;
  }

  int flash_CmdAddr(unsigned char cmd, unsigned int addr)
  {
    flash_SelectSpi(1);
    flash_TransferSpi(cmd,0);
    flash_TransferSpi((addr>>24)&0xFF,0);
    flash_TransferSpi((addr>>16)&0xFF,0);
    flash_TransferSpi((addr>> 8)&0xFF,0);
    flash_TransferSpi((addr>> 0)&0xFF,0);
    flash_SelectSpi(0);

    return kTRUE;
  }

  int flash_CmdAddrData(unsigned char cmd, unsigned int addr, unsigned char *data, int len)
  {
    int i;

    flash_SelectSpi(1);
    flash_TransferSpi(cmd,0);
    flash_TransferSpi((addr>>24)&0xFF,0);
    flash_TransferSpi((addr>>16)&0xFF,0);
    flash_TransferSpi((addr>> 8)&0xFF,0);
    flash_TransferSpi((addr>> 0)&0xFF,0);

    for(i=0;i<len;i++)
      flash_TransferSpi(data[i],0);

    flash_SelectSpi(0);

    return kTRUE;
  }

  int flash_IsValid()
  {
    unsigned char rsp[3];

    flash_SelectSpi(0);
    flash_GetId(rsp);
    flash_GetId(rsp);

    if( (rsp[0] == SPI_MFG_WINBOND) &&
        (rsp[1] == (SPI_DEVID_W25Q256JVIQ>>8)) &&
        (rsp[2] == (SPI_DEVID_W25Q256JVIQ&0xFF)) )
      return kTRUE;

    printf("%s: ERROR mfg=%02X, devid=%02X%02X\n", __func__, (unsigned int)rsp[0], (unsigned int)rsp[1], (unsigned int)rsp[2]);
    return kFALSE;
  }

  int flash_FirmwareUpdateVerify(char *filename)
  {
    int result;

    printf("Updating firmware...");
    result = flash_FirmwareUpdate(filename);
    if(result != kTRUE)
    {
      printf("failed.\n");
      return result;
    }
    else
      printf("succeeded.");

    printf("\nVerifying...");
    result = flash_FirmwareVerify(filename);
    if(result != kTRUE)
    {
      printf("failed.\n");
      return result;
    }
    else
      printf("ok.\n");

    return kTRUE;
  }

  int flash_FirmwareUpdate(char *filename)
  {
    FILE *f;
    int i;
    unsigned int addr = 0, page_size = 256, erase_first = 1;
    unsigned char buf[256];

    if(flash_IsValid() != kTRUE)
      return kFALSE;

    f = fopen(filename, "rb");
    if(!f)
    {
      printf("%s: ERROR: invalid file %s\n", __func__, filename);
      return kFALSE;
    }

    flash_Cmd(FLASH_CMD_WREN);
    flash_Cmd(FLASH_CMD_4BYTE_EN);

    memset(buf, 0xff, page_size);
    while(fread(buf, 1, page_size, f) > 0)
    {
      // Erase when at a new 64k block boundary
      if(!(addr % 65536) || erase_first)
      {
        erase_first = 0;
        printf("%s: Erasing sector @ 0x%08X\n", __func__, addr);

        flash_Cmd(FLASH_CMD_WREN);
        flash_CmdAddr(FLASH_CMD_ERASE64K, addr);

        i = 0;
        while(1)
        {
          if(!(flash_GetStatus() & 0x1))
            break;
          usleep(16000);
          if(i == 60+6) /* 1000ms maximum sector erase time */
          {
            fclose(f);
            printf("%s: ERROR: failed to erase flash\n", __func__);
            flash_Cmd(FLASH_CMD_WREN);
            flash_Cmd(FLASH_CMD_4BYTE_DIS);
            return kFALSE;
          }
          i++;
        }
      }

      // Program 256 byte page
      flash_Cmd(FLASH_CMD_WREN);
      flash_CmdAddrData(FLASH_CMD_WRPAGE, addr, buf, 256);

      i = 0;
      while(1)
      {
        if(!(flash_GetStatus() & 0x1)) // slow call over ethernet (>>10us per call)
          break;
        if(i == 300) /* 3ms maximum page program time  */
        {
          fclose(f);
          printf("%s: ERROR: failed to erase flash\n", __func__);
          flash_Cmd(FLASH_CMD_WREN);
          flash_Cmd(FLASH_CMD_4BYTE_DIS);
          return kFALSE;
        }
        i++;
      }

      memset(buf, 0xff, 256);
      addr+= 256;
    }
    flash_Cmd(FLASH_CMD_WREN);
    flash_Cmd(FLASH_CMD_4BYTE_DIS);

    return kTRUE;
  }

  int flash_FirmwareRead(char *filename)
  {
    FILE *f;
    int i;

    if(flash_IsValid() != kTRUE)
      return kFALSE;

    f = fopen(filename, "wb");
    if(!f)
    {
      printf("%s: ERROR: invalid file %s\n", __func__, filename);
      return kFALSE;
    }

    flash_Cmd(FLASH_CMD_WREN);
    flash_Cmd(FLASH_CMD_4BYTE_EN);

    flash_SelectSpi(1);
    flash_TransferSpi(FLASH_CMD_RD,0);  // continuous array read
    flash_TransferSpi(0,0);
    flash_TransferSpi(0,0);
    flash_TransferSpi(0,0);
    flash_TransferSpi(0,0);

    for(i = 0; i < FLASH_BYTE_LENGTH; i++)
    {
      fputc(flash_TransferSpi(0xFF,1), f);
      if(!(i% 65536))
      {
        printf(".");
        usleep(10000);
      }
    }

    flash_SelectSpi(0);
    flash_Cmd(FLASH_CMD_WREN);
    flash_Cmd(FLASH_CMD_4BYTE_DIS);
    fclose(f);

    return kTRUE;
  }

  int flash_FirmwareVerify(char *filename)
  {
    FILE *f;
    int i, len, addr = 0;
    unsigned char buf[256], val;

    if(flash_IsValid() != kTRUE)
      return kFALSE;

    f = fopen(filename, "rb");
    if(!f)
    {
      printf("%s: ERROR: invalid file %s\n", __func__, filename);
      return kFALSE;
    }

    flash_Cmd(FLASH_CMD_WREN);
    flash_Cmd(FLASH_CMD_4BYTE_EN);

    flash_SelectSpi(1);
    flash_TransferSpi(FLASH_CMD_RD,0);  // continuous array read
    flash_TransferSpi(0,0);
    flash_TransferSpi(0,0);
    flash_TransferSpi(0,0);
    flash_TransferSpi(0,0);

    while((len = fread(buf, 1, 256, f)) > 0)
    {
      for(i=0; i<len; i++)
      {
        val = flash_TransferSpi(0xFF,1);
        if(buf[i] != val)
        {
          flash_SelectSpi(0);
          flash_Cmd(FLASH_CMD_WREN);
          flash_Cmd(FLASH_CMD_4BYTE_DIS);
          fclose(f);
          printf("%s: ERROR: failed verify at address 0x%08X[%02X,%02X]\n", __func__, addr, (unsigned int)buf[i], (unsigned int)val);
          return kFALSE;
        }
      }
      addr+= 256;
      if(!(addr & 0xFFFF))
      {
        printf(".");
        fflush(stdout);
      }
    }
    flash_SelectSpi(0);
    flash_Cmd(FLASH_CMD_WREN);
    flash_Cmd(FLASH_CMD_4BYTE_DIS);
    fclose(f);

    return kTRUE;
  }

private:
  enum GUI_IDs
  {
    BTN_ALERTFEB_FIRMWARE_UPDATE
  };

  ALERTFEB_Regs       *pRegs;

  ModuleFrame         *pM;
};

#endif
