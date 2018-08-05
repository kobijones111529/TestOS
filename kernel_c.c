#include "hal.h"
#include "print.h"

extern void get_cpu_vendor_id(unsigned int ptr);

/*void init_pic() {
	//initialization control word 1
	write_port(0x20, 0x11);
	write_port(0xA0, 0x11);

	//icw 2: irq lines 0x20-0x2F
	write_port(0x21, 0x20);
	write_port(0xA1, 0x28);

	//icw 3: irq line 2
	write_port(0x21, 0x4); //second bit (0100)
	write_port(0xA1, 0x2);

	//icw 4
	write_port(0x21, 0x1);
	write_port(0xA1, 0x1);

	//clear data registers
	write_port(0x21, 0x0);
	write_port(0xA1, 0x0);
}*/

void divide_by_0_fault() {
	print("Divide by 0!", 0xB);
}

void main(void) {
	init_hal();

	char* hello = "Hello! ";
	print(hello, 0x0F);

	char c = 0;
	unsigned char* vga = (unsigned char*)0xB8000;
	for(;;) {
		c = pit_ticks % 26 + 'a';
		vga[0] = c;
		vga[1] = 0x0F;
	}
}
