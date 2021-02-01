# Design Pattern "Command"

## Problem statement

You need to develop an application that displays a list of one's company business units and its employees in a *tree view*. The list must be loaded from an **xml** file. 

The program should provide the ability to *(add / delete / edit)* the name and structure of departments and edit employees in them. The program must provide the ability to *undo* and *revert* changes. When developing, you need to use design patterns (an xml file with data is attached to the task).

Employee fields:
- Full Name (Surname, Name, Middle Name)
- Position
- Salary (which is integer)

Division fields:
- Name
- Number of employees
- Average salary

## How to build

    mkdir build
    cd build
    cmake ..
    make
    cd ..

## How to run

    ./build/command
