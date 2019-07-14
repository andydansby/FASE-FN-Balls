
;https://www.worldofspectrum.org/forums/discussion/comment/870963/#Comment_870963




screen_data EQU $C000
attrib_data EQU $C800

; The following correctly fills the screen with vertical lines. This works correctly
ld b, 5                    ; Bank 5
ld c, 0                    ; Screen Normal

call change_bank
call fill_attrib_data
call fill_screen

; The following simply displays a black screen  This is not correct. My expectation is that I'm writing to and displaying the shadow screen
ld b, 7                     ; Bank 7
ld c, 8                     ; Screen Shadow
call change_bank
call fill_attrib_data
call fill_screen

; b = Bits 0-2: RAM page (0-7) to map into memory at 0xc000.
; c = Bit 3   : Select normal (0) or shadow (1) screen to be displayed.
change_bank:
     ld      a,(0x5b5c)      ;previous value of port
     and     %11110000
     or      b
     or      c
     ld      bc,0x7ffd
     ld      (0x5b5c),a
     out     (c),a
     ret

fill_attrib_data:
    ld hl, attrib_data
    ld b, %01111000
    ld de, 768
_loop:
    ld (hl), b
    inc hl  
    dec de
    ld a,d
    or e
    jp nz, _loop
    ret

fill_screen:
    ld hl, screen_data
    ld b, 0x01 ; Value to write to the screen
    ld de, $1800 ; Screen Length
_loop:
    ld (hl), b
    inc hl
    dec de
    ld a,d
    or e
    jp nz, _loop
    ret
	
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
*/
	
	
	
	
	