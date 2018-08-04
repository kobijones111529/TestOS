print_rm:
	pusha
.print_rm_loop:
	lodsb
	or al, al
	jz .print_rm_done
	mov ah, 0x0E
	int 0x10
	
	jmp .print_rm_loop
.print_rm_done:
	popa
	ret