//
// Created by bulbasaur on 17/12/24.
//
#include <stddef.h>
#ifndef KERNEL_H
#define KERNEL_H
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define WELCOME "Welcome to Coffee OS\n\nWe currently have some features to work on like : \n0. ASCII character and newline support text mode ( Done :) ) \n1. Scrolling behaviour\n2. Keyboard input\n3. Shell\n4. File system\n"
void print(unsigned char*);
void println(unsigned char*);
#endif //KERNEL_H
