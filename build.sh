make clean
make all
mkdir -p isodir/boot/grub
cp ./build/coffee.iso isodir/boot/coffee.iso
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ./build/coffee.iso isodir
rm -rf isodir
