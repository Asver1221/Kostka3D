#include "cube.h"
Cube::Cube() : size(256.0f) {}

//reset ustawia na domysne wartosci te wszystkie wierzcholki by byl na domyslnej pozycji jak nacisniemy reset
void Cube::reset()
{
    pf[0] = Punkt4D(0.0f, 0.0f, 0.0f, 1.0f);
    pf[1] = Punkt4D(size, 0.0f, 0.0f, 1.0f);
    pf[2] = Punkt4D(size, size, 0.0f, 1.0f);
    pf[3] = Punkt4D(0.0f, size, 0.0f, 1.0f);

    pb[0] = Punkt4D(0.0f, 0.0f, size, 1.0f);
    pb[1] = Punkt4D(size, 0.0f, size, 1.0f);
    pb[2] = Punkt4D(size, size, size, 1.0f);
    pb[3] = Punkt4D(0.0f, size, size, 1.0f);
}
