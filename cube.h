#ifndef CUBE_H
#define CUBE_H

#include <QVector4D>
#include <punkt4d.h>

class Cube
{
    public:
        Cube();
        void reset();

        Punkt4D* getPF(int i)
        {
            return &pf[i];
        }

        Punkt4D* getPB(int i)
        {
            return &pb[i];
        }

        float getSize() const
        {
            return size;
        }

    private:
        Punkt4D pf[4];
        Punkt4D pb[4];
        float size;
};

#endif // CUBE_H
