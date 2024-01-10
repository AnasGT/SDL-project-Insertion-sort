#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"
#include <ctype.h> 


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MAX_DIGITS 11

bool IsAllDigitsEntered(int digitCount) {
    return digitCount >= MAX_DIGITS - 1;
}

int main(int argc, char** argv){
SDL_Init(SDL_INIT_EVERYTHING);
SDL_Init(SDL_INIT_VIDEO);
TTF_Init();


///#########################--------------------DECLARATION--------------------#########################
//window
SDL_Window *window;
//surface
SDL_Surface *background,*ScreenSurface, *menu_img,*menu_buttons[2],*play_img,*play_numbers, *exit_button, *choose_bk, *choose_button[2], *input_bk, *on, *off, *setting_img, *set_button[2], *set_exit; 
//rectangle
SDL_Rect menu_buttons_rect[2],numbers_rect,play_exit,  choose_button_rect[2], choose_rect, input_rect, set_button_rect[2], set_exit_rect, on_off_rect[2];
//vars
int n=10,i,j,v,T[11],k, tst_choose, music_vol = 100, chunk_vol = 100, cot = 0;
int menu=0,play=0,Exit=0,choose=0,Settings=0,input=0,index=10;
int bol;
//chars
char T_str[30];
//text color
SDL_Color textColor= { 20, 45, 73 };
SDL_Color hover_color= { 255, 255, 255 };
//font
TTF_Font *font, *font2, *set_font;
//sdl_event
SDL_Event event;
//mix Music
Mix_Music *music;
// mix chunk
Mix_Chunk *click;
//bool
bool music_tst = true, chunk_tst = true;
bool digitsEntered = false;



///###############--------------------Window Valaeu + test--------------------###############
window= SDL_CreateWindow("add_chain", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_FULLSCREEN);

if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}

///###############--------------------render--------------------###############
SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
if (render == NULL) {
    printf("render could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}

///###############--------------------screenSurface Valaeu + test--------------------###############
ScreenSurface = SDL_GetWindowSurface(window);

if (ScreenSurface == NULL) {
    printf("ScreenSurface could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}

///###############--------------------Backround Valeau + test-------------------###############
background = IMG_Load("imgs/back.png");

if (background == NULL) {
    printf("Background image could not be loaded! SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

///###############----------------------DECLARATION----------------------###############
//OPEN FONT 
TTF_Init();
font  = TTF_OpenFont("my_font/DripOctober-vm0JA.ttf",60);
font2 = TTF_OpenFont("my_font/DripOctober-vm0JA.ttf",150);
set_font = TTF_OpenFont("my_font/DripOctober-vm0JA.ttf",10);


//input img
input_bk = IMG_Load("imgs/play_bk.png");


//input 
int digitCount = 0; // To count the number of entered digits
SDL_Color color = {255, 255, 30, 255};
char textInput[MAX_DIGITS * 2]; // Maximum 10 digits + 9 spaces + 1 null terminator
textInput[0] = '\0';
SDL_Surface *temp = TTF_RenderText_Solid(font, "ENTRE 10 DIGIT HERE", color);
SDL_Texture *textImage = SDL_CreateTextureFromSurface(render, temp);
SDL_Rect pos = {300, 450, temp->w, temp->h};
SDL_FreeSurface(temp);
temp = NULL;


//settings img 
on = IMG_Load("imgs/set/on.png");
off = IMG_Load("imgs/set/off.png");
setting_img = IMG_Load("imgs/set/ggg.png");

//set button
set_button[0] = TTF_RenderText_Solid(font,"Music sound",color);
set_button[1] = TTF_RenderText_Solid(font,"click sound",color);

//set button rect
set_button_rect[0].x = 646;
set_button_rect[0].y = 375;
set_button_rect[1].x = 646;
set_button_rect[1].y = 482;

//set exit button
set_exit = TTF_RenderText_Solid(font,"EXIT",textColor);
set_exit_rect.x = 1177;
set_exit_rect.y = 630;

//on off rect
on_off_rect[0].x = 1122;
on_off_rect[0].y = 370;
on_off_rect[1].x = 1122;
on_off_rect[1].y = 480;

//play image
play_img = IMG_Load("imgs/play_bk.png");

// menu button
menu_buttons[0]=TTF_RenderText_Solid(font,"START",textColor);
menu_buttons[1]=TTF_RenderText_Solid(font,"Exit",textColor);

//menu_buttons_rect
menu_buttons_rect[0].x=891;
menu_buttons_rect[0].y=440;
menu_buttons_rect[1].x=893;
menu_buttons_rect[1].y=585;

//choose img + rect
choose_bk = IMG_Load("imgs/choose.png");
choose_rect.x = 470;
choose_rect.y = 280;

//choose button
choose_button[0] = TTF_RenderText_Solid(font,"RANDOM",textColor);
choose_button[1] = TTF_RenderText_Solid(font,"INPUT",textColor);

//choose button rect
choose_button_rect[0].x = 845;
choose_button_rect[0].y = 440;
choose_button_rect[1].x = 883;
choose_button_rect[1].y = 586;

//exit button in play
exit_button = TTF_RenderText_Solid(font,"Exit", hover_color);
play_exit.x = 1490;
play_exit.y = 842;

//numbers_rect
numbers_rect.x=305;
numbers_rect.y=450;

//SDL Mixer
//music
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,2048);
music = Mix_LoadMUS("my_sound/main/07.-Main-Music-01.ogg");
if (music == NULL) {
    printf("Failed to load music! SDL Mixer Error: %s\n", Mix_GetError());
}
Mix_PlayMusic(music, -1);

//chunk
click=Mix_LoadWAV("my_sound/mouse/mixkit-arcade-mechanical-bling-210.ogg");
music = Mix_LoadMUS("my_sound/main/07.-Main-Music-01.ogg");
if (click == NULL) {
    printf("Failed to load chunk! SDL Mixer Error: %s\n", Mix_GetError());
}

    Mix_VolumeMusic(music_vol);
    Mix_VolumeChunk(click,chunk_vol);

///###############--------------------Menu-------------------###############
//menu
menu:

  menu=1;
  while(menu!=0){

    SDL_BlitSurface( background, NULL, ScreenSurface, NULL);
    SDL_BlitSurface( menu_buttons[0], NULL, ScreenSurface, &menu_buttons_rect[0]);
    SDL_BlitSurface( menu_buttons[1], NULL, ScreenSurface, &menu_buttons_rect[1]);
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                menu = 0;
                goto Exit;
                break;

            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                    case SDLK_q:
                    case SDLK_e:
                        menu=0;
                        goto Exit;
                        break;
            }
    
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(event.motion.x > 846 && event.motion.x < 1073 && event.motion.y > 420 && event.motion.y < 512){
                        //play
                        Mix_PlayChannel(-1,click,0);
                        goto choose;
                    }

                    else if (event.button.x > 850 && event.button.x < 1069 && event.button.y > 565 && event.button.y < 657){
                        //Exit
                        Mix_PlayChannel(-1,click,0);
                        goto Exit;
                    }

                    else if ((event.button.x > 264 && event.button.x < 350 && event.button.y > 174 && event.button.y < 260) || (event.button.x > 322 && event.button.x < 411 && event.button.y > 231 && event.button.y < 321)  ){
                        //Settings
                        Mix_PlayChannel(-1,click,0);
                        goto Settings;
                    }

                }
                break;

            case SDL_MOUSEMOTION:
                if(event.motion.x > 846 && event.motion.x < 1073 && event.motion.y > 420 && event.motion.y < 512){
                    //play
                    SDL_FreeSurface(menu_buttons[0]);
                    menu_buttons[0]=TTF_RenderText_Solid(font,"PLAY", hover_color);
                }
                else if(event.button.x > 850 && event.button.x < 1069 && event.button.y > 565 && event.button.y < 657){
                    //Exit
                    SDL_FreeSurface(menu_buttons[1]);
                    menu_buttons[1]=TTF_RenderText_Solid(font,"Exit", hover_color);
                }
                else {
                    SDL_FreeSurface(menu_buttons[1]);
                    SDL_FreeSurface(menu_buttons[0]);
                    menu_buttons[0]=TTF_RenderText_Solid(font,"PLAY", textColor);
                    menu_buttons[1]=TTF_RenderText_Solid(font,"Exit", textColor);
                }
            break;
        break;
        }
    }
    SDL_UpdateWindowSurface( window );
}




// ///###############--------------------choose-------------------###############
choose:
choose=1;

while (choose){
    SDL_BlitSurface(play_img,NULL,ScreenSurface,NULL);
    SDL_BlitSurface(choose_bk,NULL,ScreenSurface,&choose_rect);
    SDL_BlitSurface(choose_button[0],NULL,ScreenSurface,&choose_button_rect[0]);
    SDL_BlitSurface(choose_button[1],NULL,ScreenSurface,&choose_button_rect[1]);

        while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                menu = 0;
                goto Exit;
                break;

            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                    case SDLK_q:
                    case SDLK_e:
                        menu=0;
                        goto Exit;
                        break;
            }
    
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(event.motion.x > 840 && event.motion.x < 1080 && event.motion.y > 418 && event.motion.y < 512){
                        //random
                        Mix_PlayChannel(-1,click,0);

                        //random valeur de tableau
                        
                        for (j=0; j<10 ;j++)
                            T[j]=-1;
                        i=0;
                         srand((unsigned int)time(NULL));

                        for (j=0; j<10;j++){
                            bol = 0;
                            while (bol == 0) {
                                k = rand() % 10;
                                bol=verife(T,k);
                                if(bol == 1){
                                    T[j] = k;
                                }
                            }
                        }
                        choose = 0;
                        goto play;
                    }
                        // input
                    else if (event.button.x > 851 && event.button.x < 1070 && event.button.y > 565 && event.button.y < 658){
                        Mix_PlayChannel(-1,click,0);
                        goto input;
                    }
                }
                break;

            case SDL_MOUSEMOTION:
                if(event.motion.x > 840 && event.motion.x < 1080 && event.motion.y > 418 && event.motion.y < 512){
                    //Random
                    SDL_FreeSurface(choose_button[0]);
                    choose_button[0]=TTF_RenderText_Solid(font,"RANDOM", hover_color);
                }
                    else if (event.button.x > 851 && event.button.x < 1070 && event.button.y > 565 && event.button.y < 658){
                    //Input
                    SDL_FreeSurface(choose_button[1]);
                    choose_button[1]=TTF_RenderText_Solid(font,"INPUT", hover_color);
                }
                else {
                    SDL_FreeSurface(choose_button[1]);
                    SDL_FreeSurface(choose_button[0]);
                    choose_button[0]=TTF_RenderText_Solid(font,"RANDOM", textColor);
                    choose_button[1]=TTF_RenderText_Solid(font,"INPUT", textColor);
                }
            break;
        break;
        }
    }
    SDL_UpdateWindowSurface( window );
}

///###############--------------------input-------------------###############
SDL_StartTextInput();
input:
        choose = 0;
        digitCount = 0;
        textInput[0] = '\0'; // Resetting the textInput string
        SDL_UpdateWindowSurface(window);

while (1) {
input = 1;

    while (input) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    input = 0;
                    break;

                case SDL_TEXTINPUT:
                    // Check if the input is a numeric character and there's still space for input
                    if (strlen(textInput) < sizeof(textInput) - 2 && digitCount < MAX_DIGITS && strlen(event.text.text) == 1 && isdigit(event.text.text[0])) {
                        // Concatenate the input to the existing text
                        strcat(textInput, event.text.text);

                        // Add a space after each digit (if not the last digit)
                        if (digitCount < MAX_DIGITS - 1) {
                            strcat(textInput, " ");
                        }

                        // Store the entered digit in the array
                        T[digitCount] = event.text.text[0] - '0';

                        digitCount++;

                        if (digitCount >= MAX_DIGITS - 1) {
                            input = 0; 
                            SDL_DestroyRenderer(render);
                            
                            goto play;
                        }

                        if (textImage) {
                            SDL_DestroyTexture(textImage);
                            textImage = NULL;
                        }
                        // Update text image
                        temp = TTF_RenderText_Solid(font2, textInput, color);

                        if (temp) {
                            textImage = SDL_CreateTextureFromSurface(render, temp);
                            pos.w = temp->w;
                            pos.h = temp->h;
                            SDL_FreeSurface(temp);
                            temp = NULL;
                        }
                    }
                    break;
            }
        }
        // SDL_RenderClear(render);
        // SDL_RenderCopy(render, textImage, NULL, &pos);
        // SDL_RenderPresent(render);
        SDL_RenderClear(render);
        input_bk = IMG_Load("imgs/play_bk.png");
        SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(render, input_bk);
        SDL_RenderCopy(render, backgroundTexture, NULL, NULL);
        SDL_DestroyTexture(backgroundTexture);
        SDL_RenderCopy(render, textImage, NULL, &pos);
        SDL_RenderPresent(render);
    }
}

///###############--------------------Play-------------------###############
play:
play=1;

convertIntToCharWithSpaces(T,T_str,n,1);
play_numbers=TTF_RenderText_Solid(font2,T_str,color);

while(play){
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_BlitSurface(play_img,NULL,ScreenSurface,NULL);
    SDL_BlitSurface(exit_button, NULL, play_img, &play_exit);
    SDL_BlitSurface(play_numbers,NULL,ScreenSurface,&numbers_rect);

    SDL_UpdateWindowSurface( window );

for (i = 1; i < n; i++) {
v = T[i];
j = i;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                play = 0;
                goto Exit;
                break;

            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                    case SDLK_q:
                    case SDLK_e:
                        play=0;
                        goto menu;
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(event.motion.x > 1435 && event.motion.x < 1671 && event.motion.y > 825 && event.motion.y < 918){
                        //Exit
                        Mix_PlayChannel(-1,click,0);
                        goto menu;
                    }
                }
        break;
        }
    }
       SDL_UpdateWindowSurface( window );

        while (j > 0 && T[j - 1] > v) {
            T[j] = T[j - 1];
            j--;
        }
        T[j] = v;
            // SDL_BlitSurface(exit_button, NULL, play_img, &play_exit);
            convertIntToCharWithSpaces(T,T_str,n,1);
            SDL_FreeSurface(play_numbers);
            play_numbers=TTF_RenderText_Solid(font2,T_str,color);
            SDL_BlitSurface(play_img,NULL,ScreenSurface,NULL);
            SDL_BlitSurface(play_numbers,NULL,ScreenSurface,&numbers_rect);
            SDL_UpdateWindowSurface( window );
            SDL_Delay(1000);
    }   
    exit_button = TTF_RenderText_Solid(font,"Exit", hover_color);
    SDL_UpdateWindowSurface( window );
    SDL_FreeSurface(exit_button);
    SDL_Delay(5000);
    goto menu;    
}   


///###############--------------------Settings-------------------###############
Settings:
    Settings = 1;
    while(Settings!=0){
        SDL_BlitSurface(setting_img, NULL, ScreenSurface, NULL);
        SDL_BlitSurface( set_button[0], NULL, ScreenSurface, &set_button_rect[0]);
        SDL_BlitSurface( set_button[1], NULL, ScreenSurface, &set_button_rect[1]);

        if(music_vol == 100)    SDL_BlitSurface( on, NULL, ScreenSurface, &on_off_rect[0]);
        if(chunk_vol == 100)    SDL_BlitSurface( on, NULL, ScreenSurface, &on_off_rect[1]);

        SDL_BlitSurface( set_exit, NULL, ScreenSurface, &set_exit_rect);

        SDL_UpdateWindowSurface(window);

            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        Settings = 0;
                        goto Exit;
                        break;

                    case SDL_KEYDOWN: 
                        switch (event.key.keysym.sym){
                            case SDLK_ESCAPE:
                            case SDLK_q:
                            case SDLK_e:
                                Settings=0;
                                goto Exit;
                                break;
                        }
                        
                    case SDL_MOUSEBUTTONUP:
                        if (event.button.button == SDL_BUTTON_LEFT){
                            if(event.motion.x > 1144 && event.motion.x < 1337 && event.motion.y > 616 && event.motion.y < 695){
                                //exit
                                Mix_PlayChannel(-1,click,0);
                                goto menu;
                            }

                    else if (event.button.x > 1122 && event.button.x < 1250 && event.button.y > 370 && event.button.y < 430) {
                        // Music button
                        Mix_PlayChannel(-1, click, 0);
                        if (music_vol == 100) {
                            Mix_HaltMusic(); // Halt the music if it's playing
                            SDL_BlitSurface( off, NULL, ScreenSurface, &on_off_rect[0]);
                            music_vol = 0;
                        } else {
                            Mix_PlayMusic(music, -1); // Play the music
                            Mix_VolumeMusic(MIX_MAX_VOLUME); // Set music volume to maximum
                            SDL_BlitSurface(on, NULL, ScreenSurface, &on_off_rect[0]);
                            music_vol = 100;
                        }
                    }
                    else if (event.button.x > 1122 && event.button.x < 1250 && event.button.y > 480 && event.button.y < 539) {
                        // Chunk button
                        Mix_PlayChannel(-1, click, 0);
                        if (chunk_vol == 100) {
                            Mix_VolumeChunk(click, 0); // Mute the chunk if its volume is at maximum
                            SDL_BlitSurface( off, NULL, ScreenSurface, &on_off_rect[1]);
                            chunk_vol = 0;
                        } else {
                            Mix_VolumeChunk(click, MIX_MAX_VOLUME); // Set chunk volume to maximum
                            chunk_vol = 100;
                        }
                    }
         
                }
                break;

                case SDL_MOUSEMOTION:
                    if(event.motion.x > 1144 && event.motion.x < 1337 && event.motion.y > 616 && event.motion.y < 695){
                        //exit
                        SDL_FreeSurface(set_exit);
                        set_exit=TTF_RenderText_Solid(font,"Exit", hover_color);
                    }
                 else {
                    SDL_FreeSurface(set_exit);
                    set_exit=TTF_RenderText_Solid(font,"Exit", textColor);
            }
            break;
        break;
        }
    }
    SDL_UpdateWindowSurface( window );
}


///###############--------------------EXIT-------------------###############
Exit:
    TTF_CloseFont(font);

    // Free SDL surfaces
    SDL_FreeSurface(background);
    SDL_FreeSurface(ScreenSurface);
    SDL_FreeSurface(menu_img);
    SDL_FreeSurface(menu_buttons[0]);
    SDL_FreeSurface(menu_buttons[1]);
    SDL_FreeSurface(play_img);
    SDL_FreeSurface(play_numbers);
    SDL_FreeSurface(exit_button);
    SDL_FreeSurface(choose_bk);
    SDL_FreeSurface(choose_button[0]);
    SDL_FreeSurface(choose_button[1]);
    SDL_FreeSurface(input_bk);
    SDL_FreeSurface(on);
    SDL_FreeSurface(off);
    SDL_FreeSurface(setting_img);
    SDL_FreeSurface(set_button[0]);
    SDL_FreeSurface(set_button[1]);
    SDL_FreeSurface(set_exit);
    SDL_DestroyWindow(window);

    // Free chunks and close SDL Mixer
    Mix_FreeChunk(click);
    Mix_CloseAudio();

    TTF_Quit();
    SDL_Quit();
    return 0;
}
