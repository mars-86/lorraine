%ifndef __X16_STDIO_INC_INCLUDED__
%define __X16_STDIO_INC_INCLUDED__

[bits 16]

jmp stdio_lib

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x16/modules/keyboard/keyboard.inc"
%include "x16/modules/video/video.inc"

;*******************************************************
;	Data section
;*******************************************************

new_line db 0xA, 0xD, 0
new_line_len equ $ - new_line

stdio_lib:

; return:
; AH = BIOS scan code
; AL = ASCII character
getc_16:
	call get_keystroke_16
	ret

; in:
; AL = ASCII character
putc_16:
	call write_char_at_cursor_pos_16
	ret

; in:
; void
;
; return:
; void
newln_16:
	push new_line
	push new_line_len
	call print_string_16
	add sp, 4
	ret

; in:
; STACK = string
; STACK = length
;
; return:
; void
print_string_16:
	push bp
	push cx
	mov bp, sp
	call get_cursor_pos_16					; this call change cx reg among others
	mov cx, [bp + 6]						; length
	mov bp, [bp + 8]						; string
	dec cx									; we don't want to print null character
	call write_string_16
	pop cx
	pop bp
	ret


%endif								; __X16_STDIO_INC_INCLUDED__
