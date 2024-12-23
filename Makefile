DEBUG_FILE = ./build/kernelfull.o

all: ./build/coffee.iso

./build/coffee.iso: ./build/boot.o ./build/kernel.o ./build/idt.o ./build/load_idt.o ./build/handler.o ./build/stdlib.o ./build/gdt.o ./build/load_gdt.o ./build/pic.o ./build/io.o ./build/kheap.o ./build/heap.o ./build/paging.o ./build/enable_paging.o ./build/ata.o
	i686-elf-ld -g -T linker.ld -o $(DEBUG_FILE) $^
	i686-elf-gcc -g -T linker.ld -o $@ -ffreestanding -O0 -nostdlib $^ -lgcc

./build/boot.o: ./src/boot/boot.asm
	nasm -f elf $< -o $@

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


./build/load_idt.o: ./src/idt/load_idt.asm
	nasm -f elf $< -o $@

./build/idt.o: ./src/idt/idt.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


./build/stdlib.o: ./src/stdlib/stdlib.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

./build/load_gdt.o: src/gdt/load_gdt.asm
	nasm -f elf -o $@ $<

./build/gdt.o: ./src/gdt/gdt.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


./build/handler.o: ./src/idt/handler.asm
	nasm -f elf -o $@ $<



./build/pic.o: ./src/pic/pic.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


./build/io.o: ./src/port-io/io.asm
	nasm -f elf -o $@ $<


./build/kheap.o: ./src/heap/kheap.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

./build/heap.o: ./src/heap/heap.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O0 -Wall -Wextra


./build/paging.o: ./src/paging/paging.c
	i686-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O0 -Wall -Wextra

./build/enable_paging.o: ./src/paging/enable_paging.asm
	nasm -f elf -g -o $@ $<


./build/ata.o: ./src/drivers/ata/ata.c
	i386-elf-gcc -g -c $< -o $@ -std=gnu99 -ffreestanding -O0 -Wall -Wextra

clean:
	rm -rf ./build/*
