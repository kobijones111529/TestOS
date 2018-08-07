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

unsigned char get_cursor_pos_x() {
	return get_cursor_pos() % COLUMNS;
}

unsigned char get_cursor_pos_y() {
	return get_cursor_pos() / COLUMNS;
}

void set_cursor_pos_low(unsigned char data) {
	write_port(0x3D4, 0x0F);
	write_port(0x3D5, data);
}

void set_cursor_pos_high(unsigned char data) {
	write_port(0x3D4, 0x0E);
	write_port(0x3D5, data);
}

void set_cursor_pos(unsigned short pos) {
	unsigned char low = pos & 0xFF;
	unsigned char high = (pos >> 0x8) & 0xFF;

	set_cursor_pos_low(low);
	set_cursor_pos_high(high);
}

void inc_cursor_pos() {
	set_cursor_pos(get_cursor_pos() + 1);
}

void dec_cursor_pos() {
	set_cursor_pos(get_cursor_pos() - 1);
}

void print_char(unsigned char c, unsigned char attribs) {
	unsigned short cursor_pos = get_cursor_pos();

	VGA[cursor_pos * 2] = c;
	VGA[cursor_pos * 2 + 1] = attribs;

	set_cursor_pos(cursor_pos + 1);
}

void print(const char* string, unsigned char attribs) {
	unsigned short pos = get_cursor_pos();
	while(*string) {
		print_char_at(*string, attribs, pos);
		string++;
		pos++;
	}

	set_cursor_pos(pos);
}

void print_int(unsigned int number, unsigned char radix, unsigned char attribs) {
	if(radix < 2 || radix > 16) {
		return;
	}

	char buffer[33];
	unsigned char startIndex = 0;

	for(int i = 0; i < 32; i++) {
		unsigned char c = number % radix;
		number /= radix;
		buffer[31 - i] = c;
	}
	while(!buffer[startIndex] && startIndex < 31) {
		startIndex++;
	}
	for(int i = startIndex; i < 32; i++) {
		if(buffer[i] < 0xA) {
			buffer[i] += '0';
		} else {
			buffer[i] -= 0xA;
			buffer[i] += 'A';
		}
	}

	print(&buffer[startIndex], attribs);
}

void print_char_at(unsigned char c, unsigned char attribs, unsigned short pos) {
	VGA[pos * 2] = c;
	VGA[pos * 2 + 1] = attribs;
}

void print_at(const char* string, unsigned char attribs, unsigned short pos) {
	while(*string) {
		print_char_at(*string, attribs, pos);
		string++;
		pos++;
	}

	set_cursor_pos(pos);
}

void print_int_at(unsigned int number, unsigned char radix, unsigned char attribs, unsigned short pos) {
	if(radix < 2 || radix > 16) {
		return;
	}

	char buffer[33];
	unsigned char startIndex = 0;

	for(int i = 0; i < 32; i++) {
		unsigned char c = number % radix;
		number /= radix;
		buffer[31 - i] = c;
	}
	while(!buffer[startIndex] && startIndex < 31) {
		startIndex++;
	}
	for(int i = startIndex; i < 32; i++) {
		if(buffer[i] < 0xA) {
			buffer[i] += '0';
		} else {
			buffer[i] -= 0xA;
			buffer[i] += 'A';
		}
	}

	print_at(&buffer[startIndex], attribs, pos);
}
