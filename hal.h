#ifndef _HAL_H
#define _HAL_H

#include "idt.h"
#include "pic.h"
#include "pit.h"

//assembly functions
extern void disable_interrupts();
extern void enable_interrupts();
extern void gen_interrupt(unsigned char i);

extern void init_hal();

#endif
