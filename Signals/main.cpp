//============================================================================
// Name        : Signals.cpp
// Created on  : 15.09.2021
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Signals C++ project
//============================================================================

#include <iostream>


#include <QCoreApplication>
#include <QFrame>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>
#include <QtCore>
#include <QWidget>
#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QStyle>


void windowWithButton(int argc,  char** argv)
{
    QApplication app(argc, argv);
    QWidget window;

    QPushButton btnQuit("Quit", &window);
    btnQuit.setFont(QFont("Times", 18, QFont::Bold));
    btnQuit.setGeometry(150, 80, 100, 40);
    QObject::connect(&btnQuit, SIGNAL(clicked()), &app, SLOT(quit()));

    window.resize(400, 200);
    window.show();

    QApplication::exec();
}


int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    windowWithButton(argc, argv);

   
    return EXIT_SUCCESS;
}
