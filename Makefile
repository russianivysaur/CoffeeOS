all: ./build/coffee.iso

./build/coffee.iso: ./build/boot.o ./build/kernel.o
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

./build/boot.o: ./src/boot/boot.s
	i686-elf-as $< -o $@

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -rf ./build/*
