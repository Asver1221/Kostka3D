#ifndef PUNKT2D_H
#define PUNKT2D_H

class Punkt2D
{
public:
    float x, y;

    Punkt2D();
    Punkt2D(float xx, float yy);

    void setX(float xx);
    void setY(float yy);

    float X();
    float Y();

};

#endif // PUNKT2D_H
