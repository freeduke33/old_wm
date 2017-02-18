public WM_RESTORECRT,WM_PUTWINDOW,WM__SCROLL

proc pascal WM_RESTORECRT far
	push	ds
	push	si
	push	di
	call	far WM_CURSOROFF

	lds	si,[cs:WM_TOP]
@@next:
	mov	ax,ds
	or	ax,si
	jz	@@exit
	call	putwindow
	lds	si,[ds:si+soft_w.next]
	jmp	@@next
@@exit:
	call	far WM_UPDATESCR
	pop	di
	pop	si
	pop	ds
	call	far WM_CURSORON
	ret
endp

proc pascal WM_PUTWINDOW far
arg wHandle:word
	push	ds
	push	si
	push	di

	lds	si,[cs:WM_TOP]
@@next:
	mov	ax,ds
	or	ax,si
	jz	@@exit
	mov	ax,[ds:si+soft_w.handle]
	cmp     ax,[wHandle]
	je	@@put
	lds	si,[ds:si+soft_w.next]
	jmp	@@next
@@put:
	call	putwindow
@@exit:
	pop	di
	pop	si
	pop	ds
	ret
endp

proc putwindow
	mov	ax,[ds:si+soft_w.Control]
	test	ax,_HIDDEN
	jz	@@continue
	ret
@@continue:
	push	ds
	push	si
	push	di
	push	bp

;
; подготовка к рисованию окна
;
	push	ax
	les	di,[cs:WM_WINDOWS]
	mov	ax,[cs:Vwidth]
	mov	dx,ax
	mov	bx,[word ptr ds:si+soft_w.Y]  ; x:y
	mul	bl
	add	al,bh
	adc	ah,0
	shl	ax,1
	add	di,ax
	mov	[cs:BeginP],di
	mov	ax,[word ptr ds:si+soft_w.Y1]  ; x1:y1
	sub	al,bl
	inc	al
	sub	ah,bh
	inc	ah
	mov	[byte ptr cs:lenH],ah
	mov	[byte ptr cs:lenV],al
;
; дальше окно
;
	push	si
	push	ds
	mov	ax,[ds:si+soft_w.dYY]
	mov	bx,[ds:si+soft_w.XX]
	mul	bx
	add	ax,[ds:si+soft_w.dXX]
	shl	ax,1
	lds	si,[ds:si+soft_w.data]
	add	si,ax

	mov	dx,[cs:Vwidth]
	mov	cx,[cs:lenV]
	mov	ax,[cs:lenH]
	sub	dx,ax
	shl	dx,1
	sub	bx,ax
	shl	bx,1

@@line:
	mov	bp,cx
	mov	cx,ax
	rep	movsw
	add	si,bx
	add	di,dx
	mov	cx,bp
	loop	@@line
	pop	ds
	pop	si

;
; рисуем бордюр
;
	pop	ax
	test	ax,_BORDUR
	jz	@@no_box
	push	ax

	add	[cs:lenH],2
	mov	ax,[cs:Vwidth]
	inc	ax
	shl	ax,1
	sub	[cs:BeginP],ax
	push	ds
	push	si
	mov	di,[cs:BeginP]
	lds	si,[ds:si+soft_w.bordur]
	sub	ax,2
	sub	dx,4
	sub	ax,dx
	mov	cx,ax
	shr	cx,1
	rep	movsw
	mov	cx,[cs:lenV]
	sub	ax,4
@@loop1:
	add	di,dx
	movsw
	add	di,ax
	movsw
	loop	@@loop1
	add	ax,4
	add	di,dx
	mov	cx,ax
	shr	cx,1
	rep	movsw
	pop	si
	pop	ds
	add	[cs:lenV],2

	pop	ax
@@no_box:
;
; теперь рисуем тени
;
	test 	ax,_SHADOW
	jz	@@no_shadow
	mov	al,[ds:si+soft_w.setup.shadow_ch]
	mov	ah,[ds:si+soft_w.setup.attr_shadow]
	mov	di,[cs:BeginP]
	mov	bx,[cs:Vwidth]
	dec	bx
	dec	bx
	shl	bx,1
	mov	dx,[cs:lenH]
	inc	dx
	inc	dx
	shl	dx,1
	add	di,dx
	mov	cx,[cs:lenV]
	dec	cx
	jcxz	@@next
	or	al,al
	jz	@@attr2
@@loop2:
	add	di,bx
	stosw
	stosw
	loop	@@loop2
	jmp	short @@next
@@attr2:
	xchg	al,ah
@@loop2a:
	add	di,bx
	inc	di
	stosb
	inc	di
	stosb
	loop	@@loop2a
	xchg	al,ah
@@next:
	sub	dx,8
	sub	bx,dx
	shr	dx,1
	inc	dx
	inc	dx
	mov	cx,dx
	add	di,bx
	or	al,al
	jz	@@attr3a
	rep stosw
	jmp	@@no_shadow
@@attr3a:
	xchg	al,ah
@@loop3a:
	inc	di
	stosb
	loop	@@loop3a
@@no_shadow:
	pop	bp
	pop	di
	pop	si
	pop	ds
	ret
endp

proc pascal WM__SCROLL far
arg wind:dword,num:word,fill:word
	push	ds
	push	si
	push	di
	lds	si,[wind]

	mov	al,[ds:si+soft_w.setup.attr_say]
	mov	[byte ptr fill+1],al
	mov	bx,[ds:si+soft_w.YY]
	cmp	bx,[num]
	jae	@@large
	mov	[num],bx
@@large:
	mov	ax,[ds:si+soft_w.XX]
	shl	ax,1
	mov	cx,ax
	mul	bx
	xchg	ax,cx
	sub	bx,[num]
	mul	bx
	sub	cx,ax
	les	di,[ds:si+soft_w.data]
	mov	bx,es
	mov	ds,bx
	mov	si,di
	add	si,cx
	xchg	ax,cx
	cld
	jcxz	@@no
	rep movsb
@@no:
	shr	ax,1
	mov	cx,ax
	jcxz	@@no1
	mov	ax,[fill]
	rep stosw
@@no1:
	pop	di
	pop	si
	pop	ds
	call	far WM_RESTORECRT
	ret
endp
