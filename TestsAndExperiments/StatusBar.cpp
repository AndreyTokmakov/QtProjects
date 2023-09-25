/**============================================================================
Name        : StatusBar.cpp
Created on  : 24.09.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : StatusBar.cpp
============================================================================**/

#include "StatusBar.h"

#include <iostream>
#include <utility>

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
#include <QProgressBar>

namespace StatusBar::Simple
{
    class Window : public QMainWindow
    {
    public:
        Window() {
            QStatusBar* statusBar = this->statusBar();
            statusBar->showMessage("Status bar...");

            setCentralWidget(&frame);
            setWindowTitle("Status bar example");
            resize(300, 300);
        }

    private:
        QFrame frame;
    };

    void run(int argc, char *argv[])
    {
        QApplication application(argc, argv);
        Window window1;
        window1.show();
        QApplication::exec();
    }
}



namespace StatusBar::DarkMode
{
    class Application : public QApplication
    {
    public:
        Application(int &argc, char **argv) : QApplication(argc, argv) {
            enableDarkMode();
        }

    private:
        void enableDarkMode() {
#ifndef Q_OS_MACOS
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
#endif
        }
    };

    class Window : public QMainWindow
    {
    public:
        Window() {
            QStatusBar* statusBar = this->statusBar();
            statusBar->showMessage("Status bar...");

            QLabel *statusLabel = new QLabel(this);

            QProgressBar *statusProgressBar = new QProgressBar(this);

            // statusProgressBar->move(50, 110);
            // statusProgressBar->resize(100, 25);
            statusProgressBar->setMinimum(0);
            statusProgressBar->setMaximum(100);
            statusProgressBar->setValue(50);
            statusProgressBar->setTextVisible(false);
            statusProgressBar->setToolTip(QString("Blah-Blah-Blah"));

            // statusProgressBar->setGeometry(0,0, 100,10);

            // statusProgressBar->set


            //statusProgressBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

            statusLabel->setText("Status Label");

            /** Add status bar: **/
            // status->showMessage("Status bar...");
            statusBar->addPermanentWidget(statusLabel);
            statusBar->addPermanentWidget(statusProgressBar);


            setCentralWidget(&frame);
            setWindowTitle("Status bar example");
            resize(300, 300);
        }

    private:
        QFrame frame;
    };

    void run(int argc, char *argv[])
    {
        Application application(argc, argv);
        Window window;
        window.show();
        DarkMode::Application::exec();
    }
}

void StatusBar::TestAll(int argc, char *argv[])
{
    // Simple::run(argc, argv);
    DarkMode::run(argc, argv);
}