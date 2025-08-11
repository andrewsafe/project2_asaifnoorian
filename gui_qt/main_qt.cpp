#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w(/*startingCoins=*/100);
    w.show();
    return app.exec();
}
