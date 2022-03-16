#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../config.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "./button.h"

Button::Button() :
GameObject()
{
    //setUnPushTexture(fw, "assets/default.png");
    //setPushTexture  (fw, "assets/default.png");
}

Button::Button(Framework &fw,
               char* texturePath,
               char* pushTexturePath,
               SDL_Rect hitbox) :
GameObject(fw,
           texturePath,
           hitbox)
{
    setUnPushTextureFromPath(fw, texturePath);
    setPushTextureFromPath  (fw, pushTexturePath);
}


void Button::setUnPushTexture(SDL_Texture *unPushTexture)
{
    this->unPushTexture = unPushTexture;

}
void Button::setPushTexture  (SDL_Texture *pushTexture)
{
    this->pushTexture = pushTexture;
}

void Button::setUnPushTextureFromPath(Framework &fw, char* texturePath)     
{
    this->unPushTexture = fw.importTexture(texturePath, &hitbox.w, &hitbox.h);
}

void Button::setPushTextureFromPath(Framework &fw, char* texturePath)
{
    this->pushTexture = fw.importTexture(texturePath, &hitbox.w, &hitbox.h);    
}

void Button::push(Framework &fw)
{
    texture = pushTexture;
}

void Button::unPush(Framework &fw)
{
    texture = unPushTexture;
}
