#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../config.h"
#include "../framework/framework.h"
#include "../button/button.h"
#include "./field.h"

Field::Field() :
Button()
{
    this->type = 42;
    this->isClosed = 1;
    this->isFlag = 0;
}

Field::Field(Framework &fw,
             char* texturePath,
             char* pushTexturePath,
             SDL_Rect hitbox) :
Button(fw,
       texturePath,
       pushTexturePath,
       hitbox)
{
    this->type = 42;
    this->isClosed = 1;
    this->isFlag = 0;
}

int  Field::getType()     { return type;     }
bool Field::getIsClosed() { return isClosed; }
bool Field::getIsFlag()   { return isFlag;   }

void Field::setType    (int  type)     { this->type     = type;     }
void Field::setIsClosed(bool isClosed) { this->isClosed = isClosed; }
void Field::setIsFlag  (bool isFlag)   { this->isFlag   = isFlag;   }