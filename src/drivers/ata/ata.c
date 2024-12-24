//
// Created by bulbasaur on 23/12/24.
//

#include "ata.h"
void lba_read(uint32_t lba,uint8_t sectors,uint16_t* buffer){
  uint8_t lba_8_bits = ((uint8_t)(lba >> 24 )) | (0b11100000);
  outb(LBA_PORT_24_27,lba_8_bits);
  outb(SECTORS_PORT,sectors);
  lba_8_bits = lba & 0x000000ff;
  outb(LBA_PORT_0_7,lba_8_bits);
  lba_8_bits = (lba & 0x0000ff00) >> 8;
  outb(LBA_PORT_8_15,lba_8_bits);
  lba_8_bits = (lba & 0x00ff0000) >> 16;
  outb(LBA_PORT_16_23,lba_8_bits);
  outb(COMMAND_PORT,0x20);
  uint8_t test = inb(COMMAND_PORT) & 0b00001000;
  while(test==0){
    test = inb(COMMAND_PORT) & 0b00001000;
  }


  for(int s=0;s<sectors;s++){
     for(int i=0;i<256;i++){
       *buffer = inw(DATA_PORT);
       buffer++;
     }
  }
  return;
}