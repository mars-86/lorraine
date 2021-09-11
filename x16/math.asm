; ax -> num
absol:
	cmp ax, 0
	jge .positive
	imul ax, -1
	.positive:
	ret

; ax -> base
; cx -> power
pow:
;	cmp cx, 0
;	je .dopowz
;	cmp cx, 2
;	jge .dopow
;	jmp .end
;	.dopow:
;		mov dx, ax
;		.l1:
;			mul ax, dx
;			sub cx
;			cmp cx, 2
;			jge .l1
;	jmp .end
;	.dopowz:
;		mov ax, 1
;	.end:
	ret

; ax -> num
sqrt:
	
	ret
