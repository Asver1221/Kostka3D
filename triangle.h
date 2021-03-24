#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <punkt2d.h>

class Triangle
{
public:
    float wektorTri1[1];
    float wektorTri2[1];
    float wektorTri[1];

    Triangle(Punkt2D v1, Punkt2D v2, Punkt2D v3);

    Punkt2D getVertex(int i) const
    {
        return vertices[i];
    }

    void setVertex(int i, const Punkt2D& v)
    {
        vertices[i] = v;
    }

private:
    Punkt2D vertices[3];
};

#endif // TRIANGLE_H
