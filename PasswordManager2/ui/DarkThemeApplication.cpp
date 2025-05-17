/**============================================================================
Name        : DarkThemeApplication.cpp
Created on  : 17.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : DarkThemeApplication.cpp
============================================================================**/

#include "DarkThemeApplication.h"

namespace ui
{
    DarkThemeApplication::DarkThemeApplication(int &argc, char **argv) : QApplication(argc, argv) {
        enableDarkMode();
    }

    QColor DarkThemeApplication::makeColor(const int32_t red, const int32_t green, const int32_t blue) noexcept
    {
        return QColor(red, green, blue);
    }

    void DarkThemeApplication::enableDarkMode()
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
}