#include <QApplication>
#include "CannyWidget.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    CannyWidget w;
    w.show();

    return app.exec();
}
