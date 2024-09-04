FILES = bin/boot.bin
all: $(FILES)
	rm -rf bin/os.bin
	dd if=bin/boot.bin >> bin/os.bin

bin/boot.bin: src/boot/boot.asm
	nasm -f bin src/boot/boot.asm -o bin/boot.bin

clean:
	rm -rf bin/*
	rm -rf build/*