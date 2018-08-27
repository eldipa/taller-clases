#include "Greeter.h"

Greeter::Greeter(QWidget *parent) : QWidget(parent), buttonGreet("Saludar") {
    QVBoxLayout* greeterLayout = new QVBoxLayout();
    QHBoxLayout* inputLayout = new QHBoxLayout();
    // Armo la primer linea de widgets con un layout horizontal
    inputLayout->addWidget(&this->inputName);
    inputLayout->addWidget(&this->buttonGreet);
    // Inserto el input y el boton de saludar en la primer linea
    greeterLayout->addLayout(inputLayout);
    greeterLayout->addWidget(&this->labelOut);
    this->labelOut.setText("Ingrese un nombre");
    this->setLayout(greeterLayout);
    /**
     * Conecto el evento "clicked" del boton a la funcion "updateGreetings"
     * del Greeter. El primer parametro es el boton que lanza el evento, el
     * segundo es el evento que se esta conectando, el tercer parametro es
     * el widget que recibe el evento, y el cuarto es la funcion que responde
     * al evento
     **/
    QObject::connect(&this->buttonGreet, &QPushButton::clicked,
                     this, &Greeter::updateGreetings);
}

void Greeter::updateGreetings() {
    QString name = this->inputName.text();
    QString greetings = QString("Hola %1").arg(name);
    this->labelOut.setText(greetings);
}
