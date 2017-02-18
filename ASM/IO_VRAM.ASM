.model small
LOCALS
IDEAL


include "asm\wm_io.inc"

; redisplay buffer
public WMX_UPDATE
; redraw all windows into buffer & redisplay buffer
public WMX_REDRAW
; store display into buffer
public WMX_SAVE

; put single char into window
public WMX_SAYCHAR
; cursor on/off
public WMX_CURSORON,WMX_CURSOROFF
; redisplay window
public WMX_PUTWINDOW
; scroll window & redisplay it
public WMX_SCROLL

extrn           WMX_DISPLAY:dword
extrn           WMX_MAP:dword
extrn           WMX_TOP:dword
extrn           WMX_WINDOWS:dword
extrn           WMX_SHOWCHECK:byte
extrn           WMX_FREEZE:byte

extrn           WM_XSCR:word
Vwidth          equ             WM_XSCR
extrn           WM_YSCR:word
Vheight         equ             WM_YSCR
extrn           Vregen:word
extrn           Vpage:byte
extrn           WM_CPOS:word
extrn           WM_CSIZE:word
Vsize           equ             WM_CSIZE
cPos            equ             WM_CPOS
cSize           equ             WM_CSIZE

extrn           BeginP:word
extrn           lenH:word
extrn           lenV:word
extrn           _wm_actwin:dword




CODESEG



proc WMX_UPDATE pascal far
        cmp     [cs:WMX_FREEZE],0
        jne     @@no_update
        push    ds
        push    si
        push    di

        lds     si,[cs:WMX_WINDOWS]
        les     di,[cs:WMX_DISPLAY]
        mov     cx,[cs:Vregen]
        cld
        mov     al,[byte ptr cs:WMX_SHOWCHECK]
        or      al,al
        jz      @@direct
        mov     dx,3dah
@@put:
        lodsw
        mov     bx,ax
@@wait:
        in      al,dx
        test    al,1
        jz      @@wait
        mov     ax,bx
        stosw
        loop    @@put
@@exit:
        pop     di
        pop     si
        pop     ds
@@no_update:
        ret
@@direct:
        rep movsw
        jmp     @@exit
endp

proc WMX_CURSORON pascal far
        cmp     [cs:WMX_FREEZE],0
        je      @@ok
        ret
@@ok:
        push    ds
        push    si
        lds     si,[_wm_actwin]
        mov     ax,[ds:si+soft_w.Control]
        test    ax,_CURSOR
        jz      @@no_put

        mov     al,[ds:si+soft_w.X]
        xor     ah,ah
        add     ax,[ds:si+soft_w.Xpos]
        sub     ax,[ds:si+soft_w.dXX]
        mov     bx,[cs:Vwidth]
        cmp     al,bl
        ja      @@no_put
        mov     dl,al
        mov     al,[ds:si+soft_w.Y]
        add     ax,[ds:si+soft_w.Ypos]
        sub     ax,[ds:si+soft_w.dYY]
        cmp     al,[byte ptr cs:Vheight]
        ja      @@no_put
        mov     dh,al
        mov     ax,bx
        mul     dh
        add     al,dl
        adc     ah,0
        mov     bx,[ds:si+soft_w.handle]
        lds     si,[cs:WMX_MAP]
        add     si,ax
        lodsb
        and     al,7fh
        cmp     al,bl
        jne     @@no_put
        mov     bl,[cs:Vpage]
        mov     ah,2
        int     10h
        mov     cx,[cs:Vsize]
@@set:
        mov     ah,1
        int     10h
        pop     si
        pop     ds
        ret
@@no_put:
        mov     cx,2000h
        jmp     @@set
endp

proc WMX_CURSOROFF pascal far
        cmp     [cs:WMX_FREEZE],0
        jne     @@no
        mov     cx,2000h
        mov     ah,1
        int     10h
@@no:
        ret
endp


proc WMX_SAYCHAR pascal far
arg wind:dword,x:word,y:word,character:word
        push    ds
        push    si
        push    di
        lds     si,[wind]
        mov     dx,[x]
        mov     bx,[y]
        mov     ax,[ds:si+soft_w.XX]
        mul     bl
        shl     ax,1
        shl     dx,1
        add     ax,dx
        les     di,[ds:si+soft_w.data]
        add     di,ax
        mov     ax,[character]
        stosw
        cmp     [cs:WMX_FREEZE],0
        jne     @@no_put
        test    [ds:si+soft_w.Control],_HIDDEN
        jnz     @@no_put
        shr     dx,1
        sub     dx,[ds:si+soft_w.dXX]
        add     dl,[ds:si+soft_w.X]
        sub     bx,[ds:si+soft_w.dYY]
        add     bl,[ds:si+soft_w.Y]
        mov     ax,[cs:Vwidth]
        mov     cx,dx
        mul     bx
        add     ax,cx
        cmp     ax,[cs:Vregen]
        ja      @@no_put
        mov     dx,ax
        les     di,[cs:WMX_MAP]
        add     di,ax
        mov     al,[es:di]
        mov     ah,[byte ptr ds:si+soft_w.handle]
        xor     al,ah
        jz      @@put
        cmp     al,80h
        jne     @@no_put
@@put:
        shl     dx,1
        les     di,[cs:WMX_DISPLAY]
        add     di,dx
        mov     dl,al
        mov     ax,[character]
        stosb
        or      dl,dl
        jnz     @@no_put
        mov     al,ah
        stosb
@@no_put:
        pop     di
        pop     si
        pop     ds
        ret
endp


proc WMX_REDRAW pascal far
        push    ds
        push    si
        push    di
        call    far WMX_CURSOROFF

        lds     si,[cs:WMX_TOP]
@@next:
        mov     ax,ds
        or      ax,si
        jz      @@exit
        call    putwindow
        lds     si,[ds:si+soft_w.next]
        jmp     @@next
@@exit:
        call    far WMX_UPDATE
        pop     di
        pop     si
        pop     ds
        call    far WMX_CURSORON
        ret
endp

proc WMX_PUTWINDOW pascal far
arg wHandle:word
        push    ds
        push    si
        push    di

        lds     si,[cs:WMX_TOP]
@@next:
        mov     ax,ds
        or      ax,si
        jz      @@exit
        mov     ax,[ds:si+soft_w.handle]
        cmp     ax,[wHandle]
        je      @@put
        lds     si,[ds:si+soft_w.next]
        jmp     @@next
@@put:
        call    putwindow
@@exit:
        pop     di
        pop     si
        pop     ds
        ret
endp

proc putwindow
        mov     ax,[ds:si+soft_w.Control]
        test    ax,_HIDDEN
        jz      @@continue
        ret
@@continue:
        push    ds
        push    si
        push    di
        push    bp

;
; подготовка к рисованию окна
;
        push    ax
        les     di,[cs:WMX_WINDOWS]
        mov     ax,[cs:Vwidth]
        mov     dx,ax
        mov     bx,[word ptr ds:si+soft_w.Y]  ; x:y
        mul     bl
        add     al,bh
        adc     ah,0
        shl     ax,1
        add     di,ax
        mov     [cs:BeginP],di
        mov     ax,[word ptr ds:si+soft_w.Y1]  ; x1:y1
        sub     al,bl
        inc     al
        sub     ah,bh
        inc     ah
        mov     [byte ptr cs:lenH],ah
        mov     [byte ptr cs:lenV],al
;
; дальше окно
;
        push    si
        push    ds
        mov     ax,[ds:si+soft_w.dYY]
        mov     bx,[ds:si+soft_w.XX]
        mul     bx
        add     ax,[ds:si+soft_w.dXX]
        shl     ax,1
        lds     si,[ds:si+soft_w.data]
        add     si,ax

        mov     dx,[cs:Vwidth]
        mov     cx,[cs:lenV]
        mov     ax,[cs:lenH]
        sub     dx,ax
        shl     dx,1
        sub     bx,ax
        shl     bx,1

@@line:
        mov     bp,cx
        mov     cx,ax
        rep     movsw
        add     si,bx
        add     di,dx
        mov     cx,bp
        loop    @@line
        pop     ds
        pop     si

;
; рисуем бордюр
;
        pop     ax
        test    ax,_BORDUR
        jz      @@no_box
        push    ax

        add     [cs:lenH],2
        mov     ax,[cs:Vwidth]
        inc     ax
        shl     ax,1
        sub     [cs:BeginP],ax
        push    ds
        push    si
        mov     di,[cs:BeginP]
        lds     si,[ds:si+soft_w.bordur]
        sub     ax,2
        sub     dx,4
        sub     ax,dx
        mov     cx,ax
        shr     cx,1
        rep     movsw
        mov     cx,[cs:lenV]
        sub     ax,4
@@loop1:
        add     di,dx
        movsw
        add     di,ax
        movsw
        loop    @@loop1
        add     ax,4
        add     di,dx
        mov     cx,ax
        shr     cx,1
        rep     movsw
        pop     si
        pop     ds
        add     [cs:lenV],2

        pop     ax
@@no_box:
;
; теперь рисуем тени
;
        test    ax,_SHADOW
        jz      @@no_shadow
        mov     al,[ds:si+soft_w.setup.shadow_ch]
        mov     ah,[ds:si+soft_w.setup.attr_shadow]
        mov     di,[cs:BeginP]
        mov     bx,[cs:Vwidth]
        dec     bx
        dec     bx
        shl     bx,1
        mov     dx,[cs:lenH]
        inc     dx
        inc     dx
        shl     dx,1
        add     di,dx
        mov     cx,[cs:lenV]
        dec     cx
        jcxz    @@next
        or      al,al
        jz      @@attr2
@@loop2:
        add     di,bx
        stosw
        stosw
        loop    @@loop2
        jmp     short @@next
@@attr2:
        xchg    al,ah
@@loop2a:
        add     di,bx
        inc     di
        stosb
        inc     di
        stosb
        loop    @@loop2a
        xchg    al,ah
@@next:
        sub     dx,8
        sub     bx,dx
        shr     dx,1
        inc     dx
        inc     dx
        mov     cx,dx
        add     di,bx
        or      al,al
        jz      @@attr3a
        rep stosw
        jmp     @@no_shadow
@@attr3a:
        xchg    al,ah
@@loop3a:
        inc     di
        stosb
        loop    @@loop3a
@@no_shadow:
        pop     bp
        pop     di
        pop     si
        pop     ds
        ret
endp

proc WMX_SCROLL pascal far
arg wind:dword,num:word,fill:word
        push    ds
        push    si
        push    di
        lds     si,[wind]

        mov     al,[ds:si+soft_w.setup.attr_say]
        mov     [byte ptr fill+1],al
        mov     bx,[ds:si+soft_w.YY]
        cmp     bx,[num]
        jae     @@large
        mov     [num],bx
@@large:
        mov     ax,[ds:si+soft_w.XX]
        shl     ax,1
        mov     cx,ax
        mul     bx
        xchg    ax,cx
        sub     bx,[num]
        mul     bx
        sub     cx,ax
        les     di,[ds:si+soft_w.data]
        mov     bx,es
        mov     ds,bx
        mov     si,di
        add     si,cx
        xchg    ax,cx
        cld
        jcxz    @@no
        rep movsb
@@no:
        shr     ax,1
        mov     cx,ax
        jcxz    @@no1
        mov     ax,[fill]
        rep stosw
@@no1:
        pop     di
        pop     si
        pop     ds
        call    far WMX_REDRAW
        ret
endp


proc WMX_SAVE pascal far
arg data:dword
        push    ds
        push    di
        push    si
        mov     cx,[cs:Vregen]
        les     di,[data]
        lds     si,[cs:WMX_DISPLAY]
        rep     movsw
        pop     si
        pop     di
        pop     ds
        ret
endp


end

