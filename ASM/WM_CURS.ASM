public WM_CURSORON,WM_CURSOROFF

extrn _wm_actwin:dword

proc pascal WM_CURSORON far
	cmp	[cs:WMX_FREEZE],0
	je	@@ok
	ret
@@ok:
	push	ds
	push	si
	lds	si,[_wm_actwin]
	mov	ax,[ds:si+soft_w.Control]
	test	ax,_CURSOR
	jz	@@no_put

	mov	al,[ds:si+soft_w.X]
	xor	ah,ah
	add	ax,[ds:si+soft_w.Xpos]
	sub	ax,[ds:si+soft_w.dXX]
	mov	bx,[cs:Vwidth]
	cmp	al,bl
	ja	@@no_put
	mov	dl,al
	mov	al,[ds:si+soft_w.Y]
	add	ax,[ds:si+soft_w.Ypos]
	sub	ax,[ds:si+soft_w.dYY]
	cmp	al,[byte ptr cs:Vheight]
	ja	@@no_put
	mov	dh,al
	mov	ax,bx
	mul	dh
	add	al,dl
	adc	ah,0
	mov	bx,[ds:si+soft_w.handle]
	lds	si,[cs:WM_MAP]
	add	si,ax
	lodsb
	and	al,7fh
	cmp	al,bl
	jne	@@no_put
	mov	bl,[cs:Vpage]
	mov	ah,2
	int	10h
	mov	cx,[cs:Vsize]
@@set:
	mov	ah,1
	int	10h
	pop	si
	pop	ds
	ret
@@no_put:
	mov	cx,2000h
	jmp	@@set
endp

proc pascal WM_CURSOROFF far
	cmp	[cs:WMX_FREEZE],0
	jne	@@no
	mov	cx,2000h
	mov	ah,1
	int	10h
@@no:
	ret
endp
