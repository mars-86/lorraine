%ifndef __GDT_ASM_INCLUDED__
%define __GDT_ASM_INCLUDED__

[bits 16]

gdt_load:
	pusha
	cli
	lgdt [gdt_descriptor]
	sti
	popa
	ret

gdt_start:

gdt_null:								; we fill all the first descriptor with 0
	dd 0x0								; first 4 bytes
	dd 0x0								; last 4 bytes

gdt_code:
	dw 0xffff							; limit (bits 0 - 15)
	dw 0x0								; base (bits 0 - 15)
	db 0x0								; base (bits 16 - 23)
	db 10011010b						; 1st flags
	db 11001111b						; 2nd flags
	db 0x0								; base (bits 24 - 31)

gdt_data:
	dw 0xffff							; limit (bits 0 - 15)
	dw 0x0								; base (bits 0 - 15)
	db 0x0								; base (bits 16 -23)
	db 10010010b						; 1st flags
	db 11001111b						; 2nd flags
	db 0x0								; base (bits 24 - 31)

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1 			; gdt size
	dd gdt_start						; start address of gdt
	
CODE_SEGMENT equ gdt_code - gdt_start	; code segment offset
DATA_SEGMENT equ gdt_data - gdt_start	; data segment offset

%endif 									; __GDT_ASM_INCLUDED__