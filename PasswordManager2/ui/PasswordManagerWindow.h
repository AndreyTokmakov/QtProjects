/**============================================================================
Name        : PasswordManagerWindow.h
Created on  : 17.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : PasswordManagerWindow.h
============================================================================**/

#ifndef QTPROJECTS_PASSWORDMANAGERWINDOW_H
#define QTPROJECTS_PASSWORDMANAGERWINDOW_H

#include <QTextEdit>
#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>

namespace ui
{
    class PasswordManagerWindow final : public QMainWindow
    {
        const std::unique_ptr<QMenuBar> menu { menuBar() };
        const std::unique_ptr<QStatusBar> status { statusBar() };
        const std::unique_ptr<QTextEdit> textEditField = std::make_unique<QTextEdit>(this);
        const std::unique_ptr<QLabel> statusLabel = std::make_unique<QLabel>(this);

    public:

        PasswordManagerWindow();

    private:

        void createMenu();
        void handleMenuItemClick() const;
        void handleOpenFileClick();
        void handleNewFileClick() ;
        void handleSaveFileClick();
        void onAboutClick();
    };
}


#endif //QTPROJECTS_PASSWORDMANAGERWINDOW_H
