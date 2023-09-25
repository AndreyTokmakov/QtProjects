/**============================================================================
Name        : main.cpp
Created on  :
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : QT Controls
============================================================================**/

#include <QCoreApplication>
#include <QDebug>

#include "TreeView/TreeView.h"
#include "TreeWidget/TreeWidget.h"
#include "ProgressBar/ProgressBar.h"

int main(int argc, char *argv[])
{
    // TreeView::TestAll(argc, argv);
    // TreeWidget::TestAll(argc, argv);
    ProgressBar::TestAll(argc, argv);

    return EXIT_SUCCESS;
}
