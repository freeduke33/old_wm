public WM__GETARRAY,W__PUTARRAY

proc pascal WM__GETARRAY far
arg wind:dword,x:byte,y:byte,len:word,axis:word,str:dword
	push	ds
	push	si
	push	di

	lds	si,[wind]
	mov	ax,[ds:si+soft_w.XX]
	mov	bl,[y]
	xor	bh,bh
	mul	bx
	mov	bl,[x]
	shl	bx,1
	add	bx,ax
	mov	ax,[axis]
	mov	dx,2
	cmp	al,0
	je	@@copy
	cmp	al,1
	je	@@invers
	mov	dx,[ds:si+soft_w.XX]
	shl	dx,1
	cmp	al,2
	je	@@copy
	cmp	al,3
	jne	@@none
@@invers:
	not	dx
	inc	dx
@@copy:
	lds	si,[ds:si+soft_w.data]
	add	si,bx
	les	di,[str]
	mov	cx,[len]
@@loc:
	mov	ax,[ds:si]
	stosw
	add	si,dx
	loop	@@loc
@@none:
	pop	di
	pop	si
	pop	ds
	ret
endp

proc pascal WM__PUTARRAY far
arg wind:dword,x:byte,y:byte,len:word,axis:word,str:dword
	push	ds
	push	si
	push	di

	lds	si,[wind]
	mov	ax,[ds:si+soft_w.XX]
	shl	ax,1
	mov	bl,[y]
	xor	bh,bh
	mul	bx
	mov	bl,[x]
	shl	bx,1
	add	bx,ax
	mov	ax,[axis]
	mov	dx,2
	cmp	al,0
	je	@@copy
	cmp	al,1
	je	@@invers
	mov	dx,[ds:si+soft_w.XX]
	shl	dx,1
	cmp	al,2
	je	@@copy
	cmp	al,3
	jne	@@none
@@invers:
	not	dx
	inc	dx
@@copy:
	les	di,[ds:si+soft_w.data]
	add	di,bx
	lds	si,[str]
	mov	cx,[len]
@@loc:
	lodsw
	mov	[es:di],ax
	add	di,dx
	loop	@@loc
@@none:
	pop	di
	pop	si
	pop	ds
	ret
	ret
endp
