#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ctype.h> 

void convertIntToCharWithSpaces(int intArray[], char charArray[], int length, int spacesBetweenChars) {
    int charIndex = 0;

    for (int i = 0; i < length; i++) {
        charArray[charIndex] = intArray[i] + '0';
        charIndex++;

        if (i < length - 1) {
            for (int space = 0; space < spacesBetweenChars; space++) {
                charArray[charIndex] = ' ';
                charIndex++;
            }
        }
    }
    charArray[charIndex] = '\0';
}


int verife(int t[], int k){
int bol = 1,j;
    for (j=0; j<10;j++){
        if(k  == t[j]){
            bol = 0;
            break;
        }
    }
    return bol;
 }