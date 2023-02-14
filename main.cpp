
#include "haro.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Haro w;

    w.show();

    return a.exec();
}
