#ifndef PUNKT4D_H
#define PUNKT4D_H

class Punkt4D
{
public:
    float x, y, z, w;

    Punkt4D();
    Punkt4D(float xx, float yy, float zz, float ww);

    void setX(float xx);
    void setY(float yy);
    void setZ(float zz);
    void setW(float ww);

    float X();
    float Y();
    float Z();
    float W();

private:

};

#endif // PUNKT4D_H
