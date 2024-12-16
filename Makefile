all: ./build/coffee.iso
	dd bs=512 count=10 if=/dev/zero >> $<

./build/coffee.iso: ./build/boot.bin ./build/kernel.bin
	cat $^ > $@

./build/boot.bin: ./src/boot/boot.asm
	nasm -f bin -o $@ $<

./build/kernel.bin: ./build/kernel.o
	i686-elf-ld -m elf_i386 -T linker.ld -g -o $@ $^

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc -nostdlib -m32 -ffreestanding -c -g -o $@ $<

clean:
	rm ./build/*
