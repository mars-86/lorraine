%ifndef __X32_IO_INC_INCLUDED__
%define __X32_IO_INC_INCLUDED__

[bits 32]

jmp .lib

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x32/constants.asm"

;*******************************************************
;	Data section
;*******************************************************


.lib:

write:
	push ax
	push edx
	push esi
	mov edx, VIDEO_ADDRESS
	.repeat:
		mov ah, [esi]
		mov al, 0x0f

		or ah, ah
		jz .done

		mov [edx], ax
		add edx, 2
		inc esi
		jmp .repeat
	.done:
	pop esi
	pop edx
	pop ax
	ret

%endif								; __X32_IO_INC_INCLUDED__
