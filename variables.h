#ifndef VARIABLES_H
#define VARIABLES_H

////////////////////////////////////
//         GLOBAL VARIABLES       //
////////////////////////////////////

//extern long heap(50000);
//#pragma output CLIB_MALLOC_HEAP_SIZE = 10000
//#pragma output STACKPTR = 64000

//////////////////////////////////////
//  VARIABLES TAGGED for INSPECTION //
//////////////////////////////////////
char xx, yy;//used in display



static unsigned short jz,jsr=5;//used in randomizer

//obsolete?????
unsigned char screenX;
unsigned char screenY;
//////////////////////////////////////
//  VARIABLES TAGGED for INSPECTION //
//////////////////////////////////////


/////////////// LEAST USED VARIABLES

#define maxvx   600
#define maxvy   600

//used for our high Score List
struct HiScore {
   long hiScoreList;
   char hiInitals[4];
};

struct HiScore scores[] = 
{
	{4000L, "AMD"},
	{3000L, "RVG"},	
	{2000L, "DAV"},
	{1000L, "ALV"},
	{200L, "BAZ"},
	{199, "WTF"}
};//minimum 3 digits, messes up on 2 digits
//used for our high Score List

unsigned char initials[4]  = "\0";
long key;

//objects
unsigned char oneUpCollected, oneUpDisplay;
unsigned char oneUpX, oneUpY;
unsigned char keyCollected;

unsigned char twohundredPoints;
unsigned char fourhundredPoints;
unsigned char twohundredPointsX, twohundredPointsY;
unsigned char fourhundredPointsX, fourhundredPointsY;

unsigned char gateOpen;
unsigned char keyX, keyY;
unsigned char warpX, warpY;
unsigned char gateX1, gateY1, gateX2, gateY2;
unsigned char animate;
unsigned char screenWarpX;
unsigned char screenWarpY;
unsigned char levelWarpX;
unsigned char levelWarpY;

unsigned char stopPlayer;

unsigned char runOnce;//run this once per level



unsigned char yourScoreTXT[20] = "000000000";//000,000,000
unsigned char yourLivesTXT[3] = "03";
unsigned char gameOverTXT[10] = "GAME OVER";
unsigned char gameStartTXT[10] = "GO";
unsigned char highScoreMessage1[16] = "CONGRATULATIONS";
unsigned char highScoreMessage2[26] = "YOU HAVE A NEW HIGH SCORE";
unsigned char highScoreMessage3[24] = "Enter your initals with";
unsigned char highScoreMessage4[13] = "UP/Down/FIRE";
unsigned char clearTXT[10] = "         ";
long yourScore;//2,147,483,647 max
char yourLives;
unsigned char scoreTxT[6] = "Score";
unsigned char livesTxT[6] = "Lives";
unsigned char levelText[6] = "Level";
unsigned char highScoreText[20] = "The Top Scores are:";

unsigned char buffer[3] = "\0";
unsigned char pressSpace[12] = "Press Space";
char str[25];

unsigned char letter;
int timeout;

unsigned char gameOver;




char bulletDirection;
char playerDirection;


//used for display especially with 128k
/*int _g_number;
unsigned char g_str_x;
unsigned char g_str_y;
unsigned char _g_mask;
unsigned char *textString;
unsigned char *ptr_tmp;
unsigned char g_string[32] = "                               ";*/


//used for display especially with 128k


unsigned char data[20]= 
{
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};//enemy placement data


unsigned char debug;


short levelPositioning[3] = {0,0,0};

char dirbul[4];//used for bullets

//globals
char i, j;

char mapx;//used for indexing screen
char mapy;//used for indexing screen
char spacepressed;//used for firing bullets

unsigned char gameMap;//used to pull up a new maps
unsigned char level;//which game level are we on
unsigned char isLevelRead;//used to read each level when loaded in memory


//from _show_str()
unsigned int scr, dst;
//    char count;



/////////////// LEAST USED VARIABLES

/////////////// MID RANGE VARIABLES
//speeds up and slows down the enemies
unsigned char enemySlowDown;
unsigned char enemySpeedUp;
//speeds up and slows down the enemies

unsigned char xCenterofTile;
unsigned char yCenterofTile;// used to detect if enemy is in the center of the tile

unsigned char singleBullet;
char num_bullets;
char k;

unsigned char enemyRetreat;//used when calling moveEnemy
unsigned char enemySteps;//used when calling moveEnemy
unsigned char enemyDirection;// move the enemy X number of steps from the obstacle
//used when calling moveEnemy

/////////////// MID RANGE VARIABLES

/////////////// MOST USED VARIABLES



short x, vx, ax;
short y, vy, ay;

unsigned char movePlayer;//animation for player sprite 

short xx1;//used in collision of player
short xx2;//used in collision of player
short yy1;//used in collision of player
short yy2;//used in collision of player



short x1;//used in collision of enemy
short x2;//used in collision of enemy
short y1;//used in collision of enemy
short y2;//used in collision of enemy

//inital placement of enemies
unsigned char enemy1x;
unsigned char enemy1y;
unsigned char enemy2x;
unsigned char enemy2y;
unsigned char enemy3x;
unsigned char enemy3y;
unsigned char enemy4x;
unsigned char enemy4y;


//ATTENTION
//these temporary variables are to be used with functions

unsigned char count;//count how many items are in the array	
unsigned char tile;
unsigned char attribute;

unsigned char differenceX;//used in taxicab difference
unsigned char differenceY;//used in taxicab difference
unsigned char difference;//used in taxicab difference

unsigned char tmpx1;//used to detect if bullet hit enemy
unsigned char tmpy1;//used to detect if bullet hit enemy

unsigned char iterator;
unsigned char arrayCounter;
//ATTENTION
//these temporary variables are to be used with functions
unsigned char enemyPosition;



unsigned char enemyX,enemyY,enemyF,enemyImage,enemyStatus;
unsigned char enemyLaunchX, enemyLaunchY;


//players position
unsigned short playerXpos;//player X position 0-255
unsigned short playerYpos;//player Y position 0-172
unsigned char playerXattr;//player x attribute position
unsigned char playerYattr;//player y attribute position

unsigned char lastGoodX, lastGoodY;



unsigned char playerCharX;//playerCharX character range 0 - 15
unsigned char playerCharY;//playerCharY character range 0 - 9
unsigned char enemyCharX;//enemyCharX character range 0 - 15
unsigned char enemyCharY;//enemyCharY character range 0 - 9
//playerX pixel range 0 - 240
//playerY pixel range 0 - 160
//enemyX pixel range 0 - 240
//enemyY pixel range 0 - 160
//players position

short squaredRadius, squaredDifferenceX, squaredDifferenceY;
unsigned char objectRadius;

//used for our Grassfire AI
unsigned char grassfire[150] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

//only use this during partial screen scanner in enemies.h
unsigned char screenScanX;
unsigned char screenScanY;
unsigned char screenCounter;
unsigned char screenCounterStart;
unsigned char screenCounterEnd;
//only use this during partial screen scanner in enemies.h

unsigned char centerValue;
unsigned char northValue;
unsigned char southValue;
unsigned char eastValue;
unsigned char westValue;
unsigned char compare1;
unsigned char compare2;
unsigned char compare3;
unsigned char center, north, south, east, west;
//used for our Grassfire AI


/////////////// MOST USED VARIABLES

//these are reusable variables
unsigned char compareX1, compareX2;
unsigned char compareY1, compareY2;




unsigned char minRedrawX, maxRedrawX;
unsigned char minRedrawY, maxRedrawY;

//temp for testing
short xx3, yy3;
short xx4, yy4;
char tileType;

//stuff below is just notes















///////////////////////////////////
//  VARIABLES TAGGED for REMOVAL //
///////////////////////////////////

/*char enemyDirections[4] = {
	0,0,0,0
};*/
//unsigned int killed;
//int bobbie;

//char initals[5] = "AMD";

//temp variables
//	char in1[10] = "         ";
//	char in2[10];
//	char in3[10];
//	char in4[10];
//	char output[40];
//	int noggin;
//temp variables


//char hiTemp[4];

//unsigned char firstInital = 65;//letter A
//unsigned char secondInital = 65;//letter A
//unsigned char thirdInital = 65;//letter A


////   Moved from Function ////
//short vY1, aY1, YY1;//eliminated
//short vX1,aX1,XX1;
//char buildMap;// are you currently playing

//char loop;
//short xx3;
//short xx4;
//short yy3;
//short yy4;

//short count;//count how many items are in the array	
//short tile;
//unsigned char lives;
//
//unsigned char tmpx2;
//unsigned char tmpy2;

//

//unsigned short decision;
//unsigned char barrierPosition;
//unsigned char enemyCenter;
//unsigned char enemyXwest, enemyXeast;
//unsigned char enemyYnorth, enemyYsouth;
//unsigned char tileCenter;
//unsigned char enemyObsticleTrace;
//unsigned char barrier;
//unsigned char bob = 0;//used to print to screen
//unsigned char sue;//used to print to screen also
//unsigned char test;
//unsigned char scanx, scany;
//long scorearray[6] = {0,0,0,0,0,0};
// short horizonal [3] = {0,0,0};
// short vertical [3] = {0,0,0};


///////////////////////////////////
//  VARIABLES TAGGED for REMOVAL //
///////////////////////////////////




////////////////////////////////////
//         GLOBAL VARIABLES       //
////////////////////////////////////



//// AMD, RVG, AAG, BAZ, JIM,GNU
/*
uint32_t topTenScores[10]; will allow ten 32-bit scores.  A long is signed so it will take one bit away for negative scores.  A uint32_t is defined in stdint.h and means the same thing as unsigned long.  stdint.h is usually preferred because it's portable (the name uint32_t says unsigned 32-bit whereas what a long is depends on the compiler)*/

/*
There is a shellsort function in the library that is very short - you may want to check that out if you need to sort the table

https://github.com/z88dk/z88dk/tree/master/libsrc/_DEVELOPMENT/stdlib/z80/sort

Insertion sort might actually be smaller yet.  You can find the c functions defined in stdlib.h.  I think they both work like qsort*/

/*You may end up having an array of structs as high score table to associate a name with a score.  These functions can sort those as well.*/

#endif
