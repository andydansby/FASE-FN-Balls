#ifndef GAMEDISPLAY1_H
#define GAMEDISPLAY1_H

#define printInk(k)			printf("\x10%c", (k))
#define printPaper(k)		printf("\x11%c", (k))
#define printMode(mode)		printf("\x01%c", (mode))
#define printAt(row, col)	printf("\x16%c%c", ' '+(row), ' '+(col))
#define FLASH_ON			printf("\x12\x31")
#define printCls()			printf("\x0c")
#define printInk(k)			printf("\x10%c", (k))
#define printPaper(k)		printf("\x11%c", (k))


/*
void __FASTCALL__ just5QUEUE()
{
	#asm

	;previous value of port stored in system variable 23388
	ld a,(23388)	;fetch current value
	;and 248	;clear bits 0–2 (bank #) 11111000
	and 240	;clear bits 0–3 (bank #)
	;or 5		;select new bank
	
	or 8
	ld bc,32765	;our port
	di
	ld (23388),a	;write new value back to sys. var
	out (c), a		;perform Bankswitch operation port 32765
	ei
	;ret
	#endasm
	
	//ld a,(23388)	;fetch current value
	//and %11111000	;clear bits 0–2 (bank #)
	//or 1		;select new bank
	//ld bc,32765	;our port
	//di		;condom on
	//ld (23388),a	;write new value back to sys. var
	//out (c),a	;and to port
	//ei		;condom off
	//ret		;we should be back in BASIC now	
}*/

//does set to 8
//MMM= ram bank at C000 (0-7)   
//S=Screen page bit    
//R=Rom Low bit    
//I=I/O Disabling 
//UU = unused bits on Sinclair/Amstrad models
//UUIRSMMM
//11000000 = 192 = Bank 0, no shadow
//11001000 = 200 = Bank 0, shadow
//11000101 = 197 = bank 5, no shadow
//11001101 = 205 = bank 5, shadow
//11000111 = 199 = bank 7, no shadow
//11001111 = 207 = bank 7, shadow

/*void __FASTCALL__ shadow99QUEUE()
{
	#asm
		;previous value of port stored in system variable 23388
		ld a,(23388)	;fetch current value
		and 255	;clear bits 0–7 (bank #) 11110000
		ld bc,32765	;our port
		di
		out (c), a		;perform Bankswitch operation port 32765
		ld (23388),a	;write new value back to sys. var
		ei		
	#endasm
	bpoke (23553,0);//FASE Engine
}*/


/*void __FASTCALL__ shadowResetQUEUE()
{
	#asm
		;previous value of port stored in system variable 23388
		ld a,(23388)	;fetch current value
		;and 240	;clear bits 0–3 (bank #) 11110000
		or 8 ; select shadow bit 3
		ld bc,32765	;our port
		di
		out (c), a		;perform Bankswitch operation port 32765
		ld (23388),a	;write new value back to sys. var
		ei		
	#endasm
	bpoke (23553,128);//FASE Engine
}*/

/*void __FASTCALL__ shadow0()
{
	#asm
		;previous value of port stored in system variable 23388
		ld a,(23388)	;fetch current value
		;and 240	;clear bits 0–3 (bank #) 11110000
		or 8 ; select shadow bit 3
		xor 8
		ld bc,32765	;our port
		di
		out (c), a		;perform Bankswitch operation port 32765
		ld (23388),a	;write new value back to sys. var
		
		;ld a, (23553)
		;xor 128
		;xor 128
		;ld (23553),a
		
		
		ei		
	#endasm
	//bpoke (23553,0);//FASE Engine
}*/


/*
void screen0()
{
	//POKE 23388, 24 will activate screen one, whereas POKE 23388, 16 will activate screen zero
	bpoke (23388,16);//128k system variable
	bpoke (23553,0);//FASE Engine
	//wpoke (23553,128);
}

void screen1()
{
	//POKE 23388, 24 will activate screen one, whereas POKE 23388, 16 will activate screen zero
	
	
	bpoke (23388,24);//128k system variable
	bpoke (23553,128);//FASE Engine	
	//outp(32765,24);//perform bankswitch	
	
	//wpoke (23553,0);
}*/

void checkFrame()
{
	if (wpeek (23553) == 0)
	{
		wpoke (23553,0);
	}
	if (wpeek (23553) == 128)
	{
		wpoke (23553,0);
	}
}




	
	void __FASTCALL__ assemblyCLS()
	{
		//attributes
		//	8	7	6	5	4	3	2	1
		//	FL	BR	PA	PA	PA	IK	IK	IK
		//FL = FLASH
		//BR = BRIGHT
		//PA = PAPER
		//IK = INK
		// 56 would be
		//	0011 1000
		// Flash and Bright off
		// paper 111 = 7 (white)
		// INK = 000 = 0 (black)
		//black paper & red ink = 00000010 = 2
		#asm
			push af
			push hl
			push de
			push bc
		ld a, 03		;attributte
		ld hl, 16384	;pixels
		ld de, 16385	;pixels + 1
		ld bc, 6144		;pixel area
		ld (hl), l		;set first byte to '0' as HL = 16384 = $4000  therefore L = 0
		ldir			;copy bytes
		ld bc, 767		;attribute area length - 1
		ld (hl), a		;set first byte to attribute value
		ldir			;copy bytes
			pop bc
			pop de
			pop hl
			pop af	
		#endasm
	}
	
	void __FASTCALL__ callScreen()
	{
		#asm
		ld a,2
		call 0x1601      ; select screen
		#endasm
	}

	

	void clearScreen()
	{
		//clear the sprites
		for (screenCounter = 0; screenCounter < 5; ++ screenCounter )
		{
			sprites[screenCounter].n = 129;
		}
		
		for (screenScanY = 0; screenScanY < 10; ++ screenScanY)
		{
			for (screenScanX = 0; screenScanX < 15; ++ screenScanX)
			{
				tiles[screenScanY * scrw + screenScanX] = 0;
			}
		}
		//#define tilepaint(from_x, from_y, to_x, to_y)
		//tilepaint(0, 0, 14, 9) | *shadow << 8;
		//	if (speccy128k == true)
		//	{
		//		tilepaint(0, 0, 14, 9);
				//tilepaint(0, 0, 14, 9) | *shadow << 8;
		//	}

		//	if (speccy128k == false)
		//		tilepaint(0, 0, 14, 9);
			
		tilepaint(0, 0, 14, 9);
			
		FRAME;
	}
	
	

	void blockClear()
	{
		Bitmap(1, 0);
		Bitmap(1, 1);
		Bitmap(1, 2);
	}


	void insertionSort()
	{
		char hiTemp[4];
		
		i = 0;
		j = 0;
		
		for(i = 1; i < 6; ++i)
		{
			key = scores[i].hiScoreList;
			
			strcpy(hiTemp, scores[i].hiInitals);//copies the value of initials[i] to hiTemp
			j = i - 1;
			
			
			while( key > scores[j].hiScoreList && j >= 0)
			{
				//swap scores
				scores[j + 1].hiScoreList = scores[j].hiScoreList;
				
				//copy initials
				strcpy(scores[j + 1].hiInitals, scores[j].hiInitals);
				
				-- j;
			}
			
			scores[j + 1].hiScoreList = key;// place temp value in slot
			strcpy(scores[j + 1].hiInitals, hiTemp);
		}
	}
	
	void update_scoreboard()
	{
		//PrintStr(scoreTxT, 0x0101);
		ltoa(yourScore,yourScoreTXT , 10);//use lota for long variables
		PrintStr(yourScoreTXT, 0x0101);
		
		PrintStr(livesTxT, 0x1801);
		itoa(yourLives,yourLivesTXT , 10);
		PrintStr(yourLivesTXT, 0x1e01);
		
		/*PrintStr("      ", 0x1001);
		ltoa(vy,yourLivesTXT , 10);
		PrintStr(yourLivesTXT, 0x1001);*/
		
		

		//itoa(yourLives,yourLivesTXT , 10);
		//PrintStr(yourLivesTXT, 0x1901);
		//PrintStr(livesTxT, 0x1301);
	}


	void update_screen()
	{
		//*screen= mapy * mapw + mapx;
		
		*screen = gameMap;
		
		for ( j = 1; j < 5; ++j )
		{
			if( sprites[j].n > 0x7f )
				sprites[j].n -= 0x80;
		}
		

	}



#endif