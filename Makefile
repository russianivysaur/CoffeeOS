build:
	nasm -f bin boot.asm -o boot.bin
	dd if=disk.txt >> boot.bin
	dd if=/dev/zero bs=512 count=1 >> boot.bin
