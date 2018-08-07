#!/bin/bash

BOOT_0=boot0.asm
BOOT_1=boot1.asm
KERNEL=kernel.bin
KERNEL_ASM=kernel_asm.asm
SOURCE_FILES=(kernel_c.cpp hal.cpp idt.cpp pic.cpp pit.cpp keyboard.cpp print.cpp)
BOOT=boot.flp
VM="TestOS"

nasm -f bin $BOOT_0 -o ${BOOT_0/%.*/.bin}
nasm -f bin $BOOT_1 -o ${BOOT_1/%.*/.bin}

nasm -f elf32 $KERNEL_ASM -o ${KERNEL_ASM/%.*/.o}
for i in ${SOURCE_FILES[@]}; do
	g++ -Wall -g -ffreestanding -m32 -c $i -o ${i%.*}.o
done
ld -T link.ld -m elf_i386 --oformat binary ${KERNEL_ASM/%.*/.o} $(IFS=$' '; printf "${SOURCE_FILES[*]/%.*/.o}") -o $KERNEL

if [ -f ${KERNEL_ASM/%.*/.o} ]; then
	rm ${KERNEL_ASM/%.*/.o}
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
dd if=${BOOT_0/%.*/.bin} of=$BOOT bs=512 count=1 seek=0 conv=notrunc
dd if=${BOOT_1/%.*/.bin} of=$BOOT bs=512 count=1 seek=1 conv=notrunc
dd if=$KERNEL of=$BOOT bs=512 count=16 seek=2 conv=notrunc

if [ -f ${BOOT_0/%.*/.bin} ]; then
	rm ${BOOT_0/%.*/.bin}
fi
if [ -f ${BOOT_1/%.*/.bin} ]; then
	rm ${BOOT_1/%.*/.bin}
fi
if [ -f $KERNEL ]; then
	rm $KERNEL
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
