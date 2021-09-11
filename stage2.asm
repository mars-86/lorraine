[bits 16]
[org 0x0000]

main:
	mov ax, cs
	mov ds, ax
	
	cli				; clear interrupts
	xor	ax, ax			; null segments
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x9000		; stack begins at 0x9000-0xffff
	mov	ss, ax
	mov	sp, 0xFFFF
	sti

	mov si, stage2_message
	call print_string_16
	
	call gdt_load			; load gdt
	
	cli
	mov eax, cr0					; mov cr0 register to eax
	or	eax, 0x1					; set first bit
	mov cr0, eax					; copy modified data so we can enter to pm
	
	jmp CODE_SEGMENT:enter_pm		; far jmp to 32 bits area, that way the cpu will clear the pipeline

enter_pm:
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp , 0x90000 				; Update our stack position so it is right
	mov esp , ebp 					; at the top of the free space.
	
	jmp main32

%include "x16/string.asm"
%include "x16/gdt.asm"
%include "x32/main32.asm"

stage2_message db "Entering stage 2...", 0
