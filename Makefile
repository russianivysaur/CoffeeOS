all: ./build/os.bin
	dd bs=512 count=4 if=/dev/zero >> ./build/os.bin
	qemu-system-x86_64 -hda ./build/os.bin

./build/os.bin: ./build/boot.bin ./build/kernel.bin
	cat $^ > $@

./build/boot.bin: ./src/boot/boot.asm
	nasm -f bin $< -o $@

./build/kernel.bin: ./build/kernel.o ./build/kernel_start.o
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@

./build/kernel_start.o: ./src/kernel/kernel_start.asm
	nasm -f elf -o $@ $<
