rem compiling options

@echo off

rem if not exist z88dkenv.bat (
rem   echo.
rem  echo Error: z88dkenv.bat doesn't exist. Please copy it into this folder.
rem   exit /b 1
rem )

echo #########################
echo #### remove old TAP  ####
echo #########################
del game.tap

echo #########################
echo ## compile with        ##
echo ##    FASE GFX         ##
echo #########################


echo #########################
echo #### setting paths   ####
echo #########################
rem /////////////////////////////////////////////////
SET PATH=%PATH%;C:\z88dk10
SET Z80_OZFILES=C:\z88dk10\lib
SET ZCCCFG=C:\z88dk10\lib\config
SET PATH=C:\z88dk10\bin;%PATH%
SET Z88DK_ENV_id074741=true
rem /////////////////////////////////////////////////

echo #########################
echo ## done setting paths  ##
echo #########################
rem pause


if "%1"=="gfx" (

  bin\Png2Rcs gfx\loading.png build\loading.rcs build\loading.atr
  bin\zx7b build\loading.rcs build\loading.rcs.zx7b
  bin\zx7b build\loading.atr build\loading.atr.zx7b
rem <-------------------------------------
rem copy mus\music.asm build\music.asm 

  bin\png2rcs gfx\menu.png build\menu.rcs build\menu.atr  
  bin\zx7b build\menu.rcs build\menu.rcs.zx7b
  bin\zx7b build\menu.atr build\menu.atr.zx7b
  

  bin\Png2Rcs gfx\control.png build\control.rcs build\control.atr
  bin\zx7b build\control.rcs build\control.rcs.zx7b
  bin\zx7b build\control.atr build\control.atr.zx7b

rem  bin\GenTmx 3 3 10 10 gfx\map.tmx

  bin\TmxCompress gfx\map.tmx build\map_compressed.bin > build\defmap.asm
  
  echo #########################
  echo ##        MUSIC        ##
  echo #########################
  
  rem 128k only music
rem  bin\sjasmplus asm\player.asm > nul
rem  bin\zx7b build\player.bin build\player.zx7b

  rem push music data (notes) to the build directory
rem  bin\xm2tritone mus\music.xm build\music.asm
  copy mus\music.asm build\music.asm

bin\step1
  
  
rem compiling the player file  
rem  bin\sjasmplus asm\music.asm > nul
rem compressing and moving the compiled player
rem  if exist mus/music.xm bin\zx7b 
rem  build\music.bin build\music.zx7b

rem bin\zx7b build\music.bin build\music.zx7b
  
  echo #########################
  echo ##        MUSIC        ##
  echo #########################
  
  goto cont
)

rem pause


echo ######################
echo ##graphics and sound##
echo ######################

if "%1"=="config" (
:cont
  bin\sjasmplus asm\engine0.asm > nul
  bin\sjasmplus asm\engine1.asm > nul
  bin\sjasmplus asm\engine2.asm > nul
  bin\step2
  bin\zx7b build\block1.bin build\block1.zx7b
  bin\zx7b build\block2.bin build\block2.zx7b
)
echo.

rem call z88dkenv.bat

rem zcc +zx -zorg=32772 -O3 -vn main.c -o build\main.bin -lndos

rem zcc +zx -zorg=32772 -O3 -vn -m main.c mus\anteat.asm -o build\main.bin -lndos

rem --c-code-in-asm -a

zcc +zx -zorg=32772 -O3 -vn -m main.c mus\anteat.asm -o build\main.bin -lndos 

rem zcc +zx -zorg=32772 -O3 -vn -m main.c mus\anteat.asm -o build\main.bin -lndos


echo File main.bin compiled from main.c
bin\zx7b build\main.bin build\main.zx7b
bin\step3
bin\sjasmplus asm\loader.asm

bin\gentape game.tap                  ^
        basic game 0  build\loader.bin  ^
         data         build\engine.zx7b ^
         data         build\player.zx7b

rem if exist build\player.zx7b (
rem  bin\gentape game.tap                  ^
rem         basic game 0  build\loader.bin  ^
rem          data         build\engine.zx7b ^
rem          data         build\player.zx7b
rem ) else (
rem   bin\gentape game.tap                  ^
rem         basic game 0  build\loader.bin  ^
rem         data         build\engine.zx7b
rem )




rem if exist build\player.zx7b (
rem  bin\gentape game.tzx                  ^
rem        basic game 0  build\loader.bin  ^
rem         data         build\engine.zx7b ^
rem       stop48                           ^
rem         data         build\player.zx7b
rem ) else (
rem  bin\gentape game.tzx                  ^
rem        basic game 0  build\loader.bin  ^
rem         data         build\engine.zx7b
rem )
