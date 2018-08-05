#include "hal.h"

void init_hal() {
	init_idt();
	init_pic();
	enable_interrupts();
}

void eoi_request(unsigned char i) {
	if(i > 0xF) {
		return;
	} else if(i > 0x7) {
		write_port(PIC2_COMMAND_PORT, PIC_EOI);
	}

	write_port(PIC1_COMMAND_PORT, PIC_EOI);
}
