all: ./build/os.iso
	dd bs=512 count=100 if=/dev/zero >> ./build/os.iso
	qemu-system-x86_64 -hda ./build/os.iso

./build/os.iso: ./build/boot.bin ./build/kernel.bin
	cat $^ > $@

./build/boot.bin: ./src/boot/boot.asm
	nasm $< -f bin -o $@

./build/kernel.bin: ./build/kernel.o ./build/printing_utils.o ./build/kernel_start.o
	i686-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@

./build/printing_utils.o: ./src/kernel/printing_utils.c
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@

./build/kernel_start.o: ./src/kernel/kernel_start.asm
	nasm $< -f elf -o $@


clean:
	rm ./build/*
