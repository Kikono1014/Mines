#ifndef FIELD_H
#define FIELD_H

#include "../button/button.h"

class Field : public Button
{
private:
    int  type;
    bool isClosed;
    bool isFlag;
public:
    Field();
    Field(Framework &fw,
          char* texturePath,
          char* pushTexturePath,
          SDL_Rect hitbox);

    int  getType();
    bool getIsClosed();
    bool getIsFlag();

    void setType    (int  type);
    void setIsClosed(bool isClosed);
    void setIsFlag  (bool isFlag);
};

#endif
