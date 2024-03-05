#include "PaperSticher.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaperSticher w;
    w.show();
    return a.exec();
}
