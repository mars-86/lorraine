[bits 16]
[org 0x7c00]      					; Bootloader starts at physical address 0x7c00

jmp start

;*******************************************************
;	Preprocessor directives
;*******************************************************

;*******************************************************
;	Data section
;*******************************************************

message_floppy_reset db 'Reseting Floppy...', 0x0A, 0x0D, 0
message_read_into_mem db 'Loading to memory...', 0x0A, 0x0D, 0
message_read_into_mem_success db 'Successfully loaded.', 0x0A, 0x0D, 0
message_read_into_mem_error db 'Error', 0x0A, 0x0D, 0
message_halt_due_to_error db 'Halting system due to errors', 0x0A, 0x0D, 0
read_into_mem_retries dw 3

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

											; At start bootloader sets DL to boot drive

											; Since we specified an ORG(offset) of 0x7c00 we should make sure that
											; Data Segment (DS) is set accordingly. The DS:Offset that would work
											; in this case is DS=0 . That would map to segment:offset 0x0000:0x7c00
											; which is physical memory address (0x0000<<4)+0x7c00 . We can't rely on
											; DS being set to what we expect upon jumping to our code so we set it
											; explicitly
    
start:

xor ax, ax
mov ds, ax        							; DS=0

cli               							; Turn off interrupts for SS:SP update
											; to avoid a problem with buggy 8088 CPUs
mov ss, ax        							; SS = 0x0000
mov sp, 0x7c00    							; SP = 0x7c00
											; We'll set the stack starting just below
											; where the bootloader is at 0x0:0x7c00. The
											; stack can be placed anywhere in usable and
											; unused RAM.
sti              							; Turn interrupts back on

mov si, message_floppy_reset
call print_string

reset_floppy:                				; Resets floppy drive
    xor ax, ax         						; AH = 0 = Reset floppy disk
    int 0x13
    jc reset_floppy         				; If carry flag was set, try again

mov si, message_read_into_mem
call print_string

mov ax, 0x07e0     							; When we read the sector, we are going to read to
											;    address 0x07e0:0x0000 (phys address 0x07e00)
											;    right after the bootloader in memory
mov es, ax         							; Set ES with 0x07e0
xor bx, bx         							; Offset to read sector to

mov si, message_read_into_mem_error

read_to_mem:
	mov ah, 0x02
	mov al, 0x02
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	mov dl, 0x00
	int 0x13
	jnc .read_done
	call print_string
	push bx
	mov bx, [read_into_mem_retries]
	dec bx
	or bx, bx
	jz .error
	mov [read_into_mem_retries], bx
	pop bx
	jmp read_to_mem

.read_done:

mov si, message_read_into_mem_success
call print_string

jmp 0x07e0:0x0000 							; Jump to 0x7e0:0x0000 setting CS to 0x07e0
											; IP to 0 which is code in second stage
											; (0x07e0<<4)+0x0000 = 0x07e00 physical address

.error:

mov si, message_halt_due_to_error
call print_string

jmp $										; endless loop

times 510 - ($ - $$) db 0   				; Fill the rest of sector with 0
dw 0xAA55                   				; This is the boot signature
