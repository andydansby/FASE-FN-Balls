//You must change the print routine. 
//Now you always print at $4000 video memory
//But video memory change between $4000 and $C000 every frame
//So you need to read $5c01 variable
//PRINT ROUTINE SCREWING WITH 128K mode!!! ERROR

//#pragma output CLIB_MALLOC_HEAP_SIZE = 10000
//#pragma output stack=50000
#pragma output STACKPTR = 56000
//56000

#define max(x,y) (((x)>(y))?(x):(y))
#define min(x,y) (((x)<(y))?(x):(y))

#include "mus/turner3.h"

#include <stdio.h>//being used to convert ints to strings
#include <stdlib.h>//standard library
#include "string.h"//part of z88dk
#include "spectrum.h"//part of z88dk spectrum related utilities
#include "fase.h"//our sprite library
//#include "utils.h"
#include "variables.h"//holds all global variables (my function)



//#include "screenutils.h"//printing messages to the screen TESTING (my function)
#include "gamedisplay.h"
#include "collision.h"//player collisions (my function)
#include "mapsandstart.h"
#include "movement.h"
#include "enemy.h"





#define gettile(x,y) tiles[x + (y << 4) - y ]


void main()
{
	//DI;
	//INIT;// initialize engine
	
	start:
	{//at the start of a game
		
		speccy128k = false;//by defaut a 48k speccy
		
		//is the game 128k
		if( *is128 )
		{
			speccy128k = true;//detects a 128k machine
			//EI;
			//*intadr= IsrSound;
		}
	}

	
	DI;
	INIT;// initialize engine
	
	while (1)//main menu
	{		
		i= inp(0xf7fe) & 0x1f;

		//call to music routine, stops on keypress
		anteat();
		
		if( i==0x1e )//press 1, select kempston joystick
		{
			Input = Joystick;
			//kempston joystick and zx interface 2, port 1
			break;
		}
		
		else if( i==0x1d )//press 2, select cursor joystick
		{
			Input = Cursors;
			//cursor joystick
			break;
		}
		
		else if( i==0x1b )//press 3, select keyboard control
		{
			Input = Keyboard;
			//QAOP space
			break;
		}
		
		else if( i==0x17 )//press 4 redefine keys
		{
			Redefine();
		}
		
		else if( i==0x0F )// press 5 for high score   0000 1111
		{
			//cls();
			blockClear();

			printHighScores();
			
			while (1)
			{
				//z88dkPrint(pressSpace, 21,9);
				//PrintStr128(pressSpace, 9, 21);
				PrintStr(pressSpace, 0x0915);
				i= inp(0x7ffe) & 0x1f;
				
				anteat();
				
				if( i==0x1e )
					break;
			}
			Pause (30);
			Bitmap(0, 0);			
			goto start;// start all over
		}
		
	}
	//place sound effect here
	SFX(5);

//	DI;
	
	//initialize variables before game start
	{
		//initialize variables
		mapx = 0;
		mapy = 0;
		spacepressed = 0;
		num_bullets = 0;
		singleBullet = true; //true
		
		//buildMap = 0;
		//*shadow= 0;
		
		x = vx = ax = 0;
		y = vy = ay = 0;
		
		level = gameMap = 0;//
		//MAX of 12 levels
		yourLives = 3;//yourLives = 5;//temp
		yourScore = 0;//temp	//2,147,483,647 max
		//1147483647
		
		movePlayer = 0;
		
		enemySlowDown = 0;
		enemySpeedUp = 20;//enemySpeedUp = 20;
		
		enemyRetreat = 0;
		enemySteps = 0;
		
		isLevelRead = false;//used to read level into array
		
		bulletDirection = 1;
		playerDirection = 0;
		
		oneUpDisplay = false;
		
		runOnce = true;//so that uniques values can be read once per level

		gameOver = false;		
		animate = 0;		
		stopPlayer = false;		
		debug = false;		
		if(speccy128k == true)	{FRAME;}
			//gets AI to work in 128k mode for some reason

	}
	

	while(1)//game loop
	{
		//we need to read level into array
		//initialize level
		//does not reread on playerDeath
		if (isLevelRead == false)
		{
			runOnceperLevel();
			
			//to test the levels
			//gameMap = level = 0;
			
			if (level > 12)
				level = gameMap = 1;
			if (gameMap > 12)
				level = gameMap = 1;
			
			levelPositioning[2] = ((short)level);//recast level to fit properly in array 
			startingPosition((short)levelPositioning);
			x = levelPositioning[0];
			y = levelPositioning[1];
			
			//place our player
			playerXpos = (unsigned char)(x >> 8);
			playerYpos = (unsigned char)(y >> 8);
			playerCharX = playerXpos >> 4;
			playerCharY = playerYpos >> 4;
				
			//enemyStart(level);//placement of enemies
			
			//enemySlowDown = 0;
			//enemySpeedUp --;//lower is faster
			//if (enemySpeedUp < 0) enemySpeedUp = 0;//now an unsigned char, so this should be redundant

			arrayCounter = 0;
			screenScanX = 0;
			screenScanY = 0;
			screenCounter = 0;
			screenCounterStart = 0;
			screenCounterEnd = 0;//only use this during partial screen scanner in enemies.h
			
			//have you collected the key
			keyCollected = false;
			
			*screen = gameMap;
			
			singleBullet = true;//can fire again
			bullets[0].y = 255;
			
			FRAME;
			
			//update sprites
			for ( i = 0; i < 5; ++ i )
			{
				//FRAME;
				sprites[i].n= data[0 | i<<2],
				sprites[i].x= data[1 | i<<2],
				sprites[i].y= data[2 | i<<2],
				sprites[i].f= data[3 | i<<2];
			}
			
			
			FRAME;
			
			
			cleanTaxicab();
			TaxicabDifference();//taxicab runs ok
			
			gateOpen = false;
			keyCollected = false;
			
			FRAME;
			


			
			
			update_screen();
			
			{
				// find the area to be redrawn when a 
				//special object is collected
				if (oneUpDisplay == true)
				{
					tiles[oneUpY * scrw + oneUpX] = 0;
					tilepaint(oneUpX, oneUpY, oneUpX, oneUpY);
					FRAME;
				}
			}
			
			update_scoreboard();
			
			FRAME;
			
			
			vx = ax = 0;
			vy = ay = 0;
			
			isLevelRead = true;//level has now been read
			
			// Sound to start
			{
				//place sound effect here
				SFX(2);
				Pause (10);
				SFX(2);
				Pause (10);
				SFX(2);
			}
			
			M_OUTP(0xfe, 0);
			
			
		}//end initialize level
		
		//if (debug == true)	Pause (0);
		
		
		
		//tile elimination works ok here, but displays to player first
		
		

		
		//now we play
		if (isLevelRead == true)
		{
			FRAME;// this causes the engine to process a frame generating the scenario
			// we seem to have to refresh when we read the tiles

			
			continousGrassFire();
			
			++ animate;
			if (animate > 1)
				animate = 0;
				
			// movement of enemy sprites
			for ( i = 1; i < 5; ++ i )
			{
				bulletHits();
				{
					{						
						enemyX = sprites[i].x;
						enemyY = sprites[i].y;
						enemyImage = sprites[i].n;
						enemyF = sprites[i].f;
	/*					
						enemyX = sprites[2].x;
						enemyY = sprites[2].y;
						enemyImage = sprites[2].n;
						enemyF = sprites[2].f;
	*/					

						//convert pixel position to character position
						playerCharX = playerXpos >> 4;
						playerCharY = playerYpos >> 4;
						
						
						moveEnemy(enemyX, enemyY, enemyF);//temp
						//enemyCollision(enemyX, enemyY);//temp
						enemyCollision();//temp
						

						sprites[i].x = enemyX;
						sprites[i].y = enemyY;
						sprites[i].n = enemyImage;
						sprites[i].f = enemyF;
/*	
						sprites[2].x = enemyX;
						sprites[2].y = enemyY;
						sprites[2].n = enemyImage;
						sprites[2].f = enemyF;
*/
						//sprites[i].x && sprites[i].y == direction of sprites
						//sprites[i].n == The .n is the number of the sprite 
						//(will draw a different sprite if changed
						//the .f has no effect on the engine, but it's used by 
						//the demo to store the direction of movement 
						//(it's diagonal movement so only 4 directions).
					}
					
				
					
					if (enemySlowDown == 0)
					{
						enemySlowDown = 0;
					}
					++ enemySlowDown;
					if (enemySlowDown == enemySpeedUp) enemySlowDown = 0;				
					//eventually enemySpeedUp will count down with each new level 
					// to be added for artificial stupidity
				}
			}
			
			*drwout= (unsigned int)update_scoreboard;

			// movement of bullets
			for ( i = 0; i < num_bullets; ++ i )
			{
				if( dirbul[i]&3 )
				{
					if( dirbul[i]&1 )
					{
						if( bullets[i].x < scrw * 16 )
							bullets[i].x += 4;
						else
							remove_bullet(i);
					}				
					else
					{
						if( bullets[i].x > 4 )
							bullets[i].x -= 4;
						else
							remove_bullet(i);
					}
				}
				
				if( dirbul[i]&12 )
				{
					if( dirbul[i]&4 )
					{
						if( bullets[i].y<scrh*16 )
							bullets[i].y+= 4;
						else
						remove_bullet(i);
					}
					else
					{
						if( bullets[i].y>4 )
							bullets[i].y-= 4;
						else
							remove_bullet(i);
					}
				}
			}
			
			{				
				//	printGrassFire();
				tileCollision();
				verticalMovement();
				horizontalMovement();				

				//here X>>8 is from 0 to 240
				//here Y>>8 is from 0 to 159
				//here Y>>9 is from 0 to 207
				
				playerXpos = (unsigned char)(x >> 8);
				playerYpos = (unsigned char)(y >> 8);
			}
			
			//directional movement of the character
			{
				++ movePlayer;
				if (movePlayer > 16) movePlayer = 0;
				moveMainCharacter(movePlayer);			
			}			
			//move main character
			sprites[0].x = x >> 8;
			sprites[0].y = y >> 8;
			
			//hard number if player tries to cheat by forcing to the right
			if (sprites[0].x > 234)
			{
				playerDeath();
			}
			

			
			//beta testers cheat
			/*
			i= inp(0xbffe) & 0x1f;
			if( i==0x0F )
			{
				warpLevel();
			}*/
			
		}
		
		//game over check
		if( yourLives < 1 ) //end game
		{
			//remove all sprites
			for ( i = 0; i < 5; ++ i )
			{
				sprites[i].n = 129;
			}
			
			//bpoke (23553,128);//FASE Engine
			if (bpeek (23553) == 128)
				FRAME;
			blockClear();			
			EXIT;// to stop the engine
			
			
			//endgame();
			PrintStr2(gameOverTXT, 0x0b03);
			Pause (180);
			
			//blockClear();
			//check to see if your current score is a new high score
			if (yourScore > scores[4].hiScoreList)
			{
				highScore();
			}
			
			Bitmap(0, 0);//display title screen
			
			isLevelRead = false;//reset flag to re read level

			INIT;// initialize engine
			
			goto start;// start all over
		}
		
	}//end of play loop
	
}//end of program loop
