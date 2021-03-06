bits 32

extern main
extern pit_ir
extern keyboard_ir
extern kb_events

global start
global load_idt
global read_port
global write_port
global disable_interrupts
global enable_interrupts
global gen_interrupt
global halt
global pit_ir_asm
global keyboard_ir_asm

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

disable_interrupts:
	cli
	ret

enable_interrupts:
	sti
	ret

gen_interrupt:
	mov eax, [esp + 4]
	mov [.int + 1], al
.int:
	int 0
	ret

pit_ir_asm:
	pushad
	call pit_ir
	popad
	iretd

keyboard_ir_asm:
	pushad
	call keyboard_ir
	popad
	iretd
