[bits 32]

main32:								; this is the entry point for pm
	mov si, welcome_to_pm
	call print_string_32

	jmp $							; endless loop

%include "x32/string.asm"

welcome_to_pm db "Welcome to protected mode", 0x0A, 0x0D, 0
