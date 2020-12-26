#include "notepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad w;
    w.show();
   // w.setWindowIcon(QIcon("qrc:/favicon.ico"));
    return a.exec();
}
