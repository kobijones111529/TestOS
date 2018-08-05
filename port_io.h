#ifndef _PORT_IO_H
#define _PORT_IO_H

//assembly functions
extern short read_port(unsigned short port);
extern char write_port(unsigned short port, unsigned char data);

#endif
