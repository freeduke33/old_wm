; putstr, putattr

proc putstr
;
; bx x:y
; ax character
; cx length
; dl axis
;
	push	es

	push	ax
	mov	ax,1
	cmp	dl,0
	je	@@go
	cmp	dl,1
	je	@@invers
	mov	ax,[cs:Vwidth]
	cmp	dl,2
	je	@@go
@@invers:
	not	ax
	inc	ax
@@go:
	les	di,[cs:WM_WINDOWS]
	shl	ax,1
	mov	dx,ax
	mov	ax,[cs:Vwidth]
	mul     bl
	shl	ax,1
	add	di,ax
	mov	al,bh
	cbw
	shl	ax,1
	add	di,ax
	pop	ax
@@loc:
	mov	[es:di],ax
	add	di,dx
	loop	@@loc
	pop	es
	ret
endp

proc putattr
;
; bx x:y
; al attrib
; cx length
; dl axis
;
	push	es

	push	ax
	mov	ax,1
	cmp	dl,0
	je	@@go
	cmp	dl,1
	je	@@invers
	mov	ax,[cs:Vwidth]
	cmp	dl,2
	je	@@go
@@invers:
	not	ax
	inc	ax
@@go:
	les	di,[cs:WM_WINDOWS]
	shl	ax,1
	mov	dx,ax
	mov	ax,[cs:Vwidth]
	mul     bl
	shl	ax,1
	add	di,ax
	mov	al,bh
	cbw
	shl	ax,1
	add	di,ax
	inc	di
	pop	ax
@@loc:
	mov	[es:di],al
	add	di,dx
	loop	@@loc
	pop	es
	ret
endp
