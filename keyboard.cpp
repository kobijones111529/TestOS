#include "keyboard.h"

unsigned int kb_events = 0;

void init_keyboard() {
	unmask(0x1);
	set_interrupt(0x21, 0x8, IDT_DESC_PRESENT | IDT_DESC_BIT32, (unsigned int)&(*keyboard_ir_asm));
}

void keyboard_ir() {
	kb_events++;
	eoi_request(0x1);
}
