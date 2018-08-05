#ifndef _PIC_H
#define _PIC_H

#include "port_io.h"

#define PIC1_COMMAND_PORT 0x20
#define PIC1_STATUS_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC1_IMR_PORT 0x21

#define PIC2_COMMAND_PORT 0xA0
#define PIC2_STATUS_PORT 0xA0
#define PIC2_DATA_PORT 0xA1
#define PIC2_IMR_PORT 0xA1

#define PIC_EOI 0x20

extern void init_pic();

#endif
