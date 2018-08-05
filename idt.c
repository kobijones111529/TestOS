#include "idt.h"

//assembly functions
extern void load_idt(unsigned int ptr);

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

static struct idt_desc idt[MAX_INTERRUPTS];
static struct idt_ptr idtr;

static void default_ir() {
	print("Unhandled interrupt!", 0x0F);
	//for(;;);
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
		set_interrupt(i, 0x8, IDT_DESC_PRESENT | IDT_DESC_BIT32, (unsigned int)&(*default_ir));
	}

	idtr.limit = sizeof(struct idt_desc) * MAX_INTERRUPTS - 1;
	idtr.base = (unsigned int)&idt[0];
	load_idt((unsigned int)&idtr);
}
