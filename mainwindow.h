#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvas.h"
#include "cube.h"
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage* texture;
    float d;

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void draw();

    bool isHideWallsModeOn() const;
    bool isTextureModeOn() const;
    QImage* getTexture() const;

    float getD() const;


private slots:

    void on_rotacjaX_valueChanged(int);
    void on_rotacjaY_valueChanged(int);
    void on_rotacjaZ_valueChanged(int);
    void on_hideWall_toggled(bool);
    void on_texture_toggled(bool);
    void on_reset_clicked();

private:
    Ui::MainWindow* ui;
    Canvas* canvas;


    int vx = 1;
    int vy = 1;
    int vz = 1;

    Punkt3D pos;
    Punkt3D scale;
    Punkt3D rotation;

    Cube cube;
};

#endif // MAINWINDOW_H
