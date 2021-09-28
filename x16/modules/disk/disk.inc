;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_DISK_INC_INCLUDED__
%define __X16_DISK_INC_INCLUDED__

[bits 16]

jmp module

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; disk_int 0x13

module:

; reset disk system
; in:
; AH = 00h
; DL = drive (if bit 7 is set both hard disks and floppy disks reset)
;
; return:
; AH = status (see #00234)
; CF clear if successful (returned AH=00h)
; CF set on error

reset_disk_16:
    xor ah, ah
    int 0x13
    ret


; get status of last operation
; in:
; AH = 01h
; DL = drive (bit 7 set for hard disk)
;
; return:
; CF clear if successful (returned status 00h)
; CF set on error
; AH = status of previous operation (see #00234)

get_status_of_last_operation_16:
    mov ah, 0x01
    int 0x13
    ret


; read sector(s) into memory
; in:
; AH = 02h
; AL = number of sectors to read (must be nonzero)
; CH = low eight bits of cylinder number
; CL = sector number 1-63 (bits 0-5)
; high two bits of cylinder (bits 6-7, hard disk only)
; DH = head number
; DL = drive number (bit 7 set for hard disk)
; ES:BX -> data buffer
;
; return:
; CF set on error
; if AH = 11h (corrected ECC error), AL = burst length
; CF clear if successful
; AH = status (see #00234)
; AL = number of sectors transferred (only valid if CF set for some BIOSes)

read_sectors_into_memory_16:
    mov ah, 0x02
    int 0x13
    ret


; write disk sector(s)
; in:
; AH = 03h
; AL = number of sectors to write (must be nonzero)
; CH = low eight bits of cylinder number
; CL = sector number 1-63 (bits 0-5)
; high two bits of cylinder (bits 6-7, hard disk only)
; DH = head number
; DL = drive number (bit 7 set for hard disk)
; ES:BX -> data buffer
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234)
; AL = number of sectors transferred
; (only valid if CF set for some BIOSes)

write_disk_sectors_16:
    mov ah, 0x03
    int 0x13
    ret


; verify disk sector(s)
; in:
; AH = 04h
; AL = number of sectors to verify (must be nonzero)
; CH = low eight bits of cylinder number
; CL = sector number 1-63 (bits 0-5)
; high two bits of cylinder (bits 6-7, hard disk only)
; DH = head number
; DL = drive number (bit 7 set for hard disk)
; ES:BX -> data buffer (PC,XT,AT with BIOS prior to 1985/11/15)
; 
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234)
; AL = number of sectors verified

verify_disk_sectors_16:
    mov ah, 0x04
    int 0x13
    ret

%endif								; __X16_DISK_INC_INCLUDED__
