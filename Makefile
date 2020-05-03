OS=myos
CC=/home/jona/bin/cross/bin/i686-elf-gcc
AS=/home/jona/bin/cross/bin/i686-elf-as

run: ${OS}.iso
	qemu-system-i386 -cdrom ${OS}.iso

iso: ${OS}.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp ${OS}.bin isodir/boot/${OS}.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ${OS}.iso isodir

link: boot.o kernel.o linker.ld
	${CC} -T linker.ld -o ${OS}.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

boot: boot.s
	${AS} boot.s -o boot.o

kernel: kernel.c
	${CC} -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
