#ifndef SCREENUTILS_H
#define SCREENUTILS_H



//#include <stdio.h>//being used to convert ints to strings
//#include <stdlib.h>//being used to convert ints to strings
//#include <input.h>//used to read keys
//#include "spectrum.h"

/*
d,i		16-bit int	signed decimal
b		16-bit int	unsigned binary
o		16-bit int	unsigned octal
x,X		16-bit int	unsigned hexadecimal, X uses capitals
u		16-bit int	unsigned decimal
ld,li	32-bit long	signed decimal
lb		32-bit long	unsigned binary
lo		32-bit long	unsigned octal
lx,lX	32-bit long	unsigned hexadecimal, X uses capitals
lu		32-bit long	unsigned decimal
c		char	single character
s		char *	string of characters up to \0 or until precision exhausted
p,P		void *	pointer (printed as x,X with leading 0x)
lp,lP	24-bit void *	pointer (printed as lx,lX with leading 0x)
n		int *	number of characters output so far is written into the argument
%		none	output a %
*/

void printtester6(unsigned char info, unsigned char info2,unsigned char info3, unsigned char info4)
{
	char text[20];
	PrintStr("             ", 821);	
	sprintf(text, "%d:%d:%d:%d", info,info2,info3,info4);
	PrintStr(text, 821);
}



/*
void printtester1(unsigned char info)
{
	char text[10];
	//unsigned char info2 = (unsigned char)info;
	//PrintStr("          ", 321);
	PrintStr("    ", 3,1);
	sprintf(text, "%d", info);
	//sprintf(text, "%d", info);//prints in decimal
	//sprintf(text, "%x", info);//prints in hex	
	//char* text = "bob";//works
	
	PrintStr(text, 3,1);	
}

void printtester9(unsigned char info1,unsigned char info2, unsigned char info3)
{
	char text[25];
	
	PrintStr("          ", 3,1);
	sprintf(text, "%d:%d:%d", info1, info2, info3);
	PrintStr(text, 3,1);
}

void printtester11(unsigned char info1, unsigned char info2, unsigned char info3)
{
	char text[10];
	PrintStr("          ", 8,1);
	sprintf(text, "%d:%d:%d", info1, info2, info3);
	PrintStr(text, 8,1);
}


/*
void printtester2(unsigned char info, unsigned char info2)
{
	char text[10];
	PrintStr("          ", 321);	
	sprintf(text, "%d:%d", info,info2);
	PrintStr(text, 321);
}

void printtester3(unsigned char info, unsigned char info2)
{
	char text[10];
	PrintStr("            ", 321);
	sprintf(text, "%d:%d", info,info2);
	PrintStr(text, 321);
}

void printtester4(unsigned char info)
{
	char text[10];
	
	PrintStr("    ", 321);
	sprintf(text, "%d", info);
	PrintStr(text, 321);
}

void printtester5(unsigned char info, unsigned char info2)
{
	char text[20];
	PrintStr("            ", 822);	
	sprintf(text, "%d:%d", info,info2);
	PrintStr(text, 822);
}

void printtester6(unsigned char info, unsigned char info2,unsigned char info3, unsigned char info4)
{
	char text[20];
	PrintStr("             ", 321);	
	sprintf(text, "%d:%d:%d:%d", info,info2,info3,info4);
	PrintStr(text, 321);
}

void printtester8(unsigned char info, unsigned char info2,unsigned char info3, unsigned char info4)
{
	char text[20];
	PrintStr("             ", 821);	
	sprintf(text, "%d:%d:%d:%d", info,info2,info3,info4);
	PrintStr(text, 821);
}





void printtester12(unsigned char info, unsigned char info2,unsigned char info3, unsigned char info4,unsigned char info5)
{
	char text[20];
	PrintStr("                 ", 321);	
	sprintf(text, "%d:%d:%d:%d:%d", info,info2,info3,info4,info5);
	PrintStr(text, 321);
}




void printtester99(long info)
{
	char text[10];
	
	PrintStr("          ", 821);
	sprintf(text, "%ld", info);
	PrintStr(text, 821);
}

/*
void printtester99(unsigned char *info)
{
	char text[10];
	
	PrintStr("    ", 821);
	sprintf(text, "%s", info);
	PrintStr(text, 821);
}*/

#endif