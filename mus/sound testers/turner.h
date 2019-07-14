//Steve Turner / Hewson Cons 
//sfx engine
//used in Ranarama, Quazatron,IronMan 
//можно вешать на прерывания или вызывать в основном цикле
//you can use this routine on interrupts (as autor)
//or in main game cycle


//	32982 start of data
//https://www.dropbox.com/s/zon8n9r7kep8g2g/sound.a80?dl=0

extern void __FASTCALL__ SFX(unsigned char fx) 
{
	#asm
	
	ld a,L			;32763

	
	ld (sonreq),a
	


	sound:
		ld a,(sonreq) ;new sound play?
		and a
;//		jr z,nonew  ;no	
;yes
		ld (sonnow),a
		dec a
		jr z,noise	;#01 noise
		ld hl,sfx_data
		dec a
		add a,a
		add a,a
		add a,a
		ld e,a
		xor a
		ld (sonreq),a
		ld d,a
		add hl,de
		ld bc,8
		ld de,sonfrq
		ldir
		jr nz,process  ;jr process

;	nonew:
;		ld a,(sonnow) ;and the old sound is?
;		and a
;		ret z
;		dec a	;continue noise?
;		jr nz,process ;continue sound
;		jr cnois

	cnois:
		ld b,$30

	noise:
		ld a,$a
		ld (sonlen),a
		xor a
		ld (sonreq),a

	gain:
		call random
		and $10
		out ($fe),a
		ld c,2

	make:
		dec c
		jr nz,make
		djnz gain
		ld hl,sonlen
		dec (hl)
		ret nz
		xor a
		ld (sonnow),a
		ret

	process:
		ld a,(sonfrq)
		ld h,a
		ld a,$10
		ld d,$ff

	sonlp:
		ld e,h
		out ($fe),a
		xor $10

	freq:
		dec d
		jr z,mod
		dec e
		jr nz,freq
		jr sonlp

	mod:
		ld a,(soncfg)
		add a,h
		ld (sonfrq),a
		ld hl,sonmod
		dec (hl)
		ret nz
		ld hl,sonlen
		dec (hl)
		jr nz,modify
		xor a
		ld (sonnow),a
		ld a,(sonnex)
		and a
		ret z
		ld (sonreq),a
		ret

	modify:
		ld a,(sobrsf)
		ld c,a
		ld a,(sontyp)
		and a
		jr z,reset
		dec a
		jr z,typ1
		dec a
		jr z,typ2

	typoth:
		ld a,(soncfg)
		neg
		ld (soncfg),a
		jr mode

	typ2:
		inc c
		inc c
		ld a,c
		ld (sobrsf),a
		jr reset

	typ1:
		dec c
		dec c
		ld a,c
		ld (sobrsf),a
		jr reset

	reset:
		ld a,c
		ld (sonfrq),a

	mode:
		ld a,(sonrnd)
		ld (sonmod),a
		ret

	random:
		push hl
		ld hl,(rnseed)
		inc hl
		ld a,h
		and $3
		ld h,a
		
	rok:
		ld (rnseed),a
		ld a,r
		xor (hl)
		pop hl
		ret			;commenting out causes issues

	rnseed:	defw $1000

	sonfrq:	defw (sfx_data + 0)	;start frequency		
	soncfg:	defw (sfx_data + 1)	;frequency change
	sonmod:	defw (sfx_data + 2)	;change times
	sonlen:	defw (sfx_data + 3)	;repeat times
	sontyp:	defw (sfx_data + 4)	;modulate type
				;0 sawtooth
				;1 2nd mod down
				;2 2nd mod up
				;3+ triangle
	sobrsf:	defw (sfx_data + 5)	;reset frequency
	sonrnd:	defw (sfx_data + 6) ;change reset temp
	sonnex:	defw (sfx_data + 7)	;linked sfx
	sonnow:	defw (sfx_data + 8)	;which effect playing
	sonreq:	defw (sfx_data + 9)	;we have an effect
			;

;start freq  freq change sound mods  sound reps  modulate type  reset freq  change temp link
;64,	  	 5,	 		 10,	     1,	  		 0,	  			0,	  	    0,	  		0;

;32982 start
sfx_data:	
;here all sound excepts number 1 reserved for random noise 	
	defb	 64,  5,  10,  1,  0,  0,  0,  0;effect 2 ??
	defb	 40,  5,  10,  1,  0,  0,  0,  0;effect 3	OK
	defb	 64,  5,  20,  1,  0,  0,  0,  0;effect 4	OK
	defb     20,220,  64,  1,  3,  10, 1,  0;effect 5	OK
	defb	 64,  4,  32,  1,  3,  96,  0,  2;effect 6 working on
	defb    255,131,  32,  1,  0,  0,  0,  0;effect 7
	defb 	255,131,  40, 32, 1, 60,  1,  8;effect 8
	defb 	240,240,   8,  3, 0, 60,  6,  0;effect 9	OK
	defb	  2,120,  10,  1, 0,  0,  0,  0;effect 10	OK
	defb	 40,250,   8,  1, 0,  0,  0,  0;effect 11	OK
	defb 	250, 44,   6, 10, 1,132,  1,  0;effect 12	OK
	defb	  0,252,  20,  8, 1, 80,  8,  0;effect 13
	defb 	230,230,   4,  1, 1,  0,  0,  0;effect 14	OK
	defb	 45, 67,  20,  1, 1,  0,  0,  0;effect 15	OK
	defb	0,		0,   0,   0,   0,   0,   0,   0
	defb	0,		0,   0,   0,   0,   0,   0,   0
	defb	0,		0,   0,   0,   0,   0,   0,   0
	defb	0,		0,   0,   0,   0,   0,   0,   0
	defb	0,		0,   0,   0,   0,   0,   0,   0
	defb	0,		0,   0,   0,   0,   0,   0,   0
	
#endasm
}

/*
	sonfrq:	defb 00	;start frequency		
	soncfg:	defb 00	;frequency change
	sonmod:	defb 00	;change times
	sonlen:	defb 00	;repeat times
	sontyp:	defb 00	;modulate type
				;0 sawtooth
				;1 2nd mod down
				;2 2nd mod up
				;3+ triangle
	sobrsf:	defb 00	;reset frequency
	sonrnd:	defb 00	;change reset temp
	sonnex:	defb 00	;linked sfx
	sonnow:	defb 00	;which effect playing
	sonreq:	defb 00	;we have an effect
*/

/*
	di
	ld d,#28		;length/iterations
loop
	add hl,de
	dec de
	ld a,h
	out (#fe),a
	ld a,e
	or d
	jr nz,loop
	
	ei
	ret
*/
