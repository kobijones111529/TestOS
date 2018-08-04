#ifndef _IDT_H
#define _IDT_H

struct idt_entry {
	unsigned short base_low;
	unsigned short selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));

struct idtr {
	unsigned short limit;
	void* base;
} __attribute__((packed));

struct idt_entry idt[256];
//struct idtr ptr;

//assembly functions
extern void load_idt(void* ptr);

extern void init_idt();

#endif
