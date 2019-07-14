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
		
		SoundFX_A_Init:
		
		ld hl,sfxData			;//32764
		;reports 32826 **WRONG WHY??
		;should be 32830
			
			
		LD (sfxData+1),A		;//32767
		LD A,B
		LD (sfxData+2),A
		LD A,C
		LD (sfxData+3),A
		LD A,D
		LD (sfxData),A
		XOR A
		LD (SoundFX_A_V4),A
		;RET

		; Call this during your main loop
		; It will play one step of the sound effect each pass
		; until the complete sound effect has finished
		;
		SoundFX_A_Main:
			LD A,0
			DEC A
		;		RET Z
				LD (sfxData),A
		
		SoundFX_A_V1:
				LD B,0
				LD HL,SoundFX_A_V4
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

		SoundFX_A_V4:		DEFB 1,10,255,5

sfxData:
	defw SoundEffect0Data
	defw SoundEffect1Data
	
	
	;32818
	
	SoundEffect0Data:
	defb 1,10,255,5
	SoundEffect1Data:
	defb 10,50,200,15

	#endasm
}	