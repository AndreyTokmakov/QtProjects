/**============================================================================
Name        : StatusBar.cpp
Created on  : 17.11.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : StatusBar.cpp
============================================================================**/

#include "StatusBar.h"

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QStatusBar>
#include <QHBoxLayout>

class Statusbar : public QMainWindow
{

public:
    Statusbar(QWidget *parent = nullptr);

private slots:
    void OnOkPressed();
    void OnApplyPressed();

private:
    QPushButton *okBtn;
    QPushButton *aplBtn;
};


Statusbar::Statusbar(QWidget *parent): QMainWindow(parent) {

    auto *frame = new QFrame(this);
    setCentralWidget(frame);

    auto *hbox = new QHBoxLayout(frame);

    okBtn = new QPushButton("OK", frame);
    hbox->addWidget(okBtn, 0, Qt::AlignLeft | Qt::AlignTop);

    aplBtn = new QPushButton("Apply", frame);
    hbox->addWidget(aplBtn, 1, Qt::AlignLeft | Qt::AlignTop);

    statusBar();

    connect(okBtn, &QPushButton::clicked, this, &Statusbar::OnOkPressed);
    connect(aplBtn, &QPushButton::clicked, this, &Statusbar::OnApplyPressed);
}

void Statusbar::OnOkPressed() {

    statusBar()->showMessage("OK button pressed", 2000);
}

void Statusbar::OnApplyPressed() {

    statusBar()->showMessage("Apply button pressed", 2000);
}


void StatusBar::TestAll([[maybe_unused]] int argc,
                          [[maybe_unused]] char** argv)
{
    QApplication app(argc, argv);

    Statusbar window;

    window.resize(300, 200);
    window.setWindowTitle("QStatusBar");
    window.show();

    app.exec();
}
