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
#include <filesystem>
#include <fstream>


#include <QTextEdit>
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
#include <QFileDialog>

#include "FileUtilities.h"

class DarkThemeApplication final : public QApplication
{
public:
    DarkThemeApplication(int &argc, char **argv) : QApplication(argc, argv) {
        enableDarkMode();
    }

private:

    static QColor makeColor(const int32_t red = 0, const int32_t green = 0, const int32_t blue = 0) noexcept
    {
        return QColor(red, green, blue);
    }

    static void enableDarkMode()
    {
#ifndef Q_OS_MACOS

        qApp->setStyle("Fusion");
        QPalette darkPalette = QPalette();
        const QColor darkColor = makeColor(65, 65, 65);
        const QColor baseColor = makeColor(0, 43, 54);
        const QColor disabledColor = makeColor(127,127,127);
        const QColor linksColor = makeColor(42, 130, 218);

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
        darkPalette.setColor(QPalette::Link, linksColor);
        darkPalette.setColor(QPalette::Highlight, linksColor);
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

        qApp->setPalette(darkPalette);
        qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
#endif
    }
};


class PasswordManagerWindow final : public QMainWindow
{
    const std::unique_ptr<QMenuBar> menu { menuBar() };
    const std::unique_ptr<QTextEdit> textEditField = std::make_unique<QTextEdit>(this);
    const std::unique_ptr<QStatusBar> status { statusBar() };
    const std::unique_ptr<QLabel> statusLabel = std::make_unique<QLabel>(this);

public:

    PasswordManagerWindow()
    {
        this->resize(1200, 800);

        createMenu();
        setCentralWidget(textEditField.get());

        statusLabel->setText("Status Label");
        status->showMessage("Status bar... | On the LEFT");
        status->addPermanentWidget(statusLabel.get());




        // INFO WordWrap
        // textEditField->setWordWrapMode(QTextOption::WordWrap);
        // textEditField->setReadOnly(true);
        // textEditField->document()->find(text, document->textCursor(), flags);
        // textEditField->setStyleSheet("font: 24pt ;");

        // QTextEdit::ExtraSelection selection;
        // selection.format.setBackground(Qt::yellow);
        // selection.format.setForeground(Qt::black);

        // textEditField->installEventFilter(this);


        // setMenuBar(menu.get());
        // setStatusBar(status.get());

        showMaximized();
    }

private:

    void createMenu()
    {
        QMenu* menuFile = menu->addMenu("&File");

        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_FileIcon),"&New",this, &PasswordManagerWindow::handleMenuItemClick);
        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_DirOpenIcon), "&Open",this, &PasswordManagerWindow::handleOpenFileClick);

        menuFile->addSeparator();
        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_DialogSaveButton),"&Save", this, &PasswordManagerWindow::handleSaveFileClick);
        menuFile->addAction("Save &As...", this,&PasswordManagerWindow::handleSaveFileClick);

        menuFile->addSeparator();
        menuFile->addAction("&Exit", this,&PasswordManagerWindow::close);

        QMenu* menuHelp = menu->addMenu("&Help");
        menuHelp->addAction("&About", this, &PasswordManagerWindow::onAboutClick);
    }

    void handleMenuItemClick() const
    {
        status->showMessage("Status bar...... | ");
    }

    void handleOpenFileClick()
    {
        const QString fileName = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Choose a file"),
            QDir::currentPath(),
            "Text files (*.txt);All files (*.*)");

        const std::string text = FileUtilities::ReadFile(fileName.toStdString().c_str());
        textEditField->setText(text.c_str());
    }

    void handleSaveFileClick()
    {
        const QString fileName = QFileDialog::getSaveFileName(this,
                                                              QString::fromUtf8("Choose a file"),
                                                              QDir::currentPath(),
                                                              "Text files (*.txt);All files (*.*)");
        const std::string file { fileName.toStdString() };
        std::cout << file << std::endl;
    }

    void onAboutClick()
    {
        QMessageBox::about(this, "About", "Simple password manager app"
                                          ".\nVersion 1.0.0\n\n@ 2024 by Andrei Tokmakov.");
    }


public:

    /*
    void OpenDialog()
    {
        std::unique_ptr<QDialog> dialog { std::make_unique<QDialog>() };
        // dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->show();
    }*/
};





// TODO:
//  - Password Dialog on Open
//  - Choose BG color && Text Color
//  - Decrypt / Encrypt password file
//  - list of previously opened files
//  - Store HEADER in file when savin data?


// INFO: Menu: https://ravesli.com/urok-7-sozdanie-menyu-i-paneli-instrumentov-v-qt5/?ysclid=m3tsgy076u360587604

// https://cpp.hotexamples.com/examples/-/QTextEdit/-/cpp-qtextedit-class-examples.html
int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    DarkThemeApplication app(argc, argv);

    // std::unique_ptr<QDialog> dialog { std::make_unique<QDialog>() };
    // dialog->setAttribute(Qt::WA_DeleteOnClose);
    // dialog->show();

    PasswordManagerWindow window;
    window.show();

    return DarkThemeApplication::exec();
}
