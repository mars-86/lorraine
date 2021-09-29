;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_MODULES_REALTIME_CLOCK_INC_INCLUDED__
%define __X16_MODULES_REALTIME_CLOCK_INC_INCLUDED__

[bits 16]

jmp rtc_module

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; time_int 0x1A

rtc_module:

; get real-time clock time
; in:
; AH = 02h
; CF clear to avoid bug (see below)
;
; return:
; CF clear if successful
; CH = hour (BCD)
; CL = minutes (BCD)
; DH = seconds (BCD)
; DL = daylight savings flag (00h standard time, 01h daylight time)
; CF set on error (i.e. clock not running or in middle of update)

get_realtime_clock_time_16:
    clc
    mov ah, 0x02
    int 0x1A
    ret


; set real-time clock time
; AH = 03h
; CH = hour (BCD)
; CL = minutes (BCD)
; DH = seconds (BCD)
; DL = daylight savings flag (00h standard time, 01h daylight time)
;
; return:
; void

set_realtime_clock_time_16:
    mov ah, 0x03
    int 0x1A
    ret


; get real-time clock date
; in:
; AH = 04h
; CF clear to avoid bug (see below)
;
; return:
; CF clear if successful
; CH = century (BCD)
; CL = year (BCD)
; DH = month (BCD)
; DL = day (BCD)
; CF set on error

get_realtime_clock_date_16:
    clc
    mov ah, 0x04
    int 0x1A
    ret


; set real-time clock date
; in:
; AH = 05h
; CH = century (BCD)
; CL = year (BCD)
; DH = month (BCD)
; DL = day (BCD)
;
; return:
; void

set_realtime_clock_date_16:
    mov ah, 0x05
    int 0x1A
    ret


%endif								; __X16_MODULES_REALTIME_CLOCK_INC_INCLUDED__