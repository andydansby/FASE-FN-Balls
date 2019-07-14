cls

zcc +zx -zorg=32685 -O3 -vn -m main.c ntropic.asm -o build\main.bin -lndos

cd build

appmake +zx -b main.bin --org 32685 -o program.tap

move program.tap ..\

cd ..


rem 32763 is program start
rem 32844 is sound data start