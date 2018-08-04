#include "hal.h"

unsigned char* vga;
unsigned short cursor_pos;

unsigned char get_cursor_pos_low() {
	write_port(0x3D4, 0x0F);
	return read_port(0x3D5);
}

unsigned char get_cursor_pos_high() {
	write_port(0x3D4, 0x0E);
	return read_port(0x3D5);
}

unsigned short get_cursor_pos() {
	unsigned short low = get_cursor_pos_low();
	unsigned short high = get_cursor_pos_high();
	
	return low | (high << 0x8);
}

void set_cursor_pos_low(unsigned char data) {
	write_port(0x3D4, 0x0F);
	write_port(0x3D5, data);
}

void set_cursor_pos_high(unsigned char data) {
	write_port(0x3D4, 0x0E);
	write_port(0x3D5, data);
}

void set_cursor_pos(unsigned short data) {
	unsigned char low = data & 0xFF;
	unsigned char high = (data >> 0x8) & 0xFF;
	
	set_cursor_pos_low(low);
	set_cursor_pos_high(high);
}

void put_char(unsigned char c, unsigned char attribs) {
	unsigned int index = cursor_pos * 2;
	vga[index] = c;
	vga[index + 1] = attribs;
	cursor_pos += 1;
	set_cursor_pos(cursor_pos);
}

void print(char* string, unsigned char attribs) {
	while(*string != 0) {
		put_char(*string, attribs);
		string++;
	}
}

int new_idt_entry(unsigned char i, unsigned char flags, unsigned char selector, unsigned int ir) {
	unsigned short base_low = ir & 0xFFFF;
	unsigned short base_high = (ir >> 0x10) & 0xFFFF;
	
	idt[i].base_low = base_low;
	idt[i].selector = 0x08;
	idt[i].zero = 0x00;
	idt[i].flags = 0x8E;
	idt[i].base_high = base_high;
	
	return 0;
}

void default_ir() {
	print("Unhandled interrupt!", 0x0F);
	for(;;);
}

void init_idt() {
	for(int i = 0; i < 256; i++) {
		new_idt_entry(i, 0x8E, 0x8, (unsigned int)&(*default_ir));
	}
	
	ptr.limit = 2048;
	ptr.base = &idt[0];
	load_idt(&ptr);
}

void init_pic() {
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
}

void eoi_request() {
	write_port(0x20, 0x20);
}

void main(void) {
	init_idt();
	init_pic();
	
	init_hal();
	
	vga = (unsigned char*)0xB8000;
	cursor_pos = get_cursor_pos();
	set_cursor_pos(cursor_pos);
	
	char string[] = "Hello!";
	print(&string[0], 0x0F);
}
