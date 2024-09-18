#pragma once

class Object
{
    friend class Map;

public:
    inline int getPosX() const { return posX; }
    inline int getPosY() const { return posY; }

private:
    int posX;
    int posY;
};
