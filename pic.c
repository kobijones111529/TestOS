#include "pic.h"

void init_pic() {
	//initialization control word 1
	//00010001: enable ic4, set initialization
	write_port(PIC1_COMMAND_PORT, 0x11);
	write_port(PIC2_COMMAND_PORT, 0x11);

	//icw 2
	//map to interrupts 0x20-0x2F (32-48)
	write_port(PIC1_DATA_PORT, 0x20);
	write_port(PIC2_DATA_PORT, 0x28);

	//icw 3
	//irq line 2 connets pics
	write_port(PIC1_DATA_PORT, 0x4); //second bit
	write_port(PIC2_DATA_PORT, 0x2);

	//icw 4
	//enable 80x86 mode
	write_port(PIC1_DATA_PORT, 0x1);
	write_port(PIC2_DATA_PORT, 0x1);

	//clear data registers
	write_port(PIC1_DATA_PORT, 0x0);
	write_port(PIC2_DATA_PORT, 0x0);
}
