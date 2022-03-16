#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./framework.h"

Framework::Framework(int width, int height, char* title, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    this->width  = width;
    this->height = height;
    this->r      = r;
    this->g      = g;
    this->b      = b;
    this->a      = a;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {       // Initializing SDL as Video
        printf("SDL could not initialize! SDL_Error %s\n", SDL_GetError());
    }
    else {
        IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
        TTF_Init();
        window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED_MASK,
                                  SDL_WINDOWPOS_CENTERED_MASK,
                                  width,
                                  height,
                                  SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }
}

int           Framework::getWidth()    {return width   ;}
int           Framework::getHheight()  {return height  ;}
SDL_Window*   Framework::getWindow()   {return window  ;}
SDL_Renderer* Framework::getRenderer() {return renderer;}

void Framework::updateScreen()
{
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

SDL_Texture* Framework::importTexture(char* texturePath, int *width, int *height) {
    SDL_Texture* texture {nullptr};
    SDL_Surface* surface = IMG_Load(texturePath);
    if(!surface) {
        printf("(ERR) Texture %s not found!\n", texturePath);
        surface = IMG_Load("assets/default.png");
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    //SDL_QueryTexture(texture, nullptr, nullptr, width, height);
    //const int SIZEK = (this->width * this->height) / (*width * *height) / 100;
    const int SIZEK = 1;
    *width  *= SIZEK;
    *height *= SIZEK;
    SDL_FreeSurface(surface);
    return texture;
}

// Destructor
Framework::~Framework(){
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
