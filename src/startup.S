DMACONR         EQU             $dff002
ADKCONR         EQU             $dff010
INTENAR         EQU             $dff01c
INTREQR         EQU             $dff01e

DMACON          EQU             $dff096
ADKCON          EQU             $dff09e
INTENA          EQU             $dff09a
INTREQ          EQU             $dff09c

BLTCON0         EQU             $dff040
BLTCON1         EQU             $dff042
BLTAFWM         EQU             $dff044
BLTALWM         EQU             $dff046
BLTCPTH         EQU             $dff048
BLTBPTH         EQU             $dff04C
BLTAPTH         EQU             $dff050
BLTDPTH         EQU             $dff054
BLTSIZE         EQU             $dff058
BLTBMOD         EQU             $dff062
BLTCMOD         EQU             $dff060
BLTAMOD         EQU             $dff064
BLTDMOD         EQU             $dff066

entry:
	;; store hardware registers, store view- and copperaddresses, load blank view,
	;; wait 2x for top of frame, own blitter, wait for blitter AND finally forbid multitasking!
	;; all this just to be able to exit gracely store data in hardwareregisters ORed with
	;; $8000 (bit 15 is a write-set bit when values are written back into the system)
	 
	move.w   DMACONR,d0
	or.w     #$8000,d0
	lea 	 olddmareq,a5
	move.w   d0,(a5)
	move.w   INTENAR,d0
	or.w     #$8000,d0
	lea      oldintena,a5
	move.w   d0,(a5)
	move.w   INTREQR,d0
	or.w     #$8000,d0
	lea      oldintreq,a5
	move.w   d0,(a5)
	move.w   ADKCONR,d0
	or.w     #$8000,d0
	lea      oldadkcon,a5
	move.w   d0,(a5)

        move.l  $4,a6       ; execBase ==> a6
        move.l  #gfxname,a1 ; pointer to gfxname ==> a1 : used in openLibrary
        moveq   #0,d0       ; d0 = 0 any version of graphics.library will do
        jsr     -552(a6)    ; d0 = openLibrary(a1,d0)
        lea     gfxbase,a5
        move.l  d0,(a5)     ; store the returned pointer ==> gfxbase
        move.l  d0,a6       ; d0 ==> a6 : a6 used as addressing base below
        lea     oldview,a5
        move.l  34(a6),(a5) ; store old Viewport
        lea     oldcopper,a5
        move.l  38(a6),(a5) ; store old Copperlist

        move.l  #0,a1
        jsr -222(a6)    ; LoadView
        jsr -270(a6)    ; WaitTOF
        jsr -270(a6)    ; WaitTOF
        jsr -456(a6)    ; OwnBlitter
        jsr -228(a6)    ; WaitBlit
        move.l $4,a6
        jsr -132(a6)    ; Forbid

	;; call the main routine
        jsr main(pc)
	
	;; exit gracely - reverse everything done in init
	
        move.w  #$7fff,DMACON           ; set bits[0,14] = 0 (bit15 is a set/clear bit)
        move.w  olddmareq,DMACON        ; and set bits[0,14] as they were at init
        move.w  #$7fff,INTENA           ; set bits[0,14] = 0 (bit15 is a set/clear bit)
        move.w  oldintena,INTENA        ; and set bits[0,14] as they were at init
        move.w  #$7fff,INTREQ           ; set bits[0,14] = 0 (bit15 is a set/clear bit)
        move.w  oldintreq,INTREQ        ; and set bits[0,14] as they were at init
        move.w  #$7fff,ADKCON           ; set bits[0,14] = 0 (bit15 is a set/clear bit)
        move.w  oldadkcon,ADKCON        ; and set bits[0,14] as they were at init

        move.l  oldcopper,$dff080       ; load old Copperlist
	
	;; graphics.library calls
	
        move.l  gfxbase,a6      ; gfxBase ==> a6
        move.l  oldview,a1      ; oldView ==> a1 (used in LoadView)
        jsr -222(a6)            ; LoadView : load back the view at start of program
        jsr -270(a6)            ; WaitTOF : Wait for Top Of Frame to get everything synced up
        jsr -270(a6)            ; WaitTOF : (2 times for interlaced screens)
        jsr -228(a6)            ; WaitBlit : wait for Blitter to finish running task (if any)
        jsr -462(a6)            ; DisownBlitter : release Blitter to system

	;; exec.library calls
	
        move.l  $4,a6           ; execBase ==> a6
        move.l  gfxbase,a1      ; gfxBase ==> a1 (used in closeLibrary)
        jsr -414(a6)            ; closeLibrary : close graphics.library
        jsr -138(a6)            ; Permit multitasking

	;; end program
	
        rts

	;; storage for 32-bit data
        CNOP 0,4
oldview:   dc.l 0
oldcopper: dc.l 0
gfxbase:   dc.l 0
frame:     dc.l 0
copper:    dc.l 0
haltend:   dc.l 0

	;; storage for 16-bit data
        CNOP 0,4
olddmareq: dc.w 0
oldintreq: dc.w 0
oldintena: dc.w 0
oldadkcon: dc.w 0

	;; storage for 8-bit data
        CNOP 0,4
gfxname:   dc.b 'graphics.library',0
