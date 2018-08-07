#include "idt.h"

struct idt_desc {
	unsigned short base_low;
	unsigned short selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_desc idt[MAX_INTERRUPTS];
struct idt_ptr idtr;

void default_ir() {
	print("Unhandled interrupt!", 0x0F);
	for(;;);
}

void ir0() {
	print("Unhandled interrupt 0!", 0x0F);
	for(;;);
}

void set_interrupt(unsigned char i, unsigned short selector, unsigned char flags, unsigned int ir_ptr) {
	idt[i].base_low = ir_ptr & 0xFFFF;
	idt[i].selector = selector;
	idt[i].zero = 0x00;
	idt[i].flags = flags;
	idt[i].base_high = (ir_ptr >> 0x10) & 0xFFFF;
}

void init_idt() {
	for(unsigned int i = 0; i < MAX_INTERRUPTS; i++) {
		if(i == 0x20) {
			set_interrupt(i, 0x8, IDT_DESC_PRESENT | IDT_DESC_BIT32, (unsigned int)&(*ir0));
		} else {
			set_interrupt(i, 0x8, IDT_DESC_PRESENT | IDT_DESC_BIT32, (unsigned int)&(*default_ir));
		}
	}

	idtr.limit = sizeof(struct idt_desc) * MAX_INTERRUPTS - 1;
	idtr.base = (unsigned int)&idt[0];
	load_idt((unsigned int)&idtr);
}
