#ifndef _PIT_H
#define _PIT_H

#define PIT_FREQUENCY 1193180
#define PIT_COUNTER0_PORT 0x40
#define PIT_COUNTER1_PORT 0x41
#define PIT_COUNTER2_PORT 0x42
#define PIT_COMMAND_PORT 0x43

#include "idt.h"
#include "port_io.h"

static unsigned int pit_ticks = 0;

extern void init_pit();

#endif
