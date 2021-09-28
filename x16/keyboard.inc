;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_KEYBOARD_INC_INCLUDED__
%define __X16_KEYBOARD_INC_INCLUDED__

[bits 16]

jmp module

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************

; keyboard_int 0x16

module:

; get keystroke
; in:
; AH = 00h
; return:
; AH = BIOS scan code
; AL = ASCII character

get_keystroke_16:
	mov ah, 0x00
	int 0x16
	ret


; check for keystroke
; in:
; AH = 01h
;
; return:
; ZF set if no keystroke available
; ZF clear if keystroke available
; AH = BIOS scan code
; AL = ASCII character

check_for_keystroke_16:
	mov ah, 0x01
	int 0x16
	ret


; get shift flags
; in:
; AH = 02h
;
; return:
; AL = shift flags (see #00582)
; AH destroyed by many BIOSes

get_shift_flags_16:
	mov ah, 0x02
	int 0x16
	ret


; set typematic rate and delay
; in:
; AH = 03h
; AL = subfunction
; 00h set default delay and rate (PCjr and some PS/2)
; 01h increase delay before repeat (PCjr)
; 02h decrease repeat rate by factor of 2 (PCjr)
; 03h increase delay and decrease repeat rate (PCjr)
; 04h turn off typematic repeat (PCjr and some PS/2)
; 05h set repeat rate and delay (AT,PS)
; BH = delay value (00h = 250ms to 03h = 1000ms)
; BL = repeat rate (00h=30/sec to 0Ch=10/sec [def] to 1Fh=2/sec)
; 06h get current typematic rate and delay (newer PS/2s)
;
; return:
; BL = repeat rate (above)
; BH = delay (above)
;
; return:
; AH destroyed by many BIOSes

set_typematic_rate_and_delay_16:
	mov ah, 0x03
	int 0x16
	ret


; store keystroke in keyboard buffer
; in:
; AH = 05h
; CH = BIOS scan code
; CL = ASCII character
;
; return:
; AL = status
; 00h if successful
; 01h if keyboard buffer full
; AH destroyed by many BIOSes

store_keystroke_in_keyboard_buffer_16:
	mov ah, 0x05
	int 0x16
	ret


; get keyboard functionality
; in:
; AH = 09h
;
; return:
; AL = supported keyboard functions (see #00585)
; AH destroyed by many BIOSes

get_keyboard_functionality_16:
	mov ah, 0x09
	int 0x16
	ret


; get keyboard id
; in:
; AH = 0Ah
;
; return:
; BX = keyboard ID (see #00586)
; AH destroyed by many BIOSes

get_keyboard_id_16:
	mov ah, 0x0A
	int 0x16
	ret


; get enhanced keystroke
; in:
; AH = 10h
;
; return:
; AH = BIOS scan code
; AL = ASCII character

get_enhanced_keystroke_16:
	mov ah, 0x10
	int 0x16
	ret


; check for enhanced keystroke
; in:
; AH = 11h
;
; return:
; ZF set if no keystroke available
; ZF clear if keystroke available
; AH = BIOS scan code
; AL = ASCII character

check_for_enhanced_keystroke_16:
	mov ah, 0x11
	int 0x16
	ret


; get extended shit states
; in:
; AH = 12h
;
; return:
; AL = shift flags 1 (same as returned by AH=02h) (see #00587)
; AH = shift flags 2 (see #00588)

get_extended_shift_states_16:
	mov ah, 0x12
	int 0x16
	ret


%endif								; __X16_KEYBOARD_INC_INCLUDED__
