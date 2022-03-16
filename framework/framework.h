#ifndef FRAMEWORK_H
#define FRAMEWORK_H

class Framework
{
private:
    int           width;              // Width of the window
    int           height;             // Height of the window
    Uint8         r;
    Uint8         g;
    Uint8         b;
    Uint8         a;
    SDL_Window   *window   {nullptr}; // Pointer for the window
    SDL_Renderer *renderer {nullptr}; // Pointer for the renderer
public:
    Framework(int width, int height, char* title, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 1);

    int           getWidth();
    int           getHheight();
    SDL_Window*   getWindow();
    SDL_Renderer* getRenderer();

    void updateScreen();
    SDL_Texture* importTexture(char* texturePath, int *width, int *height);

    ~Framework();
};
#endif
