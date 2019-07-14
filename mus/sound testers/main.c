//#include "SFX2.h"
//#include "dean.h"
//#include "beepfx.h"
//#include "beepfxtrim.h"
#include "turner.h"

extern void ntropic(void);

void __FASTCALL__ Pause ( unsigned int msecs ){
    #asm
loop1:  ld      bc, 21
loop2:  djnz    loop2
        dec     c
        jr      nz, loop2
        dec     hl
        ld      a, l
        or      h
        jr      nz, loop1
    #endasm
}

main()
{
   //ntropic();
   
   Pause (90);
   
   while (1)
   {
	   
	   SFX(8);
	   Pause (30);
	  // SFX(7);
	  // Pause (90);
	   
   }
   
   {
	   /*
	    beepeffx(0);
		Pause (90);
		beepeffx(1);
		Pause (90);
		*/	   
   }
   
}


//compile with
// zcc +zx -zorg=32772 -O3 -vn -m main.c  tritone.asm -o build\main.bin -lndos


//appmake +zx -b main.bin --org 32772  -o program.tap
