[bits 16]
[org 0x7c00]      ; Bootloader starts at physical address 0x7c00

jmp start

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/string.asm"
; %include "x16/error.inc"

;*******************************************************
;	Data section
;*******************************************************

message_floppy_reset db 'Reseting Floppy...', 0x0A, 0x0D, 0
message_read_into_mem db 'Loading to memory...', 0x0A, 0x0D, 0
message_read_into_mem_success db 'Successfully loaded.', 0x0A, 0x0D, 0
message_read_into_mem_error db 'Error', 0x0A, 0x0D, 0
message_halt_due_to_error db 'Halting system due to several errors', 0x0A, 0x0D, 0
msg_err_len equ $ - message_halt_due_to_error
message_halt_due_to_error2 db 'Halting system due to several errors 2', 0x0A, 0x0D, 0

stage_2_address equ 0x7e00


start:
; At start bootloader sets DL to boot drive

; Since we specified an ORG(offset) of 0x7c00 we should make sure that
; Data Segment (DS) is set accordingly. The DS:Offset that would work
; in this case is DS=0 . That would map to segment:offset 0x0000:0x7c00
; which is physical memory address (0x0000<<4)+0x7c00 . We can't rely on
; DS being set to what we expect upon jumping to our code so we set it
; explicitly

xor ax, ax
mov ds, ax        ; DS=0

cli               ; Turn off interrupts for SS:SP update
                  ; to avoid a problem with buggy 8088 CPUs
mov ss, ax        ; SS = 0x0000
mov sp, 0x7c00    ; SP = 0x7c00
                  ; We'll set the stack starting just below
                  ; where the bootloader is at 0x0:0x7c00. The
                  ; stack can be placed anywhere in usable and
                  ; unused RAM.
sti               ; Turn interrupts back on

; cli

; xor ax, ax
; mov es, ax
; mov ds, ax
; mov ss, ax
; mov sp, 0x7c00
; mov bp, sp

; sti

mov si, message_floppy_reset
call print_string_16

reset_floppy:
	xor ax, ax
	int 0x13
	jc reset_floppy
		
mov si, message_read_into_mem
call print_string_16

mov ax, 0x07e0
mov es, ax
xor bx, bx
mov bx, 3

mov si, message_read_into_mem_error

read_to_mem:
	mov ah, 0x02
	mov al, 0x01
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	; mov dl, 0x00
	int 0x13
	jnc .read_done
	call print_string_16
	dec bx
	or bx, bx
	jz .error
	jmp read_to_mem

.read_done:

mov si, message_read_into_mem_success
call print_string_16

jmp 0x07e0:0x0000

.error:

mov si, message_halt_due_to_error
add si, msg_err_len
call print_string_16

jmp $

times 510-($-$$) db 0
dw 0xAA55
