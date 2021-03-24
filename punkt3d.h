#ifndef PUNKT3D_H
#define PUNKT3D_H

class Punkt3D
{
public:
    float x, y, z;

    Punkt3D();
    Punkt3D(float xx, float yy, float zz);

    void setX(float xx);
    void setY(float yy);
    void setZ(float zz);

    float X();
    float Y();
    float Z();
};

#endif // PUNKT3D_H
