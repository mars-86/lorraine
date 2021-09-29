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

jmp disk_module

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; disk_int 0x13

disk_module:

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


; get drive parameters
; in:
; AH = 08h
; DL = drive (bit 7 set for hard disk)
; ES:DI = 0000h:0000h to guard against BIOS bugs
;
; return:
; CF set on error
; AH = status (07h) (see #00234)
; CF clear if successful
; AH = 00h
; AL = 00h on at least some BIOSes
; BL = drive type (AT/PS2 floppies only) (see #00242)
; CH = low eight bits of maximum cylinder number
; CL = maximum sector number (bits 5-0)
; high two bits of maximum cylinder number (bits 7-6)
; DH = maximum head number
; DL = number of drives
; ES:DI -> drive parameter table (floppies only)

get_drive_parameters_16:
    xor ax, ax
    mov es, ax
    mov di, ax
    mov ah, 0x08
    int 0x13
    ret


; get disk type
; in:
; AH = 15h
; DL = drive number (bit 7 set for hard disk)
; (AL = FFh, CX = FFFFh, see Note)
;
; return:
; CF clear if successful
; AH = type code
; 00h no such drive
; (SpeedStor) AL = 03h hard disk
; CX:DX = number of 512-byte sectors
; 01h floppy without change-line support
; 02h floppy (or other removable drive) with change-line support
; 03h hard disk
; CX:DX = number of 512-byte sectors
; CF set on error
; AH = status (see #00234 at AH=01h)

get_disk_type_16:
    mov ah, 0x15
    int 0x13
    ret


; set media type for format
; in:
; AH = 18h
; DL = drive number
; CH = lower 8 bits of highest cylinder number (number of cylinders - 1)
; CL = sectors per track (bits 0-5)
; top 2 bits of highest cylinder number (bits 6,7)
;
; return:
; AH = status
; 00h requested combination supported
; 01h function not available
; 0Ch not supported or drive type unknown
; 80h there is no disk in the drive
; ES:DI -> 11-byte parameter table (see #01264 at INT 1E)

set_media_type_for_format_16:
    mov ah, 0x18
    int 0x13
    ret


%endif								; __X16_DISK_INC_INCLUDED__
