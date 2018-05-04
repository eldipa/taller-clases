#ifndef GREETER_H
#define GREETER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

class Greeter : public QWidget {
public:
    explicit Greeter(QWidget *parent = 0);
private:
    // Creo los widgets asignandole un padre
    QLabel labelOut;
    QPushButton buttonGreet;
    QLineEdit inputName;
    void updateGreetings();
};

#endif // GREETER_H
