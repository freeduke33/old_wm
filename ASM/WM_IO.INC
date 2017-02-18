
_BORDUR 	=	10000000b
_SHADOW 	=	01000000b
_COOKED 	=	00100000b
_HIDDEN 	=	00010000b
_CURSOR 	=	00001000b
_SCROLL 	=	00000100b
_SCROLBARS	=	00000010b
_FREEZE 	=	00000001b

ws_OK		=	0
ws_VIRTSIZE	=	1
ws_VMODE	=	2


struc wm_set
box		db	8 dup(?)
attr_box	db	0
shadow_ch	db	0
attr_shadow	db	0
attr_say	db	0
attr_actget	db	0
attr_nactget	db	0
attr_title	db	0
ends wm_set

struc soft_w
Control 	dw	0
handle		dw	0
memory		db	0
Y		db	0
X		db	0
Y1		db	0
X1		db	0

XX		dw	0
YY		dw	0
dXX		dw	0
dYY		dw	0
Xpos		dw	0
Ypos		dw	0
Metod		dd	0
setup		wm_set	?
titl		dd	12 dup(0)
bordur		dd	0
data		dd	0
next		dd	0
ends soft_w

