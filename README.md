Requirements : 
1. make
2. i686-elf-gcc
3. i686-elf-as
4. nasm
5. qemu-system

Run these commands for a iso file :

-> ./build.sh


You might also want to make a fat16 virtual disk for the file system modules of the os, to create one just create a file named fat16.img and use mkfs.fat to write a FAT fs into it.


...............................

You can also download the iso from [here.](https://github.com/russianivysaur/CoffeeOS/releases/download/prebuilt/coffee.iso)
