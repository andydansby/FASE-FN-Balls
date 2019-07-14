org 32763

main
ld a,5
ld (sonreq),a
;jr main
ret
	


sound 	
	ld a,(sonreq) ;????? ???? ???????
	and a
	jr nz,nonew  ;??? jr z,nonew

	ld (sonnow),a
	dec a
	jr z,noise	;#01 ???

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
	ld bc,08
	ld de,sonfrq
	ldir
	jr process
	


nonew 	ld a,(sonnow) ;? ?????? ???? ?????
	and a
	ret z
	
	dec a	;?????????? ????
	jr nz,process ;?????????? ????

	jr cnois

noise 	ld a,0ah
	ld (sonlen),a
	xor a
	ld (sonreq),a

cnois 	ld b,30h

gain	call random
	and 10h
	out (0feh),a
	ld c,02h

make	dec c
	jr nz,make
	djnz gain
	ld hl,sonlen
	dec (hl)
	ret nz
	xor a
	ld (sonnow),a
	ret

process	ld a,(sonfrq)
	ld h,a
	ld a,10h
	ld d,0ffh

sonlp 	ld e,h
	out (0feh),a
	xor 10h

freq	dec d
	jr z,mod
	dec e
	jr nz,freq
	jr sonlp

mod	ld a,(soncfg)
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

modify	ld a,(sobrsf)
	ld c,a
	ld a,(sontyp)
	and a
	jr z,reset
	dec a
	jr z,typ1
	dec a
	jr z,typ2

typoth	ld a,(soncfg)
	neg
	ld (soncfg),a
	jr mode

typ2	inc c
	inc c
	ld a,c
	ld (sobrsf),a
	jr reset

typ1	dec c
	dec c
	ld a,c
	ld (sobrsf),a
	jr reset

reset 	ld a,c
	ld (sonfrq),a

mode	ld a,(sonrnd)
	ld (sonmod),a
	ret

random	push hl
	ld hl,(rnseed)
	inc hl
	ld a,h
	and 03
	ld h,a
rok	ld (rnseed),a
	ld a,r
	xor (hl)
	pop hl
	ret

rnseed	defw 1000h

sonfrq	defb 00	;????????¤ ???????
		;start frequency
soncfg	defb 00	;???????? ????????¤ ???????
		;frequency change
sonmod	defb 00	;?????????? ?????¤??? ? ?????
		;change times
sonlen	defb 00	;?????????? ?????????? ?????
		;repeat times
sontyp	defb 00	;??? ?????¤???
		;modulate type
			;0 sawtooth
			;1 2nd mod down
			;2 2nd mod up
			;3+ triangle
sobrsf	defb 00	;??????? ??????
		;reset frequency
sonrnd	defb 00	;???? ????????¤ ??????? ??????
		;change reset temp
sonnex	defb 00	;??????????? ??????
		;linked sfx
sonnow	defb 00	;??? ??????
		;
sonreq	defb 00	;???¤?? ??????
		;

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

