/**============================================================================
Name        : ListBox.h
Created on  : 17.11.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : ListBox.h
============================================================================**/

#ifndef QTPROJECTS_LISTBOX_H
#define QTPROJECTS_LISTBOX_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

namespace ListBox
{
    class ListWidget : public QWidget {


    public:
        explicit ListWidget(QWidget *parent = 0);

    private slots:
        void addItem();
        void renameItem();
        void removeItem();
        void clearItems();

    private:
        QListWidget *lw;
        QPushButton *add;
        QPushButton *rename;
        QPushButton *remove;
        QPushButton *removeAll;
    };

    void TestAll([[maybe_unused]] int argc,
                 [[maybe_unused]] char** argv);
};

#endif //QTPROJECTS_LISTBOX_H
