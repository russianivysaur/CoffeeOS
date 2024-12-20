//
// Created by bulbasaur on 17/12/24.
//

#include "idt.h"
#include <stdint.h>
#include "../stdlib/stdlib.h"
#include "../kernel/kernel.h"
#include "../pic/pic.h"

struct IDTDescriptor idt_descriptors[INTERRUPT_COUNT];
struct IDTRDescriptor idtr;

void add_interrupt(uint16_t offset,void* handler_address){
  struct IDTDescriptor* descriptor = &idt_descriptors[offset];
  descriptor -> offset_lower = (uint16_t) (((uint32_t)handler_address) & 0x0000ffff);
  descriptor -> segment_selector = 0x08; //kernel ka
  descriptor -> reserved = 0x0;
  descriptor -> flags = 0x8E;
  descriptor -> offset_higher =(uint16_t) (((uint32_t) handler_address) >> 16);
}

extern void load_idt(struct IDTRDescriptor*);

void init_idt(){
  idtr.size = sizeof(idt_descriptors) - 1;
  idtr.offset = (uint32_t) &idt_descriptors;
  load_idt(&idtr);
  pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}

void c_handler(){
  unsigned char ascii[256] =
	{
		0x0, 0x0, '1', '2', '3', '4', '5', '6',		// 0 - 7
		'7', '8', '9', '0', '-', '=', 0x0, 0x0,		// 8 - 15
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',		// 16 - 23
		'o', 'p', '[', ']', '\n', 0x0, 'a', 's',	// 24 - 31
		'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',		// 32 - 39
		'\'', '`', 0x0, '\\', 'z', 'x', 'c', 'v',	// 40 - 47
		'b', 'n', 'm', ',', '.', '/', 0x0, '*',		// 48 - 55
		0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,		// 56 - 63
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',		// 64 - 71
		'8', '9', '-', '4', '5', '6', '+', '1',		// 72 - 79
		'2', '3', '0', '.'				// 80 - 83
	};
  int index = (int)read_keyboard_data();
  pic_ack();
}