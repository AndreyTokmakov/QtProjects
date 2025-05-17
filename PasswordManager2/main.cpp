/**============================================================================
Name        : PasswordManager.cpp
Created on  : 17.11.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : PasswordManager.cpp
============================================================================**/

#include <string_view>
#include <vector>

#include "LoginDialog.h"
#include "DarkThemeApplication.h"
#include "PasswordManagerWindow.h"


int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    ui::DarkThemeApplication app(argc, argv);

    std::unique_ptr<ui::LoginDialog> dialog { std::make_unique<ui::LoginDialog>() };
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    if (dialog->exec() != QDialog::Accepted) {
        return EXIT_FAILURE;
    }

    ui::PasswordManagerWindow window;
    window.show();

    return ui::DarkThemeApplication::exec();
}
