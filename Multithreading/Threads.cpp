/**============================================================================
Name        : Threads.cpp
Created on  : 18.06.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Threads
============================================================================**/

#include "Threads.h"

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

// https://qthelper.ru/qthread/

namespace Threads::DemoOne
{
    class MyThread : public QThread
    {
    Q_OBJECT

    public:
        explicit MyThread(QString s) : name(std::move(s)) {
        }

        void run() override
        {
            for(int i = 1; i <= 5; ++i) {
                qDebug() << this->name << " " << i;
                //std::cout << this->name.toStdString() << " " << i << std::endl;
            }
        }

    private:
        QString name;
    };

    int SimpleThread(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);
        std::array<MyThread, 3> workers { MyThread {"A" }, MyThread {"B" }, MyThread {"C" }};

        for (auto& T: workers)
            T.start();
        for (auto& T: workers)
            T.wait();

        return QCoreApplication::exec();
    }
}

namespace Threads::DemoTwo
{
    class HelloThread : public QThread
    {
    Q_OBJECT
    private:
        void run() override
        {
            qDebug() << "hello from worker thread " << thread()->currentThreadId();
        }
    };

    void Test(int argc, char *argv[])
    {
        QCoreApplication app(argc, argv);
        HelloThread thread;
        thread.start();
        qDebug() << "hello from GUI thread " << app.thread()->currentThreadId();
        thread.wait();  // do not exit before the thread is completed!
    }
}

void Threads::TestAll(int argc, char *argv[])
{
    // DemoOne::SimpleThread(argc, argv);
    DemoTwo::Test(argc, argv);
}

#include "Threads.moc"
