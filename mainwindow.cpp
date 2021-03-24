#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

//w konstruktorze tworzymy nowego canvasa , ustwaiamy teskture i wylaczamy animacje
//i ustawiamy by przycisk byl wlaczony
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    canvas = new Canvas(this, ui -> frame -> x(), 20, ui -> frame -> width(), ui -> frame -> height());
    //wybieramy początkową teksture
    texture = new QImage("Sciezka bezposrednia do pliku Texture.jpg");

    on_reset_clicked();
    on_rotacjaX_valueChanged(0);
}

//dekonstruktor
MainWindow::~MainWindow()
{
    delete texture;
    delete canvas;
    delete ui;
}

//paintevent wywoluje draw z canvasa
void MainWindow::paintEvent(QPaintEvent*)
{
    canvas -> draw();
}

//draw wywoluje drawcube z canvasa
void MainWindow::draw()
{
    canvas -> reset();
    canvas -> drawCube(&cube, pos, scale, rotation);
    update();
}

QImage* MainWindow::getTexture() const
{
    return texture;
}

float MainWindow::getD() const
{
    return d;
}

void MainWindow::on_rotacjaX_valueChanged(int value)
{
    /*potrzebujemy do obrotu*/
    rotation.setX(value / 180.0f * M_PI);
    rotation.setX(static_cast<int>(rotation.X() * 100.0f));
    rotation.setX(rotation.X() / 100.0f);
    draw();
}

void MainWindow::on_rotacjaY_valueChanged(int value)
{
    rotation.setY(value / 180.0f * M_PI);
    rotation.setY(static_cast<int>(rotation.Y() * 100.0f));
    rotation.setY(rotation.Y() / 100.0f);
    draw();
}

void MainWindow::on_rotacjaZ_valueChanged(int value)
{
    rotation.setZ(value / 180.0f * M_PI);
    rotation.setZ(static_cast<int>(rotation.Z() * 100.0f));
    rotation.setZ(rotation.Z() / 100.0f);
    draw();
}

void MainWindow::on_hideWall_toggled(bool checked)
{
    ui -> texture -> setEnabled(checked);
    draw();
}

void MainWindow::on_texture_toggled(bool checked)
{
    draw();
}

void MainWindow::on_reset_clicked()
{
    pos.setX(canvas -> getWidth() / 2.0f - cube.getSize() / 2.0f);
    pos.setY(canvas -> getHeight() / 2.0f - cube.getSize() / 2.0f);
    pos.setZ(10.0f);

    scale.setX(1.0f);
    scale.setY(1.0f);
    scale.setZ(1.0f);

    rotation.setX(0.0f);
    rotation.setY(0.0f);
    rotation.setZ(0.0f);

    /*tu jest zmienna d!*/
    d = 1000.0f;

    //ui -> sldD -> setValue(d);

    cube.reset();

    ui -> rotacjaX -> setValue(rotation.X());
    ui -> rotacjaY -> setValue(rotation.Y());
    ui -> rotacjaZ -> setValue(rotation.Z());

    ui -> hideWall -> setChecked(false);
    ui -> texture -> setChecked(false);
}

bool MainWindow::isHideWallsModeOn() const
{
    return ui -> hideWall -> isChecked();
}

bool MainWindow::isTextureModeOn() const
{
    return ui -> texture -> isChecked();
}
