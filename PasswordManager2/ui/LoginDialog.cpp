/**============================================================================
Name        : LoginDialog.cpp
Created on  : 17.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : LoginDialog.cpp
============================================================================**/

#include "LoginDialog.h"

#include <QVBoxLayout>

namespace
{
    using namespace std::string_literals;
}

namespace ui
{
    LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
    {
        resize(300, 100);
        QVBoxLayout *layout = new QVBoxLayout(this);

        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        passwordInput = new QLineEdit();

        layout->addWidget(passwordInput);
        layout->addWidget(buttonBox);


        // QPushButton* ok = buttonBox->button(QDialogButtonBox::Ok);
        // ok->move(50, 110);

        // QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
        // btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &LoginDialog::handleOk);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &LoginDialog::handleCancel);
        // QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(LoginDialog::handleOk()));
    }


    void LoginDialog::handleOk()
    {
        const std::string& text = passwordInput->text().toStdString();
        if (text == "12345"s) {
            return accept();
        }
        return reject();
    }

    void LoginDialog::handleCancel()
    {
        return reject();
    }
}