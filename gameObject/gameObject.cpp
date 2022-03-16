#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../config.h"
#include "../framework/framework.h"
#include "./gameObject.h"

GameObject::GameObject()
{
    this->hitbox  = SDL_Rect{0, 0, 0, 0};
}

GameObject::GameObject(Framework &fw,
                       char* texturePath,
                       SDL_Rect hitbox)
{
    this->hitbox  = hitbox;
    this->texture = fw.importTexture(texturePath, &hitbox.w, &hitbox.h);
}

SDL_Texture* GameObject::getTexture() { return texture;  }
void GameObject::setTextureFromPath(Framework &fw, char* texturePath)
{
    this->texture = fw.importTexture(texturePath, &hitbox.w, &hitbox.h);
}
SDL_Rect*    GameObject::getHitbox()  { return(&hitbox); }
int          GameObject::getWidth()   { return hitbox.w; }
int          GameObject::getHeight()  { return hitbox.h; }
int          GameObject::getX()       { return hitbox.x; }
int          GameObject::getY()       { return hitbox.y; }

void GameObject::setTexture(SDL_Texture* texture) { this->texture = texture; }
void GameObject::setHitbox (SDL_Rect hitbox)      { this->hitbox  = hitbox;  }
void GameObject::setWidth  (int w)                { hitbox.w = w; }
void GameObject::setHeight (int h)                { hitbox.h = h; }
void GameObject::setX      (int x)                { hitbox.x = x; }
void GameObject::setY      (int y)                { hitbox.y = y; }


bool GameObject::isTouchHitbox(int x, int y) {
    return ((x > hitbox.x) && (x < hitbox.x + hitbox.h)) &&
           ((y > hitbox.y) && (y < hitbox.y + hitbox.h));
}
