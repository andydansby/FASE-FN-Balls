
//org org 32763


extern void __FASTCALL__ SFX(unsigned char sfxData)
{
#asm

;data is pushed using the L register, but is pushed using HL pair.  for char data type is found in L

	ld a,l			;32763
	;//ld a,0
	//hl = 00000	'hl = 10072 1st pass
	//hl = 00001	'hl = 10072 1st pass
	
play:
	ld hl,sfxData	;32764	
	;//address of sound effects data 
	;//calls up address = 32972
	;//z80 does least significant bit first
	;//The Z80 is little endian, i. e. it stores the LSB first. Therefore, if you have a 16-bit number, the lower byte is at the lower address
	
	;//32972 = 222, 128 pass 1
	;//32972 = 222, 128 pass 2
	;//1101 1110 = 222
	;//1000 0000 = 128
	
	;// LSB means 128 + 222
	;//10000000 11011110 = 32990
	;//32990 is first bit of data


;	//di; disabling interupts here cause issues with sprite redraw
	push ix			;32767
	push iy			;32769

	ld b,0			;32771
	ld c,a			;32773
	add hl,bc		;32774
	add hl,bc		;32775
	ld e,(hl)		;32776
	inc hl			;32777
	ld d,(hl)		;32778
	push de			;32779
	pop ix			;32780

	rra				;32782//here ix = data 32990
	rra				;32783
	rra				;32784 
	and 7			;32785
	
	
	ld (sfxRoutineToneBorder  + 1),a	;32787

	;//32990 data1	33002 data2
	
readData:
	ld a,(ix+0)		;read block type	;32796
	ld c,(ix+1)		;read duration 1	;32799
	ld b,(ix+2)							;32802
	ld e,(ix+3)		;read duration 2	;32805
	ld d,(ix+4)							;32808
	push de								;32811
	pop iy								;32812

	dec a					;32814
	jr z,sfxRoutineTone		;32815
	dec a					;32817

	pop iy					;32823
	pop ix					;32825

	ret						;32827

	

;play sample
nextData:
	add ix,bc		;skip to the next block	;32858
	jr readData								;32860



;generate tone with many parameters
sfxRoutineTone:
	ld e,(ix+5)		;freq			;32862
	ld d,(ix+6)						;32865
	ld a,(ix+9)		;duty			;32868
	ld (sfxRoutineToneDuty+1),a		;32871
	ld hl,0							;32874

sfxRT0:
	push bc		;32877
	push iy		;32878
	pop bc		;32880
sfxRT1:
	add hl,de	;32881
	ld a,h		;32882
sfxRoutineToneDuty:
	cp 0		;32883
	sbc a,a		;32885
	and 16		;32886
sfxRoutineToneBorder:
	or 0		;32888
	out (254),a	;32890

	dec bc			;32892
	ld a,b			;32893
	or c			;32894
	jr nz,sfxRT1	;32895

	ld a,(sfxRoutineToneDuty+1)	 ;duty change	;32897
	add a,(ix+10)								;32900
	ld (sfxRoutineToneDuty+1),a					;32903

	ld c,(ix+7)		;slide		;32906
	ld b,(ix+8)					;32909
	ex de,hl					;32912
	add hl,bc					;32913
	ex de,hl					;32914

	pop bc						;32915
	dec bc						;32916
	ld a,b						;32917
	or c						;32918
	jr nz,sfxRT0				;32919

	ld c,11						;32921
	jr nextData					;32923

;generate noise with two parameters
;	ld c,7						;32968
;	jr nextData					;32970

sfxData:
SoundEffectsData:
	defw SoundEffect0Data
	defw SoundEffect1Data
	defw SoundEffect2Data
	defw SoundEffect3Data
	defw SoundEffect4Data
	defw SoundEffect5Data
	defw SoundEffect6Data
	defw SoundEffect7Data
	defw SoundEffect8Data
	
	;SIREN 
SoundEffect0Data:
	defb 1 ;tone 			     32990
	defw 50,200,25,65486,5375	;32991 - 33000
	defb 0						;33001
	
	;FIRE 33002
SoundEffect1Data:
	defb 1 ;tone				;33002
	defw 12,96,400,65526,2688	;33003 - 33012
	defb 0						;33013
	
	;33015
	;enemy dies by being shot
SoundEffect2Data:
	defb 1 ;tone
	defw 15,100,200,65516,1408
	defb 1 ;tone
	defw 15,100,200,20,1408
	defb 0
	
	;enemy dies by running into barrier
SoundEffect3Data:
	defb 1 ;tone
	defw 15,100,300,20,2688
	defb 1 ;tone
	defw 15,100,500,65516,2688
	defb 0
	
	;collect key
SoundEffect4Data:
	defb 1 ;tone
	defw 12,255,300,10,640
	defb 1 ;pause
	defw 10,100,0,0,0
	defb 1 ;tone
	defw 12,255,600,10,640
	defb 0
	
	;transport
SoundEffect5Data:
	defb 1 ;tone
	defw 10,1000,100,20,60671
	defb 0
	
	;collect key
SoundEffect6Data:
	defb 1 ;tone
	defw 10,500,200,0,3968
	defb 1 ;tone
	defw 10,500,200,0,6528
	defb 0

	;level over
SoundEffect7Data:
	defb 1 ;tone
	defw 10,500,200,0,3968
	defb 1 ;tone
	defw 10,500,200,0,6528
	defb 0
	
	;player death
SoundEffect8Data:
	defb 1 ;tone
	defw 10,2000,200,65521,60612
	defb 0
	
	
;SoundEffect0Data:
;	defb 1 ;tone
;	defw 50=frames,400=frame length,50=pitch,65436,5375
;	defb 0


#endasm
}
