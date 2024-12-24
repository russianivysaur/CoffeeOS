#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "../idt/idt.h"
#include "../gdt/gdt.h"
#include "../stdlib/stdlib.h"
#include "../heap/kheap.h"
#include "../paging/paging.h"
#include "../drivers/ata/ata.h"
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

void print(unsigned char* string){
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

void println(unsigned char* string){
  print(string);
  curr_row++;
  curr_col = 1;
}

extern void handler();

void main(void){
  cls();
  unsigned char* message = (unsigned char*)WELCOME;
  println(message);
  init_gdt();
  println((unsigned char*)"GDT Loaded");

  //heap
  init_kheap();
  println((unsigned char*)"100 mb kernel heap allocated");


  //paging
  uint32_t* kernel_page_directory = create_directory();
  switch_directory(kernel_page_directory);
  uint32_t* memory1 = (uint32_t*) kzalloc(10); //2 bytes
  map_vaddr(kernel_page_directory,(void*)0x1000,(uint32_t)memory1);
  init_paging();
  uint8_t* memory2 = (uint8_t*)0x1000;
  memory2[0] = 'a';
  memory2[1] = 'b';
  memory2[2] = '\0';
  println((unsigned char*)memory1);
  println((unsigned char*)memory2);
  println((unsigned char*)"Enabled paging");


  //interuupts and idt
  add_interrupt(33,handler);
  init_idt();
  println((unsigned char*)"IDT Loaded");



  //reading from disk
  uint32_t* buffer = kzalloc(10000);
  lba_read(0,10,(uint16_t*)buffer);
  println((unsigned char*)buffer);
  while(1){}
}

