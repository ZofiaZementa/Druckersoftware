#include "controlwindow.h"
#include "machinecontroller.h"
#include "iocontroller.h"
#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("P-Seminar 3D-Drucker");
    QCoreApplication::setApplicationName("DruckerSoftware");
    QCoreApplication::setApplicationVersion("v0.2.15");

    QThread *sysThread = new QThread;
    QThread *ioThread = new QThread;
    MachineController c;
    IOController io;
    ControlWindow w;

    c.moveToThread(sysThread);
    io.moveToThread(ioThread);

    QObject::connect(&c, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
    QObject::connect(&io, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
    QObject::connect(ioThread, SIGNAL(started()), &io, SLOT(mainLoop()));

    sysThread->start();
    ioThread->start();
    w.show();

    return a.exec();
}
