;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_MODULES_SYSTEM_INC_INCLUDED__
%define __X16_MODULES_SYSTEM_INC_INCLUDED__

[bits 16]

jmp system_module

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; system_int 0x12

system_module:

; get equipment list
; in:
; Return:
; (E)AX = BIOS equipment list word (see #00226,#03215 at INT 4B"Tandy")

get_equipment_list_16:
    int 0x11
    ret


; get memory size
; in:
; return:
; AX = kilobytes of contiguous memory starting at absolute address 00000h

get_memory_size_16:
    int 0x12
    ret


; set event wait interval
; in:
; AH = 83h
; AL = subfunction
; 00h set interval
; CX:DX = microseconds to delay
; ES:BX -> byte whose high bit is to be set at end of interval
; 01h cancel wait interval
;
; return:
; CF set on error or function already busy
; AH = status
; 80h invalid command (PC,PCjr)
; 86h function not supported (XT and later)
; CF clear if successful

set_event_wait_interval_16:
    mov ah, 0x83
    int 0x15
    ret


; wait (at, ps)
; in:
; AH = 86h
; CX:DX = interval in microseconds
;
; return:
; CF clear if successful (wait interval elapsed)
; CF set on error or AH=83h wait already in progress
; AH = status (see #00496)

wait_16:
    mov ah, 0x86
    int 0x15
    ret


%endif								; __X16_MODULES_SYSTEM_INC_INCLUDED__
