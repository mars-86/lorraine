[bits 16]
[org 0x0000]

jmp stage2

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/string.asm"
%include "x32/string.asm"
%include "x16/gdt.asm"
; %include "x32/main32.asm"

;*******************************************************
;	Data section
;*******************************************************

stage2_message db "Entering stage 2...", 0x0A, 0x0D, 0
welcome_to_protected_mode db "Welcome to protected mode!", 0x0A, 0x0D, 0


stage2:
	cli
	push cs
	pop ds
	
	mov si, stage2_message
	call print_string_16

	cli					; clear interrupts
	xor	ax, ax			; null segments
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x9000		; stack begins at 0x9000-0xffff
	mov	ss, ax
	mov	sp, 0xFFFF
	sti
	
	call gdt_load			; load gdt
	
	mov al, 2
    out 0x92, al

	cli
	mov eax, cr0					; mov cr0 register to eax
	or	eax, 0x1					; set first bit
	mov cr0, eax					; copy modified data so we can enter to pm

	jmp 0x08:enter_pm		; far jmp to 32 bits area, that way the cpu will clear the pipeline

[bits 32]

enter_pm:
	mov     ax, 0x10        ; set data segments to data selector (0x10)
    mov     ds, ax
    mov     ss, ax
    mov     es, ax
    mov     esp, 90000h     ; stack begins from 90000h

	mov si, welcome_to_protected_mode
	call string_print_32

	hlt
