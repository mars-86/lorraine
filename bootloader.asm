[bits 16]
[org 0x7c00]      							; Bootloader starts at physical address 0x7c00

jmp start


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

message_floppy_reset db 'Reseting Floppy...', 0x0A, 0x0D, 0
message_read_into_mem db 'Loading to memory...', 0x0A, 0x0D, 0
message_read_into_mem_success db 'Successfully loaded.', 0x0A, 0x0D, 0
message_read_into_mem_error db 'Error', 0x0A, 0x0D, 0
message_halt_due_to_error db 'Halting system due to errors', 0x0A, 0x0D, 0
read_into_mem_retries dw 3


start:

xor ax, ax									; Set DS manually because we specified an ORG
mov ds, ax        							; DS = 0

cli               							

mov ss, ax        							; SS = 0x0000
mov sp, 0x77FF    							; SP = 0x77FF

sti              							

mov si, message_floppy_reset
call print_string

reset_floppy:                				; Resets floppy
    xor ax, ax         						; AH = 0 = Reset floppy disk
    int 0x13
    jc reset_floppy         				; CF set means error, try again

mov si, message_read_into_mem
call print_string

mov ax, 0x0050     							; When we read the sector, we are going to read to
											; address 0x0050:0x7300 (phys address 0x07800)
											; 1Kb right before the bootloader in memory
mov es, ax         							; Set ES with 0x0050
mov bx, 0x7300    							; Offset to read sector to 0x7300

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

jmp 0x0050:0x7300 							; Jump to 0x50:0x7300 setting CS to 0x0050
											; IP to 7300 which is code in second stage
											; (0x0050 << 4) + 0x7300 = 0x7800 physical address

.error:

mov si, message_halt_due_to_error
call print_string

jmp $										; Endless loop

times 510 - ($ - $$) db 0   				; Fill the rest of sector with 0
dw 0xAA55                   				; Boot signature
