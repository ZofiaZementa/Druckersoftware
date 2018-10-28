# Druckersoftware

This software is made to run on the controller of the 3d-printer of the P-Seminar at Carl-Spitzweg-Gymnasium. The Controller is a KUNBUS RevolutionPi with a DIO & AIO module and it is made to control 4 Nanotec PD2-N41 steppermotors, as well as some heating elements and LED's. At the moment the project consists of the main controller, the gui and the commandprompt but there is a plan for a webcontroller to be added later. It is written in c++ using the Qt framework and is made to only run on linux.

## Getting Started

Since this project is not even at version 1.0 yet, you'll have to build it yourself. First download this project. You'll also need to install Qt 5.6.0 or newer, the GNU g++ compiler and make. To get these, see how to install them on your os. To build the software, run

```
qmake -config debug
make
```

### Running Druckersoftware

You can either run it with a gui

```
./Druckersoftware
```

or without one, which is recommended, since the gui doesn't have any function yet.

```
./Druckersoftware -nG
```

Type in `help` for more information.

## Setup of Druckersoftware

To setup Druckersoftware, you need to first specify the serialport on which the motors are connected and the baudrate to use

```
>>>svalue serialinterface/portname ttyUSB0 QString
>>>svalue serialinterface/baudrate 115200 int
>>>sdconnect
>>>sconnect
```

Of course we use examples here, the values might be different for you. Now you can set all the values for the motors and the heatingelements, please consider the manual for that. After that we should be ready to go, you can start the print by setting the file you want to print and start it

```
>>>setfile /media/usb/example.gcode
>>>print
```

But since this is still a pre-release version, it probably wont work, so be careful.

## Authors

* **Maximilian Fischer** - [xxfischixx2](https://github.com/xxfischixx2)
