;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_MODULES_HARD_DISK_INC_INCLUDED__
%define __X16_MODULES_HARD_DISK_INC_INCLUDED__

[bits 16]

hd_module:

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; disk_int 0x13

; initialize controller with drive parameters
; in:
; AH = 09h
; DL = drive (80h for first, 81h for second)
;
; return:
; CF clear if successful
; CF set on error
; AH = status (see #00234)

hd_init_controller_with_drive_params_16:
    mov ah, 0x09
    int 0x13
    ret


; read long sector(s)
; in:
; AH = 0Ah
; AL = number of sectors (01h may be only value supported)
; CH = low eight bits of cylinder number
; CL = sector number (bits 5-0)
; high two bits of cylinder number (bits 7-6)
; DH = head number
; DL = drive number (80h = first, 81h = second)
; ES:BX -> data buffer
;
; return:
; CF clear if successful
; CF set on error
; AH = status (see #00234)
; AL = number of sectors transferred

hd_read_long_sectors_16:
    mov ah, 0x0A
    int 0x13
    ret


; write long sector(s)
; in:
; AH = 0Bh
; AL = number of sectors (01h may be only value supported)
; CH = low eight bits of cylinder number
; CL = sector number (bits 5-0)
; high two bits of cylinder number (bits 7-6)
; DH = head number
; DL = drive number (80h = first, 81h = second)
; ES:BX -> data buffer
;
; return:
; CF clear if successful
; CF set on error
; AH = status (see #00234)
; AL = number of sectors transferred

hd_write_long_sectors_16:
    mov ah, 0x0B
    int 0x13
    ret


; seek to cylinder
; in:
; AH = 0Ch
; CH = low eight bits of cylinder number
; CL = sector number (bits 5-0)
; high two bits of cylinder number (bits 7-6)
; DH = head number
; DL = drive number (80h = first, 81h = second hard disk)
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234)

hd_seek_to_cylinder_16:
    mov ah, 0x0C
    int 0x13
    ret


; reset hard disk
; in:
; AH = 0Dh
; DL = drive number (80h = first, 81h = second hard disk)
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234)

hd_reset_hard_disk_16:
    mov ah, 0x0D
    int 0x13
    ret


; read sector buffer (xt)
; in:
; AH = 0Eh
; DL = drive number (80h = first, 81h = second hard disk)
; ES:BX -> buffer
;
; return:
; CF set on error
; CF clear if successful
; AH = status code (see #00234)

hd_read_sector_buffer_16:
    mov ah, 0x0E
    int 0x13
    ret


; write sector buffer (xt)
; in:
; AH = 0Fh
; DL = drive number (80h = first, 81h = second hard disk)
; ES:BX -> buffer
;
; return:
; CF set on error
; CF clear if successful
; AH = status code (see #00234)

hd_write_sector_buffer_16:
    mov ah, 0x0F
    int 0x13
    ret


; check if drive ready
; in:
; AH = 10h
; DL = drive number (80h = first, 81h = second hard disk)
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234 at AH=01h)

hd_check_if_drive_ready_16:
    mov ah, 0x10
    int 0x13
    ret


; recalibrate drive
; in:
; AH = 11h
; DL = drive number (80h = first, 81h = second hard disk)
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234 at AH=01h)

hd_recalibrate_drive_16:
    mov ah, 0x11
    int 0x13
    ret


; controller ram diagnostic (xt, ps)
; in:
; AH = 12h
; DL = drive number (80h = first, 81h = second hard disk)
;
; return:
; CF set on error
; CF clear if successful
; AH = status code (see #00234 at AH=01h)
; AL = 00h

hd_controller_ram_diagnostic_16:
    mov ah, 0x12
    int 0x13
    ret


; drive diagnostic (xt, ps)
; in:
; AH = 13h
; DL = drive number (80h = first, 81h = second hard disk)
;
; return:
; CF set on error
; CF clear if successful
; AH = status code (see #00234 at AH=01h)
; AL = 00h

hd_drive_diagnostic_16:
    mov ah, 0x13
    int 0x13
    ret


; controller internal diagnostic
; in:
; AH = 14h
;
; return:
; CF set on error
; CF clear if successful
; AH = status code (see #00234 at AH=01h)
; AL = 00h

hd_controller_internal_diagnostic_16:
    mov ah, 0x14
    int 0x13
    ret


%endif								; __X16_MODULES_HARD_DISK_INC_INCLUDED__
