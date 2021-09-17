[bits 16]
; [org 0x7c00]      ; Bootloader starts at physical address 0x7c00

jmp start

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/string.asm"

;*******************************************************
;	Data section
;*******************************************************

message_floppy_reset db 'Reseting Floppy...', 0x0A, 0x0D, 0
message_read_into_mem db 'Loading kernel...', 0x0A, 0x0D, 0

stage_2_address equ 0x07e0


start:
; At start bootloader sets DL to boot drive

; Since we specified an ORG(offset) of 0x7c00 we should make sure that
; Data Segment (DS) is set accordingly. The DS:Offset that would work
; in this case is DS=0 . That would map to segment:offset 0x0000:0x7c00
; which is physical memory address (0x0000<<4)+0x7c00 . We can't rely on
; DS being set to what we expect upon jumping to our code so we set it
; explicitly

; xor ax, ax
; mov ds, ax        ; DS=0

; cli               ; Turn off interrupts for SS:SP update
                  ; to avoid a problem with buggy 8088 CPUs
; mov ss, ax        ; SS = 0x0000
; mov sp, 0x7c00    ; SP = 0x7c00
                  ; We'll set the stack starting just below
                  ; where the bootloader is at 0x0:0x7c00. The
                  ; stack can be placed anywhere in usable and
                  ; unused RAM.
; sti               ; Turn interrupts back on

mov si, message_floppy_reset
call print_string_16

reset_floppy:
	xor ax, ax
	int 0x13
	jc reset_floppy
		
mov si, message_read_into_mem
call print_string_16

mov ax, stage_2_address
mov es, ax
xor bx, bx

read_to_mem:
	mov ah, 0x02
	mov al, 0x01
	mov ch, 0x01
	mov cl, 0x02
	mov dh, 0x00
	mov dl, 0x00
	int 0x13
	jc read_to_mem

jmp stage_2_address:0x0000

times 510-($-$$) db 0
dw 0xAA55
