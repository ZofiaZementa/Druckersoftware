#include "controlwindow.h"
#include "machinecontroller.h"
#include "iocontroller.h"
#include "commandlineui.h"
#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{

    bool gui = true;

    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("P-Seminar 3D-Drucker");
    QCoreApplication::setApplicationName("DruckerSoftware");
    QCoreApplication::setApplicationVersion("v0.2.15");

    for(int i = 1;i < argc;i++){

        if(strcmp(argv[i], "-nG") == 0){

            gui = false;
        }
    }

    QThread *sysThread = new QThread;
    QThread *ioThread = new QThread;
    MachineController c;
    IOController io;


    c.moveToThread(sysThread);
    io.moveToThread(ioThread);

    QObject::connect(ioThread, SIGNAL(started()), &io, SLOT(mainLoop()));

    if(gui == true){

        ControlWindow w;

        QObject::connect(&c, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
        QObject::connect(&io, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));

        w.show();
    }

    else{

        QThread *cmdThread = new QThread;
        CommandlineUI cmd;

        cmd.setMachineController(&c);

        cmd.moveToThread(cmdThread);
        QObject::connect(cmdThread, SIGNAL(started()), &cmd, SLOT(mainLoop()));
        cmdThread->start();
    }

    sysThread->start();
    ioThread->start();

    return a.exec();
}
