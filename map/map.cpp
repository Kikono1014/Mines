#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../config.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "../field/field.h"
#include "./map.h"


SDL_Texture* textures[13];

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int random = mersenne() % max + min;
    return random;
}

Map::Map(int width,
         int height,
         int bombAmount,
         Framework &fw,
         char* texturePath) :
GameObject(fw,
           texturePath,
           SDL_Rect {(SCREEN_WIDTH - (width * 25 + 9)) / 2,
                     (SCREEN_HEIGHT - (height * 25 + 9)) /2,
                     width * 25 + 9, height * 25 + 9})
{
    this->width      = width;
    this->height     = height;
    this->bombAmount = bombAmount;
    Field **fields = new Field * [width];
    for (int i = 0; i < width; i++) {
        fields[i] = new Field [height];
    }
    this->fields = fields;
    
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            fields[i][j] = Field {fw,
                                  (char*)"assets/field.png",
                                  (char*)"assets/fieldPush.png",
                                  SDL_Rect {
                                            (i * 25) + hitbox.x + 4,
                                            (j * 25) + hitbox.y + 4,
                                            25,
                                            25
                                  }
                                };
        }
    }
    for (int i = 0; i < 10; ++i) {
        char path[] = "assets/field0.png";
        path[12] = '0' + i;
        textures[i] = fw.importTexture(path, &width, &height);
    }
    textures[10] = fw.importTexture((char*)"assets/fieldFlag.png", &width, &height);
    textures[11] = fw.importTexture((char*)"assets/field.png", &width, &height);
    textures[12] = fw.importTexture((char*)"assets/fieldClearedBomb.png", &width, &height);
}

void Map::changeMap (Framework &fw, int width, int height, int bombAmount)
{
    this->width      = width;
    this->height     = height;
    this->bombAmount = bombAmount;
    Field **fields = new Field * [width];
    for (int i = 0; i < width; i++) {
        fields[i] = new Field [height];
    }
    this->fields = fields;
    
    SDL_Rect hitbox {(SCREEN_WIDTH - (width * 25 + 9)) / 2,
                     (SCREEN_HEIGHT - (height * 25 + 9)) /2,
                     width * 25 + 9, height * 25 + 9};
    setHitbox(hitbox);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            fields[i][j] = Field {fw,
                                  (char*)"assets/field.png",
                                  (char*)"assets/fieldPush.png",
                                  SDL_Rect {
                                            (i * 25) + hitbox.x + 4,
                                            (j * 25) + hitbox.y + 4,
                                            25,
                                            25
                                  }
                                };
        }
    }
}

int Map::getWidth()      { return width;      }
int Map::getHeight()     { return height;     }
int Map::getBombAmount() { return bombAmount; }

void Map::setWidth     (int width)      { this->width      = width;      }
void Map::setHeight    (int height)     { this->height     = height;     }
void Map::setBombAmount(int bombAmount) { this->bombAmount = bombAmount; }

int Map::getAmountOfClosedField()
{
    int closedAmount = 0;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            closedAmount += (fields[i][j].getIsClosed()) ? 1 : 0;
        }
    }
    return closedAmount;
}

int Map::getAmountOfBombAround(int x, int y)
{
    int bombAmount = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (x + i < width  && x + i >= 0 &&
                y + j < height && y + j >= 0)
            {
                bombAmount += (fields[x+i][y+j].getType() == 9) ? 1 : 0;
            }
        }
    }
    return bombAmount;
}

int Map::getAmountOfFlagAround(int x, int y)
{
    int flagAmount = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (x + i < width  && x + i >= 0 &&
                y + j < height && y + j >= 0)
            {
                flagAmount += (fields[x+i][y+j].getIsFlag()) ? 1 : 0;
            }
        }
    }
    return flagAmount;
}

void Map::checkField(Framework &fw, int x, int y)
{
    if (fields[x][y].getType() == 9) {
        openFields(fw);
    }
    if (fields[x][y].getType() == 0) {
        openField(fw, x, y);
        openAroundFields(fw, x ,y);
    }
    else {
        openField(fw, x, y);
    }
}

void Map::openField(Framework &fw, int x, int y)
{
    fields[x][y].setIsClosed(0);
    fields[x][y].push(fw);
}

void Map::openAroundFields(Framework &fw, int x, int y)
{
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (x + i < width  && x + i >= 0 &&
                y + j < height && y + j >= 0 && 
                fields[x+i][y+j].getIsClosed() && 
                !(fields[x+i][y+j].getIsFlag()))
            {
                checkField(fw, x+i, y+j);
            }
        }
    }
}

void Map::openFields(Framework &fw)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            openField(fw, i, j);
        }
    }
}

void Map::closeFields(Framework &fw)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            fields[i][j].unPush(fw);
        }
    }
}

void Map::setVoidToAroundFields(Framework &fw, int x, int y)
{
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            if (x + i < width  && x + i >= 0 &&
                y + j < height && y + j >= 0)
            {                
                fields[x+i][y+j].setType(0);
                fields[x+i][y+j].setPushTexture(textures[0]);
            }
        }
    }
}

void Map::setBombs(Framework &fw)
{
    int curBombAmount = 0;
    int bombPercents = 0;
    while (bombAmount != curBombAmount) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                bombPercents = (bombAmount * 100) / (width * height);
                if (random(0, 100) < bombPercents &&
                    bombAmount > curBombAmount &&
                    fields[i][j].getType() != 0 &&
                    fields[i][j].getType() != 9)
                {
                    curBombAmount++;
                    fields[i][j].setType(9);
                    fields[i][j].setPushTexture(textures[9]);
                }
            }
        }
    }
}

void Map::setNumbers(Framework &fw)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (fields[i][j].getType() != 9) {
                fields[i][j].setType(getAmountOfBombAround(i, j));
                fields[i][j].setPushTexture(textures[fields[i][j].getType()]);
            }
        }
    }
}

void Map::clear(Framework &fw)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            fields[i][j].setType(42);
            fields[i][j].setIsFlag(0);
            fields[i][j].setIsClosed(1);
            fields[i][j].setPushTexture(textures[0]);
            fields[i][j].setUnPushTexture(textures[11]);
        }
    }
}


void Map::pressField(Framework &fw, int x, int y)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (fields[i][j].isTouchHitbox(x, y) && !(fields[i][j].getIsFlag())) {
                if (fields[i][j].getType() == 42) {
                    fields[i][j].setType(0);
                    fields[i][j].setPushTexture(textures[0]);
                    setVoidToAroundFields(fw, i, j);
                    generate(fw, i, j);
                }
                if (fields[i][j].getIsClosed()) {
                    checkField(fw, i, j);
                }
                else if (!(fields[i][j].getIsClosed()) &&
                         getAmountOfFlagAround(i, j) == fields[i][j].getType())
                {
                    openAroundFields(fw, i, j);
                }
            }
        }
    }
}

void Map::setFlag(Framework &fw, int x, int y)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (fields[i][j].isTouchHitbox(x, y) && fields[i][j].getIsClosed()) {
                    fields[i][j].setUnPushTexture(textures[10 + fields[i][j].getIsFlag()]);
                    fields[i][j].unPush(fw);
                    fields[i][j].setIsFlag(!(fields[i][j].getIsFlag()));
            }
        }
    }
}

void Map::render(Framework &fw)
{
    SDL_RenderCopy(fw.getRenderer(), texture, nullptr, &hitbox);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            SDL_RenderCopy(fw.getRenderer(), fields[i][j].texture, nullptr, &(fields[i][j].hitbox));
        }
    }
}

void Map::generate(Framework &fw, int x, int y)
{
    setBombs(fw);
    setNumbers(fw);
}


void Map::restart(Framework &fw)
{
    clear(fw);
    closeFields(fw);
}

void Map::changeBombTextureToCleared(Framework &fw)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (fields[i][j].getType() == 9) {
                fields[i][j].setPushTexture(textures[12]);
                openField(fw, i, j);
            }
        }
    }
}

void Map::win(Framework &fw)
{   
    changeBombTextureToCleared(fw);
    openFields(fw);
}

int Map::getAmountOfBombs()
{
    int bombsAmount = 0;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            bombsAmount += (fields[i][j].getType() == 9) ? 1 : 0;
        }
    }
    return bombsAmount;
}

void Map::checkWin(Framework &fw)
{
    if (getAmountOfClosedField() == bombAmount) {
        win(fw);
    }
}
