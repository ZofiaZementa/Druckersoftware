#include "commandlineui.h"

CommandlineUI::CommandlineUI(QObject *parent) : QObject(parent)
{

}

void CommandlineUI::setMachineController(MachineController *machineController)
{

    m_machineController = machineController;
}

void CommandlineUI::setIOController(IOController *iOController)
{

    m_iOController = iOController;
}

void CommandlineUI::setLogger(Logger *logger)
{

    m_logger = logger;
}

void CommandlineUI::mainLoop()
{

    int check;

    while(true){

        printf(">>>");
        scanf("%399s", *m_input);
        printf("\r\n");
        check = checkCommands();

        if(check == 1){

            return;
        }

        else if(check == 2){

            printhelp();
        }
    }
}

QStringList CommandlineUI::breakUpString(QString string)
{

    int help = -1;

    QStringList retString;

    for(int i = 0;i < string.count();i++){

        if(string.at(i) == QString(" ") && i - help > 1){

            retString.append(string.mid((help + 1), (i - help - 1)));
            help = i;
        }

        else if(string.at(i) == QString(" ")){

            help = i;
        }
    }

    if(string.count() - 1 - help > 1){

        retString.append(string.mid((help + 1), (string.count() - help - 1)));
    }

    return retString;
}

int CommandlineUI::checkCommands()
{

    QStringList input = breakUpString(QString(*m_input));

    for(int i = 0;i < input.count();i++){

        if(input.at(i) == QString("exit")){

            return 1;
        }

        else if(input.at(i) == QString("setfile")){

            m_machineController->setFilePath(QUrl(input.at(i + 1)));
            printf("Filepath set to %s\r\n", input.at(i + 1).toLatin1().data());
            return 0;
        }

        else if(input.at(i) == QString("setline")){

            m_machineController->setLine(input.at(i + 1).toInt());
            printf("filepath set to %d\r\n", input.at(i + 1).toInt());
            return 0;
        }

        else if(input.at(i) == QString("print")){

            if(m_machineController->print() == true){

                m_machineController->print();
                printf("printing...\r\n");
                return 0;
            }

            else{

                printf("print couldnt be started\r\n");
                return 0;
            }
        }

        else if(input.at(i) == QString("pause")){

            if(m_machineController->pause() == true){

                printf("print paused\r\n");
                return 0;
            }

            else{

                printf("print couldn't be paused\r\n");
                return 0;
            }
        }

        else if(input.at(i) == QString("play")){

            if(m_machineController->play() == true){

                printf("print continued\r\n");
                return 0;
            }

            else{

                printf("print couldn't be continued\r\n");
                return 0;
            }
        }

        else if(input.at(i) == QString("reset")){

            m_machineController->reset();
            printf("all values reset\n");
            return 0;
        }

        else if(input.at(i) == QString("write")){

            if(input.count() == i + 3){

                bool ok;

                if(m_iOController->writeVariableValue(input.at(i), input.at(i).toInt(&ok, 10)) == true && ok == true){

                    return 1;
                }

                else{

                    return 2;
                }
            }

            else{

                return 2;
            }
        }

        else if(input.at(i) == QString("read")){

            if(input.count() == i + 2){

                printf("value: %d\r\n", m_iOController->readVariableValue(input.at(i)));
                return 1;
            }

            else{

                return 2;
            }
        }

        else if(input.at(i) == QString("addlog")){

            QList<int> types;
            QString logName;
            bool ok;

            if(input.count() >= 3){

                logName = input.at(1);

                for(int n = 2;n < input.count();n++){

                    types.append(input.at(n).toInt(&ok, 10));

                    if(ok == false){

                        return 2;
                    }
                }
            }

            else{

                return 2;
            }

            m_logger->addLog(types, logName);
        }

        else if(input.at(i) == QString("editlog")){

            QList<int> types;
            QString logName;
            bool ok;

            if(input.count() >= 3){

                logName = input.at(1);

                for(int n = 2;n < input.count();n++){

                    types.append(input.at(n).toInt(&ok, 10));

                    if(ok == false){

                        return 2;
                    }
                }
            }

            else{

                return 2;
            }

            m_logger->editLog(types, logName);
        }

        else if(input.at(i) == QString("dellog")){

            QString logName;

            if(input.count() == 2){

                logName = input.at(i);
            }

            else{

                return 2;
            }

            m_logger->deleteLog(logName);
        }

        else if(input.at(i) == QString("setlfpath")){

            QString folderPath;

            if(input.count() == 2){

                folderPath = input.at(i);
            }

            else{

                return 2;
            }

            m_logger->setLogFolderPath(folderPath);
        }

        else if(input.at(i) == QString("chnglfpath")){

            QString folderPath;

            if(input.count() == 2){

                folderPath = input.at(i);
            }

            else{

                return 2;
            }

            m_logger->changeLogFolderPath(folderPath);
        }

        else if(input.at(i) == QString("lfpath")){

            QByteArray output;

            if(input.count() == 2){

                output = m_logger->logFolderPath().toLatin1();
            }

            else{

                return 2;
            }

            printf("log folder path: %s", output.data());
        }

        else if(input.at(i) == QString("g0")){

            qreal x = 0.0;
            qreal y = 0.0;
            qreal z = 0.0;
            qreal e = 0.0;
            int s = 0;

            for(int n = i;n < input.count();n++){

                if(input.at(n).at(0) == QString("X") || input.at(n).at(0) == QString("x")){

                    input[n].remove(0, 1);
                    x = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QString("Y") || input.at(n).at(0) == QString("y")){

                    input[n].remove(0, 1);
                    y = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QString("Z") || input.at(n).at(0) == QString("z")){

                    input[n].remove(0, 1);
                    z = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QString("E") || input.at(n).at(0) == QString("e")){

                    input[n].remove(0, 1);
                    e = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QString("S") || input.at(n).at(0) == QString("s")){

                    input[n].remove(0, 1);
                    s = input.at(n).toInt();
                }

                else{

                    return 2;
                }
            }

            m_machineController->g0(x, y, z, e, -1.0, s);

            printf("drive to X%e Y%e Z%e E%e with the endstop behavior %d\r\n", (double)(x), (double)(y), (double)(z), (double)(e), s);
            return 0;
        }

        else{

            return 2;
        }


    }

    return 2;
}

void CommandlineUI::printhelp()
{
    printf("commands for the Printersoftware:\r\n\n\n");

    printf("settings:\r\n\n");
    printf("\tsetfile   \t<filepath> sets the filepath\r\n");
    printf("\tsetline   \t<linenumber> sets the linenumber at which to start\r\n");

    printf("\ncontrols:\r\n\n");
    printf("\texit      \texits the Printersoftware and goes back to the terminal\r\n");
    printf("\tprint     \tstarts the print with the given parameters\r\n");
    printf("\tpause     \tpauses the print\r\n");
    printf("\tplay      \tcontinues the print\r\n");
    printf("\treset     \tresets all set values\r\n");

    printf("\nio controls:\r\n\n");
    printf("\twrite     \t<pinName> <value>\r\n");
    printf("\tread      \t<pinName>\r\n");

    printf("\nloggercontrols:\r\n\n");
    printf("\taddlog    \t<logName> <type1> <type2> ...\r\n");
    printf("\teditlog   \t<logName> <type1> <type2> ...\r\n");
    printf("\tdellog    \t<logName>\r\n");
    printf("\tsetlfpath \t<filePath>\r\n");
    printf("\tchnglfpath\t<filePath>\r\n");
    printf("\tlfpath    \tprints out the log folder path\r\n");

    printf("\ngcode commands:\n\n");
    printf("\tg0        \t[X<xvalue>] [Y<yvalue>] [Z<zvalue>] [E<evalue>] [S<svalue>] drives to the given position with top speed\r\n");
}
