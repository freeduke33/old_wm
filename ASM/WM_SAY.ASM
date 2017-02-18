public WM__SAYCHAR

proc pascal WM__SAYCHAR far
arg wind:dword,x:word,y:word,character:word
	push	ds
	push	si
	push	di
	lds	si,[wind]
	mov	dx,[x]
	mov	bx,[y]
	mov	ax,[ds:si+soft_w.XX]
	mul	bl
	shl	ax,1
	shl	dx,1
	add	ax,dx
	les	di,[ds:si+soft_w.data]
	add	di,ax
	mov	ax,[character]
	stosw
	cmp	[cs:WMX_FREEZE],0
	jne	@@no_put
	test	[ds:si+soft_w.Control],_HIDDEN
	jnz	@@no_put
	shr	dx,1
	sub	dx,[ds:si+soft_w.dXX]
	add	dl,[ds:si+soft_w.X]
	sub	bx,[ds:si+soft_w.dYY]
	add	bl,[ds:si+soft_w.Y]
	mov	ax,[cs:Vwidth]
	mov	cx,dx
	mul	bx
	add	ax,cx
	cmp	ax,[cs:Vregen]
	ja	@@no_put
	mov	dx,ax
	les	di,[cs:WM_MAP]
	add	di,ax
	mov	al,[es:di]
	mov	ah,[byte ptr ds:si+soft_w.handle]
	xor	al,ah
	jz	@@put
	cmp	al,80h
	jne	@@no_put
@@put:
	shl	dx,1
	les	di,[cs:WM_DISPLAY]
	add	di,dx
	mov	dl,al
	mov	ax,[character]
	stosb
	or	dl,dl
	jnz	@@no_put
	mov	al,ah
	stosb
@@no_put:
	pop	di
	pop	si
	pop	ds
	ret
endp
