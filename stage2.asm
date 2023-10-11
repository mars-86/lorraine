[bits 16]
[org 0x7300]								; Jump was 0x050:0x7300 so ORG = Offset = 0x7300.

jmp stage2

print_string:
	push ax
	push si
	mov ah, 0x0E
	.repeat:
		mov al, [si]
		cmp al, 0
		je .end
		int 0x10
		inc si
		jmp .repeat
	.end:
	pop si
	pop ax
	ret

choose_option:
	mov ah, 0x00
	int 0x16
	mov ah, 0x0A
	mov bh, 0x00
	mov bl, 0x00
	mov cx, 0x01
	int 0x10
	ret

reset_floppy:                				; Resets floppy
    xor ax, ax         						; AH = 0 = Reset floppy disk
    int 0x13
    jc reset_floppy
	ret

read_into_mem_retries dw 3

read_to_mem:
	mov ah, 0x02
	int 0x13
	ret
	call print_string
	push bx
	mov bx, [read_into_mem_retries]
	dec bx
	or bx, bx
	jmp stage2_error
	mov [read_into_mem_retries], bx
	pop bx
	jmp read_to_mem


;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/gdt.asm"
%include "x16/lib/string.inc"

;*******************************************************
;	Data section
;*******************************************************

stage2_msg db "Entering stage 2...", 0x0A, 0x0D, 0
stage2_msg_len equ $ - stage2_msg
opt_msg db \
			"Select an option", 0x0A, 0x0D, \
			"    1. Real Mode", 0x0A, 0x0D, \
			"    2. Real Mode (Extended)", 0x0A, 0x0D, \
			"    3. Protected Mode (32bits)", 0x0A, 0x0D, \
			"    4.", 0x0A, 0x0D, \
			0x0A, 0x0D, 0
opt_sel_msg db "Option: ", 0
opt_invalid_msg db "Invalid option", 0x0A, 0x0D, 0
opt_invalid_msg_len equ $ - opt_invalid_msg
message_read_into_mem db 'Loading kernel...', 0x0A, 0x0D, 0
message_read_into_mem_success db 'Successfully loaded.', 0x0A, 0x0D, 0
message_read_into_mem_error db 'Error', 0x0A, 0x0D, 0
message_halt_due_to_error db 'Halting system due to errors', 0x0A, 0x0D, 0
new_line db 0xA, 0xD, 0

stage2:

mov ax, cs
mov ds, ax									; Set DS = CS

mov si, stage2_msg
call print_string

mov si, opt_msg
call print_string


.select_opt:								; here we decide where to go now
	mov si, opt_sel_msg
	call print_string
	call choose_option
	mov si, new_line
	call print_string
	cmp al, '1'
	je .real_mode
	cmp al, '2'
	je .real_mode_ext
	cmp al, '3'
	je .prot_mode_32
	cmp al, '4'
	je .prot_mode_64
	mov si, opt_invalid_msg
	call print_string
	jmp .select_opt


.real_mode:
	cli										; clear interrupts
	mov	ax, 0xFE00							; stack begins at 0xFE00 - 0xFFFF (512 bytes)
	mov	ss, ax
	mov	sp, 0xFFFF
	mov ax, 0x07e0							; we want to load kernel at PA = 0x7e00
	mov es, ax								; ES = 0x07e0
	xor bx, bx								; OFF = 0x0000
											; set up reads
	push 0x0000								; head and drive number (dh = 0x00, dl = 0x00)
	push 0x0004								; kernel's sector at floppy (ch = 0x00, cl = 0x04)
	push 0x0001								; set up ax (ah = 0x00, al = 0x01)
	sti
	jmp mode_setup_done

.real_mode_ext:
	cli										; clear interrupts
	; xor	ax, ax							; null segments
	; mov	ds, ax
	; mov	es, ax
	; mov	ax, 0xFE00						; stack begins at 0xFE00-0xffff (512 bytes)
	; mov	ss, ax
	; mov	sp, 0xFFFF
	sti
	jmp stage2_error

.prot_mode_32:
	cli										; clear interrupts
	; xor	ax, ax							; null segments
	; mov	ds, ax
	; mov	es, ax
	; mov	ax, 0xFE00						; stack begins at 0xFE00-0xffff (512 bytes)
	; mov	ss, ax
	; mov	sp, 0xFFFF
	sti

	; call gdt_load							; load gdt
	
	; mov al, 2
	; out 0x92, al
    
	; cli
	; mov eax, cr0							; mov cr0 register to eax
	; or eax, 0x1							; set first bit
	; mov cr0, eax							; copy modified data so we can enter to pm

	; jmp 0x8:enter_pm						; far jmp to 32 bits area, that way the cpu will clear the pipeline

	jmp stage2_error

.prot_mode_64:
	; call_func_16 print_string_16, p64_mode_msg, p64_mode_msg_len
	jmp stage2_error

mode_setup_done:

call reset_floppy

mov si, message_read_into_mem
call print_string

pop ax
pop cx
pop dx

call read_to_mem

mov si, message_read_into_mem_success
call print_string

push es
push bx
retf										; Far jump to address where we want to load the kernel

stage2_error:

mov si, message_halt_due_to_error
call print_string

jmp $										; Endless loop

times 1024 - ($ - $$) db 0

; [bits 32]

; enter_pm:

; mov     ax, 0x10        					; set data segments to data selector (0x10)
; mov     ds, ax
; mov     ss, ax
; mov     es, ax
; mov     esp, 90000h     					; stack begins from 90000h

; mov si, welcome_to_protected_mode
; call string_print_32

; cli
; hlt


; %include "x32/string.asm"
; %include "x32/main32.asm"

; welcome_to_protected_mode db "Welcome to protected mode!", 0x0A, 0x0D, 0

section .bss
new_string_copy resb 50
str_concats resb 50
