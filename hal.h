#ifndef _HAL_H
#define _HAL_H

#include "idt.h"
#include "pic.h"
#include "pit.h"

//assembly functions
extern "C" void disable_interrupts();
extern "C" void enable_interrupts();
extern "C" void gen_interrupt(unsigned char i);

extern void init_hal();

#endif
