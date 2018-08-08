#include "hal.h"

void init_hal() {
	init_idt();
	init_pic();
	//init_pit();
	init_keyboard();
	enable_interrupts();
}
