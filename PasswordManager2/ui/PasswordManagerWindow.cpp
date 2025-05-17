/**============================================================================
Name        : PasswordManagerWindow.cpp
Created on  : 17.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : PasswordManagerWindow.cpp
============================================================================**/

#include "PasswordManagerWindow.h"

#include <string_view>
#include <filesystem>

#include "FileUtilities.h"
#include "Encryption.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QTreeView>
#include <QInputDialog>
#include <QFileDialog>
#include <QPushButton>

namespace
{
    constexpr std::string_view FOLDER { R"(/home/andtokm/DiskS/Temp/Folder_For_Testing)" };
}

namespace ui
{

    PasswordManagerWindow::PasswordManagerWindow()
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

    void PasswordManagerWindow::createMenu()
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

    void PasswordManagerWindow::handleMenuItemClick() const
    {
        status->showMessage("Status bar...... | ");
    }


    void PasswordManagerWindow::handleOpenFileClick()
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



    void PasswordManagerWindow::handleNewFileClick() // FIXME --> Remove
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


    void PasswordManagerWindow::handleSaveFileClick()
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


    void PasswordManagerWindow::onAboutClick()
    {
        QMessageBox::about(this, "About", "Simple password manager app"
                                          ".\nVersion 1.0.0\n\n@ 2024 by Andrei Tokmakov.");
    }
}
