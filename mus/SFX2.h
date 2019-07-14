//https://mikeinmono.blogspot.com/2009/05/machine-coding-101-user-defined-sound.html

//Lines 530 to 600 are where the sound effect is created. Here this is given as an example, but really any data in any part of the memory will do. The sound stops being read when uds finds a zero.

//At line 10 uds is positioned into memory at address 32768 which might seem like a strange number, but it is exactly half way through the total machine memory, and begins to make more sense if viewed as hexadecimal or as higher and lower order bytes in decimal - 128, 0, i.e. 128 * 256 + 0 = 32768. Perhaps this is running before walking. The point being that you can change this number, but I would recommend that if you do, make it higher so that it doesn't clash with any BASIC program. 

//Line 20 defines where this particular sound effect is placed in memory, again it could be anywhere, but here its "a bit further on from uds", and the address is called udata.

//Line 50 defines the variable "duration" with a default of 1. The sound can be stretched by increasing this number up to a maximum of 255. But it will lose its identity pretty quickly, and I usually don't go beyond 16.

//Line 320 contains the number 8. This value I refer to as the inner wheel tuning and it is meant to balance the sound. Again this value can be increased up to 255 to lower the overall tuning.

//310 and 440 contain the value 251. It can be changed to a value between and including 244 to 251. I think of this as being an octave ladder. 244 being the lowest. 

//After the routine is compiled and the sound effect created, it will be triggered and then pause until you press the keyboard, then triggered again.




extern void __FASTCALL__ SFX(unsigned char sfxData)
{
#asm
;org 32778

ld hl,sfx_data		; address of sound effects data

main:
	xor a			; 6
	ld a, (hl)		; 7
	or 0			; 8
	jr nz, next 	; 9
	ret				; 10

next:				; 11
	ld bc, 1		; 12

pushSpeaker:		; 13
	push bc			; 14
	ld b,0			; 15
	ld c, (hl)		; 16
	push bc			; 17
	ld a, 0x10		; 18
	and 0xf8		; 19 ; mask out unwanted bits
	out (0xfe),a	; 20
	nop				; 21
	nop				; 22
	nop				; 23
	nop				; 24
	nop 			; 25
	nop 			; 26
	nop				; 27
	
temp1:
	dec bc			; 29
	ld a,c			; 30
	or b			; 31
	jp nz, temp1	; 32805
	ld bc, 8		; 33

play:
	dec bc			; 34
	ld a, c			; 35
	or b			; 36
	jp nz, play		; 37
	ld a, 0x7		; 38
	and 0xf8		; 39
	out (0xfe),a	; push speaker
	pop bc			; 41
	nop				; 42
	nop				; 43
	nop				; 44
	nop				; 45
	nop				; 46
	nop				; 47
	nop				; 48

readdata:
	dec bc
	ld a, c
	or b
	jp nz, readdata
	pop bc
	dec bc
	ld a, c
	or b
	jp nz, pushSpeaker
	inc hl
	jp main

sfx_data:

SoundEffectsData:
	defw SoundEffect0Data
	defw SoundEffect1Data
	defw SoundEffect2Data
	
SoundEffect0Data:
	defw 1,128,3,134,5,140,7,146,9,151,11,155,13,158,15,159,17,160,19,159,21,157,23,154,25,150,27,145,29,140,31,134,33,127,35,121,37,115,39,109,41,105,43,101,45,98,47,96,49,96,51,97,53,99,55,102,57,106,59,111,61,117,63,123,65,130,67,136,69,142,71,147,73,152,75,156,77,158,79,160,81,160,83,159,85,157,87,153,89,149,91,144,93,138,95,101,114,103,108,105,104,107,100,109,98,111,96,113,96,115,97,117,100,119,103,121,108,123,113,125,119,127,125,129,131,131,137,133,143,135,148,137,153,139,156,141,159,143,160,145,160,147,158,149,156,151,152,153,148,155,142,157,137,159,130,161,124,163,118,165,112,167,107,169,103,171,99,173,97,175,96,177,96,179,98,181,100,183,104,185,109,187,114,189,120,191,126,193,133,195,139,197,145,199,150,201,154,203,157,205,159,207,160,209,160,211,158,213,155,215,151,217,147,219,141,221,135,223,129,225,122,227,116,229,111,231,106,233,102,235,99,237,97,239,96,241,97,243,98,245,101,247,105,249,110,251,116,253,122,255
	defb 0
SoundEffect1Data:
	defw 1,30,5,162,187,71,183,11,42,76,174,50,199,28,33,115,106,25,252,31,249,178,253,128,251,160,250,194,191,118,129,121,198,182,238,192,96,91,164,88,94,114,184,229,18,14,189,145,75,219,57,0
	defb 0
SoundEffect2Data:
	defw 1,160,200,26,238,35,96,128,254,77
	defb 0

#endasm
}

//SoundEffect0Data:
//	defw 50,200,25,65486,5375
//	defb 0
//SoundEffect1Data:
//	defw 12,96,400,65526,2688
//	defb 0





