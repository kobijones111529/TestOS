#ifndef _HAL_H
#define _HAL_H

#include "idt.h"

//assembly functions
extern short read_port(unsigned short port);
extern char write_port(unsigned short port, unsigned char data);

extern void init_hal();

#endif
