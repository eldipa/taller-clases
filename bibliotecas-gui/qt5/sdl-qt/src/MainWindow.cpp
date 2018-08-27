#include "MainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget* parent) :QMainWindow(parent) {
	// Instancio la configuracion generada por el designer y uic
    Ui::MainWindow ui;
    // Configuro este widget para use esa configuracion
    ui.setupUi(this);
    connectEvents();
}

void MainWindow::connectEvents() {
}

unsigned int MainWindow::getWinId() const {
	QWidget* centralWidget = findChild<QWidget*>("centralWidget");
	// winId devuelve un unsigned int, lo devuelvo
	// casteado listo para que lo use SDL
	return centralWidget->winId();
}
