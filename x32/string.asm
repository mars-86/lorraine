%ifndef __X32_STRING_ASM_INCLUDED__
%define __X32_STRING_ASM_INCLUDED__

[bits 32]

print_string_32:
	push ax
	push edx
	push si
	mov edx, VIDEO_ADDRESS
	.repeat:
		mov ah, [si]
		mov al, 0x0f
		
		cmp ah, 0
		je .done
		
		mov [edx], ax
		add edx, 2
		inc si
		jmp .repeat
	.done:
	pop si
	pop edx
	pop ax
	ret

%include "x32/constants.asm"

%endif								; __X32_STRING_ASM_INCLUDED__