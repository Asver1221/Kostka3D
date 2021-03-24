#include "punkt3d.h"

Punkt3D::Punkt3D() {}
Punkt3D::Punkt3D(float xx, float yy, float zz)
{
    x = xx;
    y = yy;
    z = zz;
}
void Punkt3D::setX(float xx)
{
    x = xx;
}
void Punkt3D::setY(float yy)
{
    y = yy;
}
void Punkt3D::setZ(float zz)
{
    z = zz;
}

float Punkt3D::X()
{
    return x;
}
float Punkt3D::Y()
{
    return y;
}
float Punkt3D::Z()
{
    return z;
}
