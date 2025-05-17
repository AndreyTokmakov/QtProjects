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
#include <expected>


#include <QTextEdit>
#include <QWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>
#include <QIcon>
#include <QMenuBar>
#include <QStandardItem>
#include <QTreeView>
#include <QLabel>
#include <QFileDialog>

#include "FileUtilities.h"
#include "Utilities.h"
#include "Encryption.h"


// FIXME
#include "hex.h"
#include "base64.h"
#include "osrng.h"
#include "modes.h"



namespace {

    constexpr std::string_view FOLDER { R"(/home/andtokm/DiskS/Temp/Folder_For_Testing)" };
}


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
    const std::unique_ptr<QStatusBar> status { statusBar() };
    const std::unique_ptr<QTextEdit> textEditField = std::make_unique<QTextEdit>(this);
    const std::unique_ptr<QLabel> statusLabel = std::make_unique<QLabel>(this);

    // static inline constexpr std::string_view iv = "";
    // static inline constexpr std::string_view key = "some_password";
    // std::vector<uint8_t> ivBytes { Utilities::str2Bytes(iv) };
    // std::vector<uint8_t> keyBytes { Utilities::str2Bytes(key) };

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

        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_FileIcon),
                            "&New",this, &PasswordManagerWindow::handleNewFileClick);
        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_DirOpenIcon),
                            "&Open",this, &PasswordManagerWindow::handleOpenFileClick);

        menuFile->addSeparator();
        menuFile->addAction(style()->standardIcon(QStyle::StandardPixmap::SP_DialogSaveButton),
                            "&Save", this, &PasswordManagerWindow::handleSaveFileClick);
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
            // QDir::currentPath(),
            QDir(FOLDER.data()).path(),
            "Dat files (*.dat);All files (*.*)");
        const std::filesystem::path filePath { fileName.toStdString() };

        const std::expected<std::string, std::string> result = Encryption::decryptFile(filePath);
        if (result) {
            const std::string& decryptedText = result.value();
            textEditField->setText(decryptedText.c_str());
            status->showMessage(std::to_string(decryptedText.size()).append(" bytes decrypted").data());
        } else {
            status->showMessage(result.error().data());
        }
    }

    void handleNewFileClick() // FIXME --> Remove
    {
        const QString fileName = QFileDialog::getOpenFileName(this,
                QString::fromUtf8("Choose a file"),
                // QDir::currentPath(),
                QDir(FOLDER.data()).path(),
                "Text files (*.txt);Dat files (*.dat);All files (*.*)");
        const std::filesystem::path filePath { fileName.toStdString() };

        try {
            const std::string fileContent = FileUtilities::ReadFile(filePath);
            textEditField->setText(fileContent.c_str());
        }
        catch (const std::exception& exc) {
            status->showMessage(exc.what());
        }
    }

    void handleSaveFileClick()
    {
        const QString fileName = QFileDialog::getSaveFileName(this,
                QString::fromUtf8("Choose a file"),
                QDir(FOLDER.data()).path());
        const std::filesystem::path filePath { fileName.toStdString() };
        const std::string& content = textEditField->toPlainText().toStdString();

        try {
            const auto encrypted = Encryption::encrypt(content);
            const int32_t bytesWriten = FileUtilities::WriteToFile(filePath, encrypted.value());
            if (bytesWriten == encrypted.value().size()) {
                status->showMessage("File encrypted and stored successfully");
            } else {
                status->showMessage("Failed to write to file");
            }
        }
        catch (const std::exception& exc) {
            status->showMessage(exc.what());
        }
    }

    void onAboutClick()
    {
        QMessageBox::about(this, "About", "Simple password manager app"
                                          ".\nVersion 1.0.0\n\n@ 2024 by Andrei Tokmakov.");
    }

    /*
    void OpenDialog()
    {
        std::unique_ptr<QDialog> dialog { std::make_unique<QDialog>() };
        // dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->show();
    }*/
};


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
