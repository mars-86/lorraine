%ifndef __X16_STRING_INC_INCLUDED__
%define __X16_STRING_INC_INCLUDED__

; In :
; SI = string to print
;
; Return:
; void
string_print_16:
	push ax
	push si
	mov ah, 0x0E
	.repeat:
		mov al, [si]
		cmp al, 0
		je .end
		int 0x10
		inc si
		jmp .repeat
	.end:
	pop si
	pop ax
	ret

%endif									; __X16_STRING_INC_INCLUDED__
