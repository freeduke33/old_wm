public WM_UPDATESCR

proc pascal WM_UPDATESCR far
	cmp	[cs:WMX_FREEZE],0
	jne	@@no_update
	push	ds
	push	si
	push	di

	lds	si,[cs:WM_WINDOWS]
	les	di,[cs:WM_DISPLAY]
	mov	cx,[cs:Vregen]
	cld
	mov	al,[byte ptr cs:WM_SHOWCHECK]
	or	al,al
	jz	@@direct
	mov	dx,3dah
@@put:
	lodsw
	mov	bx,ax
@@wait:
	in	al,dx
	test	al,1
	jz	@@wait
	mov	ax,bx
	stosw
	loop	@@put
@@exit:
	pop	di
	pop	si
	pop	ds
@@no_update:
	ret
@@direct:
	rep movsw
	jmp	@@exit
endp
