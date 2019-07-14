void print_value(unsigned char x, unsigned char y, int number)
{
    _g_str_x = x;
    _g_str_y = y;
    _g_mask = 1;

    //_itoa(number); // g_string saved in func
	itoa(number, yourLivesTXT, 10);
	textString = yourLivesTXT;

    // print with engine sync
    //if(fase_status == FASE_RUNNING)
    //    *drwout = (unsigned int) _show_str;
    //else
    //    _show_str();
}

	void z88dkPrint(unsigned char *string, unsigned char x, unsigned char y)
	{
		printPaper(0);
		printInk(7);
		
		printMode(32);//how many columns
		printAt(x, y);
		printf("GAME OVER");//printf(string);//
	}

void highscoreEntry128k()
{
	arrayCounter = 0;
	while (arrayCounter < 3)
	{
		if (*shadow == 128)
			*shadow = 0;
		
		//now we have down doing the same as up for testing
		if( Input() & 0x04 )// A go down
		{
			-- letter;
		}
		if( Input() & 0x08 )// Q go up
		{
			++ letter;			
		}
		if( Input() & 0x10) // Space (FIRE)
		{
			//Sound(EFFX, 0);
			//i= Input() & 0x0f;
			++ arrayCounter;
		}
		//letter tiles are 32 to 57
		//however sinclair ascii is from 65 to 90
		if (letter > 65) letter = 90;//if you go past Z, roll back to A
		if (letter < 65) letter = 90;//if you go past A, roll back to Z

		initials[arrayCounter] = letter;//+33 is adjusting for sinclair ascii
		sprintf(buffer, "%c", letter);
		
		switch(arrayCounter)
		{
			case 0:
				PrintStr2("Z", 0x0c14);
			break;
			
			case 1:
				PrintStr2("Z", 0x0d14);
			break;
			
			case 2:
				PrintStr2("Z", 0x0e14);
			break;
			
			Pause (20);
		}
	}
}


void highscoreEntry48k()
{
	arrayCounter = 0;
	while (1)
	{
		FRAME;
		//now we have down doing the same as up for testing
		if( Input() & 0x04 )// A go down
		{
			-- letter;
		}
		if( Input() & 0x08 )// Q go up
		{
			++ letter;			
		}
		if( Input() & 0x10) // Space (FIRE)
		{
			//Sound(EFFX, 0);
			//i= Input() & 0x0f;
			++ arrayCounter;
		}
		//Pause (0);
		
		//letter tiles are 32 to 57
		//however sinclair ascii is from 65 to 90
		if (letter > 57) letter = 32;//if you go past Z, roll back to A
		if (letter < 32) letter = 57;//if you go past A, roll back to Z

		initials[arrayCounter] = letter + 33;//+33 is adjusting for sinclair ascii
		sprintf(buffer, "%c", letter);
		
		if (arrayCounter == 0)
		{
			tiles[5 + scrw * 6] = letter;
			tilepaint(5, 6, 5, 6);
			if (speccy128k == true)
			{
				*shadow;
			}
		}
		
		if (arrayCounter == 1)
		{
			tiles[6 + scrw * 6] = letter;
			tilepaint(6, 6, 6, 6);
		}
		
		if (arrayCounter == 2)
		{
			tiles[7 + scrw * 6] = letter;
			tilepaint(7, 6, 7, 6);
		}
		
		if (arrayCounter == 3)
		{	break;}
		Pause (10);
	}
}

void printHighScores()
{
	screenCounter = 0;
	
	insertionSort();

	//PrintStr128(highScoreText, 01, 01);
	//FRAME;
	//z88dkPrint(highScoreText, 9, 6);
	//z88dkPrint(highScoreText, 9, 6) | *shadow << 8;
	//PrintStr128(highScoreText, 6, 9);
	if (speccy128k == false){		
		cls();
		PrintStr(highScoreText, 0x0609);
		FRAME;
		}
	
	if (speccy128k == true){		
		cls();
		PrintStr(highScoreText, 0x0609);
		//FRAME;
		}
	
	xx = 11;
	//xx = 0x0403;//if using PrintStr
	
	for (screenCounter = 0; screenCounter < 5; screenCounter++ )
	{
		strcpy (str," ");
		strcat (str,scores[screenCounter].hiInitals);	//Concatenate strings
		strcat (str,"....");
		
		ltoa(scores[screenCounter].hiScoreList, yourScoreTXT , 10);//use lota for long variables
		strcat (str,yourScoreTXT);
		
		if (speccy128k == false){
			PrintStr(str, 0x030b + xx);
			FRAME;
		}
		//PrintStr128(str, 9, xx);
		//PrintStr128(gameOverTXT, 11,3);
		//PrintStr128(str, 9, xx) | *shadow<<8;
		//PrintStr128(str, 9, xx);
		//FRAME;
		//PrintStr128(str, 9, xx);
		//PrintStr(str, 0x030b + xx);
		//PrintStr(str, xx);
		//PrintStr(gameOverTXT, 0x0b03);
		xx ++;
	}
	//FRAME;
}


//meant to copy from one screen to another in 128k mode
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
		/*if (*shadow != 0)
		{
			#asm
				ld hl,$c000
				ld de,$4000
				ld bc,6912
				ldir
		   #endasm
		}*/
	}
}


void setShadow()
{
	//set shadow to 0
		#asm
		ld hl,$5c01;
		ld a,0;
		ld (hl),a;
		#endasm
}

void changeBanks()
{
		//ld a,($5b5c) ;Previous value of port
		//and $f8
		//or 0 ;Select bank 0
		//di
		//ld bc,$7ffd
		//ld ($5b5c),a
		//out (c),a
		//ei
	#asm
		ld      a, ($5c01)
		xor     b
		ld      b, a
		and     $80
		xor     h
        ld      h, a
	#endasm		
}



void __CALLEE__ PrintStr_old ( char *string, unsigned char x, unsigned char y ){
    #asm
        pop     af
        pop     de
        pop     bc
        pop     ix
        push    af
        ld      hl, ($5c00)
        ld      a, e
        and     $18
        or      $40
        or      h
        ld      h, a
        ld      a, e
        rrca
        rrca
        rrca
        and     $e0
        add     a, c
        ld      l, a
print3:
		ex      de, hl
        ld      a, (ix)
        inc     ix
        add     a, a
        ret     z
        ld      l, a
        ld      h, $0f
        add     hl, hl
        add     hl, hl
        ld      b, 4
print4: 
		ld      a, (hl)
        ld      (de), a
        inc     l
        inc     d
        ld      a, (hl)
        ld      (de), a
        inc     l
        inc     d
        djnz    print4
        ld      hl, $f801
        add     hl, de
        jr      print3
    #endasm
}