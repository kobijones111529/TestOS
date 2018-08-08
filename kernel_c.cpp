#include "kernel_c.h"

void divide_by_0_fault() {
	print("divide_by_0_fault", 0x0F);
	for(;;);
}
void single_step_trap() {
	print("single_step_trap", 0x0F);
	for(;;);
}
void nmi_trap() {
	print("nmi_trap", 0x0F);
	for(;;);
}
void breakpoint_trap() {
	print("breakpoint_trap", 0x0F);
	for(;;);
}
void overflow_trap() {
	print("overflow_trap", 0x0F);
	for(;;);
}
void bounds_check_fault() {
	print("bounds_check_fault", 0x0F);
	for(;;);
}
void invalid_opcode_fault() {
	print("invalid_opcode_fault", 0x0F);
	for(;;);
}
void no_device_fault() {
	print("no_device_fault", 0x0F);
	for(;;);
}
void double_fault_abort() {
	print("double_fault_abort", 0x0F);
	for(;;);
}
void invalid_tss_fault() {
	print("invalid_tss_fault", 0x0F);
	for(;;);
}
void no_segment_fault() {
	print("no_segment_fault", 0x0F);
	for(;;);
}
void stack_fault() {
	print("stack_fault", 0x0F);
	for(;;);
}
void general_protection_fault() {
	print("general_protection_fault", 0x0F);
	for(;;);
}
void page_fault() {
	print("page_fault", 0x0F);
	for(;;);
}
void fpu_fault() {
	print("fpu_fault", 0x0F);
	for(;;);
}
void alignment_check_fault() {
	print("alignment_check_fault", 0x0F);
	for(;;);
}
void machine_check_abort() {
	print("machine_check_abort", 0x0F);
	for(;;);
}
void simd_fpu_fault() {
	print("simd_fpu_fault", 0x0F);
	for(;;);
}

void main(void) {
	init_hal();

	set_interrupt(0, 0x8, 0x8E, (unsigned int)&(*divide_by_0_fault));
	set_interrupt(1, 0x8, 0x8E, (unsigned int)&(*single_step_trap));
	set_interrupt(2, 0x8, 0x8E, (unsigned int)&(*nmi_trap));
	set_interrupt(3, 0x8, 0x8E, (unsigned int)&(*breakpoint_trap));
	set_interrupt(4, 0x8, 0x8E, (unsigned int)&(*overflow_trap));
	set_interrupt(5, 0x8, 0x8E, (unsigned int)&(*bounds_check_fault));
	set_interrupt(6, 0x8, 0x8E, (unsigned int)&(*invalid_opcode_fault));
	set_interrupt(7, 0x8, 0x8E, (unsigned int)&(*no_device_fault));
	set_interrupt(8, 0x8, 0x8E, (unsigned int)&(*double_fault_abort));
	set_interrupt(10, 0x8, 0x8E, (unsigned int)&(*invalid_tss_fault));
	set_interrupt(11, 0x8, 0x8E, (unsigned int)&(*no_segment_fault));
	set_interrupt(12, 0x8, 0x8E, (unsigned int)&(*stack_fault));
	set_interrupt(13, 0x8, 0x8E, (unsigned int)&(*general_protection_fault));
	set_interrupt(14, 0x8, 0x8E, (unsigned int)&(*page_fault));
	set_interrupt(16, 0x8, 0x8E, (unsigned int)&(*fpu_fault));
	set_interrupt(17, 0x8, 0x8E, (unsigned int)&(*alignment_check_fault));
	set_interrupt(18, 0x8, 0x8E, (unsigned int)&(*machine_check_abort));
	set_interrupt(19, 0x8, 0x8E, (unsigned int)&(*simd_fpu_fault));

	unsigned short pos = get_cursor_pos();

	for(;;) {
		print_int_at(kb_events, 10, 0x0F, pos);
	}

	//print("Hi!", 0x0F);

	for(unsigned int counter = 2;; counter++) {
		unsigned int prime = 1;
		for(unsigned int checker = 2;; checker++) {
			if(checker * checker > counter) {
				break;
			} else if(counter % checker == 0) {
				prime = 0;
				break;
			}
		}

		if(prime) {
			unsigned int timerStart = pit_ticks;
			set_cursor_pos(pos);
			print_int_at(counter, 10, 0x0F, pos);
			for(; pit_ticks - timerStart < 100;);
		}
	}
}
