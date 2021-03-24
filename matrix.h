#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix(int wiersze, int kolumny);
    Matrix(double v0, double v1, double v2, double v3);

    int width();
    int height();

    double get(int w, int k);
    void set(int w, int k, double value);

private:
    int _width, _height;
    double m[16];

};

#endif // MATRIX_H



