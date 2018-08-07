#ifndef _PRINT_H
#define _PRINT_H

#include "port_io.h"

#define VGA     0xB8000
#define COLUMNS 80
#define ROWS    25

extern unsigned short get_cursor_pos();
extern void set_cursor_pos(unsigned short pos);
extern void inc_cursor_pos();
extern void dec_cursor_pos();

extern void print_char(unsigned char c, unsigned char attribs);
extern void print(char* string, unsigned char attribs);
extern void print_int(unsigned int number, unsigned char radix, unsigned char attribs);
extern void print_char_at(unsigned char c, unsigned char attribs, unsigned short pos);
extern void print_at(char* string, unsigned char attribs, unsigned short pos);
extern void print_int_at(unsigned int number, unsigned char radix, unsigned char attribs, unsigned short pos);

#endif
