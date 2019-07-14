#ifndef MOVEMENT_H
#define MOVEMENT_H

void remove_bullet(char k)
{
	if( num_bullets )
	{
		-- num_bullets;

		while ( k < num_bullets )
		{
			dirbul[k] = dirbul[k + 1],
			bullets[k].x = bullets[k + 1].x;
			bullets[k].y = bullets[++k].y;
			//bullets[k].y = bullets[k + 1].y;
		}
		bullets[k].y = 255;
	}
	singleBullet = true;//can fire again
}

//void moveMainCharacter(unsigned char movePlayer);
//this routine has issues with Calling via non-function pointer 
//Input() is non-function pointer
void moveMainCharacter(unsigned char movePlayer)
{
	unsigned char spriteFrame;
	unsigned char xCenterofTile;
	unsigned char yCenterofTile;
	
	//animation
	{
		if (movePlayer > 8) spriteFrame = 1;
		if (movePlayer < 8) spriteFrame = 0;
	}
	
	//playerX pixel range 0 - 240
	//playerY pixel range 0 - 160	
	//center of tile = (half_tileSize + (tileSize * tileNumber))

	{//move player
	
		if (stopPlayer == false)
		{
			if ( !Input() & 0x0f )//if there is any direction pressed
			{
				bulletDirection = 0;
				playerDirection = 0;
			}
			
			if( Input() & 0x01 ) // P - go right / east
			{
				sprites[0].n = 0 + spriteFrame;//bubble orientation right 4th sprite over
				ax = vx < maxvx ? 40 : 0;
				bulletDirection += 1;
				playerDirection += 2;//x increasing
			}

			if( Input() & 0x02 ) // O - go left / west
			{	
				sprites[0].n = 2 + spriteFrame;//bubble orientation left 4th sprite over
				ax = vx > -maxvx ? -40 : 0;
				bulletDirection += 2;
				playerDirection += 8;//x decreasing
			}

			if( Input() & 0x04 )// A go down / south
			{
				sprites[0].n = 4 + spriteFrame;//bubble orientation down 4th sprite over
				ay = (vy < maxvy) ? 40 : 1;
				bulletDirection += 4;
				playerDirection += 1;//y increasing
			}

			if( Input() & 0x08 )// Q go up / north
			{
				sprites[0].n = 6 + spriteFrame;//bubble orientation up 4th sprite over
				ay = (vy > -maxvy) ? -40 : -1;
				bulletDirection += 8;
				playerDirection += 4;//y decreasing
			}

			//FIRE BULLET
			if( Input() & 0x10 && !spacepressed && singleBullet == true )
			{ // Space (FIRE)
				
				//place sound effect here
				SFX(4);
				
				singleBullet = false;//cannot fire flag
				
				bullets[num_bullets].x= sprites[0].x;
				bullets[num_bullets].y= sprites[0].y;
				i= Input() & 0x0f;
				//dirbul[num_bullets]= i ? i : 1;
				dirbul[num_bullets] = i ? i : bulletDirection;
				++ num_bullets;
				
				//place sound effect here   
			}
			spacepressed= Input() & 0x10;
		}//end false stop player
		
		if (stopPlayer == true)
		{
			//find last good known position
			// playerXpos & playerYpos
			x = lastGoodX << 8;
			y = lastGoodY << 8;
			stopPlayer = false;
		}
		

	}
	
	center = playerCharX + scrw * playerCharY;

	{
		north = playerCharX + scrw * (playerCharY - 1);	
		if (north > 150)
			north = center;
	}
	
	{
		south = playerCharX + scrw * (playerCharY + 1);
		if (south > 150)
			south = center;
	}
	
	{
		east = playerCharX + 1 + scrw * playerCharY;
		if (east > 150)
			east = center;
	}
	
	{
		west = playerCharX - 1 + scrw * playerCharY;
		if (west > 150)
			west = center;
	}
	
	northValue = grassfire[north];
	southValue = grassfire[south];
	eastValue = grassfire[east];
	westValue = grassfire[west];
	
	//tiles[center]
	
	//PROBLEM 1 Array not updating correctly once player moves from start tile
	//IDEA seems solid in spreadsheet
	//set kernel
	//center of tile = 1
	
	//refresh the tiles on moving
	if (tiles[north] == 0)
		grassfire[north] = 2;
	else
		grassfire[north] = 255;
	
	if (tiles[south] == 0)
		grassfire[south] = 2;
	else
		grassfire[south] = 255;
	
	if (tiles[east] == 0)
		grassfire[east] = 2;
	else
		grassfire[east] = 255;
	
	if (tiles[west] == 0)
		grassfire[west] = 2;
	else
		grassfire[west] = 255;
	
	if (tiles[center] == 0)
		grassfire[center] = 1;
	if (tiles[center] > 0)
		grassfire[center] = 255;
	//refresh the tiles on moving
	
	
		
	//enhancement 1
	//when player touches the center of a tile, change the grassfire slightly and throw the enemy off course
	xCenterofTile = (8+ (16 * playerCharX));
	yCenterofTile = (8+ (16 * playerCharY));
	if ((playerXpos == xCenterofTile) && (playerYpos == yCenterofTile))
	{
		// when player touches center of tile, do something
		//M_OUTP(0xfe, 6);//flashes to show that sprite is in the middle of the tile
	}
}

#endif