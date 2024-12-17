all: ./build/coffee.iso

./build/coffee.iso: ./build/boot.o ./build/kernel.o ./build/idt.o ./build/load_idt.o ./build/interrupt.o ./build/stdlib.o
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

./build/boot.o: ./src/boot/boot.s
	i686-elf-as $< -o $@

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


./build/load_idt.o: ./src/idt/load_idt.asm
	nasm -f elf $< -o $@

./build/idt.o: ./src/idt/idt.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

./build/interrupt.o: ./src/kernel/interrupt.asm
	nasm -f elf $< -o $@


./build/stdlib.o: ./src/stdlib/memset.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -rf ./build/*
