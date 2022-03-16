#ifndef MAP_H
#define MAP_H

#include "../gameObject/gameObject.h"

class Map : public GameObject
{
private:
    int width;
    int height;
    int bombAmount;
    Field **fields;

    int  getAmountOfClosedField    ();
    int  getAmountOfBombs          ();
    int  getAmountOfBombAround     (int x, int y);
    int  getAmountOfFlagAround     (int x, int y);
    void setVoidToAroundFields     (Framework &fw, int x, int y);
    void setBombs                  (Framework &fw);
    void setNumbers                (Framework &fw);
    void clear                     (Framework &fw);
    void win                       (Framework &fw);
    void changeBombTextureToCleared(Framework &fw);
    void checkField                (Framework &fw, int x, int y);
    void openField                 (Framework &fw, int x, int y);
    void openAroundFields          (Framework &fw, int x, int y);
    void openFields                (Framework &fw);
    void closeFields               (Framework &fw);
public:

    Map(int width,
        int height,
        int bombAmount,
        Framework &fw,
        char* texturePath);

    int getWidth();
    int getHeight();  
    int getBombAmount();

    void setWidth     (int width);
    void setHeight    (int height);     
    void setBombAmount(int bombAmount);

    void changeMap (Framework &fw, int width, int height, int bombAmount);
    void generate  (Framework &fw, int x, int y);
    void restart   (Framework &fw);
    void checkWin  (Framework &fw);
    void setFlag   (Framework &fw, int x, int y);
    void pressField(Framework &fw, int x, int y);
    void render    (Framework &fw);

};

#endif
