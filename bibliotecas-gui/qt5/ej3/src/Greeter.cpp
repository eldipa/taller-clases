#include "Greeter.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_Greeter.h"

Greeter::Greeter(QWidget *parent) : QWidget(parent) {
    // Instancio la configuracion generada por el designer y uic
    Ui::Greeter greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
    connectEvents();
}

void Greeter::updateGreetings() {
    /**
     * findChild es un metodo de qObject que permite buscar un widget hijo
     * segun su nombre. Si observamos el codigo generado en ui_Greeter
     * cada uno de los objetos recibe un nombre mediante la funcion
     * setObjectName(QString nombre)
     **/
    QLineEdit* inputName = findChild<QLineEdit*>("inputName");
    QLabel* labelOut = findChild<QLabel*>("labelOut");
    QString name = inputName->text();
    QString greetings = QString("Hola %1").arg(name);
    labelOut->setText(greetings);
}

void Greeter::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonGreet = findChild<QPushButton*>("buttonGreet");
    QObject::connect(buttonGreet, &QPushButton::clicked,
                     this, &Greeter::updateGreetings);
}
