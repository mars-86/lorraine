print_string_16:
	mov ah, 0x0E
	push si
	.repeat:
		mov al, [si]
		cmp al, 0
		je .end
		int 0x10
		inc si
		jmp .repeat
	.end:
	pop si
	ret
