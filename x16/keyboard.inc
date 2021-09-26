%ifndef __X16_KEYBOARD_INC_INCLUDED__
%define __X16_KEYBOARD_INC_INCLUDED__

[bits 16]

jmp .lib

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************


.lib:

; Return:
; AH = BIOS scan code
; AL = ASCII character
get_key_16:
	mov ah, 0x00
	int 0x16
	ret

%endif								; __X16_KEYBOARD_INC_INCLUDED__
