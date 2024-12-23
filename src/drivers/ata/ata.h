//
// Created by bulbasaur on 23/12/24.
//
#include <stdint.h>
#ifndef ATA_H
#define ATA_H

#define SECTORS_PORT 0x01F2
#define LBA_PORT_0_7 0x1f3
#define LBA_PORT_8_15 0x1f4
#define LBA_PORT_16_23 0x1f5
#define LBA_PORT_24_27 0x01f6
#define COMMAND_PORT 0x1f7
#define READ_COMMAND 0x20
#define DATA_PORT 0x1f0
#define DATA_READY_FLAG 8

enum Mode {
  CHS,
  LBA
};
//CHS TODO
//void chs_read();
//void chs_write();

//LBA
void lba_read();
void lba_write();
#endif //ATA_H
