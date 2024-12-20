#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "../idt/idt.h"
#include "../gdt/gdt.h"
#include "../stdlib/stdlib.h"
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

volatile char* vga_buffer = (volatile char*) 0xb8000;
static size_t curr_row = 1;
static size_t curr_col = 1;

static inline uint8_t color_byte(enum vga_color background,enum vga_color foreground){
  return (foreground) | (background<<4);
}

void write_char(unsigned char c,uint16_t offset,enum vga_color background,enum vga_color foreground){
  vga_buffer[offset] = c;
  vga_buffer[offset+1] = color_byte(background,foreground);
}

uint16_t row_col_to_offset(uint16_t row,uint16_t col){
	uint16_t offsets_before_col = 0;
	uint16_t offsets_above_row = 0;
	if(row!=1){
		offsets_above_row = (row-1) * VGA_WIDTH * 2;
	}
	if(col!=1){
		offsets_before_col = (col-1) * 2;
	}
	return offsets_before_col + offsets_above_row;
}

void cls(){
  for(uint16_t row=1;row<=VGA_HEIGHT;row++){
    for(uint16_t col=1;col<=VGA_WIDTH;col++){
      write_char(' ',row_col_to_offset(row,col),VGA_COLOR_BLACK,VGA_COLOR_WHITE);
    }
  }
}

void kernel_print(unsigned char* string){
  while(*string != '\0') {
    if(*string == '\n'){
      curr_row++;
      curr_col = 1;
      string++;
      continue;
    }
    write_char(*string,row_col_to_offset(curr_row,curr_col),VGA_COLOR_BLACK,VGA_COLOR_WHITE);
    if(curr_col==VGA_WIDTH){
      curr_col = 1;
      curr_row++;
    }else{
      curr_col++;
    }
    string++;
  }
}

extern void handler();
extern void interrupt();

void main(void){
  cls();
  unsigned char* message = (unsigned char*)WELCOME;
  kernel_print(message);
  init_gdt();
  kernel_print((unsigned char*)"GDT Loaded\n");
  add_interrupt(33,handler);
  init_idt();
  kernel_print((unsigned char*)"IDT Loaded\n");
  kernel_print((unsigned char*)&store[0]);
  //interrupt();
}

