PRIOR ATTEMPTS

void __FASTCALL__ riverbank()
{
	#asm
	push bc
	push af
	
	ld b, 5                    ; Bank 5
	ld c, 0                    ; Screen Normal
	
	ld	a,(0x5b5c)      ;previous value of port
	and	240				; %11110000
	or b
	or c
	
	di
	
	ld bc,0x7ffd
	ld (0x5b5c),a
	out (c),a
	
	ei
	pop af
	pop bc
	#endasm
}

void __FASTCALL__ bank5()
{
	#asm
	push af
	push bc
	ld a,(0x5b5c)	;Previous value of port system variable 23388
	and 0xf8		;Reset bits 0-2 11111000
	or 5			;OR pagenumber Set bits 0-2 to new page number
	
	di				;disable interupts
	
	ld bc,0x7ffd	;Set BC to 32765 for write port 32765
	ld (0x5b5c),a
	
	out (c), a		;perform Bankswitch operation
	ei				;enable interups
	pop bc
	pop af
	#endasm
}


void just5()
{
	//UUIRSMMM
	//MMM= ram bank at C000 (0-7)   
	//S=Screen page bit    
	//R=Rom Low bit    
	//I=I/O Disabling 
	//UU = unused bits on Sinclair/Amstrad models
	//;00000101
	
	//Bits 0-2: RAM page (0-7) to map into memory at 0xc000.
	//Bit 3: Select normal (0) or shadow (1) screen to be displayed. 
	//The normal screen is in bank 5, whilst the shadow screen is in bank 7. Note that this does not affect the memory between 0x4000 and 0x7fff, which is always bank 5.
	//Bit 4: ROM select. ROM 0 is the 128k editor and menu system; ROM 1 contains 48K BASIC.
	//Bit 5: If set, memory paging will be disabled and further output to this port will be ignored until the computer is reset.
	
	//000
	
	
	//push af
	//push bc	
	//di				;disable the interups
	//;ld a,(0x5b5c)	;Previous value of port system variable 23388
	//;and 0xf0		;Reset bits 0-3 11110000
	//;or 5			;set page 5
	//;or 8			; set shadow screen
	//ld a,(0)
	//ld bc,0x7ffd	;Set BC to 32765 for write port 32765
	//out (c), a		;perform Bankswitch operation
	
	
	
	//working 5b5c = 208
	//not working 5b5c = also 208 ARRRGH
	//1101 0000
	#asm
	push af
	push bc
	di				;disable the interups
	;ld a,(0x1f)		;31 decimal
	ld a,(31)		;31 decimal
	ld bc,0x7ffd	;Set BC to 32765 for write port 32765
	out (c), a		;perform Bankswitch operation	
	ld (0x5b5c),a	;update 23388
	pop bc
	pop af
	#endasm
}

void __FASTCALL__ bank7()
	{
		#asm
		di;
		ld      a, 0x1c;	ld a, $18
		out     (c), a
		ei;
		#endasm
	}

void __FASTCALL__ bank7()
{
	#asm
		;Port	Backup		Bits		Details
	;&7FFD	&5B5C  	 	--IRSMMM  	MMM= ram bank at C000 (0-7)   
	;S=Screen page bit    R=Rom Low bit    I=I/O Disabling
	;- - I R S M M M
	;0 0 0 0 0 0 0 0
	
	push af
	push bc
	ld a,(0x5b5c)	;Previous value of port
	and 0xf8
	or 5			;Select bank 5
	ld bc,0x7ffd
	di
	ld (0x5b5c),a
	out (c),a
	ei
	pop bc
	pop af
	#endasm
}

	void __FASTCALL__ setShadow()
	{
		//set shadow to 0
			#asm
			push af
			push hl
			ld hl,$5c01;
			ld a,0;
			xor a
			ld (hl),a;
			pop hl
			pop af
			ret
			#endasm
	}

	void __FASTCALL__ setShadow1()
	{
		//set shadow to 0
		//UUIRSMMM
		//11111000
		//11110101
		
		//MMM= ram bank at C000 (0-7)   
		//S=Screen page bit    
		//R=Rom Low bit    
		//I=I/O Disabling 
		//UU = unused bits on Sinclair/Amstrad models
		#asm
		
		push bc
		push af
		ld a,(0x5b5c)	;Previous value of port system variable 23388
		
		and 245		;Reset bits 0-2 11111000
		di				;disable interupts
	
		ld bc,0x7ffd	;Set BC to 32765 for write port 32765
		out (c), a		;perform Bankswitch operation
		ld (0x5b5c),a
		ei				;enable interups
		
		pop af
		pop bc
		
			
		#endasm
	}
	
	
==========================================================

see http://www.chibiakumas.com/z80/ZXSpectrum.php


OUT port to write 7FFD
memory address to read 5B5C

bits
UUIRSMMM

MMM= ram bank at C000 (0-7)   
S=Screen page bit    
R=Rom Low bit    
I=I/O Disabling 
UU = unused bits on Sinclair/Amstrad models



The hardware switch normally used to select RAM is at I/O address
7FFDh (32765). The bit field for this address is as follows:
D0...D2 - RAM select
D3 - Screen select
D4 - ROM select
D5 - Disable paging


	;Switching between screens is carried out
	;port 32765 (# 7FFD), to display an additional 
	;screen should run the program: 
	;screen 2
	DI; Disable interrupts.
	PUSH BC; Remember BC.
	LD BC, # 7FFD;
	LD A, (23388); Get the contents of the first. BANK
	SET 3, A; Install the third bit is determined
				; That returns the active screen.
	LD (23388), A; Post New znaeenie in
				; Variable BANK.
	OUT (C), A; Output port 32765 (# 7FFD)
				;, The contents of the battery.
	POP BC; Recall BC.
	EI; Enable interrupts.
	RET; Return from the program.

	;For conventional screen: screen 1
	DI; Disable interrupts.
	PUSH BC; Remember BC.
	LD BC, # 7FFD;
	LD A, (23388); Get the contents of the first. BANK
	RES 3, A; Reset the third bit is determined
				; Yuschy active screen.
	LD (23388), A; Post New znaeenie in
				; Variable BANK.
	OUT (C), A; Output port 32765 (# 7FFD)
				;, The contents of the battery.
	POP BC; Recall BC.
	EI; Enable interrupts.
	RET; Return from the program.
	 
;;;;;;;;;;;;
#asm
	;push af
	;push bc
	;di
	ld a,(0x5b5c)	;Previous value of port

	and 0xf8
	or 5			;Select bank 5
	ld bc,0x7ffd		
	ld (0x5b5c),a
	out (c),a
	;ei
	;pop bc
	;pop af
#endasm
;;;;;;;;;;;;
ASM
	di
	; ld a,(ix+5) ; Not needed already in A
	and 7
	or 8
	ld bc,32765;0x7ffd
	out (c),a
	ld (23388),a;0x5b5c
	ei
ENDASM
	
;;;;;;;;;;;;	
	push af
	push bc
	ld bc, 0x7ffd;0x7ffd
	ld a, (0x5b5c)
	xor 0x10
	di
	ld (0x5b5c), a
	out (c), a
	ei
	pop bc
	pop af
	
;;;;;;;;;;;;
;sinclair FAQ
	ld a,(0x5b5c)      ;Previous value of port
	and 0xf8
	or 4               ;Select bank 4
	ld bc,0x7ffd
	di
	ld (0x5b5c),a
	out (c),a
	ei
;;;;;;;;;;;;
;resets FASE
		#asm
		push af
		push bc
		ld a,(0x5b5c)	;Previous value of port
		and 0xf8
		or 5			;Select bank 5
		ld bc,0x7ffd
		di
		ld (0x5b5c),a
		out (c),a
		ei
		pop bc
		pop af
		#endasm
		
		
//meant to copy from one screen to another in 128k mode
/*
void bitmapCopy()
{
	if (speccy128k == true)
	{
		//;ld hl,$5c01
		//	;ld a,0
		//	;ld (hl),a
		
		//5c01 is which frame for 128 mode
		
		//if (*shadow == 0)			
		{
			#asm
				ld hl,$4000
				ld de,$c000
				ld bc,6912
				ldir
		   #endasm
		}
		if (*shadow != 0)
		{
			#asm
				ld hl,$c000
				ld de,$4000
				ld bc,6912
				ldir
		   #endasm
		}
	}
}

void __FASTCALL__ bank5()
{
	#asm
	push af
	push bc
	ld a,(0x5b5c)	;Previous value of port system variable 23388
	and 0xf8		;Reset bits 0-2 11111000
	or 5			;OR pagenumber Set bits 0-2 to new page number
	
	di				;disable interupts
	
	ld bc,0x7ffd	;Set BC to 32765 for write port 32765
	ld (0x5b5c),a
	
	out (c), a		;perform Bankswitch operation
	ei				;enable interups
	pop bc
	pop af
	#endasm
}
*/


	//ld a,($5b5c) ;Previous value of port
	//and $f8
	//or 0 ;Select bank 0
	//di
	//ld bc,$7ffd
	//ld ($5b5c),a
	//out (c),a
	//ei
	//#asm
	//	ld      a, ($5c01)
	//	xor     b
	//	ld      b, a
	//	and     $80
	//	xor     h
    //  ld      h, a
	//#endasm
	