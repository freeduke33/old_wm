public WM_SETMAP,WM_RESETMAP

proc  pascal  WM_SETMAP far
arg wind:word
	push	ds
	push	si
	push	di

	lds	si,[cs:WM_TOP]
	mov	dx,[wind]
@@next:
	mov	ax,ds
	or	ax,si
	jz	@@end
	cmp	dx,[ds:si+soft_w.handle]
	je	@@update
	lds	si,[ds:si+soft_w.next]
	jmp	@@next
@@update:
	call	ws_setmap
@@end:
	pop	di
	pop	si
	pop	ds
	ret
endp

proc pascal WM_RESETMAP far
	push	ds
	push	si
	push	di
	lds	si,[cs:WM_TOP]
@@next:
	mov	ax,ds
	or	ax,si
	je	@@end
	mov	dx,[ds:si+soft_w.handle]
	call	ws_setmap
	lds	si,[ds:si+soft_w.next]
	jmp	@@next
@@end:
	pop	di
	pop	si
	pop	ds
	ret
endp

proc pascal ws_setmap
	mov	ax,[ds:si+soft_w.Control]
	test	ax,_HIDDEN
	jnz	@@no_map
	mov	bx,[word ptr ds:si+soft_w.Y]
	mov	cx,[word ptr ds:si+soft_w.Y1]
	inc	cl
	inc	ch
	push	bx
	push	cx

	test	ax,_BORDUR
	jz	@@ok_coord
	inc	cl
	dec	bl
	inc	ch
	dec	bh
	push	bx
	push	cx
@@ok_coord:

	test	ax,_SHADOW
	jz	@@no_shadow
	inc	cl
	inc	ch
	inc	ch

	inc	bl
	inc	bh
	inc	bh

	push	ax
	mov	dl,07eh
	cmp	[ds:si+soft_w.setup.shadow_ch],0
	jne	@@ok
	inc	dl
	inc	dl
@@ok:
	call	map
	pop	ax
@@no_shadow:
	test	ax,_BORDUR
	jz	@@no_box
	pop	cx
	pop	bx
	mov	dx,07eh
	call	map
@@no_box:
	pop	cx
	pop	bx
	mov	dx,[ds:si+soft_w.handle]
	call	map
@@no_map:
	ret
endp

proc map
	cmp	cl,bl
	je	@@abort
	cmp	ch,bh
	je	@@abort
	mov	ax,[cs:Vwidth]
	mov	dh,al
	mul	bl
	sub	ch,bh	; число столбцов
	sub	cl,bl	; число строк
	sub	dh,ch	; пропуск
	mov	bl,bh
	xor	bh,bh
	add	ax,bx
	les	di,[cs:WM_MAP]
	add	di,ax
	mov	bl,ch
	xor	ch,ch
	mov	al,dl
	mov	ah,al

	mov	dl,dh
	xor	dh,dh
@@loc:
	mov	bh,cl
	mov	cl,bl
@@line:
	cmp	ah,80h
	jne	@@put
	mov	al,[es:di]
	or	al,ah
@@put:
	stosb
	loop	@@line
	add	di,dx
	mov	cl,bh
	loop	@@loc
@@abort:
	ret
endp map
