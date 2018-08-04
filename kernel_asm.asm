bits 32

extern main

global start
global load_idt
global read_port
global write_port

start:
	call main
	jmp $

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret

read_port:
	mov dx, [esp + 4]
	in al, dx
	ret

write_port:
	mov dx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	ret
