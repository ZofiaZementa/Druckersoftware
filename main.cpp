#include "controlwindow.h"
#include "machinecontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("P-Seminar 3D-Drucker");
    QCoreApplication::setApplicationName("DruckerSoftware");
    QCoreApplication::setApplicationVersion("v0.2");

    ControlWindow w;
    MachineController c;

    QObject::connect(&c, SIGNAL(error(QString)), &w, SLOT(dislpayErrorMessage(QString)));

    w.show();

    return a.exec();
}
