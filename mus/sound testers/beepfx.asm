
;org 32763

;data is pushed using the L register, but is pushed using HL pair.  for char data type is found in L

	ld a,l			;32763
	;//ld a,0
	//hl = 00000	'hl = 10072 1st pass
	//hl = 00001	'hl = 10072 1st pass
	
play:
	ld hl,sfxData	;32764	
	;//address of sound effects data 
	;//1st call = 32972
	;//2nd call = 32972
	;//bytes of 32972 = 222 128
	
	;//32990 data

;	//di; disabling interupts here cause issues with sprite redraw
	push ix			;32767
	push iy			;32769

	ld b,0			;32771
	ld c,a			;32773
	add hl,bc		;32774
	add hl,bc		;32775
	ld e,(hl)		;32776
	inc hl			;32777
	ld d,(hl)		;32778	//magic
	push de			;32779
	pop ix			;32780
	;//put it into ix
	
	;//32990 data1	33002 data2

;//	ld a,(23624)	;get border color from BASIC vars to keep it unchanged
	rra				;32782//here ix = data 32990
	rra				;32783
	rra				;32784 
	and 7			;32785
	ld (sfxRoutineToneBorder  +1),a	;32787
	ld (sfxRoutineNoiseBorder +1),a	;32790
	ld (sfxRoutineSampleBorder+1),a	;32793

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
	jr z,sfxRoutineNoise	;32818
	dec a					;32820
	jr z,sfxRoutineSample	;32821
	pop iy					;32823
	pop ix					;32825
;//	ei ; enabling interupts here cause issues with sprite redraw
	ret						;32827

	

;play sample

sfxRoutineSample:
	ex de,hl				;32828
sfxRS0:
	ld e,8					;32829
	ld d,(hl)				;32831
	inc hl					;32832
sfxRS1:
	ld a,(ix+5)				;32833
sfxRS2:
	dec a					;32836
	jr nz,sfxRS2			;32837
	rl d					;32839
	sbc a,a					;32841
	and 16					;32842
sfxRoutineSampleBorder:
	or 0					;32844
	out (254),a				;32846
	dec e					;32848
	jr nz,sfxRS1			;32849
	dec bc					;32851
	ld a,b					;32852
	or c					;32853
	jr nz,sfxRS0			;32854

	ld c,6					;32856
	
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

sfxRoutineNoise:
	ld e,(ix+5)		;pitch		;32925

	ld d,1						;32928
	ld h,d						;32930
	ld l,d						;32931
sfxRN0:
	push bc						;32932
	push iy						;32933
	pop bc						;32934
sfxRN1:
	ld a,(hl)					;32936
	and 16						;32937
sfxRoutineNoiseBorder:
	or 0						;32939
	out (254),a					;32941
	dec d						;32943
	jr nz,sfxRN2				;32944
	ld d,e						;32946
	inc hl						;32947
	ld a,h						;32948
	and 31						;32949
	ld h,a						;32951
sfxRN2:
	dec bc						;32952
	ld a,b						;32953
	or c						;32954
	jr nz,sfxRN1				;32955

	ld a,e						;32957
	add a,(ix+6)	;slide		;32958
	ld e,a						;32961

	pop bc						;32962
	dec bc						;32963
	ld a,b						;32964
	or c						;32965
	jr nz,sfxRN0				;32966

	ld c,7						;32968
	jr nextData					;32970

	;//from 32971 to 32989, what is used. perhaps stack??
	
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
