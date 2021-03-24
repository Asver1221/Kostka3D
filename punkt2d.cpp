#include "punkt2d.h"

Punkt2D::Punkt2D() {}
Punkt2D::Punkt2D(float xx, float yy)
{
    x = xx;
    y = yy;
}
void Punkt2D::setX(float xx)
{
    x = xx;
}
void Punkt2D::setY(float yy)
{
    y = yy;
}

float Punkt2D::X()
{
    return x;
}
float Punkt2D::Y()
{
    return y;
}

