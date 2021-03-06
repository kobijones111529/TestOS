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

extern unsigned int pit_ticks;

//assembly functions
extern "C" void gen_interrupt(unsigned char i);
extern "C" void pit_ir_asm();

extern void init_pit();
extern "C" void pit_ir();

#endif
