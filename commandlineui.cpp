#include "commandlineui.h"

CommandlineUI::CommandlineUI(QObject *parent) : QObject(parent)
{

}

void CommandlineUI::setMachineController(MachineController *machineController)
{

    m_machineController = machineController;
}

void CommandlineUI::mainLoop()
{

    int check;

    while(true){

        printf(">>>\n");
        scanf("%400s", *m_input);
        printf("\n");
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
            printf("Filepath set to %s\n", input.at(i + 1).toLatin1().data());
            return 0;
        }

        else if(input.at(i) == QString("setline")){

            m_machineController->setLine(input.at(i + 1).toInt());
            printf("filepath set to %d\n", input.at(i + 1).toInt());
            return 0;
        }

        else if(input.at(i) == QString("print")){

            if(m_machineController->print() == true){

                m_machineController->print();
                printf("printing...\n");
                return 0;
            }

            else{

                printf("print couldnt be started\n");
                return 0;
            }
        }

        else if(input.at(i) == QString("pause")){

            if(m_machineController->pause() == true){

                printf("print paused\n");
                return 0;
            }

            else{

                printf("print couldn't be paused\n");
                return 0;
            }
        }

        else if(input.at(i) == QString("play")){

            if(m_machineController->play() == true){

                printf("print continued\n");
                return 0;
            }

            else{

                printf("print couldn't be continued\n");
                return 0;
            }
        }

        else if(input.at(i) == QString("play")){

            m_machineController->reset();
            printf("all values reset\n");
            return 0;
        }

        else if(input.at(i) == QString("g0")){

            qreal x = 0.0;
            qreal y = 0.0;
            qreal z = 0.0;
            qreal e = 0.0;
            int s = 0;

            for(int n = i;n < input.count();n++){

                if(input.at(n).at(0) == QChar("X") || input.at(n).at(0) == QChar("x")){

                    input.at(n).remove(0, 1);
                    x = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QChar("Y") || input.at(n).at(0) == QChar("y")){

                    input.at(n).remove(0, 1);
                    y = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QChar("Z") || input.at(n).at(0) == QChar("z")){

                    input.at(n).remove(0, 1);
                    z = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QChar("E") || input.at(n).at(0) == QChar("e")){

                    input.at(n).remove(0, 1);
                    e = input.at(n).toDouble();
                }

                else if(input.at(n).at(0) == QChar("S") || input.at(n).at(0) == QChar("s")){

                    input.at(n).remove(0, 1);
                    s = input.at(n).toInt();
                }

                else{

                    return 2;
                }
            }

            m_machineController->g0(x, y, z, e, s);

            printf("drive to X%e Y%e Z%e E%e with the endstop behavior %d\n", (double)(x), (double)(y), (double)(z), (double)(e), s);
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
    printf("commands for the Printersoftware:\n\n");

    printf("settings:\n\n");
    printf("\tsetfile   \t<filepath> sets the filepath\n");
    printf("\tsetline   \t<linenumber> sets the linenumber at which to start\n");

    printf("controls:\n\n");
    printf("\texit      \texits the Printersoftware and goes back to the terminal\n");
    printf("\tprint     \tstarts the print with the given parameters\n");
    printf("\tpause     \tpauses the print\n");
    printf("\tplay      \tcontinues the print\n");
    printf("\treset     \tresets all set values\n");

    printf("gcode commands:\n\n");
    printf("\tg0        \t[X<xvalue>] [Y<yvalue>] [Z<zvalue>] [E<evalue>] [S<svalue>] drives to the given position with top speed\n");
}
