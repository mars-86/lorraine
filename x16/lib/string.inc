%ifndef __X16_STRING_INC_INCLUDED__
%define __X16_STRING_INC_INCLUDED__

; args:
; STACK = string
;
; return
; AX = length

string_length_16:
	push bp
	push si
	mov bp, sp
	mov si, [bp + 2]
	xor ax, ax
	.repeat:
		cmp [si], 0
		je .done
		inc ax
		inc si
		jmp .repeat
	.done:
	pop si
	pop bp
	ret


; args:
; STACK = dest string
; STACK = src string
;
; return
; DI = new string

string_concat_16:
	push bp
	push si
	mov sp, bp
	mov di, [bp + 4]					; move 
	push di
	.repeat_1:
		cmp di, 0
		je .done1
		inc di
		jmp .repeat_1
	.done1:
	mov di, [bp + 2]
	pop di
	pop si
	pop bp
	ret


%endif									; __X16_STRING_INC_INCLUDED__
