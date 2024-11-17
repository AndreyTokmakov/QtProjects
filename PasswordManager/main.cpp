/**============================================================================
Name        : PasswordManager.cpp
Created on  : 17.11.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : PasswordManager.cpp
============================================================================**/

#include <iostream>
#include <string_view>
#include <vector>



#include <QtCore>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>
#include <QFrame>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QStyle>
#include <QStandardItem>
#include <QHeaderView>
#include <QTreeView>
#include <QLabel>
#include <QProgressBar>

class Application : public QApplication
{
public:
    Application(int &argc, char **argv) : QApplication(argc, argv) {
        enableDarkMode();
    }

private:
    void enableDarkMode()
    {
#ifndef Q_OS_MACOS
        qApp->setStyle("Fusion");
        QPalette darkPalette = QPalette();
        const QColor darkColor = QColor(65, 65, 65);
        const QColor baseColor = QColor(48,48,48);
        const QColor disabledColor = QColor(127,127,127);

        darkPalette.setColor(QPalette::Window, darkColor);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, baseColor);
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

    Window()
    {
        // TODO: Refactor this
        QLabel *statusLabel = new QLabel(this);

        QProgressBar *statusProgressBar = new QProgressBar(this);

        // statusProgressBar->move(50, 110);
        // statusProgressBar->resize(100, 25);
        statusProgressBar->setMinimum(0);
        statusProgressBar->setMaximum(100);
        statusProgressBar->setValue(50);
        statusProgressBar->setTextVisible(false);
        statusProgressBar->setToolTip(QString("Blah-Blah-Blah"));

        //statusProgressBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

        statusLabel->setText("Status Label");

        /** Add status bar: **/
        // status->showMessage("Status bar...");
        status->addPermanentWidget(statusLabel);
        status->addPermanentWidget(statusProgressBar);


        QMenu* menuFile = menu->addMenu("&File");
        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_FileIcon),"&New",this, &Window::OnMenuItemClick);
        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_DirOpenIcon), "&Open",this, &Window::OnMenuItemClick);

        menuFile->addSeparator();

        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_DialogSaveButton),"&Save", this, &Window::OnMenuItemClick);
        menuFile->addAction("Save &As...", this,&Window::OnMenuItemClick);

        menuFile->addSeparator();

        menuFile->addAction("&Exit", this,&Window::OnMenuItemClick);

        QMenu* menuEdit = menu->addMenu("&Edit");
        menuEdit->addAction("&Undo", this,&Window::OnMenuItemClick);
        menuEdit->addAction("&Redo", this,&Window::OnMenuItemClick);

        menuEdit->addSeparator();

        menuEdit->addAction(QIcon::fromTheme("edit-cut"), "&Cut",this, &Window::OnMenuItemClick);
        menuEdit->addAction(QIcon::fromTheme("edit-copy"), "&Copy",this, &Window::OnMenuItemClick);
        menuEdit->addAction(QIcon::fromTheme("edit-paste"), "&Paste",this, &Window::OnMenuItemClick);

        menuEdit->addSeparator();

        menuEdit->addAction("Select &All", this,&Window::OnMenuItemClick);

        QMenu* menuHelp = menu->addMenu("&Help");
        menuHelp->addAction("&About", this, &Window::OnMenuHelpAboutClick);


        setCentralWidget(&frame);
        setWindowTitle("Tree view example");
        //resize(300, 300);

        // thread.start();
        // thread.wait();
    }

private:
    void OnMenuItemClick() {
        status->showMessage("Status bar...... | ");
    }

    void OnMenuHelpAboutClick() {
        QMessageBox::about(this, "About", "Simple password manager app"
                                          ".\nVersion 1.0.0\n\n@ 2024 by Andrei Tokmakov.");
    }

private:
    QFrame frame;
    QVBoxLayout layout { &frame };
    QStandardItemModel model;

    const std::unique_ptr<QStatusBar> status { statusBar() };
    const std::unique_ptr<QMenuBar> menu { menuBar() };
};


void runApp(int argc, char **argv)
{
    Application application(argc, argv);
    Window window;
    window.resize(1200, 800);
    window.show();
    QApplication::exec();
}


int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    runApp(argc, argv);
   
    return EXIT_SUCCESS;
}
