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


#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#include <openssl/engine.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/dh.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/stack.h>
#include <openssl/pkcs12.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/evperr.h>
#include <openssl/aes.h>
#include <openssl/crypto.h>


#include "FileUtilities.h"


namespace
{
    static std::vector<uint8_t> str2Bytes(const std::string& message)
    {
        std::vector<uint8_t> out(message.size());
        for (size_t n = 0; n < message.size(); n++) {
            out[n] = message[n];
        }
        return out;
    }

    static std::vector<uint8_t> str2Bytes(std::string_view message)
    {
        std::vector<uint8_t> out(message.size());
        for (size_t n = 0; n < message.size(); n++) {
            out[n] = message[n];
        }
        return out;
    }

    static std::string bytes2Str(const std::vector<uint8_t>& bytes)
    {
        return std::string(bytes.begin(), bytes.end());
    }
}



namespace Encryption
{
    bool encrypt(const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& message,
                 const std::vector<uint8_t>& iv,
                 std::vector<uint8_t>& output)
    {
        output.resize(message.size() * AES_BLOCK_SIZE);
        int outlen = 0;

        std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)> ctx {
                EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free
        };

        if (0 == EVP_EncryptInit(ctx.get(), EVP_aes_256_cbc(), key.data(), iv.data())) {
            std::cerr << "Error: EVP_EncryptInit() failed" << std::endl;
            return false;
        }
        if (0 == EVP_EncryptUpdate(ctx.get(), output.data(), &outlen, message.data(), message.size())) {
            std::cerr << "Error: EVP_EncryptUpdate() failed" << std::endl;
            return false;
        }
        size_t total_out = outlen;
        if (0 == EVP_EncryptFinal(ctx.get(), output.data()+total_out, &outlen)) {
            std::cerr << "Error: EVP_EncryptUpdate() failed" << std::endl;
            return false;
        }

        total_out += outlen;
        output.resize(total_out);

        return true;
    }

    bool decrypt(const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& message,
                 const std::vector<uint8_t>& iv,
                 std::vector<uint8_t>& output)
    {
        output.resize(message.size() * 3);
        std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)> ctx {
                EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free
        };

        int outlen {0 };
        if (0 == EVP_DecryptInit(ctx.get(), EVP_aes_256_cbc(), key.data(), iv.data())) {
            std::cerr << "Error: EVP_EncryptInit() failed" << std::endl;
            return false;
        }
        if (0 == EVP_DecryptUpdate(ctx.get(), output.data(), &outlen, message.data(), message.size())) {
            std::cerr << "Error: EVP_DecryptUpdate() failed" << std::endl;
            return false;
        }
        size_t total_out = outlen;
        if (0 == EVP_DecryptFinal(ctx.get(), output.data() + outlen, &outlen)) {
            std::cerr << "Error: EVP_DecryptUpdate() failed" << std::endl;
            return false;
        }

        total_out += outlen;
        output.resize(total_out);
        return true;
    }


    void Test()
    {
        const std::string iv = "1234567890123456", key = "passwordpasswordpasswordpassword";
        const std::string message = "Some Crypto Text";

        const std::vector<uint8_t> ivBytes { str2Bytes(iv) };
        std::vector<uint8_t> dataEncrypted, dataDecrypted;

        Encryption::encrypt(str2Bytes(key), str2Bytes(message), ivBytes, dataEncrypted);
        Encryption::decrypt(str2Bytes(key), dataEncrypted, ivBytes, dataDecrypted);

        std::cout << bytes2Str(dataEncrypted) << std::endl;
        std::cout << bytes2Str(dataDecrypted) << std::endl;
    }
};

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

    static inline constexpr std::string_view iv = "1234567890123456";
    static inline constexpr std::string_view key = "some_password";

    // TODO: --> std::array
    std::vector<uint8_t> ivBytes { str2Bytes(iv) };

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
            // QDir::currentPath(),
            QDir("/home/andtokm/DiskS/ProjectsUbuntu/QtProjects/PasswordManager/data/").path(),
            "Text files (*.txt);Dat files (*.dat);All files (*.*)");
        const std::filesystem::path filePath { fileName.toStdString() };

        try {
            const std::string fileContent = decryptFileEx(filePath);
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
                QDir("/home/andtokm/DiskS/ProjectsUbuntu/QtProjects/PasswordManager/data/").path());
        const std::filesystem::path filePath { fileName.toStdString() };
        const std::string& content = textEditField->toPlainText().toStdString();

        try {
            const std::vector<uint8_t> bytesEncrypted = encryptContentEx(content);
            FileUtilities::WriteToFileBytes(filePath, bytesEncrypted);
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

private:

    [[nodiscard]]
    std::expected<std::string, std::string> decryptFile(const std::filesystem::path& filePath) const noexcept
    {
        /*
        const std::vector<uint8_t> fileDataBytes = FileUtilities::ReadFileAsBytes(filePath);
        std::vector<uint8_t> dataDecrypted;
        if (!Encryption::decrypt(str2Bytes(key), fileDataBytes, ivBytes, dataDecrypted))
        {
            return std::unexpected("Decrypt failed");
        }
        */

        const std::vector<uint8_t> fileDataBytes = FileUtilities::ReadFileAsBytes(filePath);
        return bytes2Str(fileDataBytes);
    }

    [[nodiscard]]
    std::expected<std::vector<uint8_t>, bool> encryptContent(const std::string& data) const noexcept
    {
        std::vector<uint8_t> dataBytes = str2Bytes(data);
        return dataBytes;


        /*if (Encryption::encrypt(str2Bytes(key), str2Bytes(data), ivBytes, dataBytes)){
            return dataBytes;
        } */

        return std::unexpected(false);
    }

    [[nodiscard]]
    std::string decryptFileEx(const std::filesystem::path& filePath) const
    {
        const std::vector<uint8_t> fileDataBytes = FileUtilities::ReadFileAsBytes(filePath);

        std::vector<uint8_t> dataDecrypted;
        if (!Encryption::decrypt(str2Bytes(key), fileDataBytes, ivBytes, dataDecrypted)) {
            throw std::runtime_error("Decrypt failed");
        }

        return bytes2Str(fileDataBytes);
    }

    [[nodiscard]]
    std::vector<uint8_t> encryptContentEx(const std::string& data) const
    {
        std::vector<uint8_t> dataBytes = str2Bytes(data);
        return dataBytes;


        /*if (Encryption::encrypt(str2Bytes(key), str2Bytes(data), ivBytes, dataBytes)){
            return dataBytes;
        } */

        return std::unexpected(false);
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
//  - Generate CERT, PASS, IV during the CMake ??
//  -
//  - Status bar updates:
//  - 1.  Decrypt / Encrypt
//  - 2.  Open and save file




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
