#!/bin/bash

BOOT_STAGE_0=boot0
BOOT_STAGE_1=boot1
KERNEL=kernel
KERNEL_ASM=kernel_asm
KERNEL_C=kernel_c
SOURCE_FILES=(hal.c)
BOOT=boot.flp
VM="TestOS"

nasm -f bin $BOOT_STAGE_0.asm -o $BOOT_STAGE_0.bin
nasm -f bin $BOOT_STAGE_1.asm -o $BOOT_STAGE_1.bin

nasm -f elf32 $KERNEL_ASM.asm -o $KERNEL_ASM.o
gcc -Wall -g -ffreestanding -m32 -c ${SOURCE_FILES[*]} -o ${SOURCE_FILES[*]%.*}.o
gcc -Wall -g -ffreestanding -m32 -c $KERNEL_C.c
ld -T link.ld -m elf_i386 --oformat binary $KERNEL_ASM.o $KERNEL_C.o ${SOURCE_FILES[*]%.*}.o -o $KERNEL.bin

if [ -f $KERNEL_ASM.o ]; then
	rm $KERNEL_ASM.o
fi
if [ -f $KERNEL_C.o ]; then
	rm $KERNEL_C.o
fi

for i in ${SOURCE_FILES[@]}; do
	if [ -f ${i%.*}.o ]; then
		rm ${i%.*}.o
	fi
done

if [ -f $BOOT ]; then
	rm $BOOT
fi

dd if=/dev/zero of=$BOOT bs=512 count=2880
dd if=$BOOT_STAGE_0.bin of=$BOOT bs=512 count=1 seek=0 conv=notrunc
dd if=$BOOT_STAGE_1.bin of=$BOOT bs=512 count=1 seek=1 conv=notrunc
#dd if=$KERNEL_ASM.bin of=$BOOT bs=512 count=1 seek=2 conv=notrunc
dd if=$KERNEL.bin of=$BOOT bs=512 count=3 seek=2 conv=notrunc

if [ -f $BOOT_STAGE_0.bin ]; then
	rm $BOOT_STAGE_0.bin
fi
if [ -f $BOOT_STAGE_1.bin ]; then
	rm $BOOT_STAGE_1.bin
fi
if [ -f $KERNEL.bin ]; then
	rm $KERNEL.bin
fi

if [ ! -f $BOOT ]; then
	exit 1
fi

printf "\nWould you like to boot? : "
read RUN
RUN=$(printf "$RUN" | tr "[:upper:]" "[:lower:]")
printf "\n"

if [ "$RUN" != "y" ] && [ "$RUN" != "yes" ]; then
	exit 0
fi

#VBoxManage startvm $VM --type gui
qemu-system-i386 -drive file=$BOOT,format=raw
