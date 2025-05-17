/**============================================================================
Name        : DarkThemeApplication.h
Created on  : 17.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : DarkThemeApplication.h
============================================================================**/

#ifndef QTPROJECTS_DARKTHEMEAPPLICATION_H
#define QTPROJECTS_DARKTHEMEAPPLICATION_H

#include <QApplication>
#include <QMenuBar>

namespace ui
{
    struct DarkThemeApplication final : public QApplication
    {
        DarkThemeApplication(int &argc, char **argv);

    private:

        static QColor makeColor(const int32_t red = 0, const int32_t green = 0, const int32_t blue = 0) noexcept;
        static void enableDarkMode();
    };
}

#endif //QTPROJECTS_DARKTHEMEAPPLICATION_H
