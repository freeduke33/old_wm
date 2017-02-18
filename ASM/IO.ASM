.model small
LOCALS
IDEAL

; internal variables
public WMX_DISPLAY,WMX_WINDOWS,WMX_TOP,WMX_FREEZE,WMX_SHOWCHECK,WMX_MAP
public WM_XSCR,WM_YSCR,WM_CPOS,WM_CSIZE,Vregen,Vpage,BeginP,lenH,lenV

; internal routines
public WMX_SETMAP,WMX_RESETMAP,WMX_INIT,WMX_DEINIT,WMX_BORDER

include "asm\wm_io.inc"

CODESEG

; Инициализировать переменные пакета
proc WMX_INIT pascal far
        push    ds
        push    si
        push    di
        mov     ah,03
        int     10h
        mov     [cs:cPos],dx
        mov     [cs:cSize],cx

        mov     ah,0fh
        int     10h
        mov     dl,ah
        xor     dh,dh
        mov     [cs:Vpage],bh
        mov     [cs:Vwidth],dx
        cmp     al,07
        jne     @@no_mono
        mov     [word ptr cs:WMX_DISPLAY+2],0b000h
        jmp     short @@offset
@@no_mono:
        cmp     al,3
        ja      @@no_text
        mov     [word ptr cs:WMX_DISPLAY+2],0b800h
@@offset:
        xor     ax,ax
        mov     ds,ax
        mov     ax,[ds:44eh]
        mov     [word ptr cs:WMX_DISPLAY],ax
        mov     ax,[ds:44ch]
        mov     bx,dx
        xor     dx,dx
        shr     ax,1
        div     bx
        mov     [cs:Vheight],ax
        mul     bx
        mov     [cs:Vregen],ax
        mov     ax,ws_OK
        jmp     @@exit
@@no_text:
        mov     ax,ws_VMODE
@@exit:
        pop     di
        pop     si
        pop     ds
        ret
endp

proc WMX_DEINIT pascal far
        mov     bh,[cs:Vpage]
        mov     cx,[cs:cSize]
        mov     ah,1
        int     10h
        mov     dx,[cs:cPos]
        mov     ah,2
        int     10h
        mov     ax,ws_OK
        ret
endp


proc WMX_SETMAP pascal far
arg wind:word
        push    ds
        push    si
        push    di

        mov     dx,[wind]
        lds     si,[cs:WMX_TOP]
@@next:
        mov     ax,ds
        or      ax,si
        jz      @@end
        cmp     dx,[ds:si+soft_w.handle]
        je      @@update
        lds     si,[ds:si+soft_w.next]
        jmp     @@next
@@update:
        call    near ws_setmap
@@end:
        pop     di
        pop     si
        pop     ds
        ret
endp

proc WMX_RESETMAP pascal far
        push    ds
        push    si
        push    di
        lds     si,[cs:WMX_TOP]
@@next:
        mov     ax,ds
        or      ax,si
        je      @@end
        mov     dx,[ds:si+soft_w.handle]
        call    near ws_setmap
        lds     si,[ds:si+soft_w.next]
        jmp     @@next
@@end:
        pop     di
        pop     si
        pop     ds
        ret
endp

proc ws_setmap near
        mov     ax,[ds:si+soft_w.Control]
        test    ax,_HIDDEN
        jnz     @@no_map
        mov     bx,[word ptr ds:si+soft_w.Y]
        mov     cx,[word ptr ds:si+soft_w.Y1]
        inc     cl
        inc     ch
        push    bx
        push    cx

        test    ax,_BORDUR
        jz      @@ok_coord
        inc     cl
        dec     bl
        inc     ch
        dec     bh
        push    bx
        push    cx
@@ok_coord:

        test    ax,_SHADOW
        jz      @@no_shadow
        inc     cl
        inc     ch
        inc     ch

        inc     bl
        inc     bh
        inc     bh

        push    ax
        mov     dl,07eh
        cmp     [ds:si+soft_w.setup.shadow_ch],0
        jne     @@ok
        inc     dl
        inc     dl
@@ok:
        call    map
        pop     ax
@@no_shadow:
        test    ax,_BORDUR
        jz      @@no_box
        pop     cx
        pop     bx
        mov     dx,07eh
        call    map
@@no_box:
        pop     cx
        pop     bx
        mov     dx,[ds:si+soft_w.handle]
        call    map
@@no_map:
        ret
endp

proc map
        cmp     cl,bl
        je      @@abort
        cmp     ch,bh
        je      @@abort
        mov     ax,[cs:Vwidth]
        mov     dh,al
        mul     bl
        sub     ch,bh   ; число столбцов
        sub     cl,bl   ; число строк
        sub     dh,ch   ; пропуск
        mov     bl,bh
        xor     bh,bh
        add     ax,bx
        les     di,[cs:WMX_MAP]
        add     di,ax
        mov     bl,ch
        xor     ch,ch
        mov     al,dl
        mov     ah,al

        mov     dl,dh
        xor     dh,dh
@@loc:
        mov     bh,cl
        mov     cl,bl
@@line:
        cmp     ah,80h
        jne     @@put
        mov     al,[es:di]
        or      al,ah
@@put:
        stosb
        loop    @@line
        add     di,dx
        mov     cl,bh
        loop    @@loc
@@abort:
        ret
endp map

proc WMX_BORDER pascal far
arg wind:dword
        push    di
        push    si
        push    ds
        lds     si,[wind]
        call    setbox
        pop     ds
        pop     si
        pop     di
        ret
endp

proc setbox
        xor     ch,ch
        push    si
        les     di,[ds:si+soft_w.bordur]
        mov     ax,[word ptr ds:si+soft_w.Y]
        mov     bx,[word ptr ds:si+soft_w.Y1]
        sub     bl,al
        inc     bl
        sub     bh,ah
        inc     bh
        mov     ah,[ds:si+soft_w.setup.attr_box]
        add     si,offset 0+soft_w.setup.box
        lodsb
        stosw
        mov     cl,bh
        lodsb
        rep stosw
        lodsb
        stosw
        lodsb
        mov     dl,al
        lodsb
        mov     dh,al
        mov     cl,bl
@@loop:
        mov     al,dh
        stosw
        mov     al,dl
        stosw
        loop    @@loop
        lodsb
        stosw
        lodsb
        mov     cl,bh
        rep stosw
        lodsb
        stosw
        pop     si
        ret
endp


WMX_DISPLAY      dd              0
WMX_MAP          dd              0
WMX_TOP          dd              0
WMX_WINDOWS      dd              0
WMX_SHOWCHECK    db              0
WMX_FREEZE       db              0

WM_XSCR         dw              80
Vwidth          equ             WM_XSCR
WM_YSCR         dw              0
Vheight         equ             WM_YSCR
Vregen          dw              0
Vpage           db              0
WM_CPOS         dw              0
WM_CSIZE        dw              0
Vsize           equ             WM_CSIZE
cPos            equ             WM_CPOS
cSize           equ             WM_CSIZE

BeginP          dw              0
lenH            dw              0
lenV            dw              0

end

