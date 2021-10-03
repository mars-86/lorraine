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
; STACK = dest
; STACK = src
;
; return
; DI = new string

string_concat_16:
	push bp
	push si
	mov bp, sp
	mov di, [bp + 4]					; move 
	push di
	.repeat_1:
		cmp [di], 0
		je .done1
		inc di
		jmp .repeat_1
	.done1:
	mov di, [bp + 2]
	pop di
	pop si
	pop bp
	ret


; args:
; STACK = dest
; STACK = src
;
; return
; DI = copied string

string_copy_16:
	push bp
	mov bp, sp
	push si
	push di
	mov si, [bp + 2]
	.repeat:
		mov ah, [si]
		mov [di], ah
		cmp [si], 0
		je .done
		inc si
		inc di
		jmp .repeat
	.done:
	pop di
	pop si
	pop bp
	ret


%endif									; __X16_STRING_INC_INCLUDED__
