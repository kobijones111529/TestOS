#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "print.h"

extern unsigned int kb_events;

extern "C" void keyboard_ir_asm();

extern void init_keyboard();
extern "C" void keyboard_ir();

#endif
