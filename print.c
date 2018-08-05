#include "print.h"

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

void print_char(unsigned char c, unsigned char attribs) {
	unsigned short cursor_pos = get_cursor_pos();

	unsigned char* vga = (unsigned char*)VGA;
	vga[cursor_pos * 2] = c;
	vga[cursor_pos * 2 + 1] = attribs;

	set_cursor_pos(cursor_pos + 1);
}

void print(char* string, unsigned char attribs) {
	while(*string) {
		print_char(*string, attribs);
		string++;
	}
}

void print_number(unsigned int number, unsigned char attribs) {
	//char string[11];
	for(int i = 0; i < 8; i++) {
		//string[10 - i - 1] = '0' + number % 10;
		//number /= 10;

		unsigned char c = (number >> 0x1C) & 0xF;
		if(c < 0xA) {
			c += '0';
		} else {
			c += 'A' - 0xA;
		}
		print_char(c, 0x0F);
		number = number << 0x4;
	}
	//print(&string[0], attribs);
}
