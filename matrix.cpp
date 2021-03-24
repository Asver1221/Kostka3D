#include "matrix.h"

//  0 0 0 0
//  0 0 0 0
//  0 0 0 0
//  0 0 0 1
Matrix::Matrix(int wiersze, int kolumny) : _width(kolumny), _height(wiersze)
{
    for (int i = 0; i < _width * _height; i++) {
        m[i] = 0;
    }
    m[_width * _height -1] = 1;
}

//  v0 v1 v2 v3
Matrix::Matrix(double v0, double v1, double v2, double v3)
{
    m[0] = v0;
    m[1] = v1;
    m[2] = v2;
    m[3] = v3;
    _width = 1;
    _height = 4;
}

int Matrix::width()
{
    return _width;
}

int Matrix::height()
{
    return _height;
}


double Matrix::get(int w, int k)
{
    return m[w * _width + k];
}

void Matrix::set(int w, int k, double value)
{
    m[w * _width + k] = value;
}
