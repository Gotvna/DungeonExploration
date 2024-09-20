#pragma once

class Object
{
    friend class Map;

public:
    inline int getPosX() const { return m_posX; }
    inline int getPosY() const { return m_posY; }

private:
    int m_posX;
    int m_posY;
};
