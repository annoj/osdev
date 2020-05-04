OS=redstar
CC=/home/jona/bin/cross/bin/i686-elf-gcc
AS=/home/jona/bin/cross/bin/i686-elf-as

run: iso
	qemu-system-i386 -cdrom ${OS}.iso

iso: link grub.cfg
	mkdir -p isodir/boot/grub
	cp ${OS}.bin isodir/boot/${OS}.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ${OS}.iso isodir

link: boot kernel kernel/arch/i368/linker.ld
	${CC} -T kernel/arch/i368/linker.ld -o ${OS}.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

boot: kernel/arch/i368/boot.s
	${AS} kernel/arch/i368/boot.s -o boot.o

kernel: kernel/kernel/kernel.c
	${CC} -c kernel/kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
