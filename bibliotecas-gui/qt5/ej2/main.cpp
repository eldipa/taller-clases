#include <QApplication>
#include "Greeter.h"

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio el greeter
    Greeter greeter;
    greeter.show();
    // Arranca el loop de la UI
    return app.exec();
}
