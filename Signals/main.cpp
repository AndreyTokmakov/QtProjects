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

/*
class MyLabel : public QLabel
{
public:
    explicit MyLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags()):
            QLabel(text, parent, f) {
    }

Q_OBJECT
public slots:
    void setCustomText() {
        this->setText("received a signal");
    }
};
*/

void windowWithButton(int argc,  char** argv)
{
    QApplication app(argc, argv);
    QWidget window;

    QPushButton btnQuit("Quit", &window);
    btnQuit.setFont(QFont("Times", 18, QFont::Bold));
    btnQuit.setGeometry(30, 20, 80, 40);

    QPushButton btnSerTest("Set Text", &window);
    btnSerTest.setFont(QFont("Times", 18, QFont::Bold));
    btnSerTest.setGeometry(30, 80, 120, 40);

    QLabel textField("Some initial text", &window);
    textField.setGeometry(180, 80, 120, 40);


    QObject::connect(&btnSerTest, SIGNAL(clicked()), &textField, SLOT(setText("asasasa")));
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
