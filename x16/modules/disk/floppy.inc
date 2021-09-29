;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_FLOPPY_DISK_INC_INCLUDED__
%define __X16_FLOPPY_DISK_INC_INCLUDED__

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




%endif								; __X16_FLOPPY_DISK_INC_INCLUDED__
