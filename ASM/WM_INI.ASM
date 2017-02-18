public WMX_INIT,WMX_DEINIT

proc pascal WMX_DEINIT far
	mov	bh,[cs:Vpage]
	mov	cx,[cs:cSize]
	mov	ah,1
	int	10h
	mov	dx,[cs:cPos]
	mov     ah,2
	int 	10h
	mov	ax,ws_OK
	ret
endp


; Инициализировать переменные пакета
proc  pascal WMX_INIT far
	push	ds
	push	si
	push	di
	mov	ah,03
	int	10h
	mov	[cs:cPos],dx
	mov	[cs:cSize],cx

	mov	ah,0fh
	int	10h
	mov	dl,ah
	xor	dh,dh
	mov	[cs:Vpage],bh
	mov	[cs:Vwidth],dx
	cmp	al,07
	jne	@@no_mono
	mov	[word ptr cs:WM_DISPLAY+2],0b000h
	jmp	short @@offset
@@no_mono:
	cmp	al,3
	ja	@@no_text
	mov	[word ptr cs:WM_DISPLAY+2],0b800h
@@offset:
	xor	ax,ax
	mov	ds,ax
	mov	ax,[ds:44eh]
	mov	[word ptr cs:WM_DISPLAY],ax
	mov	ax,[ds:44ch]
	mov     bx,dx
	xor	dx,dx
	shr	ax,1
	div	bx
	mov	[cs:Vheight],ax
	mul	bx
	mov	[cs:Vregen],ax
	mov	ax,ws_OK
	jmp	@@exit
@@no_text:
	mov	ax,ws_VMODE
@@exit:
	pop	di
	pop	si
	pop	ds
	ret
endp
