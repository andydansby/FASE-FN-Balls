#ifndef COLLISION_H
#define COLLISION_H



void blockMinMax()
{
	//for clearing a block of tiles
	//especially key and gate tiles

	minRedrawX = min(gateX1,keyX);
	minRedrawY = min(gateY1,keyY);
	maxRedrawX = max(gateX1,keyX);
	maxRedrawY = max(gateY1,keyY);
}


void playerDeath()
{
	yourLives --;
	
	//M_OUTP(0xfe, 5);//changes border color
	//place sound effect here		 
	
	//clearScreen();//causing crash
	
	singleBullet = true;//can fire again
	
	bullets[0].x = bullets[0].y = 1;
	
	//place sound effect here
	SFX(10);
	
	//debug = true;
	
	// setup screen
	isLevelRead = false;
}

void warpLevel()
{
	mapx ++;
	level ++;
	gameMap ++;
		
		
	runOnce = true;//only happens once per level
	isLevelRead = false;
	
	//place sound effect here
	SFX(3);
	
	//bullets[0].x = bullets[0].y = 1;							 
}

void collect1up()
{

	yourScore += 25;
	yourLives ++;
	if (yourLives > 9)
		yourLives = 9;
	
	tiles[oneUpX + scrw * oneUpY] = 0;
	
	tilepaint(oneUpX, oneUpY, oneUpX, oneUpY);
	
	FRAME;
	
	//place sound effect here
	SFX(8);
}

void collectKey()
{
	/*if (keyCollected == false)
	{
		//add key
		tiles[keyX + scrw * keyY] = 13;
		gateOpen = false;
	}
	if (keyCollected == true)
	{
		tiles[keyX + scrw * keyY] = 0;
		tiles[gateX1 + scrw * gateY1] = 0;
		gateOpen = true;
		keyCollected = true;
	}*/
	tiles[keyX + scrw * keyY] = 0;
	tiles[gateX1 + scrw * gateY1] = 0;
	gateOpen = true;
	keyCollected = true;
	
	blockMinMax();
	
	tilepaint(minRedrawX, minRedrawY, maxRedrawX, maxRedrawY);
	
	yourScore += 25;
	
	//place sound effect here
	SFX(7);
}

void collect200()
{
	//hundredPoints = true;
	
	yourScore += 200;
	
	tiles[twohundredPointsX + scrw * twohundredPointsY] = 0;
	
	tilepaint(twohundredPointsX, twohundredPointsY, twohundredPointsX, twohundredPointsY);
	
	FRAME;
	
	//place sound effect here
	SFX(8);
}

void collect400()
{
	//hundredPoints = true;
	
	yourScore += 400;
	
	tiles[fourhundredPointsX + scrw * fourhundredPointsY] = 0;
	
	tilepaint(fourhundredPointsX, fourhundredPointsY, fourhundredPointsX, fourhundredPointsY);
	
	FRAME;
	
	//place sound effect here
	SFX(8);
}

void warpScreen()
{
	xx1 = (warpX << 4) + 8;
	yy1 = (warpY << 4) + 8;
	
	sprites[0].n = 129;	
	
	sprites[0].x = tmpx1;
	sprites[0].y = tmpy1;
	playerXpos = tmpy1;
	playerYpos = tmpy1;
	playerCharX = warpX;
	playerCharY = warpY;
	//place sound effect here
	SFX(5);

	sprites[0].n = 0;
	
	x = xx1 << 8;
	y = yy1 << 8;
}


void bouncePlayer()
{
	vx = -vx;
	vy = -vy;
	
	//place sound effect here
	SFX(6);
	
	//need some sort of limitor
	/*if (vx > 600)
	{
		vx = 600; ax = -40;
	}
	if (vx < -600)
	{
		vx = -600; ax = 40;
	}
	if (vy > 600) 
	{
		vy = 600; ay = -40;
	}
	if (vy < -600) 
	{
		vy = -600; ay = 40;
	}*/
}


//Check vertical border / edges
//void verticalEdge ();
void verticalMovement()
{
	//mapx is char
	//mapy is char
	
	vy += ay;
	y += vy;
		
	if( vy + 8 >> 3 )
	{
		ay = -vy >> 3;
	}
	else
	{
		ay = vy = 0;
	}
	
	if (stopPlayer == true)
	{
		ay = vy = 0;
		//place sound effect here
		SFX(12);
	}

}

//Check horizontal border / edges
//void horizontalEdge ();
void horizontalMovement()
{
	//mapx is char
	//mapy is char

	vx += ax;
	x += vx;

	if( vx + 8 >> 3 )
	{
		ax = -vx >> 3;
	}
	else
	{
		ax = vx = 0;
	}
	
	if (stopPlayer == true)
	{
		ax = vx = 0;
		//place sound effect here
		SFX(12);
	}
}

void tileCollision()
{
	tileType = 0;	
	//players sprite
	xx1 = (sprites[0].x - 6) >> 4;//6 pixels from center up
	xx2 = (sprites[0].x + 5) >> 4;//5 pixels from center down
	yy1 = (sprites[0].y - 6) >> 4;//6 pixels from center left
	yy2 = (sprites[0].y + 5) >> 4;//5 pixels from center right

	xx3 = sprites[0].x;
	yy3 = sprites[0].y;
	
	xx4 = sprites[0].x >> 4;
	yy4 = sprites[0].y >> 4;
	
	//these 4 conditions can cause issues on edges
	//if (tiles[xx1 + scrw * yy1] > 0)
	if (tiles[xx1 + scrw * yy1] > 8)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx1 + scrw * yy1];
	}
	if (tiles[xx2 + scrw * yy1] > 8)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx2 + scrw * yy1];
	}
	if (tiles[xx1 + scrw * yy2] > 8)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx1 + scrw * yy2];
	}
	if (tiles[xx2 + scrw * yy2] > 8)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx2 + scrw * yy2];
	}
	
	if (xx3 > 230)
	{
		vx = -vx;
		//place sound effect here
		SFX(6);
	}
	if (xx3 < 7)
	{
		vx = -vx;
		//place sound effect here
		SFX(6);
	}
	if (yy3 > 152)
	{
		vy = -vy;
		//place sound effect here
		SFX(6);
	}
	if (yy3 < 8)
	{
		vy = -vy;
		//place sound effect here
		SFX(6);
	}
	

	switch(tileType)
	{
		//do nothing
		case 0://empty square
		{
			//need to capture the last place where we were when blank
			
			//unsigned short playerXpos;//player X position 0-255
			//unsigned short playerYpos;//player Y position 0-172
			
			//last known good position
			//playerXpos = xx3;
			//playerYpos = yy3;
			
			lastGoodX = xx3;
			lastGoodY = yy3;
			
			stopPlayer = false;
			break;
		}
		case 1://bottom edge
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 2://top edge
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 3://left edge
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 4://right edge
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 5://left top corner
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 6://right top corner
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 7://left bottom corner
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}
		case 8://right bottom corner
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			break;
		}		
		case 9://warp
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			warpLevel();
			break;
		}		
		case 10://warp destination
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			//do nothing
			break;
		}
		case 11://in screen warp
		{
			warpScreen();
			break;
		}			
		case 12://in screen warp
		{
			warpScreen();
			break;
		}		
		case 13://key
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			//keyCollected = true;
			collectKey();			
			break;
		}		
		case 14://1UP
		{
			lastGoodX = xx3;
			lastGoodY = yy3;
			oneUpCollected = true;
			collect1up();
			break;
		}
		case 15://enemy launcher / deadly
		{
			playerDeath();
			break;
		}
		case 16://red diamond obsticle
		{
			playerDeath();
			break;
		}
		case 17://yellow diamond obsticle
		{
			playerDeath();
			break;
		}
		case 18://yellow spikes obsticle
		{
			playerDeath();
			break;
		}
		case 19://red spikes obsticle
		{
			playerDeath();
			break;
		}
		case 20://gate obsticle
		{
			stopPlayer = true;
			break;
		}
		case 21://red skull obsticle
		{
			playerDeath();
			break;
		}
		case 22://yellow skull obsticle
		{
			playerDeath();
			break;
		}
		
		case 23://barrier obsticle
		{
			stopPlayer = true;
			break;
		}
		
		case 24://barrier obsticle
		{
			stopPlayer = true;
			break;
		}
		
		case 25://barrier obsticle
		{
			stopPlayer = true;
			break;
		}
		
		case 26://barrier obsticle
		{
			stopPlayer = true;
			break;
		}
		
		case 27://barrier obsticle
		{
			stopPlayer = true;
			break;
		}
		
		//tester
		case 28://tester
		{
			bouncePlayer();
			
			vx = vx >> 1;
			vy = vy >> 1;
			break;
		}
		
		case 29://curves obsticle
		{
			vx = vx - 50;
			vy = vy - 50;
			break;
		}
		
		case 30://bounce obsticle
		{
			bouncePlayer();			
			break;
		}
		
		case 31://slowdown obsticle
		{
			//vx += (ax + ax);
			//vy += (ay + ay);
			
			vx = ax;
			vy = ay;
			break;
		}
		
		case 32://collect 200 points
		{
			collect200();
			break;
		}
		
		case 33://collect 400 points
		{
			collect400();
			break;
		}
	}//end cases


	

}


#endif