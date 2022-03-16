#ifndef GAMEOBJ_H
#define GAMEOBJ_H

class GameObject
{
public:
    SDL_Texture *texture {nullptr};
    SDL_Rect hitbox;

    GameObject();
    GameObject(Framework &fw,
               char* texturePath,
               SDL_Rect hitbox);

    SDL_Texture* getTexture();
    SDL_Rect*    getHitbox();
    int          getWidth();
    int          getHeight();
    int          getX();
    int          getY();

    void setTexture        (SDL_Texture* texture);
    void setTextureFromPath(Framework &fw, char* texturePath);
    void setHitbox         (SDL_Rect hitbox);
    void setWidth          (int w);
    void setHeight         (int h);
    void setX              (int x);
    void setY              (int y);

    bool isTouchHitbox(int x, int y);
};

#endif
