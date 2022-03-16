#ifndef BUTTON_H
#define BUTTON_H

#include "../gameObject/gameObject.h"

class Button : public GameObject
{
private:
    SDL_Texture *unPushTexture {nullptr};
    SDL_Texture *pushTexture {nullptr};
public:
    Button();
    Button(Framework &fw,
           char* texturePath,
           char* pushTexturePath,
           SDL_Rect hitbox);

    void setUnPushTextureFromPath(Framework &fw, char* texturePath);
    void setPushTextureFromPath  (Framework &fw, char* pushTexturePath);

    void setUnPushTexture(SDL_Texture *unPushTexture);
    void setPushTexture  (SDL_Texture *pushTexture);

    void push  (Framework &fw);
    void unPush(Framework &fw);
};

#endif
