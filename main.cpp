#include "UI/GUI/controlwindow.h"
#include "machinecontroller.h"
#include "IO/heatingcontroller.h"
#include "IO/sensorlistener.h"
#include "IO/fancontroller.h"
#include "IO/iocontroller.h"
#include "IO/iomainloop.h"
#include "IO/lightingcontroller.h"
#include "UI/CMD/commandlineui.h"
#include "UI/CMD/cmduiiocontrollerinterface.h"
#include "UI/CMD/cmduiloggerinterface.h"
#include "UI/CMD/cmduimachinecontrollerinterface.h"
#include "Logging/logger.h"
#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{

    bool gui = true;
    bool directprint = false;

    QApplication a(argc, argv);

    //sets general application-information
    QCoreApplication::setOrganizationName("P-Seminar 3D-Drucker");
    QCoreApplication::setApplicationName("DruckerSoftware");
    QCoreApplication::setApplicationVersion("v0.2.41");

    //checks if th -nG argument was supplied
    //if not, gui is set to true, if yes, gui is set to false
    for(int i = 1;i < argc;i++){

        if(strcmp(argv[i], "-p") == 0 && i == 1){

            if(argc == 2){

                directprint = true;
                break;
            }
        }

        else if(strcmp(argv[i], "-nG") == 0){

            gui = false;
        }
    }

    //Thread-definition and initialisation

    QThread *sysThread = new QThread;
    QThread *ioThread = new QThread;

    //definition of the cmdThread, if it gets used, it gets initialised later
    QThread *cmdThread;

    //Component-definition

    MachineController c;
    IOController io;
    SensorListener sl;
    HeatingController hc;
    FanController fc;
    ControlWindow w;
    CommandlineUI cmd;
    CmdUIIOControllerInterface cioi;
    CmdUILoggerInterface cli;
    CmdUIMachineControllerInterface cmci;
    Logger l;
    IOMainLoop ioml;
    LightingController lc;

    //moving system-components to the sysThread

    //moving the MotorController to the sysThread
    c.moveToThread(sysThread);
    //moving the Logger to the sysThread
    l.moveToThread(sysThread);

    //moving IO-components to the ioThread

    //moving the IOController to the ioThread
    io.moveToThread(ioThread);
    //moving the SensorListner to the ioThread
    sl.moveToThread(ioThread);
    //moving the HeatingController to the ioThread
    hc.moveToThread(ioThread);
    //moving the FanController to the ioThread
    fc.moveToThread(ioThread);
    //moving the IOMainLoop to the ioThread
    ioml.moveToThread(ioThread);
    //moving the LightingController to the ioThread
    lc.moveToThread(ioThread);

    //sets the pointers in IOMainLoop

    ioml.setFanController(&fc);
    ioml.setHeatingController(&hc);
    ioml.setSensorListener(&sl);
    ioml.setIOController(&io);
    ioml.setLightingController(&lc);

    //signals & slots

    //logging

    //connecting the logEntry signal of the SensorListener to the log slot of the Logger
    QObject::connect(&sl, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    //connecting the logEntry signal of the IOController to the log slot of the Logger
    QObject::connect(&io, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    //connecting the logEntry signal of the IOMainLoop to the log slot of the Logger
    QObject::connect(&ioml, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));
    //connecting the logEntry signal of the MachineController to the log slot of the Logger
    QObject::connect(&c, SIGNAL(logEntry(QString, int)), &l, SLOT(log(QString,int)));
    //connecting the logEntry signal of the LightingController to the log slot of the Logger
    QObject::connect(&lc, SIGNAL(logEntry(QString,int)), &l, SLOT(log(QString,int)));

    //enstops

    //connectiong the xAxisPositiveEndstopHit signal of the SensorListener to the xAxisPositiveEndstopHit slot of the MachineController
    QObject::connect(&sl, SIGNAL(xAxisPositiveEndstopHit()), &c, SLOT(xAxisPositiveEndstopHit()));
    //connectiong the xAxisNegativeEndstopHit signal of the SensorListener to the xAxisNegativeEndstopHit slot of the MachineController
    QObject::connect(&sl, SIGNAL(xAxisNegativeEndstopHit()), &c, SLOT(xAxisNegativeEndstopHit()));
    //connectiong the yAxisPositiveEndstopHit signal of the SensorListener to the yAxisPositiveEndstopHit slot of the MachineController
    QObject::connect(&sl, SIGNAL(yAxisPositiveEndstopHit()), &c, SLOT(yAxisPositiveEndstopHit()));
    //connectiong the yAxisNegativeEndstopHit signal of the SensorListener to the yAxisNegativeEndstopHit slot of the MachineController
    QObject::connect(&sl, SIGNAL(yAxisNegativeEndstopHit()), &c, SLOT(yAxisNegativeEndstopHit()));
    //connectiong the zAxisPositiveEndstopHit signal of the SensorListener to the zAxisPositiveEndstopHit slot of the MachineController
    QObject::connect(&sl, SIGNAL(zAxisPositiveEndstopHit()), &c, SLOT(zAxisPositiveEndstopHit()));
    //connectiong the zAxisNegativeEndstopHit signal of the SensorListener to the zAxisNegativeEndstopHit slot of the MachineController
    QObject::connect(&sl, SIGNAL(zAxisNegativeEndstopHit()), &c, SLOT(zAxisNegativeEndstopHit()));

    //miscellaneous

    //connecting the setStatusLED signal of the MachineController to the setStatusLED slot of the LightingController
    QObject::connect(&c, SIGNAL(setStatusLED(int,int)), &lc, SLOT(setStatusLED(int,int)));
    //connecting the started signal of the ioThread to the startMainLoop slot of the IOMainLoop, so that it starts when the thread starts
    QObject::connect(ioThread, SIGNAL(started()), &ioml, SLOT(startMainLoop()));

    //checks a GUI should be displayed or not
    //triggered if it should
    if(gui == true && directprint == false){

        //signals & slots

        //connects the error signal of the MachineController to the displayErrorMessage slot of the GUI
        QObject::connect(&c, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
        //connects the error signal of the IOController to the displayErrorMessage slot of the GUI
        QObject::connect(&io, SIGNAL(error(QString)), &w, SLOT(displayErrorMessage(QString)));
        //connects the destroyed signal of the GUI to the quit slot of the sysThread, so that the sysThread stops when the window gets closed
        QObject::connect(&w, SIGNAL(destroyed()), sysThread, SLOT(quit()));
        //connects the destroyed signal of the GUI to the quit slot of the ioThread, so that the ioThread stops when the window gets closed
        QObject::connect(&w, SIGNAL(destroyed()), ioThread, SLOT(quit()));

        //shows the ControlWindow
        w.showFullScreen();
    }

    //triggered if it shouldn't
    else if(gui == false && directprint == false){

        //initialises the cmdThread
        cmdThread = new QThread;

        //sets the pointers in CmdUIIOControllerInterface, CmdUILoggerInterface and CmdUIMachineControllerInterface

        //sets the pointer to the IOController in CmdUIIOControllerInterface to the IOController
        cioi.setIOController(&io);
        //sets the pointer to the Logger in CmdUILoggerInterface to the Logger
        cli.setLogger(&l);
        //sets the pointer to the MachineController in CmdUIMachineControllerInterface to the MachineController
        cmci.setMachineController(&c);

        //moves the components to their threads

        //moving the CmdUIIOControllerInterface to the ioThread
        cioi.moveToThread(ioThread);
        //moving the CmdUILoggerInterface to the sysThread
        cli.moveToThread(sysThread);
        //moving the CmdUIMachineControllerInterface to the sysThread
        cmci.moveToThread(sysThread);
        //moving the CommandlineUI to the cmdThread
        cmd.moveToThread(cmdThread);

        //signals & slots

        //connecting the CommandlineUI to the CmdUIMachineControllerInterface

        //connecting the machineControllerG0 signal of the CommandlineUI to the g0 slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerG0(qreal,qreal,qreal,qreal,qreal,int)), &cmci, SLOT(g0(qreal,qreal,qreal,qreal,qreal,int)), Qt::BlockingQueuedConnection);
        //connecting the machineControllerPause signal of the CommandlineUI to the pause slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerPause(bool*)), &cmci, SLOT(pause(bool*)), Qt::BlockingQueuedConnection);
        //connecting the machineControllerPlay signal of the CommandlineUI to the play slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerPlay(bool*)), &cmci, SLOT(play(bool*)), Qt::BlockingQueuedConnection);
        //connecting the machineControllerPrint signal of the CommandlineUI to the print slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerPrint(bool*)), &cmci, SLOT(print(bool*)), Qt::BlockingQueuedConnection);
        //connecting the machineControllerReset signal of the CommandlineUI to the reset slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerReset()), &cmci, SLOT(reset()), Qt::BlockingQueuedConnection);
        //connecting the machineControllerSetFilePath signal of the CommandlineUI to the setFilePath slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerSetFilePath(QUrl)), &cmci, SLOT(setFilePath(QUrl)), Qt::BlockingQueuedConnection);
        //connecting the machineControllerSetLine signal of the CommandlineUI to the setLine slot of the CmdUIMachineControllerInterface
        QObject::connect(&cmd, SIGNAL(machineControllerSetLine(int)), &cmci, SLOT(setLine(int)), Qt::BlockingQueuedConnection);

        //connecting the CommandlineUI to the CmdUIIOControllerInterface

        //connecting the iOControllerRead signal of the CommandlineUI to the iOControllerRead slot of the CmdUIIOControllerInterface
        QObject::connect(&cmd, SIGNAL(iOControllerRead(QString,int*)), &cioi, SLOT(iOControllerRead(QString,int*)), Qt::BlockingQueuedConnection);
        //connecting the iOControllerWrite signal of the CommandlineUI to the iOControllerWrite slot of the CmdUIIOControllerInterface
        QObject::connect(&cmd, SIGNAL(iOControllerWrite(QString,int,bool*)), &cioi, SLOT(iOControllerWrite(QString,int,bool*)), Qt::BlockingQueuedConnection);

        //connecting the CommandlineUI to the CmdUILoggerInterface

        //connecting the loggerAddLog signal of the CommandlineUI to the addLog slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerAddLog(QList<int>,QString)), &cli, SLOT(addLog(QList<int>,QString)), Qt::BlockingQueuedConnection);
        //connecting the loggerChangeLogFolderPath signal of the CommandlineUI to the changeLogFolderPath slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerChangeLogFolderPath(QString)), &cli, SLOT(changeLogFolderPath(QString)), Qt::BlockingQueuedConnection);
        //connecting the loggerDeleteLog signal of the CommandlineUI to the deleteLog slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerDeleteLog(QString)), &cli, SLOT(deleteLog(QString)), Qt::BlockingQueuedConnection);
        //connecting the loggerEditLog signal of the CommandlineUI to the editLog slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerEditLog(QList<int>,QString)), &cli, SLOT(editLog(QList<int>,QString)), Qt::BlockingQueuedConnection);
        //connecting the loggerLog signal of the CommandlineUI to the log slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerLog(QString,int)), &cli, SLOT(log(QString,int)), Qt::BlockingQueuedConnection);
        //connecting the loggerLogFiles signal of the CommandlineUI to the logFiles slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerLogFiles(QStringList*)), &cli, SLOT(logFiles(QStringList*)), Qt::BlockingQueuedConnection);
        //connecting the loggerLogFolderPath signal of the CommandlineUI to the logFolderPath slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerLogFolderPath(QString*)), &cli, SLOT(logFolderPath(QString*)), Qt::BlockingQueuedConnection);
        //connecting the loggerReadFile signal of the CommandlineUI to the readFile slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerReadFile(QString,QStringList*)), &cli, SLOT(readFile(QString,QStringList*)), Qt::BlockingQueuedConnection);
        //connecting the loggerSetLogFolderPath signal of the CommandlineUI to the setLogFolderPath slot of the CmdUILoggerInterface
        QObject::connect(&cmd, SIGNAL(loggerSetLogFolderPath(QString)), &cli, SLOT(setLogFolderPath(QString)), Qt::BlockingQueuedConnection);

        //connecting the cmdThread to the several threads

        //connecting the started signal of the cmdThread to the mainLoop slot of the CommandlineUI, so that it starts when the cmdThread starts
        QObject::connect(cmdThread, SIGNAL(started()), &cmd, SLOT(mainLoop()));
        //connecting the finished signal of the cmdThread to the quit slot of the ioThread
        QObject::connect(cmdThread, SIGNAL(finished()), ioThread, SLOT(quit()));
        //connecting the finished signal of the cmdThread to the quit slot of the sysThread
        QObject::connect(cmdThread, SIGNAL(finished()), sysThread, SLOT(quit()));

        //starts the cmdThread
        cmdThread->start();
    }

    //starts the sysThread
    sysThread->start();
    //starts the ioThread
    ioThread->start();

    if(directprint == true){

        c.setFilePath(QUrl(QString(argv[2])));

        if(c.print() == false){

            sysThread->quit();
            ioThread->quit();
            printf("error. See logfiles for more information\r\n");
        }
    }

    return a.exec();
}
