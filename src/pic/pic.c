//
// Created by bulbasaur on 18/12/24.
//

#include <stdint.h>
#include "pic.h"

#define KEYBOARD_DATA_PORT 0x60



uint8_t read_keyboard_data(){
  return inb(KEYBOARD_DATA_PORT);
}
void pic_ack(){
  outb(0x20,0x20);
}

void pic_remap(int offset1, int offset2)
{
  outb(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
  outb(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
  outb(PIC_1_DATA, offset1);
  outb(PIC_2_DATA, offset2);
  outb(PIC_1_DATA, 4);
  outb(PIC_2_DATA, 2);

  outb(PIC_1_DATA, PIC_ICW4_8086);
  outb(PIC_2_DATA, PIC_ICW4_8086);

  outb(PIC_1_DATA, 0xFD);
  outb(PIC_2_DATA, 0xFF);

  asm("sti"); // Enable interrupts.
}
