#include "canvas.h"
#include "mainwindow.h"
#include <cmath>

//konstruktor dziedziczący po konstruktorze mainWindow
//posiada wszystkie jego dane + to co niżej
Canvas::Canvas(MainWindow* uiMainWindow, int x, int y, int width, int height)
    : mainWindow(uiMainWindow), x(x), y(y)
{
    // tworzymy nowy QImage
    canvasImg = new QImage(width, height, QImage::Format_RGB32);
    reset();
 }

//dekonstruktor
Canvas::~Canvas()
{
    delete canvasImg;
}

int Canvas::getWidth() {
    return canvasImg -> width();
}

int Canvas::getHeight() {
    return canvasImg -> height();
}

//wybieramy tutaj tło na którym będziemy rysować
void Canvas::draw()
{
    QPainter painter(mainWindow);
    painter.drawImage(x, y, *canvasImg);
}

void Canvas::rysowaniePixela(int x, int y, int r, int g, int b) {
    unsigned char *ptr;
    ptr = canvasImg->bits();
    if(x >= 0 && y >=0 && x < getWidth() && y < getHeight()) {
        ptr[getWidth() * 4 * y + 4 * x] = b;
        ptr[getWidth() * 4 * y + 4 * x + 1] = g;
        ptr[getWidth() * 4 * y + 4 * x + 2] = r;
    }
}

void Canvas::rysowanieLinii(Punkt2D pkt1, Punkt2D pkt2) {

    int x1, y1, x2, y2;
    x1 = (int)pkt1.X();
    y1 = (int)pkt1.Y();
    x2 = (int)pkt2.X();
    y2 = (int)pkt2.Y();

    double a, b;
    int container;
    int i;

    if(abs(x1 - x2) > abs(y1 - y2)){

        if(x1 > x2){
            container = x1;
            x1 = x2;
            x2 = container;
            container = y1;
            y1 = y2;
            y2 = container;
        }

        a = (y2 - y1) / static_cast<double>(x2 - x1);
        b = y1 - a * x1;

        for(i = x1; i <= x2; i++) {
            container = static_cast<int>(a * i + b) ;
            rysowaniePixela(i,container, 0 ,0 ,0);
        }
    } else {

        if(y1 > y2){
            container = x1;
            x1 = x2;
            x2 = container;
            container = y1;
            y1 = y2;
            y2 = container;

        }
        a = (x2 - x1) / static_cast<double>(y2 - y1);
        b = x1 - a * y1;

        for(i = y1; i <= y2; i++){
            container = static_cast<int>(a * i + b);
            rysowaniePixela(container,i, 0 ,0 ,0);
        }
    }
}

void Canvas::rysowanieLinii(Punkt4D pkt1, Punkt4D pkt2) {
    rysowanieLinii(to2D(pkt1), to2D(pkt2));
}

//funcja multiply do mnożenia macierzy przez wektor
Punkt4D matrixMultiply(Matrix matrix, Punkt4D punkt) {
    //setX - funkcja klasy Punkt4D, ustawia koordynatu punktu
    Punkt4D punkt4D;
    punkt4D.setX(matrix.get(0, 0) * punkt.X() + matrix.get(0, 1) * punkt.Y() + matrix.get(0, 2) * punkt.Z() + matrix.get(0, 3) * punkt.W());
    punkt4D.setY(matrix.get(1, 0) * punkt.X() + matrix.get(1, 1) * punkt.Y() + matrix.get(1, 2) * punkt.Z() + matrix.get(1, 3) * punkt.W());
    punkt4D.setZ(matrix.get(2, 0) * punkt.X() + matrix.get(2, 1) * punkt.Y() + matrix.get(2, 2) * punkt.Z() + matrix.get(2, 3) * punkt.W());
    punkt4D.setW(matrix.get(3, 0) * punkt.X() + matrix.get(3, 1) * punkt.Y() + matrix.get(3, 2) * punkt.Z() + matrix.get(3, 3) * punkt.W());

    return punkt4D;
}


//mnożenie przez ostatnią macierz [x y z 1] - slajdy
Punkt4D matrixMultiply(Matrix matrix, Punkt4D* punkt) {
    return matrixMultiply(matrix, *punkt);
}


//funkcja służąca do rysowania kostki (bierzemy wektory przeksztalcen , oraz sinusy i cosinusy to wszystko bylo na slajdach)
void Canvas::drawCube(Cube* cube, Punkt3D pozycja, Punkt3D rozmiar, Punkt3D rotacja) {
    //z pomocą wartości obrotu wyliczamy funkcje trygonometryczne(slajdy)
    float sinx = sinf(rotacja.X());
    float siny = sinf(rotacja.Y());
    float sinz = sinf(rotacja.Z());
    float cosx = cosf(rotacja.X());
    float cosy = cosf(rotacja.Y());
    float cosz = cosf(rotacja.Z());

    // wyliczamy środek kostki
    //potrzebne do skalowania
    float originX = 256.0f / 2.0f * rozmiar.X();
    float originY = 256.0f / 2.0f * rozmiar.Y();
    float originZ = 256.0f / 2.0f * rozmiar.Z();

    //korzystamy z macierzy 4x4 ze względu na współrzędne jednorodne.
    //Reprezentujemy n-wymiarowy punkt za pomocą n+1 współrzędnych


    // Przesunięcie(translacja)

    // 1   0   0   tx
    // 0   1   0   ty
    // 0   0   1   tz
    // 0   0   0   1

    Matrix translacja(4, 4);
    translacja.set(0, 0, 1);
    translacja.set(0, 3, pozycja.X());
    translacja.set(1, 1, 1);
    translacja.set(1, 3, pozycja.Y());
    translacja.set(2, 2, 1);
    translacja.set(2, 3, pozycja.Z());

    //translacja przez wektor originX, originY, originZ aby środek obrotu wrócił na swoje pierwotne miejsce
    Matrix translacjaSrodek(4, 4);
    translacjaSrodek.set(0, 0, 1);
    translacjaSrodek.set(0, 3, originX);
    translacjaSrodek.set(1, 1, 1);
    translacjaSrodek.set(1, 3, originY);
    translacjaSrodek.set(2, 2, 1);
    translacjaSrodek.set(2, 3, originZ);


    //i na koniec przesuwamy o wektor -originX, -originY, -originZ po czym środek obrotu znajduje się na początku układu współrzędnych(film YT o przekształceniach)
    Matrix translacjaWspolrzedne(4, 4);
    translacjaWspolrzedne.set(0, 0, 1);
    translacjaWspolrzedne.set(0, 3, -originX);
    translacjaWspolrzedne.set(1, 1, 1);
    translacjaWspolrzedne.set(1, 3, -originY);
    translacjaWspolrzedne.set(2, 2, 1);
    translacjaWspolrzedne.set(2, 3, -originZ);

    //Skalowanie(względem punktu 0,0,0)

    // sx   0   0   0
    // 0    sy  0   0
    // 0    0   sz  0
    // 0    0   0   1

    Matrix skalowanie(4, 4);
    skalowanie.set(0, 0, rozmiar.X());
    skalowanie.set(1, 1, rozmiar.Y());
    skalowanie.set(2, 2, rozmiar.Z());




    //Obrót względem osi OX

    // 1    0     0      0
    // 0    cosa  -sina  0
    // 0    sina  cosa   0
    // 0    0     0      1

    Matrix obrotOX(4, 4);
    obrotOX.set(0, 0, 1);
    obrotOX.set(1, 1, cosx);
    obrotOX.set(1, 2, -sinx);
    obrotOX.set(2, 1, sinx);
    obrotOX.set(2, 2, cosx);


    //Obrot wzgledem osi OY

    // cosa    0     sina    0
    // 0       1     0       0
    // -sina   0     cosa    0
    // 0       0     0       1

    Matrix obrotOY(4, 4);
    obrotOY.set(0, 0, cosy);
    obrotOY.set(0, 2, siny);
    obrotOY.set(1, 1, 1);
    obrotOY.set(2, 0, -siny);
    obrotOY.set(2, 2, cosy);

    //obrot wzgledem osi OZ

    // cosa    -sina   0       0
    // sina    cosa    0       0
    // 0       0       1       0
    // 0       0       0       1

    Matrix obrotOZ(4, 4);
    obrotOZ.set(0, 0, cosz);
    obrotOZ.set(0, 1, -sinz);
    obrotOZ.set(1, 0, sinz);
    obrotOZ.set(1, 1, cosz);
    obrotOZ.set(2, 2, 1);


    //mnożenie macierzy przez wektor
    for (int i = 0; i < dim; i++) {
        //pfront to wierzchołki przednie te co widzimy bliżej
        //pb to wierzchołki tylne

        //skalowanie
        pf[i] = matrixMultiply(skalowanie, cube -> getPF(i));
        pb[i] = matrixMultiply(skalowanie, cube -> getPB(i));

        //translacja przez wektor -originX, -originY, -originZ
        pf[i] = matrixMultiply(translacjaWspolrzedne, pf[i]);
        pb[i] = matrixMultiply(translacjaWspolrzedne, pb[i]);

        //obrót względem osi OX
        pf[i] = matrixMultiply(obrotOX, pf[i]);
        pb[i] = matrixMultiply(obrotOX, pb[i]);

        //obrót względem osi OY
        pf[i] = matrixMultiply(obrotOY, pf[i]);
        pb[i] = matrixMultiply(obrotOY, pb[i]);

        //obrót względem osi OZ
        pf[i] = matrixMultiply(obrotOZ, pf[i]);
        pb[i] = matrixMultiply(obrotOZ, pb[i]);

        //translacja przez wektor originX, originY, originZ
        pf[i] = matrixMultiply(translacjaSrodek, pf[i]);
        pb[i] = matrixMultiply(translacjaSrodek, pb[i]);

        //przesuniecie wzgledem (0,0,0)
        pf[i] = matrixMultiply(translacja, pf[i]);
        pb[i] = matrixMultiply(translacja, pb[i]);

    }


    //tworzymy nowy qimage zeby pobrac teksture w MainWindow
    QImage* textureImage = mainWindow -> getTexture();

    float szerokosc = textureImage -> width();
    float wysokosc = textureImage -> height();

    //Główna część programu, rysowanie oraz teksturowanie

    // pierwszy krok, sprawdzamy czy checkBox ukryj tylne ściany jest zaznaczony
    if (mainWindow -> isHideWallsModeOn()) {

        //teraz sprawdzamy po kolei które ze ścian są widoczne aby teksturować tylko te nam potrzebne

        //sciana1
        if (isWallVisible(pf[3], pb[3], pf[0])) {

            //texture checkBox
            if (mainWindow -> isTextureModeOn()) {

                //pobieramy trójkąt ze ściany
                Triangle src(Punkt2D(szerokosc, 0.0f),
                             Punkt2D(szerokosc, wysokosc),
                             Punkt2D(0.0f, wysokosc));

                //pobieramy trójkąt z tekstury
                Triangle dst(to2D(pb[0]), to2D(pb[3]), to2D(pf[3]));

                //nakładamy na ścianę
                drawTexture(textureImage, dst, src);

                //ustawiamy wierzchołki
                src.setVertex(0, Punkt2D(0.0f, 0.0f));
                src.setVertex(1, Punkt2D(szerokosc, 0.0f));
                src.setVertex(2, Punkt2D(0.0f, wysokosc));
                dst.setVertex(0, to2D(pf[0]));
                dst.setVertex(1, to2D(pb[0]));
                dst.setVertex(2, to2D(pf[3]));
                drawTexture(textureImage, dst, src);
            } else {

                rysowanieLinii(pf[0], pb[0]);
                rysowanieLinii(pf[3], pb[3]);
                rysowanieLinii(pb[0], pb[3]);
                rysowanieLinii(pf[0], pf[3]);

            }
        }

        //sciana2
        if (isWallVisible(pf[2], pf[1], pb[2])) {

            //texture checkBox
            if (mainWindow -> isTextureModeOn()) {

                //pobieramy trójkąt ze ściany
                Triangle src(Punkt2D(szerokosc, 0.0f),
                             Punkt2D(szerokosc, wysokosc),
                             Punkt2D(0.0f, wysokosc));

                //pobieramy trójkąt z tekstury
                Triangle dst(to2D(pb[1]), to2D(pb[2]), to2D(pf[2]));
                drawTexture(textureImage, dst, src);

                //nakładamy na ścianę
                src.setVertex(0, Punkt2D(0.0f, 0.0f));
                src.setVertex(1, Punkt2D(szerokosc, 0.0f));
                src.setVertex(2, Punkt2D(0.0f, wysokosc));
                dst.setVertex(0, to2D(pf[1]));
                dst.setVertex(1, to2D(pb[1]));
                dst.setVertex(2, to2D(pf[2]));
                drawTexture(textureImage, dst, src);

            } else {

                //rysowanie linii przy włączonym teksturowaniu
                rysowanieLinii(pf[1], pf[2]);
                rysowanieLinii(pb[1], pb[2]);
                rysowanieLinii(pf[2], pb[2]);
                rysowanieLinii(pf[1], pb[1]);

            }
        }

        //sciana3
        if (isWallVisible(pf[1], pf[0], pb[1])) {

            //texture checkBox
            if (mainWindow -> isTextureModeOn()) {
                //pobieramy trójkąt ze ściany
                Triangle src(Punkt2D(szerokosc, 0.0f),
                             Punkt2D(szerokosc, wysokosc),
                             Punkt2D(0.0f, wysokosc));

                //pobieramy trójkąt z tekstury
                Triangle dst(to2D(pb[0]), to2D(pb[1]), to2D(pf[1]));
                drawTexture(textureImage, dst, src);

                //nakładamy na ścianę
                src.setVertex(0, Punkt2D(0.0f, 0.0f));
                src.setVertex(1, Punkt2D(szerokosc, 0.0f));
                src.setVertex(2, Punkt2D(0.0f, wysokosc));
                dst.setVertex(0, to2D(pf[0]));
                dst.setVertex(1, to2D(pb[0]));
                dst.setVertex(2, to2D(pf[1]));
                drawTexture(textureImage, dst, src);

            } else {

                rysowanieLinii(pf[0], pf[1]);
                rysowanieLinii(pb[0], pb[1]);
                rysowanieLinii(pf[0], pb[0]);
                rysowanieLinii(pf[1], pb[1]);

            }
        }

        //sciana4
        if (isWallVisible(pf[2], pb[2], pf[3])) {

            //texture checkBox
            if (mainWindow -> isTextureModeOn()) {

                //pobieramy trójkąt ze ściany
                Triangle src(Punkt2D(szerokosc, 0.0f),
                             Punkt2D(szerokosc, wysokosc),
                             Punkt2D(0.0f, wysokosc));

                //pobieramy trójkąt z tekstury
                Triangle dst(to2D(pb[2]), to2D(pb[3]), to2D(pf[3]));
                drawTexture(textureImage, dst, src);

                //nakładamy na ścianę
                src.setVertex(0, Punkt2D(0.0f, 0.0f));
                src.setVertex(1, Punkt2D(szerokosc, 0.0f));
                src.setVertex(2, Punkt2D(0.0f, wysokosc));
                dst.setVertex(0, to2D(pf[2]));
                dst.setVertex(1, to2D(pb[2]));
                dst.setVertex(2, to2D(pf[3]));
                drawTexture(textureImage, dst, src);

            } else {

                //rysowanie linii przy włączonym teksturowaniu
                rysowanieLinii(pf[2], pf[3]);
                rysowanieLinii(pb[2], pb[3]);
                rysowanieLinii(pf[3], pb[3]);
                rysowanieLinii(pf[2], pb[2]);

            }
        }

        //sciana5
        if (isWallVisible(pf[2], pf[3], pf[1])) {

            //texture checkBox
            if (mainWindow -> isTextureModeOn()) {

                //pobieramy trójkąt ze ściany
                Triangle src(Punkt2D(szerokosc, 0.0f),
                             Punkt2D(szerokosc, wysokosc),
                             Punkt2D(0.0f, wysokosc));

                //pobieramy trójkąt z tekstury
                Triangle dst(to2D(pf[1]), to2D(pf[2]), to2D(pf[3]));
                drawTexture(textureImage, dst, src);

                //nakładamy na ścianę
                src.setVertex(0, Punkt2D(0.0f, 0.0f));
                src.setVertex(1, Punkt2D(szerokosc, 0.0f));
                src.setVertex(2, Punkt2D(0.0f, wysokosc));
                dst.setVertex(0, to2D(pf[0]));
                dst.setVertex(1, to2D(pf[1]));
                dst.setVertex(2, to2D(pf[3]));
                drawTexture(textureImage, dst, src);

            } else {

                //rysowanie linii przy włączonym teksturowaniu
                rysowanieLinii(pf[0], pf[1]);
                rysowanieLinii(pf[2], pf[3]);
                rysowanieLinii(pf[2], pf[1]);
                rysowanieLinii(pf[0], pf[3]);

            }
        }

        //sciana6
        if (isWallVisible(pb[2], pb[1], pb[3])) {

            //texture checkBox
            if (mainWindow -> isTextureModeOn()) {
                //pobieramy trójkąt ze ściany
                Triangle src(Punkt2D(szerokosc, 0.0f),
                             Punkt2D(szerokosc, wysokosc),
                             Punkt2D(0.0f, wysokosc));

                //pobieramy trójkąt z tekstury
                Triangle dst(to2D(pb[1]), to2D(pb[2]), to2D(pb[3]));
                drawTexture(textureImage, dst, src);

                //nakładamy na ścianę
                src.setVertex(0, Punkt2D(0.0f, 0.0f));
                src.setVertex(1, Punkt2D(szerokosc, 0.0f));
                src.setVertex(2, Punkt2D(0.0f, wysokosc));
                dst.setVertex(0, to2D(pb[0]));
                dst.setVertex(1, to2D(pb[1]));
                dst.setVertex(2, to2D(pb[3]));
                drawTexture(textureImage, dst, src);

            } else {

                //rysowanie linii przy włączonym teksturowaniu
                rysowanieLinii(pb[0], pb[1]);
                rysowanieLinii(pb[2], pb[3]);
                rysowanieLinii(pb[2], pb[1]);
                rysowanieLinii(pb[0], pb[3]);

            }
        }

    } else {

        //jeżeli żaden z powyzszych ifów nie jest spełniony rysujemy wszystkie krawędzie i nie teksturujemy ścian
        rysowanieLinii(pf[0], pb[0]);
        rysowanieLinii(pf[1], pb[1]);
        rysowanieLinii(pf[2], pb[2]);
        rysowanieLinii(pf[3], pb[3]);
        rysowanieLinii(pf[0], pf[1]);
        rysowanieLinii(pf[2], pf[3]);
        rysowanieLinii(pf[2], pf[1]);
        rysowanieLinii(pf[0], pf[3]);
        rysowanieLinii(pb[0], pb[1]);
        rysowanieLinii(pb[2], pb[3]);
        rysowanieLinii(pb[2], pb[1]);
        rysowanieLinii(pb[0], pb[3]);

    }
}


//algorytm texturowania trójkątów
void Canvas::drawTexture(QImage* image, Triangle dst, Triangle src)
{
    Punkt2D minPos = dst.getVertex(0);
    Punkt2D maxPos = dst.getVertex(0);

    for (int i = 1; i < 3; i++)
    {
        Punkt2D pos = dst.getVertex(i);
        /*okreslamy min i max*/
        if (minPos.X() > pos.X())
            minPos.setX(pos.X());

        if (minPos.Y() > pos.Y())
            minPos.setY(pos.Y());

        if (maxPos.X() < pos.X())
            maxPos.setX(pos.X());

        if (maxPos.Y() < pos.Y())
            maxPos.setY(pos.Y());


    }
    /*okreslamy szerokosc i wysokosc*/
    float width = maxPos.X() - minPos.X();
    float height = maxPos.Y() - minPos.Y();

    /*pobieramy ze sciany*/
    float xa = dst.getVertex(0).X();
    float ya = dst.getVertex(0).Y();
    float xb = dst.getVertex(1).X();
    float yb = dst.getVertex(1).Y();
    float xc = dst.getVertex(2).X();
    float yc = dst.getVertex(2).Y();

    /*xb-xA      xc-xa
     yb-ya       yc-ya*/
    float m = (xb - xa) * (yc - ya) - (xc - xa) * (yb - ya);

    float xta = src.getVertex(0).X();
    float yta = src.getVertex(0).Y();
    float xtb = src.getVertex(1).X();
    float ytb = src.getVertex(1).Y();
    float xtc = src.getVertex(2).X();
    float ytc = src.getVertex(2).Y();

    int textureWidth = image -> width();
    int textureHeight = image -> height();

    for (float y = minPos.Y(); y <= minPos.Y() + height; y+=0.5f)
    {
        for (float x = minPos.X(); x <= minPos.X() + width; x+=0.5f)
        {
            /*x-xA      xc-xa
             y-ya       yc-ya*/
            float v = ((x - xa) * (yc - ya) - (xc - xa) * (y - ya)) / m;
            /*xb-xA      x-xa
             yb-ya       yc-ya*/
            float w = ((xb - xa) * (y - ya) - (x - xa) * (yb - ya)) / m;
            /*u=1-v-w; bo u+v+w-1*/
            float u = 1.0f - v - w;

            if (u < 0.0f || v < 0.0f || w < 0.0f || u > 1.0f || v > 1.0f || w > 1.0f)
                continue;
            //współrzędne barycentryczne(wierzchołki)
            int xt = roundf(u * xta + v * xtb + w * xtc);
            int yt = roundf(u * yta + v * ytb + w * ytc);
            if (xt >= textureWidth) xt = textureWidth - 1;
            if (yt >= textureHeight) yt = textureHeight - 1;

            QColor color = image -> pixel(QPoint(xt, yt));
            rysowaniePixela(x, y, color.red(), color.green(), color.blue());
        }
    }
}

//resetowanie pozycji kostki(slidery)
void Canvas::reset()
{
    for (int y = 0; y < canvasImg -> width(); y++)
    {
        for (int x = 0; x < canvasImg -> height(); x++)
        {
            //z dokumentacji
            //setPixel(int x, int y, uint index_or_rgb)
            canvasImg->setPixel(x, y, QColor(255, 255, 255).rgb());
        }
    }
}


Punkt2D Canvas::to2D(Punkt3D punkt)
{

    //d to zmienna którą trzeba dobrać aby bryła się nie rozjeżdżała
    float d = mainWindow -> getD();
    float m = (1.0f + punkt.Z() / d);
    return Punkt2D(punkt.X() / m, punkt.Y() / m);
}

Punkt2D Canvas::to2D(Punkt4D punkt)
{

    //d to zmienna którą trzeba dobrać aby bryła się nie rozjeżdżała
    float d = mainWindow -> getD();
    float m = (1.0f + punkt.Z() / d);
    return Punkt2D(punkt.X() / m, punkt.Y() / m);
}

bool Canvas::isWallVisible(Punkt3D punkt0, Punkt3D punkt1, Punkt3D punkt2)
{
    float d = mainWindow -> getD();

    float d1[2];
    float d2[2];

    float v1[2];
    float v2[2];
    float v3[3];

    v1[0] = punkt0.X() / (1.0f + punkt0.Z() / d);
    v1[1] = punkt0.Y() / (1.0f + punkt0.Z() / d);

    v2[0] = punkt1.X() / (1.0f + punkt1.Z() / d);
    v2[1] = punkt1.Y() / (1.0f + punkt1.Z() / d);

    v3[0] = punkt2.X() / (1.0f + punkt2.Z() / d);
    v3[1] = punkt2.Y() / (1.0f + punkt2.Z() / d);


    //obliczamy współrzędne punktów

    d1[0]=v2[0] - v1[0];
    d1[1]=v2[1] - v1[1];

    d2[0]=v3[0] - v1[0];
    d2[1]=v3[1] - v1[1];

    //http://www.cubic.org/docs/backcull.htm
    //Complete Formula: z = (d1.x * d2.y) - (d1.y * d2.x)
    float z = (d1[0] * d2[1]) - (d1[1] * d2[0]);

    if((z >= 0.0f)) {
        return true;
    } else {
        return false;
    }
}

//sprawdzamy widoczność ścian, jeżeli bool = true to znaczy że ściany są widoczne
bool Canvas::isWallVisible(Punkt4D v0, Punkt4D v1, Punkt4D v2)
{
    return isWallVisible(Punkt3D(v0.X(), v0.Y(), v0.Z()),
                         Punkt3D(v1.X(), v1.Y(), v1.Z()),
                         Punkt3D(v2.X(), v2.Y(), v2.Z()));
}
