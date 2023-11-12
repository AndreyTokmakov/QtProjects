//============================================================================
// Name        : Signals.cpp
// Created on  : 15.09.2021
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Signals C++ project
//============================================================================

#include <iostream>
#include <vector>
#include <string_view>


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
#include <QTextEdit>
#include <QApplication>
#include <QCheckBox>
#include <QFrame>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>

namespace Signals::Demo
{
    class MyApplication : public QApplication
    {
    public:
        MyApplication(int &argc, char **argv) : QApplication(argc, argv) {
            enableDarkMode();
        }

    private:
        void enableDarkMode()
        {
            qApp->setStyle("Fusion");
            auto darkPalette = QPalette();
            auto darkColor = QColor(48, 48, 48);
            auto disabledColor = QColor(127,127,127);
            darkPalette.setColor(QPalette::Window, darkColor);
            darkPalette.setColor(QPalette::WindowText, Qt::white);
            darkPalette.setColor(QPalette::Base, QColor(18,18,18));
            darkPalette.setColor(QPalette::AlternateBase, darkColor);
            darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
            darkPalette.setColor(QPalette::ToolTipText, Qt::white);
            darkPalette.setColor(QPalette::Text, Qt::white);
            darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
            darkPalette.setColor(QPalette::Button, darkColor);
            darkPalette.setColor(QPalette::ButtonText, Qt::white);
            darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
            darkPalette.setColor(QPalette::BrightText, Qt::red);
            darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::HighlightedText, Qt::black);
            darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

            qApp->setPalette(darkPalette);
            qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
        }
    };

    class Window : public QMainWindow
    {
    Q_OBJECT

    public:
        Window()
        {
            labelOne.move(10, 14);
            labelOne.setText("labelOne Text");

            labelTwo.move(10, 54);
            labelTwo.setText("labelTwo Text");

            buttonOne.move(110, 10);
            buttonOne.setText("Button One");

            buttonTwo.move(110, 50);
            buttonTwo.setText("Button Two");

            /** Handle 'buttonOne' click **/
            connect(&buttonOne, &QPushButton::clicked, [this] {
                qDebug() << "Handle 'Button One' click";
                labelOne.setText("New Text");
            });

            /** Handle 'buttonTwo' click **/
            QObject::connect(&buttonTwo, SIGNAL(clicked()), this, SLOT(updateText()));


            setCentralWidget(&frame);
            resize(600, 600);
        }

    private:
        QFrame frame;

        QLabel labelOne {&frame};
        QLabel labelTwo {&frame};

        QPushButton buttonOne {&frame};
        QPushButton buttonTwo {&frame};

    public slots:

        void updateText()
        {
            qDebug() << "Handle 'Button Two' click";
            labelTwo.setText("New Text 2");
        };
    };


    void test(int argc, char** argv)
    {
        MyApplication application(argc, argv);
        Window window;
        window.show();
        MyApplication::exec();
    }
};




int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    Signals::Demo::test(argc, argv);

   
    return EXIT_SUCCESS;
}

#include "main.moc"
