extern void __FASTCALL__ text(unsigned char sfxData)
{
#asm
	;//data is normally pushed using the L register, but is pushed using HL pair
	;//org 24000
	;//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	;//		Routine to Print a Single Character to Spectrum Screen on Pixel Boundaries
	;//		Registers Used - AF,BC,DE,HL
	;//		On Entry - HL Points to 8 Bytes of Character Data
	;//		        	BC Contains Y and X Position to Print at where 0,0 = Top Left
	;//		Typical use:
	;//
	;//		ld a,"X"
	;//		ld bc,99*256+10 [Y Value=99 X Value=10]
	;//		call print_char
	;//		ret
	;//print_char	ld  de,(23606) [System Variable holding Display Characters]
	;//		ld  h,0
	;//		ld  l,a
	;//		add  hl,hl
	;//		add  hl,hl
	;//		add  hl,hl
	;//		add  hl,de
	;//		call p_print
	;//		ret
	;//
	;//		UDGs and User generated data can be used by either replacing the value of 23606 above
	;//		or by setting HL directly with the address of the required Character to print.
	;//		In which case use:
	;//
	;//		ld bc,99*256+10
	;//		ld hl,xxxx
	;//		call p_print
	;//
	;//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	ld b,1
	loop1:
		ld c,b
		push bc
		;//ld a,"A";//letter to be loaded
		call print_char
		pop bc
		inc b
		inc b
		ld a,b
		cp 200
		jr nz,loop1
		ret
	;//
	print_char:	
		ld  de,(23606) 
		ld  h,0
		ld  l,a
		add  hl,hl
		add  hl,hl
		add  hl,hl
		add  hl,de
		call p_print
		ret
;//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
;
	p_print:	
		call p_at
		;//convert the Y and X pixel values to the correct Screen Address  - Address in DE
		ld a,8
	;//set counter to 8 - Bytes of Character Data to put down

	p_print0	
		push af
		;//save off Counter
		ld a,b
		cp 192
		jr c,p_print1
	 	pop af
		ret
		
	;//don't print character if  > 191 - off the bottom of the screen - restore AF and exit Print routine 
	;//[this can be removed if you are keeping tight control of your Y values]
	p_print1:
		push hl
		push de
		push de
		;//save off Address of Character Data, Screen Address, Screen Address
		ld a,c
		and 7
		ld d,a
		;//get lowest 3 bits of Screen address
		ld e,255
		;//set up E with the Mask to use - 11111111b = All On 
		ld a,(hl)
		jr z,p_print3
		;//get a Byte of Character Data to put down - but ignore the following Mask shifting
		;//if the the X value is on an actual Character boundary i.e. there's no need to shift anything
	p_print2:
		rrca
		srl e
		dec d
		jr nz,p_print2
		;//Rotate the Character Data Byte D times - and Shift the Mask Byte as well, forcing Zeroes into the
		;//Left hand side. The Mask will be used to split the Rotated Character Data over a Character boundary 
	p_print3:
		pop hl
		;//POP one of the Screen Addresses (formerly in DE) into HL
		ld d,a
		ld a,e
		and d
		or (hl)
		ld (hl),a
		;//take the Rotated Character Data, mask it with the Mask Byte and the OR it with what's already on the Screen,
		;//this takes care of the first part of the Byte 
		;//[remove the OR (HL) if you just want a straight write rather than a merge]
		inc l
		ld a,l
		and 31
		jr z,p_print4
		;//Increment the Screen Address and check to see if it's at the end of a line,
		;//if so then there's no need to put down the second part of the Byte
		ld a,e
		cpl
		and d
		or (hl)
		ld (hl),a
		;//Similar to the first Byte, we need to Invert the mask with a CPL so we can put down the second part of the Byte
		;//in the next Character location
		;//[again, remove the OR (HL) if you just want a straight write rather than a merge]
	p_print4
		pop de
		inc d
		inc b
		;//get the Screen Address back into DE, increment the MSB so it points the the Address immediately below
		;//it and Increment the Y value in B as well
		ld a,b
		and 7
		call z,p_at
		;//now check if the Y value has gone over a Character Boundary i.e. we will need to recalculate the Screen
		;//Address if we've jumped from one Character Line to another - messy but necessary especially for lines 7 and 15
		pop hl
		inc hl
		;//get the Address of the Character Data back and increment it ready for the next byte of data
		pop af
		dec a
		jr nz,p_print0
		;//get the Counter value back, decrement it and go back for another write if we haven't reached the end yet
		ret
		;//
		;//P_AT is a subroutine routine to convert pixel values into an absolute screen address
		;//On Entry - B = Y Value C = X Value	On Exit - DE = Screen Address
	p_at:
		ld a,b
		srl a
		srl a
		srl a
		ld e,a
		and 24
		or 64
		ld d,a
		ld a,b
		and 7
		add a,d
		ld d,a
		ld a,e
 		and  7
		rrca
		rrca
		rrca
		ld e,a
		ld a,c
		srl a
		srl a
	 	srl a
	 	add a,e
		ld  e,a
		ret
	

#endasm
}
