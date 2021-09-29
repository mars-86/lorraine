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

; get memory size
; in:
; return:
; AX = kilobytes of contiguous memory starting at absolute address 00000h

get_memory_size_16:
    int 0x12
    ret


%endif								; __X16_MODULES_SYSTEM_INC_INCLUDED__
