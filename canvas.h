#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>
#include <QImage>
#include "cube.h"
#include "triangle.h"
#include "punkt4d.h"
#include "punkt3d.h"
#include "matrix.h"

class MainWindow;

class Canvas:public QObject
{
public:
    int dim = 4;
    int sinx, cosx;
    int siny, cosy;
    int sinz, cosz;
    int transx, transy, transz = 1;
    int transox, transoy, transoz = 1;
    int rotationx, rotationy, rotationz = 1;
    int scalex, scaley, scalez = 1;
    Punkt4D pf[4];
    Punkt4D pb[4];
    float macierz[4][4];

    Canvas(MainWindow* mainWindow, int x, int y, int width, int height);
    ~Canvas();

    int getWidth();
    int getHeight();

    void draw();
    void rysowaniePixela(int x, int y, int r, int g, int b);
    void rysowanieLinii(Punkt2D p1, Punkt2D p2);
    void rysowanieLinii(Punkt4D p1, Punkt4D p2);

    void drawCube(Cube* cube, Punkt3D pos, Punkt3D scale, Punkt3D rotation);

    void drawTexture(QImage* image, Triangle dst, Triangle src);
    void reset();
    Punkt2D to2D(Punkt3D Punkt3D);
    Punkt2D to2D(Punkt4D vector4D);
    bool isWallVisible(Punkt3D v0, Punkt3D v1, Punkt3D v2);
    bool isWallVisible(Punkt4D v0, Punkt4D v1, Punkt4D v2);


private:
    MainWindow* mainWindow;
    QImage* canvasImg;
    int x;
    int y;
};

#endif // CANVAS_H
