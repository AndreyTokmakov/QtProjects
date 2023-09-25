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

namespace Threads::Pool
{
    class Work : public QRunnable {
    public:
        void run() override {
            qDebug() << "Hello from thread " << QThread::currentThread();
        }
    };

    int Test(int argc, char *argv[])
    {
        QCoreApplication app(argc, argv);
        Work work;
        work.setAutoDelete(false);
        QThreadPool *threadPool = QThreadPool::globalInstance();
        threadPool->start(&work);
        qDebug() << "hello from GUI thread " << QThread::currentThread();
        threadPool->waitForDone();
        return EXIT_SUCCESS;
    }
}

namespace Threads::ClockGUI
{

    class ClockThread : public QThread
    {
    Q_OBJECT
    signals:
        void sendTime(QString time);

    private:
        void run() override
        {
            QTimer timer;
            connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
            timer.setInterval(10);
            timer.start();   // puts one event in the threads event queue
            exec();
            timer.stop();
        }

        QString m_lastTime;

    private slots:

        void timerHit()
        {
            QString newTime= QDateTime::currentDateTime().toString("ddd MMMM d yy, hh:mm:ss");
            if(m_lastTime != newTime ){
                m_lastTime = newTime;
                emit sendTime(newTime) ;
            }
        }
    };

    int runClock(int argc, char *argv[])
    {
        QApplication app(argc, argv);
        QWidget widget;
        QLabel *label = new QLabel;
        QHBoxLayout *layout = new QHBoxLayout(&widget);
        layout->addWidget(label);
        widget.setWindowTitle("clock");

        ClockThread clockThread;
        QObject::connect(&clockThread,
                         SIGNAL(sendTime(QString)),
                         label,
                         SLOT(setText(QString)),
                         Qt::QueuedConnection);
        clockThread.start();
        widget.show();
        QApplication::exec();

        clockThread.quit();
        clockThread.wait();

        return EXIT_SUCCESS;
    }
}

/*
namespace Threads::PermanentThread
{
    int main(int argc, char *argv[])
    {
        QCoreApplication app(argc, argv);
        Thread thread;
        qDebug() << "main thread ID: " << app.thread()->currentThreadId();
        WorkerObject *worker = new WorkerObject;
        thread.launchWorker(worker);
        QMetaObject::invokeMethod(worker, "doWork", Qt::QueuedConnection);
        QMetaObject::invokeMethod(worker, "startPolling",  Qt::QueuedConnection,  Q_ARG(int, 500));
        //let application produce output for 3 seconds and quit
        QTimer::singleShot(3000, &app, SLOT(quit()));
        app.exec();
        thread.stop();
        thread.wait();
        delete worker;
        return 0;
    }
}
*/


void Threads::TestAll(int argc, char *argv[])
{
    DemoOne::SimpleThread(argc, argv);
    // DemoTwo::Test(argc, argv);

    // Pool::Test(argc, argv);

    // ClockGUI::runClock(argc, argv);
}

#include "Threads.moc"
