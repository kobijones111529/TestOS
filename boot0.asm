bits 16
org 0x7C00

start:
	cli
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00
	sti

	mov [DISK], dl

	mov ah, 0x00
	int 0x13

	mov bx, 0x7E00 ;buffer address pointer
	mov ah, 0x02   ;int 0x13 read from drive
	mov al, 1   ;sectors to read count
	mov ch, 0x00   ;cylinder
	mov cl, 0x02   ;sector
	mov dh, 0x00   ;head
	mov dl, [DISK] ;drive
	int 0x13
	jc disk_read_error
	or al, al
	jz disk_read_error

	mov bx, 0x1000 ;buffer address pointer
	mov ah, 0x02   ;int 0x13 read from drive
	mov al, 17   ;sectors to read count
	mov ch, 0x00   ;cylinder
	mov cl, 0x03   ;sector
	mov dh, 0x00   ;head
	mov dl, [DISK] ;drive
	int 0x13
	jc disk_read_error
	or al, al
	jz disk_read_error

	jmp 0x7E00
	jmp $

disk_read_error:
	mov si, DISK_READ_ERROR_MESSAGE
	call print_rm
	jmp $

DISK db 0
DISK_READ_ERROR_MESSAGE db 'Disk read error!', 0

%include "./print_rm.asm"

times 510 - ($ - $$) db 0x00
dw 0xAA55
