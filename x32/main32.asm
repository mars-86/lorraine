[bits 32]

main32:								; this is the entry point for pm
	mov si, welcome_to_pm
	; call string_print_32

	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp , 0x90000 				; Update our stack position so it is right
	mov esp , ebp 					; at the top of the free space.

	mov si, welcome_to_pm
	; call string_print_32
	
	hlt

	mov si, welcome_to_pm
	; call string_print_32

	jmp $							; endless loop

%include "x32/string.asm"

welcome_to_pm db "Welcome to protected mode", 0x0A, 0x0D, 0
