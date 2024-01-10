all:
	gcc -Isrc/Include -Lsrc/lib -o main src/main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -ISDL_image -ISDL.h  -ISDL_ttf.h -ISDL_image.h -ISDL_mixer.h