%ifndef __X32_STRING_ASM_INCLUDED__
%define __X32_STRING_ASM_INCLUDED__

[bits 32]

jmp .lib

;*******************************************************
;	Preprocessor directives
;*******************************************************

%include "x32/io.inc"

;*******************************************************
;	Data section
;*******************************************************


.lib:

string_print_32:
	call write
	ret

string_length_32:
	push ebx
	xor eax, eax
	.repeat:
		mov bh, [esi]
		or bh, bh
		jz .done
		inc eax
		inc esi
		jmp .repeat
	.done:
	pop ebx
	ret

string_concat_32:
	push ebp
	mov ebp, esp
	sub esp, 4
	mov [ebp - 4], edi					; copy edi initial address

	mov edi, [ebp + 8]					; copy src string to edi
	.repeat1:							; first we go to the end '\0'
		mov ah, [edi]
		or ah, ah
		jz .done1
		inc edi
		jmp .repeat1
	.done1:

	mov edi, [ebp + 4]					; now we append the second string

	mov edi, [ebp - 4]					; restore edi to the beginning
	pop ebp
	ret

string_reverse_32:
	push ebp
	mov ebp, esp
	sub esp, 8

	mov esi, [ebp + 4]					; mov src string to esi
	mov [ebp - 4], esi					; copy esi initial address
	mov [ebp - 8], edi					; 

	.repeat1:							; first we go to the end '\0'
		mov ah, [esi]
		or ah, ah
		jz .done1
		inc esi
		jmp .repeat1
	.done1:

	.repeat2:							; invert string order
		mov edi, esi
		cmp esi, [ebp - 4]				; if esi == initial address
		je .done2
		inc edi							;
		dec esi							;
		jmp .repeat2
	.done2:

	mov edi, [ebp - 8]					; restore edi to the beginning
	pop ebp
	ret

%endif									; __X32_STRING_ASM_INCLUDED__
