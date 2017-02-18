public WM_SAVESCR

proc pascal WM_SAVESCR far
arg data:dword
	push	ds
	push	di
	push	si
	mov	cx,[cs:Vregen]
	les	di,[data]
	lds	si,[cs:WM_DISPLAY]
	rep	movsw
	pop	si
	pop	di
	pop	ds
	ret
endp
