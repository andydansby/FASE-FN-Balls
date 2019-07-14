/*extern int __FASTCALL__ SFX(int fx)
{
	#asm
	
	;ld (sonreq),hl
	zap:
		ld d,16		;speaker = bit 4
		ld e,128		;distance between speaker move counter	ld e,0
		ld b,128	;overall length counter					ld b,255
	blp0:	ld a,d
		and 248		;keep border colour the same
		out (254),a	;move the speaker in or out depending on bit 4
		cpl		;toggle, so we alternative between speaker in and out to make sound
		ld d,a		;store it
		ld c,e		;now a pause
	blp1:	dec c
		jr nz,blp1
		dec e		;change to inc e to reverse the sound, or remove to make it a note
		djnz blp0	;repeat B=255 times
		ret
		
	#endasm
}*/

/*extern int __FASTCALL__ SFX1(int fx)
{
	#asm
	
	;HL must be !0 aka set HL to 0 for silence
	ld d,125    ;prescaler mask
loop:
	rlc d
	jr nc,skip
	
	add hl,hl
	sbc a,a
	xor l
	ld l,a
	
	cp 0x10       ;cp n -  n = volume
	sbc a,a
	
	out (0xfe),a
	jr loop
	
skip:
	cp 0x10       ;cp n -  n = volume
	sbc a,a
	
	out (0xfe),a
	jr loop
	
	#endasm
}*/

/*extern int __FASTCALL__ SFX2(int fx)
{
	#asm
	
	;ld hl,0
	ld c,255
lp1:
	inc hl
	ld a,(hl)
	and 248
	or 7
	out (254),a
	ld b,c
lp0:
	djnz lp0
	dec c
	jr nz,lp1
	ret
	
	#endasm
}*/

/*extern int __FASTCALL__ SFX3(int fx)
{
	#asm
SFX:
	; ld hl,0
	ld bc,2
	ld d,24
	call loop
	ld c,24
	ld d,64
loop:
	ld a,(hl)
	inc hl
	cp c
	sbc a,a
	and 24
	or 7
	out (254),a
	djnz loop
	dec d
	jr nz,loop
	ret
	#endasm
}*/

extern int __FASTCALL__ SFX3(int fx)
{
	#asm
	
sound_setup:
	ld de, 5
	ld b,3
;	ld hl, 938 	; pitch
sound_loop:
	dec h
	push bc
	push de
	push hl
	call 949 	; call ROM beeper routine
	pop hl
	pop de
	pop bc
	djnz sound_loop
	ret
		#endasm
}