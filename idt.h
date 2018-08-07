#ifndef _IDT_H
#define _IDT_H

#include "print.h"

#define MAX_INTERRUPTS 0x100
#define IDT_DESC_BIT16 0x06
#define IDT_DESC_BIT32 0x0E
#define IDT_DESC_RING1 0x40
#define IDT_DESC_RING2 0x20
#define IDT_DESC_RING3 0x60
#define IDT_DESC_PRESENT 0x80

//assembly functions
extern void load_idt(unsigned int ptr);

extern void init_idt();
extern void set_interrupt(unsigned char i, unsigned short selector, unsigned char flags, unsigned int ir_ptr);

#endif
