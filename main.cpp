#include "controlwindow.h"
#include "machinecontroller.h"
#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("P-Seminar 3D-Drucker");
    QCoreApplication::setApplicationName("DruckerSoftware");
    QCoreApplication::setApplicationVersion("v0.2.15");

    QThread *sys = new QThread;
    MachineController c;
    ControlWindow w;

    c.moveToThread(sys);

    QObject::connect(&c, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));

    sys->start();
    w.show();

    return a.exec();
}
