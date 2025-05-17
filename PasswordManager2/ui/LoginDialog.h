/**============================================================================
Name        : LoginDialog.h
Created on  : 17.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : LoginDialog.h
============================================================================**/

#ifndef QTPROJECTS_LOGINDIALOG_H
#define QTPROJECTS_LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>

namespace ui
{
    struct LoginDialog: QDialog
    {
        explicit LoginDialog(QWidget *parent = nullptr);

        void handleOk();
        void handleCancel();

        QLineEdit* passwordInput;
        QDialogButtonBox* buttonBox { nullptr };
    };
}


#endif //QTPROJECTS_LOGINDIALOG_H
