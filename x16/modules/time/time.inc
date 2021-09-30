;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_MODULES_TIME_INC_INCLUDED__
%define __X16_MODULES_TIME_INC_INCLUDED__

[bits 16]

time_module:

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/modules/rtc.inc"

;*******************************************************
;	Data section
;*******************************************************

; time_int 0x1A

; get system time
; in:
; AH = 00h
;
; return:
; CX:DX = number of clock ticks since midnight
; AL = midnight flag, nonzero if midnight passed since time last read

get_system_time_16:
    mov ah, 0x00
    int 0x1A
    ret


; set system time
; in:
; AH = 01h
; CX:DX = number of clock ticks since midnight
;
; return:
; void

set_system_time_16:
    mov ah, 0x01
    int 0x1A
    ret


; set alarm
; in:
; AH = 06h
; CH = hour (BCD)
; CL = minutes (BCD)
; DH = seconds (BCD)
;
; return:
; CF set on error (alarm already set or clock stopped for update)
; CF clear if successful

set_alarm_16:
    mov ah, 0x06
    int 0x1A
    ret


; cancel alarm
; in:
; AH = 07h
;
; return:
; alarm disabled

cancel_alarm_16:
    mov ah, 0x07
    int 0x1A
    ret


%endif								; __X16_MODULES_TIME_INC_INCLUDED__
