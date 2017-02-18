public WM_XBORDER

proc pascal WM_XBORDER far
arg wind:dword
	push	di
	push	si
	push	ds
	lds	si,[wind]
	call	setbox
	pop	ds
	pop	si
	pop	di
	ret
endp

proc setbox
	xor	ch,ch
	push	si
	les	di,[ds:si+soft_w.bordur]
	mov	ax,[word ptr ds:si+soft_w.Y]
	mov	bx,[word ptr ds:si+soft_w.Y1]
	sub	bl,al
	inc	bl
	sub	bh,ah
	inc	bh
	mov	ah,[ds:si+soft_w.setup.attr_box]
	add	si,offset 0+soft_w.setup.box
	lodsb
	stosw
	mov	cl,bh
	lodsb
	rep stosw
	lodsb
	stosw
	lodsb
	mov	dl,al
	lodsb
	mov	dh,al
	mov	cl,bl
@@loop:
	mov	al,dh
	stosw
	mov	al,dl
	stosw
	loop	@@loop
	lodsb
	stosw
	lodsb
	mov	cl,bh
	rep stosw
	lodsb
	stosw
	pop	si
	ret
endp