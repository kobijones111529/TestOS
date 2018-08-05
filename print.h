#ifndef _PRINT_H
#define _PRINT_H

#include "port_io.h"

#define VGA     0xB8000
#define COLUMNS 80
#define ROWS    25

extern void print_char(unsigned char c, unsigned char attribs);
extern void print(char* string, unsigned char attribs);
extern void print_number(unsigned int number, unsigned char attribs);

#endif
