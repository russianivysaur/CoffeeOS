//
// Created by bulbasaur on 23/12/24.
//

#include "ata.h"
void lba_read(uint32_t lba,uint32_t sectors,uint32_t* buffer){
  uint8_t lba_8_bits = (lba & 0x0f0000000 ) | (0b00000000000000000000000011100000);
  outb(lba_8_bits,LBA_PORT_24_27);
  lba_8_bits = lba & 0x000000ff;
  outb(lba_8_bits,LBA_PORT_0_7);
  lba_8_bits = lba & 0x0000ff00;
  outb(lba_8_bits,LBA_PORT_8_15);
  lba_8_bits = lba & 0x00ff0000;
  outb(lba_8_bits,LBA_PORT_16_23);
}