bits 16
org 0x7E00

cli
lgdt [gdt_ptr]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp 0x8:init_pm

gdt:
gdt_null:
	times 8 db 0x00
gdt_code:
	dw 0xFFFF ;limit low
	dw 0x0000 ;base low
	db 0x00   ;base middle
	db 0x9A   ;access byte
	db 0xCF   ;limit high, flags
	db 0x00   ;base high
gdt_data:
	dw 0xFFFF ;limit
	dw 0x0000 ;base low
	db 0x00   ;base middle
	db 0x92   ;access byte
	db 0xCF   ;limit high, flags
	db 0x00   ;base high
gdt_ptr:
	dw $ - gdt - 1
	dd gdt

bits 32

init_pm:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	mov ebp, 0x7C00
	mov esp, ebp
	
	mov al, 2
	out 0x92, al
	
	jmp 0x8:0x1000
	jmp $
	
clear_screen:
	mov esi, 2000
.loop:
	dec esi
	mov ah, 0x0F
	mov al, ' '
	mov [0xB8000 + esi * 2], ax
	or esi, esi
	jnz .loop
	ret
