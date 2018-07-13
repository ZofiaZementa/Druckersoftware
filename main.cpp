#include "UI/controlwindow.h"
#include "machinecontroller.h"
#include "IO/heatingcontroller.h"
#include "IO/sensorlistener.h"
#include "IO/fancontroller.h"
#include "IO/iocontroller.h"
#include "IO/iomainloop.h"
#include "IO/lightingcontroller.h"
#include "UI/commandlineui.h"
#include "Logging/logger.h"
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
    SensorListener sl;
    HeatingController hc;
    FanController fc;
    ControlWindow w;
    QThread *cmdThread = new QThread;
    CommandlineUI cmd;
    Logger l;
    IOMainLoop ioml;
    LightingController lc;

    c.moveToThread(sysThread);
    l.moveToThread(sysThread);
    io.moveToThread(ioThread);
    sl.moveToThread(ioThread);
    hc.moveToThread(ioThread);
    fc.moveToThread(ioThread);
    ioml.moveToThread(ioThread);
    lc.moveToThread(ioThread);

    ioml.setFanController(&fc);
    ioml.setHeatingController(&hc);
    ioml.setSensorListener(&sl);
    ioml.setIOController(&io);
    ioml.setLightingController(&lc);

    QObject::connect(&sl, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    QObject::connect(&io, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    QObject::connect(&ioml, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    QObject::connect(&c, SIGNAL(logEntry(QString, int)), &l, SLOT(log(QString,int)));
    QObject::connect(&lc, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    QObject::connect(&c, SIGNAL(setStatusLED(int,int)), &lc, SLOT(setStatusLED(int,int)));
    QObject::connect(&sl, SIGNAL(xAxisPositiveEndstopHit()), &c, SLOT(xAxisPositiveEndstopHit()));
    QObject::connect(&sl, SIGNAL(xAxisNegativeEndstopHit()), &c, SLOT(xAxisNegativeEndstopHit()));
    QObject::connect(&sl, SIGNAL(yAxisPositiveEndstopHit()), &c, SLOT(yAxisPositiveEndstopHit()));
    QObject::connect(&sl, SIGNAL(yAxisNegativeEndstopHit()), &c, SLOT(yAxisNegativeEndstopHit()));
    QObject::connect(&sl, SIGNAL(zAxisPositiveEndstopHit()), &c, SLOT(zAxisPositiveEndstopHit()));
    QObject::connect(&sl, SIGNAL(zAxisNegativeEndstopHit()), &c, SLOT(zAxisNegativeEndstopHit()));

    if(gui == true){

        QObject::connect(&c, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
        QObject::connect(&io, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
        QObject::connect(&w, SIGNAL(destroyed()), sysThread, SLOT(quit()));
        QObject::connect(&w, SIGNAL(destroyed()), ioThread, SLOT(quit()));
        w.show();
    }

    else{

        cmd.setMachineController(&c);
        cmd.setIOController(&io);
        cmd.setLogger(&l);
        cmd.moveToThread(cmdThread);
        QObject::connect(cmdThread, SIGNAL(started()), &cmd, SLOT(mainLoop()));
        QObject::connect(cmdThread, SIGNAL(finished()), ioThread, SLOT(quit()));
        QObject::connect(cmdThread, SIGNAL(finished()), sysThread, SLOT(quit()));
        cmdThread->start();
    }

    sysThread->start();
    ioThread->start();

    return a.exec();
}
