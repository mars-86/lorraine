;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_VIDEO_INC_INCLUDED__
%define __X16_VIDEO_INC_INCLUDED__

[bits 16]

jmp module

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; video_int 0x10

module:

; set video mode
; in:
; AH = 00h
; AL = desired video mode (see #00010)
;
; return:
; AL = video mode flag (Phoenix, AMI BIOS)
; 20h mode > 7
; 30h modes 0-5 and 7
; 3Fh mode 6
; AL = CRT controller mode byte (Phoenix 386 BIOS v1.10)

set_video_mode_16:
	mov ah, 0x00
	int 0x10
	ret


; set cursor shape
; in:
; AH = 01h
; CH = cursor start and options (see #00013)
; CL = bottom scan line containing cursor (bits 0-4)
;
; return:
; void

set_cursor_shape_16:
	mov ah, 0x01
	int 0x10
	ret


; set cursor position
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
	mov ah, 0x02
	mov bh, 0x00
	int 0x10
	ret


; get cursor position and size
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
	mov ah, 0x03
	mov bh, 0x00
	int 0x10
	ret


; select active display page
; in:
; AH = 05h
; AL = new page number (00h to number of pages - 1) (see #00010)
;
; return:
; void

select_active_display_page_16:
	mov ah, 0x05
	int 0x10
	ret


; scroll up window
; in:
; AH = 06h
; AL = number of lines by which to scroll up (00h = clear entire window)
; BH = attribute used to write blank lines at bottom of window
; CH,CL = row,column of window's upper left corner
; DH,DL = row,column of window's lower right corner

; return:
; void

scroll_up_window_16:
	mov ah, 0x06
	int 0x10
	ret


; scroll down window
; in:
; AH = 07h
; AL = number of lines by which to scroll down (00h=clear entire window)
; BH = attribute used to write blank lines at top of window
; CH,CL = row,column of window's upper left corner
; DH,DL = row,column of window's lower right corner
;
; return
; void

scroll_down_window_16:
	mov ah, 0x07
	int 0x10
	ret


; read char at cursor position
; in:
; AH = 08h
; BH = page number (00h to number of pages - 1) (see #00010)
;
; return:
; AH = character's attribute (text mode only) (see #00014)
; AH = character's color (Tandy 2000 graphics mode only)
; AL = character

read_char_at_cursor_pos_16:
	mov ah, 0x08
	mov bh, 0x00
	int 0x10
	ret


; write char at cursor position
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

write_char_at_cursor_pos_16:
	mov ah, 0x09
	mov bh, 0x00
	mov bl, 0x07							; fix !!
	int 0x10
	ret


; set background / border color
; in:
; AH = 0Bh
; BH = 00h
; BL = background/border color (border only in text modes)
;
; return:
; void

set_background_border_color_16:
	mov ah, 0x0B
	mov bh, 0x00
	int 0x10
	ret


; set palette
; in:
; AH = 0Bh
; BH = 01h
; BL = palette ID
; 00h background, green, red, and brown/yellow
; 01h background, cyan, magenta, and white
;
; return:
; void

set_palette_16:
	mov ah, 0x0B
	mov bh, 0x01
	int 0x10
	ret


; write graphics pixel
; in:
; AH = 0Ch
; BH = page number
; AL = pixel color
; if bit 7 set, value is XOR'ed onto screen except in 256-color modes
; CX = column
; DX = row
;
; return:
; void

write_graphics_pixels_16:
	mov ah, 0x0C
	mov bh, 0x00
	int 0x10
	ret


; read graphics pixel
; in:
; AH = 0Dh
; BH = page number
; CX = column
; DX = row
;
; return:
; AL = pixel color

read_graphics_pixels_16:
	mov ah, 0x0D
	mov bh, 0x00
	int 0x10
	ret


; teletype output
; in:
; AH = 0Eh
; AL = character to write
; BH = page number
; BL = foreground color (graphics modes only)
;
; return:
; void

tty_output_16:
	mov ah, 0x0E
	mov bh, 0x00
	int 0x10


; get current video mode
; in:
; AH = 0Fh
;
; return:
; AH = number of character columns
; AL = display mode (see #00010 at AH=00h)
; BH = active page (see AH=05h)

get_current_video_mode_16:
	mov ah, 0x0F
	int 0x10
	ret


; write string
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
	mov ah, 0x13
	mov al, 0x01
	mov bh, 0x00
	mov bl, 0x07					; fix!!
	int 0x10
	ret


%endif								; __X16_VIDEO_INC_INCLUDED__
