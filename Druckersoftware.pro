#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T14:11:32
#
#-------------------------------------------------

QT       += core gui serialport svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Druckersoftware
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    machinecontroller.cpp \
    gcodereader.cpp \
    serialinterface.cpp \
    motorcontroller.cpp \
    Logging/logfile.cpp \
    Logging/logger.cpp \
    IO/fancontroller.cpp \
    IO/heatingcontroller.cpp \
    IO/iocontroller.cpp \
    IO/sensorlistener.cpp \
    IO/iomainloop.cpp \
    IO/lightingcontroller.cpp \
    UI/CMD/commandlineui.cpp \
    UI/CMD/cmduiiocontrollerinterface.cpp \
    UI/CMD/cmduiloggerinterface.cpp \
    UI/CMD/cmduimachinecontrollerinterface.cpp \
    UI/GUI/controlwindow.cpp \
    UI/GUI/menubar.cpp \
    UI/GUI/homescreen.cpp \
    UI/GUI/InfoScreen/infogcodescreen.cpp \
    UI/GUI/InfoScreen/infoheatingscreen.cpp \
    UI/GUI/InfoScreen/infomiscscreen.cpp \
    UI/GUI/InfoScreen/infomotorscreen.cpp \
    UI/GUI/InfoScreen/infoscreen.cpp \
    UI/GUI/InfoScreen/infoserialscreen.cpp \
    UI/GUI/InfoScreen/InfoIOScreen/infoiocorescreen.cpp \
    UI/GUI/InfoScreen/InfoIOScreen/infoioscreen.cpp \
    UI/GUI/InfoScreen/InfoIOScreen/infoiodigitalscreen.cpp \
    UI/GUI/InfoScreen/InfoIOScreen/infoiortdscreen.cpp \
    UI/GUI/errorscreen.cpp \
    UI/GUI/warningbar.cpp \
    UI/GUI/InfoScreen/InfoIOScreen/infoioanalogoutscreen.cpp \
    UI/GUI/InfoScreen/InfoIOScreen/infoioanaloginscreen.cpp \
    UI/GUI/startaprintscreen.cpp \
    UI/GUI/manualscreen.cpp \
    UI/GUI/sysactionsscreen.cpp \
    UI/GUI/spinbox.cpp \
    UI/GUI/LogScreen/logscreen.cpp \
    UI/GUI/SettingsScreen/settingsscreen.cpp \
    UI/GUI/LogScreen/logeditlogscreen.cpp \
    UI/GUI/LogScreen/logreadlogscreen.cpp \
    UI/GUI/SettingsScreen/settingsloggingscreen.cpp \
    UI/GUI/SettingsScreen/settingsgeneralscreen.cpp \
    UI/GUI/SettingsScreen/settingsserialscreen.cpp \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguiscreen.cpp \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingscreen.cpp \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsioscreen.cpp \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorscreen.cpp \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorgeneralscreen.cpp \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorxaxisscreen.cpp \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotoryaxisscreen.cpp \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorzaxisscreen.cpp \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorextruderscreen.cpp \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiosensorscreen.cpp \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsioheatingscreen.cpp \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiolightingscreen.cpp \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiomiscscreen.cpp \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatinghotendscreen.cpp \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingbedscreen.cpp \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguimanualscreen.cpp \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguispinboxscreen.cpp

HEADERS += \
    machinecontroller.h \
    gcodereader.h \
    serialinterface.h \
    motorcontroller.h \
    Logging/logfile.h \
    Logging/logger.h \
    IO/fancontroller.h \
    IO/heatingcontroller.h \
    IO/iocontroller.h \
    IO/piControl.h \
    IO/sensorlistener.h \
    IO/iomainloop.h \
    IO/lightingcontroller.h \
    UI/CMD/commandlineui.h \
    UI/CMD/cmduiiocontrollerinterface.h \
    UI/CMD/cmduiloggerinterface.h \
    UI/CMD/cmduimachinecontrollerinterface.h \
    UI/GUI/controlwindow.h \
    UI/GUI/menubar.h \
    UI/GUI/homescreen.h \
    UI/GUI/InfoScreen/infogcodescreen.h \
    UI/GUI/InfoScreen/infoheatingscreen.h \
    UI/GUI/InfoScreen/infomiscscreen.h \
    UI/GUI/InfoScreen/infomotorscreen.h \
    UI/GUI/InfoScreen/infoscreen.h \
    UI/GUI/InfoScreen/infoserialscreen.h \
    UI/GUI/InfoScreen/InfoIOScreen/infoiocorescreen.h \
    UI/GUI/InfoScreen/InfoIOScreen/infoioscreen.h \
    UI/GUI/InfoScreen/InfoIOScreen/infoiodigitalscreen.h \
    UI/GUI/InfoScreen/InfoIOScreen/infoiortdscreen.h \
    UI/GUI/errorscreen.h \
    UI/GUI/warningbar.h \
    UI/GUI/InfoScreen/InfoIOScreen/infoioanalogoutscreen.h \
    UI/GUI/InfoScreen/InfoIOScreen/infoioanaloginscreen.h \
    UI/GUI/startaprintscreen.h \
    UI/GUI/manualscreen.h \
    UI/GUI/sysactionsscreen.h \
    UI/GUI/spinbox.h \
    UI/GUI/LogScreen/logscreen.h \
    UI/GUI/SettingsScreen/settingsscreen.h \
    UI/GUI/LogScreen/logeditlogscreen.h \
    UI/GUI/LogScreen/logreadlogscreen.h \
    UI/GUI/SettingsScreen/settingsloggingscreen.h \
    UI/GUI/SettingsScreen/settingsgeneralscreen.h \
    UI/GUI/SettingsScreen/settingsserialscreen.h \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguiscreen.h \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingscreen.h \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsioscreen.h \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorscreen.h \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorgeneralscreen.h \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorxaxisscreen.h \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotoryaxisscreen.h \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorzaxisscreen.h \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorextruderscreen.h \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiosensorscreen.h \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsioheatingscreen.h \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiolightingscreen.h \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiomiscscreen.h \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatinghotendscreen.h \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingbedscreen.h \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguimanualscreen.h \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguispinboxscreen.h

FORMS += \
    UI/GUI/controlwindow.ui \
    UI/GUI/menubar.ui \
    UI/GUI/homescreen.ui \
    UI/GUI/InfoScreen/infogcodescreen.ui \
    UI/GUI/InfoScreen/infoheatingscreen.ui \
    UI/GUI/InfoScreen/infomiscscreen.ui \
    UI/GUI/InfoScreen/infomotorscreen.ui \
    UI/GUI/InfoScreen/infoscreen.ui \
    UI/GUI/InfoScreen/infoserialscreen.ui \
    UI/GUI/InfoScreen/InfoIOScreen/infoiocorescreen.ui \
    UI/GUI/InfoScreen/InfoIOScreen/infoioscreen.ui \
    UI/GUI/InfoScreen/InfoIOScreen/infoiodigitalscreen.ui \
    UI/GUI/InfoScreen/InfoIOScreen/infoiortdscreen.ui \
    UI/GUI/errorscreen.ui \
    UI/GUI/warningbar.ui \
    UI/GUI/InfoScreen/InfoIOScreen/infoioanalogoutscreen.ui \
    UI/GUI/InfoScreen/InfoIOScreen/infoioanaloginscreen.ui \
    UI/GUI/startaprintscreen.ui \
    UI/GUI/manualscreen.ui \
    UI/GUI/sysactionsscreen.ui \
    UI/GUI/spinbox.ui \
    UI/GUI/LogScreen/logscreen.ui \
    UI/GUI/SettingsScreen/settingsscreen.ui \
    UI/GUI/LogScreen/logeditlogscreen.ui \
    UI/GUI/LogScreen/logreadlogscreen.ui \
    UI/GUI/SettingsScreen/settingsloggingscreen.ui \
    UI/GUI/SettingsScreen/settingsgeneralscreen.ui \
    UI/GUI/SettingsScreen/settingsserialscreen.ui \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguiscreen.ui \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingscreen.ui \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsioscreen.ui \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorscreen.ui \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorgeneralscreen.ui \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorxaxisscreen.ui \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotoryaxisscreen.ui \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorzaxisscreen.ui \
    UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorextruderscreen.ui \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiosensorscreen.ui \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsioheatingscreen.ui \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiolightingscreen.ui \
    UI/GUI/SettingsScreen/SettingsIOScreen/settingsiomiscscreen.ui \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatinghotendscreen.ui \
    UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingbedscreen.ui \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguimanualscreen.ui \
    UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguispinboxscreen.ui

RESOURCES += \
    icons.qrc \
    UI/Fonts/fonts.qrc
