extern void __FASTCALL__ SFX(unsigned char sfxData)
{
	//DEHL
	//Fastcall linkage allows one parameter to be passed by register in a subset of DEHL.
	//So if the parameter is 8-bit, the value will be in L.  
	//If the parameter is 16-bit, the value is in HL and 
	//if it is 32-bit the value is in DEHL.
	
	//
	// Title:	ZX Spectrum 48K Sound Routines
	//  Author:	Dean Belfield
	// Created:	august 11 2011
	// Last Updated:	august 11 2011
	//	; Requires:
	//	; Modinfo:
	
	// Call this every time you want to initialise a sound effect
	// A = Variable 1
	// B = Variable 2
	// C = Duration of overall sound effect
	// D = Duration of each step of the sound effect
	
	#asm
	ld a,l					;//32763

	ld hl,SoundEffectsData
	;// points to data in 32824
	;//60 128
	;//LSB = 10000000 00111100 = 32828
	;//32828 is where SFX Data resides
			
	SoundFX_A_Init:
		ld b,0			;//32767
		ld c,a			;//32769
		add hl,bc		;//32770
		add hl,bc		;//32771
		ld e,(hl)		;//32772
		inc hl			;//32773
		ld d,(hl)		;//32774
		
	rra				;32782
	rra				;32783
	rra				;32784 
	and 7			;32785
	
nextData:
	add ix,bc		;skip to the next block	;32858
	jr readData								;32860
			
		;//SoundEffect0Data 32828-32831
		;//SoundEffect1Data 32832-32835
		;//----------------------------
		
		LD (SoundEffectsData + 1),A		;//32774
		LD A,B
		LD (SoundEffectsData + 2),A
		LD A,C
		LD (SoundEffectsData + 3),A
		LD A,D
		LD (SoundEffectsData),A
		XOR A
		;//	LD (SoundFX_A_V4),A
		;//RET

		; Call this during your main loop
		; It will play one step of the sound effect each pass
		; until the complete sound effect has finished
		;
	SoundFX_A_Main:
		LD A,0
		DEC A
	RET Z
		LD (SoundEffectsData),A
		
		SoundFX_A_V1:
				LD B,0
			;//	LD HL,SoundFX_A_V4
		SoundFX_A_L1:
			LD C,B
			LD A, 8
			out (254),a
			LD A,(HL)
			
		SoundFX_A_V2:
			XOR 0
			LD B,A
		temp1:
			DJNZ temp1
			XOR A
			out (254),a
			LD A,(HL)
			
		SoundFX_A_V3:
			XOR 0
			LD B,A
		temp2:
			DJNZ temp2
			DEC (HL)
			LD B,C
			DJNZ SoundFX_A_L1
			RET

	;//	SoundFX_A_V4:		DEFB 1,10,255,5
	
	
	
	
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
	
	
	

;//sfxData:
SoundEffectsData:
	defw SoundEffect0Data
	defw SoundEffect1Data
	
	
	;32818
	;32828-32831
	SoundEffect0Data:
	defb 50,10,200,20

	
	;32832-32835
	SoundEffect1Data:
	defb 10,50,40,15

	#endasm
}

//	defb 1,10,255,5