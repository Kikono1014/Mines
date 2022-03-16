#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>	
#include <SDL2/SDL_ttf.h>
#include "./framework/framework.h"
#include "./config.h"

Framework fw(SCREEN_WIDTH, SCREEN_HEIGHT, (char*)"Mines", 215, 215, 215);
SDL_Event event;

#include "./button/button.h"
#include "./field/field.h"
#include "./map/map.h"

Map map{32,
        16,
        100,
        fw,
        (char*)"assets/map.png"
    };
void keyProcessing();
void buttonProcessing();
void showLocation(char* location);

int main(int argc, char **argv) {
    while(!(event.type == SDL_QUIT)){
        if (SDL_PollEvent(&event)) {
            keyProcessing();
            buttonProcessing();
        }
        map.checkWin(fw);
        map.render(fw);

        fw.updateScreen();
    }
}

void keyProcessing()
{
    if (event.type == SDL_KEYDOWN){
        //std::cout << event.key.keysym.sym << std::endl;
        switch (event.key.keysym.sym)
        {
            case SDLK_r:
                map.restart(fw);
                break;
            case SDLK_1:
                map.changeMap(fw, 8, 8, 10);
                break;
            case SDLK_2:
                map.changeMap(fw, 8, 8, 20);
                break;
            case SDLK_3:
                map.changeMap(fw, 16, 16, 30);
                break;
            case SDLK_4:
                map.changeMap(fw, 16, 16, 50);
                break;
            case SDLK_5:
                map.changeMap(fw, 24, 16, 50);
                break;
            case SDLK_6:
                map.changeMap(fw, 24, 16, 70);
                break;
            case SDLK_7:
                map.changeMap(fw, 32, 16, 70);
                break;
            case SDLK_8:
                map.changeMap(fw, 32, 16, 100);
                break;
            case SDLK_9:
                map.changeMap(fw, 32, 16, 200);
                break;
        }
    }
}

void buttonProcessing() 
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:
                map.pressField(fw, event.button.x, event.button.y);
                break;
            case SDL_BUTTON_RIGHT:
                map.setFlag(fw, event.button.x, event.button.y);
                break;
        }
    }
}