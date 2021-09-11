; args [regs]
; x -> ax
; y -> bx
; di -> width
plotpixel:
	imul di, bx				; width * y0 (row)
	add di, ax				; row + x0	 (column)	
	mov [es:di], dl			; draw pixel
	mov di, 320
	ret

; args [stack]
; x0
; y0
; x1
; y1
plotline:
	push bp
	mov bp, sp
	sub sp, 12

	mov ax, [bp + 06]		; x1
	sub ax, [bp + 10]		; x1 - x0
	call absol
	mov [bp - 2], ax		; dx = abs(x1 - x0)

	mov ax, [bp + 04]		; y1
	sub ax, [bp + 08]		; y1 - y0
	call absol
	imul ax, -1
	mov [bp - 4], ax		; dy = -abs(y1 - y0)

	mov ax, [bp + 06]		; x1
	cmp [bp + 10], ax		; x0 < x1
	jl .xless
	mov [bp - 6], word - 1
	jmp .xgreat
	.xless:
	mov [bp - 6], word 1
	.xgreat:				; sx = x0 < x1 ? 1 : -1

	mov ax, [bp + 04]		; y1
	cmp [bp + 08], ax		; y0 < y1
	jl .yless
	mov [bp - 8], word - 1
	jmp .ygreat
	.yless:
	mov [bp - 8], word 1
	.ygreat:				; sy = y0 < y1 ? 1 : -1

	mov ax, [bp - 2]
	add ax, [bp - 4]
	mov [bp - 10], ax		; err = dx + dy

	.plot:
	mov ax, [bp + 10]		; ax = x0
	mov bx, [bp + 08]		; bx = y0
	call plotpixel
	mov ax, [bp - 10]		; err
	imul ax, 2
	mov [bp - 12], ax		; e2 = err * 2
	
	mov ax, [bp - 4]
	cmp [bp - 12], ax		; e2 >= dy
	jl .plotnoy
	mov ax, [bp + 06]		; x1
	cmp [bp + 10], ax		; x0 == x1
	je .endplot
	mov ax, [bp - 4]
	add [bp - 10], ax		; err += dy
	mov ax, [bp - 6]
	add [bp + 10], ax		; x0 += sx
	.plotnoy:

	mov ax, [bp - 2]
	cmp [bp - 12], ax		; e2 <= dx
	jg .plotnox
	mov ax, [bp + 04]		; y1
	cmp [bp + 08], ax		; y0 == y1
	je .endplot
	mov ax, [bp - 2]
	add [bp - 10], ax		; err += dx
	mov ax, [bp - 8]
	add [bp + 08], ax		; y0 += sy
	.plotnox:
	jmp .plot

	.endplot:
	add sp, 12
	pop bp
	ret
	
; args [stack]
; x0
; y0
; width
; height
plotrect:
	push bp
	mov bp, sp

	push word [bp + 10]		; x0
	push word [bp + 8]		; y0
	mov ax, [bp + 10]		 
	add ax, [bp + 6]		; x0 + width
	push ax
	push word [bp + 8]		
	call plotline
	add sp, 8
	
	push ax					; x0 + width
	push word [bp + 8]		; y0
	push ax					; x0 + width
	mov ax, [bp + 8]
	add ax, [bp + 4]		; y0 + height
	push ax
	call plotline
	add sp, 8
		
	push word [bp + 10]		; x0
	push word [bp + 8]		; y0
	push word [bp + 10]		; x0
	push ax					; y0 + height
	call plotline
	add sp, 8
	
	push word [bp + 10]		; x0
	push ax					; y0 + height
	mov bx, [bp + 10]		 
	add bx, [bp + 6]		; x0 + width
	push bx
	push ax					; y0 + height
	call plotline
	add sp, 8
		
	pop bp
	ret

; args [stack]
; x0
; y0
; width
plotsquare:
	push bp
	mov bp, sp
		
	push word [bp + 8]		; x0
	push word [bp + 6]		; y0
	push word [bp + 4]		; width
	push word [bp + 4]		; height
	call plotrect
	add sp, 8

	pop bp
	ret

%include "math.asm"
