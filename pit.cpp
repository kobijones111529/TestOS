#include "pit.h"

unsigned int pit_ticks = 0;

void pit_ir() {
	pit_ticks++;
	eoi_request(0x0);
}

void init_pit() {
	//command word
	//binary counting, mode 3, read/load lsb then msb, channel 0
	write_port(0x43, 0x36);

	//load counter
	unsigned short count = PIT_FREQUENCY / 100;
	write_port(0x40, count & 0xFF);
	write_port(0x40, (count >> 0x8) & 0xFF);

	unmask(0x0);
	set_interrupt(0x20, 0x8, IDT_DESC_PRESENT | IDT_DESC_BIT32, (unsigned int)&(*pit_ir_asm));
}
