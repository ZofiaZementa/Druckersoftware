#include "commandlineui.h"

CommandlineUI::CommandlineUI(QObject *parent) : QObject(parent)
{

    m_settings = new QSettings(this);
}

//mainloop to provide a consistent commandline interface
void CommandlineUI::mainLoop()
{

    //variable to check wether to print the help or not or shut down the software down or not
    int check;

    //loop
    while(true){

        //prints linestart
        printf(">>>");
        //waits for user input
        scanf("%399s", *m_input);
        //carriage return & new line feed
        printf("\r\n");
        //checks for commands
        check = checkCommands();

        //checks wether to print the help, shutdown the software or do nothing
        //triggered if supposed to shut down the software
        if(check == 1){

            this->thread()->quit();
            return;
        }

        //triggered if supposed to print the help
        else if(check == 2){

            //prints the help
            printhelp();
        }
    }

}

//breaks up String at the spaces
QStringList CommandlineUI::breakUpString(QString string)
{

    //help-variable
    int help = -1;
    //stringlist to return
    QStringList retString;

    //loop to go through the single characters on by one
    for(int i = 0;i < string.count();i++){

        //checks if the current position i is a space and if the word is longer than 1 character
        //triggered if both is true
        if(string.at(i) == QString(" ") && i - help > 1){

            //appeds the word to the outputlist
            retString.append(string.mid((help + 1), (i - help - 1)));
            // sets help to i, so the search for the next word can begin
            help = i;
        }

        //triggered if the current position is a space
        else if(string.at(i) == QString(" ")){

            help = i;
        }
    }

    //checks if the string ends with a word or a space
    //triggered if it ends with a word, appends that word to the outputlist
    if(string.count() - 1 - help > 1){

        //appends the string to the outputlist
        retString.append(string.mid((help + 1), (string.count() - help - 1)));
    }

    //returns the outputlist
    return retString;
}

//checks the m_input for commands and executes them
int CommandlineUI::checkCommands()
{

    //breaks up the string
    QStringList input = breakUpString(QString(*m_input));

    //loop to go through allthe different components of the input
    for(int i = 0;i < input.count();i++){

        //checks the if it is a command
        //triggered if it is help
        if(input.at(i) == QString("help")){

            //prints help
            printhelp();
        }

        //triggered if it is exit
        else if(input.at(i) == QString("exit")){

            //returns a 1 so the loop knows it has to exit
            return 1;
        }

        //triggered if it is print
        else if(input.at(i) == QString("print")){

            //there to hold the return of the execution of print
            bool ret;
            //emits signal so that the MachineController starts printing
            emit machineControllerPrint(&ret);

            //checks wether the return of the execution of print was true
            //triggered if it is
            if(ret == true){

                //prints that the printer is printing
                printf("printing...\r\n");
                return 0;
            }

            //triggered if it isnt't
            else{

                //prints that the printer couldn't print
                printf("print couldnt be started\r\n");
                return 0;
            }
        }

        //triggered if it is pause
        else if(input.at(i) == QString("pause")){

            //there to hold the return of the execution of pause
            bool ret;
            //emits signal so that the MachineController pauses the print
            emit machineControllerPause(&ret);

            //checks wether the return of the execution of pause was true
            //triggered if it is
            if(ret == true){

                //prints that the print was paused
                printf("print paused\r\n");
                return 0;
            }

            //triggered if it isnt't
            else{

                //prints that the print couldn't be paused
                printf("print couldn't be paused\r\n");
                return 0;
            }
        }

        //triggered if it is play
        else if(input.at(i) == QString("play")){

            //there to hold the return of the execution of play
            bool ret;
            //emits signal so that the MachineController continues the print
            emit machineControllerPlay(&ret);

            //checks wether the return of the execution of play was true
            //triggered if it is
            if(ret == true){

                //prints that the print was continued
                printf("print continued\r\n");
                return 0;
            }

            //triggered if it isnt't
            else{

                //prints that the print couldn't continued
                printf("print couldn't be continued\r\n");
                return 0;
            }
        }

        //triggerd if it is reset
        else if(input.at(i) == QString("reset")){

            //emits signal so that the MachineController resets
            emit machineControllerReset();
            //prints that the values have been reset
            printf("all values reset\n");
            return 0;
        }

        //triggered if it is setfile
        else if(input.at(i) == QString("setfile")){

            //emits signal so that the MachineController sets the filepath to the given argument
            emit machineControllerSetFilePath(QUrl(input.at(i + 1)));
            //prints that the filepath was set to ...
            printf("Filepath set to %s\r\n", input.at(i + 1).toLatin1().data());
            return 0;
        }

        //triggered if it is setline
        else if(input.at(i) == QString("setline")){

            //emits signal so that the MachineController sets the line to the given argument
            emit machineControllerSetLine(input.at(i + 1).toInt());
            //prints that the line was set to ...
            printf("line set to %d\r\n", input.at(i + 1).toInt());
            return 0;
        }

        //triggered if it is setvalue
        else if(input.at(i) == QString("setvalue")){

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == i + 3){

                //checks the types
                //triggered if the type is int
                if(input.at(i + 3) == QString("int")){

                    bool ok;
                    //converts value from String to int and sets it at the key
                    m_settings->setValue(input.at(i + 1), input.at(i + 2).toInt(&ok, 10));
                    return 0;
                }

                //triggered if the type is qreal
                else if(input.at(i + 3) == QString("qreal")){

                    bool ok;
                    //converts value from String to double and sets it at the key
                    m_settings->setValue(input.at(i + 1), input.at(i + 2).toDouble(&ok));
                    return 0;
                }

                //triggered if the type is bool
                else if(input.at(i + 3) == QString("bool")){

                    //checks if the value is 1, true, 0 or false
                    //triggered if it is 1
                    if(input.at(i + 2) == QString("1")){

                        //sets true at the key
                        m_settings->setValue(input.at(i + 1), true);
                        return 0;
                    }

                    //triggered if it is true
                    else if(input.at(i + 2) == QString("true")){

                        //sets true at the key
                        m_settings->setValue(input.at(i + 1), true);
                        return 0;
                    }

                    //triggered if it is 0
                    else if(input.at(i + 2) == QString("0")){

                        //sets false at the key
                        m_settings->setValue(input.at(i + 1), false);
                        return 0;
                    }

                    //triggered if it is false
                    else if(input.at(i + 2) == QString("false")){

                        //sets false at the key
                        m_settings->setValue(input.at(i + 1), false);
                        return 0;
                    }

                    //triggered if it is something else
                    else{

                        //returns 2 so that the loop prints the help
                        return 2;
                    }
                }

                //triggered if the type is invalid
                else{

                    //returns 2 so that the loop prints the help
                    return 2;
                }
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }
        }

        //triggered if it is value
        else if(input.at(i) == QString("value")){

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == i + 1){

                //prints the value at key
                printf("Value: %s\r\n", m_settings->value(input.at(i + 1)).toByteArray().data());
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }
        }

        //triggered if it is write
        else if(input.at(i) == QString("iowrite")){

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == i + 3){

                //there for the conversion from string to int
                bool ok;
                //there to hold the return of the execution of write
                bool ret;
                //emits signal so that the IOController writes the values
                emit iOControllerWrite(input.at(i), input.at(i).toInt(&ok, 10), &ret);

                //checks wether the return of the execution of write and the conversion from string to int were true
                //triggered if it is
                if(ret == true && ok == true){

                    return 1;
                }

                //triggered if it is
                else{

                    //returns 2 so that the loop prints the help
                    return 2;
                }
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }
        }

        //triggered if it is read
        else if(input.at(i) == QString("ioread")){

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == i + 2){

                //there to hold the return of the execution of read
                int ret;
                //emits signal so that the IOController reads the values
                emit iOControllerRead(input.at(i), &ret);

                //prints the value
                printf("value: %d\r\n", ret);
                return 1;
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }
        }

        //triggered if it is swrite
        else if(input.at(i) == QString("swrite")){

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == i + 1){

                //emits signal so that the SerialInterface sends the text
                emit serialInterfaceSend(input.at(i + 1));
                return 0;
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }
        }

        //triggered if it is sconnect
        else if(input.at(i) == QString("sconnect")){

            emit serialInterfaceConnect();
            return 0;
        }

        //triggered if it is sdconnect
        else if(input.at(i) == QString("sdconnect")){

            emit serialInterfaceDisconnect();
            return 0;
        }

        //triggered if it is addlog
        else if(input.at(i) == QString("addlog")){

            //variable for the types of the log
            QList<int> types;
            //variable for the logname which to add
            QString logName;
            //there for the conversion from string to int
            bool ok;

            //checks if there are enough arguments
            //triggered if there are
            if(input.count() >= 3){

                //sets the the logname to the first argument
                logName = input.at(1);

                //loop to add all the types to the typeslist
                for(int n = 2;n < input.count();n++){

                    //appends type at the current position n to the list
                    types.append(input.at(n).toInt(&ok, 10));

                    //checks if the conversion from string to int was successfull
                    //triggerd if it isn't
                    if(ok == false){

                        //returns 2 so that the loop prints the help
                        return 2;
                    }
                }
            }

            //triggered if there aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }

            //emits signal so that the Logger adds the log
            emit loggerAddLog(types, logName);
        }

        //triggerd if it is editlog
        else if(input.at(i) == QString("editlog")){

            //variable for the types of the log
            QList<int> types;
            //variable for the logname which to edit
            QString logName;
            //there for the conversion from string to int
            bool ok;

            //checks if there are enough arguments
            //triggered if there are
            if(input.count() >= 3){

                //sets the the logname to the first argument
                logName = input.at(1);

                //loop to add all the types to the typeslist
                for(int n = 2;n < input.count();n++){

                    //appends type at the current position n to the list
                    types.append(input.at(n).toInt(&ok, 10));

                    //checks if the conversion from string to int was successfull
                    //triggerd if it isn't
                    if(ok == false){

                        //returns 2 so that the loop prints the help
                        return 2;
                    }
                }
            }

            //triggered if there aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }

            //emits signal so that the Logger edits the log
            emit loggerEditLog(types, logName);
        }

        //triggerd if it is dellog
        else if(input.at(i) == QString("dellog")){

            //variable for the logname which to delete
            QString logName;

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == 2){

                //sets logName to the first argument
                logName = input.at(i);
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }

            //emits signal so that the Logger deletes the log
            emit loggerDeleteLog(logName);
        }

        //triggerd if it is setlfpath
        else if(input.at(i) == QString("setlfpath")){

            //variable for the folderpath which to set
            QString folderPath;

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == 2){

                //sets folderpath to the first argument
                folderPath = input.at(i);
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }

            //emits signal so that the Logger sets the folderpath
            emit loggerSetLogFolderPath(folderPath);
        }

        //triggerd if it is chnglfpath
        else if(input.at(i) == QString("chnglfpath")){

            //variable for the folderpath which to change
            QString folderPath;

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == 2){

                //sets folderpath to the first argument
                folderPath = input.at(i);
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }

            //emits signal so that the Logger changes the folderpath
            emit loggerChangeLogFolderPath(folderPath);
        }

        //triggerd if it is lfpath
        else if(input.at(i) == QString("lfpath")){

            //there for the output
            QByteArray output;

            //checks if all the arguments are there
            //triggered if they are
            if(input.count() == 2){

                //there to hold the return of the execution of write
                QString ret;
                //emits signal so that the Logger returns the folderpath
                emit loggerLogFolderPath(&ret);
                //converts the returned string to a QByteArray
                output = ret.toLatin1();
            }

            //triggered if they aren't
            else{

                //returns 2 so that the loop prints the help
                return 2;
            }

            //prints that the folder path is ...
            printf("log folder path: %s", output.data());
        }

        //triggerd if it is g0
        else if(input.at(i) == QString("g0")){

            //variable for the x-axis coordinate
            qreal x = 0.0;
            //variable for the y-axis coordinate
            qreal y = 0.0;
            //variable for the z-axis coordinate
            qreal z = 0.0;
            //variable for the x-extruder coordinate
            qreal e = 0.0;
            //variable for the enstop behavior
            int s = 0;

            //loop to go through all the arguments
            for(int n = i;n < input.count();n++){

                //checks what the argument is
                //triggered if it is X
                if(input.at(n).at(0) == QString("X") || input.at(n).at(0) == QString("x")){

                    //removes the X from th argument
                    input[n].remove(0, 1);
                    //converts the argument into a double and writes it into x
                    x = input.at(n).toDouble();
                }

                //triggered if it is Y
                else if(input.at(n).at(0) == QString("Y") || input.at(n).at(0) == QString("y")){

                    //removes the Y from th argument
                    input[n].remove(0, 1);
                    //converts the argument into a double and writes it into y
                    y = input.at(n).toDouble();
                }

                //triggered if it is Z
                else if(input.at(n).at(0) == QString("Z") || input.at(n).at(0) == QString("z")){

                    //removes the Z from th argument
                    input[n].remove(0, 1);
                    //converts the argument into a double and writes it into z
                    z = input.at(n).toDouble();
                }

                //triggered if it is E
                else if(input.at(n).at(0) == QString("E") || input.at(n).at(0) == QString("e")){

                    //removes the E from th argument
                    input[n].remove(0, 1);
                    //converts the argument into a double and writes it into e
                    e = input.at(n).toDouble();
                }

                //triggered if it is S
                else if(input.at(n).at(0) == QString("S") || input.at(n).at(0) == QString("s")){

                    //removes the S from th argument
                    input[n].remove(0, 1);
                    //converts the argument into a int and writes it into s
                    s = input.at(n).toInt();
                }

                //triggerd if it is none of the above
                else{

                    //returns 2 so that the loop prints the help
                    return 2;
                }
            }

            //emits signal so that the MachineController excutes the g0
            emit machineControllerG0(x, y, z, e, -1.0, s);

            //prints that the MachineController executed g0 with the given arguments
            printf("drive to X%e Y%e Z%e E%e with the endstop behavior %d\r\n", (double)(x), (double)(y), (double)(z), (double)(e), s);
            return 0;
        }

        //triggerd if it is none of the above
        else{

            //returns 2 so that the loop prints the help
            return 2;
        }


    }

    //returns 2 so that the loop prints the help
    return 2;
}

//prints the help
void CommandlineUI::printhelp()
{
    printf("commands for the Printersoftware:\r\n\n\n");

    printf("help:\r\n\n");
    printf("\thelp      \tprints this help\r\n");

    printf("\ncontrols:\r\n\n");
    printf("\texit      \texits the Printersoftware and goes back to the terminal\r\n");
    printf("\tprint     \tstarts the print with the given parameters\r\n");
    printf("\tpause     \tpauses the print\r\n");
    printf("\tplay      \tcontinues the print\r\n");
    printf("\treset     \tresets all set values\r\n");

    printf("settings:\r\n\n");
    printf("\tsetfile   \t<filepath> sets the filepath\r\n");
    printf("\tsetline   \t<linenumber> sets the linenumber at which to start\r\n");
    printf("\tsetvalue  \t<key> <value> <type> sets the value pf the key to value of type\r\n");
    printf("\tvalue     \t<key> reads the value of the key and prints it\r\n");

    printf("\nio controls:\r\n\n");
    printf("\tiowrite   \t<pinName> <value>\r\n");
    printf("\tioread    \t<pinName>\r\n");

    printf("\nserial controls:\r\n\n");
    printf("\tswrite    \t<string to write> writes string into the serialinterface\r\n");
    printf("\tsconnect  \topens connection of the serialinterface\r\n");
    printf("\tsdconnect \tclosesconnection of the serialinterface\r\n");

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
