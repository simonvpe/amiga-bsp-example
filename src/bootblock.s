; Bootblock example code by Blueberry / Loonies, 23/9-2012
; Public Domain

WRITEFLAG = 0	; 1 TO WRITE BOOTBLOCK TO DF0

SCREENWIDTH = 320
SCREENHEIGHT = 256
SCREENDEPTH = 4

	printv	BB_SIZE
	printv	SPACE_SIZE

	if	WRITEFLAG=1
	auto	c\BB_START\BB_START+1024\sector\
	auto	ws\sector\0\2\cc\
	endc


; System constants
_LVOFindResident = -96
_LVOLoadView = -222
_LVOWaitTOF = -270
gb_ActiView = 34
gb_copinit = 38
IVBLIT = 156
RT_INIT = 22


	; Testing wrapper - for running bootblock during development
Test:
	; Store old view
	move.l	$4.w,a6
	move.l	IVBLIT(a6),a6
	move.l	gb_ActiView(a6),-(a7)

	; Switch to PAL
	suba.l	a1,a1
	jsr	_LVOLoadView(a6)
	move.w	#$0020,$dff1dc
	jsr	_LVOWaitTOF(a6)
	jsr	_LVOWaitTOF(a6)

	; Call the bootblock
	move.l	$4.w,a6
	jsr	BB_START+12

	; Enable DMAs and interrupts
	move.w	#$83e0,$dff096
	move.w	#$c000,$dff09a

	; Wait for LMB release
.wait:
	btst.b	#6,$BFE001
	beq.b	.wait

	; Restore view
	move.l	$4.w,a6
	move.l	IVBLIT(a6),a6
	move.l	(a7)+,a1
	jsr	_LVOLoadView(a6)
	rts

	if	WRITEFLAG
	; Chip buffer to write bootblock from
	section	sector,bss_c
sector:	ds.b	1024
	endc


	section	BB,code

; The bootblock starts here.
; It cannot generally be assumed to be placed in a specific
; kind of memory, or at any specific address, so all code
; must be completely PC relative, and all chip data must
; be explicitly copied to chip memory.

BB_START:
	DC.B	'DOS',0
	DC.L	0
	DC.L	880

J:
	; Bootblock code goes here.

	movem.l	d0-a6,-(a7)

	; Global pointer to chip space in A4
	if	WRITEFLAG
	; Chip space at the end of (512k) chip memory
	lea.l	$80000-SPACE_SIZE,a4
	else
	; Chip space in a section
	lea.l	Space,a4
	endc

	; Copy copperlist to chip
	lea.l	CopperData(pc),a0
	lea.l	Copper-Space(a4),a1
	moveq.l	#(CopperData_End-CopperData)/4-1,d7
.coploop:
	move.l	(a0)+,(a1)+
	dbf	d7,.coploop

	; Set bitplane pointers
	lea.l	Screen-Space(a4),a2
	move.w	#$0e0,d3
	moveq.l	#SCREENDEPTH-1,d7
.bplptrloop:
	; A2 = Pointer
	; D3 = Hardware Address
	; A1 = Copper Address

	move.w	d3,(a1)+
	move.l	a2,(a1)
	addq.l	#2,a1
	addq.w	#2,d3
	move.w	d3,(a1)+
	move.w	a2,(a1)+
	addq.w	#2,d3

	lea.l	SCREENWIDTH/8(a2),a2
	dbf	d7,.bplptrloop

	; Set colors
	lea.l	ColorData(pc),a0
	move.w	#$180,d0
	moveq.l	#(1<<SCREENDEPTH)-1,d7
.colorloop:
	move.w	d0,(a1)+
	move.w	(a0)+,(a1)+
	addq.w	#2,d0
	dbf	d7,.colorloop

	; End of copperlist
	moveq.l	#-2,d0
	move.l	d0,(a1)+


	lea.l	$DFF000,A5

	; Example sound: constant minor chord
	lea.l	Waveform-Space(a4),a1
	move.w	#$7f80,(a1)
	lea.l	$0a0(a5),a2
	move.w	#3000,d0
	moveq.l	#4-1,d7
.channel:
	move.l	a1,(a2)+	; Pointer
	move.w	#1,(a2)+	; Length
	move.w	d0,(a2)+	; Period
	move.w	#10,(a2)+	; Volume
	addq.l	#6,a2
	add.w	#1000,d0
	dbf	d7,.channel

	; Turn off audio filter
	bclr.b	#1,$bfe001

	; Set copperlist
	lea.l	Copper-Space(a4),a1
	move.l	a1,$080(a5)

	; Disable interrupts and set some DMAs
	move.w	#$4000,$09a(a5)
	move.w	#$87CF,$096(a5)

	; Main per-frame loop
MainLoop:
	bsr.b	WaitVbl
	; Switch off sprite DMA
	move.w	#$0020,$096(a5)

	; Example effect: Complement random rectangle in random bitplane
	bsr.b	Effect

	; Loop until LMB
	btst.b	#6,$bfe001
	bne.b	MainLoop

Exit:
	; Turn off sound
	move.w	#$000f,$096(a5)
	; Restore registers
	movem.l	(a7)+,d0-a6
	; Restore copper
	move.l	IVBLIT(a6),a0
	move.l	gb_copinit(a0),$DFF080

	; Return init function of dos.library resident in A0
	lea.l	DosName(pc),a1
	jsr	_LVOFindResident(a6)
	move.l	d0,a0
	move.l	RT_INIT(a0),a0
	moveq.l	#0,d0
	rts

DosName:
	dc.b	'dos.library',0


WaitVbl:
	tst.b	$005(a5)
	beq.b	WaitVbl
wvb:	tst.b	$005(a5)
	bne.b	wvb
	rts

Randomseed:
	dc.w	$BEEF
Random:
	; D1 = Magnitude
	lea.l	Randomseed(pc),a0
	move.w	(a0),d0
	mulu.w	#58679,d0
	move.w	d0,(a0)
	mulu.w	d1,d0
	swap.w	d0
	; D0.w = Random
	rts

Effect:
	; Random bounds and plane
	move.w	#SCREENWIDTH,d1
	bsr.b	Random
	move.w	d0,d4
	bsr.b	Random
	move.w	d0,d6
	cmp.w	d4,d6
	bge.b	.xok
	exg.l	d4,d6
.xok:
	addq.w	#1,d6

	move.w	#SCREENHEIGHT,d1
	bsr.b	Random
	move.w	d0,d5
	bsr.b	Random
	move.w	d0,d7
	cmp.w	d5,d7
	bge.b	.yok
	exg.l	d5,d7
.yok:
	addq.w	#1,d7

	moveq.l	#SCREENDEPTH,d1
	bsr.b	Random
	; D4/D5 = Upper-left X/Y
	; D6/D7 = Lower-right X/Y
	; D0 = Plane

	; Vertical offset and size
	sub.w	d5,d7
	mulu.w	#SCREENDEPTH,d5
	add.w	d0,d5
	lea.l	Screen-Space(a4),a1
	mulu.w	#SCREENWIDTH/8,d5
	add.l	d5,a1

	; First/last word mask
	moveq.l	#15,d0
	moveq.l	#15,d1
	and.w	d4,d0
	and.w	d6,d1
	moveq.l	#-1,d2
	moveq.l	#-1,d3
	lsr.w	d0,d2
	lsr.w	d1,d3
	not.w	d3

	; Horizontal offset and size
	lsr.w	#4,d4
	lsr.w	#4,d6
	sub.w	d4,d6
	addq.w	#1,d6
	add.w	d4,d4
	add.w	d4,a1

	; Blitter size and modulo
	lsl.w	#6,d7
	add.w	d6,d7
	move.w	#SCREENWIDTH/8*SCREENDEPTH,d5
	add.w	d6,d6
	sub.w	d6,d5

	bsr.b	WaitBlit
	move.l	#$035a0000,$040(a5)	; BLTCON0/BLTCON1
	move.w	d2,$044(a5)		; BLTAFWM
	move.w	d3,$046(a5)		; BLTALWM
	move.l	a1,$048(a5)		; BLTCPTR
	move.l	a1,$054(a5)		; BLTDPTR
	move.w	d5,$060(a5)		; BLTCMOD
	move.w	d5,$066(a5)		; BLTDMOD
	move.w	#$ffff,$074(a5)		; BLTADAT
	move.w	d7,$058(a5)		; BLTSIZE
	rts

WaitBlit:
	btst	#14,$002(a5)
.wait:	btst	#14,$002(a5)
	bne.b	.wait
	rts


CopperData:
	; Example copperlist: Interleaved 320x256 screen
	dc.l	$008E2C81,$00902CC1
	dc.l	$00920038,$009400D0
	dc.l	$01000200+(SCREENDEPTH<<12)
	dc.l	$01020000,$01040000
	dc.l	$01080000+(SCREENWIDTH/8)*(SCREENDEPTH-1)
	dc.l	$010A0000+(SCREENWIDTH/8)*(SCREENDEPTH-1)
	dc.l	$01FC0000
CopperData_End:

ColorData:
	dc.w	$000,$300,$600,$900,$C00,$F00,$F30,$F60
	dc.w	$F90,$FC0,$FF0,$FF3,$FF6,$FF9,$FFC,$FFF

BB_END:
BB_SIZE	=	BB_END-BB_START
	if	BB_SIZE<1024
	dcb.b	1024-BB_SIZE,"B"
	endc


	section	space,bss_c

Space:
	; Put everything that needs to be in chip memory in this section!

Waveform:
	ds.l	1

Copper:
	ds.b	CopperData_End-CopperData
	ds.l	SCREENDEPTH*2	; Bitplane pointers
	ds.l	1<<SCREENDEPTH	; Colors
	ds.l	1		; Terminator

Screen:
	ds.l	SCREENWIDTH/32*SCREENHEIGHT*SCREENDEPTH

Space_End:

SPACE_SIZE	=	Space_End-Space
