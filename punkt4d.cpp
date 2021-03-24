#include "punkt4d.h"

Punkt4D::Punkt4D() {}
Punkt4D::Punkt4D(float xx, float yy, float zz, float ww)
{
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}
void Punkt4D::setX(float xx)
{
    x = xx;
}
void Punkt4D::setY(float yy)
{
    y = yy;
}
void Punkt4D::setZ(float zz)
{
    z = zz;
}
void Punkt4D::setW(float ww)
{
    w = ww;
}

float Punkt4D::X()
{
    return x;
}
float Punkt4D::Y()
{
    return y;
}
float Punkt4D::Z()
{
    return z;
}
float Punkt4D::W()
{
    return w;
}
