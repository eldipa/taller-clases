#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio el greeter
    MainWindow window;
    window.show();
    // Arranca el loop de la UI
    return app.exec();
}

