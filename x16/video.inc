%ifndef __X16_VIDEO_INC_INCLUDED__
%define __X16_VIDEO_INC_INCLUDED__

[bits 16]

jmp .lib

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; video_int 0x10

.lib:

; in:
; AH = 0Ah
; AL = character to display
; BH = page number (00h to number of pages - 1) (see #00010)
; background color in 256-color graphics modes (ET4000)
; BL = attribute (PCjr, Tandy 1000 only) or color (graphics mode)
; if bit 7 set in <256-color graphics mode, character is XOR'ed
; onto screen
; CX = number of times to write character
;
; return:
; void

write_char_to_cursor_pos_16:
	push ax
	push bx
	push cx
	mov ah, 0x0A
	mov bh, 0x00
	mov bl, 0x00
	mov cx, 0x01
	int 0x10
	pop cx
	pop bx
	pop ax
	ret

; in:
; AH = 0Ah
; AL = character to display
; BH = page number (00h to number of pages - 1) (see #00010)
; background color in 256-color graphics modes (ET4000)
; BL = attribute (PCjr, Tandy 1000 only) or color (graphics mode)
; if bit 7 set in <256-color graphics mode, character is XOR'ed
; onto screen
; CX = number of times to write character
;
; return:
; void

write_n_char_to_cursor_pos_16:
	push ax
	push bx
	mov ah, 0x0A
	mov bh, 0x00
	mov bl, 0x00
	int 0x10
	pop bx
	pop ax
	ret

; in:
; AH = 02h
; BH = page number
; 0-3 in modes 2&3
; 0-7 in modes 0&1
; 0 in graphics modes
; DH = row (00h is top)
; DL = column (00h is left)
;
; return:
; void

set_cursor_pos_16:
	push ax
	push bx
	mov ah, 0x02
	mov bh, 0x00
	int 0x10
	pop bx
	pop ax
	ret

; in:
; AH = 03h
; BH = page number
; 0-3 in modes 2&3
; 0-7 in modes 0&1
; 0 in graphics modes
;
; return:
; AX = 0000h (Phoenix BIOS)
; CH = start scan line
; CL = end scan line
; DH = row (00h is top)
; DL = column (00h is left)

get_cursor_pos_16:
	push ax
	push bx
	mov ah, 0x03
	mov bh, 0x00
	int 0x10
	pop bx
	pop ax
	ret

; in:
; AH = 13h
; AL = write mode
;
; bit 0:
; Update cursor after writing
;
; bit 1:
; String contains alternating characters and attributes
;
; bits 2-7:
; Reserved (0).
; BH = page number.
; BL = attribute if string contains only characters.
; CX = number of characters in string.
; DH,DL = row,column at which to start writing.
; ES:BP -> string to write
;
; return:
; void

write_string_16:
	push ax
	push bx
	mov ah, 0x13
	mov al, 0x01
	mov bh, 0x00
	mov bl, [color_light_gray]
	int 0x10
	pop bx
	pop ax
	ret

%include "x16/palette.inc"

%endif								; __X16_VIDEO_INC_INCLUDED__
