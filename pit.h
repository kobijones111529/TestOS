#ifndef _PIT_H
#define _PIT_H

#define PIT_COUNTER0_PORT 0x40
#define PIT_COUNTER1_PORT 0x41
#define PIT_COUNTER2_PORT 0x42
#define PIT_COMMAND_PORT 0x43
#define PIT_FREQUENCY 1193180

#include "idt.h"
#include "port_io.h"
#include "pic.h"

//assembly functions
extern void gen_interrupt(unsigned char i);
extern void pit_ir_asm();
extern unsigned int get_pit_ticks();
extern void set_pit_ticks(unsigned int ticks);

extern void init_pit();

#endif
