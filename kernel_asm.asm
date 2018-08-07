bits 32

extern main
extern pit_ir

global start
global load_idt
global read_port
global write_port
global disable_interrupts
global enable_interrupts
global gen_interrupt
global get_pit_ticks
global set_pit_ticks
global inc_pit_ticks
global pit_ir_asm

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
	int 0x20
	ret

gen_interrupt:
	mov eax, [esp + 4]
	mov [.int + 1], al
.int:
	int 0
	ret

get_pit_ticks:
	mov eax, [pit_ticks]
	ret

set_pit_ticks:
	mov eax, [esp + 4]
	mov [pit_ticks], eax
	ret

inc_pit_ticks:
	mov eax, [pit_ticks]
	inc eax
	mov [pit_ticks], eax
	ret

pit_ir_asm:
	pushad
	call pit_ir
	popad
	iretd

pit_ticks times 4 db 0
