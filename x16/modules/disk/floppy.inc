;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_MODULES_FLOPPY_DISK_INC_INCLUDED__
%define __X16_MODULES_FLOPPY_DISK_INC_INCLUDED__

[bits 16]

floppy_module:

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; disk_int 0x13

; format track
; in:
; AH = 05h
; AL = number of sectors to format
; CH = track number
; DH = head number
; DL = drive number
; ES:BX -> address field buffer (see #00235)
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234)

floppy_format_track_16:
    mov ah, 0x05
    int 0x13
    ret


; detect disk change
; in:
; AH = 16h
; DL = drive number (00h-7Fh)
; SI = 0000h (to avoid crash on AT&T 6300)
;
; return:
; CF clear if change line inactive
; AH = 00h (disk not changed)
; CF set if change line active
; AH = status
; 01h invalid command (SyQuest)
; 06h change line active or not supported
; 80h drive not ready or not present

floppy_detect_disk_change_16:
    xor si, si
    mov ah, 0x16
    int 0x13
    ret


; set disk type for format (at, ps)
; in:
; AH = 17h
; AL = format type
; 01h = 320/360K disk in 360K drive
; 02h = 320/360K disk in 1.2M drive
; 03h = 1.2M disk in 1.2M drive
; 04h = 720K disk in 720K or 1.44M drive
; DL = drive number
;
; return:
; CF set on error
; CF clear if successful
; AH = status (see #00234 at AH=01h)

floppy_set_disk_type_for_format_16:
    mov ah, 0x17
    int 0x13
    ret


%endif								; __X16_MODULES_FLOPPY_DISK_INC_INCLUDED__
