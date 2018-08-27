#ifndef GREETER_H
#define GREETER_H

#include <QWidget>

class Greeter : public QWidget {
public:
    explicit Greeter(QWidget *parent = 0);
private:
    void updateGreetings();
    void connectEvents();
};

#endif // GREETER_H
