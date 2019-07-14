extern void __FASTCALL__ SFX(unsigned char sfxData)
{
	//DEHL
	//Fastcall linkage allows one parameter to be passed by register in a subset of DEHL.
	//So if the parameter is 8-bit, the value will be in L.  
	//If the parameter is 16-bit, the value is in HL and 
	//if it is 32-bit the value is in DEHL.
	
	
	
	#asm
		;
		; Title:	ZX Spectrum 48K Sound Routines
		; Author:	Dean Belfield
		; Created:	august 11 2011
		; Last Updated:	august 11 2011
		;
		; Requires:
		;
		; Modinfo:
		;
		
		ld a,l					;//32763
		
		; Call this every time you want to initialise a sound effect
		; A = Variable 1
		; B = Variable 2
		; C = Duration of overall sound effect
		; D = Duration of each step of the sound effect
		
		ld hl,SoundEffectsData			;//32764
				;reports 32834 **WRONG WHY??
				;should be 32838
		
		SoundFX_A_Init:		
			
				
			ld b,0			;//32767
			ld c,a			;//32769
			add hl,bc		;//32770
			add hl,bc		;//32771
			ld e,(hl)		;//32772
			inc hl			;//32773
			ld d,(hl)		;//32774
			
			;//SoundEffect0Data 32830-32833
			;//SoundEffect1Data 32842-32845
			
			
			
			
			
		;----------------------------
			LD (SoundEffectsData + 1),A		;//32774
			LD A,B
			LD (SoundEffectsData + 2),A
			LD A,C
			LD (SoundEffectsData + 3),A
			LD A,D
			LD (SoundEffectsData),A
			XOR A
		;//	LD (SoundFX_A_V4),A
		;RET

		; Call this during your main loop
		; It will play one step of the sound effect each pass
		; until the complete sound effect has finished
		;
		SoundFX_A_Main:
			LD A,0
			DEC A
		;		RET Z
				LD (SoundEffectsData),A
		
		SoundFX_A_V1:
				LD B,0
			;//	LD HL,SoundFX_A_V4
		SoundFX_A_L1:
			LD C,B
			LD A, 8
			OUT (254),A
			LD A,(HL)
			
		SoundFX_A_V2:
			XOR 0
			LD B,A
		temp1:
			DJNZ temp1
			XOR A
			OUT (254),A
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

;//sfxData:
SoundEffectsData:
	defw SoundEffect0Data
	defw SoundEffect1Data
	
	
	;32818
	;32828-32831
	SoundEffect0Data:
	defb 50,10,100,15
	;defb 1,10,255,5
	
	;32832-32835
	SoundEffect1Data:
	defb 10,50,200,15

	#endasm
}	