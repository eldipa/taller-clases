#ifndef GREETER_H
#define GREETER_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = 0);
    unsigned int getWinId() const;
private:
    void connectEvents();
};

#endif // GREETER_H
