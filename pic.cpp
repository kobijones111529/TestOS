#include "pic.h"

void init_pic() {
	//initialization control word 1
	//00010001: enable icw4, set initialization
	write_port(PIC1_COMMAND_PORT, 0x11);
	write_port(PIC2_COMMAND_PORT, 0x11);

	//icw 2
	//map to interrupts 0x20-0x2F (32-48)
	write_port(PIC1_DATA_PORT, 0x20);
	write_port(PIC2_DATA_PORT, 0x28);

	//icw 3
	//ir2 connets pics
	write_port(PIC1_DATA_PORT, 0x4); //second bit
	write_port(PIC2_DATA_PORT, 0x2);

	//icw 4
	//enable 80x86 mode
	write_port(PIC1_DATA_PORT, 0x1);
	write_port(PIC2_DATA_PORT, 0x1);
}

void eoi_request(unsigned char i) {
	if(i > 0xF) {
		return;
	} else if(i > 0x7) {
		write_port(PIC2_COMMAND_PORT, PIC_EOI);
	}

	write_port(PIC1_COMMAND_PORT, PIC_EOI);
}
