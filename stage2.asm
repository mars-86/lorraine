[bits 16]
[org 0x0000]

; ORG needs to be set to the offset of the far jump used to
; reach us. Jump was 0x7e0:0x0000 so ORG = Offset = 0x0000.

jmp stage2

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/string.inc"
%include "x16/stdio.inc"
%include "x16/gdt.asm"
%include "x16/utils/macros.inc"

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
opt_msg_len equ $ - opt_msg
opt_sel_msg db "Option: ", 0
opt_sel_msg_len equ $ - opt_sel_msg
opt_invalid_msg db "Invalid option", 0x0A, 0x0D, 0
opt_invalid_msg_len equ $ - opt_invalid_msg
real_mode_msg db "Real mode", 0x0A, 0x0D, 0
real_mode_msg_len equ $ - real_mode_msg
real_mode_ext_msg db "Real mode Extended", 0x0A, 0x0D, 0
real_mode_ext_msg_len equ $ - real_mode_ext_msg
p32_mode_msg db "Prot mode 32", 0x0A, 0x0D, 0
p32_mode_msg_len equ $ - p32_mode_msg 
p64_mode_msg db "Prot mode 64", 0x0A, 0x0D, 0
p64_mode_msg_len equ $ - p64_mode_msg

stage2:

mov ax, cs
mov ds, ax						; Set DS = CS

call_func_16 print_string_16, stage2_msg, stage2_msg_len

call_func_16 print_string_16, opt_msg, opt_msg_len

.select_opt:								; here we decide where to go now
	call_func_16 print_string_16, opt_sel_msg, opt_sel_msg_len
	call getc_16
	call putc_16
	call newln_16
	cmp al, '1'
	je .real_mode
	cmp al, '2'
	je .real_mode_ext
	cmp al, '3'
	je .prot_mode_32
	cmp al, '4'
	je .prot_mode_64
	call_func_16 print_string_16, opt_invalid_msg, opt_invalid_msg_len
	jmp .select_opt

.real_mode:
	call_func_16 print_string_16, real_mode_msg, real_mode_msg_len
	jmp .done
.real_mode_ext:
	call_func_16 print_string_16, real_mode_ext_msg, real_mode_ext_msg_len
	jmp .done
.prot_mode_32:
	call_func_16 print_string_16, p32_mode_msg, p32_mode_msg_len
	jmp .done
.prot_mode_64:
	call_func_16 print_string_16, p64_mode_msg, p64_mode_msg_len

.done:
	cli
	hlt

cli								; clear interrupts
xor	ax, ax						; null segments
mov	ds, ax
mov	es, ax
mov	ax, 0x9000					; stack begins at 0x9000-0xffff
mov	ss, ax
mov	sp, 0xFFFF
sti

call gdt_load					; load gdt
	
; mov al, 2
; out 0x92, al
    
cli
mov eax, cr0					; mov cr0 register to eax
or	eax, 0x1					; set first bit
mov cr0, eax					; copy modified data so we can enter to pm

jmp 0x8:enter_pm			; far jmp to 32 bits area, that way the cpu will clear the pipeline

[bits 32]

enter_pm:

mov     ax, 0x10        ; set data segments to data selector (0x10)
mov     ds, ax
mov     ss, ax
mov     es, ax
mov     esp, 90000h     ; stack begins from 90000h

mov si, welcome_to_protected_mode
call string_print_32

cli
hlt


%include "x32/string.asm"
; %include "x32/main32.asm"

welcome_to_protected_mode db "Welcome to protected mode!", 0x0A, 0x0D, 0

    ; Set to graphics mode 0x13 (320x200x256)
    ; mov ax, 13h
    ; int 10h

    ; Set ES to the VGA video segment at 0xA000
    ; mov ax, 0xa000
    ; mov es, ax

; vga:
    ; Draw pixel in middle of screen
    ; mov ax, [ycoord]
    ; mov bx, [xcoord]
    ; mov cx, 320
    ; mul cx
    ; add ax, bx
    ; mov di, ax
    ; mov dl, [color]
    ; mov [es:di],dl

    ; Put processor in an endless loop
    ; cli
; .endloop:
    ; hlt
    ; jmp .endloop

; Put Data after the code
; xcoord DW 160
; ycoord DW 100
; color  DB 0x0D    ; One of the magenta shades in VGA palette

