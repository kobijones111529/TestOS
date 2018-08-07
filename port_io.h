#ifndef _PORT_IO_H
#define _PORT_IO_H

//assembly functions
extern "C" short read_port(unsigned short port);
extern "C" char write_port(unsigned short port, unsigned char data);

#endif
