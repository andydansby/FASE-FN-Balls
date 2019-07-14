#ifndef MAPSANDSTART_H
#define MAPSANDSTART_H


void runOnceperLevel()
{
	if (runOnce == true)
	{
		oneUpDisplay = false;
		runOnce = false;
	}
	

	
	//fourhundredPoints
	
	//oneUpCollected
	
}


void startingPosition ()
//oid startingPosition (short levelPositioning[])
{
	//short xxx = 0;// = levelPositioning[0];// to be used for output
	//short yyy = 0;// = levelPositioning[1];
	
	xx1 = 0;
	yy1 = 0;
	
	//short Level = levelPositioning[2];
	level = levelPositioning[2];
	
	if (level == 0)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 120;
		yy1 = 24;		
		//1UP tile location, 99 if unused
		oneUpX = 99;
		oneUpY = 99;
		
		//bonus points, 99 if unused
		twohundredPointsX = 99;
		twohundredPointsY = 99;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;
		
		//key tile location
		keyX = 7;
		keyY = 6;
		//gate tile position
		gateX1 = 7;
		gateY1 = 8;		
		
		//in screen warp to
		warpX = 9;
		warpY = 5;		
		//why not 9,2?  //is this setting obsolete?
		//screenWarpX = 9;//screenWarpX = 6;
		//screenWarpY = 2;//screenWarpY = 8;		
		//warp to next level
		levelWarpX = 9;
		levelWarpY = 7;		
		//where enemy launches from after death
		//tile << 4 | 8;same as tile * 16 + 8
		enemyLaunchX = 1 << 4 | 8;//24  
		enemyLaunchY = 1 << 4 | 8;//24
		
		//----------------------------------
		//enemy 1 - 8, 8, 8, 3
		data[4] = 8;//n =sprite number
		enemy1x = 1;
		enemy1y = 1;
		
		//enemy 2 - 9, 230, 8, 3		
		data[8] = 8;//n =sprite number
		enemy2x = 13;
		enemy2y = 1;
		
		//enemy 3 - 10, 5, 150, 1		
		data[12] = 10;//n =sprite number
		enemy3x = 1;
		enemy3y = 8;
		
		//enemy 2 - 12, 230, 150, 2		
		data[16] = 12;//n =sprite number
		enemy4x = 13;
		enemy4y = 8;
	}

	if (level == 1)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 200;
		yy1 = 55;		
		//1UP tile location
		oneUpX = 6;
		oneUpY = 1;	

		//bonus points, 99 if unused
		twohundredPointsX = 99;
		twohundredPointsY = 99;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;
		
		//key tile location
		keyX = 12;
		keyY = 8;
		//gate tile position
		gateX1 = 1;
		gateY1 = 4;
		
		//in screen warp to
		warpX = 4;
		warpY = 8;		
		
		//warp to next level
		levelWarpX = 1;
		levelWarpY = 4;		
		//where enemy launches from after death
		enemyLaunchX = (1 << 4) | 8;//24
		enemyLaunchY = (1 << 4) | 8;//24
		
		//----------------------------------
		//enemy 1 - 8, 8, 8, 3
		data[4] = 8;//n =sprite number
		enemy1x = 2;
		enemy1y = 8;
		
		//enemy 2 - 9, 230, 8, 3		
		data[8] = 8;//n =sprite number
		enemy2x = 9;
		enemy2y = 8;
		
		//enemy 3 - 10, 5, 150, 1		
		data[12] = 10;//n =sprite number
		enemy3x = 12;
		enemy3y = 1;
		
		//enemy 2 - 12, 230, 150, 2		
		data[16] = 12;//n =sprite number
		enemy4x = 2;
		enemy4y = 1;
	}
	
	if (level == 2)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 24;//5
		yy1 = 56;//1
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;
		
		//bonus points, 99 if unused
		twohundredPointsX = 4;
		twohundredPointsY = 5;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;
		
		//key tile location
		keyX = 1;
		keyY = 8;
		//gate tile position
		gateX1 = 1;
		gateY1 = 4;

		//in screen warp to
		warpX = 13;
		warpY = 1;
		
		levelWarpX = 3;//
		levelWarpY = 6;//
		//where enemy launches from after death
		enemyLaunchX = (8 << 4) | 8;//136
		enemyLaunchY = (5 << 4) | 8;//88
		
		//----------------------------------
		data[4] = 8;//n =sprite number
		enemy1x = 8;
		enemy1y = 4;
		
		//enemy 2 - 9, 230, 8, 3		
		data[8] = 8;//n =sprite number
		enemy2x = 12;
		enemy2y = 2;
		
		//enemy 3 - 10, 5, 150, 1		
		data[12] = 10;//n =sprite number
		enemy3x = 8;
		enemy3y = 8;
		
		//enemy 2 - 12, 230, 150, 2		
		data[16] = 12;//n =sprite number
		enemy4x = 13;
		enemy4y = 8;
	}
	
	if (level == 3)
	{
		//pixel position of player
		//tileX or tileY * 16 + 8
		xx1 = 24;//1
		yy1 = 104;//6		
		//1UP tile location
		oneUpX = 99;//
		oneUpY = 99;//
				
		//bonus points, 99 if unused
		twohundredPointsX = 99;
		twohundredPointsY = 99;
		
		fourhundredPointsX = 6;
		fourhundredPointsY = 8;
		
		//key tile location
		keyX = 11;//
		keyY = 8;//
		//gate tile position
		gateX1 = 1;//
		gateY1 = 7;//

		//in screen warp to
		warpX = 8;//
		warpY = 1;//
		//warp to next level
		levelWarpX = 1;//
		levelWarpY = 8;//
		//where enemy launches from after death
		//tileX or tileY * 16 + 8
		enemyLaunchX = (4 << 4) | 8;//72
		enemyLaunchY = (7 << 4) | 8;//120
		
		//----------------------------------
		
		data[4] = 8;//n =sprite number
		enemy1x = 6;
		enemy1y = 5;
		
		//enemy 2 - 9, 230, 8, 3		
		data[8] = 8;//n =sprite number
		enemy2x = 8;
		enemy2y = 6;
		
		//enemy 3 - 10, 5, 150, 1		
		data[12] = 10;//n =sprite number
		enemy3x = 13;
		enemy3y = 6;
		
		//enemy 2 - 12, 230, 150, 2		
		data[16] = 12;//n =sprite number
		enemy4x = 12;
		enemy4y = 1;
	}
	
	if (level == 4)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 96;
		yy1 = 48;		
		//1UP tile location
		oneUpX = 13;
		oneUpY = 6;		
		//key tile location
		keyX = 10;
		keyY = 1;		
				
		//bonus points, 99 if unused
		twohundredPointsX = 13;
		twohundredPointsY = 1;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;
		
		
		//gate tile position
		gateX1 = 5;
		gateY1 = 4;		
		
		//in screen warp to
		warpX = 2;
		warpY = 8;		
		//why not 9,2?  //is this setting obsolete?
		//screenWarpX = 9;//screenWarpX = 6;
		//screenWarpY = 2;//screenWarpY = 8;		
		//warp to next level
		levelWarpX = 5;
		levelWarpY = 5;		
		//where enemy launches from after death
		enemyLaunchX = (11 << 4) | 8;//184
		enemyLaunchY = (8 << 4) | 8;//136
		
		//----------------------------------
		
		data[4] = 8;//n =sprite number
		enemy1x = 11;
		enemy1y = 7;
		
		//enemy 2 - 9, 230, 8, 3		
		data[8] = 8;//n =sprite number
		enemy2x = 7;
		enemy2y = 8;
		
		//enemy 3 - 10, 5, 150, 1		
		data[12] = 10;//n =sprite number
		enemy3x = 2;
		enemy3y = 6;
		
		//enemy 2 - 12, 230, 150, 2		
		data[16] = 12;//n =sprite number
		enemy4x = 13;
		enemy4y = 2;
	}	
	
	if (level == 5)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 40;
		yy1 = 88;		
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;		
		//key tile location
		keyX = 13;
		keyY = 1;
		
		//bonus points, 99 if unused
		twohundredPointsX = 10;
		twohundredPointsY = 6;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;
		
		//gate tile position
		gateX1 = 1;
		gateY1 = 5;		
		
		//in screen warp to
		warpX = 99;
		warpY = 99;		
		//warp to next level
		levelWarpX = 0;
		levelWarpY = 5;		
		//where enemy launches from after death
		enemyLaunchX = (8 << 4) | 8;//120
		enemyLaunchY = (4 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 1;
		enemy1y = 1;
		data[4] = 8;//n =sprite number

		enemy2x = 3;
		enemy2y = 3;		
		data[8] = 8;//n =sprite number		
		
		enemy3x = 3;
		enemy3y = 8;	
		data[12] = 10;//n =sprite number
				
		enemy4x = 8;
		enemy4y = 6;	
		data[16] = 12;//n =sprite number
	}
	
	if (level == 6)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 168;//10
		yy1 = 76;//	5
		//1UP tile location
		oneUpX = 3;
		oneUpY = 3;
		//key tile location
		keyX = 2;
		keyY = 7;
		//gate tile position
		gateX1 = 7;
		gateY1 = 4;

		//bonus points, 99 if unused
		twohundredPointsX = 4;
		twohundredPointsY = 1;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;	

		//in screen warp to
		warpX = 13;
		warpY = 8;		
		
		//warp to next level
		levelWarpX = 8;
		levelWarpY = 4;		
		//where enemy launches from after death
		enemyLaunchX = (1 << 4) | 8;//120
		enemyLaunchY = (4 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 6;
		enemy1y = 4;
		data[4] = 8;//n =sprite number

		enemy2x = 13;
		enemy2y = 7;		
		data[8] = 8;//n =sprite number		
		
		enemy3x = 4;
		enemy3y = 8;	
		data[12] = 10;//n =sprite number
				
		enemy4x = 3;
		enemy4y = 1;	
		data[16] = 12;//n =sprite number
	}

	if (level == 7)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 24;//10
		yy1 = 40;//	5
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;		
		//key tile location
		keyX = 12;
		keyY = 8;
		
		//bonus points, 99 if unused
		twohundredPointsX = 99;
		twohundredPointsY = 99;
		
		fourhundredPointsX = 7;
		fourhundredPointsY = 2;	

		//gate tile position
		gateX1 = 1;
		gateY1 = 1;
		
		//in screen warp to
		warpX = 2;
		warpY = 8;		
		
		//warp to next level
		levelWarpX = 1;
		levelWarpY = 0;		
		//where enemy launches from after death
		enemyLaunchX = (7 << 4) | 8;//120
		enemyLaunchY = (4 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 13;
		enemy1y = 1;
		data[4] = 8;//n =sprite number

		enemy2x = 13;
		enemy2y = 8;		
		data[8] = 10;//n =sprite number		
		
		enemy3x = 1;
		enemy3y = 8;	
		data[12] = 10;//n =sprite number
				
		enemy4x = 6;
		enemy4y = 4;	
		data[16] = 12;//n =sprite number
	}

	if (level == 8)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 216;//13
		yy1 = 120;//
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;		
		//key tile location
		keyX = 10;
		keyY = 8;

		//bonus points, 99 if unused
		twohundredPointsX = 1;
		twohundredPointsY = 4;
		
		fourhundredPointsX = 6;
		fourhundredPointsY = 2;	

		//gate tile position
		gateX1 = 13;
		gateY1 = 8;
	
		//in screen warp to
		warpX = 7;
		warpY = 7;		
		//warp to next level
		levelWarpX = 13;
		levelWarpY = 9;		
		//where enemy launches from after death
		enemyLaunchX = (2 << 4) | 8;//120
		enemyLaunchY = (1 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 9;
		enemy1y = 1;
		data[4] = 8;//n =sprite number

		enemy2x = 4;
		enemy2y = 1;		
		data[8] = 10;//n =sprite number		
		
		enemy3x = 9;
		enemy3y = 6;	
		data[12] = 12;//n =sprite number
				
		enemy4x = 6;
		enemy4y = 8;	
		data[16] = 12;//n =sprite number
	}
	
	if (level == 9)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 136;//8
		yy1 = 56;//3
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;		
		//key tile location
		keyX = 1;
		keyY = 2;

		//bonus points, 99 if unused
		twohundredPointsX = 5;
		twohundredPointsY = 6;
		
		fourhundredPointsX = 99;
		fourhundredPointsY = 99;	

		
		//gate tile position
		gateX1 = 8;
		gateY1 = 4;
	
		//in screen warp to
		warpX = 99;
		warpY = 99;		
		//warp to next level
		levelWarpX = 8;
		levelWarpY = 5;		
		//where enemy launches from after death
		enemyLaunchX = (4 << 4) | 8;//120
		enemyLaunchY = (2 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 13;
		enemy1y = 1;
		data[4] = 8;//n =sprite number

		enemy2x = 13;
		enemy2y = 8;		
		data[8] = 10;//n =sprite number		
		
		enemy3x = 1;
		enemy3y = 5;	
		data[12] = 12;//n =sprite number
				
		enemy4x = 5;
		enemy4y = 5;	
		data[16] = 12;//n =sprite number
	}

	if (level == 10)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 120;//7
		yy1 = 120;//7
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;		
		//key tile location
		keyX = 7;
		keyY = 1;
		//gate tile position
		gateX1 = 7;
		gateY1 = 6;
		
		//bonus points, 99 if unused
		twohundredPointsX = 99;
		twohundredPointsY = 99;
		
		fourhundredPointsX = 13;
		fourhundredPointsY = 3;	

		//in screen warp to
		warpX = 99;
		warpY = 99;		
		//warp to next level
		levelWarpX = 7;
		levelWarpY = 5;		
		//where enemy launches from after death
		enemyLaunchX = (13 << 4) | 8;//120
		enemyLaunchY = (1 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 4;
		enemy1y = 5;
		data[4] = 8;//n =sprite number

		enemy2x = 10;
		enemy2y = 5;		
		data[8] = 10;//n =sprite number		
		
		enemy3x = 7;
		enemy3y = 2;	
		data[12] = 12;//n =sprite number
				
		enemy4x = 12;
		enemy4y = 1;	
		data[16] = 12;//n =sprite number
	}
	
	if (level == 11)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 152;//9
		yy1 = 88;//5
		//1UP tile location
		oneUpX = 99;
		oneUpY = 99;		
		//key tile location
		keyX = 4;
		keyY = 5;
		
		//bonus points, 99 if unused
		twohundredPointsX = 99;
		twohundredPointsY = 99;
		
		fourhundredPointsX = 9;
		fourhundredPointsY = 8;	

		//gate tile position
		gateX1 = 8;
		gateY1 = 5;
		
		//in screen warp to
		warpX = 99;
		warpY = 99;		
		//warp to next level
		levelWarpX = 7;
		levelWarpY = 5;		
		//where enemy launches from after death
		enemyLaunchX = (6 << 4) | 8;//120
		enemyLaunchY = (8 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 13;
		enemy1y = 8;
		data[4] = 8;//n =sprite number

		enemy2x = 10;
		enemy2y = 1;		
		data[8] = 10;//n =sprite number		
		
		enemy3x = 1;
		enemy3y = 1;	
		data[12] = 12;//n =sprite number
				
		enemy4x = 1;
		enemy4y = 8;	
		data[16] = 12;//n =sprite number
	}

	if (level == 12)
	{
		//tileX or tileY * 16 + 8
		//pixel position of player
		xx1 = 216;//13
		yy1 = 24;//1
		//1UP tile location
		oneUpX = 8;
		oneUpY = 1;		
		//key tile location
		keyX = 9;
		keyY = 1;
		
		//bonus points, 99 if unused
		twohundredPointsX = 3;
		twohundredPointsY = 7;
		
		fourhundredPointsX = 9;
		fourhundredPointsY = 6;	

		//gate tile position
		gateX1 = 12;
		gateY1 = 1;
				
		//in screen warp to
		warpX = 13;
		warpY = 8;		
		//warp to next level
		levelWarpX = 0;
		levelWarpY = 4;		
		//where enemy launches from after death
		enemyLaunchX = (8 << 4) | 8;//120
		enemyLaunchY = (4 << 4) | 8;//72
		
		//----------------------------------
		
		enemy1x = 3;
		enemy1y = 1;
		data[4] = 8;//n =sprite number

		enemy2x = 8;
		enemy2y = 6;		
		data[8] = 10;//n =sprite number		
		
		enemy3x = 2;
		enemy3y = 8;	
		data[12] = 12;//n =sprite number
				
		enemy4x = 13;
		enemy4y = 5;	
		data[16] = 12;//n =sprite number
	}

	//have you collected the key
	keyCollected = false;
		
	//to adjust to scale.
	//returns
	playerCharX = xx1 >> 4;
	playerCharY = yy1 >> 4;
	levelPositioning[0] = xx1 * 256;
	levelPositioning[1] = yy1 * 256;
	
	data[0] = 0;//n = sprite number 
	data[1] = xx1;//x position
	data[2] = yy1;//y position
	data[3] = 0;//f = data
	
	data[7] = 0;//f value, enemy 1
	data[11] = 0;//f value, enemy 2
	data[15] = 0;//f value, enemy 3
	data[19] = 2;//f value, enemy 4
	
	//PLACING ENEMIES
	//enemy1
	//tile << 4 | 8;same as tile * 16 + 8
	data[5] = enemy1x << 4 | 8;//x position
	data[6] = enemy1y << 4 | 8;//y position
	//enemy2
	data[9] = enemy2x << 4 | 8;//x position
	data[10] = enemy2y << 4 | 8;//y position
	//enemy3
	data[13] = enemy3x << 4 | 8;//x position
	data[14] = enemy3y << 4 | 8;//y position
	//enemy4
	data[17] = enemy4x << 4 | 8;//x position
	data[18] = enemy4y << 4 | 8;//y position
	
	//comes after the level data is set to initilize sprites
	for ( i = 0; i < 5; ++ i )
	{
		sprites[i].n = data[0 | i<<2],
		sprites[i].x = data[1 | i<<2],
		sprites[i].y = data[2 | i<<2],
		sprites[i].f = data[3 | i<<2];
	}
	
	
	
	
}



#endif